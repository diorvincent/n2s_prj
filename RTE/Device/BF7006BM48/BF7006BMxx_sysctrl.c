/*!
    \file  BF7006BMxx_sysctrl.c
    \brief system control driver
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_sysctrl.c initial version

*/

#include "BF7006BMxx_sysctrl.h"

XTAL_Init_Status is_xtal_init_success = XTAL_Init_Status_Never_Initialize;    // change in xtal_init()
volatile uint8_t xtal_timeout = 0;

/*!
    \brief      sci1 port select 
    \param[in]  port_sel: SCI1_PF0_PF1,SCI1_PE2_PE3,SCI1_PE6_PE7
    \param[out] none
    \retval     none
*/
void sci1_port_sel(uint8_t port_sel)
{
    SYS_PTSEL = port_sel;
}

/*!
    \brief      system clock select
    \param[in]  pll_source_sel: pll source clock select
                    SYS_PLL_SEL_RC1M: pll source clock select rc_1M
                    SYS_PLL_SEL_XTAL_16M: pll source clock select xtal/16
                    SYS_PLL_SEL_XTAL_12M: pll source clock select xtal/12
                    SYS_PLL_SEL_XTAL_8M: pll source clock select xtal/8
    \param[in]  clk_sel: clock select
                    SYS_CLK_PLL_32M: system clock select pll 32M hz
                    SYS_CLK_PLL_16M: system clock select pll 16M hz
                    SYS_CLK_PLL_8M: system clock select pll 8M hz
                    SYS_CLK_XTAL: system clock select xtal
    \param[out] none
    \retval     none
*/
void system_clk_sel(uint32_t pll_source_sel,uint32_t clk_sel,uint8_t xtal_freq)
{
    ErrorStatus rval;
    if((pll_source_sel == SYS_PLL_SEL_RC1M) && (clk_sel != SYS_CLK_XTAL)){
        SYS_PLL_SOURCE_SEL = pll_source_sel;
        SYS_CLK_SEL = clk_sel;
    }else{
        if((SYS_XTAL_CTRL & SYS_XTAL_CTRL_INIT) == 0U){
            rval = xtal_init();
            if(rval == ERROR){
                pll_source_sel = SYS_PLL_SEL_RC1M;
                if(clk_sel == SYS_CLK_XTAL){
                    if(xtal_freq == 0x01U){
                        clk_sel = SYS_CLK_16M;
                    }else if(xtal_freq == 0x02U){
                        clk_sel = SYS_CLK_16M;
                    }else if(xtal_freq == 0x03U){
                        clk_sel = SYS_CLK_8M;
                    }else{
                        clk_sel = SYS_CLK_32M;
                    }
                }
            }
        }
        SYS_PLL_SOURCE_SEL = pll_source_sel;
        SYS_CLK_SEL = clk_sel;
    }

    // update SystemCoreClock
    if(SYS_CLK_SEL == SYS_CLK_XTAL){
        if(xtal_freq == 0x01U){
            SystemCoreClock = (uint32_t)16000000;
        }else if(xtal_freq == 0x02U){
            SystemCoreClock = (uint32_t)12000000;
        }else if(xtal_freq == 0x03U){
            SystemCoreClock = (uint32_t)8000000;
        }
    }else{
        switch(SYS_CLK_SEL){
            case SYS_CLK_32M:
                SystemCoreClock = (uint32_t)32000000;
                break;
            case SYS_CLK_16M:
                SystemCoreClock = (uint32_t)16000000;
                break;
            case SYS_CLK_8M:
                SystemCoreClock = (uint32_t)8000000;
                break;
        }
    }
}

/*!
    \brief      xtal initiliaze
                if xtal initiliaze success,enable xtal invalid check
                if xtal initiliaze fail,return error to change clock select
    \param[in]  none
    \param[out] none
    \retval     ERROR:xtal initiliaze fail,SUCCESS:xtal initiliaze success
    \info       this function use systick to count for a timeout of 200ms, 
                be aware of systick configuration would be changed in this function
*/
/* Select optimization level O0 for this function */
#if defined ( __CC_ARM )
    #pragma push
    #pragma O0
