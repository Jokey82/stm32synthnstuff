
#include "saw_osc.h"

uint16_t wave_buf[BUF_LEN];
int i=0;
void gen_saw(uint16_t *buffer, int len);
int frq = MAX_FRQ;


void init_osc(void){
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
  
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	gen_saw(wave_buf, BUF_LEN);
	
  TIM6->PSC = 0;
  TIM6->ARR = frq;
  TIM6->DIER |= TIM_DIER_UIE;
  TIM6->CR1 |= TIM_CR1_CEN;
  NVIC_EnableIRQ(TIM6_DAC_IRQn);
  TIM7->PSC = 0;
  TIM7->ARR = frq+1000;
  TIM7->DIER |= TIM_DIER_UIE;
  TIM7->CR1 |= TIM_CR1_CEN;
  NVIC_EnableIRQ(TIM7_IRQn);
	
  DAC->CR |= DAC_CR_EN1;
	DAC->CR |= DAC_CR_EN2;
}

void gen_saw(uint16_t *buffer, int len){
	for (int i =0;i<len;i++){
		buffer[i]	= MAX_AMP / i;
	}
}


void TIM6_DAC_IRQHandler(void) {
  TIM6->SR &= ~TIM_SR_UIF; 
  DAC->DHR12R1=wave_buf[i++];
  if (i==BUF_LEN) i=0;
	
}
void TIM7_IRQHandler(void) {
  TIM7->SR &= ~TIM_SR_UIF; 
  DAC->DHR12R2=wave_buf[i++];
  if (i==BUF_LEN) i=0;
}

void set_freq(uint16_t freq){
	if(freq != frq){
		TIM6->ARR = freq;
		TIM7->ARR = freq+1000;
	}
}
