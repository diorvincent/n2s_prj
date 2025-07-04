/*!
    \file  BF7006BMxx_adc.c
    \brief adc driver
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_adc.c initial version
*/

#include "BF7006BMxx_adc.h"
#include "BF7006BMxx_pwm.h"

static void adc_reg_config(void);
static void adc_clk_init(uint8_t adc_clk,uint32_t sys_clk);


/*!
    \brief      adc initialize
    \param[in]  adc_init: adc initialize parameter
    \arg        adc_clk: adc clock select:system clock divide(1/2/3/4/6/8/10/12) 
    \arg        sample_clk_num: adc sample clock number set 
    \arg        adco_en: adc continuous convert enable
    \arg        data_width:adc convert data width select:8bits or 12bits
    \arg        channel_en: adc channel enale 
    \arg        int_en: adc interrupt enable
    \arg        trigger: adc trigger config 
    \arg        trigger_mode: adc trigger mode select:hardware or software
    \arg        trigger_source: adc trigger source select:PWM or RTC or NMI
    \param[in]  adc_compare:adc compare struct
        \arg      compare_en: compare enable or disable
        \arg      compare_condition: compare condition,ADC_COMP_LESS or ADC_COMP_LARGER or ADC_COMP_BETWEEN
        \arg      lower_limit_val: lower limit value
        \arg      higher_limit_val: higher limit value
    \param[out] none
    \retval     none
*/
/* Note: if compare_condition=ADC_COMP_LESS,then compare value set higher_limit_val 
         if compare_condition=ADC_COMP_LARGER,then compare value set lower_limit_val 
         if compare_condition=ADC_COMP_BETWEEN,then lower_limit_val must less than higher_limit_val
*/
void adc_init(adc_parameter_struct adc_init_para)
{
    /* adc control register config */
    ADC_SC1 = 0x1fUL;
    if(adc_init_para.adco_en == ENABLE){    //adc continuous convert mode enable
        ADC_SC1 |= ADC_SC1_ADCO;
    }else{                                  //adc continuous convert mode disable
        ADC_SC1 &= ~ADC_SC1_ADCO;
    }

    ADC_SC2 = 0X00UL;

    ADC_CFG = 0x00UL;
    if(adc_init_para.data_width == ADC_DATA_12BITS){        //adc data width 12bits
        ADC_CFG |= ADC_CFG_MODE;
    }else if(adc_init_para.data_width == ADC_DATA_8BITS){   //adc data width 8bits
        ADC_CFG &= ~ADC_CFG_MODE;
    }else{
        ADC_CFG |= ADC_CFG_MODE;
    }

    /* adc clock config,adc_clk must less than 16M */
    adc_clk_init(adc_init_para.adc_clk,SystemCoreClock);

    ADC_SPT = adc_init_para.sample_clk_num;                 //adc sample clock number set
    
    /* adc register config,note: do not change */
    adc_reg_config();
    
    /* adc trigger config */
    adc_trigger_config(adc_init_para.trigger);
    
    /* adc compare config */
    adc_compare_config(adc_init_para.compare);

    /* adc channel enable */
    adc_channel_enable(adc_init_para.channel_en);
    
    /* adc power down disable */
    adc_powerdown(DISABLE);
    
    /* adc interrupt config */
    adc_interrupt_set(adc_init_para.int_en);
    
//    adc_cgroup();
//    adc_calibrate();
}

/*!
    \brief      adc interrupt set
    \param[in]  en:ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_interrupt_set(FunctionalState en)
{
    if(en == ENABLE){
        ADC_SC1 |= ADC_SC1_AIEN;
        NVIC_EnableIRQ(ADC_IRQn);
    }else{
        ADC_SC1 &= ~ADC_SC1_AIEN;
        NVIC_DisableIRQ(ADC_IRQn);
    }
}

/*!
    \brief      wait for adc convert 
    \param[in]  none
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrorStatus wait_adc_convert(void)
{
    uint32_t timeout = 30000U;
    while(timeout != 0x00U){
        timeout --;
        if((ADC_SC1 & ADC_SC1_COCO) != 0x00U){
            return SUCCESS;
        }
    }
    return SUCCESS;
}

/*!
    \brief      adc convert data get
    \param[in]  none
    \param[out] none
    \retval     adc convert data
*/
uint16_t adc_data_get(void)
{
    return (uint16_t)ADC_DATA;
}

/*!
    \brief      adc start convert
    \param[in]  ch: adc channel to convert, write 0x1F to abort continuous conversion
    \param[out] none
    \retval     none
*/
void adc_start_convert(uint8_t ch)
{
    ch |= 0xe0U;
    ADC_SC1 |= 0x1fU;
    ADC_SC1 &= ch;
}

