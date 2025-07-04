/*!
    \file  BF7006BMxx_gpio.c
    \brief gpio driver
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_gpio.c initial version

*/

#include "BF7006BMxx_gpio.h"

/*!
    \brief      initialize gpio 
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G) 
    \param[in]  mode: gpio pin mode
      \arg        GPIO_MODE_IN_FLOATING: floating input mode
      \arg        GPIO_MODE_IPU: pull-up input mode
      \arg        GPIO_MODE_OUT: GPIO output
    \param[in]  pin: GPIO_PIN_x(x=0..7), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_init(uint32_t gpio_periph,GPIO_MODE mode,uint8_t pin)
{
	switch(mode){
		case GPIO_MODE_IN_FLOATING:
			GPIO_PTDD(gpio_periph) &= ~pin;
			GPIO_PTPE(gpio_periph) &= ~pin;
			break;
		case GPIO_MODE_IPU:
			GPIO_PTDD(gpio_periph) &= ~pin;
			GPIO_PTPE(gpio_periph) |= pin;
			break;
		case GPIO_MODE_OUT:
			GPIO_PTDD(gpio_periph) |= pin;
			break;
		default:
			/* error gpio mode */
			break;
	}
}

/*!
    \brief      gpio bit set
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G) 
    \param[in]  pin: GPIO_PIN_x(x=0..7), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_set(uint32_t gpio_periph,uint8_t pin)
{
	GPIO_PTD(gpio_periph) |= pin;
}

/*!
    \brief      gpio bit reset
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G) 
    \param[in]  pin: GPIO_PIN_x(x=0..7), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_reset(uint32_t gpio_periph,uint8_t pin)
{
	GPIO_PTD(gpio_periph) &= ~pin;
}

/*!
    \brief      write data to the specified GPIO pin
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G) 
    \param[in]  pin: GPIO_PIN_x(x=0..7)
    \param[in]  bit_value: SET or RESET
      \arg        RESET: clear the port pin
      \arg        SET: set the port pin
    \param[out] none
    \retval     none
*/
void gpio_bit_write(uint32_t gpio_periph,uint8_t pin,FlagStatus bit_value)
{
    if(bit_value == SET){
        GPIO_PTD(gpio_periph) |= pin;
    }else{
        GPIO_PTD(gpio_periph) &= ~pin;
    }
}

/*!
    \brief      gpio port write
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G) 
    \param[in]  data: specify the value to be written to the port output data register
    \param[out] none
    \retval     none
*/
void gpio_port_write(uint32_t gpio_periph,uint8_t data)
{
	GPIO_PTD(gpio_periph) = data;
}

/*!
    \brief      get GPIO pin status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G) 
    \param[in]  pin: GPIO_PIN_x(x=0..7), GPIO_PIN_ALL
    \param[out] none
    \retval     input status of gpio pin: SET or RESET
*/
FlagStatus gpio_bit_get(uint32_t gpio_periph,uint8_t pin)
{
	
    if((GPIO_PTD(gpio_periph)&(pin)) != 0x00U){
        return SET; 
    }else{
        return RESET;
    }
}

/*!
    \brief      get GPIO port status
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G) 
    \param[out] none
    \retval     input status of gpio all pins
*/
uint8_t gpio_port_get(uint32_t gpio_periph)
{
	uint32_t retal;
	retal = GPIO_PTD(gpio_periph);
	return (uint8_t)retal;

}

/*!
    \brief      gpio toggle
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G) 
    \param[in]  pin: GPIO_PIN_x(x=0..7), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_toggle(uint32_t gpio_periph,uint8_t pin)
{
	if(gpio_bit_get(gpio_periph,pin) == SET){
		gpio_bit_reset(gpio_periph,pin);
	}else{
		gpio_bit_set(gpio_periph,pin);
	}
}

/*!
    \brief      gpio trigge mode set
    \param[in]  gpio_periph: GPIOx(x = A,B,C,D,E,F,G) 
	\param[in]	trg_mode: GPIO_TRG_HIGH,GPIO_TRG_LOW,GPIO_TRG_RISING,GPIO_TRG_FALLING
    \param[in]  pin: GPIO_PIN_x(x=0..7), GPIO_PIN_ALL
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrorStatus gpio_trigge_mode(uint32_t gpio_periph,GPIO_TRG_MODE trg_mode,uint8_t pin)
{
	if((gpio_periph != ((uint32_t)GPIOA)) && (gpio_periph != ((uint32_t)GPIOB)) && (gpio_periph != ((uint32_t)GPIOD))){
		return ERROR;
	}
	/* GPIO interrput trigge mode configuration */
	switch(trg_mode){
		case GPIO_TRG_HIGH:
			GPIO_PTSC(gpio_periph) |= GPIO_PTSC_TRGMOD;
			GPIO_PTES(gpio_periph) |= pin;
			break;
		case GPIO_TRG_LOW:
			GPIO_PTSC(gpio_periph) |= GPIO_PTSC_TRGMOD;
			GPIO_PTES(gpio_periph) &= ~pin;
			break;
		case GPIO_TRG_RISING:
			GPIO_PTSC(gpio_periph) &= ~GPIO_PTSC_TRGMOD;
			GPIO_PTES(gpio_periph) |= pin;
			break;
		case GPIO_TRG_FALLING:
			GPIO_PTSC(gpio_periph) &= ~GPIO_PTSC_TRGMOD;
			GPIO_PTES(gpio_periph) &= ~pin;
			break;
		default:
			/* error */
			break;
	}
	/* gpio trigge pin enable */
	GPIO_PTPS(gpio_periph) |= pin;
	return SUCCESS;
}