#elif defined (__clang__)
    #pragma clang diagnostic push
    #pragma OPTIMIZE(0)
#endif

ErrorStatus xtal_init(void)
{
    /* set timeout to approximately 200ms */
#if defined ( __CC_ARM )
    uint32_t timeout = 140000UL;
#elif defined (__clang__)
    uint32_t timeout = 280000UL;
#endif

    uint32_t timeout_cycle = 0;
    ErrorStatus ret_val = ERROR;

    SYS_XTAL_CTRL |= SYS_XTAL_CTRL_EN;
    SYS_INTEN |= SYS_INTEN_XTALINIT;
    NVIC_EnableIRQ(SYS_IRQn);
    SYS_XTAL_INIT = 0x00U;
    SYS_XTAL_INIT &= ~SYS_XTAL_INIT_RSTEN;
    SYS_XTAL_INIT |= SYS_XTAL_INIT_EN;
    xtal_timeout = 0U;

    SystemCoreClockUpdate();
    if(SystemCoreClock == 32000000UL){
        timeout_cycle = timeout * 3 / 2;
    }else if(SystemCoreClock == 16000000UL){
        timeout_cycle = timeout;
    }else if(SystemCoreClock == 12000000UL){
        timeout_cycle = timeout * 2 / 3;
    }else if(SystemCoreClock == 8000000UL){
        timeout_cycle = timeout / 2;
    }else{      // should be poweron state, the reset value system clock is 16MHz
        timeout_cycle = timeout;
    }

    while(timeout_cycle > 0){
        if((SYS_XTAL_CTRL & SYS_XTAL_CTRL_INIT) != 0x00U){  //xtal initialize success then enable xtal invalid check
            SYS_XTAL_CHK = 0x00U;
            SYS_XTAL_CHK |= SYS_XTAL_CHK_EN;
            SYS_XTAL_CHK |= SYS_XTAL_CHK_RSTEN;
            SYS_INTEN |= SYS_INTEN_XTALCHK;
            SYS_XTAL_INIT |= SYS_XTAL_INIT_RSTEN;
            SYS_XTAL_INIT |= SYS_XTAL_INIT_EN;
            SYS_INTEN |= SYS_INTEN_XTALINIT;
            is_xtal_init_success = XTAL_Init_Status_Init_Success;   //xtal init flag set
            ret_val = SUCCESS;
            break;
        }
        if(xtal_timeout != 0x00U){
            SYS_XTAL_CTRL &= ~SYS_XTAL_CTRL_EN;             //xtal initialize error then disable xtal
            is_xtal_init_success = XTAL_Init_Status_Init_Failed;    //xtal init flag clear
            ret_val = ERROR;
            break;
        }
        timeout_cycle--;
    }

    if(ret_val != SUCCESS){
        SYS_XTAL_CTRL &= ~SYS_XTAL_CTRL_EN;                 //xtal initialize error then disable xtal
        is_xtal_init_success = XTAL_Init_Status_Init_Failed;    //xtal init flag clear
    }
    return ret_val;
}
/* Limits optimization level O0 only to this function */
#if defined ( __CC_ARM )
    #pragma pop
#elif defined (__clang__)
    #pragma clang diagnostic pop
#endif

