/*!
    \file  BF7006BMxx_config.h
    \brief peripherals configuration for BF7006BMxx
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_config.h initial version

*/

#ifndef BF7006BMxx_CONFIG_H
#define BF7006BMxx_CONFIG_H

#include "RTE_Components.h"
#include "BF7006BMxx.h"
#include "BF7006BMxx_sysctrl.h"

#ifdef BF7x06BMxx_SCI_DRIVER_PRESENT
    #include "BF7006BMxx_sci.h"
#endif

#ifdef BF7x06BMxx_CAN_DRIVER_PRESENT
    #include "BF7006BMxx_can.h"
#endif

#ifdef BF7x06BMxx_ADC_DRIVER_PRESENT
    #include "BF7006BMxx_adc.h"
#endif

#ifdef BF7x06BMxx_WDT_DRIVER_PRESENT
    #include "BF7006BMxx_wdt.h"
#endif

#ifdef BF7x06BMxx_TIMER_DRIVER_PRESENT
    #include "BF7006BMxx_timer.h"
#endif

#ifdef BF7x06BMxx_RTC_DRIVER_PRESENT
    #include "BF7006BMxx_rtc.h"
#endif

#ifdef BF7x06BMxx_PWM_DRIVER_PRESENT
    #include "BF7006BMxx_pwm.h"
#endif

#ifdef BF7x06BMxx_GPIO_DRIVER_PRESENT
    #include "BF7006BMxx_gpio.h"
#endif

#ifdef BF7x06BMxx_EFLASH_DRIVER_PRESENT
    #include "BF7006BMxx_eflash.h"
#endif

/* peripherals_config return status */
typedef struct{
#ifdef BF7x06BMxx_SCI_DRIVER_PRESENT
    ErrorStatus sci;
#endif
#ifdef BF7x06BMxx_CAN_DRIVER_PRESENT
    ErrorStatus can;
#endif
#ifdef BF7x06BMxx_ADC_DRIVER_PRESENT
    ErrorStatus adc;
#endif
#ifdef BF7x06BMxx_WDT_DRIVER_PRESENT
    ErrorStatus wdt;
#endif
#ifdef BF7x06BMxx_TIMER_DRIVER_PRESENT
    ErrorStatus timer;
#endif
#ifdef BF7x06BMxx_RTC_DRIVER_PRESENT
    ErrorStatus rtc;
#endif
#ifdef BF7x06BMxx_PWM_DRIVER_PRESENT
    ErrorStatus pwm;
#endif
#ifdef BF7x06BMxx_GPIO_DRIVER_PRESENT
    ErrorStatus gpio;
#endif
    ErrorStatus overall;        /* a single error would set this var error during initialization */
}config_return_status;


/* call this function to initialize all selected peripherals */
config_return_status peripherals_config(void);

/* call this function to initialize system resources */
void system_config(void);

/* call the following functions to configure single peripheral */
ErrorStatus adc_config(void);
ErrorStatus sci_config(void);
ErrorStatus can_config(void);
ErrorStatus timer_config(void);
ErrorStatus pwm_config(void);
ErrorStatus wdt_cfg(void);
ErrorStatus rtc_config(void);
ErrorStatus gpio_config(void);

#endif
