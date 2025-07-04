/*!
    \file  BF7006BMxx_it.c
    \brief interrupt service routines
*/

#include "RTE_Components.h"
#include "BF7006BMxx.h"
#include "BF7006BMxx_sysctrl.h"

#ifdef BF7x06BMxx_ADC_DRIVER_PRESENT
    #include "BF7006BMxx_adc.h"
#endif
#ifdef BF7x06BMxx_CAN_DRIVER_PRESENT
    #include "BF7006BMxx_can.h"
#endif
#ifdef BF7x06BMxx_EFLASH_DRIVER_PRESENT
    #include "BF7006BMxx_eflash.h"
#endif
#ifdef BF7x06BMxx_GPIO_DRIVER_PRESENT
    #include "BF7006BMxx_gpio.h"
#endif
#ifdef BF7x06BMxx_LIN_DRIVER_PRESENT
    #include "BF7006BMxx_lin.h"
#endif
#ifdef BF7x06BMxx_PWM_DRIVER_PRESENT
    #include "BF7006BMxx_pwm.h"
#endif
#ifdef BF7x06BMxx_RTC_DRIVER_PRESENT
    #include "BF7006BMxx_rtc.h"
#endif
#ifdef BF7x06BMxx_SCI_DRIVER_PRESENT
    #include "BF7006BMxx_sci.h"
#endif
#ifdef BF7x06BMxx_TIMER_DRIVER_PRESENT
    #include "BF7006BMxx_timer.h"
#endif
#ifdef BF7x06BMxx_WDT_DRIVER_PRESENT
    #include "BF7006BMxx_wdt.h"
#endif

#ifdef BF7x06BMxx_CAN_APP_DRIVER_PRESENT
    #include "BF7006BMxx_app_can.h"
#endif

#ifdef BF7x06BMxx_GPIO_DRIVER_PRESENT
/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
    clr_nmi_interrupt_flag();
}
#endif

#define ID_TX  0x267;  //0x18FF7E1E;
extern can_frame_struct can_receive_data;
extern can_frame_struct can_transmit_data;
extern uint8_t is_receive_can_frame;
extern unsigned int can_send_flag;
extern unsigned int SetDutyFlag;

extern unsigned char WorkSts;       //0-关闭 1-工作 2-故障
extern unsigned char WorkSts1;      //0-无故障  1-1级故障  2-2级故障 3-3级故障
extern unsigned char WorkSts2;
extern unsigned char WorkSts3;
extern unsigned char WorkSts4;
//unsigned char WorkSts5;

extern unsigned char ErrSts;//错误状态
extern unsigned char PTCErr;//PTC错误
extern unsigned char PTCErr1;//PTC错误
extern unsigned char PTCErr2;//PTC错误

extern unsigned char T_Flag;

extern unsigned char ADChannel;
extern unsigned int adcvalue1;
extern unsigned int adccount;
extern unsigned char j;  //????
extern unsigned char n;
extern unsigned char o;
extern unsigned char p;
extern unsigned char q;
extern unsigned char r;
extern unsigned char s;
extern unsigned char t;
extern unsigned char u;

extern unsigned int TempData;

extern unsigned int AD_Water_Out1;
extern unsigned int AD_Water_Out11;
extern unsigned int AD_Water_Out12;
extern unsigned int AD_Water_Out13;
extern unsigned int AD_Water_Out14;
extern unsigned int AD_Water_Out15;
extern unsigned int AD_Water_Out17;

extern unsigned int AD_Water_In;

extern unsigned int AD_Water_In1;
extern unsigned int AD_Water_In11;
extern unsigned int AD_Water_In12;
extern unsigned int AD_Water_In13;
extern unsigned int AD_Water_In14;
extern unsigned int AD_Water_In15;
extern unsigned int AD_Water_In17;

extern unsigned int AD_Interlock;
extern unsigned int AD_Interlock1;
extern unsigned int AD_Interlock11;
extern unsigned int AD_Interlock12;
extern unsigned int AD_Interlock13;
extern unsigned int AD_Interlock14;
extern unsigned int AD_Interlock15;
extern unsigned int AD_Interlock17;

extern unsigned int Temp_IGBT1;
extern unsigned int Temp_IGBT;
extern unsigned int TIGBT1;
extern unsigned int TIGBT11;
extern unsigned int TIGBT12;
extern unsigned int TIGBT13;
extern unsigned int TIGBT14;
extern unsigned int TIGBT15;
extern unsigned int TIGBT17;

