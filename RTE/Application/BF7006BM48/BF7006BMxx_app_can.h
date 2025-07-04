/*!
    \file  BF7006BMxx_hal_can.h
    \brief can hardware abstrast layer definition
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, BF7006BMxx_app_can.h initial version
*/

#ifndef BF7006BMxx_APP_CAN_H
#define BF7006BMxx_APP_CAN_H

#include "BF7006BMxx_can.h"
#include "DCAN.h"

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------
//  <o> Can bus-off fast recovery time (ms)
//  <i> Can bus-off fast recovery time, unit: ms
#define Can_BusOff_FastRecv     ((uint16_t)50)  //can busoff fast recovery in ms

//  <o> Can bus-off slow recovery time (ms)
//  <i> Can bus-off slow recovery time, unit: ms
#define Can_BusOff_SlowRecv     ((uint16_t)200) //can busoff slow recovery in ms



/* can busoff handling function */
void can_busoff(void);
/* can ms event function */
void can_ms_event(void);
void can_busoffinit(void);

extern uint8_t is_busoff;
extern uint8_t busoff_hold;
extern can_frame_struct bus_off_frame;
extern uint8_t DCAN_19_01_DTC_CNT;

#endif
