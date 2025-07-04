#include "BF7006BMxx_config.h"
#include "app_interface.h"

#include "OSTK.h"
#include "DCAN.h"
#include "CAN_CFG.h"
#include "CAN_TP.h"


can_frame_struct can_transmit_data;
can_frame_struct can_receive_data;
uint8_t is_receive_can_frame = 0;
unsigned int adcvalue1=0;
unsigned int adccount=0;
unsigned char uart_txdata[10]={1,2,3,4,5,6,7,8,9,10};
unsigned char uart_rxdata[50]={0,0,0,0,0,0,0,0,0,0};
unsigned char uart_rxflag=0,uart_rxtime=0,uart_rxnum=0;

/* ---------- FLASH related definitions ---------- */
#define	FLASH_DataPage  (95U)                   /* FLASH page to be operated, 95 is last page */
#define	FLASH_DataAddr  (FLASH_BASE + (FLASH_SECTOR_SIZE * FLASH_DataPage)) /* FLASH address to be operated */

volatile uint8_t flashStartDeal = 0U;           /* FLASH start deal flag */
uint32_t flashData[] = 
{
    0x77555555U,
    0x66666666U,
    0x77777777U,
    0x55888888U,
};
uint32_t flashDataLen = sizeof(flashData) / 4U; /* word len */
volatile uint8_t flashFaultFlag = 0U;          /* FLASH deal fault flag */

volatile uint8_t DCAN_19_01_DTC_CNT;

//unsigned int etemp[4]={0};
unsigned int ftemp[4]={0};

#define MaxPercent                 50000 //最大占空比100%
#define RatedPower                 3500  //额定功率8000W 

#define HVOver                     530   //高压报警
#define HVOverRecover              510   //高压恢复
#define HVUnder                    290    //低压报警
#define HVUnderRecover             310    //低压恢复

#define Crrt_HighOver              200   //过流定制
#define Crrt_HighOverDerating      150   //????
#define Crrt_HighOverRecover       150   //过流恢复

#define IGBT_OverTemp              150   //IGBT过温保护
#define IGBT_OverTempDerating      150   //IGBT????(???-40)
#define IGBT_OverTempRecover       140   //IGBT过温恢复

#define PCB_OverTemp              150   //PCB过温保护
#define PCB_OverTempRecover       140   //PCB过温恢复

#define PTCOverTemp                150   //PTC过温保护
#define PTCOverTempRecover         140   //PTC过温保护恢复

#define MessageTimeout             10    //通讯超时报警定值

#define MaxKValueNum               5     //短路保护次数

unsigned char IsStartTestMyself = 0;

unsigned int Crrt_High = 0;      //??
unsigned int Crrt_High1=0,Crrt_High2=0;
unsigned int Curr_H = 0;
unsigned int Crrt_High_max = 0;      //????
unsigned int Power_High=0,Power_High1=0;     //??
unsigned int PowerSet_limit=7000;
unsigned int Volt_High22=0;

unsigned int Duty=0;//400 = 1%
unsigned int Duty1=0;
unsigned int Duty2=0;
unsigned int Duty3=0;
unsigned int Duty4=0;

unsigned int SetDutyFlag=0;
unsigned int PWM_EN=0;    //PTC使能
unsigned char PWM_EN1=0;
unsigned int WorkPtcNum = 0;

unsigned int K1Value=0; //短路保护
unsigned int K1=0;    //短路保护
unsigned int RK1=0;     //短路保护
unsigned char IsK1=0;

unsigned int K2=0;
unsigned int K2hightime=0;
unsigned int K2lowtime=0;
unsigned char HLOCK_ERR=0;

unsigned char Cnt01=0;	//
unsigned char Cnt02=0;	//
unsigned char Cnt03=0;	//
unsigned char Cnt04=0;	//
unsigned char Cnt05=0;	//
unsigned char Cnt06=0;	//
unsigned char Cnt07=0;	//
unsigned char Cnt08=0;	//
unsigned char Cnt09=0;	//
unsigned char Cnt10=0;	//
unsigned char Cnt11=0;	//
unsigned char Cnt12=0;	//
unsigned char Cnt13=0;	//
unsigned char Cnt14=0;	//
unsigned char Cnt15=0;	//
unsigned char Cnt16=0;
unsigned char Cnt17=0;
unsigned char Cnt18=0;
unsigned char Cnt19=0;
unsigned char Cnt20=0;
unsigned char Cnt21=0;
unsigned char Cnt22=0;
unsigned char Cnt23=0;
unsigned char Cnt24=0;
unsigned char Cnt25=0;
unsigned char Cnt28=0;
unsigned char Cnt29=0;
unsigned char Cnt30=0;
unsigned char Cnt31=0;
unsigned char Cnt34=0;
unsigned char Cnt35=0;
unsigned char Cnt36=0;
unsigned char Cnt37=0;
unsigned char Cnt50=0;
unsigned char Cnt51=0;
unsigned char Cnt52=0;
unsigned char Cnt53=0;
unsigned char Cnt54=0;
unsigned char Cnt55=0;
unsigned char Cnt56=0;
unsigned char Cnt57=0;
unsigned char Cnt100=0; //Boot接收计时

unsigned char ADChannel=0;
unsigned char j=0;  //
unsigned char n=0;
unsigned char o=0;
unsigned char p=0;
unsigned char q=0;
unsigned char r=0;
unsigned char s=0;
unsigned char t=0;
unsigned char u=0;
unsigned char v=0;
unsigned char w=0;
unsigned char vv=0;

unsigned int TempData=0;
unsigned int Temp_IGBT=0;

unsigned int TIGBT1=0;
unsigned int TIGBT11=0;
unsigned int TIGBT12=0;
unsigned int TIGBT13=0;
unsigned int TIGBT14=0;
unsigned int TIGBT15=0;
unsigned int TIGBT17=0;

unsigned int AD_15V=0;
unsigned int AD_15V1=0;
unsigned int AD_15V11=0;
unsigned int AD_15V12=0;
unsigned int AD_15V13=0;
unsigned int AD_15V14=0;
unsigned int AD_15V15=0;
unsigned int AD_15V17=0;

unsigned int AD_Interlock=0;
unsigned int AD_Interlock1=0;
unsigned int AD_Interlock11=0;
unsigned int AD_Interlock12=0;
unsigned int AD_Interlock13=0;
unsigned int AD_Interlock14=0;
unsigned int AD_Interlock15=0;
unsigned int AD_Interlock17=0;

unsigned int Crrt1=0;
unsigned int Crrt11=0;
unsigned int Crrt12=0;
unsigned int Crrt115[150];

unsigned int Temp_PTC1=0; //???
unsigned int Temp_PTC2=0; //???

unsigned int Temp_PTC11=0;
unsigned int Temp_PTC12=0;
unsigned int Temp_PTC13=0;

unsigned int TPTC1=0;
unsigned int TPTC11=0;
unsigned int TPTC12=0;
unsigned int TPTC13=0;
unsigned int TPTC14=0;
unsigned int TPTC15=0;
unsigned int TPTC17=0;

unsigned int TPTC2=0;
unsigned int TPTC21=0;
unsigned int TPTC22=0;
unsigned int TPTC23=0;
unsigned int TPTC24=0;
unsigned int TPTC25=0;
unsigned int TPTC27=0;

unsigned int TPCB1=0;
unsigned int TPCB11=0;
unsigned int TPCB12=0;
unsigned int TPCB13=0;
unsigned int TPCB14=0;
unsigned int TPCB15=0;
unsigned int TPCB17=0;

