#ifndef STM32F767XX_RCC_H_
#define STM32F767XX_RCC_H_

#include "stm32f7xx.h" 

static	const int freqHSE = 8000000;		// ������� �������� ���������� ����������
static	int PLLM;												// ������������ PLLM
static	int PLLN;												// ���������� PLLN
static	int PLLP;												// �������� PLLP
static	int AHB;												// �������� AHB
static	int APB1;												// �������� APB1
static	int APB2;												// �������� APB2
static	int freqAPB1;										// ������ ������� �� ���� APB1.
static	int freqAPB2;										// ������ ������� �� ���� APB2.


void RCC_Init(void);

#endif
