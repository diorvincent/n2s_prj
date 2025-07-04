/*!
    \file  BF7006BMxx_can.h
    \brief definitions for the can
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_can.h initial version

*/
#ifndef BF7006BMxx_CAN_H
#define BF7006BMxx_CAN_H

#include "BF7006BMxx.h"

/* registers definitions */
#define CAN_MOD                 (REG32(CAN_BASE + 0x00U))       /*!< CAN mode control register */
#define CAN_CMR                 (REG32(CAN_BASE + 0x04U))       /*!< CAN command control register */
#define CAN_SR                  (REG32(CAN_BASE + 0x08U))       /*!< CAN status register */
#define CAN_IF                  (REG32(CAN_BASE + 0x0CU))       /*!< CAN interupt control register */
#define CAN_IE                  (REG32(CAN_BASE + 0x10U))       /*!< CAN interupt enable register */
#define CAN_BTR0                (REG32(CAN_BASE + 0x18U))       /*!< CAN baud rate control register0 */
#define CAN_BTR1                (REG32(CAN_BASE + 0x1CU))       /*!< CAN baud rate control register1 */
#define CAN_SLPAK               (REG32(CAN_BASE + 0x20U))       /*!< CAN sleep mode acknowledge register */
#define CAN_WUP                 (REG32(CAN_BASE + 0x24U))       /*!< CAN wake up control register */
#define CAN_ALC                 (REG32(CAN_BASE + 0x2CU))       /*!< CAN arbitration lost capture register */
#define CAN_ECC                 (REG32(CAN_BASE + 0x30U))       /*!< CAN error code capture register */
#define CAN_EMLR                (REG32(CAN_BASE + 0x34U))       /*!< CAN error alarm count register */
#define CAN_RXERR               (REG32(CAN_BASE + 0x38U))       /*!< CAN rx error count register */
#define CAN_TXERR               (REG32(CAN_BASE + 0x3CU))       /*!< CAN tx error count register */
#define CAN_FRCTL               (REG32(CAN_BASE + 0x40U))       /*!< CAN frame control register */
#define CAN_IDAR0               (REG32(CAN_BASE + 0x40U))       /*!< CAN identifier acceptance register0 */
#define CAN_IDAR1               (REG32(CAN_BASE + 0x44U))       /*!< CAN identifier acceptance register1 */
#define CAN_IDAR2               (REG32(CAN_BASE + 0x48U))       /*!< CAN identifier acceptance register2 */
#define CAN_IDAR3               (REG32(CAN_BASE + 0x4CU))       /*!< CAN identifier acceptance register3 */
#define CAN_IDMR0               (REG32(CAN_BASE + 0x50U))       /*!< CAN identifier mask register0 */
#define CAN_IDMR1               (REG32(CAN_BASE + 0x54U))       /*!< CAN identifier mask register1 */
#define CAN_IDMR2               (REG32(CAN_BASE + 0x58U))       /*!< CAN identifier mask register2 */
#define CAN_IDMR3               (REG32(CAN_BASE + 0x5CU))       /*!< CAN identifier mask register3 */
#define CAN_RMC                 (REG32(CAN_BASE + 0x74U))       /*!< CAN rx fifo data count register */
#define CAN_ENABLE              (REG32(CAN_BASE + 0x78U))       /*!< CAN enable register */
#define CAN_CLRISR              (REG32(CAN_BASE + 0x80U))       /*!< CAN interrupt flag clear register */
#define CAN_CLRECC              (REG32(CAN_BASE + 0x84U))       /*!< CAN error code capture status clr register */
#define CAN_FILTER_EN           (REG32(CAN_BASE + 0x88U))       /*!< CAN wakeup from sleepdeep filter enable register */
    
/* can frame id and data regeisters definitions */
#define CAN_ID0                 (REG32(CAN_BASE + 0x44U))       /*!< CAN identifier register0 */
#define CAN_ID1                 (REG32(CAN_BASE + 0x48U))       /*!< CAN identifier register1 */
#define CAN_ID2                 (REG32(CAN_BASE + 0x4CU))       /*!< CAN identifier register2 */
#define CAN_ID3                 (REG32(CAN_BASE + 0x50U))       /*!< CAN identifier register3 */
#define CAN_DATA0               (REG32(CAN_BASE + 0x54U))       /*!< CAN data register0 */
#define CAN_DATA1               (REG32(CAN_BASE + 0x58U))       /*!< CAN data register1 */
#define CAN_DATA2               (REG32(CAN_BASE + 0x5CU))       /*!< CAN data register2 */
#define CAN_DATA3               (REG32(CAN_BASE + 0x60U))       /*!< CAN data register3 */
#define CAN_DATA4               (REG32(CAN_BASE + 0x64U))       /*!< CAN data register4 */
#define CAN_DATA5               (REG32(CAN_BASE + 0x68U))       /*!< CAN data register5 */
#define CAN_DATA6               (REG32(CAN_BASE + 0x6CU))       /*!< CAN data register6 */
#define CAN_DATA7               (REG32(CAN_BASE + 0x70U))       /*!< CAN data register7 */
/* end can frame id and data regeisters definitions */

