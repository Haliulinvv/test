#include "stm32f767xx_RCC.h" 
// ======================= ������������� ������������ ==========================

void RCC_Init(void)
{
	#if 1
	RCC->CR = 0;																									// �������� �������
	RCC->CR &= ~RCC_CR_HSION;
	RCC->CR |= RCC_CR_HSEON;																			//��������� �������� ��������� ���������� ������� ���������� �������� ������ HSE
	while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET) {} 					//HSE �������� ���������? �������� ������������ ��������� ������� HSE
		
//��� ��������� ������������ ������������ ����� �� ������� 13 �� ���. 154 RM0410
	RCC->PLLCFGR = 0;																							// �������� �������
	RCC->PLLCFGR	|= RCC_PLLCFGR_PLLSRC_HSE;											//���������� ������������� ��������� ��������� ������������ PLL �� HSE. ������������� HSI/HSE ��������� ��������� ������������ PLL
	RCC->PLLCFGR	|= (8<<RCC_PLLCFGR_PLLM_Pos);										//�������� PLLM=8. ��������� �������� PLLM /2.../63
	RCC->PLLCFGR	|= (432<<RCC_PLLCFGR_PLLN_Pos);									//���������� PLLN=432. ��������� ���������� PLLN �50...x432							
	RCC->PLLCFGR	|= (0 << RCC_PLLCFGR_PLLP_Pos);									//�������� PLLP=2. ��������� �������� PLLP /2 /4 /6 /8
		
	RCC->CR |= RCC_CR_PLLON;  																		// �������� PLL
	while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) != (RCC_CR_PLLRDY)) {}	//������������ PLL? �������� ������������ �� PLL
	RCC->CFGR = 0;																								// �������� �������
																										
//	RCC->CFGR |= RCC_CFGR_SW_HSE;
//	while((RCC->CFGR & RCC_CFGR_SWS_HSE)!= RCC_CFGR_SWS_HSE){}
//	RCC->CFGR |= RCC_CFGR_SW_HSI;
//	while((RCC->CFGR & RCC_CFGR_SWS_HSI)!= RCC_CFGR_SWS_HSI){}
	RCC->CFGR |= RCC_CFGR_SW_PLL;																	//���������� ������������� SW ��������� ���� ABH �� PLLCLK. ������������� HSI/HSE/PLLCLK 										
	while((RCC->CFGR & RCC_CFGR_SWS)!= RCC_CFGR_SWS_PLL){}				//��������� ���� ABH �����������  �� PLLCLK? �������� ��������� ������������ ��������� ���� ABH.		
	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV2;															//�������� AHB=1. ��������� �������� AHB /1 /2 /4 /8 /16 /32 /64 /128 /256 /512 
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;															//�������� APB1=2. ��������� �������� /1 /2 /4 /8 /16  MAX ������� ���� APB1 45MHz
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;															//�������� APB2=2. ��������� �������� /1 /2 /4 /8 /16  MAX ������� ���� APB2 90MHz
	#endif	
	

PLLM = 8;																												// ������������ PLLM
PLLN = 432;																											// ���������� PLLN
PLLP = 2;																												// �������� PLLP
AHB = 1;																												// �������� AHB
APB1 = 2;																												// �������� APB1
APB2 = 2;																												// �������� APB2
freqAPB1 = freqHSE / PLLM * PLLN / PLLP / AHB /APB1;						// ������ ������� �� ���� APB1
freqAPB2 = freqHSE / PLLM * PLLN / PLLP / AHB /APB2;						// ������ ������� �� ���� APB2
							
}
