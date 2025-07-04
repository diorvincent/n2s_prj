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
    static uint8_t busoff_cnt = 0x00U;
    static uint16_t busoff_time = 0x00U;
    if(is_busoff != 0x00U){
        is_busoff = 0x00U;
        can_config();
        busoff_hold = 0x01U;
        busoff_time = 0x00U;
        busoff_cnt ++;
    }
    if(busoff_hold != 0x00U){
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
    }else{
        busoff_cnt = 0x00U;
    }
}
