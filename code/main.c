#include "main.h"
#include "led.h"
#include "encoder.h"
#include "timers.h"
#include "saw_osc.h"
#include "usart.h"
#include "common.h"

int main(void)
{
	//init_osc();
	encoder_init();
	init_uart();
	init_apb1_timer(RCC_APB1Periph_TIM3, TIM3, 40000, 100);
	enable_irq(TIM3, TIM3_IRQn);
		
	
	
	while(1){
		
		
		
	}
}

void TIM3_IRQHandler(void){
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
				{
					TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
					static char buffer[64];
					//char position_str[8];
					//itoa(get_enc_count(), position_str);
					
					int pos = get_enc_count();
					
					snprintf(buffer, 64, "Encoder position: %d", pos);
					send_str(buffer);
		//set_freq(MAX_FRQ / get_enc_count());
		

	}
}

