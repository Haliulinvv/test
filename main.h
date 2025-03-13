#ifndef MAIN_H_
#define MAIN_H_


#include "stm32f767xx_it.h"
#include "stm32f767xx_RCC.h" 
#include "stm32f767xx_GPIO.h"
#include "stm32f767xx_TIM.h"

#define MAX_SIZE 10



//struct Packet{
//uint8_t n;
//uint16_t freq;
//};

//static struct Packet signal[10] = {{2,100},{3,50},{2,200}};
static uint16_t freq_values[10][2] = {{2,100},{3,50},{2,200}};

//объявление прототипов функций
//void add (struct Packet *signal);
void start (void);
void stop (void);


#endif
