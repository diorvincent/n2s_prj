/*!
    \file  BF7006BMxx_can.c
    \brief can driver
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_can.c initial version

*/

#include "BF7006BMxx_can.h"
#include "BF7006BMxx_sysctrl.h"
#include "BF7006BMxx_gpio.h"

//CAN_TX    PE6
//CAN_RX    PE7
static ErrorStatus can_baud_set(can_clk_enum can_clk,uint8_t can_baud);
static ErrorStatus can_filter_init(can_filter_parameter_struct can_filter_parameter);

/*!
    \brief      initialize can
    \param[in]  can_parameter_init: parameters for CAN initializtion
      \arg        working_mode: CAN_NOMARL,CAN_MODE_LISTEN_ONLY, CAN_MODE_SELF_TEST, CAN_MODE_SELF_RECEIVE
      \arg        resync_jump_width: CAN_BTR0_SJW_SET(x)(x=0,1, 2, 3)
    \arg        can_clk:CAN_CLK_32M,CAN_CLK_16M,CAN_CLK_8M
      \arg        can_baud: CAN_BAUD_50K,CAN_BAUD_100K,CAN_BAUD_125K,CAN_BAUD_200K,CAN_BAUD_250K,CAN_BAUD_400K,CAN_BAUD_500K,CAN_BAUD_800K,CAN_BAUD_1M
      \arg        sampling_times: 0-sample 1 timers,1-sample 2 timers
      \arg        error_alarm_count: error alarm count 
    \param[in]  can_filter_parameter: can filter parameters initializtion
      \arg        filter_mode: CAN_SINGLE_FILTER,CAN_DOUBLE_FILTER
      \arg        filter_frame: CAN_STANDARD_FRAME,CAN_EXTENDED_FRAME
      \arg        filter_RTR: CAN_REMOTE_FRAME,CAN_DATA_FRAME
      \arg        filter_single_id: single filter id:bit10~0 in standard mode,bit28~0 in extended mode
      \arg        filter_data0: single filter:only standard mode;double filter:only standard mode
      \arg        filter_data1: single filter:only in filter standard mode
      \arg        filter_mask_single_id: single filter:bit10~0 in standard mode,bit28~0 in extended mode
      \arg        filter_mask_data0: single filter:only standard mode;double filter:only standard mode
      \arg        filter_mask_data1: single filter:only standard mode
      \arg        filter_mask_RTR: ENABLE or DISABLE
      \arg        filter_double_id0: double filter:bit10~0 in standard mode,bit15~0 in extended mode
      \arg        filter_double_id1: double filter:bit10~0 in standard mode,bit15~0 in extended mode
      \arg        filter_mask_double_id0: double filter:bit10~0 in standard mode,bit15~0 in extended mode
      \arg        filter_mask_double_id1: double filter:bit10~0 in standard mode,bit15~0 in extended mode
    \param[out] none
    \retval     ErrorStatus: ERROR or SUCCESS
*/
ErrorStatus can_init(can_parameter_struct can_parameter_init,can_filter_parameter_struct can_filter_parameter)
{

    // xtal as clock source and fails to initialize
    if(is_xtal_init_success == XTAL_Init_Status_Init_Failed){
        can_module_disable(); 
        return ERROR;
    }

    can_module_rst();
    SYS_CAN_DOMAIN = 4U;
    can_module_enable();
    /* can set in reset mode */
    CAN_MOD |= CAN_MOD_RM;

    /* can work mode set */
    switch(can_parameter_init.working_mode){
        case CAN_MODE_LISTEN_ONLY:
            CAN_MOD |= CAN_MOD_LOM;
            break;
        case CAN_MODE_SELF_TEST:
            CAN_MOD |= CAN_MOD_STM;
            break;
        case CAN_MODE_SELF_RECEIVE:
            CAN_CMR |= CAN_CMR_SRR;
            break;
        case CAN_NOMARL:
            break;
    }

    /* can baud rate set */
    (void)can_baud_set(can_parameter_init.can_clk,can_parameter_init.can_baud);
    CAN_BTR0 |= can_parameter_init.resync_jump_width;
    CAN_BTR1 |= can_parameter_init.sampling_times;
    
    /* can error alarm count set */
    CAN_EMLR = ((uint32_t)can_parameter_init.error_alarm_count & 0x000000FFUL);
    
    /* can filter set */
    (void)can_filter_init(can_filter_parameter);
    
    /* can exit reset mode */
    CAN_MOD &= ~CAN_MOD_RM;
    
    can_int_enable(can_parameter_init.int_enable);
    if((can_parameter_init.nvic_int_enable & CAN_WU_NVIC_ENABLE) != 0U){
        NVIC_EnableIRQ(CAN_WAKE_IRQn);
    }else{
        NVIC_DisableIRQ(CAN_WAKE_IRQn);
    }
    if((can_parameter_init.nvic_int_enable & CAN_ERR_NVIC_ENABLE) != 0U){
        NVIC_EnableIRQ(CAN_ERR_IRQn);
    }else{
        NVIC_DisableIRQ(CAN_ERR_IRQn);
    }
    if((can_parameter_init.nvic_int_enable & CAN_RX_NVIC_ENABLE) != 0U){
        NVIC_EnableIRQ(CAN_RX_IRQn);
    }else{
        NVIC_DisableIRQ(CAN_RX_IRQn);
    }
    if((can_parameter_init.nvic_int_enable & CAN_TX_NVIC_ENABLE) != 0U){
        NVIC_EnableIRQ(CAN_TX_IRQn);
    }else{
        NVIC_DisableIRQ(CAN_TX_IRQn);
    }
    return SUCCESS;
}

