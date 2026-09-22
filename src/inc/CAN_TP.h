/*
 * CAN_TP.h
 * Xi'An ManHui Info. Science LLC
 * Modify on: Dec 26, 2023
 * Author: He Jingchi
 */

#ifndef COMM_CAN_TP_H_
#define COMM_CAN_TP_H_



/* ===========================================  Includes  =========================================== */
#include "CAN_CFG.h"
#include "DATA_TYPE.h"
//#include "EFLS_DRV.h"
/* ===========================================  Typedef  ============================================ */


/* ============================================  Define  ============================================ */
#define CAN_TP_CRC_CHECK			0
#define CRC16_CHECKED					0x01
#define CRC16_NOT_CHECKED 		0x09


#define CAN_MAX_BUFFER_SIZE 		136
//#define CAN_MAX_RESPONSE_BUF_SIZE 	128
#define CAN_MAX_BUFFER_SIZE2 		8

#define SingleFrame 					0x00
#define FirstFrame 						0x01
#define ConsecutiveFrame 			0x02
#define FlowControlFrame 			0x03
#define UpdateFromAPPMsg			0x04
#define FromLongTimeMsg				0x05

#define NoResponseFlag				0x00
#define SingleFrameFlag				0x01
#define ConsecutiveFrameFlag	0x02
#define FlowControlFrameFlag 	0x03

#define REQUEST						TRUE
#define CLEAR_REQUEST				FALSE

#define CHECKSUM_IN_SVR_0X36	0x02
#define FlowCtrlFirstByte 		0x30
#define DCAN_BLOCK_SIZE				0x80
#define DCAN_STMIN						0x00

#define FILLPATTERN						0x55
#define CAN_N_BS              150

#define EFLS_WRITE_BUFFER_SIZE 56
/* ==========================================  Variables  =========================================== */
/* ====================================  Functions declaration  ===================================== */

CANPduType* COMM_CANTP_GetRxBuff(void);
CANPduType* COMM_CANTP_GetTxBuff(void);
CANPduType* COMM_CANTP_GetRxBuff2(void);
CANPduType* COMM_CANTP_GetTxBuff2(void);

void COMM_CANTP_Init(void);
void COMM_CANTP_CleanBuffer(void);
void COMM_CANTP_DtrmnDCANService(void);
void COMM_CANTP_FrameFill(CAN_MsgInfoType *LTempFrame);

void COMM_CANTP_RX_MsgProcess(void);
void COMM_CANTP_RX_SingleFrameProcess(CANPduType** LPduPrtPrt);
void COMM_CANTP_RX_FirstFrameProcess(CANPduType** LPduPrtPrt);
void COMM_CANTP_RX_FlowCtrlFrameProcess(void);
U8 COMM_CANTP_RX_ConsecutiveFrameProcess(CANPduType** LPduPrtPrt);

void COMM_CANTP_TX_MsgProcess(void);
void COMM_CANTP_TX_3E_MsgProcess(void);
void COMM_CANTP_TX_SingleFrameProcess(CANPduType* LPdu);
void COMM_CANTP_TX_FirstFrameProcess(CANPduType* LPdu);
U8 COMM_CANTP_TX_FlowCtrlFrameProcess(void);
bool COMM_CANTP_TX_ConsecutiveFrameProcess(CANPduType* LPdu);

void COMM_CANTP_USDT_TX_SingleFrame(CAN_MsgInfoType* Tx_Buff);
void COMM_CANTP_USDT_TX_ConsecutiveFrame(CAN_MsgInfoType* LTempFrame);

extern void CAN_CFG_TX(const CAN_MsgInfoType *info);

#endif /* COMM_CAN_TP_H_ */



