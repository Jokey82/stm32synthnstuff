#include "main.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include "common.h"
#include "commands.h"

#define RX_BUF_SIZE 80


void send_to_uart(uint8_t data);
void send_str(char * string);
void init_uart(void);
uint16_t usart_main_loop_routine(void);

	