unsigned int Temp_LV=0; //???

unsigned int TLV1=0;
unsigned int TLV11=0;
unsigned int TLV12=0;
unsigned int TLV13=0;
unsigned int TLV14=0;
unsigned int TLV15=0;
unsigned int TLV17=0;

unsigned int Volt_High=0;
unsigned int Volt_High1=0;
unsigned int Volt_High2=0;
unsigned int Volt_High3=0;
unsigned int Volt_High4=0;
unsigned int Volt_High5=0;
unsigned int Volt_High6=0;
unsigned int Volt_High7=0; 

unsigned int Volt_IGBTDriver=0;
unsigned int Volt_IGBTDriver7=0;


//---CAN
//#define ID_TX  0x18FF7E1E;      //PTC-ID  PC-ID
//#define ID_TX1 0x351      //?????????--?????
#define ID_RXBOOT 0x729 		//0x74D  //0x18FFF202      //APP2Boot-ID 
#define ID_RX  0x251  //0x18FFF202      //ECU-ID

unsigned char WorkSts=0;       
unsigned char WorkSts1=0;      
unsigned char WorkSts2=0;
unsigned char WorkSts3=0;
unsigned char WorkSts4=0;
//unsigned char WorkSts5=0;
//unsigned char WorkStsdata=0;

unsigned char Fault1 = 0;    //??1
unsigned char Fault2 = 0;    //??2
unsigned char Fault3 = 0;    //??3
unsigned char SFault = 0;    //????
unsigned char Volt_High_Flag=0;

unsigned int Temp_PCB1=0;    //IGBT??

//unsigned char Version = 0; //????
unsigned char OutOfTime = 0; //通讯超时计时

unsigned int PowerSet = 0;   //请求功率
unsigned int PowerTarget=0;  //实际要求功率
unsigned char TempTarget = 0;//目标温度
unsigned char OFF=0;
unsigned char T_Flag = 0;
//unsigned char CANEN_Flag = 0;  		//Busoff
unsigned int can_send_flag = 1000;  //CAN发送周期
unsigned char led=0;


//IGBT温度表
const	unsigned int	Temp_IGBTNum[191]={     //12K?? 
		303470,283680,265410,248530,232900,218430,205010,192550,180980,170210,      //-40
		160190,150850,142140,134020,126430,119330,112690,106470,100650,95185,       //-30
		90060,85249,80728,76479,72482,68719,65176,61838,58691,55722,                //-20
		52920,50275,47776,45414,43181,41069,39070,37178,35386,33689,                //-10
		32080,30532,29065,27675,26357,25109,23925,22802,21738,20727,                //0
		19769,18859,17996,17176,16397,15658,14955,14288,13653,13050,                //10
		12476,11930,11411,10917,10447,10000,9550,9125,8724,8344,                    //20
		7985,7644,7321,7015,6724,6448,6185,5935,5698,5471,                          //30
		5256,5050,4854,4667,4489,4318,4155,4000,3851,3708,                          //40
		3571,3441,3316,3195,3080,2970,2864,2762,2665,2571,                          //50
		2481,2395,2311,2231,2154,2080,2009,1941,1874,1811,                          //60
		1750,1691,1634,1579,1526,1475,1426,1378,1333,1288,                          //70
		1246,1205,1165,1127,1090,1054,1019,986,954,923,                             //80
		892,863,835,808,782,756,732,708,685,663,                                    //90
		641,624,607,591,575,559,544,529,515,501,                                    //100
		488,474,462,449,437,425,414,403,392,381,                                    //110
		371,361,352,342,333,324,316,308,300,292,                                    //120
		284,277,270,263,256,250,243,237,231,225,                                    //130
		220,214,209,204,199,194,189,185,180,176,                                    //140
		172,                                                                        //150
};

//PTC温度表
const	unsigned int Temp_PTCNum[221]={      //????50K                                                           //180
			1677600,1564700,1460700,1364900,1276500,1194800,1119200,1049300,9843800,9241500,      //-40
			868200,816160,767720,722590,680490,641200,604490,570170,538050,507980,       //-30
			479800,453370,428570,405290,383400,362830,343480,325260,308110,291940,                //-20
			276700,262330,248760,235950,223860,212430,201630,191410,181750,172610,                //-10
			163950,155510,147630,140260,133350,126870,120770,115030,109620,104500,                //0
			99670,95093,90754,86636,82723,79002,75460,72085,68866,65794,                //10
			62860,60056,57374,54809,52352,50000,47819,45747,43780,41910,                //20
			40133,38443,36835,35304,33847,32460,31138,29877,28676,27530,                //30
			26437,25394,24398,23447,22538,21670,20840,20047,19288,18563,                //40
			17868,17203,16567,15957,15373,14813,14277,13763,13270,12797,                //50
			12343,11908,11490,11089,10703,10333,9977,9636,9307,8992,                    //60
			8688,8396,8115,7845,7585,7335,7094,6862,6639,6424,                          //70
			6217,6017,5824,5639,5460,5288,5121,4961,4806,4657,                   //80
			4513,4374,4239,4110,3984,3864,3747,3634,3525,3420,                   //90
			3318,3217,3121,3028,2939,2853,2770,2690,2613,2539,                   //100
			2467,2398,2331,2267,2204,2144,2086,2030,1975,1922,                   //110
			1871,1822,1774,1727,1683,1639,1597,1556,1516,1477,                   //120
			1440,1403,1368,1333,1300,1267,1236,1205,1175,1146,              //130
			1118,1091,1064,1038,1013,988,964,940,918,895,                   //140
			874,855,836,818,801,783,766,750,734,718,                        //150
			702,687,673,658,644,630,617,604,591,578,                        //160
			566,554,542,531,520,509,498,488,478,468,                        //170
			458,    
};

//-----------------------------------------------------------------------------
unsigned int GetIGBTTemp(unsigned int data)
{
  static unsigned int i;
  for(i=0;i<191;i++)
  {
    if(data > Temp_IGBTNum[0])
      break;
    if((data < Temp_IGBTNum[i])&&(data >= Temp_IGBTNum[i+1]))   
      break;
  }
  return i;
}
//-----------------------------------------------------------------------------
unsigned int GetPTCTemp(unsigned int data)
{
  static unsigned int i;
  for(i=0;i<221;i++)
  {
    if(data > Temp_PTCNum[0])
      break;
    if((data < Temp_PTCNum[i])&&(data >= Temp_PTCNum[i+1]))    
      break;
  }
  return i;
}

void delay(uint16_t time);

