/*
 * a4_config.h
 *
 * CPE 316 - Assignment 4, Part A
 * Constants for the 5 kHz, 25% duty cycle square wave on TIM2.
 *
 * Timing math (4 MHz timer clock, 250 ns per tick):
 *   period = 4 MHz / 5 kHz = 800 ticks = 200 us
 *   high   = 25% of 800    = 200 ticks =  50 us
 *   low    = 75% of 800    = 600 ticks = 150 us
 */

#ifndef A4_CONFIG_H
#define A4_CONFIG_H

#include "stm32l476xx.h"
#include <stdint.h>

// TIM2 input clock and the wave we want to make
#define TIMER_CLOCK_HZ   (4000000UL)   // 4 MHz timer clock
#define OUTPUT_FREQ_HZ   (5000UL)      // 5 kHz output
#define DUTY_PERCENT     (25UL)        // 25% duty cycle

// ticks in one full period: 4 MHz / 5 kHz = 800
#define PERIOD_TICKS     (TIMER_CLOCK_HZ / OUTPUT_FREQ_HZ)

/*
 * The counter runs 0, 1, ... ARR and then rolls over, so that is
 * (ARR + 1) counts per period. Subtract 1 so count 0 is included.
 * ARR = 800 - 1 = 799
 */
#define TIM2_ARR_VAL     (PERIOD_TICKS - 1UL)

// ticks the pin stays high: 800 * 25 / 100 = 200
#define HIGH_TICKS       ((PERIOD_TICKS * DUTY_PERCENT) / 100UL)

/*
 * The pin is set high at the update event (count 0) and cleared at the
 * CCR1 compare match. Matching at count 200 gives 200 high ticks
 * (counts 0..199), which is the 25% high time.
 * CCR1 = 200
 */
#define TIM2_CCR1_VAL    (HIGH_TICKS)

// Output pin - using PC0 as a free GPIO output
#define OUTPUT_PORT      GPIOC
#define OUTPUT_PIN       (0UL)
#define OUTPUT_MASK      (1UL << OUTPUT_PIN)

#endif
