/*!
    \file  BF7006BMxx_gpio.h
    \brief definitions for the gpio
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_gpio.h initial version

*/

#ifndef BF7006BMxx_GPIO_H
#define	BF7006BMxx_GPIO_H

#include "BF7006BMxx.h"

/* registers definitions */
#define GPIO_PTD(gpiox)                 (REG32((gpiox) + 0x00U))        /*!< gpio(A/B/C/D/E/F/G) data register */
#define GPIO_PTDD(gpiox)                (REG32((gpiox) + 0x04U))        /*!< gpio(A/B/C/D/E/F/G) direction register */
#define GPIO_PTPE(gpiox)                (REG32((gpiox) + 0x08U))        /*!< gpio(A/B/C/D/E/F/G) pull up/down enable register */
#define GPIO_PTSC(gpiox)                (REG32((gpiox) + 0x10U))        /*!< gpio(A/B/D) control register */
#define GPIO_PTPS(gpiox)                (REG32((gpiox) + 0x14U))        /*!< gpio(A/B/D) port interrupt enable register */
#define GPIO_PTES(gpiox)                (REG32((gpiox) + 0x18U))        /*!< gpio(A/B/D) port interrupt edge select register */
#define GPIOA_INTSTA                    (REG32(GPIO_BASE + 0x94U))      /*!< GPIOA interrupt status register */
#define GPIOB_INTSTA                    (REG32(GPIO_BASE + 0x98U))      /*!< GPIOB interrupt status register */
#define GPIOD_INTSTA                    (REG32(GPIO_BASE + 0x9CU))      /*!< GPIOD interrupt status register */
#define NMISC                           (REG32(GPIO_BASE + 0xA0U))      /*!< NMI port control register */

/* bits definitions */

/* GPIO_PTD */
#define GPIO_PTD_PTD0                   BIT(0)                          /*!< port pin 0 data */
#define GPIO_PTD_PTD1                   BIT(1)                          /*!< port pin 1 data */
#define GPIO_PTD_PTD2                   BIT(2)                          /*!< port pin 2 data */
#define GPIO_PTD_PTD3                   BIT(3)                          /*!< port pin 3 data */
#define GPIO_PTD_PTD4                   BIT(4)                          /*!< port pin 4 data */
#define GPIO_PTD_PTD5                   BIT(5)                          /*!< port pin 5 data */
#define GPIO_PTD_PTD6                   BIT(6)                          /*!< port pin 6 data */
#define GPIO_PTD_PTD7                   BIT(7)                          /*!< port pin 7 data */

/* GPIO_PTDD */
#define GPIO_PTDD_PTDD0                 BIT(0)                          /*!< port pin 0 direction */
#define GPIO_PTDD_PTDD1                 BIT(1)                          /*!< port pin 1 direction */
#define GPIO_PTDD_PTDD2                 BIT(2)                          /*!< port pin 2 direction */
#define GPIO_PTDD_PTDD3                 BIT(3)                          /*!< port pin 3 direction */
#define GPIO_PTDD_PTDD4                 BIT(4)                          /*!< port pin 4 direction */
#define GPIO_PTDD_PTDD5                 BIT(5)                          /*!< port pin 5 direction */
#define GPIO_PTDD_PTDD6                 BIT(6)                          /*!< port pin 6 direction */
#define GPIO_PTDD_PTDD7                 BIT(7)                          /*!< port pin 7 direction */

/* GPIO_PTPE */
#define GPIO_PTPE_PTPE0                 BIT(0)                          /*!< port pin 0 pull up enable */
#define GPIO_PTPE_PTPE1                 BIT(1)                          /*!< port pin 1 pull up enable */
#define GPIO_PTPE_PTPE2                 BIT(2)                          /*!< port pin 2 pull up enable */
#define GPIO_PTPE_PTPE3                 BIT(3)                          /*!< port pin 3 pull up enable */
#define GPIO_PTPE_PTPE4                 BIT(4)                          /*!< port pin 4 pull up enable */
#define GPIO_PTPE_PTPE5                 BIT(5)                          /*!< port pin 5 pull up enable */
#define GPIO_PTPE_PTPE6                 BIT(6)                          /*!< port pin 6 pull up enable */
#define GPIO_PTPE_PTPE7                 BIT(7)                          /*!< port pin 7 pull up enable */

/* GPIO_PTSC */
#define GPIO_PTSC_TRGMOD                BIT(0)                          /*!< port interrupt trigge mode select */
#define GPIO_PTSC_IE                    BIT(1)                          /*!< port interrupt enable */
#define GPIO_PTSC_ACK                   BIT(2)                          /*!< port interrupt acknowledge */
#define GPIO_PTSC_IF                    BIT(3)                          /*!< port interrupt flag */