//系统初始化
void sys_init(void)
{
	  /*
     * Multiple startup options are available in Startup -> BF7006BMxx_config.c -> Configuration Wizard
     * Please configure in Startup -> BF7006BMxx_config.c -> Configuration Wizard
     */
	  system_intvector_offset(0x5000); //0x6000
    config_return_status init_ret_val;

    /* system config, xtal_init() requires interrupt, so no disabling irq here*/
    system_config();
    PWM_C1V=51000;    //pwm波初始化
	  PWM_C0V=0;
	
    /* Disable interrupt */
    Disable_Irq();

    /* peripherals config */
    /* Please configure in Startup -> BF7006BMxx_config.c -> Configuration Wizard */
    init_ret_val = peripherals_config();

    if(is_xtal_init_success == XTAL_Init_Status_Init_Failed)
    {
        /* xtal init error handling */
    }

    if(init_ret_val.overall == ERROR)
    {
        /* handle peripherals init error here */
    }
		
//		//appInit();
		rtc_config();

		//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$2024.6.27$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
		//following insert framework code(copy from boot src) 
				
		OSTK_Init();
		COMM_CAN_Init();	
		COMM_CANTP_Init();	
		DCAN_Init();

		//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
		
    /* Enable interrupt */
    Enable_Irq();
			
		//gpio_init(GPIOB,GPIO_MODE_OUT,GPIO_PIN_3);
		gpio_init(GPIOD,GPIO_MODE_IPU,GPIO_PIN_5);   //MCU_IL
		gpio_init(GPIOD,GPIO_MODE_OUT,GPIO_PIN_4);   //PWM_IL
		gpio_init(GPIOA,GPIO_MODE_OUT,GPIO_PIN_5);   //OUTRST  
    gpio_init(GPIOA,GPIO_MODE_IPU,GPIO_PIN_1); 
		gpio_init(GPIOA,GPIO_MODE_OUT,GPIO_PIN_6);	 //LED1		
    gpio_bit_reset(GPIOA,GPIO_PIN_5);            //短路保护解锁
		
		/* old marked code
		//eeprom_prog_word(0x40000000,0x55);
		//eflash_var_mark1();
		//eflash_var_mark2();
		//delay(100);
		//flash_sector_erase(95, TRUE);
		//delay(100);
		//flash_Nwords_get(FLASH_DataAddr, ftemp, flashDataLen);
		//delay(100);
		//flash_prog_Nwords(FLASH_DataAddr, flashData, flashDataLen);
		//flash_prog_word(FLASH_DataAddr,testi); 
		//eeprom_word_get(EEP_BootEnAddr,&BootState);
		//eeprom_word_get(0x40000000,&testeedata);
		//flash_word_get(0x00010000,&testeedata);
		//delay(100);
		//flash_word_get(FLASH_DataAddr,&testeedata);
		//flash_Nwords_get(FLASH_DataAddr, ftemp, flashDataLen);
		//delay(100);
		*/

}

//高压互锁判断
void HighVol_InterLocking(void)
{
		K2=GPIO_PTD(GPIOD)&0x20;
		if(K2)
		{
			K2lowtime=0;
		}
		if(K2==0)
		{
			K2hightime=0;
		}	
}

//can 接收报文处理
void CAN_ReceiveMsg(void)
{
	if(is_receive_can_frame==1) 
	{
		 is_receive_can_frame=0;
		 if(can_receive_data.sfid == ID_RXBOOT)
		 {
			 if((can_receive_data.dlen==4)&&(can_receive_data.data[0] == 0x0a)&&(can_receive_data.data[1] == 0x02)&&(can_receive_data.data[2] == 0x55))
			 {		//Boot
					//if(Cnt100 < 5)
					//Cnt100++;
					//if(Cnt100 == 3)
				 /*BOOT进入程序*/
					if((can_receive_data.data[0] +can_receive_data.data[1]+can_receive_data.data[2])==can_receive_data.data[3])
					{  
//						eflash_var_mark1();
//						eflash_var_mark2();
//						delay(100);
//						flash_sector_erase(95, TRUE);
//						delay(100);
//						flash_prog_Nwords(FLASH_DataAddr, flashData, flashDataLen);
//						delay(100);
//						NVIC_SystemReset();  
					}
			 }
		}
		 
		if(can_receive_data.sfid == ID_RX)
		{
			if(can_receive_data.dlen==8)       //??????=8
			{
					Cnt100 = 0;
					OutOfTime = 0;           //????????

					PowerSet = 35*can_receive_data.data[1];
					PWM_EN1 = can_receive_data.data[0];
				
					if((PWM_EN1&0x03)==0x02)  
						PWM_EN=1;
					if((PWM_EN1&0x03)==0x01)
						PWM_EN=0;
					
					PowerSet_limit=can_receive_data.data[2]*100;
					
					if(PowerSet >=3325)
					{
						 PowerSet = 7000;
						 //PWM_EN = 2; 
					}
					if(PowerSet>PowerSet_limit) 
						PowerSet=PowerSet_limit;
			 }
		}
	}
}

//电压计算
void Volt_Caculate(void)
{
	SetDutyFlag=0;
	led= ~led;
	if(led)
	{
			gpio_bit_reset(GPIOA,GPIO_PIN_6);
			gpio_bit_reset(GPIOD,GPIO_PIN_4);
			//gpio_bit_reset(GPIOA,GPIO_PIN_5); 
	}
	else 
	{	
			gpio_bit_set(GPIOA,GPIO_PIN_6);
			gpio_bit_set(GPIOD,GPIO_PIN_4);
			//gpio_bit_set(GPIOA,GPIO_PIN_5);
	}
	if(K2lowtime<50) 
		K2lowtime++;
	if(K2hightime<50) 
		K2hightime++;
	
	if(K2lowtime>15||K2hightime>15)
	{
		HLOCK_ERR = 0;
	}
	else
	{
		HLOCK_ERR = 1;
	}
	
	TIGBT1 = (TIGBT11+TIGBT12+TIGBT13+TIGBT14+TIGBT15)/5;  //IGBT??
	TIGBT1 = TIGBT1*5000/4096;
	if(TIGBT1<5000)
	{        
		TIGBT17 = 10000*TIGBT1/(5000 - TIGBT1);//电阻10K
		Temp_IGBT = GetIGBTTemp(TIGBT17); 
	}
	
	TPTC1 = (TPTC11+TPTC12+TPTC13+TPTC14+TPTC15)/5;   //PTC??
	TPTC1 = TPTC1*5000/4096;
	if(TPTC1<5000)
	{
			TPTC17 = 49900*TPTC1/(5000 - TPTC1);  //电阻49.9K
			Temp_PTC1 = GetPTCTemp(TPTC17); 
			//Temp_Outlet = Temp_PTC1;
	} 
	
	wdt_clear(); 

	TPTC2 = (TPTC21+TPTC22+TPTC23+TPTC24+TPTC25)/5;
	TPTC2 = TPTC2*5000/4096;
	if(TPTC2<5000)
	{
			TPTC27 = 49900*TPTC2/(5000 - TPTC2);  //电阻49.9K
			Temp_PTC2 = GetPTCTemp(TPTC27);
			//Temp_Outlet = Temp_PTC2;
	}
	
	TPCB1 = (TPCB11+TPCB12+TPCB13+TPCB14+TPCB15)/5;   //PCB
	TPCB1 = TPCB1*5000/4096;
	if(TPCB1<5000)
	{
			TPCB17 = 10000*TPCB1/(5000 - TPCB1);  //电阻10K
			Temp_PCB1 = GetIGBTTemp(TPCB17); //
	} 
	
	wdt_clear();
	
	
	Volt_High7 = (Volt_High1+Volt_High2+Volt_High3+Volt_High4+Volt_High5)/5; //高压
	//Volt_High7 = Volt_High7*5000/4096;
	Volt_High = Volt_High7*1209/4096;    //+4为修正补偿
	Volt_High22 = Volt_High*10;
	
	Volt_IGBTDriver7 = (AD_15V11+AD_15V12+AD_15V13+AD_15V14+AD_15V15)/5; //IGBT驱动电压
	//Volt_IGBTDriver7 = Volt_IGBTDriver7*5000/4096;
	Volt_IGBTDriver = Volt_IGBTDriver7*5/72;     //换算电压10倍		
}

