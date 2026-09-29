/******************************************************************************
 * a4_config.h
 *
 * Configuration constants for CPE 316 Assignment 4.
 *
 * Assignment:
 *   Generate a 5 kHz, 25% duty-cycle square wave using TIM2 interrupts.
 ******************************************************************************/

#ifndef A4_CONFIG_H
#define A4_CONFIG_H

#include "stm32l476xx.h"
#include <stdint.h>

/*===========================================================================
 * Timer configuration
 *===========================================================================*/

/* A4 specifies a 4 MHz timer input clock. */
#define A4_TIMER_CLOCK_HZ      (4000000UL)

/* Required output waveform. */
#define A4_OUTPUT_FREQ_HZ      (5000UL)
#define A4_DUTY_PERCENT        (25UL)

/*
 * Number of TIM2 counter ticks in one output period.
 *
 * f_out = f_TIM / A4_PERIOD_TICKS
 *   -> A4_PERIOD_TICKS = 4 MHz / 5 kHz = 800 ticks
 *
 * 5 kHz period  = 200 us  (800 ticks @ 250 ns/tick)
 * 25% high time =  50 us  (200 ticks)
 * 75% low time  = 150 us  (600 ticks)
 */
#define A4_PERIOD_TICKS        \
    (A4_TIMER_CLOCK_HZ / A4_OUTPUT_FREQ_HZ)

/*
 * TIM2 counts 0, 1, ... ARR, then wraps (an update event) back to 0.
 * That is (ARR + 1) counts per period, so subtract 1 to include count 0.
 *
 *   ARR = A4_PERIOD_TICKS - 1 = 800 - 1 = 799
 */
#define A4_TIM2_ARR            (A4_PERIOD_TICKS - 1UL)

/*
 * Number of timer ticks corresponding to the high portion.
 *
 *   A4_HIGH_TICKS = (800 * 25) / 100 = 200 ticks
 */
#define A4_HIGH_TICKS          \
    ((A4_PERIOD_TICKS * A4_DUTY_PERCENT) / 100UL)

/*
 * Compare value used to generate the duty-cycle transition.
 *
 * The ISR drives the pin HIGH on the update event (count 0, start of
 * period) and LOW on the CCR1 compare event. Counting count 0 as the
 * first HIGH tick, the pin stays HIGH for counts 0 .. (A4_HIGH_TICKS - 1)
 * and the CC1IF that fires at CNT == A4_HIGH_TICKS ends the HIGH portion.
 *
 *   CCR1 = A4_HIGH_TICKS = 200  ->  HIGH for 200 ticks, LOW for 600 ticks
 */
#define A4_TIM2_CCR1           (A4_HIGH_TICKS)


/*===========================================================================
 * Output GPIO
 *===========================================================================*/

/*
 * PC0 is used here simply as a convenient GPIO output.
 *
 * Change these definitions if you choose another pin.
 */
#define A4_OUTPUT_GPIO         GPIOC
#define A4_OUTPUT_PIN          (0UL)
#define A4_OUTPUT_MASK         (1UL << A4_OUTPUT_PIN)

#endif