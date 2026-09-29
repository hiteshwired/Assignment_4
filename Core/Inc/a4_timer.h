/******************************************************************************
 * a4_timer.h
 *
 * TIM2 interface for CPE 316 Assignment 4.
 ******************************************************************************/

#ifndef A4_TIMER_H
#define A4_TIMER_H

#include "stm32l476xx.h"

void A4_TIM2_init(void);
void A4_TIM2_start(void);
void A4_TIM2_stop(void);

#endif