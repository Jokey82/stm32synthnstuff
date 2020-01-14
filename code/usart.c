#include "usart.h"

volatile char RXs[RX_BUF_SIZE];
volatile char RXc;
volatile uint8_t RXi =0; 
volatile uint8_t RX_FLAG_END_LINE = 0;

void send_to_uart(uint8_t data)  {
 while(!(USART1->SR & USART_SR_TC));
 USART1->DR=data;
}

void clear_RXBuffer(void) {
    for (RXi=0; RXi<RX_BUF_SIZE; RXi++)
        RXs[RXi] = '\0';
    RXi = 0;
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
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	 NVIC_InitTypeDef NVIC_InitStructure;
    /* Enable the USARTx Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
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
		
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

uint8_t usart_main_loop_routine(void){
	if (RX_FLAG_END_LINE == 1) {
						uint8_t command = 0;
            RX_FLAG_END_LINE = 0;
		
            send_str("Received a line:");
            send_str(RXs);
						
						
            if (strncmp(RXs, "ON1\r", 4) == 0) {
								command = LED1_ON;
            }
						if (strncmp(RXs, "ON2\r", 4) == 0) {
								command = LED2_ON;
            }
						if (strncmp(RXs, "ON3\r", 4) == 0) {
								command = LED3_ON;
            }
						if (strncmp(RXs, "ON4\r", 4) == 0) {
								command = LED4_ON;
            }
            clear_RXBuffer();
						return command;
        }
	return 0;
}

void USART1_IRQHandler(void){
	if((USART1->SR & USART_FLAG_RXNE) != (u16)RESET){
		RXc = USART_ReceiveData(USART1);
		RXs[RXi] = RXc;
		RXi++;
		//send_to_uart(RXc);
		if(RXc != 13){
			if(RXi >= RX_BUF_SIZE){
				clear_RXBuffer();
			}
		}
		else {
                RX_FLAG_END_LINE = 1;
            }
		
		
	}
}
