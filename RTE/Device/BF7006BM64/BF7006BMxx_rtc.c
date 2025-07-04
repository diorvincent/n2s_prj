/*!
    \file  BF7006BMxx_rtc.c
    \brief rtc driver
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_rtc.c initial version

*/

#include "BF7006BMxx_rtc.h"

/*!
    \brief      rtc initialize 
    \param[in]  rtc_sc: rtc control
    \param[in]  rtc_mod: rtc mod count
    \param[out] none
    \retval    none
*/
ErrorStatus rtc_init(uint16_t rtc_sc,uint32_t rtc_mod)
{
    ErrorStatus rval;
    if((rtc_sc & RTC_SC_CLK_SEL) == RTC_CLK_SEL_XTAL_DIV32)
    {
        if((SYS_XTAL_CTRL & SYS_XTAL_CTRL_INIT) == 0U){
            rval = xtal_init();
            if(rval == ERROR){
                return ERROR;
            }
        }
    }
    RTC_SC = rtc_sc;
    RTC_MOD = rtc_mod;
    if((rtc_sc & RTC_SC_IE) != 0U){
        NVIC_EnableIRQ(RTC_IRQn);
    }else{
        NVIC_DisableIRQ(RTC_IRQn);
    }
    return SUCCESS;
}

/*!
    \brief      rtc mod count set 
    \param[in]  rtc_mod: rtc mod cout
    \param[out] none
    \retval    none
*/
void rtc_mod_set(uint32_t rtc_mod)
{
    RTC_MOD = rtc_mod;
}

/*!
    \brief      rtc current count get 
    \param[in]  none
    \param[out] none
    \retval    rtc current count
*/
uint16_t rtc_cnt_get(void)
{
    return RTC_CNT;
}

/*!
    \brief      rtc enable
    \param[in]  none
    \param[out] none
    \retval    none
*/
void rtc_enable(void)
{
    RTC_SC |= RTC_ENABLE;
}

/*!
    \brief      rtc disable
    \param[in]  none
    \param[out] none
    \retval    none
*/
void rtc_disable(void)
{
    RTC_SC &= ~RTC_ENABLE;
}

/*!
    \brief      rtc interrupt enable
    \param[in]  none
    \param[out] none
    \retval    none
*/
void rtc_int_enable(void)
{
    RTC_SC |= RTC_INT_ENABLE;
    NVIC_EnableIRQ(RTC_IRQn);
}

/*!
    \brief      rtc interrupt disable
    \param[in]  none
    \param[out] none
    \retval    none
*/
void rtc_int_disable(void)
{
    RTC_SC &= ~RTC_INT_ENABLE;
    NVIC_DisableIRQ(RTC_IRQn);
}

/*!
    \brief      rtc interrupt flag get
    \param[in]  none
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus rtc_int_flag_get(void)
{
    FlagStatus state;
    if((RTC_SC & RTC_SC_IF) != 0U){
        state = SET;
    }else{
        state = RESET;
    }
    return state;
}

/*!
    \brief      rtc interrupt flag clear
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_int_flag_clr(void)
{
    RTC_SC |= RTC_SC_IF;
}


/*!
    \brief      rtc clock select
    \param[in]  clk_sel: RTC_CLK_SEL_1K,RTC_CLK_SEL_XTAL,RTC_CLK_SEL_32K
    \param[out] none
    \retval    none
*/
void rtc_clk_sel(uint8_t clk_sel)
{
    RTC_SC &= ~RTC_SC_CLK_SEL;
    RTC_SC |= clk_sel;
}
