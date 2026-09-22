/*
 * CAN_TP.c
 * Xi'An ManHui Info. Science LLC
 * Created on: Oct 31, 2023
 * Modify on: Dec 26, 2023
 * Author: He Jingchi
 */

#include "CAN_TP.h"

static CANPduType	CAN_TPdu;
static CANPduType	CAN_RPdu;
static CANPduType*	CAN_TP_TPdu;
static CANPduType*	CAN_TP_RPdu;

static CANPduType	CAN_TPdu2;
static CANPduType	CAN_RPdu2;

static U16 CAN_TP_ConsecutiveTimeout = 0;
bool CAN_TP_ConsecutiveFlag = FALSE;

extern __IO bool CAN_CFG_DIAG_NewMsgFlag;
extern __IO bool CAN_CFG_DIAG_NewFunMsgFlag;
extern __IO bool CAN_CFG_DIAG_3E_NewMsgFlag;
extern __IO bool CAN_CFG_DIAG_3E_NewFunMsgFlag;


extern CAN_MsgInfoType g_sendCANMsgInfo;
extern CAN_MsgInfoType g_recvCANMsgInfo;
extern bool g_sendCanDataRdy;


static U8 	RXBuffer[CAN_MAX_BUFFER_SIZE];
static U8 	TXBuffer[CAN_MAX_BUFFER_SIZE];
static U8 	RXBuffer2[CAN_MAX_BUFFER_SIZE2];
static U8 	TXBuffer2[CAN_MAX_BUFFER_SIZE2];
U8	DCAN_ResponseType = NoResponseFlag;
U8	DCAN_SID3E_ResponseType;
bool ConsecutiveFrameComplete;
bool SERVICE_REQUEST_FLAG;
bool SERVICE_REQUEST_FLAG2;
bool SERVICE_REQUEST_FLAG_OLD;

#if CAN_TP_CRC_CHECK
const U8 CAN_TP_CRC16Hi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};

const  U8 CAN_TP_CRC16Lo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
    0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
    0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
    0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
    0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
    0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
    0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
    0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
    0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};
#endif

void COMM_CANTP_Service_Request(bool Request)
{
	SERVICE_REQUEST_FLAG = Request;
}

void COMM_CANTP_Service_3E_Request(bool Request)
{
	SERVICE_REQUEST_FLAG2 = Request;
}


void COMM_CANTP_Init(void)
{
	U16 i = 0, j = 0;
	for (i = 0; i < CAN_MAX_BUFFER_SIZE; i++)
	{
		RXBuffer[i] = 0;
		TXBuffer[i] = 0;
	}

	for (j = 0; j < CAN_MAX_BUFFER_SIZE2; j++)
	 {
		RXBuffer2[j] = 0;
		TXBuffer2[j] = 0;
	 }

	CAN_RPdu.DataPtr = RXBuffer;
	CAN_RPdu.Length = 0;
	CAN_RPdu.Cnt = 0;

	CAN_TPdu.DataPtr = TXBuffer;
	CAN_TPdu.Length = 0;
	CAN_TPdu.Cnt = 0;

	CAN_RPdu2.DataPtr = RXBuffer2;
	CAN_RPdu2.Length = 0;
	CAN_RPdu2.Cnt = 0;

	CAN_TPdu2.DataPtr = TXBuffer2;
	CAN_TPdu2.Length = 0;
	CAN_TPdu2.Cnt = 0;

	CAN_TP_TPdu = NULL;
	CAN_TP_RPdu = NULL;

	ConsecutiveFrameComplete = TRUE;
}


CANPduType* COMM_CANTP_GetRxBuff(void)
{
	return &CAN_RPdu;
}


CANPduType* COMM_CANTP_GetTxBuff(void)
{
	return &CAN_TPdu;
}


CANPduType* COMM_CANTP_GetRxBuff2(void)
{
	return &CAN_RPdu2;
}


