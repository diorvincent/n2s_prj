/*!
    \file  BF7006BMxx_config.c
    \brief peripherals configuration for BF7006BMxx
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_config.c initial version

*/

#include "BF7006BMxx_config.h"

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define XTAL_NONE       0x0
#define XTAL_16MHz      0x1
#define XTAL_12MHz      0x2
#define XTAL_8MHz       0x3

#define SYSCLK_32M      (uint32_t)32000000
#define SYSCLK_16M      (uint32_t)16000000
#define SYSCLK_12M      (uint32_t)12000000
#define SYSCLK_8M       (uint32_t) 8000000
#define XTAL_16M        ((uint32_t)16000000)        /* Oscillator frequency 16M HZ   */
#define XTAL_12M        ((uint32_t)12000000)        /* Oscillator frequency 12M HZ   */
#define XTAL_8M         ((uint32_t) 8000000)        /* Oscillator frequency 8M HZ    */

//  <h>System Resource
//    <o>System Clock Select
//      <0=>RC 1MHz -> PLL 32MHz
//      <1=>RC 1MHz -> PLL 16MHz
//      <2=>RC 1MHz -> PLL 8MHz
//      <3=>XTAL 8MHz -> PLL 32MHz
//      <4=>XTAL 8MHz -> PLL 16MHz
//      <5=>XTAL 8MHz -> PLL 8MHz
//      <6=>XTAL 12MHz -> PLL 32MHz
//      <7=>XTAL 12MHz -> PLL 16MHz
//      <8=>XTAL 12MHz -> PLL 8MHz
//      <9=>XTAL 16MHz -> PLL 32MHz
//      <10=>XTAL 16MHz -> PLL 16MHz
//      <11=>XTAL 16MHz -> PLL 8MHz
//      <12=>XTAL 16MHz -> 16MHz
//      <13=>XTAL 12MHz -> 12MHz
//      <14=>XTAL 8MHz -> 8MHz
//    <i>System clock source and frequency configuration
#define SysClkSel 9

#if SysClkSel == 0
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_RC1M
    #define SYSTEM_CLK_FREQ     SYS_CLK_32M
    #define XTAL_FREQ           XTAL_NONE
    #define SYSTEM_CLK          SYSCLK_32M
#elif SysClkSel == 1
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_RC1M
    #define SYSTEM_CLK_FREQ     SYS_CLK_16M
    #define XTAL_FREQ           XTAL_NONE
    #define SYSTEM_CLK          SYSCLK_16M
#elif SysClkSel == 2
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_RC1M
    #define SYSTEM_CLK_FREQ     SYS_CLK_8M
    #define XTAL_FREQ           XTAL_NONE
    #define SYSTEM_CLK          SYSCLK_8M
#elif SysClkSel == 3
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_8M
    #define SYSTEM_CLK_FREQ     SYS_CLK_32M
    #define XTAL_FREQ           XTAL_8MHz
    #define SYSTEM_CLK          SYSCLK_32M
#elif SysClkSel == 4
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_8M
    #define SYSTEM_CLK_FREQ     SYS_CLK_16M
    #define XTAL_FREQ           XTAL_8MHz
    #define SYSTEM_CLK          SYSCLK_16M
#elif SysClkSel == 5
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_8M
    #define SYSTEM_CLK_FREQ     SYS_CLK_8M
    #define XTAL_FREQ           XTAL_8MHz
    #define SYSTEM_CLK          SYSCLK_8M
#elif SysClkSel == 6
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_12M
    #define SYSTEM_CLK_FREQ     SYS_CLK_32M
    #define XTAL_FREQ           XTAL_12MHz
    #define SYSTEM_CLK          SYSCLK_32M
#elif SysClkSel == 7
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_12M
    #define SYSTEM_CLK_FREQ     SYS_CLK_16M
    #define XTAL_FREQ           XTAL_12MHz
    #define SYSTEM_CLK          SYSCLK_16M
#elif SysClkSel == 8
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_12M
    #define SYSTEM_CLK_FREQ     SYS_CLK_8M
    #define XTAL_FREQ           XTAL_12MHz
    #define SYSTEM_CLK          SYSCLK_8M
#elif SysClkSel == 9
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_16M
    #define SYSTEM_CLK_FREQ     SYS_CLK_32M
    #define XTAL_FREQ           XTAL_16MHz
    #define SYSTEM_CLK          SYSCLK_32M
#elif SysClkSel == 10
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_16M
    #define SYSTEM_CLK_FREQ     SYS_CLK_16M
    #define XTAL_FREQ           XTAL_16MHz
    #define SYSTEM_CLK          SYSCLK_16M
#elif SysClkSel == 11
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_16M
    #define SYSTEM_CLK_FREQ     SYS_CLK_8M
    #define XTAL_FREQ           XTAL_16MHz
    #define SYSTEM_CLK          SYSCLK_8M
#elif SysClkSel == 12
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_16M
    #define SYSTEM_CLK_FREQ     SYS_CLK_XTAL
    #define XTAL_FREQ           XTAL_16MHz
    #define SYSTEM_CLK          SYSCLK_16M
#elif SysClkSel == 13
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_12M
    #define SYSTEM_CLK_FREQ     SYS_CLK_XTAL
    #define XTAL_FREQ           XTAL_12MHz
    #define SYSTEM_CLK          SYSCLK_12M
#elif SysClkSel == 14
    #define PLL_SOURCE_SEL      SYS_PLL_SEL_XTAL_8M
    #define SYSTEM_CLK_FREQ     SYS_CLK_XTAL
    #define XTAL_FREQ           XTAL_8MHz
    #define SYSTEM_CLK          SYSCLK_8M
#endif

void system_config(void)
{
//    <o>System interrupt vector offset
    #define SYSTEM_INTERRUPT_VECTOR_OFFSET 	0x00005000UL 		//0x00006000UL
	  //#define SYSTEM_INTERRUPT_VECTOR_OFFSET 0x00000000UL

    /* system interrupt vector offset set */
    system_intvector_offset(SYSTEM_INTERRUPT_VECTOR_OFFSET);

    system_clk_sel(PLL_SOURCE_SEL,SYSTEM_CLK_FREQ,XTAL_FREQ);

//    <h> LVDT
//      <q0> LVDT enable
//      <i> Low voltage detect enable
//      <o1> LVDT gear
//        <0=> 3.5V
//        <1=> 4.0V
//        <2=> 4.5V
//      <i> LVDT gear select
//      <q2> LVDT interrupt enable
//      <i> LVDT interrupt enable
//    </h>
#define LVDT_ENABLE 1
#define LVDT_GEAR 0
#define LVDT_INT_ENABLE 1
#if LVDT_ENABLE == 1
    #define LVDT_ENABLE_OPTION ENABLE
#else
    #define LVDT_ENABLE_OPTION DISABLE
#endif
#if LVDT_INT_ENABLE == 1
    #define LVDT_INT_ENABLE_OPTION ENABLE
#else
    #define LVDT_INT_ENABLE_OPTION DISABLE
#endif
    lvdt_init(LVDT_ENABLE_OPTION,LVDT_GEAR,LVDT_INT_ENABLE_OPTION);

//    <q> RESET filter enable
//    <i> RESET pin filter enable
#define RESET_FILTER_ENABLE 1
#if RESET_FILTER_ENABLE == 1
    #define RESET_FILTER_OPTION ENABLE
#else
    #define RESET_FILTER_OPTION DISABLE
#endif
    reset_filter(RESET_FILTER_OPTION);

//    <o> FLASH protect size
//      <0x0=> No protection
//      <0x1=> 2k Bytes
//      <0x2=> 4k Bytes
//      <0x3=> 6k Bytes
//      <0x4=> 8k Bytes
//      <0x5=> 10k Bytes
//      <0x6=> 12k Bytes
//      <0x7=> 14k Bytes
//      <0x8=> 16k Bytes
//      <0x9=> 18k Bytes
//      <0xA=> 20k Bytes
//      <0xB=> 22k Bytes
//      <0xC=> 24k Bytes
//      <0xD=> 26k Bytes
//      <0xE=> 28k Bytes
//      <0xF=> 30k Bytes
//      <0x10=> 32k Bytes
//      <0x11=> 34k Bytes
//      <0x12=> 36k Bytes
//      <0x13=> 38k Bytes
//      <0x14=> 40k Bytes
//      <0x15=> 42k Bytes
//      <0x16=> 44k Bytes
//      <0x17=> 46k Bytes
//      <0x18=> 48k Bytes
//      <0x19=> 50k Bytes
//      <0x1A=> 52k Bytes
//      <0x1B=> 54k Bytes
//      <0x1C=> 56k Bytes
//      <0x1D=> 58k Bytes
//      <0x1E=> 60k Bytes
//      <0x1F=> 62k Bytes
//      <0x20=> 64k Bytes
//      <0x21=> 66k Bytes
//      <0x22=> 68k Bytes
//      <0x23=> 70k Bytes
//      <0x24=> 72k Bytes
//      <0x25=> 74k Bytes
//      <0x26=> 76k Bytes
//      <0x27=> 78k Bytes
//      <0x28=> 80k Bytes
//      <0x29=> 82k Bytes
//      <0x2A=> 84k Bytes
//      <0x2B=> 86k Bytes
//      <0x2C=> 88k Bytes
//      <0x2D=> 90k Bytes
//      <0x2E=> 92k Bytes
//      <0x2F=> 94k Bytes
//      <0x30=> 96k Bytes
//    <i> FLASH protect size select
#ifdef BF7x06BMxx_EFLASH_DRIVER_PRESENT
    flash_protect(0);
#endif

//    <o> EEPROM protect size
//      <0x0=> No protection
//      <0x1=> 64 Bytes
//      <0x2=> 128 Bytes
//      <0x3=> 192 Bytes
//      <0x4=> 256 Bytes
//      <0x5=> 320 Bytes
//      <0x6=> 384 Bytes
//      <0x7=> 448 Bytes
//      <0x8=> 512 Bytes
//      <0x9=> 576 Bytes
//      <0xA=> 640 Bytes
//      <0xB=> 704 Bytes
//      <0xC=> 768 Bytes
//      <0xD=> 832 Bytes
//      <0xE=> 896 Bytes
//      <0xF=> 960 Bytes
//      <0x10=> 1024 Bytes
//      <0x11=> 1088 Bytes
//      <0x12=> 1152 Bytes
//      <0x13=> 1216 Bytes
//      <0x14=> 1280 Bytes
//      <0x15=> 1344 Bytes
//      <0x16=> 1408 Bytes
//      <0x17=> 1472 Bytes
//      <0x18=> 1536 Bytes
//      <0x19=> 1600 Bytes
//      <0x1A=> 1664 Bytes
//      <0x1B=> 1728 Bytes
//      <0x1C=> 1792 Bytes
//      <0x1D=> 1856 Bytes
//      <0x1E=> 1920 Bytes
//      <0x1F=> 1984 Bytes
//      <0x20=> 2048 Bytes
//    <i> EEPROM protect size select
//  </h>
#ifdef BF7x06BMxx_EFLASH_DRIVER_PRESENT
    eeprom_protect(0);
#endif
}