/*!
    \brief      can receive message
    \param[in]  none
    \param[out]  can_frame_struct: parameters for can receive
      \arg        sfid: standard frame id bit10~0
      \arg        rx_efid: extended frame id bit28~0
      \arg        ff: CAN_STANDARD_FRAME,CAN_EXTENDED_FRAME
      \arg        rx_ft: CAN_REMOTE_FRAME,CAN_DATA_FRAME
      \arg        rx_dlen: can transmit data lenth bit3~0
      \arg        rx_data[8]: can transmit data
    \retval     ErrorStatus: ERROR or SUCCESS
*/
ErrorStatus can_receive_message(can_frame_struct *receive_data)
{
    uint8_t i;
    /* can received message */
    if((CAN_IF & CAN_IF_RI) != 0U){
        uint32_t tmp[4];
        tmp[0] = CAN_ID0;
        tmp[1] = CAN_ID1;
        tmp[2] = CAN_ID2;
        tmp[3] = CAN_ID3;

        /* save recive frame format and id */
        if((CAN_FRCTL & CAN_FRCTL_FF) != 0U){
            receive_data->ff = CAN_EXTENDED_FRAME;
            receive_data->efid = (uint32_t)((tmp[0] << 21U) | (tmp[1] << 13U) | (tmp[2] << 5U) | (tmp[3] >> 3U));
        }else{
            receive_data->ff = CAN_STANDARD_FRAME;
            receive_data->sfid = (uint32_t)((tmp[0] << 3U) | (tmp[1] >> 5U));
        }

        /* save receive frame type */
        if((CAN_FRCTL & CAN_FRCTL_RTR) != 0U){
            receive_data->ft = CAN_REMOTE_FRAME;
        }else{
            receive_data->ft = CAN_DATA_FRAME;
        }

        /* save receive data lenth */
        tmp[0] = CAN_FRCTL;
        receive_data->dlen = (uint8_t)(tmp[0] & CAN_FRCTL_DLC);
        if(receive_data->dlen > 0x08U){
            receive_data->dlen = 0x08U;
        }

        /* save receive data */
        for(i=0U;i<receive_data->dlen;i++){
            tmp[0] = CAN_DATA(i);
            receive_data->data[i] = (uint8_t)tmp[0];
        }
        /* release receive buffer */
        CAN_CMR |= CAN_CMR_RRB;
        return SUCCESS;
    }
    return ERROR;
}
/*!
    \brief      can transmit message
    \param[in]  can_frame_struct: parameters for can transmit
      \arg        sfid: standard frame id bit10~0
      \arg        tx_efid: extended frame id bit28~0
      \arg        ff: CAN_STANDARD_FRAME,CAN_EXTENDED_FRAME
      \arg        ft: CAN_REMOTE_FRAME,CAN_DATA_FRAME
      \arg        dlen: can transmit data lenth bit3~0
      \arg        tx_data[8]: can transmit data
    \param[out] none
    \retval     ErrorStatus: ERROR or SUCCESS
*/
ErrorStatus can_transmit_message(can_frame_struct *transmit_data)
{
    uint8_t tmp_frame;
    uint8_t tmp_id[4] = {0x00,0x00,0x00,0x00};
    if(transmit_data == NULL){
        return ERROR;
    }
    if((CAN_SR & (CAN_SR_TCS | CAN_SR_TBS)) == (CAN_SR_TCS | CAN_SR_TBS)){
        if(transmit_data->ff == CAN_STANDARD_FRAME){    //standard frame
            tmp_id[0] = (uint8_t)(transmit_data->sfid >> 3);
            tmp_id[1] = (uint8_t)(transmit_data->sfid << 5);
        }else{  //extended frame
            tmp_id[0] = (uint8_t)(transmit_data->efid >> 21);
            tmp_id[1] = (uint8_t)(transmit_data->efid >> 13);
            tmp_id[2] = (uint8_t)(transmit_data->efid >> 5);
            tmp_id[3] = (uint8_t)(transmit_data->efid << 3);
        }
        tmp_frame = (transmit_data->dlen & 0x0fU);
        if((transmit_data->ff) != CAN_STANDARD_FRAME){
            tmp_frame |= 0x80U;
        }
        if((transmit_data->ft) != CAN_DATA_FRAME){
            tmp_frame |= 0x40U;
        }
        /* set frame foramt, type and transmit data lenth */
        CAN_FRCTL = tmp_frame;

        /* ready for transmitting id */
        CAN_ID0 = tmp_id[0];
        CAN_ID1 = tmp_id[1];
        CAN_ID2 = tmp_id[2];
        CAN_ID3 = tmp_id[3];

        /* ready for transmitting data */
        CAN_DATA0 = transmit_data->data[0];
        CAN_DATA1 = transmit_data->data[1];
        CAN_DATA2 = transmit_data->data[2];
        CAN_DATA3 = transmit_data->data[3];
        CAN_DATA4 = transmit_data->data[4];
        CAN_DATA5 = transmit_data->data[5];
        CAN_DATA6 = transmit_data->data[6];
        CAN_DATA7 = transmit_data->data[7];

        return SUCCESS;
    }
    return ERROR;
}