CANPduType* COMM_CANTP_GetTxBuff2(void)
{
	return &CAN_TPdu2;
}

#if CAN_TP_CRC_CHECK
U8 COMM_CANTP_RX_CRC16_Check(CANPduType* LPduPrt)
{
	U8 LCRCHi = 0xFF;
	U8 LCRCLo = 0xFF;
	U8 LIndex = 0;
	U8 ret = 0;
	U8 i = 0;

	for (i = 2; i < LPduPrt->Length; i++)
	{
		LIndex = (LCRCHi) ^ (LPduPrt->DataPtr[i]);
		LCRCHi = (LCRCLo) ^ (CAN_TP_CRC16Hi[LIndex]);
		LCRCLo = CAN_TP_CRC16Lo[LIndex];
	}
	if (LPduPrt->Crc == ((LCRCHi<<8) | LCRCLo))
	{
		ret = CRC16_CHECKED;
	}
	else
	{
		ret = CRC16_NOT_CHECKED;
	}
	return ret;
}
#endif

void COMM_CANTP_FrameFill(CAN_MsgInfoType *LTempFrame)
{
	U8 i = 0;
	if (LTempFrame->DLC == 8)
	{
		return;
	}
	else
	{
		for (i = 0; i < 8 - (LTempFrame->DLC); i++)
		{
			LTempFrame->DATA[i + LTempFrame->DLC] = FILLPATTERN;
		}
    LTempFrame->DLC = 8;
	}
}


void COMM_CANTP_RX_MsgProcess(void)
{
	U8 CANFrameType;
	CANPduType *LTemPdu = COMM_CANTP_GetRxBuff();
	CANPduType *LTemPdu2 = COMM_CANTP_GetRxBuff2();
  if (CAN_CFG_DIAG_3E_NewMsgFlag == TRUE || CAN_CFG_DIAG_3E_NewFunMsgFlag == TRUE)
	{
		CANFrameType = g_recvCANMsgInfo.DATA[0] >> 4;
		switch(CANFrameType)
		{
			case SingleFrame:
				DCAN_SID3E_ResponseType = SingleFrameFlag;
				//DCAN_ResponseType = SingleFrameFlag;
				COMM_CANTP_RX_SingleFrameProcess(&LTemPdu2);
				COMM_CANTP_Service_3E_Request(REQUEST);
				break;
            default:
				break;
        }
    }
	if (CAN_CFG_DIAG_NewMsgFlag == TRUE || CAN_CFG_DIAG_NewFunMsgFlag == TRUE)
	{
		CANFrameType = g_recvCANMsgInfo.DATA[0] >> 4;
		switch(CANFrameType)
		{
			case SingleFrame:
				if ((g_recvCANMsgInfo.DATA[0] & 0x0F) != 0)
				{
						if (g_recvCANMsgInfo.DATA[1] == 0x3E)
						{
								DCAN_SID3E_ResponseType = SingleFrameFlag;
								//DCAN_ResponseType = SingleFrameFlag;
								COMM_CANTP_RX_SingleFrameProcess(&LTemPdu2);
								COMM_CANTP_Service_3E_Request(REQUEST);
						}
						else
						{
								DCAN_ResponseType = SingleFrameFlag;
								COMM_CANTP_RX_SingleFrameProcess(&LTemPdu);
								COMM_CANTP_Service_Request(REQUEST);
						}
				}
				break;
			case FirstFrame:
				DCAN_ResponseType = FlowControlFrameFlag;
				COMM_CANTP_RX_FirstFrameProcess(&LTemPdu);
				ConsecutiveFrameComplete = FALSE;
				CAN_CFG_DIAG_NewMsgFlag = FALSE;
				CAN_CFG_DIAG_NewFunMsgFlag = FALSE;
				break;
			case FlowControlFrame:
				COMM_CANTP_RX_FlowCtrlFrameProcess();
        DCAN_ResponseType = ConsecutiveFrameFlag;
				CAN_CFG_DIAG_NewMsgFlag = FALSE;
				CAN_CFG_DIAG_NewFunMsgFlag = FALSE;
				break;
			case ConsecutiveFrame:
				DCAN_ResponseType = SingleFrameFlag;
				if ( (COMM_CANTP_RX_ConsecutiveFrameProcess(&LTemPdu) == CRC16_CHECKED))
				{
					//COMM_CANTP_TX_FlowCtrlFrameProcess();
				}
				break;
			default:
				break;
		}
	}
}


