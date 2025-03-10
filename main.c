#include "main.h"                  // Device header

		// Массив значений для коэффициента заполнения ШИМ
static uint16_t freq_values[2][10] = {{10000,1000},{60000,40000}};
static const uint16_t freq_values_size = sizeof(freq_values) / sizeof(freq_values[0]);


		// Инициализация GPIO
void GPIO_Init(void) {
    // Включение тактирования GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Настройка PA8 как альтернативной функции (TIM1_CH1)
    GPIOA->MODER &= ~GPIO_MODER_MODER8;  											// Очистить режим для PA8
    GPIOA->MODER |= GPIO_MODER_MODER8_1; 											// Установить режим альтернативной функции
    GPIOA->AFR[1] |= (1 << 0);           											// AFR[1] для PA8: AF1 (TIM1_CH1)
}

		// Инициализация таймера TIM1
void TIM1_Init(void) {
    // Включение тактирования TIM1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    // Настройка таймера
    TIM1->PSC = 1;  																					// Предделитель (216 МГц / 216 = 1 МГц)
    //TIM1->ARR = 10000 - 1; 																	// Период (1000 тактов = 1 кГц)
    TIM1->CCR1 = 100000;     																	// Начальный коэффициент заполнения (50%)
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;  			// Режим PWM1
    TIM1->CCER |= TIM_CCER_CC1E;  														// Включить канал 1
    TIM1->BDTR |= TIM_BDTR_MOE;   														// Включить основной выход
    TIM1->CR1 |= TIM_CR1_CEN;     														// Запустить таймер
}

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
}

int main(void) {
	
//		NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 2);  								// Приоритет прерывания TIM1
//		NVIC_SetPriority(DMA2_Stream7_IRQn, 1);   								// Приоритет прерывания DMA2 Stream7

		// Включение прерываний
//   NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
//    NVIC_EnableIRQ(DMA2_Stream7_IRQn);
			
//		TIM1->EGR |= TIM_EGR_UG;																	//инициализация счётчика и обновление регистров
//		TIM1->SR &= ~TIM_SR_UIF;																	//очистка флага обновления	

    GPIO_Init();																							// Инициализация GPIO
		TIM1_Init();																							// Инициализация таймера
    DMA_Init();																								// Инициализация DMA

    
    // Бесконечный цикл
    for(;;) {
//		for (volatile int i=0;i<1000000;i++){}
        // Основной код
    }
}
