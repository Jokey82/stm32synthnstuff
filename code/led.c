#include "led.h"


uint16_t leds[] = {LED_1, LED_2, LED_3, LED_4};

void init_led(void){
	GPIO_InitTypeDef GPIO_Led_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	for(int i=0;i<LED_NUM;i++){
		GPIO_Led_init.GPIO_Pin = leds[i];
		GPIO_Led_init.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Led_init.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_Led_init);
	}
	
	
}

void led_on(uint16_t led){
	GPIO_SetBits(GPIOC, led);
}

void led_off(uint16_t led){
	GPIO_ResetBits(GPIOC, led);
}

void led_test(void){
	init_led();
	led_on(LED_1);
	led_on(LED_2);
	led_on(LED_3);
	led_on(LED_4);
}

void led_excl_on(uint16_t led){
	for(int i =0;i < LED_NUM;i++){
		if(leds[i] != led){
			led_off(leds[i]);
		}
		else{
			led_on(leds[i]);
		}	
	}
}

void run_demo(void){
	static int pos =0;
	static int dir =0;
	if(dir == 0){
		if(pos < LED_NUM){
			led_excl_on(leds[pos++]);
		}
		else{
			pos -=2;
			led_excl_on(leds[pos--]);
			dir++;
		}
	}
	else{
		if(pos > 0){
			led_excl_on(leds[pos--]);
		}
		else{
			dir--;
			led_excl_on(leds[pos++]);
		}
	}
}