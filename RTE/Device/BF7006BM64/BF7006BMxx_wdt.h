/*!
    \file  BF7006BMxx_wdt.h
    \brief definitions for the wdt
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_wdt.h initial version

*/

#ifndef BF7006BMxx_WDT_H
#define	BF7006BMxx_WDT_H

#include "BF7006BMxx.h"

/* register definitions */
#define	WDT_CS					(REG32(WDT_BASE + 0x00U))		/*!< wdt control register */
#define	WDT_CNT					(REG32(WDT_BASE + 0x04U))		/*!< wdt count register */
#define	WDT_TOVAL				(REG32(WDT_BASE + 0x08U))		/*!< wdt over flow register */
#define	WDT_WINVAL				(REG32(WDT_BASE + 0x0cU))		/*!< wdt over flow register in window mode */
/* end registers definitions */

/* WDT_CS bits definitions */
#define	WDT_CS_WINEN			BIT(15)						/*!< wdt window mode enable */
#define	WDT_CS_CLKSEL			BIT(8)						/*!< wdt clock select */
#define	WDT_CS_EN				BIT(7)						/*!< wdt enable */
#define	WDT_CS_UPDATA			BIT(5)						/*!< wdt_cs register updata enable */
#define	WDT_CS_SLEEP			BIT(1)						/*!< wdt enable when in sleeping mode */
#define	WDT_CS_DEEPSLEEP		BIT(0)						/*!< wdt enable when in deep sleep mode */
/* end bits definitions */

/* WDT control define */
/* wdt window mode select */
#define	WDT_WIN_ENABLE			BIT(15)						/*!< wdt window mode enable */
#define	WDT_WIN_DISABLE			0U							/*!< wdt window mode disable */

/* wdt clock select */
#define	WDT_CLOCK_32KHZ			BIT(8)						/*!< wdt clock select 32k HZ */
#define	WDT_CLOCK_1KHZ			0U							/*!< wdt clock select 1k HZ */

/* wdt enable */
#define	WDT_ENABLE				BIT(7)						/*!< wdt enable */
#define	WDT_DISABLE				0U							/*!< wdt disable */

/* wdt updata enable */
#define	WDT_UPDATA_ENABLE		BIT(5)						/*!< wdt updata enable */
#define	WDT_UPDATA_DISABLE		0U							/*!< wdt updata disable */

/* wdt enable in sleep mode */
#define	WDT_SLEEP_ENABLE		BIT(1)						/*!< wdt enable when in sleep mode */
#define	WDT_SLEEP_DISABLE		0U							/*!< wdt disable when in sleep mode */

/* wdt enable in deep sleep mode */
#define	WDT_DEEPSLEEP_ENABLE	BIT(0)						/*!< wdt enable when in deep sleep mode */
#define	WDT_DEEPSLEEP_DISABLE	0U							/*!< wdt disable when in deep sleep mode */

/* function declarations */
/* wdt clear */
void wdt_clear(void);
/* wdt updata */
void wdt_updata(uint16_t wdt_cs);
/* wdt config */
void wdt_config(uint16_t wdt_cs);
/* wdt overflow count set */
void wdt_overflow_count(uint16_t wdt_cnt);
/* wdt overflow count set in window mode */
void wdt_overflow_count_win(uint16_t wdt_cnt);

#endif