#ifdef BF7x06BMxx_SCI_DRIVER_PRESENT
ErrorStatus sci_config(void)
{
//  <e>SCI
#define SCI_CONFIG_EN 1
#if SCI_CONFIG_EN == 1
//    <e>SCI0
#define SCI0_EN 0
#if SCI0_EN == 1
    sci_parameter_struct sci0_parameter_init = 
    {
//      <o>Baudrate
//        <4800=>4800
//        <9600=>9600
//        <19200=>19200
//        <38400=>38400
//        <57600=>57600
//        <115200=>115200
//      <i>SCI baudrate config
        .baud_rate = 19200,

//      <o>Work mode
//        <0x80=>Cycle mode
//        <0xA0=>Single mode
//        <0x00=>Normal mode
//      <i>SCI work mode select
        .work_mode = 0,

//      <o>Stop bit
//        <0x0=>1 bit
//        <0x40=>2 bits
//      <i>SCI stop bit width
        .stop_bit_width = 0,

//      <o>Data bit
//        <0x0=>8 bits
//        <0x10=>9 bits
//      <i>SCI data bit width select
        .data_bit_width = 0,

//      <q0.1>Parity enable
//      <i>SCI parity enable
        .parity_en = 0,

//      <o>Parity select
//        <0x1=>Odd
//        <0x0=>Even
//      <i>SCI parity type select
        .parity_sel = 1,

//      <o>Break tx size
//        <0x4=>13 bits
//        <0x0=>10 bits
//      <i>SCI stop bit width select
        .break_tx_size = 0x4,

//      <q0.1>Break check enable
//      <i>SCI break check enable
        .break_check_en = 0x2,

//      <q0.5>Baud rate auto match enable
//      <i>SCI baud rate auto match
        .rate_automatch_en = 0x00,

//      <q0.3>Tx enable
//      <i>SCI tx enable
        .tx_en = 0x8,

//      <q0.2>Rx enable
//      <i>SCI rx enable
        .rx_en = 0x4,

//      <o>Idle select
//        <0x0=>Start bit
//        <0x4=>Stop bit
//      <i>SCI idle select
        .idle_sel = 0x4,

//      <o>Wake up select
//        <0x8=>Addrrece
//        <0x0=>Idle
//      <i>SCI wake up select
        .wake_sel = 0x8,

//      <q0.4>Tx data inversion enable
//      <i>SCI tx data inversion enable
        .tx_inversion_en = 0x00,

//      <q0.3>Rwu idle select set
//      <i>SCI rwu idle select set
        .rwu_idlesel = 0x0,

//      <h>SCI Interrupt Enable
//        <q0.15>Break check interrupt
//        <q0.14>Rx edge active interrupt
//        <q0.7>Tx buffer empty interrupt
//        <q0.6>Tx complete interrupt
//        <q0.5>Rx receive full interrupt
//        <q0.4>Idle line interrupt
//        <q0.3>Rx overflow interrupt
//        <q0.2>Noise error interrupt
//        <q0.1>Frame error interrupt
//        <q0.0>Parity error interrupt
//      </h>
        .int_enable = 0x0000,

//      <h>SCI NVIC Enable
//        <q0.2>Rx
//        <q0.1>Tx
//        <q0.0>Err
//      </h>
//    </e>
        .nvic_enable = 0x0
    };

    (void)sci_init(SCI0,sci0_parameter_init);       //sci0 init
#endif

//    <e0>SCI1
#define SCI1_EN 0
#if SCI1_EN == 1

//      <o>Port select
//        <0x0=>PF0  PF1
//        <0x1=>PE2  PE3
//        <0x2=>PE6  PE7
//      <i>SCI1 output port select
    sci1_port_sel(0x1);

    sci_parameter_struct sci1_parameter_init = 
    {
//      <o>Baudrate
//        <4800=>4800
//        <9600=>9600
//        <19200=>19200
//        <38400=>38400
//        <57600=>57600
//        <115200=>115200
//      <i>SCI baudrate config
        .baud_rate = 19200,

//      <o>Work mode
//        <0x80=>Cycle mode
//        <0x20=>Single mode
//        <0x00=>Normal mode
//      <i>SCI work mode select
        .work_mode = 0,

//      <o>Stop bit
//        <0x0=>1 bit
//        <0x40=>2 bits
//      <i>SCI stop bit width
        .stop_bit_width = 0,

//      <o>Data bit
//        <0x0=>8 bits
//        <0x10=>9 bits
//      <i>SCI data bit width select
        .data_bit_width = 0,

//      <q0.1>Parity enable
//      <i>SCI parity enable
        .parity_en = 0,

//      <o>Parity select
//        <0x1=>Odd
//        <0x0=>Even
//      <i>SCI parity type select
        .parity_sel = 1,

//      <o>Break tx size
//        <0x4=>13 bits
//        <0x0=>10 bits
//      <i>SCI stop bit width select
        .break_tx_size = 0x4,

//      <q0.1>Break check enable
//      <i>SCI break check enable
        .break_check_en = 0x0,

//      <q0.5>Baud rate auto match enable
//      <i>SCI baud rate auto match
        .rate_automatch_en = 0x00,

//      <q0.3>Tx enable
//      <i>SCI tx enable
        .tx_en = 0x8,

//      <q0.2>Rx enable
//      <i>SCI rx enable
        .rx_en = 0x4,

//      <o>Idle select
//        <0x0=>Start bit
//        <0x4=>Stop bit
//      <i>SCI idle select
        .idle_sel = 0x4,

//      <o>Wake up select
//        <0x8=>Addrrece
//        <0x0=>Idle
//      <i>SCI wake up select
        .wake_sel = 0x8,

//      <q0.4>Tx data inversion enable
//      <i>SCI tx data inversion enable
        .tx_inversion_en = 0x00,

//      <q0.3>Rwu idle select
//      <i>SCI rwu idle select
        .rwu_idlesel = 0x0,

//      <h>SCI Interrupt Enable
//        <q0.15>Break check 
//        <q0.14>Rx edge
//        <q0.7>Tx empty
//        <q0.6>Tx comp
//        <q0.5>Rx full
//        <q0.4>Idle
//        <q0.3>Rx overflow
//        <q0.2>Noise err
//        <q0.1>Frame err
//        <q0.0>Parity err
//      </h>
        .int_enable = 0x0020,

//      <h>SCI NVIC Enable
//        <q0.2>Rx
//        <q0.1>Tx
//        <q0.0>Err
//      </h>
//    </e>
//  </e>
        .nvic_enable = 0x4
    };
    (void)sci_init(SCI1,sci1_parameter_init);       //sci1 init
#endif
#endif
    return SUCCESS;
}
#endif

