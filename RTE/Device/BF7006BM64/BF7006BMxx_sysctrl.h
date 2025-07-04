/*!
    \file  BF7006BMxx_sysctrl.h
    \brief definitions for the system control
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_sysctrl.h initial version

*/

#ifndef BF7006BMxx_SYS_H
#define BF7006BMxx_SYS_H

#include "BF7006BMxx.h"

/* registers definitions */
#define SYS_PTSEL                   (REG32(SYSCTRL_BASE + 0x00U))       /*!< sci2 port function remap register          */
#define SYS_XTAL_CTRL               (REG32(SYSCTRL_BASE + 0x04U))       /*!< xtal control register                      */
#define SYS_PLL_SOURCE_SEL          (REG32(SYSCTRL_BASE + 0x08U))       /*!< pll source clock select register           */
#define SYS_CLK_SEL                 (REG32(SYSCTRL_BASE + 0x0CU))       /*!< system clock select register               */
#define SYS_VECTOR_OFFSET           (REG32(SYSCTRL_BASE + 0x10U))       /*!< interrupt vector address offset register   */
#define SYS_CLK_PD                  (REG32(SYSCTRL_BASE + 0x14U))       /*!< analog clock power down register           */
#define SYS_CAN_DOMAIN              (REG32(SYSCTRL_BASE + 0x18U))       /*!< can domain count register                  */
#define SYS_CLK_OUT                 (REG32(SYSCTRL_BASE + 0x1CU))       /*!< analog clock output register               */
#define SYS_IO_LOCK                 (REG32(SYSCTRL_BASE + 0x20U))       /*!< lock io direction register                 */
#define SYS_LVDT_CRL                (REG32(SYSCTRL_BASE + 0x24U))       /*!< bor and lvdt control register              */
#define SYS_EXRST                   (REG32(SYSCTRL_BASE + 0x28U))       /*!< external reset function enable register    */
#define SYS_EXFLT                   (REG32(SYSCTRL_BASE + 0x2CU))       /*!< external filiter enable register           */
#define SYS_BIST                    (REG32(SYSCTRL_BASE + 0x30U))       /*!< sram bist test state register              */
#define SYS_PERH_HALT               (REG32(SYSCTRL_BASE + 0x34U))       /*!< PWM/WDT enable or not in debug mode when halt*/
#define SYS_PLL_T                   (REG32(SYSCTRL_BASE + 0x38U))       /*!< PLL standby timer set register             */
#define SYS_DUMMY                   (REG32(SYSCTRL_BASE + 0x3CU))       /*!< dummy register                             */
#define SYS_CAN_CLKSEL              (REG32(SYSCTRL_BASE + 0x40U))       /*!< CAN clock select register                  */
#define SYS_CAN_RST                 (REG32(SYSCTRL_BASE + 0x44U))       /*!< CAN module reset register                  */
#define SYS_CAN_SPWKFLAG            (REG32(SYSCTRL_BASE + 0x48U))       /*!< CAN wake up from deelsleep state register  */
#define SYS_RSTSTAT                 (REG32(SYSCTRL_BASE + 0x100U))      /*!< reset status register                      */
#define SYS_INTEN                   (REG32(SYSCTRL_BASE + 0x104U))      /*!< system interrupt enable register           */
#define SYS_INTFLG                  (REG32(SYSCTRL_BASE + 0x108U))      /*!< system interrupt flag register             */
#define SYS_XTAL_CHK                (REG32(SYSCTRL_BASE + 0x10CU))      /*!< xtal clcok check control register          */
#define SYS_XTAL_CHKCNT             (REG32(SYSCTRL_BASE + 0x110U))      /*!< xtal check count set register              */
#define SYS_XTAL_INIT               (REG32(SYSCTRL_BASE + 0x114U))      /*!< xtal initialize control register           */
#define SYS_LVDT_IE                 (REG32(SYSCTRL_BASE + 0x118U))      /*!< lvdt interrupt enable register             */
#define SYS_LVDT_IF                 (REG32(SYSCTRL_BASE + 0x11CU))      /*!< lvdt interrupt flag register               */

/* bits registers definitions */
/* SYS_XTAL_CTRL */
#define SYS_XTAL_CTRL_PD            BIT(7)                              /*!< xtal pown down flag                */
#define SYS_XTAL_CTRL_CNT           BITS(4,6)                           /*!< xtal valid count                   */
#define SYS_XTAL_CTRL_INIT          BIT(3)                              /*!< xtal initialize complete flag      */
#define SYS_XTAL_CTRL_SLEEPPD       BIT(1)                              /*!< xtal powndown in sleepdeep mode    */
#define SYS_XTAL_CTRL_EN            BIT(0)                              /*!< xtal enable                        */

