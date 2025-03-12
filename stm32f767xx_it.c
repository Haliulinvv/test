#include "stm32f767xx_it.h"
#include "stddef.h"

static uint16_t freq_values[10][2] = {{4,100},{6,50},{8,200}};
//static const uint16_t freq_values_size = sizeof(freq_values) / sizeof(freq_values[0]);
static uint16_t *p = NULL;

static uint32_t count = 0;


// ���������� ���������� TIM1
void TIM1_UP_TIM10_IRQHandler(void) {
  if (TIM1->SR & TIM_SR_UIF) {  											// �������� ����� ����������
        TIM1->SR &= ~TIM_SR_UIF;  										// �������� ����
	}				
	if  (count == 0){																		// ��������� �������
				if  (*p == NULL){															// ��������� ��������� �� ������� ������
				p = (uint16_t*) &freq_values;									// ���������� ����� ������� freq_values � ��������� 
				count = *(p);																	// ���������� � ������� �������� ������� �������� �������
				TIM1->RCR  = *(p+1);
				} else {
				count = *(p+=2);															// ����������� ����� �������� ��c���� �� 2 � ���������� � ������� �������� �������� �������
				TIM1->RCR  = *(p+1);

				}	
		} else{
		count--;																					// �������������� �������
// ������������ ��������� ����������
		GPIOA->ODR ^= GPIO_ODR_ODR_8;  										// ������������� ��������� PA8	
		}
}
