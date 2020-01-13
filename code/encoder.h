#include "main.h"
#include<stdint.h>

#define Read_Enc_A GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)
#define Read_Enc_B GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)

#define ENC_MAX 100
#define FORWARD     0
#define BACKWARD    1
 
#define NOREADY     0
#define READY       1
#define INIT        3

uint8_t get_enc_count(void);
void encoder_init(void);
