#include "timers.h" 

void init_apb1_timer(uint32_t APB1_timer, TIM_TypeDef * timer,  uint16_t prescaler, uint16_t period){
	RCC_APB1PeriphClockCmd(APB1_timer, ENABLE); 

	TIM_TimeBaseInitTypeDef timerInitStructure; 
	timerInitStructure.TIM_Prescaler = prescaler;
	timerInitStructure.TIM_Period = period;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(timer, &timerInitStructure);

	TIM_Cmd(timer, ENABLE);
}

void init_enc_timer(uint16_t prescaler, uint16_t period){
	TIM_TimeBaseInitTypeDef timerInitStructure; 
	timerInitStructure.TIM_Prescaler = prescaler;
	timerInitStructure.TIM_Period = period;
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI1,
  TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2, ENABLE);
}

void enable_irq(TIM_TypeDef * timer, uint8_t IRQN_Channel){
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = IRQN_Channel;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 1;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);	
}
