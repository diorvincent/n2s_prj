/*!
    \file  BF7006BMxx_sci.h
    \brief definitions for the sci
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_sci.h initial version

*/

#ifndef BF7006BMxx_SCI_H
#define	BF7006BMxx_SCI_H

#include "BF7006BMxx.h"

/* registers definitions */
#define SCI_BDH(scix)                   (REG32((scix) + 0x00U))         /*!< sci(0/1) baud rate register: High   */
#define SCI_BDL(scix)                   (REG32((scix) + 0x04U))         /*!< sci(0/1) baud rate register: Low    */
#define SCI_C1(scix)                    (REG32((scix) + 0x08U))         /*!< sci(0/1) control register 1         */
#define SCI_C2(scix)                    (REG32((scix) + 0x0CU))         /*!< sci(0/1) control register 2         */
#define SCI_S1(scix)                    (REG32((scix) + 0x10U))         /*!< sci(0/1) status register 1          */
#define SCI_S2(scix)                    (REG32((scix) + 0x14U))         /*!< sci(0/1) status register 2          */
#define SCI_C3(scix)                    (REG32((scix) + 0x18U))         /*!< sci(0/1) control register 3         */
#define SCI_D(scix)                     (REG32((scix) + 0x1CU))         /*!< sci(0/1) data register 3            */
#define SCI_EN(scix)                    (REG32((scix) + 0x20U))         /*!< sci(0/1) enable register            */
/* end registers definitions */

/* bits definitions */
/* SCI_BDH */
#define SCI_BDH_BREAK_CHECK_EN          BIT(7)                          /*!< sci break check enable or disable          */
#define SCI_BDH_RX_EDGE_INT_EN          BIT(6)                          /*!< sci rx edge interrupt enable or disable    */
#define SCI_BDH_RATE_AUTOMATCH_EN       BIT(5)                          /*!< sci baud rate auto match enable or disable */
#define SCI_BDH_BPR_H                   BIT(0,4)                        /*!< sci baud rate high 4 bits                  */

/* SCI_BDL */
#define SCI_BDL_BPR_L                   BITS(0,7)                       /*!< sci baud rate low 8 bits */

/* SCI_C1 */
#define SCI_C1_CYCLE_MODE               BIT(7)                          /*!< sci cycle mode enable          */
#define SCI_C1_STOP_WIDTH               BIT(6)                          /*!< sci stop bit width as 2bits    */
#define SCI_C1_SINGLE_TXD               BIT(5)                          /*!< sci single wire enable         */
#define SCI_C1_DATA_WIDTH               BIT(4)                          /*!< sci data bit width as 9bits    */
#define SCI_C1_WAKE_SEL                 BIT(3)                          /*!< sci receiver waked up(received data highest bit=1) */
#define SCI_C1_IDLE_SEL                 BIT(2)                          /*!< sci idle timer start after stop bit */
#define SCI_C1_PARITY_EN                BIT(1)                          /*!< sci parity enable              */
#define SCI_C1_PARITY_ODD               BIT(0)                          /*!< sci odd parity                 */

/* SCI_C2 */
#define SCI_C2_TX_EMPTY_INT_EN          BIT(7)                          /*!< sci tx empty intterrupt enable     */
#define SCI_C2_TX_COMP_INT_EN           BIT(6)                          /*!< sci tx complete intterupt enable   */
#define SCI_C2_RX_FULL_INT_EN           BIT(5)                          /*!< sci rx full interrupt enable       */
#define SCI_C2_IDLE_INT_EN              BIT(4)                          /*!< sci idle interrupt enable          */
#define SCI_C2_TX_EN                    BIT(3)                          /*!< sci tx enable                      */
#define SCI_C2_RX_EN                    BIT(2)                          /*!< sci rx enable                      */
#define SCI_C2_RWU                      BIT(1)                          /*!< sci receiver is standby state      */
#define SCI_C2_BREAK_TX                 BIT(0)                          /*!< sci transmit break control         */

/* SCI_S1 */
#define SCI_S1_TX_EMPTY_FLAG            BIT(7)                          /*!< sci tx empty interrupt flag        */
#define SCI_S1_TX_COMP_FLAG             BIT(6)                          /*!< sci tx complete interrupt flag     */
#define SCI_S1_RX_FULL_FLAG             BIT(5)                          /*!< sci rx full interrupt flag         */
#define SCI_S1_IDLE_FLAG                BIT(4)                          /*!< sci idle interrupt flag            */
#define SCI_S1_RX_OVERFLOW_FLAG         BIT(3)                          /*!< sci rx over flow interrupt flag    */
#define SCI_S1_NOSIE_ERR_FLAG           BIT(2)                          /*!< sci nosie error interrupt flag     */
#define SCI_S1_FRAME_ERR_FLAG           BIT(1)                          /*!< sci frame error interrupt flag     */
#define SCI_S1_PARITY_ERR_FLAG          BIT(0)                          /*!< sci parity error interrupt flag    */

