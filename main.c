#include "main.h"                  // Device header

int main(void) {
	
		RCC_Init();																								// ������������� RCC
    GPIO_Init();																							// ������������� GPIO
		TIM1_Init();																							// ������������� TIM1
    DMA_Init();																								// ������������� DMA
   
    // ����������� ����
    for(;;) {

        // �������� ���
			
    }
}