void COMM_CANTP_RX_FlowCtrlFrameProcess(void)
{
/*	U8 Lf_FrameHead = 0;
	U8 Lf_BlockSize = 0;
	U8 Lf_STMin = 0;
	Lf_FrameHead = g_recvCANMsgInfo.DATA[0];
	Lf_BlockSize = g_recvCANMsgInfo.DATA[1];
	Lf_STMin = g_recvCANMsgInfo.DATA[2];
*/
}


void COMM_CANTP_RX_SingleFrameProcess(CANPduType** LPduPrtPrt)
{
	U8 i = 0;
//	if ((g_recvCANMsgInfo.DATA[0] & 0x0F) == 0 || (g_recvCANMsgInfo.DATA[0] & 0x0F) > 7)
//	{
//		return;
//	}
	(*LPduPrtPrt)->Length = (g_recvCANMsgInfo.DATA[0] & 0x0F);
	for (i = 0; i<(g_recvCANMsgInfo.DATA[0] & 0x0F); i++)
	{
		(*LPduPrtPrt)->DataPtr[i] = g_recvCANMsgInfo.DATA[i+1];
	}
}


void COMM_CANTP_RX_FirstFrameProcess(CANPduType** LPduPrtPrt)
{
	U8 i=0;
//	if ((((g_recvCANMsgInfo.DATA[0] & 0x0F)<<8) + g_recvCANMsgInfo.DATA[1]) < 8)
//	{	
//		return;
//	}
	(*LPduPrtPrt)->Length = ((g_recvCANMsgInfo.DATA[0] & 0x0F)<<8) + g_recvCANMsgInfo.DATA[1];
	CAN_TP_RPdu = (*LPduPrtPrt);
	for (i = 2; i < 8; i++)
		{
			(*LPduPrtPrt)->DataPtr[i-2]=g_recvCANMsgInfo.DATA[i];
		}
	(*LPduPrtPrt)->Cnt = 6;
}


U8 COMM_CANTP_RX_ConsecutiveFrameProcess(CANPduType** LPduPrtPrt)
{
	U8 i = 0;
#if CAN_TP_CRC_CHECK
	U8 LCRC_PlaceHolder = 0;
#endif
	U8 ret = CRC16_NOT_CHECKED;
	U8 ConsecutiveFrameID;
	CAN_TP_RPdu = (*LPduPrtPrt);
#if CAN_TP_CRC_CHECK
	if(CAN_TP_RPdu->DataPtr[0] == 0x36)
	{
		LCRC_PlaceHolder = CHECKSUM_IN_SVR_0X36;
	}
	else
	{
		LCRC_PlaceHolder = 0;
	}
#endif
	ConsecutiveFrameID = g_recvCANMsgInfo.DATA[0] & 0x0F;
	if (ConsecutiveFrameID == (((CAN_TP_RPdu->Cnt)/7+1) & 0x0F))
	{
		for (i = 1; (i < 8) && (i < g_recvCANMsgInfo.DLC) && (CAN_TP_RPdu->Cnt < (CAN_TP_RPdu->Length)); i++)
		{
			CAN_TP_RPdu->DataPtr[CAN_TP_RPdu->Cnt] = g_recvCANMsgInfo.DATA[i];
			CAN_TP_RPdu->Cnt++;
		}
#if CAN_TP_CRC_CHECK
		if(LCRC_PlaceHolder==CHECKSUM_IN_SVR_0X36)
		{
			if (CAN_TP_RPdu->Cnt >= (CAN_TP_RPdu->Length))
			{
				CAN_TP_RPdu->Crc = ((U16)(g_recvCANMsgInfo.DATA[i++])<<8) + g_recvCANMsgInfo.DATA[i];
				if (COMM_CANTP_RX_CRC16_Check(COMM_CANTP_GetRxBuff()) == CRC16_CHECKED)
				{
					ret = CRC16_CHECKED;
					ConsecutiveFrameComplete = TRUE;
					COMM_CANTP_Service_Request(REQUEST);
				}
				else
				{
					ret = CRC16_NOT_CHECKED;
					ConsecutiveFrameComplete = TRUE;
					COMM_CANTP_Service_Request(REQUEST);
				}
			}
		}
		else
#endif
		{
			if (CAN_TP_RPdu->Cnt >= (CAN_TP_RPdu->Length))
			{
				ret = CRC16_CHECKED;
				ConsecutiveFrameComplete = TRUE;
				COMM_CANTP_Service_Request(REQUEST);
			}
		}
	}
	else
	{
#if CAN_TP_CRC_CHECK
		ret = CRC16_NOT_CHECKED;
#endif
	}
	return ret;
}


