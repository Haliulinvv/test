#include "stm32f767xx_DMA.h"		


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
		
//		NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 2);  								// ��������� ���������� TIM1
//		NVIC_SetPriority(DMA2_Stream7_IRQn, 1);   								// ��������� ���������� DMA2 Stream7

		// ��������� ����������
//   NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
//    NVIC_EnableIRQ(DMA2_Stream7_IRQn);
			
//		TIM1->EGR |= TIM_EGR_UG;																	//������������� �������� � ���������� ���������
//		TIM1->SR &= ~TIM_SR_UIF;																	//������� ����� ����������	
}