#ifdef BF7x06BMxx_CAN_DRIVER_PRESENT
ErrorStatus can_config(void)
{

    ErrorStatus ret_val = SUCCESS;

//  <e>CAN
#define CAN_CONFIG_EN 1
#if CAN_CONFIG_EN == 1
//    <o>CAN source clock select
//      <0x0=>XTAL
//      <0x1=>PLL
    can_clock_sel(0x0);

    can_parameter_struct can_parameter_init = 
    {
//    <o>Work mode select
//      <0x0=>Normal
//      <0x1=>Listen only
//      <0x2=>Self test
//      <0x3=>Self receive
//    <i>CAN work mode select
        .working_mode = (can_work_mode_enum)0,

//    <o>Synchronlzation jump width
//      <0x0=>0
//      <0x40=>1
//      <0x80=>2
//      <0xC0=>3
//    <i>Synchronlzation jump width
        .resync_jump_width = 0x00,

//    <o>CAN module clock select
//      <0x0=>32MHz
//      <0x1=>16MHz
//      <0x2=>8MHz
//    <i>CAN module clock select
        .can_clk = (can_clk_enum)1,

//    <o>CAN baud rate
//      <0x0=>50K
//      <0x1=>100K
//      <0x2=>125K
//      <0x3=>200K
//      <0x4=>250K
//      <0x5=>400K
//      <0x6=>500K
//      <0x7=>800K
//      <0x8=>1M
//    <i>CAN baud rate config
        .can_baud = (can_baud_enum)0x6,

//    <o>Sampling times
//      <0x0=>1 time
//      <0x80=>3 time
//     <i>Sampling times
        .sampling_times = 0x80,

//    <o>Error alarm count <0x0-0xFF:0x1><#/0x1>
//    <i>Error alarm count (8 bits)
        .error_alarm_count = 100,

//    <h>Interrupt Enable
//      <q0.7>Bus error interrupt enable
//      <q0.6>Arbitration lost interrupt enable
//      <q0.5>Error passive interrupt enable
//      <q0.4>Wake up interrupt enable
//      <q0.3>Data overflow interrupt enable
//      <q0.2>Error interrupt enable
//      <q0.1>Tx interrupt enable
//      <q0.0>Rx interrupt enable
//    </h>
        .int_enable = 0x17,

//    <h>NVIC Enable
//      <q0.3>Wake up nvic interrupt enable
//      <q0.2>Error nvic interrupt enable
//      <q0.1>Rx nvic interrupt enable
//      <q0.0>Tx nvic interrupt enable
//    </h>
        .nvic_int_enable = 0xF
    };
//    <h>CAN filter config
    can_filter_parameter_struct can_filter_parameter = 
    {
//      <o>Filter mode
//        <0x0=>Double filter
//        <0x1=>Single filter
//      <i>CAN filter mode select
        //.filter_mode = (CAN_FILTER_MODE)0x1,
				.filter_mode = (CAN_FILTER_MODE)0x0,
//      <o>Frame format
//        <0x0=>Standard frame
//        <0x1=>Extended frame
//      <i>CAN filter frame format 
        .filter_frame = (CAN_FRAME_FORMAT)0x0,

//      <o>Frame type
//        <0x0=>Data frame
//        <0x1=>Remote frame
//      <i>Frame type
        .filter_RTR = (CAN_FRAME_TYPE)0x0,

//      <o>RTR mask
//        <0x0=>Disable
//        <0x1=>Enable
//      <i>RTR mask
        .filter_mask_RTR = (FunctionalState)0,

//      <h>Single filter config
//        <o>id <0x0-0x1FFFFFFF:0x1><#/0x1>
//        <i> Standard frame : lower 11 bits valid
//        <i> Extended frame : lower 29 bits valid
        .filter_single_id = 0x251,
        
//        <o>data 0 <0x0-0xFF:0x1><#/0x1>
//        <i> Standard frame : lower 8 bits valid
//        <i> Extended frame : invalid
        .filter_data0 = 0xff,
        
//        <o>data 1 <0x0-0xFF:0x1><#/0x1>
//        <i> Standard frame : lower 8 bits valid
//        <i> Extended frame : invalid
        .filter_data1 = 0xff,
        
//        <o>id mask <0x0-0x1FFFFFFF:0x1><#/0x1>
//        <i> Standard frame : lower 11 bits valid
//        <i> Extended frame : lower 29 bits valid
        .filter_mask_single_id  = 0xf800,
        
//        <o>data 0 mask <0x0-0xFF:0x1><#/0x1>
//        <i> Standard frame : lower 8 bits valid
//        <i> Extended frame : invalid
        .filter_mask_data0      = 0xff,
        
//        <o>data 1 mask <0x0-0xFF:0x1><#/0x1>
//        <i> Standard frame : lower 8 bits valid
//        <i> Extended frame : invalid
        .filter_mask_data1      = 0xff,
//      </h>

//      <h>Double filter config
//        <o>id 0 <0x0-0x1FFFFFFF:0x1><#/0x1>
//        <i> Standard frame: Bit 10 ~ 0 valid
//        <i> Extended frame: Bit 28 ~ 13 valid
        .filter_double_id0      = 0x251,
        
//        <o>id 1 <0x0-0xFFFFFFFF:0x1><#/0x1>
//        <i> Standard frame: Bit 10 ~ 0 valid
//        <i> Extended frame: Bit 28 ~ 13 valid
        .filter_double_id1      = 0x729,		//0x74D,
        
//        <o>std frame data 0 <0x0-0xFF:0x1><#/0x1>
//        <i> Standard frame: lower 8 bits valid
//        <i> Extended frame: invalid
        .filter_data0_std       = 0xff,
        
//        <o>id 0 mask<0x0-0xFFFF:0x1><#/0x1>
//        <i> Standard frame: lower 11 bits valid
//        <i> Extended frame: lower 16 bits valid
        .filter_mask_double_id0 = 0xf800,
        
        
//        <o>id 1 mask<0x0-0xFFFF:0x1><#/0x1>
//        <i> Standard frame: lower 11 bits valid
//        <i> Extended frame: lower 16 bits valid
        .filter_mask_double_id1 = 0xf800,
        
//        <o>std frame data 0 mask<0x0-0xFF:0x1><#/0x1>
//        <i> Standard frame: lower 8 bits valid
//        <i> Extended frame: invalid
        .filter_mask_data0_std  = 0xff
//      </h>
//    </h>
//  </e>
    };

    ret_val = can_init(can_parameter_init,can_filter_parameter);
#endif
    return ret_val;
}
#endif