void COMM_CANTP_TX_MsgProcess(void)
{
	CANPduType* LPdu = NULL;
	LPdu = COMM_CANTP_GetTxBuff();
 //bool releaseFlag = TRUE;

	/*
	ConsecutiveFrem timeout CAN_N_BUS(150ms),when test new func(0x19 02/04/06) which about consecutive frame,can close these limit on process transient
	*/
	if(CAN_TP_ConsecutiveFlag == TRUE)   
	{
		CAN_TP_ConsecutiveTimeout += 10;
		if((CAN_TP_ConsecutiveTimeout > CAN_N_BS) && (DCAN_ResponseType != ConsecutiveFrameFlag)) 
		{
				CAN_TP_TPdu = NULL;
				LPdu->Cnt = 0;
				LPdu->Length = 0;
				CAN_TP_ConsecutiveFlag = FALSE;
		}
	}
		
	if ( //((CAN_CFG_DIAG_NewMsgFlag == TRUE) || (CAN_CFG_DIAG_NewFunMsgFlag == TRUE))
			((DCAN_ResponseType == SingleFrameFlag) || (DCAN_ResponseType == FlowControlFrameFlag) || (DCAN_ResponseType == ConsecutiveFrameFlag)) )
	{
		if ((LPdu->Length > 0) && (LPdu->Length <= 7) && (DCAN_ResponseType == SingleFrameFlag) && 
			(ConsecutiveFrameComplete == TRUE))
		{
			COMM_CANTP_TX_SingleFrameProcess(LPdu);
			DCAN_ResponseType = NoResponseFlag;
			CAN_CFG_DIAG_NewMsgFlag = FALSE;
			CAN_CFG_DIAG_NewFunMsgFlag = FALSE;
		}
		else if (DCAN_ResponseType == FlowControlFrameFlag) 
		{
			COMM_CANTP_TX_FlowCtrlFrameProcess();
			DCAN_ResponseType = NoResponseFlag;
			CAN_CFG_DIAG_NewMsgFlag = FALSE;
			CAN_CFG_DIAG_NewFunMsgFlag = FALSE;
		}       
		else
		{
			if ((LPdu->Length > 7) && (LPdu->Cnt == 0))
			{
				COMM_CANTP_TX_FirstFrameProcess(LPdu);
				DCAN_ResponseType = NoResponseFlag;
				CAN_CFG_DIAG_NewMsgFlag = FALSE;
				CAN_CFG_DIAG_NewFunMsgFlag = FALSE;
				CAN_TP_ConsecutiveTimeout = 0;
				CAN_TP_ConsecutiveFlag = TRUE;
			}
			else
			{
				if(DCAN_ResponseType == ConsecutiveFrameFlag) 
				{
						if(COMM_CANTP_TX_ConsecutiveFrameProcess(LPdu) == TRUE) {
								DCAN_ResponseType = NoResponseFlag;
								CAN_TP_ConsecutiveTimeout = 0;
								CAN_TP_ConsecutiveFlag = FALSE;
						}
						CAN_CFG_DIAG_NewMsgFlag = FALSE;
						CAN_CFG_DIAG_NewFunMsgFlag = FALSE;
         }
			}
		}
	}
	else if (DCAN_ResponseType == UpdateFromAPPMsg)
	{
		COMM_CANTP_TX_SingleFrameProcess(LPdu);
        DCAN_ResponseType = NoResponseFlag;
        CAN_CFG_DIAG_NewMsgFlag = FALSE;
        CAN_CFG_DIAG_NewFunMsgFlag = FALSE;
	}
	else if ((LPdu->Length > 0) && (DCAN_ResponseType == FromLongTimeMsg))
	{
		COMM_CANTP_TX_SingleFrameProcess(LPdu);
        DCAN_ResponseType = NoResponseFlag;
        CAN_CFG_DIAG_NewMsgFlag = FALSE;
        CAN_CFG_DIAG_NewFunMsgFlag = FALSE;
	}

/*    if(releaseFlag == TRUE) {
        DCAN_ResponseType = NoResponseFlag;
    }
    CAN_CFG_DIAG_NewMsgFlag = FALSE;
    CAN_CFG_DIAG_NewFunMsgFlag = FALSE;*/
}

