#include "stm32f767xx_RCC.h" 
// ======================= ������������� ������������ ==========================

void RCC_Init(void)
{
	RCC->CR = 0;																									// �������� �������
	RCC->CR |= RCC_CR_HSEON;																			//��������� �������� ��������� ���������� ������� ���������� �������� ������ HSE
	while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET) {} 					//HSE �������� ���������? �������� ������������ ��������� ������� HSE
		
//��� ��������� ������������ ������������ ����� �� ������� 13 �� ���. 154 RM0410
	RCC->PLLCFGR = 0;																							// �������� �������
	RCC->PLLCFGR	|= RCC_PLLCFGR_PLLSRC_HSE;											//���������� ������������� ��������� ��������� ������������ PLL �� HSE. ������������� HSI/HSE ��������� ��������� ������������ PLL
	RCC->PLLCFGR	|= (4<<RCC_PLLCFGR_PLLM_Pos);										//�������� PLLM=4. ��������� �������� PLLM /2.../63
	RCC->PLLCFGR	|= (96<<RCC_PLLCFGR_PLLN_Pos);									//���������� PLLN=96. ��������� ���������� PLLN �50...x432
								
	RCC->PLLCFGR	|=(~RCC_PLLCFGR_PLLP_0);													//�������� PLLP=2. ��������� �������� PLLP /2 /4 /6 /8
	RCC->CR |= RCC_CR_PLLON;  																		// �������� PLL
	while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) != (RCC_CR_PLLRDY)) {}	//������������ PLL? �������� ������������ �� PLL
	RCC->CFGR = 0;																								// �������� �������
	RCC->CFGR |= RCC_CFGR_SW_PLL;																	//���������� ������������� SW ��������� ���� ABH �� PLLCLK. ������������� HSI/HSE/PLLCLK 										
	while((RCC->CFGR & RCC_CFGR_SWS)!= RCC_CFGR_SWS_1){}					//��������� ���� ABH �����������  �� PLLCLK? �������� ��������� ������������ ��������� ���� ABH.		
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;															//�������� AHB=1. ��������� �������� AHB /1 /2 /4 /8 /16 /32 /64 /128 /256 /512 
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;															//�������� APB1=2. ��������� �������� /1 /2 /4 /8 /16  MAX ������� ���� APB1 45MHz
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;															//�������� APB2=2. ��������� �������� /1 /2 /4 /8 /16  MAX ������� ���� APB2 90MHz
							
}
