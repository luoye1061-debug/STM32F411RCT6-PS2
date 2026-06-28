#include "ax_uart1.h"
#include <stdio.h>
/**************************串口打印相关函数重定义********************************/
/**
  * @简  述  重定义fputc函数（USART1）	
  */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
/**
  * @简  述  重定义fgetc函数（USART1）	
  */
int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&huart1, &ch, 1, 0xFFFF);
    return (int)ch;
}
