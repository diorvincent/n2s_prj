#include "can_init.h"
#include "BF7006BMxx_can.h"
#include "BF7006BMxx_sysctrl.h"

/*!
    \brief      CAN初始化
	\param[in]	none
    \param[out] none
    \retval     none
*/
void canInit(void)
{
	//CAN初始化参数
	can_parameter_struct can_parameter_init = 
	{
		.working_mode		= CAN_NOMARL,					//正常模式
		.resync_jump_width	= CAN_BTR0_SJW_SET(0),			//同步跳转位宽
     //   #warning 注意晶振和波特率配置
		.can_clk			= CAN_CLK_16M,	                //使用16Mhz时钟，需和can_clock_sel()对应
		.can_baud			= CAN_BAUD_500K,	            //波特率500K			
		.sampling_times		= CAN_BTR1_SAM_SET(1),			//采样时间
		.error_alarm_count	= 100,							//错误报警限值
		.int_enable			= CAN_WUIE_ENABLE | CAN_ERR_ALL_ENABLE | CAN_RIE_ENABLE | CAN_TIE_ENABLE,	//使能中断
		.nvic_int_enable	= CAN_WU_NVIC_ENABLE | CAN_ERR_NVIC_ENABLE | CAN_RX_NVIC_ENABLE | CAN_TX_NVIC_DISABLE	//nvic中断使能
	};
	//滤波参数
	can_filter_parameter_struct can_filter_parameter = 
	{
		.filter_mode			= CAN_DOUBLE_FILTER,	//double mode
		.filter_frame			= CAN_EXTENDED_FRAME,	//standard frame
		.filter_RTR				= CAN_DATA_FRAME,		//data frame
		.filter_mask_RTR		= ENABLE,				//RTR bit mask enable
		/* single filter cofing */
		.filter_single_id		= 0x12345678U,			//single filter id,filter standard frame:11bits valid;filter extend frame:29bits valid
		.filter_data0			= 0xff,					//data0 filter,used in filter standard frame
		.filter_data1			= 0xff,					//data1 filter,used in filter standard frame
		.filter_mask_single_id	= 0xffff,				//single filter mask id,filter standard frame:11bits valid;filter extend frame:29bits valid
		.filter_mask_data0		= 0xff,					//data0 filter mask,used in filter standard frame
		.filter_mask_data1		= 0xff,					//data1 filter mask,used in filter standard frame
		/* double filter config */
		.filter_double_id0		= 0x12345678U,			//double filter id0,filter standard frame:11bits valid;filter extend frame:29bits ID  valid and filter ID28~13
		.filter_double_id1		= 0x98765432U,			//double filter id1,filter standard frame:11bits valid;filter extend frame:29bits ID  valid and filter ID28~13
		.filter_data0_std		= 0xff,					//data0 filter,used in filter standard frame
		.filter_mask_double_id0	= 0xffff,				//double filter id0 mask,filter standard frame:11bits valid;filter extend frame:16bits valid
		.filter_mask_double_id1	= 0xffff,				//double filter id1 mask,filter standard frame:11bits valid;filter extend frame:16bits valid
		.filter_mask_data0_std	= 0xff					//data0 filter mask,used in filter standard frame
	};
	
	can_clock_sel(CAN_XTAL_CLOCK);      //使用外部时钟，需和can_clk对应
	can_module_rst();                   //模块复位
	(void)can_init(can_parameter_init,can_filter_parameter);    //初始化
}
