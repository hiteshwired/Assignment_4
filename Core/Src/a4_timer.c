/******************************************************************************
 * a4_timer.c
 *
 * Configures TIM2 to generate the timing events needed for a
 * 5 kHz, 25% duty-cycle GPIO waveform.
 *
 * Two TIM2 events are used:
 *
 *   Update event:
 *       Marks the beginning of a new waveform period.
 *
 *   Channel 1 compare event:
 *       Marks the duty-cycle transition within the period.
 ******************************************************************************/

#include "a4_timer.h"
#include "a4_gpio.h"
#include "a4_config.h"


void A4_TIM2_init(void)
{
    /*--------------------------------------------------------------
     * 1. Enable TIM2 peripheral clock
     *------------------------------------------------------------*/

    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;


    /*--------------------------------------------------------------
     * 2. Stop timer while configuring it
     *------------------------------------------------------------*/

    TIM2->CR1 &= ~TIM_CR1_CEN;


    /*--------------------------------------------------------------
     * 3. Configure TIM2 as an up-counter
     *
     * DIR = 0 : up-counting
     * CMS = 00: edge-aligned counting
     *------------------------------------------------------------*/

    TIM2->CR1 &= ~TIM_CR1_DIR;
    TIM2->CR1 &= ~TIM_CR1_CMS;


    /*--------------------------------------------------------------
     * 4. Configure prescaler
     *
     * The assignment says TIM2 receives a 4 MHz clock.
     *
     * We want the counter itself to run at that rate, so determine
     * what PSC must contain.
     *
     * Timer counter clock:
     *
     *      f_CNT = f_TIM / (PSC + 1)
     *------------------------------------------------------------*/

    TIM2->PSC = /* TODO */;


    /*--------------------------------------------------------------
     * 5. Configure period
     *------------------------------------------------------------*/

    TIM2->ARR = A4_TIM2_ARR;


    /*--------------------------------------------------------------
     * 6. Configure channel 1 compare event
     *
     * When CNT reaches CCR1, CC1IF will be asserted.
     *------------------------------------------------------------*/

    TIM2->CCR1 = A4_TIM2_CCR1;


    /*--------------------------------------------------------------
     * 7. Enable TIM2 interrupt sources
     *
     * We need:
     *
     * UIE   -> interrupt when one period completes
     * CC1IE -> interrupt when CNT reaches CCR1
     *------------------------------------------------------------*/

    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->DIER |= TIM_DIER_CC1IE;


    /*--------------------------------------------------------------
     * 8. Force register update
     *
     * UG transfers prescaler / reload configuration into use.
     *
     * NOTE:
     * Generating UG can also cause UIF to become set, so we must
     * clear pending timer flags before enabling the NVIC interrupt.
     *------------------------------------------------------------*/

    TIM2->EGR |= TIM_EGR_UG;


    /*--------------------------------------------------------------
     * 9. Clear stale interrupt flags
     *------------------------------------------------------------*/

    TIM2->SR &= ~TIM_SR_UIF;
    TIM2->SR &= ~TIM_SR_CC1IF;


    /*--------------------------------------------------------------
     * 10. Enable TIM2 interrupt in the NVIC
     *
     * TIM2_IRQn identifies TIM2's Cortex-M4 interrupt number.
     *
     * Complete the appropriate NVIC enable operation.
     *------------------------------------------------------------*/

    NVIC->ISER[TIM2_IRQn >> 5] =
        (1UL << (TIM2_IRQn & 0x1FU));


    /* Global Cortex-M4 interrupts. */
    __enable_irq();
}


void A4_TIM2_start(void)
{
    /*
     * Starting from a known counter value makes the initial
     * waveform behavior deterministic.
     */
    TIM2->CNT = 0U;

    /* TODO:
     * Decide whether the GPIO should initially be HIGH or LOW,
     * based on how you designed the ISR below.
     */

    TIM2->CR1 |= TIM_CR1_CEN;
}


void A4_TIM2_stop(void)
{
    TIM2->CR1 &= ~TIM_CR1_CEN;
}


/******************************************************************************
 * TIM2_IRQHandler
 *
 * TIM2 interrupt service routine.
 *
 * Keep this ISR SHORT:
 *   1. Determine interrupt source.
 *   2. Update output pin.
 *   3. Clear the corresponding interrupt flag.
 ******************************************************************************/

void TIM2_IRQHandler(void)
{
    /*
     * Period boundary.
     */
    if ((TIM2->SR & TIM_SR_UIF) != 0U)
    {
        /*
         * TODO:
         * Should the output become HIGH or LOW here?
         *
         * Draw the waveform before answering.
         */

        /* A4_GPIO_???(); */

        TIM2->SR &= ~TIM_SR_UIF;
    }


    /*
     * CCR1 compare event.
     */
    if ((TIM2->SR & TIM_SR_CC1IF) != 0U)
    {
        /*
         * TODO:
         * Perform the opposite GPIO transition here.
         */

        /* A4_GPIO_???(); */

        TIM2->SR &= ~TIM_SR_CC1IF;
    }
}