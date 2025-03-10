#include "main.h"

static int count = 0;

// Обработчик прерывания TIM1
void TIM1_UP_TIM10_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) {  // Проверка флага прерывания
        TIM1->SR &= ~TIM_SR_UIF;  // Сбросить флаг
		}
		if  (count == 10){
		count = 1 ;
		TIM1->RCR = 50-1;
		GPIOA->ODR |= GPIO_ODR_ODR_8;	
		} else{ 
		TIM1->RCR = 1;
		count++;
			        // Переключение состояния светодиода
		GPIOA->ODR ^= GPIO_ODR_ODR_8;  // Инвертировать состояние PA8		
		}       	
}
