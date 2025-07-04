/*
 * DCAN.c
 * Xi'An ManHui Info. Science LLC
 * Created on: Nov 1, 2023
 * Modify on: Dec 26, 2023
 * Author: Xue Le
 * Modifier: He Jingchi
 * Update on: Jul 19, 2024
 */

#include "DCAN.h"
#include "BF7006BMxx_timer.h"
#include "BF7006BMxx_eflash.h"


bool g_time0IsBusy = FALSE;
bool DCAN_SID31_TaskPending;
U32 DCAN_MemAdr, DCAN_MemSize;
U32 DCAN_BlockStartAdr, DCAN_BlockMemTailSize;
U8 DCAN_CTRLMSG_STATUS;
DCAN_TaskStatus DCAN_TASK_STATUS;
//static U32 EraseStartAdd, EraseLength;
extern bool SERVICE_REQUEST_FLAG;
static DCAN_Session_Type Session_Mode = DefaultSession;
/////////////////static DCAN_Reset_Type Reset_Mode;
static DCAN_Security_Type Security_Type = KeyDefaultStatus;
static DCAN_CtrlMsg_Status CtrlMsg_Status = DefaultStatus;
static U8 DCAN_KeyTrailNum = 0;
static U16 DCAN_KeyFailTimer = DCAN_KeyTrial_MinDlyTimer;
static U16 DCAN_TestPresentTimer = DCAN_TestPresent_S3SeverTmr;
static U8 DCAN_SeedRequestAlready = 0;
static DCAN_TransData_Status DCAN_TransData_Statu = InCoMsgLenOrInvalidFmt;
static DCAN_TestPresentType DCAN_TestPresentStatu = PresentDefaultstatu;
static U8 DCAN_SeedRand = 0;
static DCAN_DTC_Info DCAN_DTC_Status = _DefaultStatus;

extern U8 KbFILE_SystemVulnerable;
extern bool SERVICE_REQUEST_FLAG;
extern bool SERVICE_REQUEST_FLAG2;
extern bool SERVICE_REQUEST_FLAG_OLD;

extern __IO bool CAN_CFG_DIAG_NewMsgFlag;
extern __IO bool CAN_CFG_DIAG_NewFunMsgFlag;
extern __IO bool CAN_CFG_DIAG_3E_NewMsgFlag;
extern __IO bool CAN_CFG_DIAG_3E_NewFunMsgFlag;

extern U8 DCAN_ResponseType;
extern bool CAN_TP_ConsecutiveFlag;

const U8 didDataF187[12] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF /* MN1234567890 */
};
const U8 didDataF18A[10] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF /* 0123456789 */
};
const U8 didDataF197[10] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF /* WPTC */
};
const U8 didDataF193[2] = {
    0xFF, 0xFF /* 0101 */
};
const U8 didDataF195[2] = {
    0xFF, 0xFF /* 0101 */
};


EepromMemList eepromMemList = {0};

SID19_Resp dtc19_resp = {0};
SID19_01_DataPack sid19_01_datapack = {0};
SID19_04_DataPack sid19_04_datapack = {0};
SID19_06_DataPack sid19_06_datapack = {0};

bool m_bx1902Earsed;
bool m_bx1904Earsed;
bool m_bx1906Earsed;

U8* _p0x190ABUF;
static U8 _0x1902Buf[EEPROM_SECTOR_SIZE / 4];
static U8 _0x1904Buf[EEPROM_SECTOR_SIZE];
static U8 _0x1906Buf[DTC_NUMBER];
static U8 _0x190ABuf[DCAN_ORIGINAL_DTC_COUNT*4];//22 dtcs, per dtc has 4bytes(tail 0xFF byte use to 4byte align)
static DCAN_ControlDTC_Type ControlDTCSet = ControlDTC_Accepted;

/*void test()
{

    U8 buf[64] = {0x01, 0x02, 0x03, 0x04};
    ErrorStatus ret = ERROR;

    ret = EFLS_DRV_Write_Data_To_Eemprom(DIDMEM_START_ADD, buf, 64);
    if (ret == SUCCESS) {
        EFLS_DRV_Read_Data_From_Eemprom(DIDMEM_START_ADD, (U8 *)&(eepromMemList.didMemList), sizeof(eepromMemList.didMemList));
    }

    EFLS_DRV_ONLYWrite_FLAG_Data(APP_VALID_FLAG_ADD, DCAN_APPVALIDFLAG, 0);

    U8 Cal[4];
    U8 Key[4];
    U8 KeyReceive[4];
    U8 level = 9;

    Cal[0] = 0x12 ^ 0xE4;
    Cal[1] = 0x16 ^ 0x2F;
    Cal[2] = 0xE1 ^ 0x45;
    Cal[3] = 0X78 ^ 0x92;

    if(level == 1) {
            Key[0]=((Cal[2] & 0xF0) << 4) | (Cal[3] & 0xF0);
            Key[1]=((Cal[3] & 0x2F) << 2) | (Cal[1] & 0x03);
            Key[2]=((Cal[1] & 0xFC) >> 2) | (Cal[0] & 0xC0);
            Key[3]=((Cal[0] & 0x0F) << 4) | (Cal[2] & 0x0F);
        } else if(level == 9) {
            Key[0]=((Cal[2] & 0x0F) << 4) | (Cal[1] & 0x0F);
            Key[1]=((Cal[0] & 0x0F) << 4) | (Cal[3] & 0x0F);
            Key[2]=((Cal[0] & 0xF0) >> 2) | ((Cal[2] & 0xF0) >> 4);
            Key[3]=((Cal[3] & 0xF0) >> 4) | ((Cal[1] & 0xF0) >> 4);
        }

    return;
}*/

void DCAN_Init(void)
{
	COMM_CANTP_Service_Request(CLEAR_REQUEST);
	COMM_CANTP_Service_3E_Request(CLEAR_REQUEST);
	DCAN_SID31_TaskPending = FALSE;
  //DCAN_Timer0_Init();
	DCAN_TASK_STATUS = Complete;
	
	//0x14/0x19 related
	DCAN_CTRLMSG_STATUS = 1;
	
	m_bx1902Earsed = false;
	memset(_0x1902Buf, 0U, sizeof(_0x1902Buf));
	dtc19_resp.DTC02_DataPack.DTCAndStatusRecord = _0x1902Buf;
	
	m_bx1904Earsed = false;
	memset(_0x1904Buf, 0U, sizeof(_0x1904Buf));
	sid19_04_datapack.DtcSnapshotRecord01.SnapshotData = _0x1904Buf;
	sid19_04_datapack.DtcSnapshotRecord02.DTCSnapshotRecordNumber = 0x0;
	sid19_04_datapack.DtcSnapshotRecord02.DTCSnapshotRecordNumberOfIdentifiers = 0xff;
	sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte1 = 0x0; 
	sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte2 = 0x0;
	
	m_bx1906Earsed = false;
	memset(_0x1906Buf, 0U, sizeof(_0x1906Buf));
	sid19_06_datapack.DTCMaskRecord.dtcmaskrecord = _0x1906Buf;
	sid19_06_datapack.DTCExtendedDataRecord.DTCExtendedDataRecordNumber = 0x00;
	sid19_06_datapack.DTCExtendedDataRecord.DTC_Number = 0x0;
	sid19_06_datapack.DTCExtendedDataRecord.DTC_Undetermined = 0x0;
	
	memset(_0x190ABuf, 0U, sizeof(_0x190ABuf));
	_p0x190ABUF = _0x190ABuf;
  //0x14/0x19 end_
	
	EFLS_DRV_Read_Data_From_Eemprom(DIDMEM_START_ADD, (U8 *)&(eepromMemList.didMemList), sizeof(eepromMemList.didMemList) / 4);
	//test();
}


/*void DCAN_Timer0_Start_Once(void)
{
    timer_init(TIMER0, TIMER_INT_ENABLE | TIMER_CLK_SYS_DIV2 | TIMER_ENABLE, 0x3E80);
}*/


void DCAN_NRC78_Send_Task(void *device, uint32_t wpara, uint32_t lpara)
{
	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
	if ( (DCAN_TASK_STATUS == Starting)
		&& (SERVICE_REQUEST_FLAG == TRUE)
		&& (DCAN_TransData_Statu != TransferCmplt)
		&& (DCAN_TransData_Statu !=TransDataNormal)
		&& (LRxPdu->DataPtr[0] == SID31) )
	{
		CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
		CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
		LTxPdu->Length = 0;
		LTxPdu->DataPtr[LTxPdu->Length++] = 0x7F;
		LTxPdu->DataPtr[LTxPdu->Length++] = LRxPdu->DataPtr[0];
		LTxPdu->DataPtr[LTxPdu->Length++] = 0x78;
		COMM_CANTP_TX_MsgProcess();
	}
}


void DCAN_Dtrmn3EService(void)
{
	//if( ((SERVICE_REQUEST_FLAG2 == TRUE) && (CAN_CFG_DIAG_NewMsgFlag == TRUE))
		//|| ((SERVICE_REQUEST_FLAG2 == TRUE) && ( CAN_CFG_DIAG_NewFunMsgFlag == TRUE)) )
  if(SERVICE_REQUEST_FLAG2 == TRUE)
	{
	    CANPduType *LRxPdu2 = COMM_CANTP_GetRxBuff2();
		switch(LRxPdu2->DataPtr[0])
		{
			case SID3E:
				DCAN_PerformService3E();
				break;
			default:
				break;
		}
		COMM_CANTP_Service_3E_Request(CLEAR_REQUEST);
		CAN_CFG_DIAG_3E_NewMsgFlag = FALSE;
    CAN_CFG_DIAG_3E_NewFunMsgFlag = FALSE;
	}
}


