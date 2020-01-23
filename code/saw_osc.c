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
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	  RCC->AHBENR |= RCC_AHBENR_DMA1EN;   
  
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	gen_saw(wave_buf, BUF_LEN);
	
  TIM6->PSC = 0;
  TIM6->ARR = 4000;
  TIM6->DIER |= TIM_DIER_UIE;
	TIM6->DIER |= TIM_DIER_UDE;
	TIM6->CR2 |= TIM_CR2_MMS_1;
  TIM6->CR1 |= TIM_CR1_CEN;
  
	DMA_DeInit(DMA1_Channel3);
	DMA_Init(DMA1_Channel3, (uint32_t)&DAC->DHR12R1, (uint32_t)&wave_buf, BUF_LEN, 
		TransCompl_Int_Disable | 
		TransError_Int_Disable | 
		HalfCompl_Int_Disable  |
		ReadMemory | 
		CircularMode_Enable |
		PeripheralInc_Disable | 
		MemoryInc_Enable | 
		PDataSize_DW | 
		MDataSize_DW | 
		ReadMemory | 
		DMA_Priority_Low | 
		M2M_Disable);
	DMA_Enable(DMA1_Channel3);
	
  DAC->CR |= DAC_CR_EN1;
}

void gen_saw(uint16_t *buffer, int len){
	for (int i =0;i<len;i++){
		buffer[i]	= (MAX_AMP - i*5)+100;
		
	}
}

void set_freq(uint16_t frq){
	TIM6->ARR = frq;
}