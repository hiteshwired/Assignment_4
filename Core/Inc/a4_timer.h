/*
 * a4_timer.h
 *
 * CPE 316 - Assignment 4
 * Declarations for the TIM2 setup functions in a4_timer.c.
 */

#ifndef A4_TIMER_H
#define A4_TIMER_H

#include "stm32l476xx.h"

void TIM2_init(void);   // configure period, compare, and interrupts
void TIM2_start(void);  // start the counter
void TIM2_stop(void);   // stop the counter

#endif