extern unsigned int AD_15V;
extern unsigned int AD_15V1;
extern unsigned int AD_15V11;
extern unsigned int AD_15V12;
extern unsigned int AD_15V13;
extern unsigned int AD_15V14;
extern unsigned int AD_15V15;
extern unsigned int AD_15V17;

//extern unsigned int Crrt1;
//extern unsigned int Crrt11;
//extern unsigned int Crrt12;
//extern unsigned int Crrt115[65];

extern unsigned int Temp_PTC1; //???
extern unsigned int Temp_PTC2; //???

extern unsigned int TPTC1;
extern unsigned int TPTC11;
extern unsigned int TPTC12;
extern unsigned int TPTC13;
extern unsigned int TPTC14;
extern unsigned int TPTC15;
extern unsigned int TPTC17;

extern unsigned int TPTC2;
extern unsigned int TPTC21;
extern unsigned int TPTC22;
extern unsigned int TPTC23;
extern unsigned int TPTC24;
extern unsigned int TPTC25;
extern unsigned int TPTC27;

extern unsigned int TPCB1;
extern unsigned int TPCB11;
extern unsigned int TPCB12;
extern unsigned int TPCB13;
extern unsigned int TPCB14;
extern unsigned int TPCB15;
extern unsigned int TPCB17;

extern unsigned int Temp_LV; //???

extern unsigned int TLV1;
extern unsigned int TLV11;
extern unsigned int TLV12;
extern unsigned int TLV13;
extern unsigned int TLV14;
extern unsigned int TLV15;
extern unsigned int TLV17;

extern unsigned int Crrt1;
extern unsigned int Crrt11;
extern unsigned int Crrt12;
extern unsigned int Crrt115[65];

extern unsigned int Volt_High;
extern unsigned int Volt_High1;
extern unsigned int Volt_High2;
extern unsigned int Volt_High3;
extern unsigned int Volt_High4;
extern unsigned int Volt_High5;
extern unsigned int Volt_High6;
extern unsigned int Volt_High7; 
extern unsigned int Volt_High22;

extern unsigned int Crrt_High;      //??
extern unsigned int Crrt_High2;
extern unsigned int Curr_H;
extern unsigned int Crrt_High_max;      //????
extern unsigned int Power_High;     //??
extern unsigned int Power_High1; 
extern unsigned int PowerSet;       //请求功率
extern unsigned int PowerTarget;        //实际要求功率
extern unsigned char TempTarget;         //目标温度
extern unsigned int Duty;//400 = 1%
extern unsigned int Duty1;
extern unsigned int Duty2;
extern unsigned int Duty3;
extern unsigned int Duty4;
extern unsigned int PWM_EN; 

extern unsigned char uart_rxdata[50];
extern unsigned char uart_rxflag,uart_rxtime,uart_rxnum;

extern bool g_time0IsBusy;
extern bool g_recvCanDataRdy;
extern unsigned char DCAN_CTRLMSG_STATUS;
extern void OSTK_TaskSchedule(void);
extern void DCAN_NRC78_Send_Task(void *device, uint32_t wpara, uint32_t lpara);

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while (1){
    }
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{

}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{

}

/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{
	OSTK_TaskSchedule();
	can_busoff();
}

/*!
    \brief      system interrupt handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SYS_IRQHandler(void)
{
    uint32_t state = SYS_INTFLG;
    /* eeprom protect range illegal access */
    if((state & SYS_INTFLG_EPOT) != 0x00U){
    }
    /* flash protect range illegal access */
    if((state & SYS_INTFLG_FPOT) != 0x00U){
    }
    /* xtal initialize fail state */
    if((state & SYS_INTFLG_XTALINIT) != 0x00U){
        xtal_timeout = 1;
    }
    /* xtal invalid check state */
    if((state & SYS_INTFLG_XTALCHK) != 0x00U){
        if((SYS_XTAL_CHK & SYS_XTAL_CHK_RSTEN) == 0x00U){
            SYS_XTAL_CTRL &= ~SYS_XTAL_CTRL_EN;
        }
    }
    SYS_INTFLG = state;
}

