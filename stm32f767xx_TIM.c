#include "stm32f767xx_TIM.h"

// Инициализация TIM1
void TIM1_Init(void) {
// Включение тактирования TIM1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

// Настройка таймера
	  TIM1->PSC = 1;  																					// Предделитель (??? МГц / ??? = ?? МГц)
//    TIM1->ARR = 10000 - 1; 																	// Период (????? тактов = ??? кГц)
    TIM1->CCR1 = 100000;     																	// Начальный коэффициент заполнения (???%)
//		TIM1->RCR = 100000;																			// Регистр счетчика повторений
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;  			// Режим PWM1
    TIM1->CCER 	|= TIM_CCER_CC1E;  														// Включить канал 1
    TIM1->BDTR 	|= TIM_BDTR_MOE;   														// Включить основной выход
    TIM1->CR1 	|= TIM_CR1_CEN;     													// Запустить таймер

// Включение прерывания по обновлению
    TIM1->DIER 	|= TIM_DIER_UIE;  														// Разрешить прерывание по обновлению

// Запуск таймера
    TIM1->CR1 	|= TIM_CR1_CEN;  															// Включить таймер

// Настройка NVIC для TIM1
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);  											// Включить прерывание в NVIC
    NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0);  								// Установить приоритет
}
