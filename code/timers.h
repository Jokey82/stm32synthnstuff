#include "main.h"
#include "stm32f10x_tim.h"

void enable_irq(TIM_TypeDef * timer, uint8_t IRQN_Channel);
void init_apb1_timer(uint32_t APB1_timer, TIM_TypeDef * timer, uint16_t prescaler, uint16_t period);
void init_enc_timer(uint16_t prescaler, uint16_t period);
