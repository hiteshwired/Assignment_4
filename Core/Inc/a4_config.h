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
 * TODO:
 * Verify this calculation manually for your report.
 */
#define A4_PERIOD_TICKS        \
    (A4_TIMER_CLOCK_HZ / A4_OUTPUT_FREQ_HZ)

/*
 * TIM2 counts from 0 through ARR, inclusive.
 *
 * TODO:
 * Complete this definition.
 */
#define A4_TIM2_ARR            (/* TODO */)

/*
 * Number of timer ticks corresponding to the high portion.
 */
#define A4_HIGH_TICKS          \
    ((A4_PERIOD_TICKS * A4_DUTY_PERCENT) / 100UL)

/*
 * Compare value used to generate the duty-cycle transition.
 *
 * TODO:
 * Determine the appropriate CCR1 value based on exactly when
 * your ISR drives the output HIGH and LOW.
 *
 * Pay special attention to the lab hint about counting zero.
 */
#define A4_TIM2_CCR1           (/* TODO */)


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