/*!
    \brief      can baud set
    \param[in]  canclk: can module clock
    \param[in]        can_baud: set can baud,CAN_BAUD_50K,CAN_BAUD_100K,CAN_BAUD_125K,CAN_BAUD_200K,CAN_BAUD_250K,
                                            CAN_BAUD_400K,CAN_BAUD_500K, 
                                            CAN_BAUD_800K,CAN_BAUD_1M---invalid if can_clk=CAN_CLK_8M 
    \param[out] none
    \retval     SUCCESS or ERROR
*/
static ErrorStatus can_baud_set(can_clk_enum can_clk,uint8_t can_baud)
{
    /* sample point in 75% ~ 88% */
    uint8_t perscaler;
    uint8_t seg1;
    uint8_t seg2;
    ErrorStatus rtal;
    switch(can_baud){
        case CAN_BAUD_50K:
            if(can_clk == CAN_CLK_8M){
                perscaler = 3U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_16M){
                perscaler = 7U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_32M){
                perscaler = 15U;
                rtal = SUCCESS;
            }else{
                perscaler = 0U;
                rtal = ERROR;
            }
            seg1 = 13U;
            seg2 = 4U;
            break;
        case CAN_BAUD_100K:
            if(can_clk == CAN_CLK_8M){
                perscaler = 1U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_16M){
                perscaler = 3U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_32M){
                perscaler = 7U;
                rtal = SUCCESS;
            }else{
                perscaler = 0U;
                rtal = ERROR;
            }
            seg1 = 13U;
            seg2 = 4U;
            break;
        case CAN_BAUD_125K:
            if(can_clk == CAN_CLK_8M){
                perscaler = 1U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_16M){
                perscaler = 3U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_32M){
                perscaler = 7U;
                rtal = SUCCESS;
            }else{
                perscaler = 0U;
                rtal = ERROR;
            }
            seg1 = 10U;
            seg2 = 3U;
            break;
        case CAN_BAUD_200K:
            if(can_clk == CAN_CLK_8M){
                perscaler = 0U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_16M){
                perscaler = 1U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_32M){
                perscaler = 3U;
                rtal = SUCCESS;
            }else{
                perscaler = 0U;
                rtal = ERROR;
            }
            seg1 = 13U;
            seg2 = 4U;
            break;
        case CAN_BAUD_250K:
            if(can_clk == CAN_CLK_8M){
                perscaler = 0U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_16M){
                perscaler = 1U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_32M){
                perscaler = 3U;
                rtal = SUCCESS;
            }else{
                perscaler = 0U;
                rtal = ERROR;
            }
            seg1 = 10U;
            seg2 = 3U;
            break;
        case CAN_BAUD_400K:
            if(can_clk == CAN_CLK_8M){
                perscaler = 0x00U;
                seg1 = 5U;
                seg2 = 2U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_16M){
                perscaler = 0x00U;
                seg1 = 13U;
                seg2 = 4U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_32M){
                perscaler = 0x01U;
                seg1 = 13U;
                seg2 = 4U;
                rtal = SUCCESS;
            }else{
                perscaler = 0U;
                seg1 = 0U;
                seg2 = 0U;
                rtal = ERROR;
            }
            break;
        case CAN_BAUD_500K:
            if(can_clk == CAN_CLK_8M){
                perscaler = 0x00U;
                seg1 = 4U;
                seg2 = 1U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_16M){
                perscaler = 0x00U;
                seg1 = 10U;
                seg2 = 3U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_32M){
                perscaler = 0x01U;
                seg1 = 10U;
                seg2 = 3U;
                rtal = SUCCESS;
            }else{
                perscaler = 0U;
                seg1 = 0U;
                seg2 = 0U;
                rtal = ERROR;
            }
            break;
        case CAN_BAUD_800K:
            if(can_clk == CAN_CLK_16M){
                perscaler = 0x00U;
                seg1 = 5U;
                seg2 = 2U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_32M){
                perscaler = 0x00U;
                seg1 = 13U;
                seg2 = 4U;
                rtal = SUCCESS;
            }else{
                perscaler = 0U;
                seg1 = 0U;
                seg2 = 0U;
                rtal = ERROR;
            }
            break;
        case CAN_BAUD_1M:
            if(can_clk == CAN_CLK_16M){
                perscaler = 0x00U;
                seg1 = 4U;
                seg2 = 1U;
                rtal = SUCCESS;
            }else if(can_clk == CAN_CLK_32M){
                perscaler = 0x00U;
                seg1 = 10U;
                seg2 = 3U;
                rtal = SUCCESS;
            }else{
                perscaler = 0U;
                seg1 = 0U;
                seg2 = 0U;
                rtal = ERROR;
            }
            break;
        default:
            perscaler = 0x00U;
            seg1 = 0U;
            seg2 = 0U;
            rtal = ERROR;
            break;
    }
    if(rtal == SUCCESS){
        CAN_BTR0 = perscaler;
        CAN_BTR1 = ((seg2 << 4U) | seg1);
    }
    return rtal;
}


