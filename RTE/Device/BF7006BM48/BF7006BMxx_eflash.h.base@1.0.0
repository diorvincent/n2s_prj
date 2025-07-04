/*!
    \file  BF7006BMxx_flash.h
    \brief definitions for the flash control
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_eflash.h initial version

*/

#ifndef BF7006BMxx_EFLASH_H
#define	BF7006BMxx_EFLASH_H

#include "BF7006BMxx.h"
#include "BF7006BMxx_wdt.h"
#include "BF7006BMxx_sysctrl.h"

#define	NONE_SEL                    0U

/* flash registers addr definitions */
#define	EFLASH_SEL_ADDR				(EFLASH_CTRL_BASE + 0x00U)		
#define	EFLASH_MODE_ADDR			(EFLASH_CTRL_BASE + 0x04U)		
#define	EFLASH_EBCFG_ADDR			(EFLASH_CTRL_BASE + 0x08U)		
#define	FLASH_STATE_ADDR			(EFLASH_CTRL_BASE + 0x0cU)		

#define	EFLASH_SEL				    (REG32(eflash_select_var))		
#define	EFLASH_MODE				    (REG32(eflash_mode_var))		
#define	EFLASH_EBCFG			    (REG32(eflash_ebcfg_var))		
#define	FLASH_STATE				    (REG32(eflash_flashstate_var))  

/* eep registers definitions */
#define EEP_SEL                     (REG32(EFLASH_CTRL_BASE + 0x00U))       /*!< flash or eeprom select register            */
#define EEP_MODE                    (REG32(EFLASH_CTRL_BASE + 0x04U))       /*!< flash and eeprom prog/erase mode register  */
#define EEP_EBCFG                   (REG32(EFLASH_CTRL_BASE + 0x08U))       /*!< flash and eeprom control register          */
#define EEP_STATE                   (REG32(EFLASH_CTRL_BASE + 0x10U))       /*!< eeprom prog/erase state register           */

/* protect registers definitions */
#define EFLASH_ECC_CTRL             (REG32(EFLASH_CTRL_BASE + 0x200U))      /*!< flash and eeprom ECC error correct enable register */
#define EFLASH_UNLOCK               (REG32(EFLASH_CTRL_BASE + 0x204U))      /*!< flash and eeprom unlock key register       */
#define FLASH_LOCK_SIZE             (REG32(EFLASH_CTRL_BASE + 0x208U))      /*!< flash lock size register                   */
#define EEPROM_LOCK_SIZE            (REG32(EFLASH_CTRL_BASE + 0x20cU))      /*!< eeprom lock size register                  */
/* end registers definitions */

/* contact define */
/* flash or eeprom select */
#define FLASH_SEL                   0xaa55U                                 /*!< select to access flash  */
#define EEPROM_SEL                  0xcd78U                                 /*!< select to access eeprom */

/* flash and eeprom unlock */
#define EFLASH_UNLOCK_KEY           0xab23dc54U                             /*!< flash and eeprom unlock key */


/* flash define */
/* flash max address */
#define FLASH_MAX_ADDR              (FLASH_BASE + 0x17FFFU)                 /*!< flash max address              */
/* flash sector size */
#define FLASH_SECTOR_SIZE           0x400U                                  /*!< flash sector size              */
/* flash sector max number */
#define FLASH_SECTOR_MAX_NUM        96U                                     /*!< flash max sector number        */
/* flash prog/erase mode define */
/* note: when cpu run code in flash to erase flash, CPU must halt when erase flash
         when cpu run code in SRAM to erase flash,CPU must run when erase flash    */
#define FLASH_HALT_ENABLE           0xa5U                                   /*!< CPU halt when erase FLASH      */
#define FLASH_HALT_DISABLE          0x5aU                                   /*!< CPU run when erase FLASH       */
/* flash prog/erase command define */
#define FLASH_SECTOR_ERASE          0x55U                                   /*!< flash sector erase             */
#define FLASH_MASS_ERASE            0xaaU                                   /*!< flash mass erase               */
#define FLASH_PROG                  0x33U                                   /*!< flash prog                     */
/* flash operation done state */    
#define FLASH_STATE_IDLE            0x01U                                   /*!< flash erase or prog done state */
/* flash lock size */
#define FLASH_LOCK_UNIT             0x800U                                  /*!< flash lock minimun unit        */
/* flash lock page number */
#define FLASH_LOCK_MAX_PAGE         48U                                     /*!< flash lock page max number     */

