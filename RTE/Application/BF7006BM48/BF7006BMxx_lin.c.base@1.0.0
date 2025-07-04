/*!
    \file  BF7006BMxx_lin.c
    \brief lin driver
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_lin.c initial version

*/
#include "BF7006BMxx_lin.h"
#include "BF7006BMxx_sci.h"
#include "BF7006BMxx_sysctrl.h"


#ifdef LIN_SEL
pt2Func LIN0_Tx_Callback = NULL;
pt2FuncU8 LIN0_Rx_Callback = NULL;

pt2Func LIN1_Tx_Callback = NULL;
pt2FuncU8 LIN1_Rx_Callback = NULL;

static uint8_t lin_overtime_state = 0U;
static uint8_t lin_overtime_cnt = 0U;
#endif

static lin_master_task_struct lin_master_task = {.state = LIN_STATE_IDLE};
static lin_slave_task_struct lin_slave_task = {.state = LIN_STATE_BREAK};
pt2FuncSlaveTask LinResponseCallBack = NULL;
pt2FuncSlaveTask LinReceiveCallBack = NULL;

void lin_master_task_state(void);
void lin_slave_task_state(uint8_t rx_int_state);

/*!
    \brief      lin initlize rx and tx callback function and enable rx break check 
    \param[in]  none 
    \param[out] none
    \retval     none
*/
void lin_init(void)
{    
    #ifdef LIN_SEL
    if(LIN_Drv == SCI0){
        LIN0_Tx_Callback = lin_master_task_state;
        LIN0_Rx_Callback = lin_slave_task_state;
    }else{
        LIN1_Tx_Callback = lin_master_task_state;
        LIN1_Rx_Callback = lin_slave_task_state;
    }
    #endif
}

/*!
    \brief      lin baud rate auqo match enable
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void lin_rate_auto_match_enable(uint32_t scix)
{
    SCI_BDH(scix) |= SCI_BDH_RATE_AUTOMATCH_EN;
}

/*!
    \brief      lin baud rate auqo match disable
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void lin_rate_auto_match_disable(uint32_t scix)
{
    SCI_BDH(scix) &= ~SCI_BDH_RATE_AUTOMATCH_EN;
}

/*!
    \brief      lin break check enable
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void lin_break_check_enable(uint32_t scix)
{
    SCI_S2(scix) |= SCI_S2_BREAK_CHECK_EN;
}

/*!
    \brief      lin break check disable
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void lin_break_check_disable(uint32_t scix)
{
    SCI_S2(scix) &= ~SCI_S2_BREAK_CHECK_EN;
}

/*!
    \brief      lin break transmit  
    \param[in]  scix: SCIx(x = 0,1) 
    \param[out] none
    \retval     none
*/
void lin_break_trans(uint32_t scix)
{
    SCI_C2(scix) |= SCI_C2_BREAK_TX;
    SCI_C2(scix) &= ~SCI_C2_BREAK_TX;
}
/*!
    \brief      lin pid calculate
    \param[in]  id: sci id
    \param[out] none
    \retval     parity: sci pid
*/

uint8_t lin_pid_calc(uint8_t id)
{
    uint8_t BitNum, Pid, BitData[8] = {0x00};
    // calculate PID from given ID
    for(BitNum=0U; BitNum<6U; BitNum++){
        BitData[BitNum] =  (id >> BitNum ) & 0x01U;
    }
    BitData[6] = BitData[0] ^ BitData[1] ^ BitData[2] ^ BitData[4];
    BitData[7] = 1U ^ BitData[1] ^ BitData[3] ^ BitData[4] ^ BitData[5];
    Pid = (BitData[7] << 7U) | (BitData[6] << 6U) | id;
    return Pid;
}