/*!
    \brief      can transmit request
    \param[in]  none
    \param[out] none
    \retval     none
*/

void can_transmit_request(void)
{
    can_int_flag_clr(CAN_IF_TI);
    /* enable can transmit */
    CAN_CMR |= CAN_CMR_TR;
}

/*!
    \brief      wait for can transmit complete
    \param[in]  none
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrorStatus can_wait_trans(void)
{
    uint32_t timeout = 30000U;
    while(timeout != 0x00U){
        timeout --;
        if((can_interrupt_flag_get() & CAN_IF_TI) != 0x00U){
            can_int_flag_clr((uint8_t)(0x01UL << 1));
            return SUCCESS;
        }
    }
    can_int_flag_clr((uint8_t)(0x01UL << 1));
    return ERROR;
}

/*!
    \brief      can filter initializtion
    \param[in]  can_filter_parameter: can filter parameters initializtion
      \arg        filter_mode: CAN_SINGLE_FILTER,CAN_DOUBLE_FILTER
      \arg        filter_frame: CAN_STANDARD_FRAME,CAN_EXTENDED_FRAME
      \arg        filter_RTR: CAN_REMOTE_FRAME,CAN_DATA_FRAME
      \arg        filter_single_id: single filter id:bit10~0 in standard mode,bit28~0 in extended mode
      \arg        filter_data0: single filter:only standard mode;double filter:only standard mode
      \arg        filter_data1: single filter:only in filter standard mode
      \arg        filter_mask_single_id: single filter:bit10~0 in standard mode,bit28~0 in extended mode
      \arg        filter_mask_data0: single filter:only standard mode;double filter:only standard mode
      \arg        filter_mask_data1: single filter:only standard mode
      \arg        filter_mask_RTR: ENABLE or DISABLE
      \arg        filter_double_id0: double filter:bit10~0 in standard mode,bit15~0 in extended mode
      \arg        filter_double_id1: double filter:bit10~0 in standard mode,bit15~0 in extended mode
      \arg        filter_mask_double_id0: double filter:bit10~0 in standard mode,bit15~0 in extended mode
      \arg        filter_mask_double_id1: double filter:bit10~0 in standard mode,bit15~0 in extended mode
    \param[out] none
    \retval     ErrorStatus: ERROR or SUCCESS
*/
static ErrorStatus can_filter_init(can_filter_parameter_struct can_filter_parameter)
{
    uint8_t tmp_id[4] = {0x00U,0x00U,0x00U,0x00U};
    uint8_t tmp_mask[4] = {0xffU,0xffU,0xffU,0xffU};
    can_filter_parameter_struct *can_filter;
    can_filter = &can_filter_parameter;
    if(can_filter->filter_mode == CAN_SINGLE_FILTER){    //single filter
        if(can_filter->filter_frame == CAN_STANDARD_FRAME){    //standard frame
            tmp_id[0] = (uint8_t)(can_filter->filter_single_id >> 3);
            tmp_id[1] = (uint8_t)(can_filter->filter_single_id << 5);
            if((can_filter->filter_RTR) != CAN_DATA_FRAME){
                tmp_id[1] |= ((uint8_t)0x01 << 4);
            }else{
                tmp_id[1] &= ~((uint8_t)0x01 << 4);
            }
            tmp_id[2] = can_filter->filter_data0;
            tmp_id[3] = can_filter->filter_data1;
            tmp_mask[0] = (uint8_t)(can_filter->filter_mask_single_id >> 3);
            tmp_mask[1] = (uint8_t)((can_filter->filter_mask_single_id << 5) | 0x1FU);
            if((can_filter->filter_mask_RTR) != DISABLE){
                tmp_mask[1] &= ~((uint8_t)0x01 << 4);
            }else{
                tmp_mask[1] |= ((uint8_t)0x01 << 4);
            }
            tmp_mask[2] = can_filter->filter_mask_data0;
            tmp_mask[3] = can_filter->filter_mask_data1;
        }else{  //extened frame
            tmp_id[0] = (uint8_t)(can_filter->filter_single_id >> 21);
            tmp_id[1] = (uint8_t)(can_filter->filter_single_id >> 13);
            tmp_id[2] = (uint8_t)(can_filter->filter_single_id >> 5);
            tmp_id[3] = (uint8_t)(can_filter->filter_single_id << 3); 
            if(can_filter->filter_RTR != CAN_DATA_FRAME){
                tmp_id[3] |= ((uint8_t)0x01 << 2);
            }else{
                tmp_id[3] &= ~((uint8_t)0x01 << 2);
            }
            tmp_mask[0] = (uint8_t)(can_filter->filter_mask_single_id >> 21);
            tmp_mask[1] = (uint8_t)(can_filter->filter_mask_single_id >> 13);
            tmp_mask[2] = (uint8_t)(can_filter->filter_mask_single_id >> 5);
            tmp_mask[3] = (uint8_t)(((uint8_t)(can_filter->filter_mask_single_id << 3)) | 0x07U);        
            if((can_filter->filter_mask_RTR) != DISABLE){
                tmp_mask[3] &= ~((uint8_t)0x01 << 2);
            }else{
                tmp_mask[3] |= ((uint8_t)0x01 << 2);
            }
        }
        CAN_MOD |= CAN_MOD_AFM;
    }else{  //double filter
        if(can_filter->filter_frame == CAN_STANDARD_FRAME){    //standard frame
            tmp_id[0] = (uint8_t)(can_filter->filter_double_id0 >> 3);
            tmp_id[1] = (uint8_t)((can_filter->filter_double_id0 << 5) | 
                        ((can_filter->filter_data0_std >> 4) & 0x0fU));
            if(can_filter->filter_RTR != CAN_DATA_FRAME){
                tmp_id[1] |= (0x01U << 4);
            }else{
                tmp_id[1] &= ~(0x01U << 4);
            }
            tmp_id[2] = (uint8_t)(can_filter->filter_double_id1 >> 3);
            tmp_id[3] = (uint8_t)((can_filter->filter_double_id1 << 5) | 
                        (can_filter->filter_data0_std & 0x0fU));
            if(can_filter->filter_RTR != CAN_DATA_FRAME){
                tmp_id[3] |= (0x01U << 4);
            }else{
                tmp_id[3] &= ~(0x01U << 4);
            }

            tmp_mask[0] = (uint8_t)(can_filter->filter_mask_double_id0 >> 3);
            tmp_mask[1] = (uint8_t)((can_filter->filter_mask_double_id0 << 5) | 
                          ((can_filter->filter_mask_data0_std >> 4) & 0x0fU));
            tmp_mask[2] = (uint8_t)(can_filter->filter_mask_double_id1 >> 3);
            tmp_mask[3] = (uint8_t)((can_filter->filter_mask_double_id1 << 5) | 
                          (can_filter->filter_mask_data0_std & 0x0fU));
            if((can_filter->filter_mask_RTR) != DISABLE){
                tmp_mask[1] &= ~((uint8_t)0x01 << 4);
            }else{
                tmp_mask[1] |= ((uint8_t)0x01 << 4);
            }
            if((can_filter->filter_mask_RTR) != DISABLE){
                tmp_mask[3] &= ~((uint8_t)0x01 << 4);
            }else{
                tmp_mask[3] |= ((uint8_t)0x01 << 4);
            }
        }else{    //extened frame
            tmp_id[0] = (uint8_t)(can_filter->filter_double_id0 >> 21);
            tmp_id[1] = (uint8_t)(can_filter->filter_double_id0 >> 13);
            tmp_id[2] = (uint8_t)(can_filter->filter_double_id1 >> 21);
            tmp_id[3] = (uint8_t)(can_filter->filter_double_id1 >> 13);
            tmp_mask[0] = (uint8_t)(can_filter->filter_mask_double_id0 >> 8);
            tmp_mask[1] = (uint8_t)can_filter->filter_mask_double_id0;
            tmp_mask[2] = (uint8_t)(can_filter->filter_mask_double_id1 >> 8);
            tmp_mask[3] = (uint8_t)can_filter->filter_mask_double_id1;
        }
        CAN_MOD &= ~CAN_MOD_AFM;
    }
    CAN_IDAR0 = tmp_id[0];
    CAN_IDAR1 = tmp_id[1];
    CAN_IDAR2 = tmp_id[2];
    CAN_IDAR3 = tmp_id[3];
    CAN_IDMR0 = tmp_mask[0];
    CAN_IDMR1 = tmp_mask[1];
    CAN_IDMR2 = tmp_mask[2];
    CAN_IDMR3 = tmp_mask[3];
    return SUCCESS;
}

