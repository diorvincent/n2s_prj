/*!
    \file  BF7006BMxx.h
    \brief definitions for the BF7006BMxx
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx.h initial version
    2022-09-01, V1.0.1, add function: Reset_system(), Set_int_priority(), Int_cmd()
*/

#ifndef BF7006BMxx_H
#define BF7006BMxx_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#define false                   FALSE
#define true                    TRUE

typedef enum {RESET = 0U, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0U, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0U, SUCCESS = !ERROR} ErrorStatus;

#define NULL                    ((void *)0)
    
typedef unsigned char           UINT8;              /* unsigned 8 bit definition    */
typedef unsigned short          UINT16;             /* unsigned 16 bit definition   */
typedef unsigned int            UINT32;             /* unsigned 32 bit definition   */
typedef signed char             INT8;               /* signed 8 bit definition      */
typedef short                   INT16;              /* signed 16 bit definition     */
typedef signed int              INT32;              /* signed 32 bit definition     */
typedef void(*pt2Func)(void);                       /* Pointer to Functions, void argument              */
typedef void(*pt2FuncU8)(UINT8);                    /* Pointer to Functions, UINT8 argument             */
typedef void(*pt2FuncU32)(UINT32);                  /* Pointer to Functions, UINT32 argument            */
typedef void(*pt2FuncU32U8)(UINT32,UINT8);          /* Pointer to Functions, UINT32 and UINT8 argument  */
    
/* bit operations */
#define REG32(addr)             (*((volatile uint32_t *)((uint32_t)(addr))))
#define REG16(addr)             (*((volatile uint16_t *)((uint32_t)(addr))))
#define REG8(addr)              (*((volatile uint8_t *)((uint32_t)(addr))))
#define BIT(x)                  ((uint32_t)(0x01UL<<((uint8_t)(x))))
//#define BIT(x)                  ((uint8_t)(((uint8_t)0x01)<<((uint32_t)x)))

//#define    BIT(0)               ((uint8_t)((uint8_t)0x01<<(x)))
#define BITS(start, end)                ((uint32_t)((0xFFFFFFFFUL << ((uint8_t)(start))) & (0xFFFFFFFFUL >> (31U - ((uint8_t)(end)))))) 
#define GET_BITS(regval, start, end)    (((regval) & BITS((start),(end))) >> (start))

