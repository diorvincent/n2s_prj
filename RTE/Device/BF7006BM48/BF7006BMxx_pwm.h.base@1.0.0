/*!
    \file  BF7006BMxx_pwm.h
    \brief definitions for the pwm
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_pwm.h initial version

*/

#ifndef BF7006BMxx_PWM_H
#define	BF7006BMxx_PWM_H

#include "BF7006BMxx.h"

/* register definitions */
#define PWM_SC                      (REG32(PWM_BASE + 0x00U))       /*!< pwm control register               */
#define PWM_CNT                     (REG32(PWM_BASE + 0x04U))       /*!< pwm current count register         */
#define PWM_MOD                     (REG32(PWM_BASE + 0x08U))       /*!< pwm mod count register             */
#define PWM_C0SC                    (REG32(PWM_BASE + 0x0cU))       /*!< pwm channel 0 control register     */
#define PWM_C0V                     (REG32(PWM_BASE + 0x10U))       /*!< pwm channel 0 count register       */
#define PWM_C1SC                    (REG32(PWM_BASE + 0x14U))       /*!< pwm channel 1 control register     */
#define PWM_C1V                     (REG32(PWM_BASE + 0x18U))       /*!< pwm channel 1 count register       */
#define PWM_C2SC                    (REG32(PWM_BASE + 0x1cU))       /*!< pwm channel 2 control register     */
#define PWM_C2V                     (REG32(PWM_BASE + 0x20U))       /*!< pwm channel 2 count register       */
#define PWM_C3SC                    (REG32(PWM_BASE + 0x24U))       /*!< pwm channel 3 control register     */
#define PWM_C3V                     (REG32(PWM_BASE + 0x28U))       /*!< pwm channel 3 count register       */
#define PWM_C4SC                    (REG32(PWM_BASE + 0x2cU))       /*!< pwm channel 4 control register     */
#define PWM_C4V                     (REG32(PWM_BASE + 0x30U))       /*!< pwm channel 4 count register       */
#define PWM_C5SC                    (REG32(PWM_BASE + 0x34U))       /*!< pwm channel 5 control register     */
#define PWM_C5V                     (REG32(PWM_BASE + 0x38U))       /*!< pwm channel 5 count register       */
#define PWM_ADC_CV                  (REG32(PWM_BASE + 0x3CU))       /*!< pwm trigg adc scan count register  */
/* end register definitions */

/* bits definitions */
/* PWM_SC */
#define PWM_SC_TOF                  BIT(7)                          /*!< pwm over flow interrupt flag       */
#define PWM_SC_TOIE                 BIT(6)                          /*!< pwm over flow interrupt enable     */
#define PWM_SC_CPWMS                BIT(5)                          /*!< pwm count unidirectional or bidirectional select */
#define PWM_SC_CLK_SEL              BITS(3,4)                       /*!< pwm clock select                   */
#define PWM_SC_CLK_SEL_LSB          3                               /*!< pwm clock select LSB               */
#define PWM_SC_CLK_DIV              BITS(0,2)                       /*!< pwm clock divide                   */
#define PWM_SC_CLK_DIV_LSB          0                               /*!< pwm clock divide LSB               */

/* PWM_CnSC(n=0~5) */
#define PWM_CnSC_IF                 BIT(7)                          /*!< pwm channel n input or output capture interrupt flag   */
#define PWM_CnSC_IE                 BIT(6)                          /*!< pwm channel n input or output capture interrupt enable */
#define PWM_CnSC_MS                 BITS(4,5)                       /*!< pwm channel n mode select          */
#define PWM_CnSC_MS_LSB             4U                              /*!< pwm channel n mode select LSB      */
#define PWM_CnSC_ELS                BITS(2,3)                       /*!< pwm channel n edge or level select */
#define PWM_CnSC_ELS_LSB            2U                              /*!< pwm channel n edge or level select LSB */
/* end bits definitions */

/* contacts definitions */
/* pwm interrupt enable */
#define PWM_INT_ENABLE              BIT(6)                          /*!< pwm interrupt enable   */
#define PWM_INT_DISABLE             0U                              /*!< pwm interrupt disable  */

/* pwm cpwms set */
#define PWM_CPWMS_UNIDIR            0U                              /*!< pwm count unidirectional   */
#define PWM_CPWMS_BIDIR             BIT(5)                          /*!< pwm count bidirectional    */

/* pwm clock select */
#define PWM_CLK_SEL_SYS             (1U << PWM_SC_CLK_SEL_LSB)      /*!< pwm clock select as system clock       */
#define PWM_CLK_SEL_EXIN            (3U << PWM_SC_CLK_SEL_LSB)      /*!< pwm clock select as external input pin */
#define PWM_CLK_SEL_CLOSE           0U                              /*!< pwm clock close                        */