/*!
    \brief      read frame error code
    \param[in]  none
    \param[out] none
    \retval     frame error code
*/
uint8_t can_read_frame_error_code(void)
{
    uint32_t retal;
    retal = CAN_ECC;
    CAN_CLRECC = 0x01;
    return (uint8_t)retal;
}

/*!
    \brief      read arbitration lost code
    \param[in]  none
    \param[out] none
    \retval     arbitration lost code
*/
uint8_t can_read_arbitration_lost_code(void)
{
    uint32_t retal;
    retal = CAN_ALC;
    return (uint8_t)retal;

}

/*!
    \brief      can transmit abort
    \param[in]  none
    \param[out] none
    \retval     none
*/
void can_transmit_abort(void)
{
    CAN_CMR |= (CAN_CMR_AT | CAN_CMR_TR);
}

/*!
    \brief      can sleep config 
    \param[in]  wakeup_mode: only valid in sleeping mode
                    0--can wakes on any dominant level on the CAN bus
                    1--can wakes only in case of a dominant pulse on the CAN bus that has a length of 2us
    \param[in]    filter_en: only valid in sleepdeep mode
                    0--can wakes on any dominant level on the CAN bus
                    1--can wakes only in case of a dominant pulse on the CAN bus that has a length of 1.5us
    \param[in]  state: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void can_sleep_config(uint8_t wakeup_mode,uint8_t filter_en,FunctionalState state)
{
    if(state == ENABLE){
        CAN_WUP |= CAN_WUP_ENABLE;
    }else{
        CAN_WUP &= ~CAN_WUP_ENABLE;
    }
    if(wakeup_mode != 0U){
        CAN_WUP |= CAN_WUP_MODE;
    }else{
        CAN_WUP &= ~CAN_WUP_MODE;
    }
    if(filter_en != 0U){
        CAN_FILTER_EN = 0x01U;
    }else{
        CAN_FILTER_EN = 0x00U;
    }
}

/*!
    \brief      can sleep request
    \param[in]  none
    \param[out] none
    \retval     SUCCESS--can step in sleep success,ERROR--can step in sleep fail
*/
ErrorStatus can_sleep_request(void)
{
    uint32_t timeout = 30000U;
    CAN_CMR |= CAN_CMR_SPM;
    while(timeout != 0x00U){
        timeout --;
        if(CAN_SLPAK != 0x00U){
            return SUCCESS;
        }
    }
    return ERROR;
}

