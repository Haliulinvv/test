#include "stm32f767xx_TIM.h"

// ������������� TIM1
void TIM1_Init(void) {
// ��������� ������������ TIM1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

// ��������� �������
	  TIM1->PSC = 1;  																					// ������������ (??? ��� / ??? = ?? ���)
//    TIM1->ARR = 10000 - 1; 																	// ������ (????? ������ = ??? ���)
    TIM1->CCR1 = 100000;     																	// ��������� ����������� ���������� (???%)
//		TIM1->RCR = 100000;																			// ������� �������� ����������
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;  			// ����� PWM1
    TIM1->CCER 	|= TIM_CCER_CC1E;  														// �������� ����� 1
    TIM1->BDTR 	|= TIM_BDTR_MOE;   														// �������� �������� �����
    TIM1->CR1 	|= TIM_CR1_CEN;     													// ��������� ������

// ��������� ���������� �� ����������
    TIM1->DIER 	|= TIM_DIER_UIE;  														// ��������� ���������� �� ����������

// ������ �������
    TIM1->CR1 	|= TIM_CR1_CEN;  															// �������� ������

// ��������� NVIC ��� TIM1
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);  											// �������� ���������� � NVIC
    NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0);  								// ���������� ���������
}
