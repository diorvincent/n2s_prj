/*
 * CAN_CFG.c
 * Xi'An ManHui Info. Science LLC
 * Created on: Oct 31, 2023
 * Author: Xue Le
 */
#include "CAN_CFG.h"
#include "CAN_TP.h"
#include "BF7006BMxx_config.h"

__IO bool CAN_CFG_DIAG_NewMsgFlag;
__IO bool CAN_CFG_DIAG_NewFunMsgFlag;
__IO bool CAN_CFG_DIAG_3E_NewMsgFlag;
__IO bool CAN_CFG_DIAG_3E_NewFunMsgFlag;

U32 sendDataBuff[64/4];
U32 recvDataBuff[64/4];

CAN_MsgInfoType g_sendCANMsgInfo;
CAN_MsgInfoType g_recvCANMsgInfo;

bool g_recvCanDataRdy = FALSE;
bool g_sendCanDataRdy = TRUE;

extern can_frame_struct can_receive_data;


/*CAN_FilterControlType canDiagFilterControl[]=
{
	{0, DISABLE, APP_START_ID, APP_END_ID},
	{1, ENABLE, PhysicalRequestCANID, 0x000},
	{2, ENABLE, FunctionalRequestCANID, 0x000},
};

CAN_FilterControlType canAPPFilterControl[]=
{
	{0, ENABLE, APP_START_ID, APP_END_ID},
	{1, DISABLE, PhysicalRequestCANID, 0x000},
	{2, DISABLE, FunctionalRequestCANID, 0x000},
};

CAN_FilterControlType canAPP_DiagFilterControl[]=
{
	{0, ENABLE, APP_START_ID, APP_END_ID},
	{1, ENABLE, PhysicalRequestCANID, 0x000},
	{2, ENABLE, FunctionalRequestCANID, 0x000},
};

CAN_FilterControlType canAPP_DiagDisFilterControl[]=
{
	{0, DISABLE, APP_START_ID, APP_END_ID},
	{1, DISABLE, PhysicalRequestCANID, 0x000},
	{2, DISABLE, FunctionalRequestCANID, 0x000},
};
*/

void COMM_CAN_Init(void)
{
    g_sendCANMsgInfo.DATA = (U8 *)sendDataBuff;
    g_recvCANMsgInfo.DATA = (U8 *)recvDataBuff;

    CAN_CFG_DIAG_NewMsgFlag = FALSE;
    CAN_CFG_DIAG_NewFunMsgFlag = FALSE;

    CAN_CFG_DIAG_3E_NewMsgFlag = FALSE;
    CAN_CFG_DIAG_3E_NewFunMsgFlag = FALSE;

    g_recvCanDataRdy = FALSE;
    g_sendCanDataRdy = TRUE;

    return;
}

void COMM_CAN_CFG_TX(const CAN_MsgInfoType *info)
{
    can_frame_struct CAN_TRANSMIT_DATA;

    CAN_TRANSMIT_DATA.ff = CAN_STANDARD_FRAME;
    CAN_TRANSMIT_DATA.ft = CAN_DATA_FRAME;
    CAN_TRANSMIT_DATA.dlen = info->DLC;
    CAN_TRANSMIT_DATA.sfid = info->ID;

    for(U8 i = 0; i < CAN_TRANSMIT_DATA.dlen; i++)
    {
        CAN_TRANSMIT_DATA.data[i] = info->DATA[i];
    }

    if(g_sendCanDataRdy == TRUE) {
        g_sendCanDataRdy = FALSE;
        can_transmit_message(&CAN_TRANSMIT_DATA);
        can_transmit_request();
        can_wait_trans();
    }

    g_sendCanDataRdy = TRUE;

    return;
}

void COMM_CAN_CFG_RX()
{
    if(g_recvCanDataRdy == TRUE)
    {
        g_recvCANMsgInfo.DLC = can_receive_data.dlen;
        g_recvCANMsgInfo.ID = can_receive_data.sfid;
        for(U8 i = 0; i < can_receive_data.dlen; i++)
        {
            g_recvCANMsgInfo.DATA[i] = can_receive_data.data[i];
        }

        if (g_recvCANMsgInfo.ID == PhysicalRequestCANID)
        {
            if((g_recvCANMsgInfo.DATA[0] == 0x02) && (g_recvCANMsgInfo.DATA[1] == 0x3E)) {
                CAN_CFG_DIAG_3E_NewMsgFlag = TRUE;
                CAN_CFG_DIAG_3E_NewFunMsgFlag = FALSE;
            } else {
                CAN_CFG_DIAG_NewMsgFlag = TRUE;
                CAN_CFG_DIAG_NewFunMsgFlag = FALSE;
            }
        }
        else if(g_recvCANMsgInfo.ID == FunctionalRequestCANID)
        {
            if((g_recvCANMsgInfo.DATA[0] == 0x02) && (g_recvCANMsgInfo.DATA[1] == 0x3E)) {
                CAN_CFG_DIAG_3E_NewMsgFlag = FALSE;
                CAN_CFG_DIAG_3E_NewFunMsgFlag = TRUE;
            } else {
                CAN_CFG_DIAG_NewMsgFlag = FALSE;
                CAN_CFG_DIAG_NewFunMsgFlag = TRUE;
            }
        }
        else
        {
            CAN_CFG_DIAG_NewMsgFlag = FALSE;
            CAN_CFG_DIAG_NewFunMsgFlag = FALSE;

            CAN_CFG_DIAG_3E_NewMsgFlag = FALSE;
            CAN_CFG_DIAG_3E_NewFunMsgFlag = FALSE;
        }
        g_recvCanDataRdy = FALSE;

        COMM_CANTP_RX_MsgProcess();
    }

    return;
}