/* SCI_S2 */
#define SCI_S2_BREAK_CHECK_FLAG         BIT(7)                          /*!< sci break check interrupt flag     */
#define SCI_S2_RX_EDGE_FLAG             BIT(6)                          /*!< sci rx edge interrupt flag         */
#define SCI_S2_RX_INVERSION             BIT(4)                          /*!< sci rx data inversion flag         */
#define SCI_S2_RWU_IDLESEL              BIT(3)                          /*!< sci set IDLE or not when receiver in standby state after an idle is detected */
#define SCI_S2_BREAK_TX_SIZE            BIT(2)                          /*!< sci trans break size is 13bits     */
#define SCI_S2_BREAK_CHECK_EN           BIT(1)                          /*!< sci rx break check enable          */
#define SCI_S2_RX_ACTIVE_FLAG           BIT(0)                          /*!< sci receiver is active             */

/* SCI_C3 */
#define SCI_C3_R8                       BIT(7)                          /*!< sci rx 8th bit data                */
#define SCI_C3_T8                       BIT(6)                          /*!< sci tx 8th bit data                */
#define SCI_C3_TX_DIR                   BIT(5)                          /*!< sci tx is output in single mode    */
#define SCI_C3_TX_INV                   BIT(4)                          /*!< sci tx data inversion              */
#define SCI_C3_RX_OF_INT_EN             BIT(3)                          /*!< sci rx over flow interrupt enable  */
#define SCI_C3_NOISE_ERR_INT_EN         BIT(2)                          /*!< sci rx noise error interrupt enable */
#define SCI_C3_FRAME_ERR_INT_EN         BIT(1)                          /*!< sci rx frame error interrupt enable */
#define SCI_C3_PARITY_ERR_INT_EN        BIT(0)                          /*!< sci parity error interrupt enable  */

/* SCI_D */
#define SCI_DATA                        BITS(0,7)                       /*!< sci data register */

/* SCI_EN */
#define SCI_ENABLE                      BIT(0)                          /*!< sci enable */

/* end bits definitions */

/* constants definitions */
/* SCI baud rate define */
#define SCI_BAUD_RATE_4800              (uint32_t)4800                  /*!< sci(0/1) baud rate define */
#define SCI_BAUD_RATE_9600              (uint32_t)9600                  /*!< sci(0/1) baud rate define */
#define SCI_BAUD_RATE_19200             (uint32_t)19200                 /*!< sci(0/1) baud rate define */
#define SCI_BAUD_RATE_38400             (uint32_t)38400                 /*!< sci(0/1) baud rate define */
#define SCI_BAUD_RATE_57600             (uint32_t)57600                 /*!< sci(0/1) baud rate define */
#define SCI_BAUD_RATE_115200            (uint32_t)115200                /*!< sci(0/1) baud rate define */

/* SCI work mode define */
#define SCI_CYCLE_MODE                  BIT(7)                          /*!< sci(0/1) cycle mode, tx connect to rx automatic */
#define SCI_SINGLE_MODE                 BIT(5)                          /*!< sci(0/1) single mode, rx pin is invalid    */
#define SCI_NORMAL_MODE                 0U                              /*!< sci(0/1) normal mode                       */

/* SCI idle select define */
#define SCI_IDLE_SEL_STARTBIT           0U                              /*!< sci idle timer start count after start bit */
#define SCI_IDLE_SEL_STOPBIT            BIT(2)                          /*!< sci idle timer start count after stop bit  */

/* SCI receiver wake up select define */
#define SCI_WAKE_SEL_ADDRRECE           BIT(3)                          /*!< sci receiver use received data to wake up  */
#define SCI_WAKE_SEL_IDLE               0U                              /*!< sci receiver use idle to wake up           */

/* SCI stop bit width set */
#define SCI_STOP_BIT_1BIT               0U                              /*!< sci stop bit width is 1bit     */
#define SCI_STOP_BIT_2BITS              BIT(6)                          /*!< sci stop bit width is 2bits    */

/* SCI data bit width set */
#define SCI_DATA_BIT_8BITS              0U                              /*!< sci data bits width is 8bits   */
#define SCI_DATA_BIT_9BITS              BIT(4)                          /*!< sci data bits width is 9bits   */

