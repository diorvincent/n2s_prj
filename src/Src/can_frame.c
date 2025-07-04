/*!
    \file  can_frame.c
    \brief can frame application
*/

#include "can_frame.h"


static can_queue_str can_queue;

void queue_init(can_queue_str *p_queue);
void queue_deinit(can_queue_str *p_queue);
uint8_t queue_empty(const can_queue_str *p_queue);
uint8_t queue_full(const can_queue_str *p_queue);
uint8_t queue_push(can_queue_str *p_queue, can_frame_struct *val);
uint8_t queue_pop(can_queue_str *p_queue, can_frame_struct *val);

void CanRxCallBack(void)
{
	can_frame_struct can_rx_data;
	Disable_Irq();
    //#warning CAN报文在此接收
	(void)can_receive_message(&can_rx_data);
	(void)queue_push(&can_queue,&can_rx_data);
	Enable_Irq();
}

void can_queue_init(void)
{
	queue_init(&can_queue);
}

uint8_t can_queue_pop(can_frame_struct *p_frame)
{
	uint8_t rtal;
	Disable_Irq();
	rtal = queue_pop(&can_queue,p_frame);
	Enable_Irq();
	return rtal;
}

void queue_init(can_queue_str *p_queue) {
	p_queue->head = 0x00U;
	p_queue->tail = 0x00U;
}

void queue_deinit(can_queue_str *p_queue) {
	p_queue->head = 0x00U;
	p_queue->tail = 0x00U;
}

uint8_t queue_empty(const can_queue_str *p_queue) {
	if(p_queue->tail == p_queue->head){
		return 0x01U;
	}else{
		return 0x00U;
	}
}

uint8_t queue_full(const can_queue_str *p_queue) {
	uint8_t size = (p_queue->tail + 0x01U);
	size = (size % Can_Queue_Size);
	if(size == p_queue->head){
		return 0x01U;
	}else{
		return 0x00U;
	}
}

uint8_t queue_push(can_queue_str *p_queue, can_frame_struct *val) {
	if (queue_full(p_queue) != 0x00U) {
		return 0x00U;
	}
	else {
		can_frame_copy(&(p_queue->arr[p_queue->tail]),val);
		p_queue->tail = ((p_queue->tail + 0x01U) % Can_Queue_Size);
		return 0x01U;
	}
}

uint8_t queue_pop(can_queue_str *p_queue, can_frame_struct *val) {
	if (queue_empty(p_queue) != 0x00U) {
		return 0x00U;
	}
	else {
		can_frame_copy(val,&(p_queue->arr[p_queue->head]));
		p_queue->head = ((p_queue->head + 0x01U) % Can_Queue_Size);
		return 0x01U;
	}
}


/*!
    \brief      can frame copy
	\param[in]  *to:point to current frame,*from:point to older frame
    \param[out] none
    \retval     none
*/
void can_frame_copy(can_frame_struct *to,can_frame_struct *from)
{
	to->data[0] = from->data[0];
	to->data[1] = from->data[1];
	to->data[2] = from->data[2];
	to->data[3] = from->data[3];
	to->data[4] = from->data[4];
	to->data[5] = from->data[5];
	to->data[6] = from->data[6];
	to->data[7] = from->data[7];
	
	to->dlen = from->dlen;
	to->efid = from->efid;
	to->ff = from->ff;
	to->ft = from->ft;
	to->sfid = from->sfid;
}
