/*!
    \file  BF7006BMxx_rtc.h
    \brief definitions for the rtc
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_app_rtc.h initial version

*/

#ifndef	BF7006BMxx_RTC_H
#define	BF7006BMxx_RTC_H

#include "BF7006BMxx.h"
#include "BF7006BMxx_sysctrl.h"

/* register definitions */
#define RTC_SC                  (REG32(RTC_BASE + 0x00U))       /*!< rtc control register */
#define RTC_CNT                 (REG32(RTC_BASE + 0x04U))       /*!< rtc count register */
#define RTC_MOD                 (REG32(RTC_BASE + 0x08U))       /*!< rtc mod count register */
/* end register definitions */

/* bits definition */
#define RTC_SC_EN               BIT(9)                      /*!< rtc enable */
#define RTC_SC_IF               BIT(7)                      /*!< rtc interrupt flag */
#define RTC_SC_CLK_SEL          BITS(5U,6U)                 /*!< rtc clock select */
#define RTC_SC_CLK_SEL_LSB      5U                          /*!< LSB of rtc clock select */
#define RTC_SC_IE               BIT(4)                      /*!< rtc interrupt enable */
/* end bits definition */

/* contacts definition */
/* rtc enable */
#define RTC_ENABLE              BIT(9)
#define RTC_DISABLE             0U

/* rtc clock select */
#define RTC_CLK_SEL_1K          0U                          /*!< select rc_1k as rtc clock */
#define RTC_CLK_SEL_XTAL_DIV32  (1U << RTC_SC_CLK_SEL_LSB)  /*!< select xtal/32 as rtc clock,if xtal initiliaze fail,change rc_1k as rtc clock */
#define RTC_CLK_SEL_32K         (2U << RTC_SC_CLK_SEL_LSB)  /*!< select rc_32k as rtc clock */

/* rtc interrupt enable */
#define RTC_INT_ENABLE          BIT(4)
#define RTC_INT_DISABLE         0U

/* function declarations */
/* rtc initialize */
ErrorStatus rtc_init(uint16_t rtc_sc,uint32_t rtc_mod);
/* rtc mod count set */
void rtc_mod_set(uint32_t rtc_mod);
/* rtc current count get */
uint16_t rtc_cnt_get(void);
/* rtc enable */
void rtc_enable(void);
/* rtc disable */
void rtc_disable(void);
/* rtc interrupt enable */
void rtc_int_enable(void);
/* rtc interrupt disable */
void rtc_int_disable(void);
/* rtc interrupt flag get */
FlagStatus rtc_int_flag_get(void);
/* rtc interrupt flag clear */
void rtc_int_flag_clr(void);
/* rtc clock select */
void rtc_clk_sel(uint8_t clk_sel);

#endif
