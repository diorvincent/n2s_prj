/*
 * DCAN.h
 * Xi'An ManHui Info. Science LLC
 * Created on: Nov 1, 2023
 * Author: He Jingchi
 * Update on: Jun 27, 2024
 */

#ifndef DCAN_DCAN_H_
#define DCAN_DCAN_H_

/* ===========================================  Includes  =========================================== */

#include "CAN_TP.h"
#include "DATA_TYPE.h"
#include "BF7006BMxx_eflash.h"

/* ===========================================  Typedef  ============================================ */


#pragma pack(push)
#pragma pack(1)

typedef struct
{
    U8 appValidFlag[EEPROM_SECTOR_SIZE];
    U8 appUpdateReqFlag[EEPROM_SECTOR_SIZE];
    U32 resumeStartAdd[EEPROM_SECTOR_SIZE/4];
} AppInfoList;

typedef struct
{
    U8 did_F18C[14];
    U8 did_F190[17];
    U8 did_F15A[9];
    U8 did_F15B[10];
    U8 reserve[14];
} DidMemList;

typedef struct
{
    AppInfoList appInfoList;
    DidMemList didMemList;
} EepromMemList;

/*SID 0x19 data structs*/
typedef struct
{
	U8 DTCFormatIdentifier;
	U8 DTCCount;
	U8 reverse[2];  //3, 7
}SID19_01_DataPack;

typedef struct
{
	U8 pos;
	U8* DTCAndStatusRecord;
}SID19_02_DataPack;

typedef struct
{
	SID19_01_DataPack DTC01_DataPack;
	SID19_02_DataPack DTC02_DataPack;
}SID19_Resp;

typedef struct
{
	U8* SnapshotData; //byte #1 ~  byte #p
}DTCSnapshotRecord01;

typedef struct
{
	U8 DTCSnapshotRecordNumber;
	U8 DTCSnapshotRecordNumberOfIdentifiers;	
	U8 DataIdentifierByte1; //(MSB)
	U8 DataIdentifierByte2; //(LSB)
	U8 snapshot_1;          //snapshot byte0
	U8 snapshot_2;          //snapshot byte1
	U8 pos;
}DTCSnapshotRecord02;

typedef struct
{
	DTCSnapshotRecord01 DtcSnapshotRecord01;
	DTCSnapshotRecord02 DtcSnapshotRecord02;
}SID19_04_DataPack;

typedef struct
{
	U8* dtcmaskrecord;
}DTCMaskRecord06;

typedef struct
{
	U8 DTCExtendedDataRecordNumber;
	U8 DTC_Number;  				//Apear times of fault
	U8 DTC_Undetermined; 		//Undetermined times of fault
}DTCExtendedDataRecord06;

typedef struct
{
	DTCMaskRecord06 DTCMaskRecord;
	DTCExtendedDataRecord06 DTCExtendedDataRecord;
}SID19_06_DataPack;

 
 
//_	SID 0x19 data structs define

#pragma pack(pop)



typedef enum
{
	MsgLenInCorrOrInvalidFormat = 1,
	SubFunctiNoSupprt,
  Session_ConditionsNotCorrect,
	DefaultSession,
	ProgrammingSession,
	ExtendedDiagSession,
	SafetySysDiagSession
} DCAN_Session_Type;

typedef enum
{
    ReadDataById_Accepted = 1,
    ReadDataById_MsgLenOrInvalidFmt,
    ReadDataById_ConditionsNotCorrect,
    ReadDataById_ReqOutOfRange,
    ReadDataById_SecAccessDenied
} DCAN_ReadDataById_Type;

typedef enum
{
    WriteDataById_Accepted = 1,
    WriteDataById_MsgLenOrInvalidFmt,
    WriteDataById_ConditionsNotCorrect,
    WriteDataById_ReqOutOfRange,
    WriteDataById_SecAccessDenied,
    WriteDataById_GenProgrammFail
} DCAN_WriteDataById_Type;

typedef enum
{
	HadrReset = 1,
	KeyOffOnReset,
	SoftReset,
	EnableRapidPowerShutDown,
	DisableRapidPowerShutDown
} DCAN_Reset_Type;

