#include "main.h"

#define LED_1 GPIO_Pin_4
#define LED_2 GPIO_Pin_5
#define LED_3 GPIO_Pin_6
#define LED_4 GPIO_Pin_7

#define LED_NUM 4

void led_test(void);
void led_on(uint16_t led);
void led_off(uint16_t led);
void init_led(void);
void led_excl_on(uint16_t led);
void run_demo(void);