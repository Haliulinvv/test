#ifndef STM32F767XX_RCC_H_
#define STM32F767XX_RCC_H_

#include "stm32f7xx.h" 

static	const int freqHSE = 8000000;		// Частота внешенго кварцевого резонатора
static	int PLLM;												// Предделитель PLLM
static	int PLLN;												// Умножитель PLLN
static	int PLLP;												// Делитель PLLP
static	int AHB;												// Делитель AHB
static	int APB1;												// Делитель APB1
static	int APB2;												// Делитель APB2
static	int freqAPB1;										// Расчет частоты на шине APB1.
static	int freqAPB2;										// Расчет частоты на шине APB2.


void RCC_Init(void);

#endif