void DCAN_DtrmnService(void)
{
	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
  DCAN_SeedRand += 7;
	
	if (DCAN_KeyTrailNum >= DCAN_KeyTrial_MAX_Num)
	{
		if (DCAN_KeyFailTimer <= 0)
		{
			DCAN_KeyFailTimer = 0;
			DCAN_KeyTrailNum--;
      Security_Type = KeyDefaultStatus;
		}
		else
		{
			DCAN_KeyFailTimer -= 10;
		}
	}
	if (SERVICE_REQUEST_FLAG_OLD == TRUE)
	{
		if (DCAN_TestPresentTimer <= 0)
		{
			Session_Mode = DefaultSession;
			DCAN_SeedRequestAlready = 0;
			Security_Type = KeyDefaultStatus;
		}
		else
		{
			DCAN_TestPresentTimer -= 10;
		}
	}
	if ( (SERVICE_REQUEST_FLAG == TRUE) && (CAN_CFG_DIAG_NewMsgFlag == TRUE) && (CAN_TP_ConsecutiveFlag == FALSE) )
	{
		DCAN_TASK_STATUS = Starting;
		switch(LRxPdu->DataPtr[0])
		{
			case SID10:
				DCAN_PerformService10();
				break;
			case SID11:
				DCAN_PerformService11();
				break;
			case SID14:
				DCAN_PerformService14();
				break;
			case SID19:
				DCAN_PerformService19();
				break;						
			case SID22:
				DCAN_PerformService22();
				break;
			case SID2E:
				DCAN_PerformService2E();
				break;
			case SID27:
				DCAN_PerformService27();
				break;
			case SID28:
				DCAN_PerformService28();
				break;
			case SID85:
				DCAN_PerformService85();
				break;
			default:
				DCAN_GenericNegResponse(LRxPdu->DataPtr[0], DCAN_ServiceNotSupported);
				break;
		}
		DCAN_TASK_STATUS = Complete;
		COMM_CANTP_Service_Request(CLEAR_REQUEST);
		CAN_CFG_DIAG_NewMsgFlag = FALSE;
		
	}
	else if ( (SERVICE_REQUEST_FLAG == TRUE) && ( CAN_CFG_DIAG_NewFunMsgFlag == TRUE) && (CAN_TP_ConsecutiveFlag == FALSE) )
	{
		DCAN_TASK_STATUS = Starting;
		switch(LRxPdu->DataPtr[0])
		{
			case SID10:
				DCAN_PerformService10();
				break;
			case SID22:
					DCAN_PerformService22();
					break;
			case SID11:
				DCAN_PerformService11();
				break;
			case SID28:
				DCAN_PerformService28();
				break;
			case SID85:
					DCAN_PerformService85();
					break;
			default:
				break;
		}
		DCAN_TASK_STATUS = Complete;
		COMM_CANTP_Service_Request(CLEAR_REQUEST);
		CAN_CFG_DIAG_NewFunMsgFlag = FALSE;
	}
}


void DCAN_PerfmSoftReset(void)
{
    Disable_Irq();
    Reset_system();
}

void DCAN_GenericPosResponse(U8 SID)
{
	if (SID == SID3E)
	{
		CANPduType *LRxPdu2 = COMM_CANTP_GetRxBuff2();
		CANPduType *LTxPdu2 = COMM_CANTP_GetTxBuff2();
		LTxPdu2->Length = 0;
		LTxPdu2->DataPtr[LTxPdu2->Length++] = SID + 0x40;
		LTxPdu2->DataPtr[LTxPdu2->Length++] = LRxPdu2->DataPtr[1] & 0x7F;
		if ((LRxPdu2->DataPtr[1] & 0x80) != 0x80)
		{
			COMM_CANTP_TX_3E_MsgProcess();
		}
	}
	else
	{
		CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
		CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
		if((LRxPdu->DataPtr[1] & 0x80) != 0x80) 
		{
				LTxPdu->Length = 0;
				LTxPdu->DataPtr[LTxPdu->Length++] = SID + 0x40;
				LTxPdu->DataPtr[LTxPdu->Length++] = LRxPdu->DataPtr[1] & 0x7F;

				COMM_CANTP_TX_MsgProcess();
		}
	}
}

void DCAN_SID10_PosResponse(U8 SID)
{

	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();

    if((LRxPdu->DataPtr[1] & 0x80) != 0x80) {
        LTxPdu->Length = 0;
        LTxPdu->DataPtr[LTxPdu->Length++] = SID10 + 0x40;
        LTxPdu->DataPtr[LTxPdu->Length++] = LRxPdu->DataPtr[1] & 0x7F;
        LTxPdu->DataPtr[LTxPdu->Length++] = P2_CAN_SERVER_MAX_HIGH;
        LTxPdu->DataPtr[LTxPdu->Length++] = P2_CAN_SERVER_MAX_LOW;
        LTxPdu->DataPtr[LTxPdu->Length++] = P2_Enhanced_CAN_SERVER_MAX_HIGH;
        LTxPdu->DataPtr[LTxPdu->Length++] = P2_Enhanced_CAN_SERVER_MAX_LOW;

        COMM_CANTP_TX_MsgProcess();
    }
}

void DCAN_SID22_PosResponse(U8 SID, const U8 *buf, U8 len)
{
    CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
    CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
    LTxPdu->Length = 0;
    LTxPdu->DataPtr[LTxPdu->Length++] = SID + 0x40;
    LTxPdu->DataPtr[LTxPdu->Length++] = LRxPdu->DataPtr[1];
    LTxPdu->DataPtr[LTxPdu->Length++] = LRxPdu->DataPtr[2];

    while(len != 0) {
        LTxPdu->DataPtr[LTxPdu->Length++] = *buf++;
        len--;
    }

    COMM_CANTP_TX_MsgProcess();

    return;
}

void DCAN_SID2E_PosResponse(U8 SID)
{
    CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
    CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
    LTxPdu->Length = 0;
    LTxPdu->DataPtr[LTxPdu->Length++] = SID + 0x40;
    LTxPdu->DataPtr[LTxPdu->Length++] = LRxPdu->DataPtr[1];
    LTxPdu->DataPtr[LTxPdu->Length++] = LRxPdu->DataPtr[2];

    COMM_CANTP_TX_MsgProcess();

    return;
}

void DCAN_GenericNegResponse(U8 SID, U8 NRC)
{
	if (SID == SID3E)
	{
		CANPduType *LTxPdu = COMM_CANTP_GetTxBuff2();
		LTxPdu->Length = 0;
        LTxPdu->DataPtr[LTxPdu->Length++] = 0x7F;
		LTxPdu->DataPtr[LTxPdu->Length++] = SID;
        LTxPdu->DataPtr[LTxPdu->Length++] = NRC;
        COMM_CANTP_TX_3E_MsgProcess();
	}
    else
    {
    	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
    	LTxPdu->Length = 0;
    	LTxPdu->DataPtr[LTxPdu->Length++] = 0x7F;
    	LTxPdu->DataPtr[LTxPdu->Length++] = SID;
    	LTxPdu->DataPtr[LTxPdu->Length++] = NRC;
    	COMM_CANTP_TX_MsgProcess();
    }
}


void DCAN_NRC78_Respose(U8 SID)
{
	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
	LTxPdu->Length = 0;
	LTxPdu->DataPtr[LTxPdu->Length++] = 0x7F;
	LTxPdu->DataPtr[LTxPdu->Length++] = SID;
	LTxPdu->DataPtr[LTxPdu->Length++] = 0x78;
	OSTK_Delayus(1000);
	COMM_CANTP_TX_MsgProcess();

    if((SID == SID2E) || (SID == SID31)) {
        DCAN_ResponseType = SingleFrameFlag;
    }
}


void DCAN_SID27_SendSeed(U8 SID, U8 level)
{
	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
#if(N2S_DEBUG == 0)
    U8 index = 0;
    U8 Seed[UDS_SECURITY_SEEDNUM];
	for (index = 0; index < UDS_SECURITY_SEEDNUM; index++)
	{
		Seed[index] = (U8)rand();
	}
#endif
	LTxPdu->Length = 0;
	LTxPdu->DataPtr[LTxPdu->Length++] = SID + 0x40;
	LTxPdu->DataPtr[LTxPdu->Length++] = LRxPdu->DataPtr[1] & 0x7F;

#if N2S_DEBUG
		LTxPdu->DataPtr[LTxPdu->Length++] = 0x12;
		LTxPdu->DataPtr[LTxPdu->Length++] = 0x16;
		LTxPdu->DataPtr[LTxPdu->Length++] = 0xE1;
		LTxPdu->DataPtr[LTxPdu->Length++] = 0x78;
#else
		if(((Security_Type == KeyPASSLevel1) && (level == 1))
			 || ((Security_Type == KeyPASSLevel9) && (level == 9))) {
				LTxPdu->DataPtr[LTxPdu->Length++] = 0;
				LTxPdu->DataPtr[LTxPdu->Length++] = 0;
				LTxPdu->DataPtr[LTxPdu->Length++] = 0;
				LTxPdu->DataPtr[LTxPdu->Length++] = 0;
		} else {
				Security_Type = KeyDefaultStatus;
				LTxPdu->DataPtr[LTxPdu->Length++] = Seed[0];
				LTxPdu->DataPtr[LTxPdu->Length++] = Seed[1];
				LTxPdu->DataPtr[LTxPdu->Length++] = DCAN_SeedRand;
				LTxPdu->DataPtr[LTxPdu->Length++] = Seed[3];
		}
#endif

	COMM_CANTP_TX_MsgProcess();
}


