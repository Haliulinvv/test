#include "stm32f767xx_GPIO.h"

#define ON 1
#define OFF 0

//функция инициализации провтов ввода-вывода GPIO
void GPIO_Init(void)
{

	
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOAEN;									//инициализация тактирования порта GPIOA

//Сброс регистров	
GPIOA->OSPEEDR 	&=~	GPIO_OSPEEDR_OSPEEDR8; 						//reset PA8. Регистр выбора скорости Low / Medium / High / Very high speed
GPIOA->OTYPER 	&=~	GPIO_OTYPER_OT8; 									//reset PA8. Регистр выбора режима push-pull/open-drain (PP/OD)
GPIOA->PUPDR 		&=~	GPIO_PUPDR_PUPDR8; 								//reset PA8. Регистр выбора режима pull-up/pull-down (PU/PD)
GPIOA->MODER 		&=~	GPIO_MODER_MODER8; 								//reset PA8. Регистр выбора режима порта цифровой вход/цифровой выход/АФ/аналоговый вход /аналоговый выход

//Установка порта как цифровой вход
#if OFF	
// Настройка PC13 как входа (кнопка)
GPIOC->MODER 		&= ~GPIO_MODER_MODER13;  								// Запись значения 0 в регистр MODER13 настраивает PC13 на выход
//GPIOC->PUPDR 		|= 	GPIO_PUPDR_PUPDR13_1;  							// Подтяжка к минусу PD
GPIOC->PUPDR 		&= ~GPIO_PUPDR_PUPDR13_1;  							// Подтяжка к плюсу PU	
#endif		

	
//Установка порта как цифровой выход
#if OFF
GPIOA->MODER		|=	GPIO_MODER_MODER8_0;
GPIOA->MODER		&=~	GPIO_MODER_MODER8_1;	
GPIOA->OSPEEDR 	&=~	GPIO_OSPEEDR_OSPEEDR8;							// Скорость Low speed
GPIOA->OTYPER 	&=~	GPIO_OTYPER_OT8;										// Выход как два устойчихых состояния (push-pull)
//GPIOA->OTYPER 	|=	GPIO_OTYPER_OT8;										// Выход как открытый исток (open-drain)
//GPIOA->PUPDR 		|= 	GPIO_PUPDR_PUPDR8_1;  							// Подтяжка к минусу PD
//GPIOA->PUPDR 		&= ~GPIO_PUPDR_PUPDR8_1;  							// Подтяжка к плюсу PU
GPIOA->PUPDR 		&= ~GPIO_PUPDR_PUPDR8;  								// Без подтяжки
#endif	

//Настройка альтернативного режима	
#if ON
	
#define AF0 0x00
#define AF1 0x01
#define AF2 0x02
#define AF3 0x03
#define AF4 0x04
#define AF5 0x05
#define AF6 0x06
#define AF7 0x07
#define AF8 0x08
#define AF9 0x09
#define AF10 0x0A
#define AF11 0x0B
#define AF12 0x0C
#define AF13 0x0D
#define AF14 0x0E
#define AF15 0x0F
	
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 0
#define PIN9 1
#define PIN10 2
#define PIN11 3
#define PIN12 4
#define PIN13 5
#define PIN14 6
#define PIN15 7

	//Массив AFR[0] для портов 0-7, и  AFR[1] для портов 8-15
//GPIOA->AFR[0] 	|= (AF1<<4*PIN1); 											 //установка PA1 в режим альтернативной функции AF1	
GPIOA->AFR[1] 	|= (AF1<<4*PIN8); 											 //установка PA8 в режим альтернативной функции AF1

GPIOA->MODER		&=~ GPIO_MODER_MODER8_0; 								 //установка PA8  в режим альтернативной функции
GPIOA->MODER 		|=	GPIO_MODER_MODER8_1; 								 //установка PA8  в режим альтернативной функции
//GPIOA->OSPEEDR 	|= 	GPIO_OSPEEDR_OSPEEDR8;							// Скорость Very high speed
//GPIOA->OTYPER 	&=~	GPIO_OTYPER_OT8;										// Выход как два устойчихых состояния (push-pull)
//GPIOA->OTYPER 	|=	GPIO_OTYPER_OT8;										// Выход как открытый исток (open-drain)
GPIOA->PUPDR 		|= 	GPIO_PUPDR_PUPDR8_1;  							// Подтяжка к минусу PD
//GPIOA->PUPDR 		&= ~GPIO_PUPDR_PUPDR8_1;  							// Подтяжка к плюсу PU
GPIOA->PUPDR 			&= ~GPIO_PUPDR_PUPDR8;  							// Без подтяжки
#endif
}

//Установка порта как аналоговый вход/выход
#if OFF
// Настройка PC13 как входа
GPIOC->MODER 		|= GPIO_MODER_MODER13;  							// Запись значения 1 в регистр MODER13 настраивает PC13 на аналоговый вход/выход
//GPIOC->PUPDR 		|= 	GPIO_PUPDR_PUPDR13_1;  							// Подтяжка к минусу PD
//GPIOC->PUPDR 		&= ~GPIO_PUPDR_PUPDR13_1;  							// Подтяжка к плюсу PU	
#endif
