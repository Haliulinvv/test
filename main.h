#ifndef MAIN_H_
#define MAIN_H_


#include "stm32f767xx_it.h"
#include "stm32f767xx_RCC.h" 
#include "stm32f767xx_GPIO.h"
#include "stm32f767xx_TIM.h"
#include "stdbool.h" 

#define MAX_SIZE 10


static uint16_t freq_values[10][2] = {{4,100},{6,50},{4,200}};
//static uint16_t freq_values[10][2] = {{1000,99}};
//объявление прототипов функций

void start (void);
void stop (void);
bool status (void);
int maxSpeed (void);


#endif