/* SYS_CLK */
#define SYS_CLK_SYSSEL              BIT(2)                              /*!< system clock select pll or xtal    */
#define SYS_CLK_PLLDIV              BITS(0,1)                           /*!< pll clock divide                   */
#define SYS_CLK_PLLDIV_Pos          0                                   /*!< pll clock divide postion           */

/* SYS_CLK_PD */
#define SYS_CLK_PD_LVDT             BIT(2)                              /*!< lvdt powerdown     */
#define SYS_CLK_PD_BOR              BIT(1)                              /*!< bor powerdown      */
#define SYS_CLK_PD_RC128K           BIT(0)                              /*!< rc128k powerdown   */

/* SYS_RSTSTAT */
#define SYS_RSTSTAT_XTALCHK         BIT(8)
#define SYS_RSTSTAT_XTALINIT        BIT(7)
#define SYS_RSTSTAT_ADDR_FLOW       BIT(6)
#define SYS_RSTSTAT_EXRST           BIT(5)
#define SYS_RSTSTAT_LOCKUP          BIT(4)
#define SYS_RSTSTAT_SOFT            BIT(3)
#define SYS_RSTSTAT_WDT             BIT(2)
#define SYS_RSTSTAT_POR             BIT(0)

/* SYS_INTEN */
#define SYS_INTEN_LVDT              BIT(9)                  /*!< lower power detect interrupt enable                */
#define SYS_INTEN_ETER              BIT(8)                  /*!< eeprom ECC error two bits or more interrupt enable */
#define SYS_INTEN_EOER              BIT(7)                  /*!< eeprom ECC error one bit interrupt enable          */
#define SYS_INTEN_FTER              BIT(6)                  /*!< flash ECC error two bits or more interrupt enable  */
#define SYS_INTEN_FOER              BIT(5)                  /*!< flash ECC error one bit interrupt enable           */
#define SYS_INTEN_EPOT              BIT(4)                  /*!< eeprom protect range illegal access interrupt enable */
#define SYS_INTEN_FPOT              BIT(3)                  /*!< flash protect range illegal access interrupt enable  */
#define SYS_INTEN_ADJ               BIT(2)                  /*!< config bits error interrupt enable                 */
#define SYS_INTEN_XTALCHK           BIT(1)                  /*!< xtal check eroor interrupt enable                  */
#define SYS_INTEN_XTALINIT          BIT(0)                  /*!< xtal initialize timeout interrupt enable           */

/* SYS_INTFLG */
#define SYS_INTFLG_LVDT             BIT(9)                  /*!< lower power detect interrupt flag                  */
#define SYS_INTFLG_ETER             BIT(8)                  /*!< eeprom ECC error two bits or more interrupt flag   */
#define SYS_INTFLG_EOER             BIT(7)                  /*!< eeprom ECC error one bit interrupt flag            */
#define SYS_INTFLG_FTER             BIT(6)                  /*!< flash ECC error two bits or more interrupt flag    */
#define SYS_INTFLG_FOER             BIT(5)                  /*!< flash ECC error one bit interrupt flag             */
#define SYS_INTFLG_EPOT             BIT(4)                  /*!< eeprom protect range illegal access interrupt flag */
#define SYS_INTFLG_FPOT             BIT(3)                  /*!< flash protect range illegal access interrupt flag  */
#define SYS_INTFLG_ADJ              BIT(2)                  /*!< config bits error interrupt flag                   */
#define SYS_INTFLG_XTALCHK          BIT(1)                  /*!< xtal check eroor interrupt flag                    */
#define SYS_INTFLG_XTALINIT         BIT(0)                  /*!< xtal initialize timeout interrupt flag             */

/* SYS_XTAL_CHK */
#define SYS_XTAL_CHK_RSTEN          BIT(1)                  /*!< xtal check fail reset enable */
#define SYS_XTAL_CHK_EN             BIT(0)                  /*!< xtal check enable            */

/* SYS_XTAL_INIT */
#define SYS_XTAL_INIT_RSTEN         BIT(1)                  /*!< xtal initialize fail reset enable */
#define SYS_XTAL_INIT_EN            BIT(0)                  /*!< xtal initialize timeout enable    */

/* constants definitions */
/* sci1 port select define */
#define SCI1_PF0_PF1                0                       /*!< select PF0 and PF1 as sci1 */
#define SCI1_PE2_PE3                1                       /*!< select PE2 and PE3 as sci1 */
#define SCI1_PE6_PE7                2                       /*!< select PE6 and PE7 as sci1 */