/*!
    \brief      adc clock init
    \param[in]  adc_clk: adc sample clock divide
    \param[in]  sys_clk: sysytem clock
    \param[out] none
    \retval     none
*/
static void adc_clk_init(uint8_t adc_clk,uint32_t sys_clk)
{    
    #define    ADC_CKC_CKV_1            ((uint8_t)0x00)
    #define    ADC_CKC_CKV_2            ((uint8_t)0x01)
    #define    ADC_CKC_CKV_4            ((uint8_t)0x02)
    #define    ADC_CKC_CKV_8            ((uint8_t)0x03)

    #define    ADC_CKC_WNUM_3            ((uint8_t)0x00 << 2)
    #define    ADC_CKC_WNUM_4            ((uint8_t)0x01 << 2)
    #define    ADC_CKC_WNUM_5            ((uint8_t)0x02 << 2)
    #define    ADC_CKC_WNUM_6            ((uint8_t)0x03 << 2)

    #define    ADC_CKC_SAMDEL_0        ((uint8_t)0x00 << 4)
    #define    ADC_CKC_SAMDEL_2        ((uint8_t)0x01 << 4)
    #define    ADC_CKC_SAMDEL_4        ((uint8_t)0x02 << 4)
    #define    ADC_CKC_SAMDEL_8        ((uint8_t)0x03 << 4)
    #define    ADC_CKC_SAMDEL_10        ((uint8_t)0x04 << 4)
    #define    ADC_CKC_SAMDEL_12        ((uint8_t)0x05 << 4)
    #define    ADC_CKC_SAMDEL_14        ((uint8_t)0x06 << 4)
    #define    ADC_CKC_SAMDEL_16        ((uint8_t)0x07 << 4)

    uint8_t adc_ckc_ckv;
    uint8_t adc_ckc_wnum;
    uint8_t adc_ckc_sambg = 0x80U;
    uint8_t adc_ckc_samdel;
    if(sys_clk == 32000000UL){
        if(adc_clk == ADC_CLK_DIV_1){        //adc_clk must less than 16M
            adc_clk = ADC_CLK_DIV_2;
        }
        switch(adc_clk){
            case ADC_CLK_DIV_2:
                adc_ckc_ckv = ADC_CKC_CKV_2;
                adc_ckc_wnum = ADC_CKC_WNUM_6;
                adc_ckc_samdel = ADC_CKC_SAMDEL_8;
                break;
            case ADC_CLK_DIV_3:
                adc_ckc_ckv = ADC_CKC_CKV_2;
                adc_ckc_wnum = ADC_CKC_WNUM_4;
                adc_ckc_samdel = ADC_CKC_SAMDEL_8;
                break;
            case ADC_CLK_DIV_4:
                adc_ckc_ckv = ADC_CKC_CKV_4;
                adc_ckc_wnum = ADC_CKC_WNUM_6;
                adc_ckc_samdel = ADC_CKC_SAMDEL_4;
                break;
            case ADC_CLK_DIV_6:
            case ADC_CLK_DIV_8:    
            case ADC_CLK_DIV_10:
            case ADC_CLK_DIV_12:
                adc_ckc_ckv = ADC_CKC_CKV_4;
                adc_ckc_wnum = ADC_CKC_WNUM_3;
                adc_ckc_samdel = ADC_CKC_SAMDEL_2;
                break;
            default:
                adc_ckc_ckv = 0x00U;
                adc_ckc_wnum = 0x00U;
                adc_ckc_samdel = 0x00U;
                break;
        }
    }else if(sys_clk == 16000000UL){
        switch(adc_clk){
            case ADC_CLK_DIV_1:
                adc_ckc_ckv = ADC_CKC_CKV_1;
                adc_ckc_wnum = ADC_CKC_WNUM_6;
                adc_ckc_samdel = ADC_CKC_SAMDEL_8;
                break;
            case ADC_CLK_DIV_2:
                adc_ckc_ckv = ADC_CKC_CKV_2;
                adc_ckc_wnum = ADC_CKC_WNUM_6;
                adc_ckc_samdel = ADC_CKC_SAMDEL_4;
                break;
            case ADC_CLK_DIV_3:
                adc_ckc_ckv = ADC_CKC_CKV_2;
                adc_ckc_wnum = ADC_CKC_WNUM_4;
                adc_ckc_samdel = ADC_CKC_SAMDEL_4;
                break;
            case ADC_CLK_DIV_4:
            case ADC_CLK_DIV_6:
            case ADC_CLK_DIV_8:    
            case ADC_CLK_DIV_10:
            case ADC_CLK_DIV_12:
                adc_ckc_ckv = ADC_CKC_CKV_2;
                adc_ckc_wnum = ADC_CKC_WNUM_3;
                adc_ckc_samdel = ADC_CKC_SAMDEL_2;
                break;
            default:
                adc_ckc_ckv = 0x00U;
                adc_ckc_wnum = 0x00U;
                adc_ckc_samdel = 0x00U;
                break;
        }
    }else{
        if(adc_clk == ADC_CLK_DIV_1){
            adc_ckc_ckv = ADC_CKC_CKV_1;
            adc_ckc_wnum = ADC_CKC_WNUM_6;
            adc_ckc_samdel = ADC_CKC_SAMDEL_4;
        }else{
            adc_ckc_ckv = ADC_CKC_CKV_1;
            adc_ckc_wnum = ADC_CKC_WNUM_3;
            adc_ckc_samdel = ADC_CKC_SAMDEL_2;
        }
    }
    ADC_CFG &= ~ADC_CFG_ADIV;
    ADC_CFG |= adc_clk;
    ADC_CKC = (adc_ckc_sambg | adc_ckc_samdel | adc_ckc_wnum | adc_ckc_ckv);
}
/*!
    \brief      adc register config
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void adc_reg_config(void)
{
    ADC_ISEL = 0X19U;
    ADC_FRSEL = 0X00U;
    ADC_CTRLSEL = 0x00U;
//    ADC_CTRLSEL = 0x02U;
}

/*!
    \brief      adc power down enable
    \param[in]  en:ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_powerdown(FunctionalState en)
{
    if(en == ENABLE){
        ADC_PD = 0x01U;
    }else{
        ADC_PD = 0x00U;
    }
}

/*!
    \brief      adc channel enable
    \param[in]  ch:adc channel enable
    \param[out] none
    \retval     none
*/
void adc_channel_enable(uint32_t ch)
{
    ADC_APCTL = 0x00U;
    ADC_APCTL |= ch;
}

