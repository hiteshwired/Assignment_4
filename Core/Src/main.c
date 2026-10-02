/*
 * main.c
 *
 * CPE 316 - Assignment 4, Part A
 * Interrupts and Timers
 *
 * Makes a 5 kHz, 25% duty cycle square wave using TIM2 interrupts.
 * main() only sets up the hardware - all the timing is handled by
 * TIM2 and its ISR, so there are no software delays here.
 */

#include "stm32l476xx.h"
#include "a4_gpio.h"
#include "a4_timer.h"

int main(void)
{
    GPIO_init();     // set up the output pin
    TIM2_init();     // set up the timer period, compare, and interrupts
    TIM2_start();    // start the wave

    while (1)
    {
        
    }
}
