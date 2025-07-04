/*!
    \file  eep.c
    \brief eeprom application
*/

#include "eep.h"

eep_flag_str eep_flag = 
{
    .needToUpgrade = 0U,
};

/*!
    \brief      写升级标志并复位到BOOT
	\param[in]	none
    \param[out] none
    \retval     none
*/
void eepMsEvent(void)
{
	if(eep_flag.needToUpgrade == 0U)
    {
        return;
	}
    
    //#warning 升级标志在此写入EEP（BOOT中为写升级完成标志）
    switch(eep_flag.needToUpgrade)
    {
        case 1U:
            if(is_eeprom_idle())
            {
                /* 擦除不等待，后续检查空闲状态即可 */
                eeprom_sector_erase(EEP_BootEnAddrPage,FALSE);
                eep_flag.needToUpgrade = 2U;
            }
            break;
        case 2U:
            if(is_eeprom_idle())
            {
                /* 写升级标志0xAA到EEP */
                if(eeprom_prog_word(EEP_BootEnAddr,0xAAU) == SUCCESS)
                {
                    uint32_t dataGet = 0U;
                    if(eeprom_word_get(EEP_BootEnAddr,&dataGet))
                    {
                        if(0xAAU == dataGet)
                        {
                            eep_flag.needToUpgrade = 0U;
                            //#warning 复位并进入boot
                            /* 复位 */
                            NVIC_SystemReset();
                        }
                        else
                        {
                            /* 重写标志 */
                            eep_flag.needToUpgrade = 1U;
                        }
                    }
                    else
                    {
                        /* 重写标志 */
                        eep_flag.needToUpgrade = 1U;
                    }
                }
                else
                {
                    /* 重写标志 */
                    eep_flag.needToUpgrade = 1U;
                }
            }
            break;
        default:
            eep_flag.needToUpgrade = 0U;
            break;
    }
}

