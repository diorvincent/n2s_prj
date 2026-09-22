/*
 * CAN_CFG.h
 * Xi'An ManHui Info. Science LLC
 * Created on: Oct 31, 2023
 * Author: He Jingchi
 */

#ifndef COMM_CAN_CFG_H_
#define COMM_CAN_CFG_H_


/* ===========================================  Includes  =========================================== */
#include <string.h>
#include "BF7006BMxx.h"
#include "DATA_TYPE.h"

/* ===========================================  Typedef  ============================================ */
#pragma pack(push)
#pragma pack(1)
typedef struct
{
	U32		*Data32Ptr;
	U8		*DataPtr;
	U16 	Length;
	U16 	Cnt;
	U16		Crc;
} CANPduType;

typedef struct _CAN_MSG_INFO
{
    uint32_t    ID;                                /*!< CAN identifier */
    uint32_t    RTS;                               /*!< Receive time stamps */
    uint8_t     ESI;                               /*!< Transmit time-stamp enable or error state indicator */
    uint8_t     DLC;                               /*!< Data length code */
    uint8_t     BRS;                               /*!< Bit rate switch */
    uint8_t     FDF;                               /*!< FD format indicator */
    uint8_t     RTR;                               /*!< Remote transmission request */
    uint8_t     IDE;                               /*!< Identifier extension */
    uint8_t     *DATA;                             /*!< Data */
} CAN_MsgInfoType;

#pragma pack(pop)


/* ==========================================  Variables  =========================================== */

/* ============================================  Define  ============================================ */
#define APP_START_ID 					0x000
#define APP_END_ID						0x6FF

#define PhysicalRequestCANID 			0x729
#define FunctionalRequestCANID 		0x7DF
#define Physical_USDT_CANID 			0x7A9
//#define Physical_UUDT_CANID 		0x5E8

/* ====================================  Functions declaration  ===================================== */
void COMM_CAN_Init(void);
void COMM_CAN_CFG_TX(const CAN_MsgInfoType *info);
void COMM_CAN_CFG_RX(void);



#endif /* COMM_CAN_CFG_H_ */