/* PLL source clock select define */
#define SYS_PLL_SEL_RC1M            0xacb3U                 /*!< pll source clock select rc_1M      */
#define SYS_PLL_SEL_XTAL_16M        0xccd2U                 /*!< pll source clock select xtal/16    */
#define SYS_PLL_SEL_XTAL_12M        0xbd5aU                 /*!< pll source clock select xtal/12    */
#define SYS_PLL_SEL_XTAL_8M         0x8d9cU                 /*!< pll source clock select xtal/8     */


/* system clock define */
#define SYS_CLK_32M                 0x9abdU                 /*!< system clock select pll 32M hz */
#define SYS_CLK_16M                 0x3ca2U                 /*!< system clock select pll 16M hz */
#define SYS_CLK_8M                  0xe78cU                 /*!< system clock select pll 8M hz  */
#define SYS_CLK_XTAL                0x7c6bU                 /*!< system clock select xtal       */

/* system interrupt define */
#define SYS_INT_LVDT_ENABLE         SYS_INTEN_LVDT          /*!< lower power detect interrupt enable                    */
#define SYS_INT_LVDT_DISABLE        0                       /*!< lower power detect interrupt disable                   */
#define SYS_INT_ETER_ENABLE         SYS_INTEN_ETER          /*!< eeprom ECC error two bits or more interrupt enable     */
#define SYS_INT_ETER_DISABLE        0                       /*!< eeprom ECC error two bits or more interrupt disable    */
#define SYS_INT_EOER_ENABLE         SYS_INTEN_EOER          /*!< eeprom ECC error one bit interrupt enable              */
#define SYS_INT_EOER_DISABLE        0                       /*!< eeprom ECC error one bit interrupt disable             */
#define SYS_INT_FTER_ENABLE         SYS_INTEN_FTER          /*!< flash ECC error two bits or more interrupt enable      */
#define SYS_INT_FTER_DISABLE        0                       /*!< flash ECC error two bits or more interrupt disable     */
#define SYS_INT_FOER_ENABLE         SYS_INTEN_FOER          /*!< flash ECC error one bit interrupt enable               */
#define SYS_INT_FOER_DISABLE        0                       /*!< flash ECC error one bit interrupt disable              */
#define SYS_INT_EPOT_ENABLE         SYS_INTEN_EPOT          /*!< eeprom protect range illegal access interrupt enable   */
#define SYS_INT_EPOT_DISABLE        0                       /*!< eeprom protect range illegal access interrupt disable  */
#define SYS_INT_FPOT_ENABLE         SYS_INTEN_FPOT          /*!< flash protect range illegal access interrupt enable    */
#define SYS_INT_FPOT_DISABLE        0                       /*!< flash protect range illegal access interrupt disable   */
#define SYS_INT_ADJ_ENABLE          SYS_INTEN_ADJ           /*!< config bits error interrupt enable                     */
#define SYS_INT_ADJ_DISABLE         0                       /*!< config bits error interrupt disable                    */
#define SYS_INT_OSC_ENABLE          SYS_INTEN_OSC           /*!< XTAL OSC error interrupt enable                        */
#define SYS_INT_OSC_DISABLE         0                       /*!< XTAL OSC error interrupt disable                       */

/* system interrupt flag define */
#define SYS_IF_LVDT_MASK            BIT(9)                  /*!< lower power detect interrupt flag mask                 */
#define SYS_IF_ETER_MASK            BIT(8)                  /*!< eeprom ECC error two bits or more interrupt flag mask  */
#define SYS_IF_EOER_MASK            BIT(7)                  /*!< eeprom ECC error one bit interrupt flag mask           */
#define SYS_IF_FTER_MASK            BIT(6)                  /*!< flash ECC error two bits or more interrupt flag mask   */
#define SYS_IF_FOER_MASK            BIT(5)                  /*!< flash ECC error one bit interrupt flag mask            */
#define SYS_IF_EPOT_MASK            BIT(4)                  /*!< eeprom protect range illegal access interrupt flag mask*/
#define SYS_IF_FPOT_MASK            BIT(3)                  /*!< flash protect range illegal access interrupt flag mask */
#define SYS_IF_ADJ_MASK             BIT(2)                  /*!< config bits error interrupt flag mask                  */
#define SYS_IF_OSC_MASK             BIT(1)                  /*!< XTAL OSC error interrupt flag mask                     */

/* can clock select define */
#define CAN_XTAL_CLOCK              0U                      /*!< select xtal as can clock */
#define CAN_PLL_CLOCK               1U                      /*!< select pll as can clock  */

/* can wakeup flag from sleepdeep mode */
#define SYS_CAN_SPWKFLAG_CLR        1