void COMM_CANTP_TX_3E_MsgProcess(void)
{
	CANPduType* LPdu = NULL;
	LPdu = COMM_CANTP_GetTxBuff2();
	if (DCAN_SID3E_ResponseType == SingleFrameFlag)
	{
		if (LPdu->Length <= 7)
		{
			COMM_CANTP_TX_SingleFrameProcess(LPdu);
		}
	}

	DCAN_SID3E_ResponseType = NoResponseFlag;
	CAN_CFG_DIAG_3E_NewMsgFlag = FALSE;
	CAN_CFG_DIAG_3E_NewFunMsgFlag = FALSE;
}


void COMM_CANTP_TX_SingleFrameProcess(CANPduType* LPdu)
{
	U8 i = 0;
	g_sendCANMsgInfo.DATA[0] = LPdu->Length;
	for(i = 0; i <= LPdu->Length; i++)
	{
			g_sendCANMsgInfo.DATA[i+1] = LPdu->DataPtr[i];
	}
	g_sendCANMsgInfo.DLC = LPdu->Length + 1;
    LPdu->Length = 0;
	COMM_CANTP_USDT_TX_SingleFrame(&g_sendCANMsgInfo);
}


void COMM_CANTP_USDT_TX_SingleFrame(CAN_MsgInfoType* Tx_Buff)
{
	g_sendCANMsgInfo.ID = Physical_USDT_CANID;
	g_sendCANMsgInfo.IDE = 0;
	g_sendCANMsgInfo.FDF = 0;
	COMM_CANTP_FrameFill(&g_sendCANMsgInfo);
	g_sendCANMsgInfo.DLC = 8;
	COMM_CAN_CFG_TX(&g_sendCANMsgInfo);
}


void COMM_CANTP_TX_FirstFrameProcess(CANPduType* LPdu)
{
	U8 i = 0;
	g_sendCANMsgInfo.DATA[0] = 0x10 + (((LPdu->Length) & 0xF00)>>16);
	g_sendCANMsgInfo.DATA[1] = LPdu->Length & 0xFF;
	for (i = 0; i < 6; i++)
	{
		g_sendCANMsgInfo.DATA[i+2] = LPdu->DataPtr[i];
	}
	LPdu->Cnt = 6;
	g_sendCANMsgInfo.DLC = 8;
	COMM_CANTP_USDT_TX_ConsecutiveFrame(&g_sendCANMsgInfo);
	CAN_TP_TPdu = LPdu;
}