/* SCI parity enable or disable set */
#define SCI_PARITY_ENABLE               BIT(1)                          /*!< sci parity enable  */
#define SCI_PARITY_DISABLE              0U                              /*!< sci parity disable */

/* SCI parity select: odd or even */
#define SCI_PARITY_ODD                  BIT(0)                          /*!< sci set as odd parity  */
#define SCI_PARITY_EVEN                 0U                              /*!< sci set as even parity */

/* SCI tx data inversion enable */
#define SCI_TX_INV_DISABLE              0U                              /*!< sci tx data inversion disable */
#define SCI_TX_INV_ENABLE               BIT(4)                          /*!< sci tx data inversion enable  */

/* SCI interrupt enable define */
#define SCI_IE_BREAK_CHECK              BIT(15)                         /*!< sci break check interrupt enable   */
#define SCI_IE_RX_EDGE                  BIT(14)                         /*!< sci rx edge interrupt enable       */
#define SCI_IE_TX_EMPTY                 BIT(7)                          /*!< sci tx empty interrupt enable      */
#define SCI_IE_TX_COMP                  BIT(6)                          /*!< sci tx complete interrupt enable   */
#define SCI_IE_RX_FULL                  BIT(5)                          /*!< sci rx full interrupt enable       */
#define SCI_IE_IDLE                     BIT(4)                          /*!< sci idle interrupt enable          */
#define SCI_IE_RX_OF                    BIT(3)                          /*!< sci rx over flow interrupt enable  */
#define SCI_IE_NOISE_ERR                BIT(2)                          /*!< sci noise error interrupt enable   */
#define SCI_IE_FRAME_ERR                BIT(1)                          /*!< sci frame error interrupt enable   */
#define SCI_IE_PARITY_ERR               BIT(0)                          /*!< sci parity error interrupt enable  */

/* SCI rwu_idlesel set */
#define SCI_RWU_IDLESEL_ENABLE          BIT(3)          /*!< sci set IDLE when receiver in standby state after an idle is detected */
#define SCI_RWU_IDLESEL_DISABLE         0U              /*!< sci not set IDLE when receiver in standby state after an idle is detected */

/* SCI break tx size select */
#define SCI_BREAK_TX_SIZE_13BITS        BIT(2)                          /*!< sci transmit break width is 13bits */
#define SCI_BREAK_TX_SIZE_10BITS        0U                              /*!< sci transmit break width is 10bits */

/* SCI break check enable set */
#define SCI_BREAK_CHECK_ENABLE          BIT(1)                          /*!< sci break check enable     */
#define SCI_BREAK_CHECK_DISABLE         0U                              /*!< sci break check disable    */

/* SCI baud rate auto match set */
#define SCI_RATE_AUTOMATCH_ENABLE       BIT(5)                          /*!< sci rate auto match enable when receive sync segment */
#define SCI_RATE_AUTOMATCH_DISABLE      0U                              /*!< sci rate auto match disable when receive sync segment */

/* SCI tx enable or disable set */
#define SCI_TX_ENABLE                   BIT(3)                          /*!< sci tx enable  */
#define SCI_TX_DISABLE                  0U                              /*!< sci tx disable */

/* SCI rx enable or disable set */
#define SCI_RX_ENABLE                   BIT(2)                          /*!< sci rx enable  */
#define SCI_RX_DISABLE                  0U                              /*!< sci tx disable */

/* SCI tx interrupt flag define */    
#define SCI_IF_TX_EMPTY                 BIT(7)                          /*!< sci tx empty interrupt flag    */
#define SCI_IF_TX_COMP                  BIT(6)                          /*!< sci tx complete interrupt flag */

/* SCI rx interrupt flag define */    
#define SCI_IF_BREAK_CHECK              BIT(7)                          /*!< sci break check interrupt flag */
#define SCI_IF_RX_EDGE                  BIT(6)                          /*!< sci rx edge interrupt flag     */
#define SCI_IF_RX_FULL                  BIT(5)                          /*!< sci rx full interrupt flag     */
#define SCI_IF_IDLE                     BIT(4)                          /*!< sci idle interrupt flag        */

/* SCI error interrupt flag define */    
#define SCI_IF_RX_OF                    BIT(3)                          /*!< sci rx over flow interrupt flag */
#define SCI_IF_NOISE_ERR                BIT(2)                          /*!< sci noise error interrupt flag  */
#define SCI_IF_FRAME_ERR                BIT(1)                          /*!< sci frame error interrupt flag  */
#define SCI_IF_PARITY_ERR               BIT(0)                          /*!< sci parity error interrupt flag */

