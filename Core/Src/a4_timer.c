/*
 * a4_timer.c
 *
 * CPE 316 - Assignment 4, Part A
 * Sets up TIM2 to make a 5 kHz, 25% duty cycle square wave.
 *
 * TIM2 sends two interrupts each period:
 *   update event (count rolls over) -> set the pin high
 *   CCR1 compare match              -> set the pin low
 *
 * Functions:
 *   TIM2_init()       - configure the timer and its interrupts
 *   TIM2_start()      - start counting
 *   TIM2_stop()       - stop counting
 *   TIM2_IRQHandler() - toggles the pin and clears the flags
 */

#include "a4_timer.h"
#include "a4_gpio.h"
#include "a4_config.h"

void TIM2_init(void)
{
    // turn on the TIM2 clock (APB1)
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    // make sure the timer is off while we set it up
    TIM2->CR1 &= ~TIM_CR1_CEN;

    // up-counting, edge-aligned
    TIM2->CR1 &= ~TIM_CR1_DIR;
    TIM2->CR1 &= ~TIM_CR1_CMS;

    // PSC = 0 so the counter runs at the full 4 MHz clock
    TIM2->PSC = 0U;

    // ARR sets the period, CCR1 sets the 25% high time
    TIM2->ARR  = TIM2_ARR_VAL;
    TIM2->CCR1 = TIM2_CCR1_VAL;

    // enable the update and CCR1 compare interrupts
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->DIER |= TIM_DIER_CC1IE;

    // UG loads PSC/ARR right away, but it also sets UIF
    TIM2->EGR |= TIM_EGR_UG;

    // clear any flags left over from the UG event
    TIM2->SR &= ~TIM_SR_UIF;
    TIM2->SR &= ~TIM_SR_CC1IF;

    // enable TIM2 in the NVIC, then enable interrupts globally
    NVIC->ISER[TIM2_IRQn >> 5] = (1UL << (TIM2_IRQn & 0x1FU));
    __enable_irq();
}

void TIM2_start(void)
{
    TIM2->CNT = 0U;        // start from a known count

    // The first update event is a full period away, so set the pin
    // high now so the very first period starts high.
    GPIO_set_output();

    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_stop(void)
{
    TIM2->CR1 &= ~TIM_CR1_CEN;
}

// check the source, flip the pin, clear the flag.
void TIM2_IRQHandler(void)
{
    // update event -> start of a new period, go high
    if ((TIM2->SR & TIM_SR_UIF) != 0U)
    {
        GPIO_set_output();
        TIM2->SR &= ~TIM_SR_UIF;
    }

    // CCR1 match -> end of the high time, go low
    if ((TIM2->SR & TIM_SR_CC1IF) != 0U)
    {
        GPIO_clear_output();
        TIM2->SR &= ~TIM_SR_CC1IF;
    }
}
