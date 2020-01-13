#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "oscillators.h"

void gen_sine(int *buffer, uint16_t buffer_len);
void gen_square(int *buffer, uint16_t buffer_len);

const uint16_t ref_sin[32] = {
 2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
 3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909,
 599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647};

int sin_buf[BUFFER_SIZE];
int sqr_buf[BUFFER_SIZE];



int main(void) { 
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
  
  
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  gen_sine(sin_buf, BUFFER_SIZE);
	gen_square(sqr_buf, BUFFER_SIZE);
	GPIO_SetBits(GPIOC, GPIO_Pin_9);
	
  TIM6->PSC = 0;
  TIM6->ARR = 100;
  TIM6->DIER |= TIM_DIER_UIE; 
  TIM6->CR1 |= TIM_CR1_CEN; 
  NVIC_EnableIRQ(TIM6_DAC_IRQn);
  
  
  DAC->CR |= DAC_CR_EN1;
  
   
  while (1)
  {
  }
}
  
void gen_sine(int *buffer, uint16_t buffer_len){
					for (int sample = 0; sample < buffer_len; sample++) {
					float value = sin(sample*((2*PI)/BUFFER_SIZE))+1;
						buffer[sample] = (int)(value*(4000/2));
          } 
}

void gen_square(int *buffer, uint16_t buffer_len){
	for(int i =0;i < buffer_len; i++){
		int value = i<buffer_len/2?0:1;
		buffer[i] = value*2000+2000 ;
	}
}


void TIM6_DAC_IRQHandler(void) {
  TIM6->SR &= ~TIM_SR_UIF;
	static int i =0;
	static  int rep = 0;
	if(MODE == 0){
		DAC->DHR12R1=ref_sin[i];
		if(rep >= REPN){
			if (i==32) i=0;
			else i++;
			rep = 0;
		}
		rep++;
	}
	if(MODE == 1){
		DAC->DHR12R1=sin_buf[i];
		if(rep >= REPN){
			if (i==BUFFER_SIZE) i=0;
			else i++;
			rep = 0;
		}
		rep+= INC;
	}
	if(MODE == 2){
		DAC->DHR12R1=sqr_buf[i];
		if(rep >= REPN){
			if (i==BUFFER_SIZE) i=0;
			else i++;
			rep = 0;
		}
		rep+= INC;
	}
   
}

