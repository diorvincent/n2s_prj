/*!
    \file  BF7006BMxx_sci.c
    \brief sci driver
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_app_sci.c initial version

*/

#include "BF7006BMxx_sci.h"
#include "BF7006BMxx_gpio.h"
#include "BF7006BMxx_sysctrl.h"

/*!
    \brief      initialize sci 
    \param[in]  scix: SCIx(x = 0,1) 
    \param[in]  sci_parameter_init: sci initialize parameter
      \arg        baud_rate: SCI_BAUD_RATE_4800,SCI_BAUD_RATE_9600,SCI_BAUD_RATE_19200,
                             SCI_BAUD_RATE_38400,SCI_BAUD_RATE_57600,SCI_BAUD_RATE_115200
      \arg        work_mode: SCI_CYCLE_MODE,SCI_SINGLE_MODE,SCI_NORMAL_MODE
      \arg        work_mode: SCI_CYCLE_MODE,SCI_SINGLE_MODE,SCI_NORMAL_MODE
      \arg        stop_bit_width: SCI_STOP_BIT_1BIT,SCI_STOP_BIT_2BITS
      \arg        data_bit_width: SCI_DATA_BIT_8BITS,SCI_DATA_BIT_9BITS
      \arg        parity_en: SCI_PARITY_ENABLE,SCI_PARITY_DISABLE
      \arg        parity_sel: SCI_PARITY_ODD,SCI_PARITY_EVEN
      \arg        break_tx_size: SCI_BREAK_TX_SIZE_13BITS,SCI_BREAK_TX_SIZE_10BITS
      \arg        break_check_en: SCI_BREAK_CHECK_ENABLE,SCI_BREAK_CHECK_DISABLE
      \arg        rate_automatch_en: SCI_RATE_AUTOMATCH_ENABLE,SCI_RATE_AUTOMATCH_DISABLE
      \arg        tx_en: SCI_TX_ENABLE,SCI_TX_DISABLE
      \arg        rx_en: SCI_RX_ENABLE,SCI_RX_DISABLE
      \arg        idle_sel: SCI_IDLE_SEL_STARTBIT,SCI_IDLE_SEL_STOPBIT
      \arg        wake_sel: SCI_WAKE_SEL_ADDRRECE,SCI_WAKE_SEL_IDLE
      \arg        tx_inversion_en: SCI_TX_INV_DISABLE,SCI_TX_INV_ENABLE
      \arg        rwu_idlesel: SCI_RWU_IDLESEL_ENABLE,SCI_RWU_IDLESEL_DISABLE
      \arg        int_enable: SCI_BREAK_CHECK_INT,SCI_RX_EDG_INT,SCI_TX_EMPTY_INT,SCI_TX_COMP_INT,
                              SCI_RX_FULL_INT,SCI_IDLE_INT,SCI_RX_OVERFLOW_INT,SCI_NOSIE_ERR_INT,
                              SCI_FRAME_ERR_INT,SCI_PARITY_ERR_INT
    \param[out] none
    \retval     SUCCESS
*/
ErrorStatus sci_init(uint32_t scix,sci_parameter_struct sci_parameter_init)
{
    uint16_t tmp;
    uint8_t temp;
    if(sci_parameter_init.baud_rate != 0U){
        tmp = (uint16_t)((SystemCoreClock/sci_parameter_init.baud_rate) >> 4);
        SCI_BDH(scix) = (tmp >> 8);
        SCI_BDL(scix) = tmp;
        SCI_C1(scix) = (sci_parameter_init.work_mode | sci_parameter_init.stop_bit_width | sci_parameter_init.data_bit_width | 
                        sci_parameter_init.wake_sel | sci_parameter_init.idle_sel | sci_parameter_init.parity_en | sci_parameter_init.parity_sel);
        SCI_BDH(scix) |= ((sci_parameter_init.int_enable >> 8) | sci_parameter_init.rate_automatch_en);
        SCI_C2(scix) = ((sci_parameter_init.int_enable & 0xf0U) | sci_parameter_init.tx_en | sci_parameter_init.rx_en);
        SCI_S2(scix) = (sci_parameter_init.rwu_idlesel | sci_parameter_init.break_tx_size | sci_parameter_init.break_check_en);
        SCI_C3(scix) = (sci_parameter_init.tx_inversion_en | (sci_parameter_init.int_enable & 0x0fU));
        temp = sci_parameter_init.nvic_enable;
        sci_rx_edge_int_flag_clr(scix);
        sci_break_int_flag_clr(scix);

        if(scix == SCI0){
            if((temp & SCI_NVIC_ERR_ENABLE) != 0U){
                NVIC_EnableIRQ(SCI0_ERR_IRQn);
            }
            if((temp & SCI_NVIC_TX_ENABLE) != 0U){
                NVIC_EnableIRQ(SCI0_TX_IRQn);
            }
            if((temp & SCI_NVIC_RX_ENABLE) != 0U){
                NVIC_EnableIRQ(SCI0_RX_IRQn);
            }
        }else{
            if((temp & SCI_NVIC_ERR_ENABLE) != 0U){
                NVIC_EnableIRQ(SCI1_ERR_IRQn);
            }
            if((temp & SCI_NVIC_TX_ENABLE) != 0U){
                NVIC_EnableIRQ(SCI1_TX_IRQn);
            }
            if((temp & SCI_NVIC_RX_ENABLE) != 0U){
                NVIC_EnableIRQ(SCI1_RX_IRQn);
            }
        }
        sci_enable(scix);
        return SUCCESS;
    }else{
        return ERROR;
    }
}