#ifdef BF7x06BMxx_ADC_DRIVER_PRESENT
ErrorStatus adc_config(void)
{
//  <e> ADC
#define ADC_CONFIG_EN 1
#if ADC_CONFIG_EN == 1
    adc_parameter_struct adc_init_para = 
    {
//    <o>Clock divide parameter
//      <0x0=> SysClk / 1
//      <0x10=>SysClk / 2
//      <0x70=>SysClk / 3
//      <0x20=>SysClk / 4
//      <0x30=>SysClk / 6
//      <0x40=>SysClk / 8
//      <0x50=>SysClk / 10
//      <0x60=>SysClk / 12
//    <i>ADC clock divide parameter
        .adc_clk = 0x00,

//    <o>Data width
//      <0x0=>8 bits
//      <0x1=>12 bits
//    <i>adc data width
        .data_width = 0x1,

//    <o>Sample clock number<0x0-0x3FF:0x1><#/0x1>
        .sample_clk_num = 100,

//    <h>Channel enable
//      <q0.23>CH 23
//      <q0.22>CH 22
//      <q0.21>CH 21
//      <q0.20>CH 20
//      <q0.19>CH 19
//      <q0.18>CH 18
//      <q0.17>CH 17
//      <q0.16>CH 16
//      <q0.15>CH 15
//      <q0.14>CH 14
//      <q0.13>CH 13
//      <q0.12>CH 12
//      <q0.11>CH 11
//      <q0.10>CH 10
//      <q0.9>CH 9
//      <q0.8>CH 8
//      <q0.7>CH 7
//      <q0.6>CH 6
//      <q0.5>CH 5
//      <q0.4>CH 4
//      <q0.3>CH 3
//      <q0.2>CH 2
//      <q0.1>CH 1
//      <q0.0>CH 0
//    </h>
        .channel_en = 0x000000U,

//    <q0.0>Continuous convert enable
//    <i>Continuous convert enable
        .adco_en = (FunctionalState)0,

//    <q0.0>Interrupt enable
//    <i>Interrupt enable
        .int_en = (FunctionalState)1,

//    <o>Trigger Mode
//      <0x0=>software trigger
//      <0x1=>hardware trigger
//    <i>adc trigger mode select
        .trigger.trigger_mode = 0x0,

//    <o>Trigger source
//      <0x1=>NMI
//      <0x2=>PWM
//      <0x3=>RTC
//    <i>adc hardware trigger source
        .trigger.trigger_source = 0x3,

//    <o>PWM trigger delay<0x0-0xFFFF:0x1><#/0x1>
        .trigger.pwm_trigger_delay = 100,

//    <h>Compare config
//      <q0.0>Compare enable
//      <i>Compare enable
        .compare.compare_en = (FunctionalState)0x0,

//      <o>Compare condition
//        <0x0=>less
//        <0x1=>larger
//        <0x2=>between
//      <i>ADC compare condition select
        .compare.compare_condition = 2,

//      <o>Lower limit<0x0-0xFFF:0x1><#/0x1>
        .compare.lower_limit_val = 100,
        
//      <o>Higher limit<0x0-0xFFF:0x1><#/0x1>
        .compare.higher_limit_val = 3500
//    </h>
//  </e>
    };

    adc_init(adc_init_para);
#endif
    return SUCCESS;
}
#endif

#ifdef BF7x06BMxx_PWM_DRIVER_PRESENT
ErrorStatus pwm_config(void)
{
//  <e>PWM
#define PWM_CONFIG_EN 1
#if PWM_CONFIG_EN == 1
//    <e0>Channel 0
#define PWM_CH0_EN 1
#if PWM_CH0_EN == 1
//      <q0.6>Interrupt enable
//      <i>Channel interrupt enable

//      <o0.2..5>Mode select
//        <0x1=>Input Capture Mode  --  Rising Edge
//        <0x2=>Input Capture Mode  --  Falling Edge
//        <0x3=>Input Capture Mode  --  Rising / Falling Edge
//        <0x5=>Output Compare Mode  --  Toggle
//        <0x6=>Output Compare Mode  --  Clear
//        <0x7=>Output Compare Mode  --  Set
//        <0xA=>Edge / Center Aligned Mode  --  High-true pulse
//        <0x9=>Edge / Center Aligned Mode  --  Low-true pulse
//      <i>Channel mode select

//      <o1>Channel value<0x0-0xFFFF:0x1><#/0x1>
//    </e>
    pwm_ch0_init(0x28,0);
#endif

//    <e0>Channel 1
#define PWM_CH1_EN 1
#if PWM_CH1_EN == 1
//      <q0.6>Interrupt enable
//      <i>Channel interrupt enable

//      <o0.2..5>Mode select
//        <0x1=>Input Capture Mode  --  Rising Edge
//        <0x2=>Input Capture Mode  --  Falling Edge
//        <0x3=>Input Capture Mode  --  Rising / Falling Edge
//        <0x5=>Output Compare Mode  --  Toggle
//        <0x6=>Output Compare Mode  --  Clear
//        <0x7=>Output Compare Mode  --  Set
//        <0xA=>Edge / Center Aligned Mode  --  High-true pulse
//        <0x9=>Edge / Center Aligned Mode  --  Low-true pulse
//      <i>Channel mode select

//      <o1>Channel value<0x0-0xFFFF:0x1><#/0x1>
//    </e>
    pwm_ch1_init(0x24,51000);
#endif

//    <e0>Channel 2
#define PWM_CH2_EN 0
#if PWM_CH2_EN == 1
//      <q0.6>Interrupt enable
//      <i>Channel interrupt enable

//      <o0.2..5>Mode select
//        <0x1=>Input Capture Mode  --  Rising Edge
//        <0x2=>Input Capture Mode  --  Falling Edge
//        <0x3=>Input Capture Mode  --  Rising / Falling Edge
//        <0x5=>Output Compare Mode  --  Toggle
//        <0x6=>Output Compare Mode  --  Clear
//        <0x7=>Output Compare Mode  --  Set
//        <0xA=>Edge / Center Aligned Mode  --  High-true pulse
//        <0x9=>Edge / Center Aligned Mode  --  Low-true pulse
//      <i>Channel mode select

//      <o1>Channel value<0x0-0xFFFF:0x1><#/0x1>
//    </e>
    pwm_ch2_init(0x28,0);
#endif

//    <e0>Channel 3
#define PWM_CH3_EN 0
#if PWM_CH3_EN == 1
//      <q0.6>Interrupt enable
//      <i>Channel interrupt enable

//      <o0.2..5>Mode select
//        <0x1=>Input Capture Mode  --  Rising Edge
//        <0x2=>Input Capture Mode  --  Falling Edge
//        <0x3=>Input Capture Mode  --  Rising / Falling Edge
//        <0x5=>Output Compare Mode  --  Toggle
//        <0x6=>Output Compare Mode  --  Clear
//        <0x7=>Output Compare Mode  --  Set
//        <0xA=>Edge / Center Aligned Mode  --  High-true pulse
//        <0x9=>Edge / Center Aligned Mode  --  Low-true pulse
//      <i>Channel mode select

//      <o1>Channel value<0x0-0xFFFF:0x1><#/0x1>
//    </e>
    pwm_ch3_init(0x28,0);
#endif

//    <e0>Channel 4
#define PWM_CH4_EN 0
#if PWM_CH4_EN == 1
//      <q0.6>Interrupt enable
//      <i>Channel interrupt enable

//      <o0.2..5>Mode select
//        <0x1=>Input Capture Mode  --  Rising Edge
//        <0x2=>Input Capture Mode  --  Falling Edge
//        <0x3=>Input Capture Mode  --  Rising / Falling Edge
//        <0x5=>Output Compare Mode  --  Toggle
//        <0x6=>Output Compare Mode  --  Clear
//        <0x7=>Output Compare Mode  --  Set
//        <0xA=>Edge / Center Aligned Mode  --  High-true pulse
//        <0x9=>Edge / Center Aligned Mode  --  Low-true pulse
//      <i>Channel mode select

//      <o1>Channel value<0x0-0xFFFF:0x1><#/0x1>
//    </e>
    pwm_ch4_init(0x28,0x0);
#endif

//    <e0>Channel 5
#define PWM_CH5_EN 0
#if PWM_CH5_EN == 1
//      <q0.6>Interrupt enable
//      <i>Channel interrupt enable

//      <o0.2..5>Mode select
//        <0x1=>Input Capture Mode  --  Rising Edge
//        <0x2=>Input Capture Mode  --  Falling Edge
//        <0x3=>Input Capture Mode  --  Rising / Falling Edge
//        <0x5=>Output Compare Mode  --  Toggle
//        <0x6=>Output Compare Mode  --  Clear
//        <0x7=>Output Compare Mode  --  Set
//        <0xA=>Edge / Center Aligned Mode  --  High-true pulse
//        <0x9=>Edge / Center Aligned Mode  --  Low-true pulse
//      <i>Channel mode select

//      <o1>Channel value<0x0-0xFFFF:0x1><#/0x1>
//    </e>
    pwm_ch5_init(0x28,0x0);
#endif
//    <h> PWM counter
//      <o0.3..4>Clock select
//        <0x0=>Off
//        <0x1=>System Clock
//        <0x2=>System Clock
//        <0x3=>External input clock
//      <i>PWM clock select

//      <o0.0..2>Clock divide parameter
//        <0x0=> / 1
//        <0x1=> / 2
//        <0x2=> / 4
//        <0x3=> / 8
//        <0x4=> / 16
//        <0x5=> / 32
//        <0x6=> / 64
//        <0x7=> / 128
//      <i>PWM clock divide parameter

//      <o0.5>Count direction
//        <0x0=>Up Counting
//        <0x1=>Up-Down Counting
//      <i>PWM count direction select

//      <q0.6>Interrupt enable
//      <i>PWM overflow interrupt enable

//      <o1>Modulo<0x0-0xFFFF:0x1><#/0x1>
//    </h>
//  </e>
    pwm_init(0x0E,50000);  //选择系统时钟计数32MHZ，分频32，实际频率1MHZ，周期40ms，25hz
#endif
    return SUCCESS;
}
#endif