/*!
    \brief      gpio trigge interrupt set
    \param[in]  gpio_periph: GPIOx(x = A,B,D) 
    \param[in]  pin: GPIO_PIN_x(x=0..7), GPIO_PIN_ALL
	\param[in]	value: ENABLE or DISABLE
    \param[out] none
    \retval     ERROR or SUCCESS
*/
void gpio_interrupt_set(uint32_t gpio_periph,uint8_t pin,FunctionalState value)
{
		/* gpio trigge interrupt enable */
	if(ENABLE == value){
		GPIO_PTSC(gpio_periph) |= GPIO_PTSC_IE;
		NVIC_EnableIRQ(GPIO_IRQn);
	}else{
		GPIO_PTSC(gpio_periph) &= ~GPIO_PTSC_IE;
		NVIC_DisableIRQ(GPIO_IRQn);
	}
}

/*!
    \brief      get gpio port interrupt state
    \param[in]  gpio_periph: GPIOx(x = A,B,D) 
    \param[out] none
    \retval     gpio port interrupt state
*/
uint8_t get_gpio_port_interrupt_state(uint32_t gpio_periph)
{
	uint32_t retal;
	if((GPIO_PTSC(gpio_periph) & GPIO_PTSC_IF) != 0x00U){
		if(gpio_periph == (uint32_t)GPIOA){
			retal = GPIOA_INTSTA;
		}else if(gpio_periph == (uint32_t)GPIOB){
			retal = GPIOB_INTSTA;
		}else if(gpio_periph == (uint32_t)GPIOD){
			retal = GPIOD_INTSTA;
		}else{
			retal = (uint32_t)0x00;
		}
	}else{
		retal = (uint32_t)0x00;
	}
	return (uint8_t)retal;
}

/*!
    \brief      get gpio interrupt state
    \param[in]  gpio_periph: GPIOx(x = A,B,D) 
    \param[in]  pin: GPIO_PIN_x(x=0..7), GPIO_PIN_ALL
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus get_gpio_interrupt_state(uint32_t gpio_periph,uint8_t pin)
{
	if((GPIO_PTSC(gpio_periph) & GPIO_PTSC_IF) != 0U){
		if(gpio_periph == (uint32_t)GPIOA){
			if((GPIOA_INTSTA & pin) != 0U){
				return SET;
			}else{
				return RESET;
			}
		}else if(gpio_periph == (uint32_t)GPIOB){
			if((GPIOB_INTSTA & pin) != 0U){
				return SET;
			}else{
				return RESET;
			}
		}else if(gpio_periph == (uint32_t)GPIOD){
			if((GPIOD_INTSTA & pin) != 0U){
				return SET;
			}else{
				return RESET;
			}
		}else{
			return RESET;
		}
	}else{
		return RESET;
	}
}

/*!
    \brief      clr gpio interrupt state
    \param[in]  gpio_periph: GPIOx(x = A,B,D) 
    \param[in]  pin: GPIO_PIN_x(x=0..7), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void clr_gpio_interrupt_state(uint32_t gpio_periph,uint8_t pin)
{
	if(gpio_periph == (uint32_t)GPIOA){
		GPIOA_INTSTA |= ((uint32_t)pin & 0x000000FFUL);
		GPIO_PTSC((uint32_t)GPIOA) |= GPIO_PTSC_ACK;
	}else if(gpio_periph == (uint32_t)GPIOB){
		GPIOB_INTSTA |= ((uint32_t)pin & 0x000000FFUL);
		GPIO_PTSC((uint32_t)GPIOB) |= GPIO_PTSC_ACK;
	}else if(gpio_periph == (uint32_t)GPIOD){
		GPIOD_INTSTA |= ((uint32_t)pin & 0x000000FFUL);
		GPIO_PTSC((uint32_t)GPIOD) |= GPIO_PTSC_ACK;
	}else{
		/* error port */
	}
}

/*!
    \brief      nmi initialize
    \param[in]  trigg_mode: NMI_TRG_LEVEL_H,NMI_TRG_LEVEL_L,NMI_TRG_RISE,NMI_TRG_FALL
    \param[in]  state: ENABLE or DISABLE interrupt
    \param[out] none
    \retval     none
*/
void nmi_init(uint8_t trigg_mode,FunctionalState state)
{
	clr_nmi_interrupt_flag();
	NMISC = (trigg_mode | (uint8_t)NMISC_PE);
	if(state == ENABLE){
		NMISC |= ((uint32_t)NMISC_IE & 0x000000FFUL);
	}
}

/*!
    \brief      clr nmi interrupt flag
    \param[in]  gpio_periph: GPIOx(x = A,B,D) 
    \param[in]  pin: GPIO_PIN_x(x=0..7), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void clr_nmi_interrupt_flag(void)
{
	NMISC |= ((uint32_t)NMISC_ACK & 0x000000FFUL);
}