/*!
    \brief      this function handles lvdt exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void LVDT_IRQHandler(void)
{
    uint8_t int_flag;
    int_flag = lvdt_int_flag_get();
    lvdt_int_flag_clr(int_flag);
}

#ifdef BF7x06BMxx_SCI_DRIVER_PRESENT
/*!
    \brief      sci0 error handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SCI0_ERR_IRQHandler(void)
{
    (void)sci_err_int_flag_get(SCI0);
}

/*!
    \brief      sci0 tx handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SCI0_TX_IRQHandler(void)
{
#ifdef LIN_SCI0
    uint8_t state;
    state = sci_tx_int_flag_get(SCI0);
    if((state & SCI_IF_TX_EMPTY) != 0x00U){
        if(LIN0_Tx_Callback != NULL){
            LIN0_Tx_Callback();
        }
    }
#else
    (void)sci_tx_int_flag_get(SCI0);
#endif
}

/*!
    \brief      sci0 rx handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SCI0_RX_IRQHandler(void)
{
    uint8_t rx_int_state;
    rx_int_state = sci_rx_int_flag_get(SCI0);
#ifdef LIN_SCI0
    if(LIN0_Rx_Callback != NULL){
        if((rx_int_state & SCI_IF_RX_EDGE) != 0x00U){
            sci_rx_edge_int_flag_clr(SCI0);
        }
        LIN0_Rx_Callback(rx_int_state);
    }else{
        if((rx_int_state & SCI_IF_BREAK_CHECK) != 0x00U){
            sci_break_int_flag_clr(SCI0);
            lin_break_check_disable(SCI0);
            }else if((rx_int_state & SCI_IF_RX_FULL) != 0x00U){ 
            (void)sci_data_get(SCI0);
        }else if((rx_int_state & SCI_IF_RX_EDGE) != 0x00U){
            sci_rx_edge_int_flag_clr(SCI0);
        }else{
            (void)sci_data_get(SCI0);
        }
    }
#else
    if((rx_int_state & SCI_IF_BREAK_CHECK) != 0x00U){
        sci_break_int_flag_clr(SCI0);
    #ifdef BF7x06BMxx_LIN_DRIVER_PRESENT
        lin_break_check_disable(SCI0);
    #endif
    }else if((rx_int_state & SCI_IF_RX_FULL) != 0x00U){ 
        (void)sci_data_get(SCI0);
    }else if((rx_int_state & SCI_IF_RX_EDGE) != 0x00U){
        sci_rx_edge_int_flag_clr(SCI0);
    }else{
        (void)sci_data_get(SCI0);
    }
#endif
}

/*!
    \brief      sci1 error handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SCI1_ERR_IRQHandler(void)
{
    (void)sci_err_int_flag_get(SCI1);
}

/*!
    \brief      sci1 tx handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SCI1_TX_IRQHandler(void)
{
#ifdef LIN_SCI1
    uint8_t state;
    state = sci_tx_int_flag_get(SCI1);
    if((state & SCI_IF_TX_EMPTY) != 0x00U){
        if(LIN1_Tx_Callback != NULL){
            LIN1_Tx_Callback();
        }
    }
#else
    (void)sci_tx_int_flag_get(SCI1);
#endif
}

/*!
    \brief      sci1 rx handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SCI1_RX_IRQHandler(void)
{
    /*uint8_t rx_int_state;
    rx_int_state = sci_rx_int_flag_get(SCI1);
#ifdef LIN_SCI1
    if(LIN1_Rx_Callback != NULL){
        if((rx_int_state & SCI_IF_RX_EDGE) != 0x00U){
            sci_rx_edge_int_flag_clr(SCI1);
        }
        LIN1_Rx_Callback(rx_int_state);
    }else{
        if((rx_int_state & SCI_IF_BREAK_CHECK) != 0x00U){
            sci_break_int_flag_clr(SCI1);
            lin_break_check_disable(SCI1);
            }else if((rx_int_state & SCI_IF_RX_FULL) != 0x00U){ 
            (void)sci_data_get(SCI1);
        }else if((rx_int_state & SCI_IF_RX_EDGE) != 0x00U){
            sci_rx_edge_int_flag_clr(SCI1);
        }else{
            (void)sci_data_get(SCI1);
        }
    }
#else
    if((rx_int_state & SCI_IF_BREAK_CHECK) != 0x00U){
        sci_break_int_flag_clr(SCI1);
    #ifdef BF7x06BMxx_LIN_DRIVER_PRESENT
        lin_break_check_disable(SCI1);
    #endif
    }else if((rx_int_state & SCI_IF_RX_FULL) != 0x00U){ 
        uart_rxdata[0]=sci_data_get(SCI1);
    }else if((rx_int_state & SCI_IF_RX_EDGE) != 0x00U){
        sci_rx_edge_int_flag_clr(SCI1);
    }else{
        uart_rxdata[0]=sci_data_get(SCI1);
    }
#endif */
    //uart_rxdata[0]=sci_data_get(SCI1);
		
		uart_rxflag=1;
		uart_rxtime=0;
		uart_rxdata[uart_rxnum]=sci_data_get(SCI1);
		uart_rxnum++;
		if(uart_rxnum>5) uart_rxnum=0;
}
#endif

