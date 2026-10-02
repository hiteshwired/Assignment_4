/*
 * a4_gpio.c
 *
 * CPE 316 - Assignment 4
 * Driver for the pin that the TIM2 ISR toggles to make the wave.
 *
 * Functions:
 *   GPIO_init()          - set the pin as a push-pull output
 *   GPIO_set_output()    - drive the pin high using BSRR
 *   GPIO_clear_output()  - drive the pin low using BRR
 *
 * The pin itself is picked in a4_config.h (PC0 by default).
 */

#include "a4_gpio.h"
#include "a4_config.h"

// Set up the output pin: push-pull, no pull resistors, high speed.
void GPIO_init(void)
{
    // turn on the GPIOC clock (it lives on the AHB2 bus)
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // MODER = 01 for general purpose output
    OUTPUT_PORT->MODER &= ~(3UL << (OUTPUT_PIN * 2UL));
    OUTPUT_PORT->MODER |=  (1UL << (OUTPUT_PIN * 2UL));

    // OTYPER = 0 for push-pull
    OUTPUT_PORT->OTYPER &= ~OUTPUT_MASK;

    // PUPDR = 00 for no pull-up / pull-down
    OUTPUT_PORT->PUPDR &= ~(3UL << (OUTPUT_PIN * 2UL));

    // OSPEEDR = 11 for high speed so the edges stay sharp
    OUTPUT_PORT->OSPEEDR |= (3UL << (OUTPUT_PIN * 2UL));

    // start low so we have a known state
    GPIO_clear_output();
}

// Drive the pin high. BSRR sets the bit without a read-modify-write.
void GPIO_set_output(void)
{
    OUTPUT_PORT->BSRR = OUTPUT_MASK;
}

// Drive the pin low. BRR clears the bit the same atomic way.
void GPIO_clear_output(void)
{
    OUTPUT_PORT->BRR = OUTPUT_MASK;
}
