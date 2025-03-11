#include "stm32f767xx_DMA.h"		
#define ON 1
#define OFF 0

		// Инициализация DMA для TIM1_CH1
void DMA_Init(void) {
    // Включение тактирования DMA2
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // Настройка DMA2 Stream 1 для TIM1_CH1 (канал 6)
#if ON
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
#endif
	
    // Настройка DMA2 Stream 3 для TIM1_CH1 (канал 6)
#if OFF
    DMA2_Stream3->CR &= ~DMA_SxCR_EN;  												// Отключить поток DMA
    DMA2_Stream3->CR |= DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1;  // Канал 6 (TIM1_CH1)
    DMA2_Stream3->PAR = (uint32_t)&TIM1->RCR;  								// Адрес регистра RСR
    DMA2_Stream3->M0AR = (uint32_t)freq_values;  							// Адрес массива данных
    DMA2_Stream3->NDTR = freq_values_size;  									// Количество данных
		DMA2_Stream3->CR |= DMA_SxCR_MSIZE_0;  										// Установить шаг инкремента адреса памяти 16бит
    DMA2_Stream3->CR |= DMA_SxCR_MINC;  											// Включить инкремент адреса памяти
		DMA2_Stream3->CR |= DMA_SxCR_CIRC;  											// Включить циклический режим
		DMA2_Stream3->CR |= DMA_SxCR_DIR_0;  											// Направление: память -> периферия
    DMA2_Stream3->CR |= DMA_SxCR_EN;  												// Включить поток DMA	
#endif

		// Настройка приоритетов
#if OFF		
		NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 2);  								// Приоритет прерывания TIM1
		NVIC_SetPriority(DMA2_Stream1_IRQn, 1);   								// Приоритет прерывания DMA2 Stream1
		NVIC_SetPriority(DMA2_Stream3_IRQn, 1);   								// Приоритет прерывания DMA2 Stream3
#endif

			// Настройка прерываний
#if OFF		
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);												// Включение прерывания TIM1
    NVIC_EnableIRQ(DMA2_Stream1_IRQn);												// Включение прерывания DMA2 Streem1
    NVIC_EnableIRQ(DMA2_Stream3_IRQn);												// Включение прерывания DMA2 Streem3
#endif

//		TIM1->EGR |= TIM_EGR_UG;																	//инициализация счётчика и обновление регистров
//		TIM1->SR &= ~TIM_SR_UIF;																	//очистка флага обновления	

// Включение DMA для TIM1_CH1
    TIM1->DIER |= TIM_DIER_CC1DE;  														// События DMA для CCR1 TIM1
}