DCAN_Security_Type DCAN_SID27_VerifyKey(U8 SID, U8 level)
{
		U8 Cal[4];
		U8 Key[4];
    U8 KeyReceive[4];
		CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
		CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
    DCAN_Security_Type ret = KeyDefaultStatus;

    KeyReceive[0] = LRxPdu->DataPtr[2];
    KeyReceive[1] = LRxPdu->DataPtr[3];
    KeyReceive[2] = LRxPdu->DataPtr[4];
    KeyReceive[3] = LRxPdu->DataPtr[5];

    Cal[0] = LTxPdu->DataPtr[2] ^ 0xE4;
    Cal[1] = LTxPdu->DataPtr[3] ^ 0x2F;
    Cal[2] = LTxPdu->DataPtr[4] ^ 0x45;
    Cal[3] = LTxPdu->DataPtr[5] ^ 0x92;

    if(level == 1) {
        Key[0]=((Cal[2] & 0xF0) << 4) | (Cal[3] & 0xF0);
        Key[1]=((Cal[3] & 0x2F) << 2) | (Cal[1] & 0x03);
        Key[2]=((Cal[1] & 0xFC) >> 2) | (Cal[0] & 0xC0);
        Key[3]=((Cal[0] & 0x0F) << 4) | (Cal[2] & 0x0F);
    } else if(level == 9) {
        Key[0]=((Cal[2] & 0x0F) << 4) | (Cal[1] & 0x0F);
        Key[1]=((Cal[0] & 0x0F) << 4) | (Cal[3] & 0x0F);
        Key[2]=((Cal[0] & 0xF0) >> 2) | ((Cal[2] & 0xF0) >> 4);
        Key[3]=((Cal[3] & 0xF0) >> 4) | ((Cal[1] & 0xF0) >> 4);
    }

	if ((KeyReceive[0] == Key[0]) && (KeyReceive[1] == Key[1]) && (KeyReceive[2] == Key[2]) && (KeyReceive[3] == Key[3]))
	{
        if(level == 1) {
            ret = KeyPASSLevel1;
        } else if(level == 9) {
            ret = KeyPASSLevel9;
        }
	}
	else
	{
    DCAN_KeyTrailNum++;
		if (DCAN_KeyTrailNum >= DCAN_KeyTrial_MAX_Num)
		{
			ret = ReachedMaxTrailNum;
      DCAN_KeyFailTimer = DCAN_KeyTrial_MinDlyTimer;
		}
		else
		{
			ret = InvalidKey;
		}
	}

    return ret;
}


void DCAN_PerformService10(void)
{
  DCAN_Session_Type sessionMode = DefaultSession;
	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
	if (LRxPdu->Length != 2)
	{
		sessionMode = MsgLenInCorrOrInvalidFormat;
	}
	else
	{
		switch (LRxPdu->DataPtr[1] & 0x7F)
		{
			case 0x01:
				sessionMode = DefaultSession;
			  ControlDTCSet = ControlDTC_Accepted;
				break;
			case 0x02:
				if(Session_Mode == DefaultSession) {
						sessionMode = Session_ConditionsNotCorrect;
				}
				else {
            sessionMode = ProgrammingSession;
					
						//LTxPdu->Length = 0;
						//LTxPdu->DataPtr[LTxPdu->Length++] = SID10 + 0x40;
						//LTxPdu->DataPtr[LTxPdu->Length++] = LRxPdu->DataPtr[1] & 0x7F;
						//COMM_CANTP_TX_MsgProcess();
						DCAN_NRC78_Respose(SID10);
						Jump2Boot();
				}
				break;
			case 0x03:
				if(Session_Mode == ProgrammingSession) {
						sessionMode = Session_ConditionsNotCorrect;
				} else {
						sessionMode = ExtendedDiagSession;
				}
				break;
			default:
				sessionMode = SubFunctiNoSupprt;
				break;
		}
	}
	switch (sessionMode)
	{
		case MsgLenInCorrOrInvalidFormat:
			DCAN_GenericNegResponse(SID10, DCAN_MsgLenOrInvalidFormat);
			break;
		case SubFunctiNoSupprt:
			DCAN_GenericNegResponse(SID10, DCAN_SubFuncNotSupport);
			break;
		case Session_ConditionsNotCorrect:
				DCAN_GenericNegResponse(SID10, DCAN_ConditionNotCorrect);
				break;
		case DefaultSession:
			SERVICE_REQUEST_FLAG_OLD = FALSE;
			DCAN_SID10_PosResponse(SID10);
			break;
		case ProgrammingSession:
			SERVICE_REQUEST_FLAG_OLD = SERVICE_REQUEST_FLAG;
			DCAN_TestPresentTimer = DCAN_TestPresent_S3SeverTmr;
			DCAN_SID10_PosResponse(SID10);
			break;
		case ExtendedDiagSession:
			SERVICE_REQUEST_FLAG_OLD = SERVICE_REQUEST_FLAG;
			DCAN_TestPresentTimer = DCAN_TestPresent_S3SeverTmr;
			DCAN_SID10_PosResponse(SID10);
			break;
		case SafetySysDiagSession:
			SERVICE_REQUEST_FLAG_OLD = SERVICE_REQUEST_FLAG;
			DCAN_SID10_PosResponse(SID10);
			break;
		default:
			break;
	}

    if((sessionMode == DefaultSession) || 
			(sessionMode == ExtendedDiagSession)) {
        Session_Mode = sessionMode;
        DCAN_SeedRequestAlready = 0;
        if((Security_Type == KeyPASSLevel1) || (Security_Type == KeyPASSLevel9)) {
            Security_Type = KeyDefaultStatus;
        }
    }

    return;
}


void DCAN_PerformService11(void)
{
	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
	if (DCAN_TestPresentTimer > 0)
	{
		DCAN_TestPresentTimer = DCAN_TestPresent_S3SeverTmr;
	}
	else
	{
		Session_Mode = DefaultSession;
		DCAN_SeedRequestAlready = 0;
		if((Security_Type == KeyPASSLevel1) || (Security_Type == KeyPASSLevel9)) {
				Security_Type = KeyDefaultStatus;
		}
	}
	if (LRxPdu->Length != 2)
	{
		DCAN_GenericNegResponse(SID11, DCAN_MsgLenOrInvalidFormat);
	}
	else
	{
		switch (LRxPdu->DataPtr[1] & 0x7F)
		{
			case 0x01:
				//Reset_Mode = HadrReset;
				Session_Mode = DefaultSession;
        LTxPdu->Length = 0;
				LTxPdu->DataPtr[LTxPdu->Length++] = SID11 + 0x40;
				LTxPdu->DataPtr[LTxPdu->Length++] = LRxPdu->DataPtr[1] & 0x7F;
				COMM_CANTP_TX_MsgProcess();
				OSTK_Delayus(10000);
				Session_Mode = DefaultSession;
			  ControlDTCSet = ControlDTC_Accepted;
				DCAN_PerfmSoftReset();
				break;
			case 0x02:
				//Reset_Mode = KeyOffOnReset;
				Session_Mode = DefaultSession;
				break;
			case 0x03:
				//Reset_Mode = SoftReset;
				Session_Mode = DefaultSession;
        LTxPdu->Length = 0;
				LTxPdu->DataPtr[LTxPdu->Length++] = SID11 + 0x40;
				LTxPdu->DataPtr[LTxPdu->Length++] = LRxPdu->DataPtr[1] & 0x7F;
				COMM_CANTP_TX_MsgProcess();
				OSTK_Delayus(10000);
				Session_Mode = DefaultSession;
			  ControlDTCSet = ControlDTC_Accepted;
				DCAN_PerfmSoftReset();
				break;
			default:
				DCAN_GenericNegResponse(SID11, DCAN_SubFuncNotSupport);
				break;
		}
	}
}

