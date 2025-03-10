#include "main.h"                  // Device header

int main(void) {
	
    GPIO_Init();																							// Инициализация GPIO
		TIM1_Init();																							// Инициализация таймера
    DMA_Init();																								// Инициализация DMA
   
    // Бесконечный цикл
    for(;;) {

        // Основной код
			
    }
}