/* end registers definitions */

/* bits definitions */
/* CAN_MOD */
#define CAN_MOD_AFM             BIT(3)      /*!< filter mode select */
#define CAN_MOD_STM             BIT(2)      /*!< self test mode */
#define CAN_MOD_LOM             BIT(1)      /*!< listen only mode */
#define CAN_MOD_RM              BIT(0)      /*!< reset mode */

/* CAN_CMR */
#define CAN_CMR_SPM             BIT(5)      /*!< sleep mode request */
#define CAN_CMR_SRR             BIT(4)      /*!< self receive request */
#define CAN_CMR_CDO             BIT(3)      /*!< clear data overflow status */
#define CAN_CMR_RRB             BIT(2)      /*!< release rx buffer */
#define CAN_CMR_AT              BIT(1)      /*!< abort transmit request */
#define CAN_CMR_TR              BIT(0)      /*!< transmit request */

/* CAN_SR */
#define CAN_SR_BS               BIT(7)      /*!< bus off status */
#define CAN_SR_ES               BIT(6)      /*!< error status */
#define CAN_SR_TS               BIT(5)      /*!< tx status */
#define CAN_SR_RS               BIT(4)      /*!< rx status */
#define CAN_SR_TCS              BIT(3)      /*!< tx complet status */
#define CAN_SR_TBS              BIT(2)      /*!< tx buffer status */
#define CAN_SR_DOS              BIT(1)      /*!< data overflow status */
#define CAN_SR_RBS              BIT(0)      /*!< rx buffer status */

/* CAN_IF */
#define CAN_IF_BEI              BIT(7)      /*!< bus error interrut flag */
#define CAN_IF_ALI              BIT(6)      /*!< arbitration lost interrupt flag */
#define CAN_IF_EPI              BIT(5)      /*!< error passive interrupt flag */
#define CAN_IF_WUPI             BIT(4)      /*!< wake up interrupt flag */
#define CAN_IF_DOI              BIT(3)      /*!< data overflow interrupt flag */
#define CAN_IF_EI               BIT(2)      /*!< error interrupt or bus state change interrupt flag */
#define CAN_IF_TI               BIT(1)      /*!< Tx interrupt flag */
#define CAN_IF_RI               BIT(0)      /*!< rx interrupt flag */

/* CAN_IE */
#define CAN_IE_BEIE             BIT(7)      /*!< bus error interrupt enable */
#define CAN_IE_ALIE             BIT(6)      /*!< arbitration lost interrupt enable */
#define CAN_IE_EPIE             BIT(5)      /*!< error passive interrupt enable */
#define CAN_IE_WUIE             BIT(4)      /*!< wake up interrupt enable */
#define CAN_IE_DOIE             BIT(3)      /*!< data overflow interrupt enable */
#define CAN_IE_EIE              BIT(2)      /*!< error interrupt enable */
#define CAN_IE_TIE              BIT(1)      /*!< tx interrupt enable */
#define CAN_IE_RIE              BIT(0)      /*!< rx interrupt enable */

/* CAN_BTR0 */
#define CAN_BTR0_SJW            BITS(6,7)   /*!< synchronlzation jump width */
#define CAN_BTR0_SJW_LSB        6U          /*!< lowest bit of CAN_BTR0_SJW */
#define CAN_BTR0_BRP            BITS(0,5)   /*!< baud rate prescaler */
#define CAN_BTR0_BRP_LSB        0U          /*!< lowest bit of CAN_BTR0_BRP */


/* CAN_BTR1 */
#define CAN_BTR1_SAM            BIT(7)      /*!< sampling timers */
#define CAN_BTR1_SAM_LSB        7U          /*!< lowst bit of CAN_BTR1_SAM */
#define CAN_BTR1_TSEG2          BITS(4,6)   /*!< time segment 2 */
#define CAN_BTR1_TSEG2_LSB      4U          /*!< lowest bit of CAN_BTR1_TSEG2 */
#define CAN_BTR1_TSEG1          BITS(0,3)   /*!< time segment 1 */
#define CAN_BTR1_TSEG1_LSB      0U          /*!< lowest bit of CAN_BTR1_TSEG1 */

