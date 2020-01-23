#include "dma.h"


void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Perif, uint32_t Mem, uint16_t Size, uint16_t Conf)
{
uint32_t tmp = 0;
 
    tmp = Channel->CCR;		
    tmp &= CCR_CLEAR_Mask;	
    tmp |= Conf;			
 
    Channel->CNDTR = Size;	
    Channel->CPAR = Perif;	
    Channel->CMAR = Mem;		
    Channel->CCR = tmp;	
}

void DMA_Enable(DMA_Channel_TypeDef* Channel)
{
    Channel->CCR |= DMA_CCR1_EN;
}
 
void DMA_Disable(DMA_Channel_TypeDef* Channel)
{
    Channel->CCR &= (uint16_t)(~DMA_CCR1_EN);
}

void DMA_DeInit(DMA_Channel_TypeDef* Channel)
{
    Channel->CCR &= (uint16_t)(~DMA_CCR1_EN);
    Channel->CCR = 0;
    Channel->CNDTR = 0;
    Channel->CPAR = 0;
    Channel->CMAR = 0;
 
 
    if (Channel == DMA1_Channel1)
      {
        /* Reset interrupt pending bits for DMA1 Channel1 */
        DMA1->IFCR |= DMA1_Channel1_IT_Mask;
      }
      else if (Channel == DMA1_Channel2)
      {
        /* Reset interrupt pending bits for DMA1 Channel2 */
        DMA1->IFCR |= DMA1_Channel2_IT_Mask;
      }
      else if (Channel == DMA1_Channel3)
      {
        /* Reset interrupt pending bits for DMA1 Channel3 */
        DMA1->IFCR |= DMA1_Channel3_IT_Mask;
      }
      else if (Channel == DMA1_Channel4)
      {
        /* Reset interrupt pending bits for DMA1 Channel4 */
        DMA1->IFCR |= DMA1_Channel4_IT_Mask;
      }
      else if (Channel == DMA1_Channel5)
      {
        /* Reset interrupt pending bits for DMA1 Channel5 */
        DMA1->IFCR |= DMA1_Channel5_IT_Mask;
      }
      else if (Channel == DMA1_Channel6)
      {
        /* Reset interrupt pending bits for DMA1 Channel6 */
        DMA1->IFCR |= DMA1_Channel6_IT_Mask;
      }
      else if (Channel == DMA1_Channel7)
      {
        /* Reset interrupt pending bits for DMA1 Channel7 */
        DMA1->IFCR |= DMA1_Channel7_IT_Mask;
      }
      else if (Channel == DMA2_Channel1)
      {
        /* Reset interrupt pending bits for DMA2 Channel1 */
        DMA2->IFCR |= DMA2_Channel1_IT_Mask;
      }
      else if (Channel == DMA2_Channel2)
      {
        /* Reset interrupt pending bits for DMA2 Channel2 */
        DMA2->IFCR |= DMA2_Channel2_IT_Mask;
      }
      else if (Channel == DMA2_Channel3)
      {
        /* Reset interrupt pending bits for DMA2 Channel3 */
        DMA2->IFCR |= DMA2_Channel3_IT_Mask;
      }
      else if (Channel == DMA2_Channel4)
      {
        /* Reset interrupt pending bits for DMA2 Channel4 */
        DMA2->IFCR |= DMA2_Channel4_IT_Mask;
      }
      else
      {
        if (Channel == DMA2_Channel5)
        {
          /* Reset interrupt pending bits for DMA2 Channel5 */
          DMA2->IFCR |= DMA2_Channel5_IT_Mask;
        }
      }
}