/* -------------------------  Interrupt Number Definition  ------------------------ */
typedef enum IRQn
{
/* -------------------  Cortex-M0 Processor Exceptions Numbers  ------------------- */
  NonMaskableInt_IRQn           = -14,      /*!<  2 Non Maskable Interrupt          */
  HardFault_IRQn                = -13,      /*!<  3 HardFault Interrupt             */
  SVCall_IRQn                   =  -5,      /*!< 11 SV Call Interrupt               */
  PendSV_IRQn                   =  -2,      /*!< 14 Pend SV Interrupt               */
  SysTick_IRQn                  =  -1,      /*!< 15 System Tick Interrupt           */

/* ----------------------  ARMCM0 Specific Interrupt Numbers  --------------------- */
  RESERVED0                     =   0,      /*!<                                    */
  SYS_IRQn                      =   1,      /*!< Flash ECC Error Interrupt          */
  RESERVED1                     =   2,      /*!<                                    */
  RESERVED2                     =   3,      /*!<                                    */
  LVDT_IRQn                     =   4,      /*!< LVDT Interrupt                     */
  PWM_CH0_IRQn                  =   5,      /*!< PWM channel 0 Interrupt            */
  PWM_CH1_IRQn                  =   6,      /*!< PWM channel 1 Interrupt            */
  PWM_CH2_IRQn                  =   7,      /*!< PWM channel 2 Interrupt            */
  PWM_CH3_IRQn                  =   8,      /*!< PWM channel 3 Interrupt            */
  PWM_CH4_IRQn                  =   9,      /*!< PWM channel 4 Interrupt            */
  PWM_CH5_IRQn                  =  10,      /*!< PWM channel 5 Interrupt            */
  PWM_TOF_IRQN                  =  11,      /*!< PWM overflow Interrupt             */
  RESERVED4                     =  12,      /*!<                                    */
  RESERVED5                     =  13,      /*!<                                    */
  RESERVED6                     =  14,      /*!<                                    */
  RESERVED7                     =  15,      /*!<                                    */
  SCI0_ERR_IRQn                 =  16,      /*!< SCI0 ERR Interrupt                 */
  SCI0_RX_IRQn                  =  17,      /*!< SCI0 RX Interrupt                  */
  SCI0_TX_IRQn                  =  18,      /*!< SCI0 TX Interrupt                  */
  SCI1_ERR_IRQn                 =  19,      /*!< SCI1 ERR Interrupt                 */
  SCI1_RX_IRQn                  =  20,      /*!< SCI1 RX Interrupt                  */
  SCI1_TX_IRQn                  =  21,      /*!< SCI1 TX Interrupt                  */
  GPIO_IRQn                     =  22,      /*!< GPIO External Interrupt            */
  ADC_IRQn                      =  23,      /*!< ADC Interrupt                      */
  RESERVED8                     =  24,      /*!<                                    */
  RTC_IRQn                      =  25,      /*!< RTC Interrupt                      */
  CAN_WAKE_IRQn                 =  26,      /*!< CAN Interrupt                      */
  CAN_ERR_IRQn                  =  27,      /*!< CAN ERR Interrupt                  */
  CAN_RX_IRQn                   =  28,      /*!< CAN RX Interrupt                   */
  CAN_TX_IRQn                   =  29,      /*!< CAN TX Interrupt                   */
  TIMER0_IRQn                   =  30,      /*!< Timer0 Interrupt                   */
  TIMER1_IRQn                   =  31,      /*!< Timer1 Interrupt                   */
} IRQn_Type;

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* --------  Configuration of the Cortex-M4 Processor and Core Peripherals  ------- */
#define __CM0_REV                   0x0000      /*!< Core revision r0p0                              */
#define __MPU_PRESENT               0           /*!< MPU present or not                              */
#define __NVIC_PRIO_BITS            2           /*!< Number of Bits used for Priority Levels         */
#define __Vendor_SysTickConfig      0           /*!< Set to 1 if different SysTick Config is used    */

#include "core_cm0.h"                           /* Processor and core peripherals                    */
#include "system_ARMCM0.h"                      /* System Header                                     */

/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */

/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#elif defined ( __CSMC__ )      /* Cosmic */
/* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/**
  \brief   System Sleeping
  \details system step into sleeping mode
 */
__STATIC_INLINE void System_Sleeping(void)
{
    SCB->SCR &= (uint32_t)(~SCB_SCR_SLEEPDEEP_Msk);
    __WFI();
}

/**
  \brief   System Sleepdeep
  \details system step into sleepdeep mode
 */
__STATIC_INLINE void System_SleepDeep(void)
{
    SCB->SCR |= (uint32_t)SCB_SCR_SLEEPDEEP_Msk;
    __WFI();
}

/**
  \brief   Set Main Stack Pointer
  \details Assigns the given value to the Main Stack Pointer (MSP).
  \param [in]    topOfMainStack  Main Stack Pointer value to set
 */
__STATIC_INLINE void set_MSP(uint32_t topOfMainStack)
{
    __set_MSP(topOfMainStack);
}

/**
  \brief   Set Process Stack Pointer
  \details Assigns the given value to the Process Stack Pointer (PSP).
  \param [in]    topOfProcStack  Process Stack Pointer value to set
 */
__STATIC_INLINE void set_PSP(uint32_t topOfProcStack)
{
    __set_PSP(topOfProcStack);
}

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
__STATIC_INLINE void NOP(void)
{
    __NOP();
}

/**
  \brief   System reset
  \details Initiates a system reset request to reset the MCU.
 */
__STATIC_INLINE void Reset_system(void)
{
    NVIC_SystemReset();
}

/**
  \brief   Interrupt priority set
  \details Sets the priority of a device specific interrupt or a processor exception.
 */
__STATIC_INLINE void Set_int_priority(IRQn_Type IRQn, uint32_t priority)
{
    NVIC_SetPriority(IRQn, priority);
}