/*!
    \brief      enable or disable xtal powerdown in sleepdeep mode
    \param[in]  pd_en:ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void xtal_sleepdeep_pd(FunctionalState pd_en)
{
    if(pd_en == ENABLE){
        SYS_XTAL_CTRL |= SYS_XTAL_CTRL_SLEEPPD;
    }else{
        SYS_XTAL_CTRL &= ~SYS_XTAL_CTRL_SLEEPPD;
    }
}

/*!
    \brief      enable or disable rc128k powerdown 
    \param[in]  pd_en:ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void rc128k_pd(FunctionalState pd_en)
{
    if(pd_en == ENABLE){
        SYS_CLK_PD |= SYS_CLK_PD_RC128K;
    }else{
        SYS_CLK_PD &= ~SYS_CLK_PD_RC128K;
    }
}

/*!
    \brief      clock out
    \param[in]  clk_source: CLK_OUT_XTAL_DIV_8,CLK_OUT_PLL_DIV_16,CLK_OUT_RC_32K,CLK_OUT_RC_250K
    \param[out] none
    \retval     none
*/
void clock_out(uint8_t clk_source)
{
    if(clk_source > 3U){
        return;
    }
    SYS_CLK_OUT &= 0x37U;
    SYS_CLK_OUT &= ~0x03U;
    SYS_CLK_OUT |= 0x04U;
    SYS_CLK_OUT |= clk_source;
}

/*!
    \brief      clock2 out
    \param[in]  clk2_source: CLK2_OUT_XTAL_DIV_16,CLK2_OUT_RC_250K
    \param[out] none
    \retval     none
*/
void clock2_out(uint8_t clk2_source)
{
    SYS_CLK_OUT &= 0x37U;
    if(clk2_source == CLK2_OUT_XTAL_DIV_16){
        SYS_CLK_OUT &= ~0x30U;
        SYS_CLK_OUT |= clk2_source;
    }else if(clk2_source == CLK2_OUT_RC_250K){
        SYS_CLK_OUT &= ~0x30U;
        SYS_CLK_OUT |= clk2_source;
    }else{
        SYS_CLK_OUT &= ~0x30U;
    }
}

/*!
    \brief      system interrupt vector address offset
    \param[in]  offset_addr: offset address
    \param[out] none
    \retval     none
*/
void system_intvector_offset(uint32_t offset_addr)
{
    SYS_VECTOR_OFFSET = offset_addr;
}

/*!
    \brief      system interrupt config
    \param[in]  int_state: 
                    lower power detect interrupt: SYS_INT_LVDT_ENABLE   or SYS_INT_LVDT_DISABLE
                    eeprom ECC error two bits or more interrupt: SYS_INT_ETER_ENABLE    or SYS_INT_ETER_DISABLE
                    eeprom ECC error one bit interrupt enable: SYS_INT_EOER_ENABLE      or SYS_INT_EOER_DISABLE
                    flash ECC error two bits or more interrupt: SYS_INT_FTER_ENABLE     or SYS_INT_FTER_DISABLE
                    flash ECC error one bit interrupt enable: SYS_INT_FOER_ENABLE       or SYS_INT_FOER_DISABLE
                    eeprom protect range illegal access interrupt: SYS_INT_EPOT_ENABLE  or SYS_INT_EPOT_DISABLE
                    flash protect range illegal access interrupt enable: SYS_INT_FPOT_ENABLE    or SYS_INT_FPOT_DISABLE
                    config bits error interrupt enable: SYS_INT_ADJ_ENABLE  or SYS_INT_ADJ_DISABLE
    \param[out] none
    \retval     none
*/
void system_int_cfg(uint16_t int_state,FunctionalState en_state)
{
    SYS_INTEN = int_state;
    if(en_state == ENABLE){
        NVIC_EnableIRQ(SYS_IRQn);
    }else{
        NVIC_DisableIRQ(SYS_IRQn);
    }
}

/*!
    \brief      system interrupt flag get
    \param[in]  none
    \param[out] none
    \retval     system interrupt flag
*/
uint16_t system_intflg_get(void)
{
    uint32_t retal;
    retal = SYS_INTFLG;
    return (uint16_t)retal;
}

/*!
    \brief      system interrupt flag clear
    \param[in]  int_flg: system interrupt flag
    \param[out] none
    \retval     none
*/
void system_intflg_clr(uint16_t int_flg)
{
    SYS_INTFLG = int_flg;
}

