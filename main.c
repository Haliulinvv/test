#include "main.h"                  // Device header

		// ������ �������� ��� ������������ ���������� ���
static uint16_t freq_values[2][10] = {{10000,1000},{60000,40000}};
static const uint16_t freq_values_size = sizeof(freq_values) / sizeof(freq_values[0]);


		// ������������� GPIO
void GPIO_Init(void) {
    // ��������� ������������ GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // ��������� PA8 ��� �������������� ������� (TIM1_CH1)
    GPIOA->MODER &= ~GPIO_MODER_MODER8;  											// �������� ����� ��� PA8
    GPIOA->MODER |= GPIO_MODER_MODER8_1; 											// ���������� ����� �������������� �������
    GPIOA->AFR[1] |= (1 << 0);           											// AFR[1] ��� PA8: AF1 (TIM1_CH1)
}

		// ������������� ������� TIM1
void TIM1_Init(void) {
    // ��������� ������������ TIM1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    // ��������� �������
    TIM1->PSC = 1;  																					// ������������ (216 ��� / 216 = 1 ���)
    //TIM1->ARR = 10000 - 1; 																	// ������ (1000 ������ = 1 ���)
    TIM1->CCR1 = 100000;     																	// ��������� ����������� ���������� (50%)
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;  			// ����� PWM1
    TIM1->CCER |= TIM_CCER_CC1E;  														// �������� ����� 1
    TIM1->BDTR |= TIM_BDTR_MOE;   														// �������� �������� �����
    TIM1->CR1 |= TIM_CR1_CEN;     														// ��������� ������
}

		// ������������� DMA ��� TIM1_CH1
void DMA_Init(void) {
    // ��������� ������������ DMA2
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // ��������� DMA2 Stream 1 ��� TIM1_CH1 (����� 6)
    DMA2_Stream1->CR &= ~DMA_SxCR_EN;  												// ��������� ����� DMA
    DMA2_Stream1->CR |= DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1;  // ����� 6 (TIM1_CH1)
    DMA2_Stream1->PAR = (uint32_t)&TIM1->ARR;  								// ����� �������� ARR
    DMA2_Stream1->M0AR = (uint32_t)freq_values+1;  						// ����� ������� ������
    DMA2_Stream1->NDTR = freq_values_size;  									// ���������� ������
    DMA2_Stream1->CR |= DMA_SxCR_MSIZE_0;  										// ���������� ��� ���������� ������ ������ 16���
		DMA2_Stream1->CR |= DMA_SxCR_MINC;												// �������� ��������� ������ ������
		DMA2_Stream1->CR |= DMA_SxCR_CIRC;  											// �������� ����������� �����
		DMA2_Stream1->CR |= DMA_SxCR_DIR_0;  											// �����������: ������ -> ���������
    DMA2_Stream1->CR |= DMA_SxCR_EN;  												// �������� ����� DMA

    // ��������� DMA2 Stream 3 ��� TIM1_CH1 (����� 6)
    DMA2_Stream3->CR &= ~DMA_SxCR_EN;  												// ��������� ����� DMA
    DMA2_Stream3->CR |= DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1;  // ����� 6 (TIM1_CH1)
    DMA2_Stream3->PAR = (uint32_t)&TIM1->CCR1;  							// ����� �������� CCR1
    DMA2_Stream3->M0AR = (uint32_t)freq_values;  							// ����� ������� ������
    DMA2_Stream3->NDTR = freq_values_size;  									// ���������� ������
		DMA2_Stream3->CR |= DMA_SxCR_MSIZE_0;  										// ���������� ��� ���������� ������ ������ 16���
    DMA2_Stream3->CR |= DMA_SxCR_MINC;  											// �������� ��������� ������ ������
		DMA2_Stream3->CR |= DMA_SxCR_CIRC;  											// �������� ����������� �����
		DMA2_Stream3->CR |= DMA_SxCR_DIR_0;  											// �����������: ������ -> ���������
    DMA2_Stream3->CR |= DMA_SxCR_EN;  												// �������� ����� DMA	
	
    // ��������� DMA ��� TIM1_CH1
    TIM1->DIER |= TIM_DIER_CC1DE;  														// ��������� DMA ��� CCR1
}

int main(void) {
	
//		NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 2);  								// ��������� ���������� TIM1
//		NVIC_SetPriority(DMA2_Stream7_IRQn, 1);   								// ��������� ���������� DMA2 Stream7

		// ��������� ����������
//   NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
//    NVIC_EnableIRQ(DMA2_Stream7_IRQn);
			
//		TIM1->EGR |= TIM_EGR_UG;																	//������������� �������� � ���������� ���������
//		TIM1->SR &= ~TIM_SR_UIF;																	//������� ����� ����������	

    GPIO_Init();																							// ������������� GPIO
		TIM1_Init();																							// ������������� �������
    DMA_Init();																								// ������������� DMA

    
    // ����������� ����
    for(;;) {
//		for (volatile int i=0;i<1000000;i++){}
        // �������� ���
    }
}