#ifdef BF7x06BMxx_WDT_DRIVER_PRESENT
ErrorStatus wdt_cfg(void)
{
//  <e>WDT
#define WDT_CONFIG_EN 1
#if WDT_CONFIG_EN == 1
//    <o2.8>Clock select
//      <0x0=>1KHz internal clock
//      <0x1=>32KHz internal clock
//    <i>WDT clock select

//    <q2.15>Window mode enable
//    <i>WDT window mode enable

//    <q2.7>WDT enable
//    <i>WDT enable

//    <q2.5>Update enable
//    <i>WDT update enable

//    <q2.1>Enable in sleep mode
//    <i>WDT enable in sleep mode

//    <q2.0>Enable in deep sleep mode
//    <i>WDT enable in deep sleep mode

//    <o1>Overflow count<0x0-0xFFFF:0x1><#/0x1>

//    <o0>Window mode overflow count<0x0-0xFFFF:0x1><#/0x1>
//  </e>
    wdt_overflow_count_win(0xC000);

    wdt_overflow_count(0xFFFF);

    wdt_config(0x120);
#endif
    return SUCCESS;
}
#endif

#ifdef BF7x06BMxx_TIMER_DRIVER_PRESENT
ErrorStatus timer_config(void)
{
//  <e>Timer
#define TIMER_CONFIG_EN 0
#if TIMER_CONFIG_EN == 1
//    <e0>Timer 0
#define TIMER0_EN 0
#if TIMER0_EN == 1
//      <o0.2>Clock select
//        <0x0=>System clock
//        <0x1=>RC32KHz
//      <i>TIMER clock select

//      <o0.3..4>Clock divide
//        <0x0=>System clock / 1
//        <0x1=>System clock / 2
//        <0x2=>System clock / 4
//        <0x3=>System clock / 8
//      <i>TIMER clock divide parameter (only when using system clock)

//      <o0.1>Auto reload mode select
//        <0x0=>Manual reload
//        <0x1=>Auto reload
//      <i>Timer auto reload mode select

//      <q0.5>Interrupt enable
//      <i>TIMER interrupt enable

//      <q0.0>Enable
//      <i>TIMER enable

//      <o1>Modulo<0x0-0xFFFF:0x1><#/0x1>
//    </e>
    timer_init(TIMER0,0x02,0x0);
#endif

//    <e>Timer 1
#define TIMER1_EN 0
#if TIMER1_EN == 1
//      <o0.2>Clock select
//        <0x0=>System clock
//        <0x1=>RC32KHz
//      <i>TIMER clock select

//      <o0.3..4>Clock divide
//        <0x0=>System clock / 1
//        <0x1=>System clock / 2
//        <0x2=>System clock / 4
//        <0x3=>System clock / 8
//      <i>TIMER clock divide parameter (only when using system clock)

//      <o0.1>Auto reload mode select
//        <0x0=>Manual reload
//        <0x1=>Auto reload
//      <i>Timer auto reload mode select

//      <q0.5>Interrupt enable
//      <i>TIMER interrupt enable

//      <q0.0>Enable
//      <i>TIMER enable

//      <o1>Modulo<0x0-0xFFFF:0x1><#/0x1>
//    </e>
//  </e>
    timer_init(TIMER1,0x02,0x0);
#endif
#endif
    return SUCCESS;
}
#endif

#ifdef BF7x06BMxx_RTC_DRIVER_PRESENT
ErrorStatus rtc_config(void)
{
    ErrorStatus ret_val = SUCCESS;
//  <e>RTC
#define RTC_CONFIG_EN 1
#if RTC_CONFIG_EN == 1
//    <o0.5..6>Clock select
//      <0x0=>1KHz
//      <0x1=>XTAL / 32
//      <0x2=>Internal 32KHz clock
//      <0x3=>Internal 32KHz clock
//    <i>RTC clock select

//    <q0.4>Interrupt enable
//    <i>TIMER interrupt enable

//    <q0.9>Enable
//    <i>TIMER enable

//    <o1>Modulo<0x0-0xFFFFFFFF:0x1><#/0x1>
//    <i>RTC mod should not be set less than 3
//  </e>
    //ret_val = rtc_init(0x250,0x07d00);
		ret_val = rtc_init(0x230,499);
#endif
    return ret_val;
}
#endif

