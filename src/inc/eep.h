/*!
    \file  eep.h
    \brief definitions for eeprom application
*/

#ifndef EEP_H
#define EEP_H

#include "BF7006BMxx.h"
#include "BF7006BMxx_eflash.h"

#define	EEP_BootEnAddrPage			0U                 //升级标志所在页
#define	EEP_BootEnAddr				((EEPROM_BASE + (EEPROM_SECTOR_SIZE * EEP_BootEnAddrPage)) + 0x04U)   //升级标志所在地址

typedef struct
{
	uint8_t needToUpgrade;
}eep_flag_str;

extern eep_flag_str eep_flag;

extern void eepMsEvent(void);

#endif
