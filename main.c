#include "main.h"                  // Device header

struct Packet{
uint8_t n;
uint16_t freq;
};

static struct Packet signal[MAX_SIZE] = {{2,100},{3,50},{2,200}};

struct Generator_name{
void (*add)(struct Packet*);
void (*start)(void);
void (*stop)(void);
};
static volatile struct Generator_name generator;

void add (struct Packet *signal);

int main(void) {

		RCC_Init();																								// ������������� RCC
    GPIO_Init();																							// ������������� GPIO
		TIM1_Init();
		generator.start = &start;
		generator.stop = &stop;
		generator.add = &add;
		generator.add((struct Packet *)signal);
		generator.start();
		//generator.stop();

    // ����������� ����
    for(;;) {
			// �������� ���																	
    }
}

void add (struct Packet *_signal){
	for(int i=0; i <= MAX_SIZE-1; i++){
	freq_values[i][0] = (uint16_t) _signal[i].n;
	freq_values[i][1] = (uint16_t) _signal[i].freq;
	}
}

void start (void){
// ������ �������
    TIM1->CR1 	|= TIM_CR1_CEN;  															// �������� ������
}

void stop (void){
// ��������� �������
    TIM1->CR1 	&= ~TIM_CR1_CEN;  														// ��������� ������
}