//电流采样
void Current_Sampling(void)
{
		v=r;                                 
		Crrt11=0;
		for(w=0;w<100;w++)
		{
			if(v>0) 
				v--;
			else 
				v=119;
			
			Crrt11+=Crrt115[v];
			//if(v==0) Curr_H=Crrt115[v];
			//else
			//{
				//if(Crrt115[v]>Curr_H) Curr_H= Crrt115[v];
			//}
		}
		Crrt12=Crrt11/300;  
		Crrt1 = Crrt12*467/1100;//修正 实际10倍----2毫欧（1211修正10%）  1169
		// 2毫欧:AD*5/4096*2/43/0.002*10 = AD*3125/11008（未修正）
		// 5毫欧:AD*5/4096*2/43/0.005*10 = AD*625/5504（未修正） 
		Crrt_High = Crrt1;
		if(Duty1==0&&Crrt_High<=1)  
			Crrt_High=0;
		Crrt_High1= Crrt_High%10;
		
		if(Crrt_High1>=5)	 
			Crrt_High2=Crrt_High/10+1;
		else 
			Crrt_High2=Crrt_High/10;						
								
		Crrt11=Crrt_High*Volt_High/10;  
		Power_High=Crrt11;
		
		Power_High1=Power_High/35;
		if(Power_High1>100) 
			Power_High1=100;
		//Power_PTC=Crrt13;

		//if(Volt_High < 60)
		//		IsStartTestMyself = 0;
		//else if(IsStartTestMyself < 20)
		if(IsStartTestMyself < 20)
				IsStartTestMyself++;
		if(IsStartTestMyself == 5)  
		{ 
			gpio_bit_set(GPIOA,GPIO_PIN_5);  
		}  //短路保护启动
}

//加热
void Heating(void)
{
		if((IsStartTestMyself >= 10)&&(PWM_EN != 0)&&
			(SFault == 0)&&(Fault1 == 0)&&(Fault2 == 0)&&
			(Fault3 == 0)&&(HLOCK_ERR == 1)) 
		{
			if(Power_High > PowerTarget) 
			{ 
				 if(Power_High >= PowerTarget*3/2)
				 { 
					 if(Duty1 >= 400)
						 Duty1 -= 400;    //300
					 else if(Duty1)
						 Duty1 -= 10;
				 }
				 else if(Power_High >= PowerTarget*13/10)
				 {     
					 if(Duty1 >= 200)
						 Duty1 -= 200;   //150
					 else if(Duty1)
						 Duty1 -= 10;
				 } 
				 else if(Power_High >= PowerTarget*6/5)
				 {     
					 if(Duty1 >= 150)
						 Duty1 -= 150;   //100
					 else if(Duty1)
						 Duty1 -= 10;
				 }     
				 else if(Power_High >= PowerTarget*11/10)
				 {      
					 if(Duty1 >= 80)
						 Duty1 -= 80;    //30
					 else if(Duty1)
						 Duty1 -= 10;
				 }    
				 else if(Power_High >= PowerTarget*21/20)
				 {     
						if(Duty1 >= 40)
						 Duty1 -= 40;     //20
						else if(Duty1)
						 Duty1 -= 10;
				 } 
				 else if(Power_High >= PowerTarget*101/100)
				 {     
						if(Duty1 >= 20)
						 Duty1 -= 20;     //20
						else if(Duty1)
						 Duty1 -= 10;
				 }                							 
			}		 
			else if((Power_High < PowerTarget)&&(Duty1 < MaxPercent))
			{
				if(Power_High <= PowerTarget*3/5)    
					Duty1 += 500;//300;                      
				else if(Power_High <= PowerTarget*7/10)    
					Duty1 += 300;//130;
				else if(Power_High <= PowerTarget*4/5)    
					Duty1 += 200;//80;
				else if(Power_High <= PowerTarget*9/10)    
					Duty1 += 100;//50;
				else if(Power_High <= PowerTarget*19/20)   
					Duty1 += 50;//20; 
				else if(Power_High <= PowerTarget*49/50)   
					Duty1 += 20;//10; 
				else if(Power_High <= PowerTarget*99/100)   
					Duty1 += 10;//10; 							
			}      
		}      
		else
		{            //
			OFF = 1;  //软关断
			Duty1 =0;
		}
	 
		PowerTarget = PowerSet;

}

//电压/电流/温度转换(用于转换为故障快照信息)
void Cal_Snapshot_Value(U16 input_value, U8* pSnapshot)
{
	U8 hiByte;
	U8 loByte;
	U8 Snapshot[2];
	
	hiByte = ((input_value & 0xFF00) >> 8) * 256;
	loByte = input_value & 0xFF;
	memset(Snapshot, 0, sizeof(Snapshot));
	pSnapshot = Snapshot;
	*pSnapshot++ = hiByte;
	*pSnapshot++ = loByte;
}


//IGBT击穿及相应故障置位
void IGBT_Breakdown(void)
{
	U8* pSnapshot;
	if((Duty1 == 0)&& (Crrt_High >= 5))     
	{
		if(Cnt03 < 12)      
		 Cnt03++;
		if(Cnt03 >= 10)     
		{           
			SFault |= 0x04;  //IGBT1
			Duty1 = 0;
			
			if(_C00116++>5)
			{	
				_C00116--;
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(0, (U8*)&DTC_C00116, true);
				
				Cal_Snapshot_Value(Crrt_High, pSnapshot);
				DCAN_WriteDTC04((U8*)&DTC_C00116, pSnapshot);
				
				DCAN_WriteDTC06((U8*)&DTC_C00116, 0, DCAN_19_01_DTC_CNT, _C00116); 
			}
		}
	}  
	else
	{
		Cnt03 = 0;
	
		if(_C00116-- == 0)
		{
			DCAN_WriteDTC02(0, (U8*)&DTC_C00116, false);
		}
	}
}

//IGBT或者PTC开路故障
void IGBT_or_PTC_OpenCircult(void)
{
	U8* pSnapshot;
	if((Duty1 >= 45000) && (Crrt_High < 5))
	{
		if(Cnt02 < 30)      
		 Cnt02++;
		if(Cnt02 >= 10) 
		{   
			Cnt01=0;					
			SFault |= 0x08;
			Duty1 = 0;
			
			if(_C00216++>5)
			{
				_C00216--;
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(4, (U8*)&DTC_C00216, true);
				
				Cal_Snapshot_Value(Duty1, pSnapshot);
				DCAN_WriteDTC04((U8*)&DTC_C00216, pSnapshot);
				
				DCAN_WriteDTC06((U8*)&DTC_C00216, 4, DCAN_19_01_DTC_CNT, _C00216);
			}
		}
	}
	else
	{
		 Cnt02=0;
		
		 if(_C00216-- == 0)
		 {
			 DCAN_WriteDTC02(4, (U8*)&DTC_C00216, false);
		 }
		
	}
		
		/*
		if(PWM_EN1!=0x10)  
			SFault &= ~(0x08);
		else 
		{
			if(Cnt01 < 100)      
			 Cnt01++;
			if(Cnt01 >= 25) 
			{
				 Cnt02 = 0;
				 SFault &= ~(0x08);
			}
		} 
		*/
}

//高压过压保护
void Protect_Over_HighVol(void)
{
	U8* pSnapshot;
	if(Volt_High >= HVOver)         
	{     
		if(Cnt06 < 30)
			Cnt06++;
		if(Cnt06 >= 1)           
		{      
			Duty1 = 0;    //
			Cnt07 = 0;
			Fault1 |= 0x01;
			
			if(_911717++>5)
			{
				_911717--;
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(8, (U8*)&DTC_911717, true);
							
				Cal_Snapshot_Value(Volt_High, pSnapshot);
				DCAN_WriteDTC04((U8*)&DTC_911717, pSnapshot);
								
				DCAN_WriteDTC06((U8*)&DTC_911717, 8, DCAN_19_01_DTC_CNT, _911717); 
			}
		}
	} 
	else if(Volt_High <= HVOverRecover)    //
	{
		if(Cnt07 < 30)
			Cnt07++;
		if(Cnt07 >= 10)
		{ 
			Cnt06 = 0;
			Fault1 &= ~(0x01);			
			
			if(_911717-- == 0)
			{ 
				DCAN_WriteDTC02(8, (U8*)&DTC_911717, false);
			}
		}
	} 
}

