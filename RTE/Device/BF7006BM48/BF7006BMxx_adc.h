/*!
    \file  BF7006BMxx_adc.h
    \brief definitions for the adc
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_adc.h initial version
*/

#ifndef BF7006BMxx_ADC_H
#define BF7006BMxx_ADC_H

#include "BF7006BMxx.h"

/* register definitions */
#define ADC_SC1                 REG32(ADC_BASE + 0x00U)         /*!< adc control register1            */
#define ADC_SC2                 REG32(ADC_BASE + 0x04U)         /*!< adc count register2              */
#define ADC_DATA                REG32(ADC_BASE + 0x08U)         /*!< adc data register                */
#define ADC_CV0                 REG32(ADC_BASE + 0x0cU)         /*!< adc compare value register0      */
#define ADC_CV1                 REG32(ADC_BASE + 0x10U)         /*!< adc compare value register1      */
#define ADC_CFG                 REG32(ADC_BASE + 0x14U)         /*!< adc config register              */
#define ADC_APCTL               REG32(ADC_BASE + 0x18U)         /*!< adc pin analog enable register   */
#define ADC_SPT                 REG32(ADC_BASE + 0x1cU)         /*!< adc sample clock config register */
#define ADC_ALC                 REG32(ADC_BASE + 0x20U)         /*!< adc calibration config register  */
#define ADC_BL5                 REG32(ADC_BASE + 0x24U)         /*!< adc calibration bit5 register    */
#define ADC_BL6                 REG32(ADC_BASE + 0x28U)         /*!< adc calibration bit6 register    */
#define ADC_BL7                 REG32(ADC_BASE + 0x2cU)         /*!< adc calibration bit7 register    */
#define ADC_BL8                 REG32(ADC_BASE + 0x30U)         /*!< adc calibration bit8 register    */
#define ADC_BL9                 REG32(ADC_BASE + 0x34U)         /*!< adc calibration bit9 register    */
#define ADC_BL10                REG32(ADC_BASE + 0x38U)         /*!< adc calibration bit10 register   */
#define ADC_BL11                REG32(ADC_BASE + 0x3cU)         /*!< adc calibration bit11 register   */
#define ADC_CTEN                REG32(ADC_BASE + 0x40U)
#define ADC_CTWIDTH             REG32(ADC_BASE + 0x44U)
#define ADC_CTM8                REG32(ADC_BASE + 0x48U)
#define ADC_CTM4                REG32(ADC_BASE + 0x4cU)
#define ADC_CTM2                REG32(ADC_BASE + 0x50U)
#define ADC_CTL8                REG32(ADC_BASE + 0x54U)
#define ADC_CTL4                REG32(ADC_BASE + 0x58U)
#define ADC_CTL2                REG32(ADC_BASE + 0x5cU)
#define ADC_CTSL8               REG32(ADC_BASE + 0x60U)
#define ADC_CTSL4               REG32(ADC_BASE + 0x64U)
#define ADC_CTSL2               REG32(ADC_BASE + 0x68U)
#define ADC_CTSL1               REG32(ADC_BASE + 0x6cU)
#define ADC_CTCOMP              REG32(ADC_BASE + 0x70U)
#define ADC_CTGR                REG32(ADC_BASE + 0x74U)
#define ADC_CKC                 REG32(ADC_BASE + 0x78U)         /*!< adc timing sequence set register    */
#define ADC_ISEL                REG32(ADC_BASE + 0x7cU)         /*!< adc bias current select register    */
#define ADC_PD                  REG32(ADC_BASE + 0x80U)         /*!< adc power down register             */
#define ADC_TEST                REG32(ADC_BASE + 0x84U)         /*!< adc self test mode register         */
#define ADC_CALEN               REG32(ADC_BASE + 0x88U)         /*!< adc calibration enable register     */
#define ADC_IKW                 REG32(ADC_BASE + 0x8cU)         /*!< adc hardware trigge select register */
#define ADC_FRSEL               REG32(ADC_BASE + 0x90U)         /*!< adc filter select register          */
#define ADC_CTRLSEL             REG32(ADC_BASE + 0x94U)         /*!< adc compare config register         */
/* end registers definitions */

/* bits definitions */
/* ADC_SC1 bits definitions */
#define ADC_SC1_COCO            BIT(7)                          /*!< adc convert over flag             */
#define ADC_SC1_AIEN            BIT(6)                          /*!< adc convert over interrupt enable */
#define ADC_SC1_ADCO            BIT(5)                          /*!< adc continue convert enable       */
#define ADC_SC1_ADCH            BITS(0,4)                       /*!< adc convert channel select        */
#define ADC_SC1_ADCH_LSB        0U                              /*!< lowest bit of ADC_SC1_ADCH        */

