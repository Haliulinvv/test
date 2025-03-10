#include "main.h"

static int count = 0;

// ���������� ���������� TIM1
void TIM1_UP_TIM10_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) {  // �������� ����� ����������
        TIM1->SR &= ~TIM_SR_UIF;  // �������� ����
		}
		if  (count == 10){
		count = 1 ;
		TIM1->RCR = 50-1;
		GPIOA->ODR |= GPIO_ODR_ODR_8;	
		} else{ 
		TIM1->RCR = 1;
		count++;
			        // ������������ ��������� ����������
		GPIOA->ODR ^= GPIO_ODR_ODR_8;  // ������������� ��������� PA8		
		}       	
}