/*!
    \brief      lin checksum calculate
    \param[in]  pid:pid
    \param[in]  data: send data
    \param[in]  len:send data lenth
    \param[out] none
    \retval     sum: data checksum
*/
uint8_t lin_checksum(uint8_t pid,uint8_t data[],uint8_t len)
{
    uint16_t sum;
    uint8_t i;
    if((pid == 0x3cU) || (pid == 0x3dU)){
        sum = 0x00U;
    }else{
        sum = pid;
    }
    for(i = 0U; i < len; i++){
        sum += data[i];
        if((sum & 0xFF00U) != 0x00U){
            sum = (sum & 0x00FFU) + 1U;
        }
    }
    sum ^= 0x00FFU;
    return (uint8_t)sum;
}

/*!
    \brief      lin overtime detect
    \param[in]  none
    \param[out] none
    \retval     none
    \info       user should call this function every 1ms
*/
/* User could disable this warning by defining the following macro definition */
#ifndef NO_WARNING_LIN_OVERTIME_DETECT_CALL
    #warning User should call function lin_overtime_detect() every 1ms
#endif

void lin_overtime_detect(void)
{
    #ifdef LIN_SEL
    if(lin_overtime_state == 1U){
        lin_overtime_cnt++;
        if(lin_overtime_cnt >= FRAME_OVERTIME_MS){
            lin_overtime_state = 0U;
            lin_overtime_cnt = 0U;
            lin_break_check_enable(LIN_Drv);
            lin_slave_task.state = LIN_STATE_BREAK;
        }
    }
    #endif
}

/*!
    \brief      lin master schedule 
    \param[in]  id: master send id
    \param[out] none
    \retval     none
*/
void lin_master_head_send(uint8_t lin_id)
{
    #ifdef LIN_SEL
    lin_master_task.pid = lin_pid_calc(lin_id);
    lin_master_task.state = LIN_STATE_BREAK;
    
    lin_slave_task.state = LIN_STATE_BREAK;
    lin_break_check_enable(LIN_Drv);
    
    if(LIN_Drv == SCI0){
        NVIC_EnableIRQ(SCI0_TX_IRQn);
    }else{
        NVIC_EnableIRQ(SCI1_TX_IRQn);
    }
    #endif
}

/*!
    \brief      lin master task state 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lin_master_task_state(void)
{
    #ifdef LIN_SEL
    switch(lin_master_task.state){
        /* lin master send break field */
        case LIN_STATE_BREAK:
            lin_break_trans(LIN_Drv);
            lin_master_task.state = LIN_STATE_SYNC;
            break;
        /* lin master send sync field */
        case LIN_STATE_SYNC:
            sci_data_send(LIN_Drv,0x55);
            lin_master_task.state = LIN_STATE_PID;
            break;
        /* lin master send pid field */
        case LIN_STATE_PID:
            sci_data_send(LIN_Drv,lin_master_task.pid);
            lin_master_task.state = LIN_STATE_IDLE;
            if(LIN_Drv == SCI0){
                NVIC_DisableIRQ(SCI0_TX_IRQn);
            }else{
                NVIC_DisableIRQ(SCI1_TX_IRQn);
            }
            break;
        /* lin master state error, set to IDLE */
        default:
            lin_master_task.state = LIN_STATE_IDLE;
            if(LIN_Drv == SCI0){
                NVIC_DisableIRQ(SCI0_TX_IRQn);
            }else{
                NVIC_DisableIRQ(SCI1_TX_IRQn);
            }
            break;
    }
    #endif
}