/* ADC_SC2 bits definitions */
#define ADC_SC2_ADACT           BIT(7)                          /*!< adc converting flag               */
#define ADC_SC2_ADTRG           BIT(6)                          /*!< adc convert trigge select         */
#define ADC_SC2_ACFE0           BIT(5)                          /*!< adc compare0 enable               */
#define ADC_SC2_ACFGT0          BIT(4)                          /*!< adc compare0 condition select     */
#define ADC_SC2_ACFE1           BIT(3)                          /*!< adc compare1 enable               */
#define ADC_SC2_ACFGT1          BIT(2)                          /*!< adc compare1 condition select     */
#define ADC_SC2_ADHTS           BIT(1)                          /*!< adc hardware trigge source select */
#define ADC_SC2_CONREN          BIT(0)                          /*!< adc calibration enable            */

/* ADC_CFG bits definitions */
#define ADC_CFG_ADIV            BITS(4,6)                       /*!< adc clock divide config        */
#define ADC_CFG_ADIV_LSB        4U                              /*!< LSB of adc clock divide config */
#define ADC_CFG_MODE            BIT(2)                          /*!< adc convert data width select  */

/* ADC_APCTL bits definitions */
#define ADC_APCTL_23            BIT(23)                         /*!< adc23 pin analog enable */
#define ADC_APCTL_22            BIT(22)                         /*!< adc22 pin analog enable */
#define ADC_APCTL_21            BIT(21)                         /*!< adc21 pin analog enable */
#define ADC_APCTL_20            BIT(20)                         /*!< adc20 pin analog enable */
#define ADC_APCTL_19            BIT(19)                         /*!< adc19 pin analog enable */
#define ADC_APCTL_18            BIT(18)                         /*!< adc18 pin analog enable */
#define ADC_APCTL_17            BIT(17)                         /*!< adc17 pin analog enable */
#define ADC_APCTL_16            BIT(16)                         /*!< adc16 pin analog enable */
#define ADC_APCTL_15            BIT(15)                         /*!< adc15 pin analog enable */
#define ADC_APCTL_14            BIT(14)                         /*!< adc14 pin analog enable */
#define ADC_APCTL_13            BIT(13)                         /*!< adc13 pin analog enable */
#define ADC_APCTL_12            BIT(12)                         /*!< adc12 pin analog enable */
#define ADC_APCTL_11            BIT(11)                         /*!< adc11 pin analog enable */
#define ADC_APCTL_10            BIT(10)                         /*!< adc10 pin analog enable */
#define ADC_APCTL_9             BIT(9)                          /*!< adc9  pin analog enable */
#define ADC_APCTL_8             BIT(8)                          /*!< adc8  pin analog enable */
#define ADC_APCTL_7             BIT(7)                          /*!< adc7  pin analog enable */
#define ADC_APCTL_6             BIT(6)                          /*!< adc6  pin analog enable */
#define ADC_APCTL_5             BIT(5)                          /*!< adc5  pin analog enable */
#define ADC_APCTL_4             BIT(4)                          /*!< adc4  pin analog enable */
#define ADC_APCTL_3             BIT(3)                          /*!< adc3  pin analog enable */
#define ADC_APCTL_2             BIT(2)                          /*!< adc2  pin analog enable */
#define ADC_APCTL_1             BIT(1)                          /*!< adc1  pin analog enable */
#define ADC_APCTL_0             BIT(0)                          /*!< adc0  pin analog enable */

/* ADC_ALC bits definitions */
#define ADC_ALC_WIDTH           BIT(5)                          /*!< adc calibrate data width select */
#define ADC_ALC_SEL             BITS(1,4)                       /*!< adc calibrate bit select        */
#define ADC_ALC_SEL_LSB         1U                              /*!< lowest bit of ADC_ALC_SEL       */
#define ADC_ALC_EN              BIT(0)                          /*!< adc calibrate enable            */

/* ADC_TEST bits definitions */
#define ADC_TEST_NUM            BIT(1)                          /*!< adc self test convert number */
#define ADC_TEST_EN             BIT(0)                          /*!< adc self test mode ebable    */
/* end bits definitions */

/* contacts definition */
/* adc data width define */
#define ADC_DATA_12BITS         0x01U                           /*!< dc data width 12bits */
#define ADC_DATA_8BITS          0x00U                           /*!< dc data width 8bits  */

