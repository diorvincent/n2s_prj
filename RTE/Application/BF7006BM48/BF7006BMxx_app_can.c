/*!
    \file  BF7006BMxx_hal_can.c
    \brief can hareware abstract layer driver
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_app_can.c initial version
*/

#include "BF7006BMxx_app_can.h"
#include "BF7006BMxx_config.h"


uint8_t is_busoff = 0x00U;
uint8_t busoff_hold = 0x00U;
static uint8_t busoff_cnt = 0x00U;
static uint16_t busoff_time = 0x00U;
can_frame_struct bus_off_frame = { 0 };

/*!
    \brief      can bus-off recovery function
    \param[in]  none
    \param[out] none
    \retval     none
    \info       user should call this function every 1ms
*/
/* User could disable this warning by defining the following macro definition */
#ifndef NO_WARNING_CAN_BUS_OFF_CALL
    #warning User should call function can_busoff() every 1ms
#endif

void can_busoff(void)
{
    if(is_busoff != 0x00U)
		{
        is_busoff = 0x00U;
        can_config();
        busoff_hold = 0x01U;
        busoff_time = 0x00U;
        busoff_cnt ++;
			
				can_busoffinit();
    }
		can_ms_event();
}

void can_busoffinit(void)
{
	bus_off_frame.ff = CAN_STANDARD_FRAME;
	bus_off_frame.ft = CAN_DATA_FRAME;
	bus_off_frame.dlen = 8;
	bus_off_frame.sfid = 0x267;
	bus_off_frame.data[0] = 0x0;
	bus_off_frame.data[1] = 0x0;
	bus_off_frame.data[2] = 0x0;
	bus_off_frame.data[3] = 0x0;
	bus_off_frame.data[4] = 0x0;
	bus_off_frame.data[5] = 0x0;
	bus_off_frame.data[6] = 0x0;
	bus_off_frame.data[7] = 0xB0; //bus_off byte
}

void can_ms_event(void)
{
    if(busoff_hold != 0x00U)
		{					
			busoff_time ++;
			if(busoff_cnt < 0x05U){
					if(busoff_time >= Can_BusOff_FastRecv){ //can fast recovery 50ms 5times
							busoff_time = (Can_BusOff_FastRecv - 0x02U);
							if(is_can_txbuf_empty()){
									can_transmit_message(&bus_off_frame);
									can_transmit_request();
							}
					}
			}else{
					if(busoff_time >= Can_BusOff_SlowRecv){	//can slow recovery 200ms
							busoff_time = (Can_BusOff_SlowRecv - 0x02U);
							if(is_can_txbuf_empty()){
									can_transmit_message(&bus_off_frame);
									can_transmit_request();
							}
					}
					busoff_cnt = 0x05U;
			}
			
			//record bus_off DTC
			if(_C07300++>5)
				_C07300 = 1;
			
			DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
			DCAN_WriteDTC02(84, (uint8_t*)&DTC_C07300, true);
    }
		else
		{
      busoff_cnt = 0x00U;
    }	
}