/*!
    \brief      get can fifo frame number
    \param[in]  none
    \param[out] none
    \retval     fifo frame number
*/
uint8_t can_get_fifo_num(void)
{
    uint32_t retal;
    retal = CAN_RMC;
    return (uint8_t)retal;
}

/*!
    \brief      can interrupt enable
    \param[in]  state: CAN_IER_RIE,CAN_IER_TIE,CAN_IER_EIE,CAN_IER_DOIE,CAN_IER_WUIE,
                       CAN_IER_EPIE,CAN_IER_ALIE,CAN_IER_BEIE
    \param[out] none
    \retval     none
*/
void can_int_enable(uint8_t intstate)
{
    CAN_IE |= intstate;
}

/*!
    \brief      can interrupt disable
    \param[in]  state: CAN_IER_RIE,CAN_IER_TIE,CAN_IER_EIE,CAN_IER_DOIE,CAN_IER_WUIE,
                       CAN_IER_EPIE,CAN_IER_ALIE,CAN_IER_BEIE
    \param[out] none
    \retval     none
*/
void can_int_disable(uint8_t intstate)
{
    CAN_IE &= ~intstate;
}

/*!
    \brief      get can interrupt flag 
    \param[in]  none
    \param[out] none
    \retval     can interrupt flag
*/
uint8_t can_interrupt_flag_get(void)
{
    uint32_t retal;
    retal = CAN_IF;
    return (uint8_t)retal;
}

