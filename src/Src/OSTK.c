/*
 * OSTK.c
 * OSTK-Operation System Task Schedule
 * Xi'An ManHui Info. Science LLC
 * Created on: Oct 27, 2023
 * Author: He Jingchi
 * Mdodify on: Jun 27, 2024
 */

#include "OSTK.h"
#include "DCAN.h"
#include "BF7006BMxx_config.h"

/*void OSTK_Test(void)
{
    can_frame_struct can_transmit_data;

    can_transmit_data.ff = CAN_STANDARD_FRAME;
    can_transmit_data.ft = CAN_DATA_FRAME;
    can_transmit_data.dlen = 8;
    can_transmit_data.sfid = 0x1;

    can_transmit_message(&can_transmit_data);
    can_transmit_request();
    can_wait_trans();

    return;
}*/

static TaskType VaTaskVar[] =
{
    {0, 10, 10, App_Core_1},		
		{0, 100, 100, App_Core_2},
		{0, 10, 10, COMM_CAN_CFG_RX},
		{0, 10, 10, DCAN_DtrmnService},
		{0, 10, 10, COMM_CANTP_TX_MsgProcess},
		{0, 20, 20, DCAN_Dtrmn3EService},
		//{0, 100, 100, wdt_clear}, //do wdt_clear in Volt_Caculate func 
    //{0, 10, 10, OSTK_Test},
};

void OSTK_Init(void)
{
	SysTick_Config(Cycle1ms);
	SystemCoreClockUpdate();
}


void OSTK_Delayus(U16 t)
{
    U8 i;
    for(; t>0; t--)
    {
        for(i=0; i < 32; i++)
        {
        	__ASM(" NOP");
        }
    }
}


void OSTK_TaskHandler(void)
{
	U8 i = 0;
	for (i = 0; i <TASK_NUM; i++)
	{
		if (VaTaskVar[i].Active)
		{
			VaTaskVar[i].Active = 0;
			VaTaskVar[i].PTaskFuncCb();
		}
	}
}


void OSTK_TaskSchedule(void)
{
	U8 i = 0;
	for (i = 0; i <TASK_NUM; i++)
	{
		if (VaTaskVar[i].TimeCnt)
		{
			VaTaskVar[i].TimeCnt--;
			if (VaTaskVar[i].TimeCnt == 0)
			{
				VaTaskVar[i].Active = 1;
				VaTaskVar[i].TimeCnt = VaTaskVar[i].TimeCntReload;
			}
		}
	}
}


/*void SysTick_Handler(void)
{
	OSTK_TimeTick++;
	OSTK_TaskSchedule();
}
*/


