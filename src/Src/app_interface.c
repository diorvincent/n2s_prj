/*!
    \file  app_interface.c
    \brief app function
*/

#include "app_interface.h"
#include "can_init.h"
#include "can_frame.h"
#include "eep.h"


void appInit(void);        /* APP初始化函数 */
void appSubPolling(void);  /* APP轮询函数   */
//static void funcInterfaceInit(void);    /* 功能接口函数初始化 */

/******************************* 用户自定义接口函数 ******************************/
void (*canOtaFunc)(can_frame_struct rx_frame) = NULL;   /* 升级处理函数 */
void (*canDealFunc)(can_frame_struct rx_frame) = NULL;  /* 非诊断帧处理函数 */
/******************************* end 用户自定义接口函数 ******************************/


/*!
    \brief      APP初始化
	\param[in]	none
    \param[out] none
    \retval     none
*/
void appInit(void)
{
    /* BOOT地址空间擦写保护 */
    //#warning 须根据BOOT大小配置保护空间，0x08对应16k空间，对应0x4000范围
    flash_protect(0x08U);	   
    
    wdt_clear();
    
    /* CAN队列初始化 */    
    //can_queue_init();         
    /* CAN初始化 */
    canInit();  
    /* 接口函数初始化 */
    //funcInterfaceInit();
}

/*!
    \brief      APP轮询
	\param[in]	none
    \param[out] none
    \retval     none
*/
void appSubPolling(void)
{
    uint8_t CanRxOk;
    can_frame_struct CanRxFrame;
    
    /* 从队列取一帧报文 */
    CanRxOk = can_queue_pop(&CanRxFrame);  
    if(CanRxOk == 0U)
    {
        return;
    }
    
    //#warning 须由用户自行定义用于CAN升级的报文ID
    if(CanRxFrame.sfid == CAN_OTA_ID)
    {
        if((canOtaFunc) != NULL)
        {
            /* 升级处理 */
            //#warning 须由用户自行实现canOtaFunc
            (*canOtaFunc)(CanRxFrame);
        }
    }
    else
    {
        if((canDealFunc) != NULL)
        {
            /* 功能报文处理 */
            //#warning 须由用户自行实现canDealFunc
            (*canDealFunc)(CanRxFrame);    
        }
    }
}



/*!
    \brief      用户接口函数初始化
	\param[in]	none
    \param[out] none
    \retval     none
*/
//static void funcInterfaceInit(void)
//{
//    //#warning 须由用户自行实现接口函数并连接到对应指针
//    /* 升级报文接口函数指针 */
//    canOtaFunc  = NULL;
//    /* 功能报文接口函数指针 */
//    canDealFunc = NULL;
//}