/* GPIO_PS */
#define GPIO_PTPS_PTPS0                 BIT(0)                          /*!< pin 0 port interrupt function enable */
#define GPIO_PTPS_PTPS1                 BIT(1)                          /*!< pin 1 port interrupt function enable */
#define GPIO_PTPS_PTPS2                 BIT(2)                          /*!< pin 2 port interrupt function enable */
#define GPIO_PTPS_PTPS3                 BIT(3)                          /*!< pin 3 port interrupt function enable */
#define GPIO_PTPS_PTPS4                 BIT(4)                          /*!< pin 4 port interrupt function enable */
#define GPIO_PTPS_PTPS5                 BIT(5)                          /*!< pin 5 port interrupt function enable */
#define GPIO_PTPS_PTPS6                 BIT(6)                          /*!< pin 6 port interrupt function enable */
#define GPIO_PTPS_PTPS7                 BIT(7)                          /*!< pin 7 port interrupt function enable */

/* GPIO_PTES */
#define GPIO_PTES_PTES0                 BIT(0)                          /*!< port pin 0 edge trigge select */
#define GPIO_PTES_PTES1                 BIT(1)                          /*!< port pin 1 edge trigge select */
#define GPIO_PTES_PTES2                 BIT(2)                          /*!< port pin 2 edge trigge select */
#define GPIO_PTES_PTES3                 BIT(3)                          /*!< port pin 3 edge trigge select */
#define GPIO_PTES_PTES4                 BIT(4)                          /*!< port pin 4 edge trigge select */
#define GPIO_PTES_PTES5                 BIT(5)                          /*!< port pin 5 edge trigge select */
#define GPIO_PTES_PTES6                 BIT(6)                          /*!< port pin 6 edge trigge select */
#define GPIO_PTES_PTES7                 BIT(7)                          /*!< port pin 7 edge trigge select */

/* GPIOA_INTSTA */
#define GPIOA_INTSTA_PIN0               BIT(0)                          /*!< port A pin 0 interrupt state */
#define GPIOA_INTSTA_PIN1               BIT(1)                          /*!< port A pin 1 interrupt state */
#define GPIOA_INTSTA_PIN2               BIT(2)                          /*!< port A pin 2 interrupt state */
#define GPIOA_INTSTA_PIN3               BIT(3)                          /*!< port A pin 3 interrupt state */
#define GPIOA_INTSTA_PIN4               BIT(4)                          /*!< port A pin 4 interrupt state */
#define GPIOA_INTSTA_PIN5               BIT(5)                          /*!< port A pin 5 interrupt state */
#define GPIOA_INTSTA_PIN6               BIT(6)                          /*!< port A pin 6 interrupt state */
#define GPIOA_INTSTA_PIN7               BIT(7)                          /*!< port A pin 7 interrupt state */

/* GPIOB_INTSTA */
#define GPIOB_INTSTA_PIN0               BIT(0)                          /*!< port B pin 0 interrupt state */
#define GPIOB_INTSTA_PIN1               BIT(1)                          /*!< port B pin 1 interrupt state */
#define GPIOB_INTSTA_PIN2               BIT(2)                          /*!< port B pin 2 interrupt state */
#define GPIOB_INTSTA_PIN3               BIT(3)                          /*!< port B pin 3 interrupt state */
#define GPIOB_INTSTA_PIN4               BIT(4)                          /*!< port B pin 4 interrupt state */
#define GPIOB_INTSTA_PIN5               BIT(5)                          /*!< port B pin 5 interrupt state */
#define GPIOB_INTSTA_PIN6               BIT(6)                          /*!< port B pin 6 interrupt state */
#define GPIOB_INTSTA_PIN7               BIT(7)                          /*!< port B pin 7 interrupt state */

/* GPIOD_INTSTA */
#define GPIOD_INTSTA_PIN0               BIT(0)                          /*!< port D pin 0 interrupt state */
#define GPIOD_INTSTA_PIN1               BIT(1)                          /*!< port D pin 1 interrupt state */
#define GPIOD_INTSTA_PIN2               BIT(2)                          /*!< port D pin 2 interrupt state */
#define GPIOD_INTSTA_PIN3               BIT(3)                          /*!< port D pin 3 interrupt state */
#define GPIOD_INTSTA_PIN4               BIT(4)                          /*!< port D pin 4 interrupt state */
#define GPIOD_INTSTA_PIN5               BIT(5)                          /*!< port D pin 5 interrupt state */
#define GPIOD_INTSTA_PIN6               BIT(6)                          /*!< port D pin 6 interrupt state */
#define GPIOD_INTSTA_PIN7               BIT(7)                          /*!< port D pin 7 interrupt state */

