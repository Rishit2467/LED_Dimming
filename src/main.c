#include "stm32f1xx.h"

void PWM_Init(void)
{
    // Enable GPIOA and TIM2 clocks
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Set PA0 as alternate function push-pull output
    GPIOA->CRL &= ~(0xF << 0);
    GPIOA->CRL |=  (0xB << 0);

    // TIM2 Channel 1 PWM configuration
    TIM2->PSC    = 72 - 1;         // 72MHz / 72 = 1MHz
    TIM2->ARR    = 1000 - 1;       // 1MHz / 1000 = 1kHz PWM
    TIM2->CCR1   = 0;              // Start at 0% duty cycle
    TIM2->CCMR1 &= ~(0x7 << 4);   // Clear OC1M bits
    TIM2->CCMR1 |=  (0x6 << 4);   // PWM mode 1
    TIM2->CCMR1 |=  TIM_CCMR1_OC1PE;  // Preload enable
    TIM2->CCER  |=  TIM_CCER_CC1E;    // Enable channel 1 output
    TIM2->CR1   |=  TIM_CR1_ARPE;     // Auto reload preload
    TIM2->EGR   |=  TIM_EGR_UG;       // Force update event
    TIM2->CR1   |=  TIM_CR1_CEN;      // Start timer
}

void delay(volatile uint32_t count)
{
    while(count--);
}

int main(void)
{
    PWM_Init();

    while (1)
    {
        // Fade IN
        for (int i = 0; i <= 999; i++)
        {
            TIM2->CCR1 = i;
            delay(2000);
        }

        // Fade OUT
        for (int i = 999; i >= 0; i--)
        {
            TIM2->CCR1 = i;
            delay(2000);
        }
    }
}