/* CAN_WUP */
#define CAN_WUP_MODE            BIT(1)      /*!< wake up mode select */
#define CAN_WUP_ENABLE          BIT(0)      /*!< wake up enable */

/* CAN_ALC */
#define CAN_ALC_CODE            BITS(0,4)   /*!< arbitration lost code */

/* CAN_ECC */
#define CAN_ECC_MODE            BITS(6,7)   /*!< error mode */
#define CAN_ECC_DIR             BIT(5)      /*!< tx or rx error */
#define CAN_ECC_CODE            BITS(0,4)   /*!< error campture code */

/* CAN_FRCTL */
#define CAN_FRCTL_FF            BIT(7)      /*!< standard or extended flame select */
#define CAN_FRCTL_RTR           BIT(6)      /*!< remote or data flame select */
#define CAN_FRCTL_DLC           BITS(0,3)   /*!< data lenth */
#define CAN_FRCTL_DLC_LSB       0U          /*!< lowest bit of  CAN_FRCTL_DLC*/

/* CAN_CLRISR */
#define CAN_CLRISR_BEI          BIT(7)      /*!< clear bus error interrupt flag */
#define CAN_CLRISR_ALI          BIT(6)      /*!< clear arbitration lost interrupt flag */
#define CAN_CLRISR_EPI          BIT(5)      /*!< clear error passive interrupt flag */
#define CAN_CLRISR_WUPI         BIT(4)      /*!< clear wake up interrupt flag */
#define CAN_CLRISR_DOI          BIT(3)      /*!< clear data overflow interrupt flag */
#define CAN_CLRISR_EI           BIT(2)      /*!< clear error interrupt flag */
#define CAN_CLRISR_TI           BIT(1)      /*!< clear tx interrupt flag */
/* end bits definitions */

/* contact definitions */
/* can tx interrupt enable and disable define */
#define CAN_TIE_ENABLE          BIT(1)      /*!< tx interrupt enable */
#define CAN_TIE_DISABLE         0U          /*!< tx interrupt disable */

/* can rx interrupt enable and disable define */
#define CAN_RIE_ENABLE          BIT(0)      /*!< rx interrupt enable */
#define CAN_RIE_DISABLE         0U          /*!< rx interrupt disable */

/* can wake up interrupt enable and disable define */
#define CAN_WUIE_ENABLE         BIT(4)      /*!< wake up interrupt enable */
#define CAN_WUIE_DISABLE        0U          /*!< wake up interrupt disable */

/* can error interrupt enable and disable define */
#define CAN_BEIE_ENABLE         BIT(7)      /*!< bus error interrupt enable */
#define CAN_BEIE_DISABLE        0U          /*!< bus error interrupt disable */
#define CAN_ALIE_ENABLE         BIT(6)      /*!< arbitration lost interrupt enable */
#define CAN_ALIE_DISABLE        0U          /*!< arbitration lost interrupt disable */
#define CAN_EPIE_ENABLE         BIT(5)      /*!< error passive interrupt enable */
#define CAN_EPIE_DISABLE        0U          /*!< error passive interrupt disable */
#define CAN_DOIE_ENABLE         BIT(3)      /*!< data overflow interrupt enable */
#define CAN_DOIE_DISABLE        0U          /*!< data overflow interrupt disable */
#define CAN_EIE_ENABLE          BIT(2)      /*!< error alarm interrupt enable */
#define CAN_EIE_DISABLE         0U          /*!< error alarm interrupt disable */
#define CAN_ERR_ALL_ENABLE      (BITS(5U,7U) | BITS(2U,3U))/*!< all error interrupt enable */

/* can nvic interrupt enable and disable define */
#define CAN_WU_NVIC_ENABLE      BIT(3)      /*!< wake up nvic interrupt enable */
#define CAN_WU_NVIC_DISABLE     0U          /*!< wake up nvic interrupt disable */

#define CAN_ERR_NVIC_ENABLE     BIT(2)      /*!< error nvic interrupt enable */
#define CAN_ERR_NVIC_DISABLE    0U          /*!< error nvic interrupt disable */

#define CAN_RX_NVIC_ENABLE      BIT(1)      /*!< rx nvic interrupt enable */
#define CAN_RX_NVIC_DISABLE     0U          /*!< rx nvic interrupt disable */

#define CAN_TX_NVIC_ENABLE      BIT(0)      /*!< tx nvic interrupt enable */
#define CAN_TX_NVIC_DISABLE     0U          /*!< tx nvic interrupt disable */