/*!
    \brief      can interrupt flag clear
    \param[in]  int_flag: CAN_IF_BEI,CAN_IF_ALI,CAN_IF_EPI,CAN_IF_WUPI,CAN_IF_DOI,CAN_IF_EI,CAN_IF_TI
    \param[out] none
    \retval     none
*/
void can_int_flag_clr(uint8_t int_flag)
{
    CAN_CLRISR = int_flag;
    SYS_CAN_SPWKFLAG = 0x01U;
}

/*!
    \brief      get can status  
    \param[in]  none
    \param[out] none
    \retval     can status 
*/
uint8_t can_status_get(void)
{
    uint32_t retal;
    retal = CAN_SR;
    return (uint8_t)retal;
}

/*!
    \brief      can wait transmit frame
    \param[in]  transmit_data: parameters for can transmit
      \arg        sfid: standard frame id bit10~0
      \arg        tx_efid: extended frame id bit28~0
      \arg        ff: CAN_STANDARD_FRAME,CAN_EXTENDED_FRAME
      \arg        ft: CAN_REMOTE_FRAME,CAN_DATA_FRAME
      \arg        dlen: can transmit data lenth bit3~0
      \arg        tx_data[8]: can transmit data
    \param[out] none
    \retval     can status 
*/
void can_wait_transmit_frame(can_frame_struct *transmit_data)
{
    (void)can_transmit_message(transmit_data);
    can_transmit_request();
    (void)can_wait_trans();
}

