#include "main.h"                  // Device header

int main(void) {
	
		RCC_Init();																								// Инициализация RCC
    GPIO_Init();																							// Инициализация GPIO
		TIM1_Init();																							// Инициализация TIM1
    DMA_Init();																								// Инициализация DMA
   
    // Бесконечный цикл
    for(;;) {

        // Основной код
			
    }
}