#ifdef BF7x06BMxx_TIMER_DRIVER_PRESENT
/*!
    \brief      timer0 handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void TIMER0_IRQHandler(void)
{
    timer_intflag_clr(TIMER0);
	
	  g_time0IsBusy = TRUE;
    DCAN_NRC78_Send_Task(NULL, 0, 0);
    g_time0IsBusy = FALSE;
}

/*!
    \brief      timer1 handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void TIMER1_IRQHandler(void)
{
    timer_intflag_clr(TIMER1);
#ifdef LIN_SEL
    lin_overtime_detect();
#endif
}
#endif

#ifdef BF7x06BMxx_PWM_DRIVER_PRESENT
/*!
    \brief      pwm over flow handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PWM_TOF_IRQHandler(void)
{
    pwm_tof_clr();
}

/*!
    \brief      pwm channel 0 handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PWM_CH0_IRQHandler(void)
{
    pwm_ch0_if_clr();
}

/*!
    \brief      pwm channel 1 handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PWM_CH1_IRQHandler(void)
{
    pwm_ch1_if_clr();
}

/*!
    \brief      pwm channel 2 handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PWM_CH2_IRQHandler(void)
{
    pwm_ch2_if_clr();
}

/*!
    \brief      pwm channel 3 handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PWM_CH3_IRQHandler(void)
{
    pwm_ch3_if_clr();
}

/*!
    \brief      pwm channel 4 handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PWM_CH4_IRQHandler(void)
{
    pwm_ch4_if_clr();
}

/*!
    \brief      pwm channel 5 handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PWM_CH5_IRQHandler(void)
{
    pwm_ch5_if_clr();
}
#endif

#ifdef BF7x06BMxx_RTC_DRIVER_PRESENT
/*!
    \brief      rtc handler
    \param[in]  none
    \param[out] none
    \retval     none
*/

void RTC_IRQHandler(void)
{
    //rtc_int_flag_clr();
	  //static uint8_t time_flag = 0;
		
	if(SetDutyFlag<250) 
			SetDutyFlag++;
		//if(uart_rxtime<250) uart_rxtime++;
		rtc_int_flag_clr();
		ADChannel=0;
		adc_start_convert(ADC_CH_0(0));	  

		if(DCAN_CTRLMSG_STATUS == 1) //DefaultStatus / EnRXDisTXAppMsg / DisRXEnTXAppMsg
		{						
			if(can_send_flag++ >= 999)    //每隔1000ms做一次
			{
					can_send_flag=0;
					/* load transmit data */
					can_transmit_data.ff = CAN_STANDARD_FRAME;
					can_transmit_data.ft = CAN_DATA_FRAME;
					can_transmit_data.dlen = 8;
					can_transmit_data.sfid = ID_TX;
					//can_transmit_data.efid = ID_TX;
					can_transmit_data.data[0] = WorkSts1;//WorkSts2;
					can_transmit_data.data[1] = Crrt_High2;   //电流
					can_transmit_data.data[2] = Volt_High22/256;  //电压
					can_transmit_data.data[3] = Volt_High22%256;   
					can_transmit_data.data[4] = Power_High1;
					can_transmit_data.data[5] = Power_High/100;
					can_transmit_data.data[6] = Temp_PTC1;
					//T_Flag++;
					//if(T_Flag>15) T_Flag=0;
					can_transmit_data.data[7] = 0;

					/* load data into registers and send frame */
					can_transmit_message(&can_transmit_data);
					can_transmit_request();					  
			}	
		
		}
	
    //time_flag = ~time_flag;
    //if(time_flag)
    //    gpio_bit_reset(GPIOB,GPIO_PIN_2);
    //else 
    //    gpio_bit_set(GPIOB,GPIO_PIN_2);
}
#endif

