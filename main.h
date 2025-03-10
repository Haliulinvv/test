#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f7xx.h"                  // Keil::Device:Startup

//объ€вление констант
//#define rate 255					//‘у-‘у-‘у  онстаны объ€вл€ть через #define дурной тон, делай это как ниже. ј если объ€вл€ешь через #define пиши им€ заглавными буквами RATE
static const int rate = 255;

//объ€вление функций

void GPIO_Init(void);
void DMA_Init(void);
void TIM1_Init(void);

#endif