typedef enum
{
  KeyDefaultStatus,
	SeedRequestLevel1 = 1,
  SeedRequestLevel9,
	SendKey,
	Level3SeedRequest,
	Level3SendKey,
	KeyPASSLevel1,
	KeyPASSLevel9,
	InvalidKey,
	ReachedMaxTrailNum,
	FailKeyTrialDelayTimeNotReached,
	RequestSequenceError,
	ServNoSupportInActvSess,
	ConditionsNotCorrect,
	SubFuncNotSupported,
	IncorrectMsgLenOrInvalidFormat,
	RequestOutOfRange
} DCAN_Security_Type;

typedef enum
{
	EraseSuccessfully = 1,
	EraseDefault,
	ErasePending,
	RequestSequenceErr,
	CondNotCorrect,
	ServNoSupportInActvSession,
	SubFuncNotSupport,
	IncorrectMsgLenOrInvalidFmt,
	ReqOutOfRange,
	GeneralProgrammingFail,
	Routine_SecAccessDenied
} DCAN_Routine_Status;

typedef enum
{
	Default_Status = 1,
	IncorrMsgLenOrInvalidFmt,
	CondNoCorrect,
	RequesOutOfRange,
	SubFuncNoSupport,
	SecurityAccessDenied,
	ServNSupportInActvSession,
	UploadDownloadNotAccepted,
	UploadDownloadAccepted,
	UploadDownloadPreCmplt
} DCAN_Download_Status;

typedef enum
{
	InCorrMsgLenOrInvalidFmt = 1,
	RqstSeqErr,
	ServNSuppInActvSession,
	TransExitCmplt
} DCAN_TransExit_Status;

typedef enum
{
	InCoMsgLenOrInvalidFmt = 1,
	RqstSqErr,
	ReqstOutRange,
	CondNoCor,
	TransDataSuspended,
	TransferCmplt,
	ServNSupptInActvSession,
	GenProgrammFail,
	WrongBlkSeqCnt,
	TransDataNormal
} DCAN_TransData_Status;

typedef enum
{
	DefaultStatus = 1,
	RestOuOfRange,
	InMsgLenOrInvalidFmt,
	ServNSupptInActSession,
	InVaildSubFunc,
	EnRXEnTXAppMsg,
	EnRXDisTXAppMsg,
	DisRXEnTXAppMsg,
	DisRXDisTXAppMsg,
	EnRXEnTXNetMsg,
	EnRXDisTXNetMsg,
	DisRXEnTXNetMsg,
	DisRXDisTXNetMsg,
	EnRXEnTXAPP_NetMsg,
	EnRXDisTXAPP_NetMsg,
	DisRXEnTXAPP_NetMsg,
	DisRXDisTXAPP_NetMsg,
} DCAN_CtrlMsg_Status;

typedef enum
{
    ControlDTC_Accepted = 1,
	  ControlDTC_Disabled,
    ControlDTC_MsgLenOrInvalidFmt,
    ControlDTC_ConditionsNotCorrect,
    ControlDTC_SubFuncNSupport,
} DCAN_ControlDTC_Type;


typedef enum
{
	PresentDefaultstatu = 1,
	InCoMsgLenOrInvalFmt,
	SubFuncNSupport,
	ServNSuppInActSession,
	TestPresent,
	TestPresent_PosResponseSuppress,
} DCAN_TestPresentType;

typedef enum
{
	Starting = 1,
	Pending,
	Complete,
} DCAN_TaskStatus;


typedef enum
{
	_DefaultStatus = 1,
	MsgLenOrInvalidFormat,
	ConditionNotFulfill,
	_SubFuncNotSupport,
	ReqOutOfRang,
}DCAN_DTC_Info;

/* ============================================  Define  ============================================ */
#define SID10 							0x10
#define SID11 							0x11
#define SID22               0x22
#define SID2E               0x2E
#define SID27 							0x27
#define SID28 							0x28
#define SID31 							0x31
#define SID34 							0x34
#define SID36 							0x36
#define SID37 							0x37
#define SID3E 							0x3E
#define SID85 							0x85
#define SID14								0x14
#define SID19								0x19

#define DCAN_APPVALIDFLAG           		0xAA
#define DCAN_APP_UPDATE_REQUEST_FLAG    0xBB
#define UDS_SECURITY_SEEDNUM            4

