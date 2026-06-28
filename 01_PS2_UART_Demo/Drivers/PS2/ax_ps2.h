/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AX_PS2_H
#define __AX_PS2_H

/* Includes ------------------------------------------------------------------*/	 
#include "stm32f4xx_hal.h"
//PS2手柄键值结构体
typedef struct			 				
{
  uint8_t mode;		    /* 手柄工作模式 */

  uint8_t btn1;         /* B0:SLCT B3:STRT B4:UP B5:R B6:DOWN B7:L   */

  uint8_t btn2;         /* B0:L2 B1:R2 B2:L1 B3:R1 B4:△ B5:○ B6:✕ B7:□  */

  uint8_t RJoy_LR;      /* 右摇杆  0x00 = 左    0xff = 右   */

  uint8_t RJoy_UD;      /* 右摇杆  0x00 = 上    0xff = 下   */

  uint8_t LJoy_LR;      /* 左摇杆  0x00 = 左    0xff = 右   */

  uint8_t LJoy_UD;      /* 左摇杆  0x00 = 上    0xff = 下   */
	
}JOYSTICK_TypeDef;


void AX_PS2_Init(void);  //PS2初始化
void AX_PS2_ScanKey(JOYSTICK_TypeDef* JoystickStruct);//PS2获取按键及摇杆数值

#endif 

