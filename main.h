#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f767xx_RCC.h" 
#include "stm32f767xx_GPIO.h"
#include "stm32f767xx_TIM.h"
#include "stm32f767xx_DMA.h"	

// Массив значений для коэффициента заполнения ШИМ	
static uint16_t freq_values[2][10] = {{10000,1000},{60000,40000}};
static const uint16_t freq_values_size = sizeof(freq_values) / sizeof(freq_values[0]);	


//объявление констант


//объявление функций


//объявление прерываний
void TIM1_UP_TIM10_IRQHandler(void);

#endif
