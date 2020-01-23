#include "main.h"
#include "led.h"
#include "encoder.h"
#include "timers.h"
#include "saw_osc.h"
#include "usart.h"
#include "common.h"
#include "commands.h"
#include "dma.h"

int main(void){
	/*INIT CONFIGURATION*/
	
	init_osc();
	encoder_init();
	
	init_led();
	init_uart();
	
	//init_apb1_timer(RCC_APB1Periph_TIM3, TIM3, 24000, 1000);
	//enable_irq(TIM3, TIM3_IRQn);
	
	/*VARIABLE INITIALISATION*/	
	
	uint16_t command;
	char aux_buffer[32];
	
	while(1){
		
		command = usart_main_loop_routine();
		switch (command){
			case 0:
				break;
			case LED1_ON:
				led_excl_on(LED_1);
				break;
			case LED2_ON:
				led_excl_on(LED_2);
				break;
			case LED3_ON:
				led_excl_on(LED_3);
				break;
			case LED4_ON:
				led_excl_on(LED_4);
				break;
			case DEMO:
				init_apb1_timer(RCC_APB1Periph_TIM4, TIM4, 24000, 100);
				enable_irq(TIM4, TIM4_IRQn);
				break;
			case STOP:
				TIM_Cmd(TIM4, DISABLE);
				break;
			case INVAL:
				send_str("Invalid frequency value");
				break;
			default:
				
				set_freq(command);
			snprintf(aux_buffer, 32, "Freq. set to %d", command);
			send_str(aux_buffer);
		}
		
	}
}

void TIM3_IRQHandler(void){
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
				{
					TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
					//static char buffer[64];
					//char position_str[8];
					//itoa(get_enc_count(), position_str);
					
					//int pos = get_enc_count();
					
					//snprintf(buffer, 64, "Encoder position: %d", pos);
					//send_str("TEST");
		set_freq(MAX_FRQ / get_enc_count());
		

	}
}

void TIM4_IRQHandler(void){
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
				{
					TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
					run_demo();
	}
}


