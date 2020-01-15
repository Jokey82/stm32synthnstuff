#include "main.h"
#include "string.h"
#include "common.h"

/*COMMANDS*/
/*LED COMMANDS*/
#define LED1_ON 1
#define LED2_ON 2
#define LED3_ON 3
#define LED4_ON 4
#define LED_RESET 5
#define DEMO 7
#define STOP 8
/*OSC COMMANDS*/

/*ERROR CODES*/
#define INVAL 21


uint8_t led_command_check(char* RXs);
uint16_t osc_command_check(char* RXs);