void DCAN_PerformService22(void)
{
    U16 readDid = 0;
    DCAN_ReadDataById_Type readDataById = ReadDataById_Accepted;
    CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
    CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();

    if(DCAN_TestPresentTimer > 0) {
        DCAN_TestPresentTimer = DCAN_TestPresent_S3SeverTmr;
    } else {
        Session_Mode = DefaultSession;
        DCAN_SeedRequestAlready = 0;
        if((Security_Type == KeyPASSLevel1) || (Security_Type == KeyPASSLevel9)) {
            Security_Type = KeyDefaultStatus;
        }
    }

    if(LRxPdu->Length != 3) {
        readDataById = ReadDataById_MsgLenOrInvalidFmt;
    } else if((Session_Mode != DefaultSession) && (Session_Mode != ExtendedDiagSession)) {
        readDataById = ReadDataById_ConditionsNotCorrect;
    } else {
        readDid = (U16)(LRxPdu->DataPtr[1] << 8) + (U16)(LRxPdu->DataPtr[2]);
        switch(readDid) {
            case 0xF187:
                DCAN_SID22_PosResponse(SID22, didDataF187, sizeof(didDataF187));
                break;
            case 0xF18A:
                DCAN_SID22_PosResponse(SID22, didDataF18A, sizeof(didDataF18A));
                break;
            case 0xF197:
                DCAN_SID22_PosResponse(SID22, didDataF197, sizeof(didDataF197));
                break;
            case 0xF193:
                DCAN_SID22_PosResponse(SID22, didDataF193, sizeof(didDataF193));
                break;
            case 0xF195:
                DCAN_SID22_PosResponse(SID22, didDataF195, sizeof(didDataF195));
                break;
            case 0xF18C:
                DCAN_SID22_PosResponse(SID22, eepromMemList.didMemList.did_F18C, sizeof(eepromMemList.didMemList.did_F18C));
                break;
            case 0xF190:
                DCAN_SID22_PosResponse(SID22, eepromMemList.didMemList.did_F190, sizeof(eepromMemList.didMemList.did_F190));
                break;
            case 0xF15B:
                DCAN_SID22_PosResponse(SID22, eepromMemList.didMemList.did_F15B, sizeof(eepromMemList.didMemList.did_F15B));
                break;
            default:
                readDataById = ReadDataById_ReqOutOfRange;
                break;
        }
    }

    switch(readDataById) {
        case ReadDataById_MsgLenOrInvalidFmt:
            DCAN_GenericNegResponse(SID22, DCAN_MsgLenOrInvalidFormat);
            break;
        case ReadDataById_ConditionsNotCorrect:
            DCAN_GenericNegResponse(SID22, DCAN_ConditionNotCorrect);
            break;
        case ReadDataById_ReqOutOfRange:
            DCAN_GenericNegResponse(SID22, DCAN_RequestOutOfRange);
            break;
//        case ReadDataById_SecAccessDenied:
//            DCAN_GenericNegResponse(SID22, DCAN_SecurityAccessDenied);
//            break;
        default:
            break;
    }

    return;
}

void DCAN_PerformService2E(void)
{
    U8 i;
    U16 writeDid = 0;
    DCAN_WriteDataById_Type writeDataById = WriteDataById_Accepted;
    CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
    CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();

    if(DCAN_TestPresentTimer > 0) {
        DCAN_TestPresentTimer = DCAN_TestPresent_S3SeverTmr;
    } else {
        Session_Mode = DefaultSession;
        DCAN_SeedRequestAlready = 0;
        if((Security_Type == KeyPASSLevel1) || (Security_Type == KeyPASSLevel9)) {
            Security_Type = KeyDefaultStatus;
        }
    }

    if(LRxPdu->Length <= 3) {
        writeDataById = WriteDataById_MsgLenOrInvalidFmt;
    } else if((Session_Mode != ProgrammingSession) && (Session_Mode != ExtendedDiagSession)) {
        writeDataById = WriteDataById_ConditionsNotCorrect;
    } else {
        writeDid = (U16)(LRxPdu->DataPtr[1] << 8) + (U16)(LRxPdu->DataPtr[2]);
        switch(writeDid) {
					case 0xF190:
                if(LRxPdu->Length - 3 != sizeof(eepromMemList.didMemList.did_F190)) {
                    writeDataById = WriteDataById_MsgLenOrInvalidFmt;
                }
#if SECURITY_ACCESS_AVAILABLE
                else if((Security_Type != KeyPASSLevel1) && (Security_Type != KeyPASSLevel9)) {
                    writeDataById = WriteDataById_SecAccessDenied;
                }
#endif
                else {
                    for(i = 0; i < sizeof(eepromMemList.didMemList.did_F190); i++) {
                        eepromMemList.didMemList.did_F190[i] = LRxPdu->DataPtr[3 + i];
                    }
                    DCAN_NRC78_Respose(SID2E);
                    if(EFLS_DRV_Write_Data_To_Eemprom(DIDMEM_START_ADD, (U8 *)&(eepromMemList.didMemList), sizeof(eepromMemList.didMemList)) == ERROR) {
                        writeDataById = WriteDataById_GenProgrammFail;
                    }
                }
                break;
            case 0xF15A:
                if(LRxPdu->Length - 3 != sizeof(eepromMemList.didMemList.did_F15A)) {
                    writeDataById = WriteDataById_MsgLenOrInvalidFmt;
                }
#if SECURITY_ACCESS_AVAILABLE
                else if(Security_Type != KeyPASSLevel9) {
                    writeDataById = WriteDataById_SecAccessDenied;
                }
#endif
                else {
                    for(i = 0; i < sizeof(eepromMemList.didMemList.did_F15A); i++) {
                        eepromMemList.didMemList.did_F15A[i] = LRxPdu->DataPtr[3 + i];
                    }
                    DCAN_NRC78_Respose(SID2E);
                    if(EFLS_DRV_Write_Data_To_Eemprom(DIDMEM_START_ADD, (U8 *)&(eepromMemList.didMemList), sizeof(eepromMemList.didMemList)) == ERROR) {
                        writeDataById = WriteDataById_GenProgrammFail;
                    }
                }
                break;
                case 0x008C:
                if(LRxPdu->Length - 3 != sizeof(eepromMemList.didMemList.did_F18C)) {
                    writeDataById = WriteDataById_MsgLenOrInvalidFmt;
                }
#if SECURITY_ACCESS_AVAILABLE
                else if((Security_Type != KeyPASSLevel1) && (Security_Type != KeyPASSLevel9)) {
                    writeDataById = WriteDataById_SecAccessDenied;
                }
#endif
                else {
                    for(i = 0; i < sizeof(eepromMemList.didMemList.did_F18C); i++) {
                        eepromMemList.didMemList.did_F18C[i] = LRxPdu->DataPtr[3 + i];
                    }
                    DCAN_NRC78_Respose(SID2E);
                    if(EFLS_DRV_Write_Data_To_Eemprom(DIDMEM_START_ADD, (U8 *)&(eepromMemList.didMemList), sizeof(eepromMemList.didMemList)) == ERROR) {
                        writeDataById = WriteDataById_GenProgrammFail;
                    }
                }
                break;
            default:
                writeDataById = WriteDataById_ReqOutOfRange;
                break;
        }
    }

    switch(writeDataById) {
        case WriteDataById_MsgLenOrInvalidFmt:
            DCAN_GenericNegResponse(SID2E, DCAN_MsgLenOrInvalidFormat);
            break;
        case WriteDataById_ConditionsNotCorrect:
            DCAN_GenericNegResponse(SID2E, DCAN_ConditionNotCorrect);
            break;
        case WriteDataById_ReqOutOfRange:
            DCAN_GenericNegResponse(SID2E, DCAN_RequestOutOfRange);
            break;
        case WriteDataById_SecAccessDenied:
            DCAN_GenericNegResponse(SID2E, DCAN_SecurityAccessDenied);
            break;
        case WriteDataById_GenProgrammFail:
            DCAN_GenericNegResponse(SID2E, DCAN_GeneralProgrammingFail);
            break;
        case WriteDataById_Accepted:
            DCAN_SID2E_PosResponse(SID2E);
            break;
        default:
            break;
    }

    return;
}



void DCAN_PerformService27(void)
{
	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
  DCAN_Security_Type securityType = KeyDefaultStatus;

	if (DCAN_TestPresentTimer > 0)
	{
		DCAN_TestPresentTimer = DCAN_TestPresent_S3SeverTmr;
	}
	else
	{
			Session_Mode = DefaultSession;
			DCAN_SeedRequestAlready = 0;
			if((Security_Type == KeyPASSLevel1) || (Security_Type == KeyPASSLevel9)) {
					Security_Type = KeyDefaultStatus;
			}
	}	
	if ((LRxPdu->Length != 2) && (LRxPdu->Length != 6))
	{
		securityType = IncorrectMsgLenOrInvalidFormat;
	}
	else if (Session_Mode != ProgrammingSession && Session_Mode != ExtendedDiagSession)
	{
     securityType = ConditionsNotCorrect;
	}
	else
	{
		switch (LRxPdu->DataPtr[1] & 0x7F)
		{
			case 0x01:
					if(Security_Type == ReachedMaxTrailNum) {
							securityType = FailKeyTrialDelayTimeNotReached;
					} else {
						DCAN_SeedRequestAlready = 1;
						securityType = SeedRequestLevel1;
          }
				break;
			case 0x02:
				if (DCAN_SeedRequestAlready != 1)
				{
					securityType = RequestSequenceError;
				}
				else
				{
					securityType = DCAN_SID27_VerifyKey(SID27, DCAN_SeedRequestAlready);
				}
        DCAN_SeedRequestAlready = 0;
				break;
			case 0x09:
					if(Security_Type == ReachedMaxTrailNum) {
							securityType = FailKeyTrialDelayTimeNotReached;
					} else {
						DCAN_SeedRequestAlready = 9;
						securityType = SeedRequestLevel9;
          }
				break;
			case 0x0A:
				if (DCAN_SeedRequestAlready != 9)
				{
					securityType = RequestSequenceError;
				}
				else
				{
					securityType = SendKey;
					securityType = DCAN_SID27_VerifyKey(SID27, DCAN_SeedRequestAlready);
				}
        DCAN_SeedRequestAlready = 0;
				break;
			default:
				securityType = SubFuncNotSupported;
				break;
		}
	}
	switch (securityType)
	{
		case KeyPASSLevel1:
    case KeyPASSLevel9:
      Security_Type = securityType;
			DCAN_GenericPosResponse(SID27);
			break;
		case SeedRequestLevel1:
    case SeedRequestLevel9:
			DCAN_SID27_SendSeed(SID27, DCAN_SeedRequestAlready);
			break;
		case ServNoSupportInActvSess:
			DCAN_GenericNegResponse(SID27, DCAN_ServNoSupportInActvSession);
			break;
		case SubFuncNotSupported:
			DCAN_GenericNegResponse(SID27, DCAN_SubFuncNotSupport);
			break;
		case ReachedMaxTrailNum:
      Security_Type = securityType;
			DCAN_GenericNegResponse(SID27, DCAN_ReachedMaxTrailNum);
			break;
		case InvalidKey:
			DCAN_GenericNegResponse(SID27, DCAN_InvalidKey);
			break;
		case FailKeyTrialDelayTimeNotReached:
			DCAN_GenericNegResponse(SID27, DCAN_ReqTimeDlyNotExpired);
			break;
		case RequestSequenceError:
			DCAN_GenericNegResponse(SID27, DCAN_RequestSequenceError);
			break;
		case ConditionsNotCorrect:
			DCAN_GenericNegResponse(SID27, DCAN_ConditionNotCorrect);
			break;
		case IncorrectMsgLenOrInvalidFormat:
			DCAN_GenericNegResponse(SID27, DCAN_MsgLenOrInvalidFormat);
			break;
		default:
			break;
	}

}