#ifdef BF7x06BMxx_GPIO_DRIVER_PRESENT
ErrorStatus gpio_config(void)
{
#define ONE_BIT(x) (0x1 << x)

//  <e> GPIO
#define GPIO_CONFIG_EN 1
#if GPIO_CONFIG_EN == 1
//    <e0>NMI
#define NMI_EN 0
#if NMI_EN == 1
//      <o0>Trigger Mode
//        <0x00=>Falling edge
//        <0x20=>Rising edge
//        <0x21=>High level
//        <0x01=>Low level
//      <i>Configure NMI triggermode
//    </e>
    nmi_init(0x20,ENABLE);
#endif

//    <e0>PA
#define PA_EN 0
#if PA_EN == 1
//      <e16.7>PIN 7
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PA_7_INOUT_MODE 0

//        <q16.7>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PA_7_TRIGGER_MODE 2
//      </e>

//      <e14.6>PIN 6
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PA_6_INOUT_MODE 2

//        <q14.6>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PA_6_TRIGGER_MODE 2
//      </e>

//      <e12.5>PIN 5
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PA_5_INOUT_MODE 2

//        <q12.5>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PA_5_TRIGGER_MODE 2
//      </e>

//      <e10.4>PIN 4
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PA_4_INOUT_MODE 1

//        <q10.4>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PA_4_TRIGGER_MODE 2
//      </e>

//      <e8.3>PIN 3
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PA_3_INOUT_MODE 1

//        <q8.3>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PA_3_TRIGGER_MODE 2
//      </e>

//      <e6.2>PIN 2
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PA_2_INOUT_MODE 1

//        <q6.2>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PA_2_TRIGGER_MODE 2
//      </e>

//      <e4.1>PIN 1
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PA_1_INOUT_MODE 0

//        <q4.1>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PA_1_TRIGGER_MODE 2
//      </e>

//      <e2.0>PIN 0
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PA_0_INOUT_MODE 0

//        <q2.0>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PA_0_TRIGGER_MODE 2
//      </e>
//    </e>
#define PA_PIN 0xFF
#define PA_IE 0x00

// init PA group
#if PA_PIN & ONE_BIT(7)         //PIN7
    gpio_init(GPIOA,(GPIO_MODE)PA_7_INOUT_MODE,GPIO_PIN_7);
#endif
#if PA_PIN & ONE_BIT(6)         //PIN6
    gpio_init(GPIOA,(GPIO_MODE)PA_6_INOUT_MODE,GPIO_PIN_6);
#endif
#if PA_PIN & ONE_BIT(5)         //PIN5
    gpio_init(GPIOA,(GPIO_MODE)PA_5_INOUT_MODE,GPIO_PIN_5);
#endif
#if PA_PIN & ONE_BIT(4)         //PIN4
    gpio_init(GPIOA,(GPIO_MODE)PA_4_INOUT_MODE,GPIO_PIN_4);
#endif
#if PA_PIN & ONE_BIT(3)         //PIN3
    gpio_init(GPIOA,(GPIO_MODE)PA_3_INOUT_MODE,GPIO_PIN_3);
#endif
#if PA_PIN & ONE_BIT(2)         //PIN2
    gpio_init(GPIOA,(GPIO_MODE)PA_2_INOUT_MODE,GPIO_PIN_2);
#endif
#if PA_PIN & ONE_BIT(1)         //PIN1
    gpio_init(GPIOA,(GPIO_MODE)PA_1_INOUT_MODE,GPIO_PIN_1);
#endif
#if PA_PIN & ONE_BIT(0)         //PIN0
    gpio_init(GPIOA,(GPIO_MODE)PA_0_INOUT_MODE,GPIO_PIN_0);
#endif

// Interrupt enable
#if PA_IE & ONE_BIT(7)         //PIN7
    gpio_trigge_mode(GPIOA,(GPIO_TRG_MODE)PA_7_TRIGGER_MODE,GPIO_PIN_7);
    gpio_interrupt_set(GPIOA,GPIO_PIN_7,ENABLE);
#endif
#if PA_IE & ONE_BIT(6)         //PIN6
    gpio_trigge_mode(GPIOA,(GPIO_TRG_MODE)PA_6_TRIGGER_MODE,GPIO_PIN_6);
    gpio_interrupt_set(GPIOA,GPIO_PIN_6,ENABLE);
#endif
#if PA_IE & ONE_BIT(5)         //PIN5
    gpio_trigge_mode(GPIOA,(GPIO_TRG_MODE)PA_5_TRIGGER_MODE,GPIO_PIN_5);
    gpio_interrupt_set(GPIOA,GPIO_PIN_5,ENABLE);
#endif
#if PA_IE & ONE_BIT(4)         //PIN4
    gpio_trigge_mode(GPIOA,(GPIO_TRG_MODE)PA_4_TRIGGER_MODE,GPIO_PIN_4);
    gpio_interrupt_set(GPIOA,GPIO_PIN_4,ENABLE);
#endif
#if PA_IE & ONE_BIT(3)         //PIN3
    gpio_trigge_mode(GPIOA,(GPIO_TRG_MODE)PA_3_TRIGGER_MODE,GPIO_PIN_3);
    gpio_interrupt_set(GPIOA,GPIO_PIN_3,ENABLE);
#endif
#if PA_IE & ONE_BIT(2)         //PIN2
    gpio_trigge_mode(GPIOA,(GPIO_TRG_MODE)PA_2_TRIGGER_MODE,GPIO_PIN_2);
    gpio_interrupt_set(GPIOA,GPIO_PIN_2,ENABLE);
#endif
#if PA_IE & ONE_BIT(1)         //PIN1
    gpio_trigge_mode(GPIOA,(GPIO_TRG_MODE)PA_1_TRIGGER_MODE,GPIO_PIN_1);
    gpio_interrupt_set(GPIOA,GPIO_PIN_1,ENABLE);
#endif
#if PA_IE & ONE_BIT(0)         //PIN0
    gpio_trigge_mode(GPIOA,(GPIO_TRG_MODE)PA_0_TRIGGER_MODE,GPIO_PIN_0);
    gpio_interrupt_set(GPIOA,GPIO_PIN_0,ENABLE);
#endif
#endif  // #if PA_EN == 1


//    <e0>PB
#define PB_EN 1
#if PB_EN == 1
//      <e16.7>PIN 7
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PB_7_INOUT_MODE 0

//        <q16.7>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PB_7_TRIGGER_MODE 2
//      </e>

//      <e14.6>PIN 6
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PB_6_INOUT_MODE 0

//        <q14.6>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PB_6_TRIGGER_MODE 2
//      </e>

//      <e12.5>PIN 5
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PB_5_INOUT_MODE 1

//        <q12.5>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PB_5_TRIGGER_MODE 2
//      </e>

//      <e10.4>PIN 4
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PB_4_INOUT_MODE 1

//        <q10.4>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PB_4_TRIGGER_MODE 2
//      </e>

//      <e8.3>PIN 3
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PB_3_INOUT_MODE 1

//        <q8.3>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PB_3_TRIGGER_MODE 2
//      </e>

//      <e6.2>PIN 2
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PB_2_INOUT_MODE 0

//        <q6.2>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PB_2_TRIGGER_MODE 2
//      </e>

//      <e4.1>PIN 1
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PB_1_INOUT_MODE 0

//        <q4.1>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PB_1_TRIGGER_MODE 2
//      </e>

//      <e2.0>PIN 0
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PB_0_INOUT_MODE 0

//        <q2.0>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PB_0_TRIGGER_MODE 2
//      </e>
//    </e>
#define PB_PIN 0xff
#define PB_IE 0x00

// init PB group
#if PB_PIN & ONE_BIT(7)         //PIN7
    gpio_init(GPIOB,(GPIO_MODE)PB_7_INOUT_MODE,GPIO_PIN_7);
#endif
#if PB_PIN & ONE_BIT(6)         //PIN6
    gpio_init(GPIOB,(GPIO_MODE)PB_6_INOUT_MODE,GPIO_PIN_6);
#endif
#if PB_PIN & ONE_BIT(5)         //PIN5
    gpio_init(GPIOB,(GPIO_MODE)PB_5_INOUT_MODE,GPIO_PIN_5);
#endif
#if PB_PIN & ONE_BIT(4)         //PIN4
    gpio_init(GPIOB,(GPIO_MODE)PB_4_INOUT_MODE,GPIO_PIN_4);
#endif
#if PB_PIN & ONE_BIT(3)         //PIN3
    gpio_init(GPIOB,(GPIO_MODE)PB_3_INOUT_MODE,GPIO_PIN_3);
#endif
#if PB_PIN & ONE_BIT(2)         //PIN2
    gpio_init(GPIOB,(GPIO_MODE)PB_2_INOUT_MODE,GPIO_PIN_2);
#endif
#if PB_PIN & ONE_BIT(1)         //PIN1
    gpio_init(GPIOB,(GPIO_MODE)PB_1_INOUT_MODE,GPIO_PIN_1);
#endif
#if PB_PIN & ONE_BIT(0)         //PIN0
    gpio_init(GPIOB,(GPIO_MODE)PB_0_INOUT_MODE,GPIO_PIN_0);
#endif

// Interrupt enable
#if PB_IE & ONE_BIT(7)         //PIN7
    gpio_trigge_mode(GPIOB,(GPIO_TRG_MODE)PB_7_TRIGGER_MODE,GPIO_PIN_7);
    gpio_interrupt_set(GPIOB,GPIO_PIN_7,ENABLE);
#endif
#if PB_IE & ONE_BIT(6)         //PIN6
    gpio_trigge_mode(GPIOB,(GPIO_TRG_MODE)PB_6_TRIGGER_MODE,GPIO_PIN_6);
    gpio_interrupt_set(GPIOB,GPIO_PIN_6,ENABLE);
#endif
#if PB_IE & ONE_BIT(5)         //PIN5
    gpio_trigge_mode(GPIOB,(GPIO_TRG_MODE)PB_5_TRIGGER_MODE,GPIO_PIN_5);
    gpio_interrupt_set(GPIOB,GPIO_PIN_5,ENABLE);
#endif
#if PB_IE & ONE_BIT(4)         //PIN4
    gpio_trigge_mode(GPIOB,(GPIO_TRG_MODE)PB_4_TRIGGER_MODE,GPIO_PIN_4);
    gpio_interrupt_set(GPIOB,GPIO_PIN_4,ENABLE);
#endif
#if PB_IE & ONE_BIT(3)         //PIN3
    gpio_trigge_mode(GPIOB,(GPIO_TRG_MODE)PB_3_TRIGGER_MODE,GPIO_PIN_3);
    gpio_interrupt_set(GPIOB,GPIO_PIN_3,ENABLE);
#endif
#if PB_IE & ONE_BIT(2)         //PIN2
    gpio_trigge_mode(GPIOB,(GPIO_TRG_MODE)PB_2_TRIGGER_MODE,GPIO_PIN_2);
    gpio_interrupt_set(GPIOB,GPIO_PIN_2,ENABLE);
#endif
#if PB_IE & ONE_BIT(1)         //PIN1
    gpio_trigge_mode(GPIOB,(GPIO_TRG_MODE)PB_1_TRIGGER_MODE,GPIO_PIN_1);
    gpio_interrupt_set(GPIOB,GPIO_PIN_1,ENABLE);
#endif
#if PB_IE & ONE_BIT(0)         //PIN0
    gpio_trigge_mode(GPIOB,(GPIO_TRG_MODE)PB_0_TRIGGER_MODE,GPIO_PIN_0);
    gpio_interrupt_set(GPIOB,GPIO_PIN_0,ENABLE);
#endif
#endif  // #if PB_EN == 1


//    <e0>PC
#define PC_EN 0
#if PC_EN == 1
//      <e8.7>PIN 7
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PC_7_INOUT_MODE 2

//      <e7.6>PIN 6
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PC_6_INOUT_MODE 2

//      <e6.5>PIN 5
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PC_5_INOUT_MODE 2

//      <e5.4>PIN 4
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PC_4_INOUT_MODE 2

//      <e4.3>PIN 3
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PC_3_INOUT_MODE 2

//      <e3.2>PIN 2
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PC_2_INOUT_MODE 2


//      <e2.1>PIN 1
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PC_1_INOUT_MODE 2

//      <e1.0>PIN 0
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
//    </e>
#define PC_0_INOUT_MODE 2

#define PC_PIN 0x00

// init PC group
#if PC_PIN & ONE_BIT(7)         //PIN7
    gpio_init(GPIOC,(GPIO_MODE)PC_7_INOUT_MODE,GPIO_PIN_7);
#endif
#if PC_PIN & ONE_BIT(6)         //PIN6
    gpio_init(GPIOC,(GPIO_MODE)PC_6_INOUT_MODE,GPIO_PIN_6);
#endif
#if PC_PIN & ONE_BIT(5)         //PIN5
    gpio_init(GPIOC,(GPIO_MODE)PC_5_INOUT_MODE,GPIO_PIN_5);
#endif
#if PC_PIN & ONE_BIT(4)         //PIN4
    gpio_init(GPIOC,(GPIO_MODE)PC_4_INOUT_MODE,GPIO_PIN_4);
#endif
#if PC_PIN & ONE_BIT(3)         //PIN3
    gpio_init(GPIOC,(GPIO_MODE)PC_3_INOUT_MODE,GPIO_PIN_3);
#endif
#if PC_PIN & ONE_BIT(2)         //PIN2
    gpio_init(GPIOC,(GPIO_MODE)PC_2_INOUT_MODE,GPIO_PIN_2);
#endif
#if PC_PIN & ONE_BIT(1)         //PIN1
    gpio_init(GPIOC,(GPIO_MODE)PC_1_INOUT_MODE,GPIO_PIN_1);
#endif
#if PC_PIN & ONE_BIT(0)         //PIN0
    gpio_init(GPIOC,(GPIO_MODE)PC_0_INOUT_MODE,GPIO_PIN_0);
#endif
#endif  // #if PC_EN == 1


//    <e0>PD
#define PD_EN 0
#if PD_EN == 1
//      <e16.7>PIN 7
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PD_7_INOUT_MODE 2

//        <q16.7>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PD_7_TRIGGER_MODE 2
//      </e>

//      <e14.6>PIN 6
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PD_6_INOUT_MODE 2

//        <q14.6>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PD_6_TRIGGER_MODE 2
//      </e>

//      <e12.5>PIN 5
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PD_5_INOUT_MODE 2

//        <q12.5>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PD_5_TRIGGER_MODE 2
//      </e>

//      <e10.4>PIN 4
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PD_4_INOUT_MODE 2

//        <q10.4>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PD_4_TRIGGER_MODE 2
//      </e>

//      <e8.3>PIN 3
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PD_3_INOUT_MODE 2

//        <q8.3>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PD_3_TRIGGER_MODE 2
//      </e>

//      <e6.2>PIN 2
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PD_2_INOUT_MODE 2

//        <q6.2>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PD_2_TRIGGER_MODE 2
//      </e>

//      <e4.1>PIN 1
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PD_1_INOUT_MODE 2

//        <q4.1>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PD_1_TRIGGER_MODE 2
//      </e>

//      <e2.0>PIN 0
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
#define PD_0_INOUT_MODE 2

//        <q2.0>Interrup enable
//        <o>Trigger mode
//          <0x0=>High level
//          <0x1=>Low level
//          <0x2=>Rising edge
//          <0x3=>Falling edge
//        <i>Configure GPIO trigger mode
#define PD_0_TRIGGER_MODE 2
//      </e>
//    </e>
#define PD_PIN 0x00
#define PD_IE 0x00

// init PD group
#if PD_PIN & ONE_BIT(7)         //PIN7
    gpio_init(GPIOD,(GPIO_MODE)PD_7_INOUT_MODE,GPIO_PIN_7);
#endif
#if PD_PIN & ONE_BIT(6)         //PIN6
    gpio_init(GPIOD,(GPIO_MODE)PD_6_INOUT_MODE,GPIO_PIN_6);
#endif
#if PD_PIN & ONE_BIT(5)         //PIN5
    gpio_init(GPIOD,(GPIO_MODE)PD_5_INOUT_MODE,GPIO_PIN_5);
#endif
#if PD_PIN & ONE_BIT(4)         //PIN4
    gpio_init(GPIOD,(GPIO_MODE)PD_4_INOUT_MODE,GPIO_PIN_4);
#endif
#if PD_PIN & ONE_BIT(3)         //PIN3
    gpio_init(GPIOD,(GPIO_MODE)PD_3_INOUT_MODE,GPIO_PIN_3);
#endif
#if PD_PIN & ONE_BIT(2)         //PIN2
    gpio_init(GPIOD,(GPIO_MODE)PD_2_INOUT_MODE,GPIO_PIN_2);
#endif
#if PD_PIN & ONE_BIT(1)         //PIN1
    gpio_init(GPIOD,(GPIO_MODE)PD_1_INOUT_MODE,GPIO_PIN_1);
#endif
#if PD_PIN & ONE_BIT(0)         //PIN0
    gpio_init(GPIOD,(GPIO_MODE)PD_0_INOUT_MODE,GPIO_PIN_0);
#endif

// Interrupt enable
#if PD_IE & ONE_BIT(7)         //PIN7
    gpio_trigge_mode(GPIOD,(GPIO_TRG_MODE)PD_7_TRIGGER_MODE,GPIO_PIN_7);
    gpio_interrupt_set(GPIOD,GPIO_PIN_7,ENABLE);
#endif
#if PD_IE & ONE_BIT(6)         //PIN6
    gpio_trigge_mode(GPIOD,(GPIO_TRG_MODE)PD_6_TRIGGER_MODE,GPIO_PIN_6);
    gpio_interrupt_set(GPIOD,GPIO_PIN_6,ENABLE);
#endif
#if PD_IE & ONE_BIT(5)         //PIN5
    gpio_trigge_mode(GPIOD,(GPIO_TRG_MODE)PD_5_TRIGGER_MODE,GPIO_PIN_5);
    gpio_interrupt_set(GPIOD,GPIO_PIN_5,ENABLE);
#endif
#if PD_IE & ONE_BIT(4)         //PIN4
    gpio_trigge_mode(GPIOD,(GPIO_TRG_MODE)PD_4_TRIGGER_MODE,GPIO_PIN_4);
    gpio_interrupt_set(GPIOD,GPIO_PIN_4,ENABLE);
#endif
#if PD_IE & ONE_BIT(3)         //PIN3
    gpio_trigge_mode(GPIOD,(GPIO_TRG_MODE)PD_3_TRIGGER_MODE,GPIO_PIN_3);
    gpio_interrupt_set(GPIOD,GPIO_PIN_3,ENABLE);
#endif
#if PD_IE & ONE_BIT(2)         //PIN2
    gpio_trigge_mode(GPIOD,(GPIO_TRG_MODE)PD_2_TRIGGER_MODE,GPIO_PIN_2);
    gpio_interrupt_set(GPIOD,GPIO_PIN_2,ENABLE);
#endif
#if PD_IE & ONE_BIT(1)         //PIN1
    gpio_trigge_mode(GPIOD,(GPIO_TRG_MODE)PD_1_TRIGGER_MODE,GPIO_PIN_1);
    gpio_interrupt_set(GPIOD,GPIO_PIN_1,ENABLE);
#endif
#if PD_IE & ONE_BIT(0)         //PIN0
    gpio_trigge_mode(GPIOD,(GPIO_TRG_MODE)PD_0_TRIGGER_MODE,GPIO_PIN_0);
    gpio_interrupt_set(GPIOD,GPIO_PIN_0,ENABLE);
#endif
#endif  // #if PD_EN == 1


//    <e0>PE
#define PE_EN 0
#if PE_EN == 1
//      <e8.7>PIN 7
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PE_7_INOUT_MODE 2

//      <e7.6>PIN 6
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PE_6_INOUT_MODE 2

//      <e6.5>PIN 5
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PE_5_INOUT_MODE 2

//      <e5.4>PIN 4
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PE_4_INOUT_MODE 2

//      <e4.3>PIN 3
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PE_3_INOUT_MODE 2

//      <e3.2>PIN 2
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PE_2_INOUT_MODE 2


//      <e2.1>PIN 1
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PE_1_INOUT_MODE 2

//      <e1.0>PIN 0
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
//    </e>
#define PE_0_INOUT_MODE 2

#define PE_PIN 0x00

// init PE group
#if PE_PIN & ONE_BIT(7)         //PIN7
    gpio_init(GPIOE,(GPIO_MODE)PE_7_INOUT_MODE,GPIO_PIN_7);
#endif
#if PE_PIN & ONE_BIT(6)         //PIN6
    gpio_init(GPIOE,(GPIO_MODE)PE_6_INOUT_MODE,GPIO_PIN_6);
#endif
#if PE_PIN & ONE_BIT(5)         //PIN5
    gpio_init(GPIOE,(GPIO_MODE)PE_5_INOUT_MODE,GPIO_PIN_5);
#endif
#if PE_PIN & ONE_BIT(4)         //PIN4
    gpio_init(GPIOE,(GPIO_MODE)PE_4_INOUT_MODE,GPIO_PIN_4);
#endif
#if PE_PIN & ONE_BIT(3)         //PIN3
    gpio_init(GPIOE,(GPIO_MODE)PE_3_INOUT_MODE,GPIO_PIN_3);
#endif
#if PE_PIN & ONE_BIT(2)         //PIN2
    gpio_init(GPIOE,(GPIO_MODE)PE_2_INOUT_MODE,GPIO_PIN_2);
#endif
#if PE_PIN & ONE_BIT(1)         //PIN1
    gpio_init(GPIOE,(GPIO_MODE)PE_1_INOUT_MODE,GPIO_PIN_1);
#endif
#if PE_PIN & ONE_BIT(0)         //PIN0
    gpio_init(GPIOE,(GPIO_MODE)PE_0_INOUT_MODE,GPIO_PIN_0);
#endif
#endif  // #if PE_EN == 1


//    <e0>PF
#define PF_EN 0
#if PF_EN == 1
//      <e8.7>PIN 7
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PF_7_INOUT_MODE 2

//      <e7.6>PIN 6
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PF_6_INOUT_MODE 2

//      <e6.5>PIN 5
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PF_5_INOUT_MODE 2

//      <e5.4>PIN 4
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PF_4_INOUT_MODE 2

//      <e4.3>PIN 3
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PF_3_INOUT_MODE 2

//      <e3.2>PIN 2
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PF_2_INOUT_MODE 2


//      <e2.1>PIN 1
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PF_1_INOUT_MODE 2

//      <e1.0>PIN 0
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
//    </e>
#define PF_0_INOUT_MODE 2

#define PF_PIN 0x00

// init PF group
#if PF_PIN & ONE_BIT(7)         //PIN7
    gpio_init(GPIOF,(GPIO_MODE)PF_7_INOUT_MODE,GPIO_PIN_7);
#endif
#if PF_PIN & ONE_BIT(6)         //PIN6
    gpio_init(GPIOF,(GPIO_MODE)PF_6_INOUT_MODE,GPIO_PIN_6);
#endif
#if PF_PIN & ONE_BIT(5)         //PIN5
    gpio_init(GPIOF,(GPIO_MODE)PF_5_INOUT_MODE,GPIO_PIN_5);
#endif
#if PF_PIN & ONE_BIT(4)         //PIN4
    gpio_init(GPIOF,(GPIO_MODE)PF_4_INOUT_MODE,GPIO_PIN_4);
#endif
#if PF_PIN & ONE_BIT(3)         //PIN3
    gpio_init(GPIOF,(GPIO_MODE)PF_3_INOUT_MODE,GPIO_PIN_3);
#endif
#if PF_PIN & ONE_BIT(2)         //PIN2
    gpio_init(GPIOF,(GPIO_MODE)PF_2_INOUT_MODE,GPIO_PIN_2);
#endif
#if PF_PIN & ONE_BIT(1)         //PIN1
    gpio_init(GPIOF,(GPIO_MODE)PF_1_INOUT_MODE,GPIO_PIN_1);
#endif
#if PF_PIN & ONE_BIT(0)         //PIN0
    gpio_init(GPIOF,(GPIO_MODE)PF_0_INOUT_MODE,GPIO_PIN_0);
#endif
#endif  // #if PF_EN == 1


//    <e0>PG
#define PG_EN 0
#if PG_EN == 1
//      <e8.7>PIN 7
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PG_7_INOUT_MODE 2

//      <e7.6>PIN 6
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PG_6_INOUT_MODE 2

//      <e6.5>PIN 5
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PG_5_INOUT_MODE 2

//      <e5.4>PIN 4
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PG_4_INOUT_MODE 2

//      <e4.3>PIN 3
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PG_3_INOUT_MODE 2

//      <e3.2>PIN 2
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PG_2_INOUT_MODE 2


//      <e2.1>PIN 1
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
#define PG_1_INOUT_MODE 2

//      <e1.0>PIN 0
//        <o>Mode
//          <0x0=>Floating
//          <0x1=>Pull up
//          <0x2=>Out
//        <i>Configure GPIO inout mode
//      </e>
//    </e>
//  </e>
#define PG_0_INOUT_MODE 2

#define PG_PIN 0x00

// init PG group
#if PG_PIN & ONE_BIT(7)         //PIN7
    gpio_init(GPIOG,(GPIO_MODE)PG_7_INOUT_MODE,GPIO_PIN_7);
#endif
#if PG_PIN & ONE_BIT(6)         //PIN6
    gpio_init(GPIOG,(GPIO_MODE)PG_6_INOUT_MODE,GPIO_PIN_6);
#endif
#if PG_PIN & ONE_BIT(5)         //PIN5
    gpio_init(GPIOG,(GPIO_MODE)PG_5_INOUT_MODE,GPIO_PIN_5);
#endif
#if PG_PIN & ONE_BIT(4)         //PIN4
    gpio_init(GPIOG,(GPIO_MODE)PG_4_INOUT_MODE,GPIO_PIN_4);
#endif
#if PG_PIN & ONE_BIT(3)         //PIN3
    gpio_init(GPIOG,(GPIO_MODE)PG_3_INOUT_MODE,GPIO_PIN_3);
#endif
#if PG_PIN & ONE_BIT(2)         //PIN2
    gpio_init(GPIOG,(GPIO_MODE)PG_2_INOUT_MODE,GPIO_PIN_2);
#endif
#if PG_PIN & ONE_BIT(1)         //PIN1
    gpio_init(GPIOG,(GPIO_MODE)PG_1_INOUT_MODE,GPIO_PIN_1);
#endif
#if PG_PIN & ONE_BIT(0)         //PIN0
    gpio_init(GPIOG,(GPIO_MODE)PG_0_INOUT_MODE,GPIO_PIN_0);
#endif
#endif  // #if PG_EN == 1
#endif
    return SUCCESS;
}
#endif