/*!
    \brief      get can tx error count
    \param[in]  none
    \param[out] none
    \retval     tx error count
*/
uint8_t can_get_txerrcnt(void)
{
    uint32_t retal;
    retal = CAN_TXERR;
    return (uint8_t)retal;
}

/*!
    \brief      get can rx error count
    \param[in]  none
    \param[out] none
    \retval     rx error count
*/
uint8_t can_get_rxerrcnt(void)
{
    uint32_t retal;
    retal = CAN_RXERR;
    return (uint8_t)retal;
}

/*!
    \brief      can module reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void can_module_rst(void)
{
    SYS_CAN_RST = 0x00U;
    SYS_CAN_RST = 0x01U;
}

/*!
    \brief      can clock select 
    \param[in]  can_clock: CAN_XTAL_CLOCK or CAN_PLL_CLOCK
    \param[out] none
    \retval     none
*/
ErrorStatus can_clock_sel(uint8_t can_clock)
{
    ErrorStatus rval;

    if(can_clock == CAN_XTAL_CLOCK){
        if((SYS_XTAL_CTRL & SYS_XTAL_CTRL_INIT) == 0x00U){
            rval = xtal_init();
            if(rval == ERROR){
                return ERROR;
            }
        }
    }
    SYS_CAN_CLKSEL = can_clock;
    return SUCCESS;
}

/*!
    \brief      can tx buff empty judge
    \param[in]  none
    \param[out] none
    \retval     TRUE or FALSE
*/
bool is_can_txbuf_empty(void)
{
    bool rtal;
    if((CAN_SR & CAN_SR_TBS) == CAN_SR_TBS){
        rtal = TRUE;
    }else{
        rtal = FALSE;
    }
    return rtal;
}

/*!
    \brief      can module enable
    \param[in]  none
    \param[out] none
    \retval     none
*/
void can_module_enable(void)
{
    CAN_ENABLE = 1U;
}

/*!
    \brief      can module disable
    \param[in]  none
    \param[out] none
    \retval     none
*/
void can_module_disable(void)
{
    CAN_ENABLE = 0U;
}