/*!
    \brief      adc channel disable
    \param[in]  adc_ch:adc channel disable
    \param[out] none
    \retval     none
*/
void adc_channel_disable(uint32_t ch)
{
    ADC_APCTL &= ~ch;
}


/*!
    \brief      adc compare config
    \param[in]  adc_compare:adc compare struct
      \arg        compare_en: compare enable or disable
      \arg        compare_condition: compare condition,ADC_COMP_LESS or ADC_COMP_LARGER or ADC_COMP_BETWEEN
      \arg        lower_limit_val: lower limit value
      \arg        higher_limit_val: higher limit value
    \param[out] none
    \retval     none
*/
void adc_compare_config(adc_compare_struct adc_compare)
{
    if(adc_compare.compare_en == ENABLE){
        if(adc_compare.compare_condition == ADC_COMP_LESS){
            ADC_SC2 |= ADC_SC2_ACFE0;
            ADC_SC2 &= ~ADC_SC2_ACFE1;
            ADC_SC2 &= ~ADC_SC2_ACFGT0;
            ADC_CV0 = adc_compare.higher_limit_val;
        }else if(adc_compare.compare_condition == ADC_COMP_LARGER){
            ADC_SC2 |= ADC_SC2_ACFE0;
            ADC_SC2 &= ~ADC_SC2_ACFE1;
            ADC_SC2 |= ADC_SC2_ACFGT0;
            ADC_CV0 = adc_compare.lower_limit_val;
        }else if(adc_compare.compare_condition == ADC_COMP_BETWEEN){
            ADC_SC2 |= ADC_SC2_ACFE0;
            ADC_SC2 |= ADC_SC2_ACFE1;
            ADC_SC2 |= ADC_SC2_ACFGT0;
            ADC_SC2 &= ~ADC_SC2_ACFGT1;
            ADC_CV0 = adc_compare.lower_limit_val;
            ADC_CV1 = adc_compare.higher_limit_val;
        }else{
            ADC_SC2 &= ~ADC_SC2_ACFE0;
            ADC_SC2 &= ~ADC_SC2_ACFE1;
        }
    }
}

/*!
    \brief      adc trigger config
    \param[in]  adc_trigger:adc trigger struct
      \arg        trigger_mode: trigger mode(ADC_TRIGG_SOFT,ADC_TRIGG_HARD)
      \arg        trigger_source: trigger source(ADC_TRIGG_HARD_NMI,ADC_TRIGG_HARD_PWM,ADC_TRIGG_HARD_RTC)
    \param[out] none
    \retval     none
*/
void adc_trigger_config(adc_trigger_struct adc_trigger)
{
    /* trigger mode select */
    if(adc_trigger.trigger_mode == ADC_TRIGG_SOFT){             //select software trigger adc scan
        ADC_SC2 &= ~ADC_SC2_ADTRG;
    }else if(adc_trigger.trigger_mode == ADC_TRIGG_HARD){       //select hardware trigger adc scan
        ADC_SC2 |= ADC_SC2_ADTRG;
    }else{
        ADC_SC2 &= ~ADC_SC2_ADTRG;
    }
    
    /* hardware trigger source select */
    if(adc_trigger.trigger_source == ADC_TRIGG_HARD_NMI){       //hardware source select NMI
        ADC_SC2 |= ADC_SC2_ADHTS;
        ADC_IKW = 0x00U;
    }else if(adc_trigger.trigger_source == ADC_TRIGG_HARD_PWM){ //hardware source select PWM
        ADC_SC2 &= ~ADC_SC2_ADHTS;
        ADC_IKW = 0x01U;
        PWM_ADC_CV = adc_trigger.pwm_trigger_delay;
    }else if(adc_trigger.trigger_source == ADC_TRIGG_HARD_RTC){ //hardware source select RTC
        ADC_SC2 &= ~ADC_SC2_ADHTS;
        ADC_IKW = 0x00U;
    }else{
        ADC_SC2 &= ~ADC_SC2_ADTRG;
    }
}