void DCAN_PerformService28(void)
{
	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
	CtrlMsg_Status = DefaultStatus;
	if (DCAN_TestPresentTimer > 0)
	{
		DCAN_TestPresentTimer = DCAN_TestPresent_S3SeverTmr;
	}
	else
	{
		Session_Mode = DefaultSession;
		DCAN_SeedRequestAlready = 0;
		if((Security_Type == KeyPASSLevel1) || (Security_Type == KeyPASSLevel9)) {
				Security_Type = KeyDefaultStatus;
		}
	}

	if (LRxPdu->Length != 3)
	{
		CtrlMsg_Status = InMsgLenOrInvalidFmt;
	}
	else if (Session_Mode != ExtendedDiagSession)
	{
		CtrlMsg_Status = ServNSupptInActSession;
	}
	else
	{
		switch(LRxPdu->DataPtr[1] & 0x7F)
		{
			case 0x00:
				switch(LRxPdu->DataPtr[2])
					{
						case 0x01:
            case 0x03:
							CtrlMsg_Status = EnRXEnTXAppMsg;
							break;
						default:
							CtrlMsg_Status = RestOuOfRange;
							break;
					}
				break;
			case 0x01:
				switch(LRxPdu->DataPtr[2])
					{
						case 0x01:
            case 0x03:
							CtrlMsg_Status = EnRXDisTXAppMsg;
							break;
						default:
							CtrlMsg_Status = RestOuOfRange;
							break;
					}
				break;
			case 0x02:
				switch(LRxPdu->DataPtr[2])
					{
						case 0x01:
            case 0x03:
							CtrlMsg_Status = DisRXEnTXAppMsg;
							break;
						default:
							CtrlMsg_Status = RestOuOfRange;
							break;
					}
				break;
			case 0x03:
				switch(LRxPdu->DataPtr[2])
					{
						case 0x01:
            case 0x03:
							CtrlMsg_Status = DisRXDisTXAppMsg;
							break;
						default:
							CtrlMsg_Status = RestOuOfRange;
							break;
					}
				break;
			default:
				CtrlMsg_Status = InVaildSubFunc;
				break;
		}
	}
	switch (CtrlMsg_Status)
	{
		case InMsgLenOrInvalidFmt:
			DCAN_GenericNegResponse(SID28, DCAN_MsgLenOrInvalidFormat);
			break;
		case ServNSupptInActSession:
			DCAN_GenericNegResponse(SID28, DCAN_ServNoSupportInActvSession);
			break;
		case InVaildSubFunc:
			DCAN_GenericNegResponse(SID28, DCAN_SubFuncNotSupport);
			break;
		case RestOuOfRange:
			DCAN_GenericNegResponse(SID28, DCAN_RequestOutOfRange);
			break;
		case EnRXEnTXAppMsg:
			//COMM_CAN_CFG_ENABLE_TX_APP();
			//COMM_CAN_CFG_ENABLE_RX_APP();
			//COMM_CAN_CFG_DISABLE_TX_DIAG();
			DCAN_CTRLMSG_STATUS = 1;
			DCAN_GenericPosResponse(SID28);
			break;
		case EnRXDisTXAppMsg:
			//COMM_CAN_CFG_ENABLE_RX_APP();
			//COMM_CAN_CFG_DISABLE_TX_APP();
			DCAN_CTRLMSG_STATUS = 0;
			DCAN_GenericPosResponse(SID28);
			break;
		case DisRXEnTXAppMsg:
			//COMM_CAN_CFG_ENABLE_RX_DIAG();
			//COMM_CAN_CFG_DISABLE_TX_DIAG();
			//COMM_CAN_CFG_ENABLE_TX_APP();
			DCAN_CTRLMSG_STATUS = 1;
			DCAN_GenericPosResponse(SID28);
			break;
		case DisRXDisTXAppMsg:
			//COMM_CAN_CFG_ENABLE_RX_DIAG();
			//COMM_CAN_CFG_DISABLE_TX_APP();
			DCAN_CTRLMSG_STATUS = 0;
			DCAN_GenericPosResponse(SID28);
			break;
		default:
			DCAN_CTRLMSG_STATUS = 1;
			DCAN_GenericPosResponse(SID28);
			break;
	}
}
void DCAN_PerformService3E(void)
{
	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff2();
	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff2();
	if (DCAN_TestPresentTimer > 0)
	{
		DCAN_TestPresentTimer = DCAN_TestPresent_S3SeverTmr;
	}
	if (DCAN_TestPresentTimer <= 0)
	{
		Session_Mode = DefaultSession;
		DCAN_SeedRequestAlready = 0;
		if((Security_Type == KeyPASSLevel1) || (Security_Type == KeyPASSLevel9)) {
				Security_Type = KeyDefaultStatus;
		}
	}
	DCAN_TestPresentStatu = PresentDefaultstatu;
	if (LRxPdu->Length != 2)
	{
		DCAN_TestPresentStatu = InCoMsgLenOrInvalFmt;
	}
//	else if (Session_Mode == DefaultSession)
//	{
//		DCAN_TestPresentStatu = ServNSuppInActSession;
//	}
	else
	{
		if ((LRxPdu->DataPtr[1] != 0x00) && (LRxPdu->DataPtr[1] != 0x80))
		{
			DCAN_TestPresentStatu = SubFuncNSupport;
		}
		else
		{
			switch (LRxPdu->DataPtr[1])
			{
				case 0x00:
					DCAN_TestPresentStatu = TestPresent;
					break;
				default:
					DCAN_TestPresentStatu = PresentDefaultstatu;
					break;
			}
		}
	}
	switch (DCAN_TestPresentStatu)
	{
	case PresentDefaultstatu:
		break;
	case ServNSuppInActSession:
		DCAN_GenericNegResponse(SID3E, DCAN_ServNoSupportInActvSession);
		break;
	case SubFuncNSupport:
		DCAN_GenericNegResponse(SID3E, DCAN_SubFuncNotSupport);
		break;
	case InCoMsgLenOrInvalFmt:
		DCAN_GenericNegResponse(SID3E, DCAN_MsgLenOrInvalidFormat);
		break;
	case TestPresent:
		DCAN_GenericPosResponse(SID3E);
		break;
	default:
		break;
	}
}

void DCAN_PerformService85(void)
{
    ControlDTCSet = ControlDTC_Accepted;
    CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
    CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();

    if(DCAN_TestPresentTimer > 0) {
        DCAN_TestPresentTimer = DCAN_TestPresent_S3SeverTmr;
    } else {
        Session_Mode = DefaultSession;
        DCAN_SeedRequestAlready = 0;
        if((Security_Type == KeyPASSLevel1) || (Security_Type == KeyPASSLevel9)) {
            Security_Type = KeyDefaultStatus;
        }
    }

    if(LRxPdu->Length != 2) {
        ControlDTCSet = ControlDTC_MsgLenOrInvalidFmt;
    } else if(Session_Mode != ExtendedDiagSession) {
        ControlDTCSet = ControlDTC_ConditionsNotCorrect;
    } else {
        switch(LRxPdu->DataPtr[1] & 0x7F) {
            case 0x01:
                ControlDTCSet = ControlDTC_Accepted;
                break;
            case 0x02:
                ControlDTCSet = ControlDTC_Disabled;
                break;
            default:
                ControlDTCSet = ControlDTC_SubFuncNSupport;
                break;
        }
    }

    switch(ControlDTCSet) {
        case ControlDTC_MsgLenOrInvalidFmt:
            DCAN_GenericNegResponse(SID85, DCAN_MsgLenOrInvalidFormat);
            break;
        case ControlDTC_ConditionsNotCorrect:
            DCAN_GenericNegResponse(SID85, DCAN_ConditionNotCorrect);
            break;
        case ControlDTC_SubFuncNSupport:
            DCAN_GenericNegResponse(SID85, DCAN_SubFuncNotSupport);
            break;
        case ControlDTC_Disabled:
				case ControlDTC_Accepted:
            DCAN_GenericPosResponse(SID85);
            break;
				
        default:
            break;
    }

    return;
}