/*!
    \brief      lvdt initialize
    \param[in]  lvdt_en: lvdt enable
    \param[in]  lvdt_vol_gear: lvdt voltage gear
    \param[in]  int_en: lvdt interrupt enable
    \param[out] none
    \retval     none
*/
void lvdt_init(FunctionalState lvdt_en,uint8_t lvdt_vol_gear,FunctionalState int_en)
{
    if(lvdt_en == ENABLE){
        if(lvdt_vol_gear > 3U){
            return ;
        }
        lvdt_enable();
        SYS_LVDT_CRL &= ~0x03U;
        SYS_LVDT_CRL |= lvdt_vol_gear;
        if(int_en == ENABLE){
            SYS_LVDT_IE = 0x01U;
            NVIC_EnableIRQ(LVDT_IRQn);
        }else{
            SYS_LVDT_IE = 0x00U;
            NVIC_DisableIRQ(LVDT_IRQn);
        }
    }else{
        lvdt_disable();
    }
}

/*!
    \brief      lvdt enable
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lvdt_enable(void)
{
    SYS_CLK_PD &= ~SYS_CLK_PD_LVDT;
}

/*!
    \brief      lvdt disable
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lvdt_disable(void)
{
    SYS_CLK_PD |= SYS_CLK_PD_LVDT;
}

/*!
    \brief      lvdt interrput flag get
    \param[in]  none
    \param[out] none
    \retval     interrupt flag
*/
uint8_t lvdt_int_flag_get(void)
{
    uint32_t rtal;
    rtal = SYS_LVDT_IF;
    return (uint8_t)rtal;
}

/*!
    \brief      lvdt interrput flag clear
    \param[in]  int_flag: interrupt flag,boost flag or buck flag
    \param[in]  int_en: lvdt interrupt enable
    \param[out] none
    \retval     none
*/
void lvdt_int_flag_clr(uint8_t int_flag)
{
    SYS_LVDT_IF = int_flag;
}


/*!
    \brief      reset pin filter enable or disable
    \param[in]  filter_en: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void reset_filter(FunctionalState filter_en)
{
    SYS_EXRST = 0x01U;
    if(filter_en == ENABLE){
        SYS_EXFLT = 0x01U;
    }else{
        SYS_EXFLT = 0x00U;
    }
}

/*!
    \brief      reset flag get
    \param[in]  none
    \param[out] none
    \retval     reset flag
*/
uint16_t rst_flag_get(void)
{
    uint32_t rtal;
    rtal = SYS_RSTSTAT;
    return (uint16_t)rtal;
}


/*!
    \brief      reset flag clear
    \param[in]  rst_flag: reset flag
    \param[out] none
    \retval     none
*/
void rst_flag_clr(uint16_t rst_flag)
{
    SYS_RSTSTAT = rst_flag;
}

/*!
    \brief      delay function using system tick
    \param[in]  time: us to delay
    \param[out] none
    \retval     none
    \info       software delay function. parameter's unit is us.
*/
void delay_us(uint32_t time)
{
    uint32_t load_val = 0;
    uint32_t temp;

    if(SystemCoreClock == 32000000UL){
        load_val = 32U;
    }else if(SystemCoreClock == 16000000UL){
        load_val = 16U;
    }else if(SystemCoreClock == 12000000UL){
        load_val = 12U;
    }else if(SystemCoreClock == 8000000UL){
        load_val = 8U;
    }

    SysTick->LOAD = time * load_val;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    do
    {
        temp = SysTick->CTRL;
    }while((temp & 0x01) && !(temp & (1 << 16)));
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk);
    SysTick->VAL = 0X00;
}