U8 COMM_CANTP_TX_FlowCtrlFrameProcess(void)
{
	U8 STMin = 0x0A;
	U8 FlowCtrlHead;
	U8 BlockSize;
	U16 BUFFER_SIZE;
#if CAN_TP_CRC_CHECK
	BUFFER_SIZE = (U16)EFLS_WRITE_BUFFER_SIZE + 4;
#else
	BUFFER_SIZE = (U16)EFLS_WRITE_BUFFER_SIZE + 2;
#endif
	if (((g_recvCANMsgInfo.DATA[0] & 0xF0) >> 4) == 1)
	{
		if ((U16)(g_recvCANMsgInfo.DATA[0] & 0x0F) +  (U16)(g_recvCANMsgInfo.DATA[1]) > BUFFER_SIZE)
		{
			FlowCtrlHead = 0x32;
		}
        else if (g_sendCanDataRdy == FALSE)
		{
			FlowCtrlHead = 0x31;
		}
		else
		{
			FlowCtrlHead = 0x30;
		}
	}
	else
	{
		if (g_sendCanDataRdy == FALSE)
		{
			FlowCtrlHead = 0x31;
		}
		else
		{
			FlowCtrlHead = 0x30;
		}
	}
	if ((U16)(BUFFER_SIZE - 6) % 7 == 0)
	{
		BlockSize = (U8)(BUFFER_SIZE - 6) / 7;
	}
	else
	{
		BlockSize = (U8)(BUFFER_SIZE - 6) / 7 + 1;
	}
	g_sendCANMsgInfo.DATA[0] = FlowCtrlHead;
	g_sendCANMsgInfo.DATA[1] = BlockSize;
	g_sendCANMsgInfo.DATA[2] = STMin;
	g_sendCANMsgInfo.DLC = 3;
	g_sendCANMsgInfo.IDE = 0;
	g_sendCANMsgInfo.ID = Physical_USDT_CANID;
	COMM_CANTP_FrameFill(&g_sendCANMsgInfo);
	g_sendCANMsgInfo.DLC = 8;
	COMM_CAN_CFG_TX(&g_sendCANMsgInfo);
	return FlowCtrlHead;
}


bool COMM_CANTP_TX_ConsecutiveFrameProcess(CANPduType* LPdu)
{
	U8 i = 0;
  bool consecutiveFrameEndFlag = FALSE;

	LPdu = CAN_TP_TPdu;
	if (LPdu != NULL)
	{
		 g_sendCANMsgInfo.DATA[0] = (ConsecutiveFrame << 4) + ((LPdu->Cnt/7 + 1) & 0x0F);
		 for(i=0; (i < 7) && (LPdu->Cnt < LPdu->Length); i++)
		 {
				 g_sendCANMsgInfo.DATA[i+1] = LPdu->DataPtr[LPdu->Cnt];
				 LPdu->Cnt++;
		 }
		 g_sendCANMsgInfo.DLC = i + 1;
		 COMM_CANTP_USDT_TX_ConsecutiveFrame(&g_sendCANMsgInfo);
		 if (LPdu->Cnt >= LPdu->Length)
		 {
			 CAN_TP_TPdu = NULL;
			 LPdu->Cnt = 0;
			 LPdu->Length = 0;
			 consecutiveFrameEndFlag = TRUE;
		 }
	} 
	else 
	{
    consecutiveFrameEndFlag = TRUE;
  }

    return consecutiveFrameEndFlag;
}


void COMM_CANTP_USDT_TX_ConsecutiveFrame(CAN_MsgInfoType* LTempFrame)
{
	LTempFrame->ID = Physical_USDT_CANID;
	LTempFrame->IDE = 0;
	COMM_CANTP_FrameFill(LTempFrame);
	COMM_CAN_CFG_TX(LTempFrame);
}
