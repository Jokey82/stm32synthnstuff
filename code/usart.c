#include "usart.h"

void send_to_uart(uint8_t data)  {
 while(!(USART1->SR & USART_SR_TC));
 USART1->DR=data;
}

void send_str(char * string) {
 uint8_t i=0;
 while(string[i]) {
  send_to_uart(string[i]);
  i++;
 }
 send_to_uart('\r');
 send_to_uart('\n');
}

void init_uart(void){
	uint8_t uart_data;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | 
	 RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | 
	 RCC_APB2Periph_GPIOB  , ENABLE);
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	 GPIO_InitTypeDef uartInitStruct;
	 uartInitStruct.GPIO_Pin   = GPIO_Pin_10;
	 uartInitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOA, &uartInitStruct);
	
		uartInitStruct.GPIO_Pin   = GPIO_Pin_9;
    uartInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    uartInitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &uartInitStruct);
	
		USART_InitTypeDef uart_struct;
    uart_struct.USART_BaudRate            = 9600;
    uart_struct.USART_WordLength          = USART_WordLength_8b;
    uart_struct.USART_StopBits            = USART_StopBits_1;
    uart_struct.USART_Parity              = USART_Parity_No ;
    uart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart_struct.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
		
		USART_Init(USART1, &uart_struct);
		
		USART_Cmd(USART1, ENABLE);
}