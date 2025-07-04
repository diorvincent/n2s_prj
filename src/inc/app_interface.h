/*!
    \file  iap_interface.h
    \brief definitions for iap
*/

#ifndef APP_H
#define APP_H

/* OTA报文ID */
#define CAN_OTA_ID      0x000U

/**********************接口函数**********************/
extern void appInit(void);         /* APP初始化函数 */
extern void appSubPolling(void);   /* APP轮询函数 */
/****************************************************/

#endif

