#include "stm32f767xx_RCC.h" 
// ======================= Инициализация тактирования ==========================

void RCC_Init(void)
{
	#if 1
	RCC->CR = 0;																									// Сбросить регистр
	RCC->CR &= ~RCC_CR_HSION;
	RCC->CR |= RCC_CR_HSEON;																			//Включение внешнего тактового генератора который генерирует тактовый сигнал HSE
	while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET) {} 					//HSE работает стабильно? Проверка стабильности тактового сигнала HSE
		
//Для настройти тактирования использовать схему из рисунка 13 на стр. 154 RM0410
	RCC->PLLCFGR = 0;																							// Сбросить регистр
	RCC->PLLCFGR	|= RCC_PLLCFGR_PLLSRC_HSE;											//Установить переключатель основного источника тактирования PLL от HSE. Переключатель HSI/HSE основного источника тактирования PLL
	RCC->PLLCFGR	|= (8<<RCC_PLLCFGR_PLLM_Pos);										//Делитель PLLM=8. Установка делителя PLLM /2.../63
	RCC->PLLCFGR	|= (432<<RCC_PLLCFGR_PLLN_Pos);									//Умножитель PLLN=432. Установка умножителя PLLN х50...x432							
	RCC->PLLCFGR	|= (0 << RCC_PLLCFGR_PLLP_Pos);									//Делитель PLLP=2. Установка делителя PLLP /2 /4 /6 /8
		
	RCC->CR |= RCC_CR_PLLON;  																		// Включить PLL
	while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) != (RCC_CR_PLLRDY)) {}	//Заблокирован PLL? Проверка заблокирован ли PLL
	RCC->CFGR = 0;																								// Сбросить регистр
																										
//	RCC->CFGR |= RCC_CFGR_SW_HSE;
//	while((RCC->CFGR & RCC_CFGR_SWS_HSE)!= RCC_CFGR_SWS_HSE){}
//	RCC->CFGR |= RCC_CFGR_SW_HSI;
//	while((RCC->CFGR & RCC_CFGR_SWS_HSI)!= RCC_CFGR_SWS_HSI){}
	RCC->CFGR |= RCC_CFGR_SW_PLL;																	//Установить переключатель SW системной шины ABH от PLLCLK. Переключатель HSI/HSE/PLLCLK 										
	while((RCC->CFGR & RCC_CFGR_SWS)!= RCC_CFGR_SWS_PLL){}				//Системной шина ABH тактируется  от PLLCLK? Проверка источника тактирования системной шины ABH.		
	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV2;															//Делитель AHB=1. Установка делителя AHB /1 /2 /4 /8 /16 /32 /64 /128 /256 /512 
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;															//Делитель APB1=2. Установка делителя /1 /2 /4 /8 /16  MAX частота шины APB1 45MHz
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;															//Делитель APB2=2. Установка делителя /1 /2 /4 /8 /16  MAX частота шины APB2 90MHz
	#endif	
	

PLLM = 8;																												// Предделитель PLLM
PLLN = 432;																											// Умножитель PLLN
PLLP = 2;																												// Делитель PLLP
AHB = 1;																												// Делитель AHB
APB1 = 2;																												// Делитель APB1
APB2 = 2;																												// Делитель APB2
freqAPB1 = freqHSE / PLLM * PLLN / PLLP / AHB /APB1;						// Расчет частоты на шине APB1
freqAPB2 = freqHSE / PLLM * PLLN / PLLP / AHB /APB2;						// Расчет частоты на шине APB2
							
}
