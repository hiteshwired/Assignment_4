/******************************************************************************
 * a4_gpio.h
 *
 * GPIO interface for CPE 316 Assignment 4.
 ******************************************************************************/

#ifndef A4_GPIO_H
#define A4_GPIO_H

#include "stm32l476xx.h"

void A4_GPIO_init(void);
void A4_GPIO_set_output(void);
void A4_GPIO_clear_output(void);

#endif