//高压欠压保护
void Protect_Under_HighVol(void)
{
	U8* pSnapshot;
	if((Volt_High < HVUnder))       
	{     
		if(Cnt50 < 30)
			Cnt50++;
		if(Cnt50 >= 10) 
		{      
			Duty1 = 0;
			Cnt51 = 0;
			Fault1 |= 0x02;
			
			if(_911716++>5)
			{
				_911716--;
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(12, (U8*)&DTC_911716, true);
				
				Cal_Snapshot_Value(Volt_High, pSnapshot);
				DCAN_WriteDTC04((U8*)&DTC_911716, pSnapshot);
				
				DCAN_WriteDTC06((U8*)&DTC_911716, 12, DCAN_19_01_DTC_CNT, _911716);
			}
		}
	} 
	else if((Volt_High >= HVUnderRecover))    //????
	{
		if(Cnt51 < 30)
			Cnt51++;
		if(Cnt51 >= 10)
		{ 
			Cnt50 = 0;
			Fault1  &= ~(0x02);
						
			if(_911716-- == 0)
			{
			 DCAN_WriteDTC02(12, (U8*)&DTC_911716, false);
			}						
		}
	}  
}

//IGBT驱动过压
void OverVol_IGBT_Driver(void)
{
	U8* pSnapshot;	
	if(Volt_IGBTDriver >= 180)   //???
	{
		if(Cnt14 < 30)
			Cnt14++;
		if(Cnt14 >= 10)
		{
			Duty1 = 0;    //????
			Cnt15 = 0;
			Fault1 |= 0x10;
						
			if(_C20116++>5)
			{
				_C20116--;
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(16, (U8*)&DTC_C20116, true);
				
				Cal_Snapshot_Value(Volt_IGBTDriver, pSnapshot);
				DCAN_WriteDTC04((U8*)&DTC_C20116,pSnapshot);
				
				DCAN_WriteDTC06((U8*)&DTC_C20116, 16, DCAN_19_01_DTC_CNT, _C20116);
			}
		}
	}
	else if(Volt_IGBTDriver <= 160)  //???
	{
		if(Cnt15 < 30)
			Cnt15++;
		if(Cnt15 >= 10)
		{
			Cnt14 = 0;
			Fault1 &= ~(0x10); //????,????
			
			if(_C20116-- == 0)
			{
				DCAN_WriteDTC02(16, (U8*)&DTC_C20116, false);
			}
		}  
	} 
}

//IGBT驱动欠压
void UnderVol_IGBT_Driver(void)
{
	U8* pSnapshot;	
	if(Volt_IGBTDriver <= 85)   //???
	{
		if(Cnt16 < 30)
			Cnt16++;
		if(Cnt16 >= 10)
		{
			Duty1 = 0;    //????
			Cnt17 = 0;
			Fault1 |= 0x20;			

			if(_C20117++>5)
			{	
				_C20117--;
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(20, (U8*)&DTC_C20117, true);
				
				Cal_Snapshot_Value(Volt_IGBTDriver, pSnapshot);
				DCAN_WriteDTC04((U8*)&DTC_C20117, pSnapshot);
				
				DCAN_WriteDTC06((U8*)&DTC_C20117, 20, DCAN_19_01_DTC_CNT, _C20117);
			}
		}
	}
	else if(Volt_IGBTDriver >= 90)  //???
	{
		if(Cnt17 < 30)
			Cnt17++;
		if(Cnt17 >= 10)
		{
			Cnt16 = 0;
			Fault1 &= ~(0x20);  //????,????
			
			if(_C20117-- == 0)
			{
				DCAN_WriteDTC02(20, (U8*)&DTC_C20117, false);
			}
		}  
	}

}

//高压过流
void OverCurrent_HighVol(void)
{
	U8* pSnapshot;
	if(Crrt_High > Crrt_HighOver)
	{
		if(Cnt18 < 30)
			Cnt18++;
		if(Cnt18 >= 10)
		{
			Duty1 = 0;
			Cnt19 = 0;
			Fault1 |= 0x40;     

			if(_C07500++>5)
			{
				_C07500--;
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(24, (U8*)&DTC_C07500, true);
				
				Cal_Snapshot_Value(Crrt_High, pSnapshot);
				DCAN_WriteDTC04((U8*)&DTC_C07500,pSnapshot);
				
				DCAN_WriteDTC06((U8*)&DTC_C07500, 24, DCAN_19_01_DTC_CNT, _C07500); 
			}
		}  
	}  
	else 
	{
		if(Cnt19 < 100) 
			Cnt19++;
		if(Cnt19 >= 50)         //5s?????,????
		{
			Cnt18 = 0;
			Fault1 &= ~(0x40);
			
			if(_C07500-- == 0)
			{
				DCAN_WriteDTC02(24, (U8*)&DTC_C07500, false);
			}			
		}  
	}		
}

//IGBT温度传感器开路
void IGBT_TempSensor_OpenCirult(void)
{
	U8* pSnapshot;
	if(Temp_IGBT == 0)           ////IGBT温度传感器开路
	{   
		 if(Cnt08 < 30)
			 Cnt08++;
		 if(Cnt08 >= 10)
		 {
				Duty1 = 0;
				Cnt28=0;
				Fault2 |= 0x01;
				
				if(_C30116++>5)
				{
					_C30116--;
					DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
					DCAN_WriteDTC02(28, (U8*)&DTC_C30116, true);
					
					Cal_Snapshot_Value(Temp_IGBT, pSnapshot);
					DCAN_WriteDTC04((U8*)&DTC_C30116, (U8*)&pSnapshot);
					
					DCAN_WriteDTC06((U8*)&DTC_C30116, 28, DCAN_19_01_DTC_CNT, _C30116);
				}
		 }
		} 
	 else
	 {
		 if(Cnt28 < 30)
			 Cnt28++;	
		 if(Cnt28 >= 10)
		 {				 
				Cnt08 = 0;
				Fault2 &= ~(0x01);
			 
				if(_C30116-- == 0)
				{
					DCAN_WriteDTC02(28, (U8*)&DTC_C30116, false);
				}				
		 }
	 }
}

//IGBT短路
void IGBT_TempSensor_ShortCircult(void)
{
	U8* pSnapshot;
	if(Temp_IGBT == 221)          //IGBT短路
	{
	 if(Cnt09 < 30)
		 Cnt09++;
	 if(Cnt09 >= 10)
	 {
			Cnt29 = 0;
			Duty1 = 0;
			Fault2 |= 0x02;  
		 
			if(_C30216++>5)
			{
				_C30216--;
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(32, (U8*)&DTC_C30216, true);
				
				Cal_Snapshot_Value(Temp_IGBT, pSnapshot);
				DCAN_WriteDTC04((U8*)&DTC_C30216, (U8*)&pSnapshot);
				
				DCAN_WriteDTC06((U8*)&DTC_C30216, 32, DCAN_19_01_DTC_CNT, _C30216); 
			}
	 }
	}
	else
	{
	 if(Cnt29 < 30)
		 Cnt29++;
	 if(Cnt29 >= 10)
	 {
			Cnt09 = 0;        
			Fault2 &= ~(0x02);
		 
			if(_C30216-- == 0)
			{
				DCAN_WriteDTC02(32, (U8*)&DTC_C30216, false);
			}
	 }
	}
}

