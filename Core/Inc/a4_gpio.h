/*
 * a4_gpio.h
 *
 * CPE 316 - Assignment 4
 * Declarations for the waveform output pin functions in a4_gpio.c.
 */

#ifndef A4_GPIO_H
#define A4_GPIO_H

#include "stm32l476xx.h"

void GPIO_init(void);          // set up the output pin
void GPIO_set_output(void);    // drive the pin high
void GPIO_clear_output(void);  // drive the pin low

#endif