/* SCI nvic enable define */
#define SCI_NVIC_ERR_ENABLE             BIT(0)                          /*!< sci nvic err interrupt enable  */
#define SCI_NVIC_ERR_DISABLE            0U                              /*!< sci nvic err interrupt disable */
#define SCI_NVIC_TX_ENABLE              BIT(1)                          /*!< sci nvic tx interrupt enable   */
#define SCI_NVIC_TX_DISABLE             0U                              /*!< sci nvic tx interrupt disable  */
#define SCI_NVIC_RX_ENABLE              BIT(2)                          /*!< sci nvic rx interrupt enable   */
#define SCI_NVIC_RX_DISABLE             0U                              /*!< sci nvic rx interrupt disable  */

/* SCI PID calculate define */
/*#define ParityBIT(A,B)                  (((A)>>(B))&0x01U)     */            /*!< A is the variable while B is the bit number */  

/* SCI initiliaze parameters struct */
typedef struct
{
    uint32_t    baud_rate;          /*!< sci baud rate set                                          */
    uint8_t     work_mode;          /*!< sci work mode select                                       */
    uint8_t     stop_bit_width;     /*!< sci stop bit width set                                     */
    uint8_t     data_bit_width;     /*!< sci data bit width set                                     */
    uint8_t     parity_en;          /*!< sci parity enable or disable                               */
    uint8_t     parity_sel;         /*!< sci parity select: odd or even                             */
    uint8_t     break_tx_size;      /*!< sci break transmit size select: 13 bits or 11 bits         */
    uint8_t     break_check_en;     /*!< sci break check enable or disable                          */
    uint8_t     rate_automatch_en;  /*!< sci baud rate auto match enable when detect lin sync section */
    uint8_t     tx_en;              /*!< sci tx enable or disable                                   */
    uint8_t     rx_en;              /*!< sci rx enable or disable                                   */
    uint8_t     idle_sel;           /*!< sci idle timer start count select                          */
    uint8_t     wake_sel;           /*!< sci receiver wake up mode select                           */
    uint8_t     tx_inversion_en;    /*!< sci tx data inversion enable                               */
    uint8_t     rwu_idlesel;        /*!< sci set IDLE or not when receiver in standby state after an idle is detected */
    uint16_t    int_enable;         /*!< sci interrupt enable                                       */
    uint8_t     nvic_enable;        /*!< sci nvic interrupt enable                                  */
}sci_parameter_struct;


/* function declarations */
/* sci initialize */
ErrorStatus sci_init(uint32_t scix,sci_parameter_struct sci_parameter_init);
/* sci enable */
void sci_enable(uint32_t scix);
/* sci disable */
void sci_disable(uint32_t scix);
/* sci data send */
void sci_data_send(uint32_t scix,uint8_t dat);
/* sci data get */
uint8_t sci_data_get(uint32_t scix);

/* sci tx enable */
void sci_tx_enable(uint32_t scix);
/* sci tx disable */
void sci_tx_disable(uint32_t scix);
/* sci rx enable */
void sci_rx_enable(uint32_t scix);
/* sci rx disable */
void sci_rx_disable(uint32_t scix);

/* sci tx output in single mode */
void sci_tx_out(uint32_t scix);
/* sci tx input in single mode */
void sci_tx_in(uint32_t scix);
/* sci t8 set */
void sci_t8_set(uint32_t scix);
/* sci t8 reset */
void sci_t8_reset(uint32_t scix);
/* sci r8 get */
FlagStatus sci_r8_get(uint32_t scix);
/* sci rx data inversion state get */
FlagStatus sci_rx_inv_get(uint32_t scix);

/* sci tx interrupt flag get */
uint8_t sci_tx_int_flag_get(uint32_t scix);
/* sci rx interrupt flag get */
uint8_t sci_rx_int_flag_get(uint32_t scix);
/* sci error interrupt flag get */
uint8_t sci_err_int_flag_get(uint32_t scix);
/* sci break check interrupt flag clear */
void sci_break_int_flag_clr(uint32_t scix);
/* sci rx edge interrupt flag clear */
void sci_rx_edge_int_flag_clr(uint32_t scix);

void UART_Send_Xinxi(uint32_t scix,unsigned char *s,unsigned char sendnum);

/* sci send byte */
ErrorStatus sci_send_byte(uint32_t scix,uint8_t dat);
/* sci receive byte */
ErrorStatus sci_rece_byte(uint32_t scix,uint8_t *rece_dat);


#endif