/*!
    \brief      system clock switch function
    \param[in]  ClkConfig: clock configuration
    \param[out] ClkConfig: clock configuration
    \retval     none
    \info       any illegal or invalid input value will be modified and returned
*/
ErrorStatus system_clock_switch(SysClkStruct* ClkConfig)
{
    uint32_t pll_source_sel;
    uint32_t clk_sel;
    ErrorStatus xtal_init_state = ERROR;

    if(ClkConfig == NULL)
        return ERROR;

    /* initialize xtal if used as clock source */
    if((ClkConfig->sys_clk_source == System_Clock_Source_XTAL) ||
       (ClkConfig->pll_source == PLL_Source_XTAL) ){
        xtal_init_state = xtal_init();
    }

    /* when xtal fails to initialize, switch to internal rc for clock source 
       and system clock frequency would stay the same */
    if(xtal_init_state == ERROR){
        if(ClkConfig->sys_clk_source == System_Clock_Source_XTAL){
            switch(ClkConfig->xtal_clock){
                case External_Clock_Source_XTAL_8MHz:
                    ClkConfig->pll_freq = PLL_Output_Clock_8M;
                    break;
                case External_Clock_Source_XTAL_12MHz:
                    ClkConfig->pll_freq = PLL_Output_Clock_16M;
                    break;
                case External_Clock_Source_XTAL_16MHz:
                    ClkConfig->pll_freq = PLL_Output_Clock_16M;
                    break;
                default:
                    return ERROR;
            }
        }
        ClkConfig->pll_source = PLL_Source_InternalRC1MHz;
        ClkConfig->sys_clk_source = System_Clock_Source_PLL;
    }

    /* XTAL as the direct system clock source */
    if(ClkConfig->sys_clk_source == System_Clock_Source_XTAL){
        switch(ClkConfig->xtal_clock){
            case External_Clock_Source_XTAL_8MHz:
                clk_sel = SYS_CLK_XTAL;
                SystemCoreClock = 8000000UL;
                break;
            case External_Clock_Source_XTAL_12MHz:
                clk_sel = SYS_CLK_XTAL;
                SystemCoreClock = 12000000UL;
                break;
            case External_Clock_Source_XTAL_16MHz:
                clk_sel = SYS_CLK_XTAL;
                SystemCoreClock = 16000000UL;
                break;
            default:
                return ERROR;
        }
    }else if(ClkConfig->sys_clk_source == System_Clock_Source_PLL){
        /* PLL output as system clock source */
        if(ClkConfig->pll_source == PLL_Source_InternalRC1MHz){
            // internal rc as pll's input
            pll_source_sel = SYS_PLL_SEL_RC1M;
        }else if(ClkConfig->pll_source == PLL_Source_XTAL){
            // xtal as pll's input
            switch(ClkConfig->xtal_clock){
                case External_Clock_Source_XTAL_8MHz:
                    pll_source_sel = SYS_PLL_SEL_XTAL_8M;
                    break;
                case External_Clock_Source_XTAL_12MHz:
                    pll_source_sel = SYS_PLL_SEL_XTAL_12M;
                    break;
                case External_Clock_Source_XTAL_16MHz:
                    pll_source_sel = SYS_PLL_SEL_XTAL_16M;
                    break;
                default:
                    return ERROR;
            }
        }else{
            return ERROR;
        }

        /* choose pll output frequency */
        switch(ClkConfig->pll_freq){
            case PLL_Output_Clock_8M:
                clk_sel = SYS_CLK_8M;
                SystemCoreClock = 8000000UL;
                break;
            case PLL_Output_Clock_16M:
                clk_sel = SYS_CLK_16M;
                SystemCoreClock = 16000000UL;
                break;
            case PLL_Output_Clock_32M:
                clk_sel = SYS_CLK_32M;
                SystemCoreClock = 32000000UL;
                break;
            default:
                return ERROR;
        }
    }

    SYS_PLL_SOURCE_SEL = pll_source_sel;
    SYS_CLK_SEL = clk_sel;
    return SUCCESS;
}
