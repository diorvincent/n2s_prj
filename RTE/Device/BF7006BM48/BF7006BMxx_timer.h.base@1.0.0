/*!
    \file  BF7006BMxx_timer.h
    \brief definitions for the timer
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_timer.h initial version
*/

#ifndef BF7006BMxx_TIMER_H
#define	BF7006BMxx_TIMER_H

#include "BF7006BMxx.h"

/* registers definitions */
#define TIMER_CFG(timerx) 			(REG32((timerx) + 0x00U))		/*!< timer0/1 control register */	
#define TIMER_MOD(timerx) 			(REG32((timerx) + 0x04U))		/*!< timer0/1 mod count register */	
#define	TIMER_CNT(timerx)			(REG32((timerx) + 0x08U))		/*!< timer0/1 current count register */
/* end registers definitions */

/* TIMER_CFG bits definitions */
#define	TIMER_CFG_IF				BIT(6)						/*!< timer0/1 interrupt flag */
#define	TIMER_CFG_IE				BIT(5)						/*!< timer0/1 interrupt enable */
#define	TIMER_CFG_CLK_DIV			BITS(3,4)					/*!< timer0/1 clock divide select */
#define	TIMER_CFG_CLK_DIV_LSB		3							/*!< LSB of clock divide select */
#define	TIMER_CFG_CLK_SEL			BIT(2)						/*!< timer0/1 clock select */
#define	TIMER_CFG_RLD				BIT(1)						/*!< timer0/1 reload select */
#define	TIMER_CFG_EN				BIT(0)						/*!< timer0/1 enable */
/* end TIMER_CFG bits definitions */

/* contacts definitions */
/* timer0/1 interrupt enable */
#define	TIMER_INT_ENABLE			BIT(5)						/*!< timer0/1 interrupt enable */
#define	TIMER_INT_DISABLE			0U							/*!< timer0/1 interrupt disable */

/* timer0/1 clock select define */
#define	TIMER_CLK_32K				0x04U						/*!< timer0/1 clock select as 32K HZ */
#define	TIMER_CLK_SYS_DIV1			0x00U						/*!< timer0/1 clock select as system clock divide 1*/
#define	TIMER_CLK_SYS_DIV2			0x08U						/*!< timer0/1 clock select as system clock divide 2*/
#define	TIMER_CLK_SYS_DIV4			0x10U						/*!< timer0/1 clock select as system clock divide 4*/
#define	TIMER_CLK_SYS_DIV8			0x18U						/*!< timer0/1 clock select as system clock divide 8*/

/* timer0/1 auto reload select */
#define	TIMER_AUTO_RLD_ENABLE		BIT(1)						/*!< timer0/1 auto reload enable */
#define	TIMER_AUTO_RLD_DISABLE		0U							/*!< timer0/1 auto reload disable */

/* timer0/1 enable */
#define	TIMER_ENABLE				BIT(0)						/*!< timer0/1 enable */
#define	TIMER_DISABLE				0U							/*!< timer0/1 disable */

/* function declarations */
/* timer0/1 initialize */
void timer_init(uint32_t timerx,uint8_t timer_cfg,uint16_t timer_mod);
/* timer0/1 enable */
void timer_enable(uint32_t timerx);
/* timer0/1 disable */
void timer_disable(uint32_t timerx);
/* timer0/1 mod count set */
void timer_mod_set(uint32_t timerx,uint16_t count);
/* timer0/1 current count get */
uint16_t timer_cnt_get(uint32_t timerx);

/* timer0/1 interrupt flag clear */
void timer_intflag_clr(uint32_t timerx);
/* timer0/1 interrupt flag get */
FlagStatus timer_intflag_get(uint32_t timerx);

#endif
