#include "stm32f767xx_DMA.h"		
#define ON 1
#define OFF 0

		// ������������� DMA ��� TIM1_CH1
void DMA_Init(void) {
    // ��������� ������������ DMA2
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // ��������� DMA2 Stream 1 ��� TIM1_CH1 (����� 6)
#if ON
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
#endif
	
    // ��������� DMA2 Stream 3 ��� TIM1_CH1 (����� 6)
#if OFF
    DMA2_Stream3->CR &= ~DMA_SxCR_EN;  												// ��������� ����� DMA
    DMA2_Stream3->CR |= DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1;  // ����� 6 (TIM1_CH1)
    DMA2_Stream3->PAR = (uint32_t)&TIM1->RCR;  								// ����� �������� R�R
    DMA2_Stream3->M0AR = (uint32_t)freq_values;  							// ����� ������� ������
    DMA2_Stream3->NDTR = freq_values_size;  									// ���������� ������
		DMA2_Stream3->CR |= DMA_SxCR_MSIZE_0;  										// ���������� ��� ���������� ������ ������ 16���
    DMA2_Stream3->CR |= DMA_SxCR_MINC;  											// �������� ��������� ������ ������
		DMA2_Stream3->CR |= DMA_SxCR_CIRC;  											// �������� ����������� �����
		DMA2_Stream3->CR |= DMA_SxCR_DIR_0;  											// �����������: ������ -> ���������
    DMA2_Stream3->CR |= DMA_SxCR_EN;  												// �������� ����� DMA	
#endif

		// ��������� �����������
#if OFF		
		NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 2);  								// ��������� ���������� TIM1
		NVIC_SetPriority(DMA2_Stream1_IRQn, 1);   								// ��������� ���������� DMA2 Stream1
		NVIC_SetPriority(DMA2_Stream3_IRQn, 1);   								// ��������� ���������� DMA2 Stream3
#endif

			// ��������� ����������
#if OFF		
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);												// ��������� ���������� TIM1
    NVIC_EnableIRQ(DMA2_Stream1_IRQn);												// ��������� ���������� DMA2 Streem1
    NVIC_EnableIRQ(DMA2_Stream3_IRQn);												// ��������� ���������� DMA2 Streem3
#endif

//		TIM1->EGR |= TIM_EGR_UG;																	//������������� �������� � ���������� ���������
//		TIM1->SR &= ~TIM_SR_UIF;																	//������� ����� ����������	

// ��������� DMA ��� TIM1_CH1
    TIM1->DIER |= TIM_DIER_CC1DE;  														// ������� DMA ��� CCR1 TIM1
}