//PCB温度传感器开路
void PCB_TempSensor_OpenCircult(void)
{
	U8* pSnapshot;	
	if(Temp_PCB1 == 0)           ////PCB温度传感器开路
	{   
		 if(Cnt34 < 30)
			 Cnt34++;
		 if(Cnt34 >= 10)
		 {
				Duty1 = 0;
				Cnt35=0;
				Fault2 |= 0x10;
			 
				if(_C40116++>5)
				{
					_C40116--;
					DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
					DCAN_WriteDTC02(36, (U8*)&DTC_C40116, true);

					Cal_Snapshot_Value(Temp_PCB1, pSnapshot);
					DCAN_WriteDTC04((U8*)&DTC_C40116, (U8*)&pSnapshot);

					DCAN_WriteDTC06((U8*)&DTC_C40116, 36, DCAN_19_01_DTC_CNT, _C40116);  
				}
		 }
		} 
	 else
	 {
		 if(Cnt35 < 30)
			 Cnt35++;	
		 if(Cnt35 >= 10)
		 {				 
				Cnt34 = 0;
				Fault2 &= ~(0x10);
			 
				if(_C40116-- == 0)
				{
					DCAN_WriteDTC02(36, (U8*)&DTC_C40116, false);
				}				
		 }
	 }
}

//PCB温度传感器短路
void PCB_TempSensor_ShortCircult(void)
{	
	U8* pSnapshot;
	if(Temp_PCB1 == 191)
	{
	 if(Cnt36 < 30)
		 Cnt36++;
	 if(Cnt36 >= 10)
	 {
			Cnt37 = 0;
			Duty1 = 0;
			Fault2 |= 0x20;  		 

			if(_C40216++>5)
			{
				_C40216--;
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(40, (U8*)&DTC_C40216, true);
				
				Cal_Snapshot_Value(Temp_PCB1, pSnapshot);			
				DCAN_WriteDTC04((U8*)&DTC_C40216, (U8*)&pSnapshot);
				
				DCAN_WriteDTC06((U8*)&DTC_C40216, 40, DCAN_19_01_DTC_CNT, _C40216); 
			}
	 }
	}
	else
	{
	 if(Cnt37 < 30)
		 Cnt37++;
	 if(Cnt37 >= 10)
	 {
			Cnt36 = 0;        
			Fault2 &= ~(0x20);
		 
			if(_C40216-- == 0)
			{
				DCAN_WriteDTC02(40, (U8*)&DTC_C40216, false);
			}
	 }
	} 	
}

//PTC1温度传感器开路
void PTC1_TempSensor_OpenCircult(void)
{
	U8* pSnapshot;
	if(Temp_PTC1 == 0)
	{   
	//IGBT???????
		 if(Cnt10 < 30)
			 Cnt10++;
		 if(Cnt10 >= 10)
		 {
			 Cnt30 = 0;
			 Duty1 = 0;
			 Fault2 |= 0x04;
			 
			if(_C50116++>5)
			{	
				_C50116--;
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(44, (U8*)&DTC_C50116, true);

				Cal_Snapshot_Value(Temp_PTC1, pSnapshot);
				DCAN_WriteDTC04((U8*)&DTC_C50116, (U8*)&pSnapshot);
				
				DCAN_WriteDTC06((U8*)&DTC_C50116, 44, DCAN_19_01_DTC_CNT, _C50116);
			}			
		 }
	 } 
	 else
	 {
		 if(Cnt30 < 30)
			 Cnt30++;
		 if(Cnt30 >= 10)
		 {
				Cnt10 = 0;
				Fault2 &= ~(0x04);
			 
				if(_C50116-- == 0)
				{
					DCAN_WriteDTC02(44, (U8*)&DTC_C50116, false);
				}
		 }
	 }
}

//PTC1温度传感器短路
void PTC1_TempSensor_ShortCircult(void)
{
	U8* pSnapshot;
	if(Temp_PTC1 == 221)          //PTC1???????
	{
	 if(Cnt11 < 30)
		 Cnt11++;
	 if(Cnt11 >= 20)
	 {
			Cnt31 = 0;
			Duty1 = 0;
			Fault2 |= 0x08; 
		 
			if(_C50216++>5)
			{
				_C50216--;
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(48, (U8*)&DTC_C50216, true);

				Cal_Snapshot_Value(Temp_PTC1, pSnapshot);
				DCAN_WriteDTC04((U8*)&DTC_C50216, (U8*)&pSnapshot);
				
				DCAN_WriteDTC06((U8*)&DTC_C50216, 48, DCAN_19_01_DTC_CNT, _C50216);
			}
	 }					 
	}
	else
	{
	 if(Cnt31 < 30)
		 Cnt31++;
	 if(Cnt31 >= 20)
	 {				 
			Cnt11 = 0;        
			Fault2 &= ~(0x08);
		 
			if(_C50216-- == 0)
			{
				DCAN_WriteDTC02(48, (U8*)&DTC_C50216, false);
			}
	 }
	} 
}

//PTC2温度传感器开路
void PTC2_TempSensor_OpenCircult(void)
{
	U8* pSnapshot;
	if(Temp_PTC2 == 0)
	{   
	//IGBT???????
		 if(Cnt52 < 30)
			 Cnt52++;
		 if(Cnt52 >= 10)
		 {
				Cnt53 = 0;
				Duty1 = 0;
				Fault2 |= 0x40;
			 
				if(_C60116++>5)
				{	
					_C60116--;
					DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
					DCAN_WriteDTC02(52, (U8*)&DTC_C60116, true);

					Cal_Snapshot_Value(Temp_PTC2, pSnapshot);
					DCAN_WriteDTC04((U8*)&DTC_C60116, (U8*)&pSnapshot);
					
					DCAN_WriteDTC06((U8*)&DTC_C60116, 52, DCAN_19_01_DTC_CNT, _C60116);
				}
			}
		} 
	 else
	 {
		 if(Cnt53 < 30)
			 Cnt53++;
		 if(Cnt53 >= 10)
		 {
				Cnt52 = 0;
				Fault2 &= ~(0x40);
			 
				if(_C60116-- == 0)
				{
					DCAN_WriteDTC02(52, (U8*)&DTC_C60116, false);
				}				
		 }
	 }
}

//PTC2温度传感器短路
void PTC2_TempSensor_ShortCircult(void)
{
	U8* pSnapshot;
	if(Temp_PTC2 == 221)          //PTC1???????
	{
	 if(Cnt54 < 30)
		 Cnt54++;
	 if(Cnt54 >= 20)
	 {
			Cnt55 = 0;
			Duty1 = 0;
			Fault2 |= 0x80; 
		 
			if(_C60216++>5)
			{	
				_C60216--;				
				DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
				DCAN_WriteDTC02(56, (U8*)&DTC_C60216, true);
				
				Cal_Snapshot_Value(Temp_PTC2, pSnapshot);
				DCAN_WriteDTC04((U8*)&DTC_C60216, (U8*)&pSnapshot);
				
				DCAN_WriteDTC06((U8*)&DTC_C60216, 56, DCAN_19_01_DTC_CNT, _C60216); 
			}
	 }					 
	}
	else
	{
	 if(Cnt55 < 30)
		 Cnt55++;
	 if(Cnt55 >= 20)
	 {				 
			Cnt54 = 0;        
			Fault2 &= ~(0x80);
		 
			if(_C60216-- == 0)
			{
				DCAN_WriteDTC02(56, (U8*)&DTC_C60216, false);
			}			
	 }
	} 
}

