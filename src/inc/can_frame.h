/*!
    \file  can_frame.h
    \brief definitions for can frame
*/


#ifndef CAN_FRAME_H
#define	CAN_FRAME_H

#include "BF7006BMxx.h"
#include "BF7006BMxx_can.h"

#define Can_Queue_Size		((uint8_t)64)

/* can queue struct */
typedef struct {
	can_frame_struct arr[Can_Queue_Size];
	uint8_t head; 
	uint8_t tail; 
}can_queue_str;


void CanRxCallBack(void);
void can_frame_copy(can_frame_struct *to,can_frame_struct *from);
uint8_t can_queue_pop(can_frame_struct *p_frame);
void can_queue_init(void);

#endif