/* pwm clock divide */
#define PWM_CLK_DIV_1               0U                              /*!< pwm clock divide 1 */
#define PWM_CLK_DIV_2               1U                              /*!< pwm clock divide 2 */
#define PWM_CLK_DIV_4               2U                              /*!< pwm clock divide 4 */
#define PWM_CLK_DIV_8               3U                              /*!< pwm clock divide 8 */
#define PWM_CLK_DIV_16              4U                              /*!< pwm clock divide 16 */
#define PWM_CLK_DIV_32              5U                              /*!< pwm clock divide 32 */
#define PWM_CLK_DIV_64              6U                              /*!< pwm clock divide 64 */
#define PWM_CLK_DIV_128             7U                              /*!< pwm clock divide 128 */

/* pwm channel n interrupr enable */
#define PWM_CHn_INT_ENABLE          BIT(6)
#define PWM_CHn_INT_DISABLE         0U

/* pwm channel n mode select */
#define PWM_CHn_MS(x)               (PWM_CnSC_MS & ((uint8_t)(x) << PWM_CnSC_MS_LSB))

/* pwm channel n edge or level select */
#define PWM_CHn_ELS(x)              (PWM_CnSC_ELS & ((uint8_t)(x) << PWM_CnSC_ELS_LSB))

/* function declarations */
/* pwm initialize */
void pwm_init(uint8_t pwm_sc,uint16_t pwm_mod);
/* pwm mod count set */
void pwm_mod_set(uint16_t mod_count);
/* pwm current count get */
uint16_t pwm_get_count(void);
/* pwm interrupt flag clear */
void pwm_tof_clr(void);

/* pwm channel 0 initialize */
void pwm_ch0_init(uint8_t pwm_ch_sc,uint16_t pwm_ch_cnt);
/* pwm channel 0 disable */
void pwm_ch0_disable(void);
/* pwm channel 0 count set */
void pwm_ch0_cnt_set(uint16_t count);
/* pwm channel 0 current count get */
uint16_t pwm_ch0_get_count(void);
/* pwm channel 0 interrupt flag clear */
void pwm_ch0_if_clr(void);

/* pwm channel 1 initialize */
void pwm_ch1_init(uint8_t pwm_ch_sc,uint16_t pwm_ch_cnt);
/* pwm channel 1 disable */
void pwm_ch1_disable(void);
/* pwm channel 1 count set */
void pwm_ch1_cnt_set(uint16_t count);
/* pwm channel 1 current count get */
uint16_t pwm_ch1_get_count(void);
/* pwm channel 1 interrupt flag clear */
void pwm_ch1_if_clr(void);

/* pwm channel 2 initialize */
void pwm_ch2_init(uint8_t pwm_ch_sc,uint16_t pwm_ch_cnt);
/* pwm channel 2 disable */
void pwm_ch2_disable(void);
/* pwm channel 2 count set */
void pwm_ch2_cnt_set(uint16_t count);
/* pwm channel 2 current count get */
uint16_t pwm_ch2_get_count(void);
/* pwm channel 2 interrupt flag clear */
void pwm_ch2_if_clr(void);

/* pwm channel 3 initialize */
void pwm_ch3_init(uint8_t pwm_ch_sc,uint16_t pwm_ch_cnt);
/* pwm channel 3 disable */
void pwm_ch3_disable(void);
/* pwm channel 3 count set */
void pwm_ch3_cnt_set(uint16_t count);
/* pwm channel 3 current count get */
uint16_t pwm_ch3_get_count(void);
/* pwm channel 3 interrupt flag clear */
void pwm_ch3_if_clr(void);

/* pwm channel 4 initialize */
void pwm_ch4_init(uint8_t pwm_ch_sc,uint16_t pwm_ch_cnt);
/* pwm channel 4 disable */
void pwm_ch4_disable(void);
/* pwm channel 4 count set */
void pwm_ch4_cnt_set(uint16_t count);
/* pwm channel 4 current count get */
uint16_t pwm_ch4_get_count(void);
/* pwm channel 4 interrupt flag clear */
void pwm_ch4_if_clr(void);

/* pwm channel 5 initialize */
void pwm_ch5_init(uint8_t pwm_ch_sc,uint16_t pwm_ch_cnt);
/* pwm channel 5 disable */
void pwm_ch5_disable(void);
/* pwm channel 5 count set */
void pwm_ch5_cnt_set(uint16_t count);
/* pwm channel 5 current count get */
uint16_t pwm_ch5_get_count(void);
/* pwm channel 5 interrupt flag clear */
void pwm_ch5_if_clr(void);


#endif