/*!
    \brief      lin slave task state 
    \param[in]  rx_int_state :sci rx interrupt state
    \param[out] none
    \retval     none
*/
void lin_slave_task_state(uint8_t rx_int_state)
{
    #ifdef LIN_SEL
    if((rx_int_state & SCI_IF_BREAK_CHECK) != 0x00U){    /* break field check */
        (void)sci_break_int_flag_clr(LIN_Drv);
        if(lin_slave_task.state == LIN_STATE_BREAK){
            lin_overtime_state = 1U;
            lin_overtime_cnt = 0U;
            lin_break_check_disable(LIN_Drv);
            lin_slave_task.state = LIN_STATE_SYNC;
        }else{
            lin_overtime_state = 0U;
            lin_overtime_cnt = 0U;
            lin_break_check_enable(LIN_Drv);
            lin_slave_task.state = LIN_STATE_BREAK;
        }
    }else if((rx_int_state & SCI_IF_RX_FULL) != 0x00U){    /* receive buffer full */
        switch(lin_slave_task.state){
            /* slave task sync field receive */
            case LIN_STATE_SYNC:
                if(sci_data_get(LIN_Drv) == 0x55U){
                    lin_slave_task.state = LIN_STATE_PID;
                }else{
                    lin_overtime_state = 0U;
                    lin_overtime_cnt = 0U;
                    lin_break_check_enable(LIN_Drv);
                    lin_slave_task.state = LIN_STATE_BREAK;
                }
                break;
            /* lin slave task pid receive */
            case LIN_STATE_PID:
                lin_slave_task.rece_pid = sci_data_get(LIN_Drv);
                lin_slave_task.data_cnt = 0x00U;
                /* Pid priority check */
                if(lin_pid_calc(lin_slave_task.rece_pid & 0x3FU) != lin_slave_task.rece_pid){
                    lin_slave_task.rece_pid = 0xFFU;
                }
                /* slave task response function call back according to receive pid */
                if(LinResponseCallBack != NULL){
                    (*LinResponseCallBack)(&lin_slave_task);
                    /* slave task is send,then send the first data */
                    if(lin_slave_task.is_tx == Node_Tx){
                        sci_data_send(LIN_Drv,lin_slave_task.response_dat[lin_slave_task.data_cnt]);
                        lin_slave_task.state = LIN_STATE_DATA;
                    }
                    /* slave task is receive */
                    else if(lin_slave_task.is_tx == Node_Rx){
                        lin_slave_task.state = LIN_STATE_DATA;
                    }
                    /* receive pid is error, slave task state back to break field check */
                    else{
                        lin_overtime_state = 0U;
                        lin_overtime_cnt = 0U;
                        lin_break_check_enable(LIN_Drv);
                        lin_slave_task.state = LIN_STATE_BREAK;
                    }
                }else{
                    lin_overtime_state = 0U;
                    lin_overtime_cnt = 0U;
                    lin_break_check_enable(LIN_Drv);
                    lin_slave_task.state = LIN_STATE_BREAK;
                }
                break;
            /* slave task data field */
            case LIN_STATE_DATA:
                /* slave task receive data */
                lin_slave_task.rece_dat[lin_slave_task.data_cnt] = sci_data_get(LIN_Drv);
                lin_slave_task.data_cnt ++;
                /* data receive and send if the pid is response data */
                if(lin_slave_task.data_cnt < lin_slave_task.data_lenth){
                    /* slave task response data */
                    if(lin_slave_task.is_tx == Node_Tx){
                        sci_data_send(LIN_Drv,lin_slave_task.response_dat[lin_slave_task.data_cnt]);
                    }
                }else{
                    /* slave task receive the last data,then send the response checksum */
                    if(lin_slave_task.is_tx == Node_Tx){
                        sci_data_send(LIN_Drv,lin_slave_task.response_checksum);
                    }
                    lin_slave_task.state = LIN_STATE_CHECKSUM;
                }
                break;
            case LIN_STATE_CHECKSUM:
                /* slave task receive checksum */
                lin_slave_task.rece_checksum = sci_data_get(LIN_Drv);
                /* Checksum validation */
                if(lin_checksum(lin_slave_task.rece_pid & 0x3FU, \
                                lin_slave_task.rece_dat, \
                                lin_slave_task.data_lenth) != lin_slave_task.rece_checksum){
                    /* error handling */
                }
                
                /* slave tsak receive frame over */
                if(LinReceiveCallBack != NULL){
                    (*LinReceiveCallBack)(&lin_slave_task);
                }
                lin_overtime_state = 0U;
                lin_overtime_cnt = 0U;
                lin_break_check_enable(LIN_Drv);
                lin_slave_task.state = LIN_STATE_BREAK;
                break;
            default:
                (void)sci_data_get(LIN_Drv);
                break;
        }
    }else{
        /* do nothing */
    }
    #endif
}