/* eeprom define */
/* eeprom max address */
#define EEPROM_MAX_ADDR             (EEPROM_BASE + 0x7FFU)                  /*!< eeprom max address             */
/* eeprom sector size */
#define EEPROM_SECTOR_SIZE          0x40U                                   /*!< eeprom sector size             */
/* eeprom sector max number */
#define EEPROM_SECTOR_MAX_NUM       32U                                     /*!< eeprom max sector number       */
/* eeprom prog/erase mode define */
#define EEPROM_PROG_ERASE_MODE      0x3cU                                   /*!< eeprom prog/erase mode         */
/* eeprom prog/erase command define */
#define EEPROM_SECTOR_ERASE         0x55U                                   /*!< eeprom sector erase            */
#define EEPROM_MASS_ERASE           0xaaU                                   /*!< eeprom mass erase              */
#define EEPROM_PROG                 0x33U                                   /*!< eeprom prog                    */
/* eeprom operation done state */    
#define EEPROM_STATE_IDLE           0x01U                                   /*!< eeprom erase or prog done state */
/* eeprom lock unit */
#define EEPROM_LOCK_UNIT            0x40                                    /*!< eeprom lock minimun unit       */
/* eeprom lock page number */
#define EEPROM_LOCK_MAX_PAGE        36U                                     /*!< eeprom lock page max number    */

/* function declarations */
/* ECC error correction enable */
ErrorStatus ecc_enable(void);
/* ECC error correction disable */
ErrorStatus ecc_disable(void);

/* flash function declarations */
void eflash_var_init(void);
void eflash_var_mark1(void);
void eflash_var_mark2(void);

/* flash sector erase */
ErrorStatus flash_sector_erase(uint8_t sector_num,bool is_wait_done);
/* flash n sectors erase */
ErrorStatus flash_Nsectors_erase(uint8_t sector_num,uint8_t len);
/* flash mass erase */
ErrorStatus flash_mass_erase(bool is_wait_done);
/* flash word prog */
ErrorStatus flash_prog_word(uint32_t addr,uint32_t data);
/* flash words prog */
ErrorStatus flash_prog_Nwords(uint32_t addr,uint32_t data[],uint32_t len);
/* is flash idle */
bool is_flash_idle(void);
/* wait flash prog/erase done */
ErrorStatus wait_flash_prog_erae_done(void);
/* flash word get */
ErrorStatus flash_word_get(uint32_t addr,uint32_t *red_dat);
/* flash words get */
ErrorStatus flash_Nwords_get(uint32_t addr,uint32_t *red_dat,uint32_t len);
/* flash protect set */
void flash_protect(uint8_t protect_page);

/* eeprom function declarations */
/* eeprom sector erase */
ErrorStatus eeprom_sector_erase(uint8_t sector_num,bool is_wait_done);
/* eeprom n sectors erase */
ErrorStatus eeprom_Nsectors_erase(uint8_t sector_num,uint8_t len);
/* eeprom mass erase */
ErrorStatus eeprom_mass_erase(bool is_wait_done);
/* eeprom word prog */
ErrorStatus eeprom_prog_word(uint32_t addr,uint32_t data);
/* eeprom words prog */
ErrorStatus eeprom_prog_Nwords(uint32_t addr,uint32_t data[],uint32_t len);
/* is eeprom idle */
bool is_eeprom_idle(void);
/* wait eeprom prog/erase done */
ErrorStatus wait_eeprom_prog_erae_done(void);
/* eeprom word get */
ErrorStatus eeprom_word_get(uint32_t addr,uint32_t *red_dat);
/* eeprom words get */
ErrorStatus eeprom_Nwords_get(uint32_t addr,uint32_t *red_dat,uint32_t len);
/* eeprom protect set */
void eeprom_protect(uint8_t protect_page);

#endif