//PTC1过温
void PTC1_OverTemp(void)
{
	U8* pSnapshot;
	if(Temp_PTC1>=PTCOverTemp) 
	{
		 if(Cnt22 < 30)
			 Cnt22++;
		 if(Cnt22 >= 10)
		 {
			 Duty1 = 0;
			 Cnt23=0;
			 if(Temp_PTC1!=221) 
			 { 
					Fault3 |= 0x01;

					if(_C07501++>5)
					{	
						_C07501--;
						DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
						DCAN_WriteDTC02(60, (U8*)&DTC_C07501, true);
						
						Cal_Snapshot_Value(Temp_PTC1, pSnapshot);
						DCAN_WriteDTC04((U8*)&DTC_C07501, pSnapshot);
						
						DCAN_WriteDTC06((U8*)&DTC_C07501, 60, DCAN_19_01_DTC_CNT, _C07501);
					}
			 }
		 }        
	} 
	else if(Temp_PTC1<PTCOverTempRecover) 
	{
		 if(Cnt23 < 30)
			 Cnt23++;
		 if(Cnt23 >= 10)
		 {
			 //Duty1 = 0;
			 Cnt22=0;
			 Fault3 &= ~(0x01);
			 
			if(_C07501-- == 0)
			{
				DCAN_WriteDTC02(60, (U8*)&DTC_C07501, false);
			}			
		 }      
	}
}

//PTC2过温
void PTC2_OverTemp(void)
{
	U8* pSnapshot;
	if(Temp_PTC2>=PTCOverTemp) 
	{
		 if(Cnt56 < 30)
			 Cnt56++;
		 if(Cnt56 >= 10)
		 {
			 Duty1 = 0;
			 Cnt57=0;
			 if(Temp_PTC2!=221) 
			 {
					Fault3 |= 0x08;
				 
					if(_C07502++>5)
					{
						_C07502--;
						DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
						DCAN_WriteDTC02(64, (U8*)&DTC_C07502, true);
						
						Cal_Snapshot_Value(Temp_PTC2, pSnapshot);
						DCAN_WriteDTC04((U8*)&DTC_C07502, pSnapshot);
						
						DCAN_WriteDTC06((U8*)&DTC_C07502, 64, DCAN_19_01_DTC_CNT, _C07502);
					}
			 }
		 }        
	} 
	else if(Temp_PTC2<PTCOverTempRecover) 
	{
		 if(Cnt57 < 30)
			 Cnt57++;
		 if(Cnt57 >= 10)
		 {
			 //Duty1 = 0;
			 Cnt56=0;
			 Fault3 &= ~(0x08);
			 
			if(_C07501-- == 0)
			{
				DCAN_WriteDTC02(64, (U8*)&DTC_C07502, false);
			}			
		 }      
	}	
}

//IGBT过温
void IGBTOver_Temp(void)
{
	U8* pSnapshot;
	if(Temp_IGBT>=IGBT_OverTemp) 
	{
		 if(Cnt24 < 30)
			 Cnt24++;
		 if(Cnt24 >= 10)
		 {
			 Duty1 = 0;
			 Cnt25=0;
			 if(Temp_IGBT!=221) 
			 {
					Fault3 |= 0x02;
				 
					if(_C07503++>5)
					{	
						_C07503--;
						DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
						DCAN_WriteDTC02(68, (U8*)&DTC_C07503, true);
						
						Cal_Snapshot_Value(Temp_IGBT,pSnapshot);
						DCAN_WriteDTC04((U8*)&DTC_C07503,pSnapshot);
						
						DCAN_WriteDTC06((U8*)&DTC_C07503, 68, DCAN_19_01_DTC_CNT, _C07503);
					}
			 }
		 }        
	} 
	else if(Temp_IGBT<IGBT_OverTempRecover) 
	{
		 if(Cnt25 < 30)
			 Cnt25++;
		 if(Cnt25 >= 10)
		 {
			 //Duty1 = 0;
			 Cnt24=0;
			 Fault3 &= ~(0x02);
			 
			if(_C07503-- == 0)
			{
				DCAN_WriteDTC02(68, (U8*)&DTC_C07503, false);
			}
		 }      
	} 
}

//PCB过温
void _PCB_OverTemp(void)
{
	U8* pSnapshot;
	if(Temp_PCB1>=PCB_OverTemp) 
	{
		 if(Cnt20 < 30)
			 Cnt20++;
		 if(Cnt20 >= 10)
		 {
			 Duty1 = 0;
			 Cnt21=0;
			 if(Temp_PCB1!=191)
			 {
				 Fault3 |= 0x04;
				 
				 if(_C07504++>5)
				 {
					 _C07504--;
					 DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
					 DCAN_WriteDTC02(72, (U8*)&DTC_C07504, true);
					 
					 Cal_Snapshot_Value(Temp_PCB1,pSnapshot);
					 DCAN_WriteDTC04((U8*)&DTC_C07504,pSnapshot);
					 
					 DCAN_WriteDTC06((U8*)&DTC_C07504, 72, DCAN_19_01_DTC_CNT, _C07504);
				 }
			 }
		 }        
	} 
	else if(Temp_PCB1<PCB_OverTempRecover) 
	{
		 if(Cnt21 < 30)
			 Cnt21++;
		 if(Cnt21 >= 10)
		 {
			 //Duty1 = 0;
			 Cnt20=0;
			 Fault3 &= ~(0x04);
			 
			if(_C07504-- == 0)
			{
				DCAN_WriteDTC02(72, (U8*)&DTC_C07504, false);
			}
		 }      
	}
}

//通信超时
void Comm_Overtime(void)
{
	U8* pSnapshot;
	U16 time;
	
  if(OutOfTime< 200)
		 OutOfTime++;
	if((OutOfTime >= MessageTimeout))
	{
		Fault1 |= 0x80;
			
		if(_D00300++>5)
		{
			_D00300--;
			DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
			DCAN_WriteDTC02(76, (U8*)&DTC_D00300, true);
			
			time = 0x00 | ((U8)OutOfTime);
			Cal_Snapshot_Value(time, pSnapshot);
			DCAN_WriteDTC04((U8*)&DTC_D00300, pSnapshot);
			
			DCAN_WriteDTC06((U8*)&DTC_D00300, 76, DCAN_19_01_DTC_CNT, _D00300); 
		}
	}
	else
	{
		Fault1 &= ~(0x80);
		
		if(_D00300-- == 0)
		{
			DCAN_WriteDTC02(76, (U8*)&DTC_D00300, false);
		}		
	}
}

//短路保护
void ShortCircult_Protect(void)
{
	U8* pSnapshot;
	K1=GPIO_PTD(GPIOA)&0x02;
	if((K1)&&(K1Value != MaxKValueNum))   
	{
		Duty1 = 0;
		if(RK1 < 60)
			RK1++;
		if(RK1 >= 50) //5S后解锁一次
		{          
			gpio_bit_reset(GPIOA,GPIO_PIN_5);
			IsK1 = 1;   //解锁标志
							
			if(_500216-- == 0)
			{
				DCAN_WriteDTC02(80, (U8*)&DTC_500216, false);
			}			
		}
	} 
	else
	{
		gpio_bit_set(GPIOA,GPIO_PIN_5);
		RK1 = 0; 
		if(IsK1)
		{
			IsK1 = 0;  
			K1Value++;
		}
	} 
	if(K1Value == MaxKValueNum)     //达到短路保护次数，报故障，不恢复，下电复位
	{        
		Duty1 = 0;
		SFault |= 0x10;
			
		if(_500216++>5)
		{	
			_500216--;
			DCAN_WriteDTC01(DCAN_19_01_DTC_CNT);
			DCAN_WriteDTC02(80, (U8*)&DTC_500216, true);
			
			Cal_Snapshot_Value(K1Value, pSnapshot);
			DCAN_WriteDTC04((U8*)&DTC_500216, (U8*)&pSnapshot);
			
			DCAN_WriteDTC06((U8*)&DTC_500216, 80, DCAN_19_01_DTC_CNT, _500216);
		}
	} 	
}