#ifdef BF7x06BMxx_CAN_DRIVER_PRESENT
/*!
    \brief      can wake up handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void CAN_WAKE_IRQHandler(void)
{
    (void)can_interrupt_flag_get();
    can_int_flag_clr(CAN_IF_WUPI);
}

/*!
    \brief      can error handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void CAN_ERR_IRQHandler(void)
{
    uint8_t state;
    state = can_interrupt_flag_get();
    (void)can_read_frame_error_code();
    if((state & CAN_IF_BEI) != 0x00U){          /* bus error */
        can_int_flag_clr(CAN_IF_BEI);
    }
    if((state & CAN_IF_ALI) != 0x00U){          /* arbitration lost */
        (void)can_read_arbitration_lost_code();
        can_int_flag_clr(CAN_IF_ALI);
    }
    if((state & CAN_IF_EPI) != 0x00U){          /* error passive */
        can_transmit_abort();
        can_int_flag_clr(CAN_IF_EPI);
    }
    if((state & CAN_IF_DOI) != 0x00U){          /* data overflow */
        can_int_flag_clr(CAN_IF_DOI);
    }
    if((state & CAN_IF_EI) != 0x00U){           /* error interrupt or bus state change */
        if((can_status_get() & CAN_SR_BS) == CAN_BUS_OFF){  //can bus off
#ifdef BF7x06BMxx_CAN_APP_DRIVER_PRESENT
        is_busoff = 0x1U;
#endif
        }
        can_int_flag_clr(CAN_IF_EI);
    }
}

/*!
    \brief      can rx handler
    \param[in]  none
    \param[out] none
    \retval     none
*/

void CAN_RX_IRQHandler(void)
{
    (void)can_interrupt_flag_get();
	  can_receive_message(&can_receive_data);
		g_recvCanDataRdy = TRUE;
    is_receive_can_frame = 1;
	
	#ifdef BF7x06BMxx_CAN_APP_DRIVER_PRESENT
    busoff_hold = 0x0U;
#endif
}

/*!
    \brief      can tx handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void CAN_TX_IRQHandler(void)
{
    (void)can_interrupt_flag_get();
    can_int_flag_clr(CAN_IF_TI);
	
	#ifdef BF7x06BMxx_CAN_APP_DRIVER_PRESENT
    if(busoff_hold != 0){       //can send frame success,exit bus-off mode
        busoff_hold = 0x00;
    }
	#endif
		
}
#endif

#ifdef BF7x06BMxx_GPIO_DRIVER_PRESENT
/*!
    \brief      gpioA/B/D interrupt handler
    \param[in]  none
    \param[out] none
    \retval     none
*/
void GPIO_IRQHandler(void)
{
    /*static uint8_t time_flag = 0;
    time_flag = ~time_flag;
    if(time_flag)
    {
        gpio_bit_set(GPIOD,GPIO_PIN_2);
    }
    else
    {
        gpio_bit_reset(GPIOD,GPIO_PIN_2);
    } */
    uint8_t stateA = get_gpio_port_interrupt_state((uint32_t)GPIOA);
    uint8_t stateB = get_gpio_port_interrupt_state((uint32_t)GPIOB);
    uint8_t stateD = get_gpio_port_interrupt_state((uint32_t)GPIOD);
    clr_gpio_interrupt_state((uint32_t)GPIOA,stateA);
    clr_gpio_interrupt_state((uint32_t)GPIOB,stateB);
    clr_gpio_interrupt_state((uint32_t)GPIOD,stateD);
}
#endif

#ifdef BF7x06BMxx_ADC_DRIVER_PRESENT
/*!
    \brief      ADC interrupt handler
    \param[in]  none
    \param[out] none
    \retval     none
*/