/**
  \brief   Interrupt enable or disable
  \details Enable or disable a device specific interrupt in the NVIC interrupt controller.
 */
__STATIC_INLINE void Int_cmd(IRQn_Type IRQn, FunctionalState en_state)
{
    if(en_state == ENABLE){
        NVIC_EnableIRQ(IRQn);
    }else{
        NVIC_DisableIRQ(IRQn);
    }
}

/**
  \brief   Enable Interrupt
  \details Enable Interrupt. This instruction can be used for code alignment purposes.
 */
__STATIC_INLINE void Enable_Irq(void)
{
    __enable_irq();
}

/**
  \brief   Disable Interrupt
  \details Disable interrupt. This instruction can be used for code alignment purposes.
 */
__STATIC_INLINE void Disable_Irq(void)
{
    __disable_irq();
}

/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */
/* Peripheral and SRAM base address */
#define FLASH_BASE              ((uint32_t)0x00000000)          ///< Flash base address
#define FLASH_NVR_BASE          ((uint32_t)0x00018000)          ///< Flash information block,read only
#define SRAM_BASE               ((uint32_t)0x20000000)          ///< SRAM base address
#define EEPROM_BASE             ((uint32_t)0x40000000)          ///< EEPROM base address
#define AHBPERIPH_BASE          ((uint32_t)0x50000000)          ///< AHB base address

/* Peripheral memory map */
#define EFLASH_CTRL_BASE        (AHBPERIPH_BASE + (uint32_t)0x00000)    ///< FLASH and EEPROM register base address
#define SYSCTRL_BASE            (AHBPERIPH_BASE + (uint32_t)0x10000)    ///< SYS control register base address
#define SCI_BASE                (AHBPERIPH_BASE + (uint32_t)0x40000)    ///< LIN0 register base address
#define CAN_BASE                (AHBPERIPH_BASE + (uint32_t)0x50000)    ///< CAN register base address
#define PWM_BASE                (AHBPERIPH_BASE + (uint32_t)0x60000)    ///< PWM register base address
#define RTC_BASE                (AHBPERIPH_BASE + (uint32_t)0x70000)    ///< RTC register base address
#define WDT_BASE                (AHBPERIPH_BASE + (uint32_t)0x80000)    ///< WDT register base address
#define ADC_BASE                (AHBPERIPH_BASE + (uint32_t)0x90000)    ///< ADC/ACMP register base address
#define GPIO_BASE               (AHBPERIPH_BASE + (uint32_t)0xA0000)    ///< GPIO register base address
#define TIMER_BASE              (AHBPERIPH_BASE + (uint32_t)0xB0000)    ///< Timer0/1 register base address

#define SCI0                    (SCI_BASE       + (uint32_t)0x0000)     ///< SCI0 register base address
#define SCI1                    (SCI_BASE       + (uint32_t)0x4000)     ///< SCI1 register base address

#define GPIOA                   (GPIO_BASE      + (uint32_t)0x0000)     ///< GPIOA register base address
#define GPIOB                   (GPIO_BASE      + (uint32_t)0x001C)     ///< GPIOB register base address
#define GPIOC                   (GPIO_BASE      + (uint32_t)0x0038)     ///< GPIOC register base address
#define GPIOD                   (GPIO_BASE      + (uint32_t)0x0048)     ///< GPIOD register base address
#define GPIOE                   (GPIO_BASE      + (uint32_t)0x0064)     ///< GPIOE register base address
#define GPIOF                   (GPIO_BASE      + (uint32_t)0x0074)     ///< GPIOF register base address
#define GPIOG                   (GPIO_BASE      + (uint32_t)0x0084)     ///< GPIOG register base address

#define TIMER0                  (TIMER_BASE     + (uint32_t)0x0000)     ///< Timer0 register base address
#define TIMER1                  (TIMER_BASE     + (uint32_t)0x4000)     ///< Timer1 register base address

/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#elif defined ( __CSMC__ )      /* Cosmic */
/* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

#ifdef __cplusplus
}
#endif

#endif  /* ARMCM0_H */
