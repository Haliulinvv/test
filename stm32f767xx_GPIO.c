#include "stm32f767xx_GPIO.h"

#define ON 1
#define OFF 0

//������� ������������� ������� �����-������ GPIO
void GPIO_Init(void)
{

//��������� ������������ ������	
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOAEN;									//������������� ������������ ����� GPIOA
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOBEN;									//������������� ������������ ����� GPIOB
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOCEN;									//������������� ������������ ����� GPIOC
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIODEN;									//������������� ������������ ����� GPIOD
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOEEN;									//������������� ������������ ����� GPIOE
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOFEN;									//������������� ������������ ����� GPIOF
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOGEN;									//������������� ������������ ����� GPIOG
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOHEN;									//������������� ������������ ����� GPIOH
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOIEN;									//������������� ������������ ����� GPIOI
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOJEN;									//������������� ������������ ����� GPIOJ
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIOKEN;									//������������� ������������ ����� GPIOK

//����� ���������	PA8
GPIOA->OSPEEDR 	&=~	GPIO_OSPEEDR_OSPEEDR8; 						//������� ������ �������� Low / Medium / High / Very high speed
GPIOA->OTYPER 	&=~	GPIO_OTYPER_OT8; 									//������� ������ ������ push-pull/open-drain (PP/OD)
GPIOA->PUPDR 		&=~	GPIO_PUPDR_PUPDR8; 								//������� ������ ������ pull-up/pull-down (PU/PD)
GPIOA->MODER 		&=~	GPIO_MODER_MODER8; 								//������� ������ ������ ����� �������� ����/�������� �����/��/���������� ���� /���������� �����
	
//����� ���������	PB0
GPIOB->OSPEEDR 	&=~	GPIO_OSPEEDR_OSPEEDR0; 						//������� ������ �������� Low / Medium / High / Very high speed
GPIOB->OTYPER 	&=~	GPIO_OTYPER_OT0; 									//������� ������ ������ push-pull/open-drain (PP/OD)
GPIOB->PUPDR 		&=~	GPIO_PUPDR_PUPDR0; 								//������� ������ ������ pull-up/pull-down (PU/PD)
GPIOB->MODER 		&=~	GPIO_MODER_MODER0; 								//������� ������ ������ ����� �������� ����/�������� �����/��/���������� ���� /���������� �����

//��������� ����� ��� �������� ����
#if OFF	
// ��������� PC13 ��� ����� (������)
GPIOC->MODER 		&= ~GPIO_MODER_MODER13;  								// ������ �������� 0 � ������� MODER13 ����������� PC13 �� �����
//GPIOC->PUPDR 		|= 	GPIO_PUPDR_PUPDR13_1;  							// �������� � ������ PD
GPIOC->PUPDR 		&= ~GPIO_PUPDR_PUPDR13_1;  							// �������� � ����� PU	
#endif		

	
//��������� ����� ��� �������� �����
#if ON

//------------ ������������� PB0 ---------------
GPIOB->MODER		|=	GPIO_MODER_MODER0_0;
GPIOB->MODER		&=~	GPIO_MODER_MODER0_1;	
GPIOB->OSPEEDR 	&=~	GPIO_OSPEEDR_OSPEEDR0;							// �������� Low speed
GPIOB->OTYPER 	&=~	GPIO_OTYPER_OT0;										// ����� ��� ��� ���������� ��������� (push-pull)
//GPIOB->OTYPER 	|=	GPIO_OTYPER_OT0;										// ����� ��� �������� ����� (open-drain)
//GPIOB->PUPDR 		|= 	GPIO_PUPDR_PUPDR0_1;  							// �������� � ������ PD
//GPIOB->PUPDR 		&= ~GPIO_PUPDR_PUPDR0_1;  							// �������� � ����� PU
GPIOB->PUPDR 		&= ~GPIO_PUPDR_PUPDR0;  								// ��� ��������


//------------ ������������� PA8 ---------------
GPIOA->MODER		|=	GPIO_MODER_MODER8_0;
GPIOA->MODER		&=~	GPIO_MODER_MODER8_1;	
GPIOA->OSPEEDR 	&=~	GPIO_OSPEEDR_OSPEEDR8;							// �������� Low speed
GPIOA->OTYPER 	&=~	GPIO_OTYPER_OT8;										// ����� ��� ��� ���������� ��������� (push-pull)
//GPIOA->OTYPER 	|=	GPIO_OTYPER_OT8;										// ����� ��� �������� ����� (open-drain)
//GPIOA->PUPDR 		|= 	GPIO_PUPDR_PUPDR8_1;  							// �������� � ������ PD
//GPIOA->PUPDR 		&= ~GPIO_PUPDR_PUPDR8_1;  							// �������� � ����� PU
GPIOA->PUPDR 		&= ~GPIO_PUPDR_PUPDR8;  								// ��� ��������
#endif	

//��������� ��������������� ������	
#if OFF
	
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

	//������ AFR[0] ��� ������ 0-7, �  AFR[1] ��� ������ 8-15
//GPIOA->AFR[0] 	|= (AF1<<4*PIN1); 											 //��������� PA1 � ����� �������������� ������� AF1	
GPIOA->AFR[1] 	|= (AF1<<4*PIN8); 											 //��������� PA8 � ����� �������������� ������� AF1

GPIOA->MODER		&=~ GPIO_MODER_MODER8_0; 								 //��������� PA8  � ����� �������������� �������
GPIOA->MODER 		|=	GPIO_MODER_MODER8_1; 								 //��������� PA8  � ����� �������������� �������
//GPIOA->OSPEEDR 	|= 	GPIO_OSPEEDR_OSPEEDR8;							// �������� Very high speed
//GPIOA->OTYPER 	&=~	GPIO_OTYPER_OT8;										// ����� ��� ��� ���������� ��������� (push-pull)
//GPIOA->OTYPER 	|=	GPIO_OTYPER_OT8;										// ����� ��� �������� ����� (open-drain)
GPIOA->PUPDR 		|= 	GPIO_PUPDR_PUPDR8_1;  							// �������� � ������ PD
//GPIOA->PUPDR 		&= ~GPIO_PUPDR_PUPDR8_1;  							// �������� � ����� PU
GPIOA->PUPDR 			&= ~GPIO_PUPDR_PUPDR8;  							// ��� ��������
#endif
}

//��������� ����� ��� ���������� ����/�����
#if OFF
// ��������� PC13 ��� �����
GPIOC->MODER 		|= GPIO_MODER_MODER13;  							// ������ �������� 1 � ������� MODER13 ����������� PC13 �� ���������� ����/�����
//GPIOC->PUPDR 		|= 	GPIO_PUPDR_PUPDR13_1;  							// �������� � ������ PD
//GPIOC->PUPDR 		&= ~GPIO_PUPDR_PUPDR13_1;  							// �������� � ����� PU	
#endif