void ADC_IRQHandler(void)
{
    uint16_t temp = adc_data_get();
	  adcvalue1=temp;
	  //adccount++;
	switch(ADChannel) 
  {
    case 0:       //-------------AD_IGBT
         if(adcvalue1 < 5000)
         {
    			  TempData = adcvalue1;       //ADP6-48?-????15V
      		  if(p<5)
      		    p++;
      		  if(p == 1)
      		   TIGBT11 = TempData;
      		  else if(p == 2)
      		   TIGBT12 = TempData;
      		  else if(p == 3)
      		   TIGBT13 = TempData;
      		  else if(p == 4)
      		   TIGBT14 = TempData;
      		  else if(p == 5)
      		  {
      		   TIGBT15 = TempData;
      		   p=0;
      		   }
          }
    	 ADChannel = 7;
			 adc_start_convert(ADC_CH_0(7));
    	 
    break;  
    case 7:      //---------------HV_V

         if(adcvalue1 < 5000)
         {
    			  TempData = adcvalue1;       //ADP6-48?-????15V
      		  if(u<5)
      		    u++;
      		  if(u == 1)
      		   Volt_High1 = TempData;
      		  else if(u == 2)
      		   Volt_High2 = TempData;
      		  else if(u == 3)
      		   Volt_High3 = TempData;
      		  else if(u == 4)
      		   Volt_High4 = TempData;
      		  else if(u == 5)
      		  {
      		   Volt_High5 = TempData;
      		   u=0;
      		   }
          }		
    	 ADChannel = 8;
    	 adc_start_convert(ADC_CH_0(8));
    break;
    case 8:     //--------------TPTC2
       if(adcvalue1 < 5000)
    	 {    		    
      		  TempData = adcvalue1;   		  
      		  if(n<5)
      		    n++;
      		  if(n == 1)
      		    TPTC21 = TempData;
      		  else if(n == 2)
      		    TPTC22 = TempData;
      		  else if(n == 3)
      		    TPTC23 = TempData;
      		  else if(n == 4)
      		    TPTC24 = TempData;
      		  else if(n == 5)
      		  {
      		    TPTC25 = TempData;
      		    n=0;
      		   } 
    	 }
    	 ADChannel = 9;
    	 adc_start_convert(ADC_CH_0(9));
    break;
    case 9:    //------------------TPTC1
        	if(adcvalue1 < 5000)
    	    {
    	      TempData = adcvalue1;
      		  if(o<5)
      		    o++;
      		  if(o == 1)
      		    TPTC11 = TempData;
      		  else if(o == 2)
      		    TPTC12 = TempData;
      		  else if(o == 3)
      		    TPTC13 = TempData;
      		  else if(o == 4)
      		    TPTC14 = TempData;
      		  else if(o == 5)
      		  {
      		    TPTC15 = TempData;
      		    o=0;
      		   }      
    		  }  
    	 ADChannel = 10;
    	 adc_start_convert(ADC_CH_0(10));
    break;
    case 10:    //AD_TPCB	
         if(adcvalue1 < 5000)
         {
    			  TempData = adcvalue1;       //ADP6-48?-????15V
      		  if(t<5)
      		    t++;
      		  if(t == 1)
      		   TPCB11 = TempData;
      		  else if(t == 2)
      		   TPCB12 = TempData;
      		  else if(t == 3)
      		   TPCB13 = TempData;
      		  else if(t == 4)
      		   TPCB14 = TempData;
      		  else if(t == 5)
      		  {
      		   TPCB15 = TempData;
      		   t=0;
      		   }
          }		
    	 ADChannel = 14;
    	 adc_start_convert(ADC_CH_0(14));          				 
    break;
    case 14:    //------------------AD_15V
				 if(adcvalue1 < 5000)
         {
    			  TempData = adcvalue1;       //ADP6-48?-????15V
      		  if(q<5)
      		    q++;
      		  if(q == 1)
      		   AD_15V11 = TempData;
      		  else if(q == 2)
      		   AD_15V12 = TempData;
      		  else if(q == 3)
      		   AD_15V13 = TempData;
      		  else if(q == 4)
      		   AD_15V14 = TempData;
      		  else if(q == 5)
      		  {
      		   AD_15V15 = TempData;
      		   q=0;
      		   }
          }
    	 ADChannel = 15;
    	 adc_start_convert(ADC_CH_0(15));
    break;
    case 15:    //------------------HV_I
         if(adcvalue1 < 5000)
         {
    			  TempData = adcvalue1;       //ADP6-48?-????15V
            Crrt115[r]=TempData;
            r++;
	          if(r>=120) r=0;
          }
    break;  							
    default:
    break;
  }
}
#endif