/* can bus state define */
#define CAN_BUS_ON              0U          /*!< can bus on */
#define CAN_BUS_OFF             BIT(7)      /*!< can bus off */


/* can baud rate prescaler set */
#define CAN_BTR0_BRP_SET(regval)    ((uint8_t)(CAN_BTR0_BRP & ((uint32_t)(regval) << CAN_BTR0_BRP_LSB)))

/* can synchronlzation jump width set */
#define CAN_BTR0_SJW_SET(regval)    ((uint8_t)(CAN_BTR0_SJW & ((uint32_t)(regval) << CAN_BTR0_SJW_LSB)))

/* can time segment 1 set */
#define CAN_BTR1_TSEG1_SET(regval)  ((uint8_t)(CAN_BTR1_TSEG1 & ((uint32_t)(regval) << CAN_BTR1_TSEG1_LSB)))

/* can time segment 2 set */
#define CAN_BTR1_TSEG2_SET(regval)  ((uint8_t)(CAN_BTR1_TSEG2 & ((uint32_t)(regval) << CAN_BTR1_TSEG2_LSB)))

/* can sample timers set */
#define CAN_BTR1_SAM_SET(regval)    ((uint8_t)(CAN_BTR1_SAM & ((uint32_t)(regval) << CAN_BTR1_SAM_LSB)))

/* can data lenth set */
#define CAN_FRCTL_DLC_SET(regval)   ((uint8_t)(CAN_FRCTL_DLC & ((uint32_t)(regval) << CAN_FRCTL_DLC_LSB)))

/* can data register */
#define CAN_DATA(x)                 (REG32(CAN_BASE + 0x54U + ((x) << 2)))

/* can work mode enum */
typedef enum
{
    CAN_NOMARL = 0,
    CAN_MODE_LISTEN_ONLY,
    CAN_MODE_SELF_TEST,
    CAN_MODE_SELF_RECEIVE,
}can_work_mode_enum;

/* can baud enum */
typedef enum
{
    CAN_BAUD_50K = 0,
    CAN_BAUD_100K,
    CAN_BAUD_125K,
    CAN_BAUD_200K,
    CAN_BAUD_250K,
    CAN_BAUD_400K,
    CAN_BAUD_500K,
    CAN_BAUD_800K,
    CAN_BAUD_1M
}can_baud_enum;

/* can module clock enum */
typedef enum
{
    CAN_CLK_32M,
    CAN_CLK_16M,
    CAN_CLK_8M
}can_clk_enum;


/* can filter mode enum */
typedef enum
{
    CAN_DOUBLE_FILTER,      /*!< double filter */
    CAN_SINGLE_FILTER,      /*!< single filter */
}CAN_FILTER_MODE;

/* can filter frame enum */
typedef enum
{
    CAN_STANDARD_FRAME,     /*!< standard frame */
    CAN_EXTENDED_FRAME,     /*!< extened frame */
}CAN_FRAME_FORMAT;

/* can filter RTR enum */
typedef enum
{
    CAN_DATA_FRAME,         /*!< data frame */
    CAN_REMOTE_FRAME,       /*!< remote frame */
}CAN_FRAME_TYPE;

/* can arbitration lost capture code enum */
typedef enum
{
    CAN_ALC_ID_BIT0,
    CAN_ALC_ID_BIT1,
    CAN_ALC_ID_BIT2,
    CAN_ALC_ID_BIT3,
    CAN_ALC_ID_BIT4,
    CAN_ALC_ID_BIT5,
    CAN_ALC_ID_BIT6,
    CAN_ALC_ID_BIT7,
    CAN_ALC_ID_BIT8,
    CAN_ALC_ID_BIT9,
    CAN_ALC_ID_BIT10,
    CAN_ALC_SRTR,
    CAN_ALC_IDE,
    CAN_ALC_ID_BIT11,
    CAN_ALC_ID_BIT12,
    CAN_ALC_ID_BIT13,
    CAN_ALC_ID_BIT14,
    CAN_ALC_ID_BIT15,
    CAN_ALC_ID_BIT16,
    CAN_ALC_ID_BIT17,
    CAN_ALC_ID_BIT18,
    CAN_ALC_ID_BIT19,
    CAN_ALC_ID_BIT20,
    CAN_ALC_ID_BIT21,
    CAN_ALC_ID_BIT22,
    CAN_ALC_ID_BIT23,
    CAN_ALC_ID_BIT24,
    CAN_ALC_ID_BIT25,
    CAN_ALC_ID_BIT26,
    CAN_ALC_ID_BIT27,
    CAN_ALC_ID_BIT28,
    CAN_ALC_RTR,
}CAN_ALC_CODE_ENUM;

