/**			                                                    
  * @说明
  *
  *   PS2数据定义
  *   BYTE   DATA   解释
  *   01     idle
  *   02     0x73   手柄工作模式
  *   03     0x5A   Bit0  Bit1  Bit2  Bit3  Bit4  Bit5  Bit6  Bit7
  *   04     data   SLCT  JOYR  JOYL  STRT   UP   RIGHT DOWN  LEFT  btn1
  *   05     data   L2     R2     L1    R1   △    O     X     □     btn2
  *   06     data   右摇杆  0x00 = 左    0xff = 右
  *   07     data   右摇杆  0x00 = 上    0xff = 下
  *   08     data   左摇杆  0x00 = 左    0xff = 右
  *   09     data   左摇杆  0x00 = 上    0xff = 下
  */

#include "ax_ps2.h"
#include "ax_delay.h"
#include "main.h"

#define DI()      HAL_GPIO_ReadPin(DI_GPIO_Port, DI_Pin)      // 数据输入

#define DO_H()   HAL_GPIO_WritePin(DO_GPIO_Port, DO_Pin, GPIO_PIN_SET)   // 命令位高
#define DO_L()   HAL_GPIO_WritePin(DO_GPIO_Port, DO_Pin, GPIO_PIN_RESET) // 命令位低

#define CS_H()    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)     // CS拉高
#define CS_L()    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)   // CS拉低

#define CLK_H()   HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET)    // 时钟拉高
#define CLK_L()   HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET)  // 时钟拉低


const  uint8_t PS2_cmnd[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   //请求获取数据命令
static uint8_t PS2_data[9] = {0};  //接受的数据


/**
  * @简  述  PS2初始化
  */
void AX_PS2_Init(void)
{
	CS_H();
  CLK_H();
	DO_H();
}


/**
  * @简  述  PS2数据读写函数
  * @参  数  data：要写入的数据
  * @返回值  读出数据
  */
static uint8_t PS2_ReadWriteData(uint8_t data)
{
	uint8_t ref, res = 0x00;	
	
	for(ref = 0x01; ref > 0x00; ref <<= 1)
	{
		CLK_L();
		if(ref&data)
			DO_H();
		else
			DO_L();	
		
		AX_Delayus(16);
		
		DO_H();
		if(DI())
			res |= ref; 
		
		AX_Delayus(16);		
	}
	
	DO_H();

	//返回读出数据
    return res;	
}

/**
  * @简  述  PS2获取按键及摇杆数值
  * @参  数  *JoystickStruct 手柄键值结构体
  * @返回值  无
  */
void AX_PS2_ScanKey(JOYSTICK_TypeDef *JoystickStruct)
{
	uint8_t i;
	
  //使能手柄	
	CS_L();
	
	//读取PS2数据
	for(i=0; i<9; i++)
	{
		PS2_data[i] = PS2_ReadWriteData(PS2_cmnd[i]);
		AX_Delayus(16);
	}
	
	//关闭使能
	CS_H();

	//数值传递
	JoystickStruct->mode = PS2_data[1];
	JoystickStruct->btn1 = ~PS2_data[3];
	JoystickStruct->btn2 = ~PS2_data[4];
	JoystickStruct->RJoy_LR = PS2_data[5];
	JoystickStruct->RJoy_UD = PS2_data[6];
	JoystickStruct->LJoy_LR = PS2_data[7];
	JoystickStruct->LJoy_UD = PS2_data[8];
}
