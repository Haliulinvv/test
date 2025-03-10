#include "stm32f767xx_DMA.h"		


		// Инициализация DMA для TIM1_CH1
void DMA_Init(void) {
    // Включение тактирования DMA2
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // Настройка DMA2 Stream 1 для TIM1_CH1 (канал 6)
    DMA2_Stream1->CR &= ~DMA_SxCR_EN;  												// Отключить поток DMA
    DMA2_Stream1->CR |= DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1;  // Канал 6 (TIM1_CH1)
    DMA2_Stream1->PAR = (uint32_t)&TIM1->ARR;  								// Адрес регистра ARR
    DMA2_Stream1->M0AR = (uint32_t)freq_values+1;  						// Адрес массива данных
    DMA2_Stream1->NDTR = freq_values_size;  									// Количество данных
    DMA2_Stream1->CR |= DMA_SxCR_MSIZE_0;  										// Установить шаг инкремента адреса памяти 16бит
		DMA2_Stream1->CR |= DMA_SxCR_MINC;												// Включить инкремент адреса памяти
		DMA2_Stream1->CR |= DMA_SxCR_CIRC;  											// Включить циклический режим
		DMA2_Stream1->CR |= DMA_SxCR_DIR_0;  											// Направление: память -> периферия
    DMA2_Stream1->CR |= DMA_SxCR_EN;  												// Включить поток DMA

    // Настройка DMA2 Stream 3 для TIM1_CH1 (канал 6)
    DMA2_Stream3->CR &= ~DMA_SxCR_EN;  												// Отключить поток DMA
    DMA2_Stream3->CR |= DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1;  // Канал 6 (TIM1_CH1)
    DMA2_Stream3->PAR = (uint32_t)&TIM1->CCR1;  							// Адрес регистра CCR1
    DMA2_Stream3->M0AR = (uint32_t)freq_values;  							// Адрес массива данных
    DMA2_Stream3->NDTR = freq_values_size;  									// Количество данных
		DMA2_Stream3->CR |= DMA_SxCR_MSIZE_0;  										// Установить шаг инкремента адреса памяти 16бит
    DMA2_Stream3->CR |= DMA_SxCR_MINC;  											// Включить инкремент адреса памяти
		DMA2_Stream3->CR |= DMA_SxCR_CIRC;  											// Включить циклический режим
		DMA2_Stream3->CR |= DMA_SxCR_DIR_0;  											// Направление: память -> периферия
    DMA2_Stream3->CR |= DMA_SxCR_EN;  												// Включить поток DMA	
	
    // Включение DMA для TIM1_CH1
    TIM1->DIER |= TIM_DIER_CC1DE;  														// Разрешить DMA для CCR1
		
//		NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 2);  								// Приоритет прерывания TIM1
//		NVIC_SetPriority(DMA2_Stream7_IRQn, 1);   								// Приоритет прерывания DMA2 Stream7

		// Включение прерываний
//   NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
//    NVIC_EnableIRQ(DMA2_Stream7_IRQn);
			
//		TIM1->EGR |= TIM_EGR_UG;																	//инициализация счётчика и обновление регистров
//		TIM1->SR &= ~TIM_SR_UIF;																	//очистка флага обновления	
}