void DCAN_SID14_PosResponse(U8 SID)
{
	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
	LTxPdu->Length = 0;
	LTxPdu->DataPtr[LTxPdu->Length++] = SID + 0x40;

	COMM_CANTP_TX_MsgProcess();
}
void DCAN_PerformService14(void)
{
	U8 GroupOfDTC[3];
	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
	
	GroupOfDTC[0] = (U8)(LRxPdu->DataPtr[1]);
	GroupOfDTC[1] = (U8)(LRxPdu->DataPtr[2]);
	GroupOfDTC[2] = (U8)(LRxPdu->DataPtr[3]);
	
	if(LRxPdu->Length != 4)
	{	
		DCAN_DTC_Status = MsgLenOrInvalidFormat;
	}
	//all of group DTC
	else if((GroupOfDTC[0]&0xFF) != 0xFF &&
					(GroupOfDTC[1]&0xFF) != 0xFF &&
					(GroupOfDTC[2]&0xFF) != 0xFF)
	{
		DCAN_DTC_Status = ConditionNotFulfill;
	}
	else //do clear DTC info here
	{
		for(U8 i=0; i<DTC_NUMBER;i+=4)
		{
			dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i] = 0xFF;
			dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i+1] = 0xFF;
			dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i+2] = 0xFF;
			dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i+3] = 0xFF;
		}
				
		if((DRV_WriteData1Eeprom(DTCMEM_START_ADDR02, dtc19_resp.DTC02_DataPack.DTCAndStatusRecord, 0U, DTC_NUMBER)) ==ERROR)
		{	
			m_bx1902Earsed = false; //Set this flag bit to erase the fault code written by 0x19 02 (so after a fault occurs, only write once)
			DCAN_GenericNegResponse(SID14, DCAN_GeneralProgrammingFail); 
		}
		else
		{	DCAN_DTC_Status = _DefaultStatus;}
	}
		
	switch(DCAN_DTC_Status)
	{
		case MsgLenOrInvalidFormat:
			DCAN_GenericNegResponse(SID14, DCAN_MsgLenOrInvalidFormat);
			break;
		case ConditionNotFulfill:
			DCAN_GenericNegResponse(SID14, DCAN_ConditionNotCorrect);
			break;
		case ReqOutOfRang:
			DCAN_GenericNegResponse(SID14, DCAN_RequestOutOfRange);
			break;	
		case _DefaultStatus:
			DCAN_SID14_PosResponse(SID14);
			break;
		default:
			break;
	}
}

void DCAN_PerformService19(void)
{
	U8 _0x19SubFunc=0x0;
	U8 DTC_Cnt=0x0;
	U8 DTCMaskRecord[3];
	CANPduType *LRxPdu = COMM_CANTP_GetRxBuff();
	CANPduType *LTxPdu = COMM_CANTP_GetTxBuff();
	
	if(LRxPdu->Length < 0x2) 
	{
    DCAN_DTC_Status = MsgLenOrInvalidFormat;
  } 
	else 
	{
		if(ControlDTCSet == ControlDTC_Accepted)
		{		
			_0x19SubFunc = LRxPdu->DataPtr[1];
			switch(_0x19SubFunc) 
			{
					case 0x01:
					{
						if(LRxPdu->DataPtr[2] != 0xFF)
						{
							DCAN_DTC_Status = ReqOutOfRang;
							break;
						}
						if(ControlDTCSet == ControlDTC_Accepted)
						{
							EFLS_DRV_Read_Data_From_Eemprom((DTCMEM_START_ADDR01), (U8*)&(dtc19_resp.DTC01_DataPack), sizeof(dtc19_resp.DTC01_DataPack));
							
							LTxPdu->Length = 0;
							LTxPdu->DataPtr[LTxPdu->Length++] = SID19 + 0x40;
							LTxPdu->DataPtr[LTxPdu->Length++] = 0x01;
							LTxPdu->DataPtr[LTxPdu->Length++] = 0xFF;
							LTxPdu->DataPtr[LTxPdu->Length++] = dtc19_resp.DTC01_DataPack.DTCFormatIdentifier;//01:ISO14229-1DTCFormat //0x00:ISO15031-6DTCFormat
							LTxPdu->DataPtr[LTxPdu->Length++] = dtc19_resp.DTC01_DataPack.DTCCount;
							
							DCAN_DTC_Status = _DefaultStatus;
						}						
					}
					break;
					case 0x02:
					{
						if(LRxPdu->DataPtr[2] != 0xFF)
						{
							DCAN_DTC_Status = ReqOutOfRang;
							break;
						}
						
						EFLS_DRV_Read_Data_From_Eemprom(DTCMEM_START_ADDR02, dtc19_resp.DTC02_DataPack.DTCAndStatusRecord, DTC_NUMBER);
						
						LTxPdu->Length=0;
						LTxPdu->DataPtr[LTxPdu->Length++] = SID19 + 0x40;
						LTxPdu->DataPtr[LTxPdu->Length++] = 0x02;
						LTxPdu->DataPtr[LTxPdu->Length++] = 0xFF;

						DTC_Cnt = DTC_NUMBER;
						while(DTC_Cnt != 0) 
						{
							LTxPdu->DataPtr[LTxPdu->Length++] = *dtc19_resp.DTC02_DataPack.DTCAndStatusRecord++;
							DTC_Cnt--;
						}
						DCAN_DTC_Status = _DefaultStatus;
						
					}
					break;
					case 0x04:
					{
						if(LRxPdu->Length < 0x6) 
						{
							DCAN_DTC_Status = MsgLenOrInvalidFormat;
							break;
						}
						if(LRxPdu->DataPtr[6] != 0xFF)
						{
							DCAN_DTC_Status = ReqOutOfRang;
							break;
						}
						
						if(ControlDTCSet == ControlDTC_Accepted)
						{
							DTCMaskRecord[0] = LRxPdu->DataPtr[3]; //DTCHighByte
							DTCMaskRecord[1] = LRxPdu->DataPtr[4]; //DTCMiddleByte
							DTCMaskRecord[2] = LRxPdu->DataPtr[5]; //DTCLowByte 
							
							EFLS_DRV_Read_Data_From_Eemprom(DTCMEM_START_ADDR04, sid19_04_datapack.DtcSnapshotRecord01.SnapshotData, DTC_NUMBER);// DTC_SNAPSHOT_DATA_NUMBER);
							
							LTxPdu->Length=0;
							LTxPdu->DataPtr[LTxPdu->Length++] = SID19 + 0x40;
							LTxPdu->DataPtr[LTxPdu->Length++] = 0x04;						
							LTxPdu->DataPtr[LTxPdu->Length++] = DTCMaskRecord[0];
							LTxPdu->DataPtr[LTxPdu->Length++] = DTCMaskRecord[1];	
							LTxPdu->DataPtr[LTxPdu->Length++] = DTCMaskRecord[2];
							
							DTC_Cnt = (U8)DTC_NUMBER;
							while(DTC_Cnt != 0) 
							{
								if(DTCMaskRecord[0] == *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++ &&
									 DTCMaskRecord[1] == *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++ &&
									 DTCMaskRecord[2] == *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++)
								{
									LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++;    //StausOfDTC
									LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++;		//sid19_04_datapack.DtcSnapshotRecord02.DTCSnapshotRecordNumber;
									LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++;		//sid19_04_datapack.DtcSnapshotRecord02.DTCSnapshotRecordNumberOfIdentifiers;
									
									LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++;		//sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte1; 
									LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++;		//sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte2;
									
									LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++;		//sid19_04_datapack.DtcSnapshotRecord02.snapshot_1;
									LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++;		//sid19_04_datapack.DtcSnapshotRecord02.snapshot_2;								
									
									LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++;    //0xFF
									LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++;		//0xFF						
									
									DTC_Cnt -= 12U;
									break;
								}
								else
								{
									//for iterate with per 4 bytes(dtc lie in 3 front of bytes, byte4 is dtc counter that no real use. for supoort 4bytes align)
									*sid19_04_datapack.DtcSnapshotRecord01.SnapshotData++; 
									DTC_Cnt -= 4U; 
								}
							}
							
							DCAN_DTC_Status = _DefaultStatus;
						}																	
					}
					break;					
					case 0x06:
					{
						if(LRxPdu->Length < 0x6) 
						{
							DCAN_DTC_Status = MsgLenOrInvalidFormat;
							break;
						}
						if(LRxPdu->DataPtr[5] != 0xFF)
						{
							DCAN_DTC_Status = ReqOutOfRang;
							break;
						}
						
						if(ControlDTCSet == ControlDTC_Accepted)
						{
							DTCMaskRecord[0] = LRxPdu->DataPtr[2]; //DTCHighByte
							DTCMaskRecord[1] = LRxPdu->DataPtr[3]; //DTCMiddleByte
							DTCMaskRecord[2] = LRxPdu->DataPtr[4]; //DTCLowByte 
							
							EFLS_DRV_Read_Data_From_Eemprom(DTCMEM_START_ADDR06, sid19_06_datapack.DTCMaskRecord.dtcmaskrecord, DTC_NUMBER);
							
							LTxPdu->Length=0;
							LTxPdu->DataPtr[LTxPdu->Length++] = SID19 + 0x40;
							LTxPdu->DataPtr[LTxPdu->Length++] = 0x06;						
							LTxPdu->DataPtr[LTxPdu->Length++] = DTCMaskRecord[0];
							LTxPdu->DataPtr[LTxPdu->Length++] = DTCMaskRecord[1];	
							LTxPdu->DataPtr[LTxPdu->Length++] = DTCMaskRecord[2];
							
							DTC_Cnt = (U8)DTC_NUMBER;
							while(DTC_Cnt != 0) 
							{
									if(DTCMaskRecord[0] == *sid19_06_datapack.DTCMaskRecord.dtcmaskrecord++ &&
										 DTCMaskRecord[1] == *sid19_06_datapack.DTCMaskRecord.dtcmaskrecord++ &&
										 DTCMaskRecord[2] == *sid19_06_datapack.DTCMaskRecord.dtcmaskrecord++)
									{			
										LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_06_datapack.DTCMaskRecord.dtcmaskrecord++; //statusOfDTC 0xFF
										LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_06_datapack.DTCMaskRecord.dtcmaskrecord++;	//ExDataRecNumber  (DTCExtendedDataRecordNumber )
										LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_06_datapack.DTCMaskRecord.dtcmaskrecord++; //dtc_Number       (ExtendedData #1 byte )
										LTxPdu->DataPtr[LTxPdu->Length++] = *sid19_06_datapack.DTCMaskRecord.dtcmaskrecord++; //dtc_Undetermined (ExtendedData #2 byte )
										*sid19_06_datapack.DTCMaskRecord.dtcmaskrecord++; //0xFF
										
										DTC_Cnt -= 8U;
										break;
									}
									else
									{
										*sid19_06_datapack.DTCMaskRecord.dtcmaskrecord++; //0xFF(cause 4 bytes align)
										DTC_Cnt -= 4U;
									}
							}
							
							DCAN_DTC_Status = _DefaultStatus;
						}										
					}
					break;
					
					case 0x0A:
					{
						if(LRxPdu->Length != 0x2) 
						{
							DCAN_DTC_Status = MsgLenOrInvalidFormat;
							break;
						}
						if(LRxPdu->DataPtr[1] != 0x0A)
						{
							DCAN_DTC_Status = ReqOutOfRang;
							break;
						}						
						
						LTxPdu->Length=0;
						LTxPdu->DataPtr[LTxPdu->Length++] = SID19 + 0x40;
						LTxPdu->DataPtr[LTxPdu->Length++] = 0x0A;
						LTxPdu->DataPtr[LTxPdu->Length++] = 0x16; //DTCStatusAvailabilityMask
						
						DTC_Cnt = DCAN_ORIGINAL_DTC_COUNT * 4; //22 DTC define(there is 4 byte that include 0xFF per tail of DTC)
						DCAN_WriteDTC0A();

						while(DTC_Cnt-- !=0)
						{
							LTxPdu->DataPtr[LTxPdu->Length++] = *_p0x190ABUF++;						
						}
						
						DCAN_DTC_Status = _DefaultStatus;
						
					}				
					break;
					
					default:
						DCAN_DTC_Status = _SubFuncNotSupport;
					break;
			}
			
			if(DCAN_DTC_Status == _DefaultStatus)
			{
				COMM_CANTP_TX_MsgProcess();			
			}
		}
		

	}
	
	switch(DCAN_DTC_Status)
	{
		case MsgLenOrInvalidFormat:
			DCAN_GenericNegResponse(SID19, DCAN_MsgLenOrInvalidFormat);
			break;
		case _SubFuncNotSupport:
			DCAN_GenericNegResponse(SID19, DCAN_SubFuncNotSupport);
			break;
		case ReqOutOfRang:
			DCAN_GenericNegResponse(SID19, DCAN_RequestOutOfRange);
			break;
		default:
			break;
	}
}

