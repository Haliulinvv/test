#include "stm32f767xx_it.h"
#include "stddef.h"

static uint16_t freq_values[10][2] = {{4,100},{6,50},{8,200}};
//static const uint16_t freq_values_size = sizeof(freq_values) / sizeof(freq_values[0]);
static uint16_t *p = NULL;

static uint32_t count = 0;


// Обработчик прерывания TIM1
void TIM1_UP_TIM10_IRQHandler(void) {
  if (TIM1->SR & TIM_SR_UIF) {  											// Проверка флага прерывания
        TIM1->SR &= ~TIM_SR_UIF;  										// Сбросить флаг
	}				
	if  (count == 0){																		// Проверяем счетчик
				if  (*p == NULL){															// Проверяем указатель на нулевой символ
				p = (uint16_t*) &freq_values;									// Записываем адрес массива freq_values в указатель 
				count = *(p);																	// Записываем в счетчик значение первого элемента массива
				TIM1->RCR  = *(p+1);
				} else {
				count = *(p+=2);															// Увеличиваем адрес элемента маcсива на 2 и записываем в счетчик значение элемента массива
				TIM1->RCR  = *(p+1);

				}	
		} else{
		count--;																					// Декрементируем счетчик
// Переключение состояния светодиода
		GPIOA->ODR ^= GPIO_ODR_ODR_8;  										// Инвертировать состояние PA8	
		}
}
