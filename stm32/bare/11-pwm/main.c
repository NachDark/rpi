//#include <stdio.h>
//#include <stdbool.h>

#include <gpio.h>
#include <usart.h>


#define TIM3	((TIMx_t*) 0x40000400)

// section 15.4.4 TIMx DMA/Interrupt enable register (TIMx_DIER)
#define TIM_DIER_UIE (1<<0)
#define TIM_DIER_TIE (1<<6)

#define TIM_EGR_UG (1<<0)
#define TIM_EGR_TG (1<<6)

#define RCC_APB1ENR_TIM3EN (1<<1)
#define TIM_CCER_CC1E (1<<0)



void setup_timer()
{
	RCC_APB1ENR |= RCC_APB1ENR_TIM3EN;
	gpio_mode(PA6, 0b1110); // output, push-pull, alt function
	u32 freq = 440;
	u32 rescale = 10; // we need this so both psc and arr are 16-bits
	TIM3->PSC=72000000UL/freq/rescale -1; 
	TIM3->ARR=freq*rescale-1;
	TIM3->CCR1 = (TIM3->ARR +1)/4 -1; // duty cycle 25% (1/4)
	TIM3->CCER |= TIM_CCER_CC1E; // enable capture/comapre 
	TIM3->CCMR1 |= 0b110<<4; // output pwm compare mode 1 
	//TIM3->EGR |= TIM_EGR_UG;;
	TIM3->CR1 |= TIM_CR1_CEN; // enable counter

	//TIM4->ARR=100; // fiddle around for testing purposes
	//TIM4->EGR |= TIM_EGR_UG; // send an update even to reset timer and apply settings
	//TIM4->EGR |= (TIM_EGR_TG | TIM_EGR_UG);
	//TIM4->DIER |= 0x01; // UIE enable interrupt
	TIM3->CR1 |= TIM_CR1_CEN;
	puts("Timer setup");
}


void main() 
{
	init_serial();
	puts("11 pwm");
	char msg[40];

	setup_timer();
	//gpio_mode_out(BUILTIN_LED);

	//NVIC_ISER0 = (1<<30);
	//TIM4->DIER |= 1;
	puts("Interrupt set");

	//enable_irq();

	putchar('\a'); // beep

	int secs = 0;
	while(1) {
		itoa(secs++, msg, 10);
		//puts(msg);
		for(int i=0; i< 1000000; i++);
		//delay(1000);
	}

	//while(1);
}

#if 0
void SystemInit()
{
	// TODO
}

void __libc_init_array()
{
	// TODO

}
#endif