# STM32 Interrupts & Timers: Square-Wave Generator

A bare-metal embedded C exercise for the STM32L476RG (Nucleo-64) that generates a
5&nbsp;kHz, 25% duty-cycle square wave entirely from a TIM2 timer interrupt &mdash; no
software delay loops. `main()` only configures the hardware; all timing lives in
the ISR.

## What it does

- `a4_timer.c/.h`: configures TIM2's period, compare value, and interrupt, and
  toggles the output in the ISR to produce the waveform.
- `a4_gpio.c/.h`: sets up the output pin at the register level.
- `main.c`: brings up GPIO and the timer, then idles while the ISR does the work.

## Hardware

- STM32L476RG (Nucleo-64)

## Build

Generated from STM32CubeMX with a CMake build. Build with the included CMake
presets and an `arm-none-eabi` toolchain, or open in STM32CubeIDE, then flash.

---

## Academic honesty & licensing

Coursework from an embedded systems course at Cal Poly, San Luis Obispo. The
`a4_timer`, `a4_gpio`, and `main.c` code is my own work. The project also bundles
STMicroelectronics' STM32L4xx HAL/CMSIS drivers and CubeMX-generated files, which
are under ST's own license terms and are **not** mine to relicense.

Shared as a learning reference only. It is intentionally not released under an
open-source license, and you should not submit it as your own work for a graded
assignment.