#define DCAN_GeneralRejected						0x10
#define DCAN_ServiceNotSupported				0x11
#define DCAN_SubFuncNotSupport					0x12
#define DCAN_MsgLenOrInvalidFormat			0x13
#define DCAN_BusyRepeatRequest					0x21
#define DCAN_ConditionNotCorrect				0x22
#define DCAN_RequestSequenceError				0x24
#define DCAN_NoRespFromSubnetComponent	0x25
#define DCAN_FailPrevtsExecOfRqstAct		0x26
#define DCAN_RequestOutOfRange					0x31
#define DCAN_SecurityAccessDenied				0x33
#define DCAN_InvalidKey									0x35
#define DCAN_ReachedMaxTrailNum					0x36
#define DCAN_ReqTimeDlyNotExpired				0x37
#define DCAN_UpDwnloadNotAccepted				0x70
#define DCAN_TransferDataSuspended			0x71
#define DCAN_GeneralProgrammingFail			0x72
#define DCAN_WrongBlockSequenceCnt			0x73
#define DCAN_RqstCorrtRecvdRespPending	0x78
#define DCAN_SubFuncNoSupptInActvSess		0x7E
#define DCAN_ServNoSupportInActvSession	0x7F
#define DCAN_TempTooHi									0x86
#define DCAN_TempTooLow									0x87
#define DCAN_VehicleSpdTooHigh					0x88
#define DCAN_VehicleSpdTooLow						0x89
#define DCAN_VoltTooHigh								0x92
#define DCAN_VoltTooLow									0x93

#define DCAN_SECURITY_MASK							0x7D3EFD82
#define DCAN_KeyTrial_MAX_Num						10
#define DCAN_KeyTrial_MinDlyTimer				10000
#define DCAN_TestPresent_S3SeverTmr			5000

#define P2_CAN_SERVER_MAX_HIGH					(0x00)
#define P2_CAN_SERVER_MAX_LOW						(0x32)
#define P2_Enhanced_CAN_SERVER_MAX_HIGH	(0x01)
#define P2_Enhanced_CAN_SERVER_MAX_LOW	(0xF4)

#define Timer_CLK         				(APB_BUS_FREQ)
#define Delay1ms   								(Timer_CLK/1000-1)

#define DCAN_ErasePageSize					0x1000
#define DCAN_Update_Flag						(U8)0xBB
#define DCAN_App_Valid							(U8)0xAA

#define DCAN_Boot_StartAdd					0x08000000
#define DCAN_Boot_Lenth							0x9000
#define DCAN_App_StartAdd						0x08009000
#define DCAN_App_ShortStartAdd			0x006000
#define DCAN_App_ShortEndAdd				0x01AFFF
#define DCAN_App_Lenth							0x12000
#define DCAN_Cal_StartAdd						0x0801B800
#define DCAN_Cal_ShortStartAdd			0x01B800
#define DCAN_Cal_ShortEndAdd				0x01FFFF
#define DCAN_Cal_Lenth							0x4800

#define DCAN_AppCal_StartAdd				0x08009000
#define DCAN_AppCal_ShortStartAdd		0x009000
#define DCAN_AppCal_ShortEndAdd			0x01FFFF
#define DCAN_AppCal_Lenth						0x17000

#define APP_VALID_FLAG_ADD (EEPROM_BASE + ((U8 *)(eepromMemList.appInfoList.appValidFlag) - (U8 *)&eepromMemList))
#define APP_UPDATE_REQ_FLAG_ADD (EEPROM_BASE + ((U8 *)(eepromMemList.appInfoList.appUpdateReqFlag) - (U8 *)&eepromMemList))
#define DIDMEM_START_ADD (EEPROM_BASE + ((U8 *)&(eepromMemList.didMemList) - (U8 *)&eepromMemList))

#define DCAN_ORIGINAL_DTC_COUNT		22
#define DTC_NUMBER								0x60 //cause have 22 faults type in app((22+2) * 4bytes per dtc),that need 4 bytes align
#define APP_EEPROM_BASE01					(EEPROM_BASE+0x80)			
#define APP_EEPROM_BASE02					(EEPROM_BASE+0x100)		
#define APP_EEPROM_BASE04					(EEPROM_BASE+0x160)
#define APP_EEPROM_BASE06					(EEPROM_BASE+0x240)	

#define DTCMEM_START_ADDR01 APP_EEPROM_BASE01		//(APP_EEPROM_BASE01 + ((U8*)&(dtc19_resp.DTC01_DataPack) -(U8 *)&dtc19_resp))
#define DTCMEM_START_ADDR02 APP_EEPROM_BASE02 	//(APP_EEPROM_BASE02 + ((U8*)&(dtc19_resp.DTC02_DataPack) -(U8 *)&dtc19_resp))
#define DTCMEM_START_ADDR04 APP_EEPROM_BASE04		//(APP_EEPROM_BASE04 + ((U8*)&(sid19_04_datapack.DtcSnapshotRecord01) -(U8 *)&sid19_04_datapack))
#define DTCMEM_START_ADDR06 APP_EEPROM_BASE06		//(APP_EEPROM_BASE06 + ((U8*)&(sid19_06_datapack.DTCMaskRecord) - (U8*)&sid19_06_datapack))


