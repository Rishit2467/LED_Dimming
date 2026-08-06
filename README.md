# STM32 PWM LED Dimming — Bare Metal

PWM LED dimming on STM32 Nucleo F103RB using bare-metal C.
No HAL, no libraries — direct hardware register access only.

## Hardware Required

- STM32 Nucleo F103RB
- LED
- 220Ω resistor
- Breadboard
- Jumper wires

## Wiring

| STM32 Pin | Component |
|-----------|-----------|
| PA0 (A0)  | Resistor → LED anode (+) |
| GND       | LED cathode (–) |

## How It Works

PWM (Pulse Width Modulation) switches the pin ON and OFF
at 1kHz — faster than the human eye can detect. The duty
cycle controls how long the pin stays HIGH each cycle,
which controls perceived brightness.

The code continuously increases then decreases the duty
cycle from 0% to 100%, creating a smooth fade in and out.

## Register Configuration

| Register | Value | Purpose |
|----------|-------|---------|
| RCC APB2ENR | IOPAEN | Enable GPIOA clock |
| RCC APB1ENR | TIM2EN | Enable TIM2 clock |
| GPIOA CRL | 0xB | PA0 alternate function push-pull |
| TIM2 PSC | 71 | Divide 72MHz to 1MHz |
| TIM2 ARR | 999 | Set PWM frequency to 1kHz |
| TIM2 CCR1 | 0-999 | Control duty cycle 0-100% |

## PWM Frequency Calculation