void DCAN_WriteDTC01(U8 count)
{
	dtc19_resp.DTC01_DataPack.DTCFormatIdentifier = 0x01;
	dtc19_resp.DTC01_DataPack.DTCCount = count;
	dtc19_resp.DTC01_DataPack.reverse[0] = 0xFF;				
	dtc19_resp.DTC01_DataPack.reverse[1] = 0xFF;
	
	if(ControlDTCSet == ControlDTC_Accepted){		
		if(DRV_WriteData1Eeprom(DTCMEM_START_ADDR01, (U8*)&dtc19_resp.DTC01_DataPack, 0U, 4U) == ERROR) 
		{
			DCAN_GenericNegResponse(SID19, DCAN_GeneralProgrammingFail);
		} 
	}
}

ErrorStatus DCAN_WriteDTC02(U8 pos, U8* pDTC, bool bWrite)
{
	ErrorStatus es = ERROR;
	if(ControlDTCSet == ControlDTC_Accepted)
	{
		 	if(bWrite)
			{
				for(U8 i=0; i<DTC_NUMBER;i++)
				{
					if(pos == i)
					{
						dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i] = *pDTC++;
						dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i+1] = *pDTC++;
						dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i+2] = *pDTC++;
						dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i+3] = 0xCC;								
						break;
					}
				}
			}
			else
			{
				for(U8 i=0; i<DTC_NUMBER;i++)
				{
					if(pos == i)
					{
						dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i] = 0xFF;
						dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i+1] = 0xFF;
						dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i+2] = 0xFF;
						dtc19_resp.DTC02_DataPack.DTCAndStatusRecord[i+3] = pos;				
						break;
					}
				}
			}
			
			
			es = DRV_WriteData2Eeprom(DTCMEM_START_ADDR02, dtc19_resp.DTC02_DataPack.DTCAndStatusRecord, (U32)pos, 4U);
	}

	return es;
	
}

ErrorStatus DCAN_WriteDTC04(U8* pDTC, U8* pSnapshot)
{
	U16 pos = 0;
	ErrorStatus es = ERROR;
	if(ControlDTCSet == ControlDTC_Accepted)
	{
		pos = sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte2;
		sid19_04_datapack.DtcSnapshotRecord02.snapshot_1 = pSnapshot[0];		
		sid19_04_datapack.DtcSnapshotRecord02.snapshot_2 = pSnapshot[1];
		
		if(pos < DTC_NUMBER-12U)
		{
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = *(U8*)pDTC;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = *(U8*)(pDTC+1);
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = *(U8*)(pDTC+2);
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = pos;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.DTCSnapshotRecordNumber;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.DTCSnapshotRecordNumberOfIdentifiers;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte1;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte2;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.snapshot_1;		
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.snapshot_2;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = 0xff;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = 0xff;
		}
		else
		{
			m_bx1904Earsed = false;
			if(sid19_04_datapack.DtcSnapshotRecord02.DTCSnapshotRecordNumber++>0xFE)
				sid19_04_datapack.DtcSnapshotRecord02.DTCSnapshotRecordNumber = 0x0;
			
			sid19_04_datapack.DtcSnapshotRecord02.DTCSnapshotRecordNumberOfIdentifiers++;
			
			sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte1++;						
			sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte2 = 0x0;
			pos = 0x0;
			
			if(sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte1 >0xFE)
				sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte1 = 0x0;
			
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = *(U8*)pDTC;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = *(U8*)(pDTC+1);
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = *(U8*)(pDTC+2);
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = pos;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.DTCSnapshotRecordNumber;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.DTCSnapshotRecordNumberOfIdentifiers;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte1;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte2;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.snapshot_1;		
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = sid19_04_datapack.DtcSnapshotRecord02.snapshot_2;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = 0xFF;
			sid19_04_datapack.DtcSnapshotRecord01.SnapshotData[pos++] = 0xFF;
					
		}
		
		sid19_04_datapack.DtcSnapshotRecord02.DataIdentifierByte2 = pos;		
		es = DRV_WriteData4Eeprom(DTCMEM_START_ADDR04, sid19_04_datapack.DtcSnapshotRecord01.SnapshotData, (U32)pos, 12U);
		
	}
	
	return es;
}

ErrorStatus DCAN_WriteDTC06(U8* pDTC, U8 ExDataRecNumber, U8 dtc_Number, U8 dtc_Undetermined)
{
	U16 pos = 0;
	ErrorStatus es = ERROR;
	if(ControlDTCSet == ControlDTC_Accepted)
	{
		pos = sid19_06_datapack.DTCExtendedDataRecord.DTCExtendedDataRecordNumber;	
		if(pos >= DTC_NUMBER)	
		{	
			pos = 0U;
			m_bx1906Earsed = false;
			sid19_06_datapack.DTCExtendedDataRecord.DTCExtendedDataRecordNumber = 0U;
		}

		sid19_06_datapack.DTCMaskRecord.dtcmaskrecord[pos++] = *(U8*)pDTC;
		sid19_06_datapack.DTCMaskRecord.dtcmaskrecord[pos++] = *(U8*)(pDTC+1);
		sid19_06_datapack.DTCMaskRecord.dtcmaskrecord[pos++] = *(U8*)(pDTC+2);
		sid19_06_datapack.DTCMaskRecord.dtcmaskrecord[pos++] = 0xFF; 						// statusOfDTC
		sid19_06_datapack.DTCMaskRecord.dtcmaskrecord[pos++] = ExDataRecNumber; // DTCExtendedDataRecordNumber 
		sid19_06_datapack.DTCMaskRecord.dtcmaskrecord[pos++] = dtc_Number;      //ExtendedData 1(DTC_Number)
		sid19_06_datapack.DTCMaskRecord.dtcmaskrecord[pos++] = dtc_Undetermined;//ExtendedData 2(DTC_Undetermined)		
		sid19_06_datapack.DTCMaskRecord.dtcmaskrecord[pos++] = 0xFF; 						//for 4bytes align
			
		sid19_06_datapack.DTCExtendedDataRecord.DTCExtendedDataRecordNumber = pos;
		
		es = DRV_WriteData6Eeprom(DTCMEM_START_ADDR06, sid19_06_datapack.DTCMaskRecord.dtcmaskrecord, (U32)pos, 8U);	
	}
		
	
	return es;
}