/* CAN initiliaze parameters struct */
typedef struct
{
    can_work_mode_enum  working_mode;           /*!< can working mode */
    uint8_t             resync_jump_width;      /*!< synchronlzation jump width */
    can_clk_enum        can_clk;                /*!< can module clock */
    can_baud_enum       can_baud;               /*!< can baud set */
    uint8_t             sampling_times;         /*!< sampling timers */
    uint8_t             error_alarm_count;      /*!< error alarm count */
    uint8_t             int_enable;             /*!< interrupt enable */
    uint8_t             nvic_int_enable;        /*!< nvic interrupt enable */
}can_parameter_struct;

/* CAN filter parameter struct */
typedef struct
{
    CAN_FILTER_MODE     filter_mode;            /*!< select filter mode: single mode or double mode */
    CAN_FRAME_FORMAT    filter_frame;           /*!< select filter standard frame or extended frame */
    CAN_FRAME_TYPE      filter_RTR;             /*!< select filter frame type */
    FunctionalState     filter_mask_RTR;        /*!< RTR bit mask */
    /* single filter cofing */
    uint32_t            filter_single_id;       /*!< single filter id */
    uint8_t             filter_data0;           /*!< data0 filter  */
    uint8_t             filter_data1;           /*!< data1 filter  */
    uint32_t            filter_mask_single_id;  /*!< single filter mask id */
    uint8_t             filter_mask_data0;      /*!< data0 filter mask  */
    uint8_t             filter_mask_data1;      /*!< data1 filter mask  */
    /* double filter config */
    uint32_t            filter_double_id0;      /*!< double filter id0 */
    uint32_t            filter_double_id1;      /*!< double filter id1 */
    uint8_t             filter_data0_std;       /*!< double filter data0 in standard frame */
    uint32_t            filter_mask_double_id0; /*!< double filter id0 mask */
    uint32_t            filter_mask_double_id1; /*!< double filter id1 mask */
    uint8_t             filter_mask_data0_std;  /*!< double filter data0 mask in standard frame */

}can_filter_parameter_struct;

/* CAN message struct */
typedef struct
{
    uint32_t            sfid;                 /*!< standard format frame identifier */
    uint32_t            efid;                 /*!< extended format frame identifier */
    CAN_FRAME_FORMAT    ff;                   /*!< format of frame, standard or extended format */
    CAN_FRAME_TYPE      ft;                   /*!< type of frame, data or remote */
    uint8_t             dlen;                 /*!< data length */
    uint8_t             data[8];              /*!< transmit data */
}can_frame_struct;

/* function declarations */
/* can initialize */
ErrorStatus can_init(can_parameter_struct can_parameter_init,can_filter_parameter_struct can_filter_parameter);
/* can receive message */
ErrorStatus can_receive_message(can_frame_struct *receive_data);
/* can transmit message */
ErrorStatus can_transmit_message(can_frame_struct *transmit_data);
/* can transmit request */
void can_transmit_request(void);
/* wait for can transmit complete */
ErrorStatus can_wait_trans(void);
/* read frame error code */
uint8_t can_read_frame_error_code(void);
/* read arbitration lost code */
uint8_t can_read_arbitration_lost_code(void);
/* can transmit abort */
void can_transmit_abort(void);
/* can sleep config */
void can_sleep_config(uint8_t wakeup_mode,uint8_t filter_en,FunctionalState state);
/* can sleep request */
ErrorStatus can_sleep_request(void);
/* can wait transmit frame */
void can_wait_transmit_frame(can_frame_struct *transmit_data);
/* get can fifo frame number */
uint8_t can_get_fifo_num(void);
/* get can tx error cnt */
uint8_t can_get_txerrcnt(void);
/* get can rx error cnt */
uint8_t can_get_rxerrcnt(void);
/* reset can module */
void can_module_rst(void);
/* enable can module */
void can_module_enable(void);
/* disable can module */
void can_module_disable(void);
/* can clock select */
ErrorStatus can_clock_sel(uint8_t can_clock);
/* can tx buff empty judge */
bool is_can_txbuf_empty(void);

/* interrupt function declarations */
/* can interrupt enable */
void can_int_enable(uint8_t intstate);
/* can interrupt disable */
void can_int_disable(uint8_t intstate);
/* get can interrupt flag */
uint8_t can_interrupt_flag_get(void);
/* can interrupt flag clear */
void can_int_flag_clr(uint8_t int_flag);
/* get can status */
uint8_t can_status_get(void);

#endif
