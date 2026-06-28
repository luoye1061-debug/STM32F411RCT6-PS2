#include "ax_delay.h"



/**
  * @简  述  延时函数初始化
  * @参  数  无
  * @返回值  无
  */
void AX_DELAY_Init(void) 
{	 
HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}

/**
  * @简  述  软件微秒延时函数
  * @参  数  us：延时长度，单位us
  * @返回值  无
  */
void AX_Delayus(uint32_t us)
{
	uint32_t temp;
	//100MHz主频下，1us对应100个脉冲
	SysTick->LOAD = 100 * us; 				 		 
  SysTick->VAL = 0x00;        				
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  	 
  do
  {
		temp = SysTick->CTRL;
  }
  while((temp & 0x01) && !(temp & (1 << 16)));	 
    
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; 
  SysTick->VAL = 0X00;
}

/**
  * @简  述  软件毫秒级延时函数
  * @参  数  ms：延时长度，单位ms
  * @返回值  无
  */
static void Delay_ms(uint16_t ms)
{	 		  	  
	uint32_t temp;	
	
	SysTick->LOAD = (uint32_t)100000 * ms;			
  SysTick->VAL = 0x00;           		
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; 
  do
  {
      temp = SysTick->CTRL;
  }while((temp & 0x01) && !(temp & (1 << 16)));	
    
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;      
  SysTick->VAL = 0X00;
}


/**
  * @简  述  软件ms延时
  * @参  数  ms：延时函数，单位ms
  * @返回值  无
  */
void AX_Delayms(uint16_t ms)
{
	uint8_t repeat = ms / 100;																
  uint16_t remain = ms % 100;

  while(repeat)
  {
      Delay_ms(100);
      repeat--;
  }
    
  if(remain)
  {
      Delay_ms(remain);
  }
}