//故障整理输出
void Fault_Ouput(void)
{
	U8 tmpCnt = 0;
	if(Duty1==0)
	{
		WorkSts=0x00;
	}	
	else
	{
		WorkSts=0x01;
	}	

	if(SFault!=0||Fault1!=0||Fault2!=0||Fault3!=0)
	{
		WorkSts=0x02;
	}

	if((SFault&0x0c)==0) 
		WorkSts3=0x00;
	else if((SFault&0x04)) 
		WorkSts3=0x04;
	else if((SFault&0x08)) 
		WorkSts3=0x08;

	WorkSts2= (HLOCK_ERR)<<4;
	WorkSts1=WorkSts|WorkSts3|WorkSts2;
	
	//dtc count
	if(SetDutyFlag >= 69)
	{
		if(_C00116>1) _C00116 = 1;
		if(_C00216>1) _C00216 = 1;
		if(_911717>1) _911717 = 1;
		if(_911716>1) _911716 = 1;
		if(_C20116>1) _C20116 = 1;
		if(_C20117>1) _C20117 = 1;
		if(_C07500>1) _C07500 = 1;
		if(_C30116>1) _C30116 = 1;
		if(_C30216>1) _C30216 = 1;
		if(_C40116>1) _C40116 = 1;
		if(_C40216>1) _C40216 = 1;
		if(_C50116>1) _C50116 = 1;
		if(_C50216>1) _C50216 = 1;
		if(_C60116>1) _C60116 = 1;
		if(_C60216>1) _C60216 = 1;
		if(_C07501>1) _C07501 = 1;
		if(_C07502>1) _C07502 = 1;
		if(_C07503>1) _C07503 = 1;
		if(_C07504>1) _C07504 = 1;
		if(_D00300>1) _D00300 = 1;
		if(_500216>1) _500216 = 1;
		if(_C07300>1) _C07300 = 1;
		
		tmpCnt += _C00116+_C00216+_911717+_911716+_C20116+_C20117;
		tmpCnt += _C07500+_C30116+_C30216+_C40116+_C40216+_C50116;
		tmpCnt += _C50216+_C60116+_C60216+_C07501+_C07502+_C07503;
		tmpCnt += _C07504+_D00300+_500216+_C07300;			

		DCAN_19_01_DTC_CNT = tmpCnt; 
	}
	
	
	
}

//占空比输出
void DutyCycle_Output(void)
{
	PWM_C0V = Duty1;	
	if(Duty1<50000) 
		PWM_C1V = 50000-Duty1;
	else 
		PWM_C1V = 0;
	if(Duty1==0) 
		PWM_C1V=51000;
	
	//PWM_C2V = Duty3;				
	//PWM_C3V = Duty4;
}


//app任務(10ms)
void App_Core_1(void)
{
		/* Place your code here */
		#ifdef BF7x06BMxx_WDT_DRIVER_PRESENT
				wdt_clear();        // clear watchdog
		#endif
		
		/************************************************************
		*********************----高压互锁判断-----*********************
		*************************************************************/
		HighVol_InterLocking();
			
		/************************************************************/
		//CAN接收报文
		CAN_ReceiveMsg();
		/************************************************************/		
				
}

//app任务(100ms)
void App_Core_2(void)
{
			//if(SetDutyFlag >= 99)    //每隔100ms做一次
			{
				/***********************************************************/
				//电压计算
				/***********************************************************/
				Volt_Caculate();				
		
				/***********************************************************/
				////////////电流采样
				/***********************************************************/
				Current_Sampling();  					

				/***********************************************************
				**************************---加热---************************
				************************************************************/ 
				Heating();
				
				/*************************************************************
				**************---IGBT击穿及相应故障置位---********************
				*************************************************************/
				IGBT_Breakdown();
			
				/*************************************************************
				*******************----IGBT或者PTC开路故障---*****************
				*************************************************************/ 
				IGBT_or_PTC_OpenCircult();
					
				/**************************************************************
				******************---高压过压保护---***********************  
				*************************************************************/ 
        Protect_Over_HighVol();				
				
				/**************************************************************
				******************---高压欠压保护---***********************  
				*************************************************************/ 
        Protect_Under_HighVol();
      
			 /************************************************************
				***************---IGBTQUDONG过压---****************
				************************************************************/ 
				OverVol_IGBT_Driver();
      
				/************************************************************
				***************---IGBTQUDONG欠压---****************
				************************************************************/ 
				UnderVol_IGBT_Driver();
			
				/************************************************************
				**********************---高压过流---*************************
				************************************************************/
				OverCurrent_HighVol();
			
				/*************************************************************
				*******************----IGBT温度传感器---******************
				************************************************************/
				IGBT_TempSensor_OpenCirult();//IGBT开路
				IGBT_TempSensor_ShortCircult();//IGBT短路
               
				/*************************************************************
				*******************----PCB温度传感器---******************
				************************************************************/
				PCB_TempSensor_OpenCircult();		//PCB温度传感器开路
				PCB_TempSensor_ShortCircult();	//PCB温度传感器短路
        
				/*************************************************************
				*******************----PTC1温度传感器----******************
				************************************************************/       
				PTC1_TempSensor_OpenCircult();
        PTC1_TempSensor_ShortCircult();     
 
				/*************************************************************
				*******************----PTC2温度传感器----******************
				************************************************************/       
      /*
				PTC2_TempSensor_OpenCircult();
				PTC2_TempSensor_ShortCircult();
      */
			 
				/************************************************************
				*********************----PTC1过温-----*********************
				*************************************************************/ 			 
				PTC1_OverTemp();

				/************************************************************
				*********************----PTC2过温-----*********************
				*************************************************************/ 			 
      /*
				PTC2_OverTemp();
			*/
				 /************************************************************
				*********************----IGBT过温-----*********************
				*************************************************************/       
				IGBTOver_Temp();
   	
				 /************************************************************
				*********************----PCB过温-----*********************
				*************************************************************/       
      	_PCB_OverTemp();
			    
				/************************************************************
				*********************----通讯超时-----*********************
				*************************************************************/
				Comm_Overtime();
              
				/************************************************************
				*********************----短路保护-----*********************
				*************************************************************/
				ShortCircult_Protect();
							
				/************************************************************
				*********************----故障整理输出 -----*******************
				*************************************************************/  
				Fault_Ouput();
			  			
				/************************************************************
				*********************----占空比输出 -----*******************
				*************************************************************/
				DutyCycle_Output();			
		 } 

}

int main(void)
{
		//系统初始化
		sys_init();

    while(1)
    {
       OSTK_TaskHandler();	  
    }

    /* Should never reach here */
    return 0;
}

void delay(uint16_t time)
{
    uint8_t i;
    while(time--)
    {
        for(i = 0; i < 100;i++);
    }
}

//--------------------------END OF FILE-----------------------------------
