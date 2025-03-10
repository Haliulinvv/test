#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f7xx.h"                  // Keil::Device:Startup

//���������� ��������
//#define rate 255					//��-��-�� �������� ��������� ����� #define ������ ���, ����� ��� ��� ����. � ���� ���������� ����� #define ���� ��� ���������� ������� RATE
static const int rate = 255;

//���������� �������

void GPIO_Init(void);
void DMA_Init(void);
void TIM1_Init(void);

#endif