void DCAN_WriteDTC0A(void)
{
	U8 pos = 0U;

	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C00116[i]) : (_p0x190ABUF[pos++] = 0xFF);}		
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C00216[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_911717[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_911716[i]) : (_p0x190ABUF[pos++] = 0xFF);}	
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C20116[i]) : (_p0x190ABUF[pos++] = 0xFF);}		
		
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C20117[i]) : (_p0x190ABUF[pos++] = 0xFF);}		
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C07500[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C30116[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C30216[i]) : (_p0x190ABUF[pos++] = 0xFF);}	
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C40116[i]) : (_p0x190ABUF[pos++] = 0xFF);}

	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C40216[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C50116[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C50216[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C60116[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C60216[i]) : (_p0x190ABUF[pos++] = 0xFF);}

	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C07501[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C07502[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C07503[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C07504[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_D00300[i]) : (_p0x190ABUF[pos++] = 0xFF);}

	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_500216[i]) : (_p0x190ABUF[pos++] = 0xFF);}
	for(U8 i = 0; i<4; i++){(i<3) ? (_p0x190ABUF[pos++] = DTC_C07300[i]) : (_p0x190ABUF[pos++] = 0xFF);}	
}

ErrorStatus DRV_WriteData1Eeprom(U32 addr, U8 *buf, U32 pos, U8 len)//for 0x19 01
{
    U32 *tmpDataAddr;
    ErrorStatus ret = ERROR;

		tmpDataAddr = (U32 *)(buf + pos);		
		if(EFLS_DRV_FlashReadyCheck() == SUCCESS) 
		{
				if(eeprom_sector_erase((addr - EEPROM_BASE) / EEPROM_SECTOR_SIZE, TRUE) == SUCCESS) 
				{
						if(eeprom_prog_Nwords(addr + pos, tmpDataAddr, len) == SUCCESS) 
						{
								ret = SUCCESS;
						} 
						else 
						{
								ret = ERROR;
						}
				} 
				else 
				{
						ret = ERROR;
				}
		} 
		else 
		{
				ret = ERROR;
		}
    
    return ret;
}

ErrorStatus DRV_WriteData2Eeprom(U32 addr, U8 *buf, U32 pos, U8 len)//for 0x19 02
{
	U32 *tmpDataAddr;
	ErrorStatus ret = ERROR;
			
	if(EFLS_DRV_FlashReadyCheck() == SUCCESS) 
	{
		if(!m_bx1902Earsed)
		{
			if(eeprom_sector_erase((addr - EEPROM_BASE) / EEPROM_SECTOR_SIZE, TRUE) == SUCCESS)
			{
				m_bx1902Earsed = true;
				ret = SUCCESS;
			}
			else 
			{
				ret = ERROR;
				return ret;
			}
		}
		
		if(dtc19_resp.DTC02_DataPack.pos != pos)
		{
			tmpDataAddr = (U32 *)(buf + pos);
			if(eeprom_prog_Nwords(addr + pos, tmpDataAddr, len) == SUCCESS) 
			{
				dtc19_resp.DTC02_DataPack.pos = pos;
				ret = SUCCESS;
			} 
			else 
			{
				ret = ERROR;
			}
		}
	} 
	else 
	{
		ret = ERROR;
	}
	
	return ret;
}

ErrorStatus DRV_WriteData4Eeprom(U32 addr, U8 *buf, U32 pos, U8 len)//for 0x19 04
{
	U32 *tmpDataAddr;
	ErrorStatus ret = ERROR;
			
	if(EFLS_DRV_FlashReadyCheck() == SUCCESS) 
	{
		if(!m_bx1904Earsed)
		{
			if(eeprom_sector_erase((addr - EEPROM_BASE) / EEPROM_SECTOR_SIZE, TRUE) == SUCCESS)
			{
				m_bx1904Earsed = true;
				ret = SUCCESS;
			}
			else 
			{
				ret = ERROR;
				return ret;
			}
		}
		
		if(sid19_04_datapack.DtcSnapshotRecord02.pos != pos)
		{
			tmpDataAddr = (U32 *)(buf);
			if(eeprom_prog_Nwords(addr + pos, tmpDataAddr, len) == SUCCESS) 
			{
				sid19_04_datapack.DtcSnapshotRecord02.pos = pos;
				ret = SUCCESS;
			} 
			else 
			{
				ret = ERROR;
			}
		}
	} 
	else 
	{
		ret = ERROR;
	}
	
	return ret;
}

ErrorStatus DRV_WriteData6Eeprom(U32 addr, U8 *buf, U32 pos, U8 len)//for 0x19 06
{
	U32 *tmpDataAddr;
	ErrorStatus ret = ERROR;
			
	if(EFLS_DRV_FlashReadyCheck() == SUCCESS) 
	{
		if(!m_bx1906Earsed)
		{
			if(eeprom_sector_erase((addr - EEPROM_BASE) / EEPROM_SECTOR_SIZE, TRUE) == SUCCESS)
			{
				m_bx1906Earsed = true;
				ret = SUCCESS;
			}
			else 
			{
				ret = ERROR;
				return ret;
			}
		}
		
		if(sid19_06_datapack.DTCExtendedDataRecord.DTC_Number != pos)
		{
			tmpDataAddr = (U32 *)(buf);
			if(eeprom_prog_Nwords(addr + pos, tmpDataAddr, len) == SUCCESS) 
			{
				sid19_06_datapack.DTCExtendedDataRecord.DTC_Number = pos;
				ret = SUCCESS;
			} 
			else 
			{
				ret = ERROR;
			}
		}
	} 
	else 
	{
		ret = ERROR;
	}
	
	return ret;
}


ErrorStatus EFLS_DRV_FlashReadyCheck(void)
{
    ErrorStatus ret = ERROR;

    if(is_flash_idle() && is_eeprom_idle()){
        return SUCCESS;
    }

    return ret;
}

/* ?用者保?addr和len的4字??? */
void EFLS_DRV_Read_Data_From_Eemprom(U32 addr, U8 *buf, U32 len)
{
    eeprom_Nwords_get(addr, (uint32_t *)buf, len / 4);

    return;
}

/* ?????addr?64?????len?4???? */
ErrorStatus EFLS_DRV_Write_Data_To_Eemprom(U32 addr, U8 *buf, U32 len)
{
    U8 i;
    U32 count = 0;
    U32 index = 0;
    U32 TempData[EEPROM_SECTOR_SIZE / 4];
    U32 *tmpDataAddr;
    ErrorStatus ret = ERROR;

    if(len % EEPROM_SECTOR_SIZE == 0) {
        count = len / EEPROM_SECTOR_SIZE;
    } else {
        count = len / EEPROM_SECTOR_SIZE + 1;
    }

    while(index < count) {
        if((len - EEPROM_SECTOR_SIZE * index) < EEPROM_SECTOR_SIZE) {
            eeprom_Nwords_get(addr, TempData, EEPROM_SECTOR_SIZE / 4);

            for(i = 0; i < (len - EEPROM_SECTOR_SIZE * index) / 4; i++) {
                TempData[i] = *((U32 *)(buf + EEPROM_SECTOR_SIZE * index + i * 4));
            }
            tmpDataAddr = TempData;
        } else {
            tmpDataAddr = (U32 *)(buf + EEPROM_SECTOR_SIZE * index);
        }

        if(EFLS_DRV_FlashReadyCheck() == SUCCESS) {
            if(eeprom_sector_erase((addr - EEPROM_BASE) / EEPROM_SECTOR_SIZE, TRUE) == SUCCESS) {
                if(eeprom_prog_Nwords(addr, tmpDataAddr, EEPROM_SECTOR_SIZE / 4) == SUCCESS) {
                    ret = SUCCESS;
                } else {
                    ret = ERROR;
                }
            } else {
                ret = ERROR;
            }
        } else {
            ret = ERROR;
        }

        addr += EEPROM_SECTOR_SIZE;
        index++;
    }

    return ret;
}

ErrorStatus EFLS_DRV_ONLYWrite_FLAG_Data(U32 Start_Address, U8 Data, U8 Order)
{
  U32 TempData[EEPROM_SECTOR_SIZE / 4];
	ErrorStatus ret = ERROR;

  eeprom_Nwords_get(Start_Address, TempData, EEPROM_SECTOR_SIZE / 4);
	TempData[Order] = Data;
	if (EFLS_DRV_FlashReadyCheck() == SUCCESS)
	{
    if (eeprom_sector_erase((Start_Address - EEPROM_BASE) / EEPROM_SECTOR_SIZE, TRUE) == SUCCESS)
		{
			if (eeprom_prog_Nwords(Start_Address, TempData, EEPROM_SECTOR_SIZE / 4) == SUCCESS)
			{
				ret = SUCCESS;
			}
			else
			{
				ret = ERROR;
			}
		}
		else
		{
			ret = ERROR;
		}
	}
	else
	{
		ret = ERROR;
	}

	return ret;
}


void EFLS_Init(void)
{
    eflash_var_init();
}

void Jump2Boot(void)
{
	EFLS_DRV_ONLYWrite_FLAG_Data(APP_UPDATE_REQ_FLAG_ADD, DCAN_APP_UPDATE_REQUEST_FLAG, 0);
	
	OSTK_Delayus(10000);	
	DCAN_PerfmSoftReset();
}
