/*!
    \file  BF7006BMxx_lin.h
    \brief definitions for the lin
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_lin.h initial version

*/

#ifndef BF7006BMxx_LIN_H
#define BF7006BMxx_LIN_H

#include "BF7006BMxx.h"

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

//  <o0>SCI select
//    <0=> SCI0
//    <1=> SCI1
//  <i> Select which SCI module as LIN interface

/* lin select, 0U select SCI0 and else select SCI1 */
#define LIN_SEL                         0U

/* lin master define */
#ifdef LIN_SEL
    #define LIN_MASTER
#endif

/* lin driver select according LIN_SEL */
#ifdef LIN_SEL
    #if (LIN_SEL == 0U)
        #define    LIN_SCI0
        #define    LIN_Drv              SCI0
    #else
        #define    LIN_SCI1
        #define    LIN_Drv              SCI1
    #endif
#endif

/* lin frame error define */
#define FRAME_CHECK_ERR_PID             0x01U
#define FRAME_CHECK_ERR_Checksum        0x02U

//  <o0>Frame overtime(ms)
//  <i> Define the timeout for one frame

/* lin frame overtime define */
#define FRAME_OVERTIME_MS               10

/* lin node tx or rx state enum */
typedef enum
{
    Node_Err,
    Node_Tx,
    Node_Rx
}Node_Tx_Rx_enum;

/* lin checksum mode enum */
typedef enum
{
    CHECKSUM_CLASSIC,
    CHECKSUM_ENHANCED
}checksum_mode_enum;

/* lin frame state enum */
typedef enum
{
    LIN_STATE_IDLE,
    LIN_STATE_BREAK,
    LIN_STATE_SYNC,
    LIN_STATE_PID,
    LIN_STATE_DATA,
    LIN_STATE_CHECKSUM
}lin_frame_state_enum;

/* lin master task struct */
typedef struct
{
    lin_frame_state_enum state;
    uint8_t pid;
}lin_master_task_struct;

/* lin slave task struct */
typedef struct
{
    lin_frame_state_enum state;         /*!< lin state                                    */
    uint8_t rece_pid;                   /*!< lin receive pid                              */
    uint8_t rece_dat[8];                /*!< lin receive data                             */
    uint8_t rece_checksum;              /*!< lin receive checksum                         */
    uint8_t response_dat[8];            /*!< lin response data                            */
    uint8_t response_checksum;          /*!< lin response checksum                        */
    uint8_t data_lenth;                 /*!< lin receive or response data lenth           */
    uint8_t data_cnt;                   /*!< lin receive or response data curretn count   */
    Node_Tx_Rx_enum is_tx;              /*!< lin slave task response send or receive data */
}lin_slave_task_struct;

/* slave task point function define */
typedef void (*pt2FuncSlaveTask)(lin_slave_task_struct *slave_task);

/* function declarations */
/* lin initlize rx and tx callback function and enable rx break check */
void lin_init(void);
/* lin baud rate auqo match enable */
void lin_rate_auto_match_enable(uint32_t scix);
/* lin baud rate auqo match disable */
void lin_rate_auto_match_disable(uint32_t scix);
/* lin break check enable */
void lin_break_check_enable(uint32_t scix);
/* lin break check disable */
void lin_break_check_disable(uint32_t scix);
/* lin break transmit */
void lin_break_trans(uint32_t scix);

/* lin pid calculate */
uint8_t lin_pid_calc(uint8_t id);
/* lin checksum calculate */
uint8_t lin_checksum(uint8_t pid,uint8_t data[],uint8_t len);
/* lin overtime detect */
void lin_overtime_detect(void);

#ifdef LIN_SEL
/* SCI0 tx callback function declaration */
extern pt2Func LIN0_Tx_Callback;
/* SCI0 rx callback function declaration */
extern pt2FuncU8 LIN0_Rx_Callback;
/* SCI1 tx callback function declaration */
extern pt2Func LIN1_Tx_Callback;
/* SCI1 rx callback function declaration */
extern pt2FuncU8 LIN1_Rx_Callback;
#endif

/* lin slave task response call back declaration */
extern pt2FuncSlaveTask LinResponseCallBack;
/* lin slave task receive call back declaration */
extern pt2FuncSlaveTask LinReceiveCallBack;
/* lin master head send */
extern void lin_master_head_send(uint8_t lin_id);
#endif