/* NMISC */
#define NMISC_MOD                       BIT(0)                          /*!< NMI interrupt trigge mode select */
#define NMISC_IE                        BIT(1)                          /*!< NMI interrupt enable */
#define NMISC_ACK                       BIT(2)                          /*!< NMI interrupt acknowledge */
#define NMISC_IF                        BIT(3)                          /*!< NMI interrupt flag */
#define NMISC_PE                        BIT(4)                          /*!< port NMI function enable */
#define NMISC_EDG                       BIT(5)                          /*!< NMI interrupt edge select */
#define NMISC_NMPDD                     BIT(6)                          /*!< NMI pull-up enable */

/* GPIO pin definitions */
#define GPIO_PIN_0                      BIT(0)                          /*!< GPIO pin 0 */
#define GPIO_PIN_1                      BIT(1)                          /*!< GPIO pin 1 */
#define GPIO_PIN_2                      BIT(2)                          /*!< GPIO pin 2 */
#define GPIO_PIN_3                      BIT(3)                          /*!< GPIO pin 3 */
#define GPIO_PIN_4                      BIT(4)                          /*!< GPIO pin 4 */
#define GPIO_PIN_5                      BIT(5)                          /*!< GPIO pin 5 */
#define GPIO_PIN_6                      BIT(6)                          /*!< GPIO pin 6 */
#define GPIO_PIN_7                      BIT(7)                          /*!< GPIO pin 7 */
#define GPIO_PIN_ALL                    BITS(0,7)                       /*!< GPIO pin all */

/* GPIO mode definitions */
typedef enum
{
    GPIO_MODE_IN_FLOATING,                                              /*!< floating input mode */
    GPIO_MODE_IPU,                                                      /*!< pull-up input mode */
    GPIO_MODE_OUT,                                                      /*!< GPIO output mode */
}GPIO_MODE;


/* GPIO interrupt mode definitions */
typedef enum
{
    GPIO_TRG_HIGH,                                                      /*!< gpio trigge mode in rising edge or high level */
    GPIO_TRG_LOW,                                                       /*!< gpio trigge mode in falling edge or low level */
    GPIO_TRG_RISING,                                                    /*!< gpio trigge mode in rising edge */
    GPIO_TRG_FALLING,                                                   /*!< gpio trigge mode in falling edge */
}GPIO_TRG_MODE;

/* NMI trigg mode definitions */
#define NMI_TRG_HIGH                    0x21                            /*!< nmi trigge mode in rising edge or high level */
#define NMI_TRG_LOW                     0x01                            /*!< nmi trigge mode in falling edge or low level */
#define NMI_TRG_RISING                  0x20                            /*!< nmi trigge mode in rising edge */
#define NMI_TRG_FALLING                 0x00                            /*!< nmi trigge mode in falling edge */

/* function declarations */
/* initialize gpio  */
void gpio_init(uint32_t gpio_periph,GPIO_MODE mode,uint8_t pin);
/* gpio bit set */
void gpio_bit_set(uint32_t gpio_periph,uint8_t pin);
/* gpio bit reset */
void gpio_bit_reset(uint32_t gpio_periph,uint8_t pin);
/* write data to the specified GPIO pin */
void gpio_bit_write(uint32_t gpio_periph,uint8_t pin,FlagStatus bit_value);
/* gpio port write */
void gpio_port_write(uint32_t gpio_periph,uint8_t data);
/* get GPIO pin status */
FlagStatus gpio_bit_get(uint32_t gpio_periph,uint8_t pin);
/* get GPIO port status */
uint8_t gpio_port_get(uint32_t gpio_periph);
/* gpio toggle */
void gpio_toggle(uint32_t gpio_periph,uint8_t pin);
/* gpio trigge mode set */
ErrorStatus gpio_trigge_mode(uint32_t gpio_periph,GPIO_TRG_MODE trg_mode,uint8_t pin);
/* gpio trigge interrupt set */
void gpio_interrupt_set(uint32_t gpio_periph,uint8_t pin,FunctionalState value);
/* get gpio port interrupt state */
uint8_t get_gpio_port_interrupt_state(uint32_t gpio_periph);
/* get gpio interrupt state */
FlagStatus get_gpio_interrupt_state(uint32_t gpio_periph,uint8_t pin);
/* clr gpio interrupt state */
void clr_gpio_interrupt_state(uint32_t gpio_periph,uint8_t pin);
/* nmi initialize */
void nmi_init(uint8_t trigg_mode,FunctionalState state);
/*  clr nmi interrupt flag */
void clr_nmi_interrupt_flag(void);
#endif
