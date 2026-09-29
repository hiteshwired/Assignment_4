/******************************************************************************
 * a4_gpio.c
 *
 * CPE 316 - Assignment 4
 * Interrupts and Timers
 *
 * GPIO driver for the waveform output pin. Provides:
 *
 *   A4_GPIO_init()         - configure the output pin (push-pull output)
 *   A4_GPIO_set_output()   - drive the pin HIGH  (atomic, via BSRR)
 *   A4_GPIO_clear_output() - drive the pin LOW   (atomic, via BRR)
 *
 * The output pin is defined in a4_config.h (default PC0).
 ******************************************************************************/

#include "a4_gpio.h"
#include "a4_config.h"


/******************************************************************************
 * A4_GPIO_init
 *
 * Enables the output port clock and configures the output pin as a
 * push-pull, no-pull, high-speed general purpose output.
 ******************************************************************************/
void A4_GPIO_init(void)
{
    /*----------------------------------------------------------------
     * 1. Enable the output port peripheral clock (GPIOC on AHB2)
     *--------------------------------------------------------------*/
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    /*----------------------------------------------------------------
     * 2. MODER: select general purpose output mode (01)
     *
     * Clear both mode bits, then set bit 0 of the field.
     *--------------------------------------------------------------*/
    A4_OUTPUT_GPIO->MODER &= ~(3UL << (A4_OUTPUT_PIN * 2UL));
    A4_OUTPUT_GPIO->MODER |=  (1UL << (A4_OUTPUT_PIN * 2UL));

    /*----------------------------------------------------------------
     * 3. OTYPER: push-pull output (0)
     *--------------------------------------------------------------*/
    A4_OUTPUT_GPIO->OTYPER &= ~A4_OUTPUT_MASK;

    /*----------------------------------------------------------------
     * 4. PUPDR: no pull-up, no pull-down (00)
     *--------------------------------------------------------------*/
    A4_OUTPUT_GPIO->PUPDR &= ~(3UL << (A4_OUTPUT_PIN * 2UL));

    /*----------------------------------------------------------------
     * 5. OSPEEDR: high speed (11) so the 5 kHz edges are clean
     *--------------------------------------------------------------*/
    A4_OUTPUT_GPIO->OSPEEDR |= (3UL << (A4_OUTPUT_PIN * 2UL));

    /*----------------------------------------------------------------
     * 6. Start in a known state (LOW)
     *--------------------------------------------------------------*/
    A4_GPIO_clear_output();
}


/******************************************************************************
 * A4_GPIO_set_output
 *
 * Drives the output pin HIGH. Writing the lower half of BSRR sets the pin
 * atomically without a read-modify-write on ODR.
 ******************************************************************************/
void A4_GPIO_set_output(void)
{
    A4_OUTPUT_GPIO->BSRR = A4_OUTPUT_MASK;
}


/******************************************************************************
 * A4_GPIO_clear_output
 *
 * Drives the output pin LOW. Writing BRR clears the pin atomically.
 ******************************************************************************/
void A4_GPIO_clear_output(void)
{
    A4_OUTPUT_GPIO->BRR = A4_OUTPUT_MASK;
}
