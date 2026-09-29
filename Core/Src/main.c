/******************************************************************************
 * main.c
 *
 * CPE 316 - Assignment 4
 * Interrupts and Timers
 *
 * Part A: Generate a 5 kHz, 25% duty-cycle square wave using TIM2.
 *
 * Waveform timing (4 MHz timer clock, 250 ns/tick):
 *   Period  = 200 us = 800 ticks  (ARR = 799, counting count 0)
 *   High    =  50 us = 200 ticks  (CCR1 = 200, 25% duty)
 *   Low     = 150 us = 600 ticks
 *
 * TIM2 raises two interrupts per period:
 *   Update event (period boundary) -> ISR drives the output HIGH
 *   CCR1 compare event             -> ISR drives the output LOW
 *
 * main() only sets up the hardware. All waveform timing is done by TIM2
 * and TIM2_IRQHandler() - no software delays and no polling of CNT.
 *
 * Clock note:
 *   The board runs on its reset-default clock (MSI @ 4 MHz = SYSCLK,
 *   APB1 prescaler = 1), so TIM2 is clocked at the 4 MHz required by the
 *   assignment. SystemClock_Config()/HAL_Init() are intentionally not
 *   called so the 4 MHz reset clock is left in place.
 ******************************************************************************/

#include "stm32l476xx.h"
#include "a4_gpio.h"
#include "a4_timer.h"

int main(void)
{
    A4_GPIO_init();     /* configure the waveform output pin */
    A4_TIM2_init();     /* configure TIM2 period, compare, and interrupts */
    A4_TIM2_start();    /* start the counter; ISR now drives the waveform */

    while (1)
    {
        /*
         * Intentionally empty. TIM2 hardware and TIM2_IRQHandler()
         * generate the waveform.
         *
         * DO NOT:
         *   - increment counters here
         *   - use software delays here
         *   - poll CNT to determine waveform timing
         */
    }
}