/*=================for DEBUG================*/
#define N2S_DEBUG           						0
#define OTA_BREAKPOINT_RESUME_AVAILABLE	0
#define SECURITY_ACCESS_AVAILABLE				1
#define ETAS_TOOL_PRESENT								0


/* ==========================================  Variables  =========================================== */


static const U8 DTC_C00116[3] = { 0xC0, 0x01, 0x16}; /* IGBT_Breakdown */
static const U8 DTC_C00216[3] = { 0xC0, 0x02, 0x16}; /* IGBT_or_PTC_OpenCircult */
static const U8 DTC_911717[3] = { 0x91, 0x17, 0x17}; /* Protect_Over_HighVol */
static const U8 DTC_911716[3] = { 0x91, 0x17, 0x16}; /* Protect_Under_HighVol */
static const U8 DTC_C20116[3] = { 0xC2, 0x01, 0x16}; /* OverVol_IGBT_Driver */
static const U8 DTC_C20117[3] = { 0xC2, 0x01, 0x17}; /* UnderVol_IGBT_Driver */
static const U8 DTC_C07500[3] = { 0xC0, 0x75, 0x00}; /* OverCurrent_HighVol */
static const U8 DTC_C30116[3] = { 0xC3, 0x01, 0x16}; /* IGBT_TempSensor_OpenCirult */
static const U8 DTC_C30216[3] = { 0xC3, 0x02, 0x16}; /* IGBT_TempSensor_ShortCircult */
static const U8 DTC_C40116[3] = { 0xC4, 0x01, 0x16}; /* PCB_TempSensor_OpenCircult */
static const U8 DTC_C40216[3] = { 0xC4, 0x02, 0x16}; /* PCB_TempSensor_ShortCircult */
static const U8 DTC_C50116[3] = { 0xC5, 0x01, 0x16}; /* PTC1_TempSensor_OpenCircult */
static const U8 DTC_C50216[3] = { 0xC5, 0x02, 0x16}; /* PTC1_TempSensor_ShortCircult */
static const U8 DTC_C60116[3] = { 0xC6, 0x01, 0x16}; /* PTC2_TempSensor_OpenCircult */
static const U8 DTC_C60216[3] = { 0xC6, 0x02, 0x16}; /* PTC2_TempSensor_ShortCircult */
static const U8 DTC_C07501[3] = { 0xC0, 0x75, 0x01}; /* PTC1_OverTemp */
static const U8 DTC_C07502[3] = { 0xC0, 0x75, 0x02}; /* PTC2_OverTemp */
static const U8 DTC_C07503[3] = { 0xC0, 0x75, 0x03}; /* IGBTOver_Temp */
static const U8 DTC_C07504[3] = { 0xC0, 0x75, 0x04}; /* PCB_OverTemp */
static const U8 DTC_D00300[3] = { 0xD0, 0x03, 0x00}; /* Comm_Overtime */
static const U8 DTC_500216[3] = { 0x50, 0x02, 0x16}; /* ShortCircult_Protect */
static const U8 DTC_C07300[3] = { 0xC0, 0x73, 0x00}; /* Bus off error */

//DTC_Undetermined
static U8 _C00116 = 0U; /* IGBT_Breakdown */
static U8 _C00216 = 0U; /* IGBT_or_PTC_OpenCircult */
static U8 _911717 = 0U; /* Protect_Over_HighVol */
static U8 _911716 = 0U; /* Protect_Under_HighVol */
static U8 _C20116 = 0U; /* OverVol_IGBT_Driver */
static U8 _C20117 = 0U; /* UnderVol_IGBT_Driver */
static U8 _C07500 = 0U; /* OverCurrent_HighVol */
static U8 _C30116 = 0U; /* IGBT_TempSensor_OpenCirult */
static U8 _C30216 = 0U; /* IGBT_TempSensor_ShortCircult */
static U8 _C40116 = 0U; /* PCB_TempSensor_OpenCircult */
static U8 _C40216 = 0U; /* PCB_TempSensor_ShortCircult */
static U8 _C50116 = 0U; /* PTC1_TempSensor_OpenCircult */
static U8 _C50216 = 0U; /* PTC1_TempSensor_ShortCircult */
static U8 _C60116 = 0U; /* PTC2_TempSensor_OpenCircult */
static U8 _C60216 = 0U; /* PTC2_TempSensor_ShortCircult */
static U8 _C07501 = 0U; /* PTC1_OverTemp */
static U8 _C07502 = 0U; /* PTC2_OverTemp */
static U8 _C07503 = 0U; /* IGBTOver_Temp */
static U8 _C07504 = 0U; /* PCB_OverTemp */
static U8 _D00300 = 0U; /* Comm_Overtime */
static U8 _500216 = 0U; /* ShortCircult_Protect */
static U8 _C07300 = 0U; /* Bus off error */
//

