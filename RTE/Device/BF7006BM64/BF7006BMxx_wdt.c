/*!
    \file  BF7006BMxx_wdt.c
    \brief wdt driver
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_wdt.c initial version

*/

#include "BF7006BMxx_wdt.h"
#include "BF7006BMxx_sysctrl.h"

/*!
    \brief      clear wdt count
    \param[in]  none
    \param[out] none
    \retval     none
*/
void wdt_clear(void)
{
	WDT_CNT = 0x55AAU;
}

/*!
    \brief      wdt updata
    \param[in]  wdt_cs: wdt control data
    \param[out] none
    \retval     none
*/
void wdt_updata(uint16_t wdt_cs)
{
	if((WDT_CS & WDT_CS_UPDATA) != 0U)
	{
		WDT_CNT = 0x6BC3U;
		WDT_CS = wdt_cs;
	}else{
		WDT_CS = wdt_cs;
	}
	SYS_PERH_HALT = 0x01U;
}

/*!
    \brief      wdt config
	\param[in]  wdt_cs: wdt control data
    \param[out] none
    \retval     none
*/
void wdt_config(uint16_t wdt_cs)
{
	WDT_CS = wdt_cs;
	SYS_PERH_HALT = 1U;
}

/*!
    \brief      wdt overflow count set
	\param[in]  wdt_cnt: wdt over flow cout
    \param[out] none
    \retval     none
*/
void wdt_overflow_count(uint16_t wdt_cnt)
{
	WDT_TOVAL = wdt_cnt;
}

/*!
    \brief      wdt overflow count set in window mode
	\param[in]  wdt_cnt: wdt over flow cout in window mode
    \param[out] none
    \retval     none
*/
void wdt_overflow_count_win(uint16_t wdt_cnt)
{
	WDT_WINVAL = wdt_cnt;
}