/* adc clock divide define,adc_clk m 16M */
#define ADC_CLK_DIV_1           0x00U                           /*!< adc clock select system clock divide 1  */
#define ADC_CLK_DIV_2           0x10U                           /*!< adc clock select system clock divide 2  */
#define ADC_CLK_DIV_3           0x70U                           /*!< adc clock select system clock divide 3  */
#define ADC_CLK_DIV_4           0x20U                           /*!< adc clock select system clock divide 4  */
#define ADC_CLK_DIV_6           0x30U                           /*!< adc clock select system clock divide 6  */
#define ADC_CLK_DIV_8           0x40U                           /*!< adc clock select system clock divide 8  */
#define ADC_CLK_DIV_10          0x50U                           /*!< adc clock select system clock divide 10 */
#define ADC_CLK_DIV_12          0x60U                           /*!< adc clock select system clock divide 12 */

/* adc trigger mode define */
#define ADC_TRIGG_SOFT          0x00U                           /*!< adc trigger mode select software trigger */
#define ADC_TRIGG_HARD          0x01U                           /*!< adc trigger mode select hardware trigger */

/* adc hardware trigger source select define */
#define ADC_TRIGG_HARD_NMI      0x01U                           /*!< adc hardware trigger source select NMI interrupt */
#define ADC_TRIGG_HARD_PWM      0x02U                           /*!< adc hardware trigger source select PWM interrupt */
#define ADC_TRIGG_HARD_RTC      0x03U                           /*!< adc hardware trigger source select RTC interrupt */

/* adc compare condition define */
#define ADC_COMP_LESS           0x00U                           /*!< adc compare condition: less than ADC_CV0            */
#define ADC_COMP_LARGER         0x01U                           /*!< adc compare condition: larger or equal than ADC_CV0 */
#define ADC_COMP_BETWEEN        0x02U                           /*!< adc compare condition: between ADC_CV0 and ADC_CV1  */

/* adc channel define */
#define ADC_CH_0(x)             ((uint8_t)(x))                  /*<! adc channel x                         */
#define ADC_CH_TEMP             26U                             /*<! adc channel internal temperature      */
#define ADC_CH_BG               27U                             /*!< adc channel internal bandgap (1.267V) */
#define ADC_CH_VREFH            29U                             /*!< adc channel VREFH                     */
#define ADC_CH_VREFL            30U                             /*!< adc channel VREFL                     */
#define ADC_CH_OFF              31U                             /*!< adc channel off, adc stop scan        */

/* adc compare 0 or 1 enum */
typedef enum
{
    ADC_COMPARE_0,
    ADC_COMPARE_1
}adc_compare_n;

/* ADC trigger parameters struct */
typedef struct
{
    uint8_t             trigger_mode;           /*!< adc trigger mode select:hardware or software               */
    uint8_t             trigger_source;         /*!< adc trigger source select:PWM or RTC or NMI                */
    uint16_t            pwm_trigger_delay;      /*!< delay between pwm overflow interrupt and start adc convert */
}adc_trigger_struct;

/* ADC compare function parameters struct */
typedef struct
{
    FunctionalState     compare_en;             /*!< adc compare function enable  */
    uint8_t             compare_condition;      /*!< adc compare condition select */
    uint16_t            lower_limit_val;        /*!< adc compare lower limit val  */
    uint16_t            higher_limit_val;       /*!< adc compare higher limit val */
}adc_compare_struct;

/* ADC initiliaze parameters struct */
typedef struct
{
    uint8_t             adc_clk;                /*!< adc clock select:system clock divide(1/2/3/4/6/8/10/12) */
    uint16_t            sample_clk_num;         /*!< adc sample clock number set,low 10bits valid            */
    FunctionalState     adco_en;                /*!< adc continuous convert enable                           */
    uint8_t             data_width;             /*!< adc convert data width select:8bits or 12bits           */
    uint32_t            channel_en;             /*!< adc channel enale    */
    FunctionalState     int_en;                 /*!< adc interrupt enable */
    adc_trigger_struct  trigger;                /*!< adc trigger config   */
    adc_compare_struct  compare;                /*!< adc compare config   */
    adc_compare_struct  compare_0;              /*!< adc compare 0 config */
    adc_compare_struct  compare_1;              /*!< adc compare 1 config */
}adc_parameter_struct;

/* function declarations */
/* adc initialize */
void adc_init(adc_parameter_struct adc_init_para);
/* adc channel enable */
void adc_channel_enable(uint32_t ch);
/* adc channel disable */
void adc_channel_disable(uint32_t ch);
/* adc start convert */
void adc_start_convert(uint8_t ch);
/* adc convert data get */
uint16_t adc_data_get(void);
/*! wait for adc convert */
ErrorStatus wait_adc_convert(void);
/* adc interrupt set */
void adc_interrupt_set(FunctionalState en);
/* adc power down enable */
void adc_powerdown(FunctionalState en);
/* adc compare config */
void adc_compare_config(adc_compare_struct adc_compare);
/* adc trigger config */
void adc_trigger_config(adc_trigger_struct adc_trigger);
#endif