config_return_status peripherals_config(void)
{
    uint32_t i = 0;
    uint32_t size = sizeof(config_return_status) / sizeof(ErrorStatus) - 1;
    uint32_t error_cnt = 0;
    ErrorStatus* pt = NULL;
    config_return_status ret_val = { ERROR };

#ifdef BF7x06BMxx_WDT_DRIVER_PRESENT
    ret_val.wdt = wdt_cfg();
#endif

#ifdef BF7x06BMxx_CAN_DRIVER_PRESENT
    ret_val.can = can_config();
#endif

#ifdef BF7x06BMxx_RTC_DRIVER_PRESENT
    ret_val.rtc = rtc_config();
#endif

#ifdef BF7x06BMxx_SCI_DRIVER_PRESENT
    ret_val.sci = sci_config();
#endif

#ifdef BF7x06BMxx_TIMER_DRIVER_PRESENT
    ret_val.timer = timer_config();
#endif

#ifdef BF7x06BMxx_ADC_DRIVER_PRESENT
    ret_val.adc = adc_config();
#endif

#ifdef BF7x06BMxx_PWM_DRIVER_PRESENT
    ret_val.pwm = pwm_config();
#endif

#ifdef BF7x06BMxx_GPIO_DRIVER_PRESENT
    ret_val.gpio = gpio_config();
#endif

    pt = (ErrorStatus*)(&ret_val);
    for(i = 0;i < size;i++){
        if(*(pt++) == ERROR){
            error_cnt++;
        }
    }

    if(error_cnt != 0){
        ret_val.overall = ERROR;
    }else{
        ret_val.overall = SUCCESS;
    }

    return ret_val;
}

//------------- <<< end of configuration section >>> ---------------------------
