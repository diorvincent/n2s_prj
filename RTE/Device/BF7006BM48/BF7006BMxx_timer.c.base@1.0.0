/*!
    \file  BF7006BMxx_timer.c
    \brief timer driver
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_timer.c initial version
*/

#include "BF7006BMxx_timer.h"

/*!
    \brief      timer0/1 initialize
    \param[in]  timerx: TIMERx(0,1)
	\param[in]	timer_cfg: timer0/1 config
	\param[in]	timer_mod: timer0/1 mod count
    \param[out] none
    \retval     none
*/
void timer_init(uint32_t timerx,uint8_t timer_cfg,uint16_t timer_mod)
{
	TIMER_CFG(timerx) = timer_cfg;
	TIMER_MOD(timerx) = timer_mod;
	if(timerx == (uint32_t)TIMER0){
		if((timer_cfg & TIMER_CFG_IE) != 0U){
			NVIC_EnableIRQ(TIMER0_IRQn);
		}else{
			NVIC_DisableIRQ(TIMER0_IRQn);
		}
	}else{
		if((timer_cfg & TIMER_CFG_IE) != 0U){
			NVIC_EnableIRQ(TIMER1_IRQn);
		}else{
			NVIC_DisableIRQ(TIMER1_IRQn);
		}
	}
}


/*!
    \brief      timer0/1 enable
    \param[in]  timerx: TIMERx(0,1)
    \param[out] none
    \retval     none
*/
void timer_enable(uint32_t timerx)
{
	TIMER_CFG(timerx) |= TIMER_CFG_EN;
}

/*!
    \brief      timer0/1 disable
    \param[in]  timerx: TIMERx(0,1)
    \param[out] none
    \retval     none
*/
void timer_disable(uint32_t timerx)
{
	TIMER_CFG(timerx) &= ~TIMER_CFG_EN;
}

/*!
    \brief      timer0/1 mod count set
    \param[in]  timerx: TIMERx(0,1)
	\param[in]	count: timer0/1 mod count 
    \param[out] none
    \retval     none
*/
void timer_mod_set(uint32_t timerx,uint16_t count)
{
	TIMER_MOD(timerx) = count;
}

/*!
    \brief      timer0/1 current count get
    \param[in]  timerx: TIMERx(0,1)
    \param[out] none
    \retval     timer0/1 current count
*/
uint16_t timer_cnt_get(uint32_t timerx)
{
	return TIMER_CNT(timerx);
}

/*!
    \brief      timer0/1 interrupt flag clear
    \param[in]  timerx: TIMERx(0,1)
    \param[out] none
    \retval     none
*/
void timer_intflag_clr(uint32_t timerx)
{
	TIMER_CFG(timerx) |= TIMER_CFG_IF;
}

/*!
    \brief      timer0/1 interrupt flag get
    \param[in]  timerx: TIMERx(0,1)
    \param[out] none
    \retval     interrupt flag,SET or RESET
*/
FlagStatus timer_intflag_get(uint32_t timerx)
{
	uint32_t intflag = TIMER_CFG(timerx);
	if((intflag & TIMER_CFG_IF) != 0x00U ){
		return SET;
	}else{
		return RESET;
	}
} 