/* ====================================  Functions declaration  ===================================== */
void DCAN_Init(void);
//void DCAN_Timer0_Start_Once(void);
void DCAN_PerfmSoftReset(void);
void DCAN_DtrmnService(void);
void DCAN_SID27_SendSeed(U8 SID, U8 level);
void DCAN_PerformService10(void);
void DCAN_PerformService11(void);
void DCAN_PerformService22(void);
void DCAN_PerformService2E(void);
void DCAN_PerformService27(void);
void DCAN_PerformService28(void);
void DCAN_PerformService3E(void);
void DCAN_PerformService85(void);
void DCAN_SID10_PosResponse(U8 SID);
void DCAN_GenericNegResponse(U8 SID, U8 NRC);
void DCAN_NRC78_Send_Task(void *device, uint32_t wpara, uint32_t lpara);
void DCAN_Dtrmn3EService(void);

//***********************************0x14/0x19******************************//
void DCAN_SID14_PosResponse(U8 SID);
void DCAN_SID19_PosResponse(U8 SID);
void DCAN_PerformService14(void);
void DCAN_PerformService19(void);

void DCAN_WriteDTC01(U8 count);
ErrorStatus DCAN_WriteDTC02(U8 pos, U8* pDTC, bool bWrite);
ErrorStatus DCAN_WriteDTC04(U8* pDTC, U8* pSnapshot);
ErrorStatus DCAN_WriteDTC06(U8* pDTC, U8 ExDataRecNumber, U8 dtc_Number, U8 dtc_Undetermined);
void DCAN_WriteDTC0A(void);

ErrorStatus DRV_WriteData1Eeprom(U32 addr, U8 *buf, U32 pos, U8 len);
ErrorStatus DRV_WriteData2Eeprom(U32 addr, U8 *buf, U32 pos, U8 len);
ErrorStatus DRV_WriteData4Eeprom(U32 addr, U8 *buf, U32 pos, U8 len);
ErrorStatus DRV_WriteData6Eeprom(U32 addr, U8 *buf, U32 pos, U8 len);

//**************************************************************************//
void Jump2Boot(void);
//import from boot EFLS
void EFLS_Init(void);
ErrorStatus EFLS_DRV_FlashReadyCheck(void);
void EFLS_DRV_Read_Data_From_Eemprom(U32 addr, U8 *buf, U32 len);
ErrorStatus EFLS_DRV_Write_Data_To_Eemprom(U32 addr, U8 *buf, U32 len);
ErrorStatus EFLS_DRV_ONLYWrite_FLAG_Data(U32 Start_Address, U8 Data, U8 Order);
//_


extern int rand(void);
extern void OSTK_Delayus(U16 t);
extern void COMM_CANTP_Service_Request(bool Request);
extern void COMM_CANTP_Service_3E_Request(bool Request);
extern U8 EFLS_READ_UPDATE_REQUEST_FLAG(void);
extern void CAN_CFG_ENABLE_TX_APP(void);
extern void CAN_CFG_ENABLE_TX_DIAG(void);
extern void CAN_CFG_DISABLE_TX_APP(void);
extern void CAN_CFG_DISABLE_TX_DIAG(void);
extern void CAN_CFG_ENABLE_RX_DIAG(void);
extern void CAN_CFG_ENABLE_RX_APP(void);
extern void CAN_CFG_ENABLE_RX_APP_DIAG(void);
extern void CAN_CFG_DISABLE_RX_APP_DIAG(void);
extern bool COMM_TP_Dtmrn_Diag_Msg(void);



#endif /* DCAN_DCAN_H_ */