/* lvde voltage gear define */
#define LVDT_GEAR_4P5V              2U                      /*!< lvdt voltage gear 4.5V */
#define LVDT_GEAR_4P0V              1U                      /*!< lvdt voltage gear 4.0V */
#define LVDT_GEAR_3P5V              0U                      /*!< lvdt voltage gear 3.5V */

/* lvdt interrupt flag define */
#define LVDT_IF_BOOST               2U                      /*!< lvdt boost interrupt flag */
#define LVDT_IF_BUCK                1U                      /*!< lvdt buck interrupt flag */

/* clock output source define */
#define CLK_OUT_XTAL_DIV_8          3U                      /*!< clock output xtal divide 8         */
#define CLK_OUT_PLL_DIV_16          2U                      /*!< clock output PLL divide 16         */
#define CLK_OUT_RC_32K              1U                      /*!< clock output internal rc 32k hz    */
#define CLK_OUT_RC_250K             0U                      /*!< clock output internal rc 250k hz   */

/* clock2 output source define */
#define CLK2_OUT_XTAL_DIV_16        0x20U                   /*!< clock2 output xtal divide 16       */
#define CLK2_OUT_RC_250K            0x10U                   /*!< clock2 output internal rc 250k hz  */

typedef enum{
    XTAL_Init_Status_Never_Initialize = 0U,
    XTAL_Init_Status_Init_Failed,
    XTAL_Init_Status_Init_Success
}XTAL_Init_Status;

typedef enum{
    External_Clock_Source_XTAL_None = 0U,
    External_Clock_Source_XTAL_8MHz,
    External_Clock_Source_XTAL_12MHz,
    External_Clock_Source_XTAL_16MHz
}External_Clock_Source;

typedef enum{
    PLL_Source_Disable = 0U,
    PLL_Source_InternalRC1MHz,
    PLL_Source_XTAL
}PLL_Source;

typedef enum{
    PLL_Output_Clock_Disable = 0U,
    PLL_Output_Clock_8M,
    PLL_Output_Clock_16M,
    PLL_Output_Clock_32M,
}PLL_Output_Freq;

typedef enum{
    System_Clock_Source_XTAL = 0U,
    System_Clock_Source_PLL
}System_Clock_Source;

typedef struct{
    External_Clock_Source   xtal_clock;         /* External clock source input */
    PLL_Source              pll_source;         /* PLL input source clock */
    PLL_Output_Freq         pll_freq;           /* PLL output frequency */
    System_Clock_Source     sys_clk_source;     /* System clock source */
}SysClkStruct;

/* variables declaration*/
extern XTAL_Init_Status is_xtal_init_success;    // xtal init flag


/* function declarations */
/* sci1 port select */
void sci1_port_sel(uint8_t port_sel);

/* system clock select */
void system_clk_sel(uint32_t pll_source_sel,uint32_t clk_sel,uint8_t xtal_freq);
/* xtal initiliaze */
ErrorStatus xtal_init(void);
/* enable or disable xtal powerdown in sleepdeep mode */
void xtal_sleepdeep_pd(FunctionalState pd_en);
/* enable or disable rc128k powerdown */
void rc128k_pd(FunctionalState pd_en);
/* clock out */
void clock_out(uint8_t clk_source);
/* clock2 out */
void clock2_out(uint8_t clk2_source);

/* system interrupt vector address offset */
void system_intvector_offset(uint32_t offset_addr);

/* system interrupt config */
void system_int_cfg(uint16_t int_state,FunctionalState en_state);
/* system interrupt flag get */
uint16_t system_intflg_get(void);
/* system interrupt flag clear */
void system_intflg_clr(uint16_t int_flg);

/* lvdt initialize */
void lvdt_init(FunctionalState lvdt_en,uint8_t lvdt_vol_gear,FunctionalState int_en);
/* lvdt enable */
void lvdt_enable(void);
/* lvdt disable */
void lvdt_disable(void);
/* lvdt interrput flag get */
uint8_t lvdt_int_flag_get(void);
/* lvdt interrput flag clear */
void lvdt_int_flag_clr(uint8_t int_flag);

/* reset pin filter enable or disable */
void reset_filter(FunctionalState filter_en);
/* reset flag get */
uint16_t rst_flag_get(void);
/* reset flag clear */
void rst_flag_clr(uint16_t rst_flag);

/* delay */
void delay_us(uint32_t time);
/* system clock switch function */
ErrorStatus system_clock_switch(SysClkStruct* ClkConfig);

/* variable declarations */
extern volatile uint8_t xtal_timeout;
#endif
