/*
 * OSTK.h
 * OSTK-Multiple Task Schedule Control
 * Xi'An ManHui Info. Science LLC
 * Created on: Oct 27, 2023
 * Author: He Jingchi
 */

#ifndef OSTK_OSTK_H_
#define OSTK_OSTK_H_

/* ===========================================  Includes  =========================================== */
#include <string.h>
#include "BF7006BMxx_config.h"
#include "DATA_TYPE.h"


/* ===========================================  Typedef  ============================================ */
typedef struct
{
	U8		Active;
	U16		TimeCnt;
	U16		TimeCntReload;
	void	(*PTaskFuncCb)(void);
} TaskType;


/* ============================================  Define  ============================================ */
#define SYSCLK_FREQ 		32000000
#define Cycle1ms    		(SYSCLK_FREQ / 1000)
#define TASK_NUM				(sizeof(VaTaskVar) / sizeof(VaTaskVar[0]))

/* ==========================================  Variables  =========================================== */

/* ====================================  Functions declaration  ===================================== */
static void (*TaskScheduleFunc) (void);
void OSTK_TaskSchedule(void);
void OSTK_TaskHandler(void);
void OSTK_Init(void);
void OSTK_Delayus(U16 t);
extern void CMTX_SendMsg0(void);
extern void COMM_CAN_CFG_RX(void);
extern void App_Core_1(void);
extern void App_Core_2(void);
#endif /* OSTK_OSTK_H_ */






