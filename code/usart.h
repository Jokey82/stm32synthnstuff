#include "main.h"
#include "stm32f10x_usart.h"

void send_to_uart(uint8_t data);
void send_str(char * string);
void init_uart(void);