/*!
    \brief      sci enable
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_enable(uint32_t scix)
{
    SCI_EN(scix) = SCI_ENABLE;
}

/*!
    \brief      sci disable
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_disable(uint32_t scix)
{
    SCI_EN(scix) = ~SCI_ENABLE;
}

/*!
    \brief      sci data send
    \param[in]  scix: SCIx(x = 0,1) 
    \param[in]  dat: data to send
    \param[out] none
    \retval     none
*/
void sci_data_send(uint32_t scix,uint8_t dat)
{
    SCI_D(scix) = dat;
}

/*!
    \brief      sci data get
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     sci data 
*/
uint8_t sci_data_get(uint32_t scix)
{
    uint32_t retal;
    retal = SCI_D(scix);
    return (uint8_t)retal;

}

/*!
    \brief      sci tx enable
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_tx_enable(uint32_t scix)
{
    SCI_C2(scix) |= SCI_C2_TX_EN;
}

/*!
    \brief      sci tx disable
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_tx_disable(uint32_t scix)
{
    SCI_C2(scix) &= ~SCI_C2_TX_EN;
}

/*!
    \brief      sci rx enable
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_rx_enable(uint32_t scix)
{
    SCI_C2(scix) |= SCI_C2_RX_EN;
}

/*!
    \brief      sci rx disable
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_rx_disable(uint32_t scix)
{
    SCI_C2(scix) &= ~SCI_C2_RX_EN;
}


/*!
    \brief      sci tx output in single mode
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_tx_out(uint32_t scix)
{
    SCI_C3(scix) |= SCI_C3_TX_DIR;
}

/*!
    \brief      sci tx input in single mode
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_tx_in(uint32_t scix)
{
    SCI_C3(scix) &= ~SCI_C3_TX_DIR;
}

/*!
    \brief      sci t8 set
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_t8_set(uint32_t scix)
{
    SCI_C3(scix) |= SCI_C3_T8;
}

/*!
    \brief      sci t8 reset
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_t8_reset(uint32_t scix)
{
    SCI_C3(scix) &= ~SCI_C3_T8;
}

/*!
    \brief      sci r8 get
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus sci_r8_get(uint32_t scix)
{
    FlagStatus status;
    if((SCI_C3(scix) & SCI_C3_R8) != 0U){
        status = SET;
    }else{
        status = RESET;
    }
    return status;
}

/*!
    \brief      sci rx data inversion state get
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus sci_rx_inv_get(uint32_t scix)
{
    FlagStatus status;
    if((SCI_S2(scix) & SCI_S2_RX_INVERSION) != 0U){
        status = SET;
    }else{
        status = RESET;
    }
    return status;
}

/*!
    \brief      sci tx interrupt flag get
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     tx interrupt flag state
*/
uint8_t sci_tx_int_flag_get(uint32_t scix)
{
    uint32_t retal;
    retal = SCI_S1(scix);
    retal &= (uint32_t)0xc0;
    return (uint8_t)retal;
}

/*!
    \brief      sci rx interrupt flag get
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     rx interrupt flag state
*/
uint8_t sci_rx_int_flag_get(uint32_t scix)
{
    uint32_t tmp;
    uint32_t sci_sta1,sci_sta2;
    sci_sta1 = SCI_S1(scix);
    sci_sta1 &= (uint32_t)0x30;
    sci_sta2 = SCI_S2(scix);
    sci_sta2 &= (uint32_t)0xc0;
    tmp = (sci_sta1 | sci_sta2);
    return (uint8_t)tmp;
}

/*!
    \brief      sci error interrupt flag get
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     error interrupt flag state
*/
uint8_t sci_err_int_flag_get(uint32_t scix)
{
    return (uint8_t)(SCI_S1(scix) & 0x0fU);
}

/*!
    \brief      sci break check interrupt flag clear
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_break_int_flag_clr(uint32_t scix)
{
    SCI_S2(scix) |= SCI_IF_BREAK_CHECK;
}

/*!
    \brief      sci rx edge interrupt flag clear
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void sci_rx_edge_int_flag_clr(uint32_t scix)
{
    SCI_S2(scix) |= SCI_IF_RX_EDGE;
}

/*!
    \brief      sci send a byte
    \param[in]  scix: SCIx(x = 0,1) 
    \param[in]  dat: send data
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrorStatus sci_send_byte(uint32_t scix,uint8_t dat)
{
    uint32_t timeout = 30000U;
    while(timeout != 0x00U){
        timeout --;
        if((SCI_S1(scix) & SCI_S1_TX_EMPTY_FLAG) != 0x00U){
            SCI_D(scix) = dat;
            return SUCCESS;
        }
    }
    return ERROR;
}

/*!
    \brief      sci receive a byte
    \param[in]  scix: SCIx(x = 0,1) 
    \param[in]  *rece_dat:point to receive data
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrorStatus sci_rece_byte(uint32_t scix,uint8_t *rece_dat)
{
    uint32_t timeout = 30000U;
    while(timeout != 0x00U){
        timeout --;
        if((SCI_S1(scix) & SCI_S1_RX_FULL_FLAG) != 0x00U){
            *rece_dat = SCI_D(scix);
            return SUCCESS;
        }
    }
    return ERROR;
}


