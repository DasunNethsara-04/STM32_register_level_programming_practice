# STM32 Register-Level Programming Practice

A hands-on collection of embedded C projects written at the **bare-metal / register level** for the **STM32F411** microcontroller (Black Pill). Each project is a standalone exercise that progressively builds knowledge of the STM32 peripheral registers — from simple GPIO blinking all the way to PWM-driven servo control — without relying on HAL abstraction layers for the core logic.

---

## 🛠️ Tech Stack

| Layer | Technology |
|---|---|
| **Microcontroller** | STM32F411CEUx (Black Pill) — ARM Cortex-M4 @ 100 MHz |
| **Language** | C (C99/C11) |
| **Programming Style** | Register-level (direct peripheral register manipulation) |
| **Firmware Library** | STM32F4xx CMSIS + STM32 HAL (used only for `HAL_Init()` / `HAL_Delay()` in early projects) |
| **Build System** | CMake (projects 001–012) / STM32CubeIDE Makefile (projects 013–020) |
| **IDE / Tooling** | STM32CubeIDE, VS Code with clangd |
| **Cube MX Config** | `.ioc` files included in each project |
| **Linker Script** | `STM32F411xx_FLASH.ld` / `STM32F411CEUX_FLASH.ld` |
| **Startup File** | `startup_stm32f411xe.s` |

---

## 📁 Project Overview

> All projects target **GPIOA**, **GPIOB**, or **GPIOC** pins on the STM32F411 Black Pill.  
> Pins are configured directly through the `MODER`, `OTYPER`, `OSPEEDR`, `PUPDR`, `ODR`, `IDR`, and `BSRR` registers.

---

### 001 — Blink

**Description:** The classic "Hello, World!" of embedded programming. Configures a single GPIO output pin and toggles it every 500 ms using `HAL_Delay()`.

| Role | Pin |
|---|---|
| LED (output) | **PC13** (on-board LED) |

**Key Registers:** `RCC->AHB1ENR`, `GPIOC->MODER`, `GPIOC->OTYPER`, `GPIOC->OSPEEDR`, `GPIOC->PUPDR`, `GPIOC->ODR`

---

### 002 — Blink 2 LEDs

**Description:** Extends the blink exercise to two external LEDs. The LEDs alternate — one turns ON for 500 ms, then the other turns ON for 500 ms, creating a chase effect.

| Role | Pin |
|---|---|
| LED 1 (output) | **PB3** |
| LED 2 (output) | **PB4** |

**Key Registers:** `RCC->AHB1ENR`, `GPIOB->MODER`, `GPIOB->OTYPER`, `GPIOB->OSPEEDR`, `GPIOB->PUPDR`, `GPIOB->ODR`

---

### 003 — Push Button

**Description:** Reads a push button connected to an input pin. While the button is held down, an LED turns ON; releasing it turns the LED OFF. Uses an external pull-down resistor on the button.

| Role | Pin |
|---|---|
| Button (input) | **PB5** |
| LED (output) | **PB4** |

**Key Registers:** `GPIOB->MODER`, `GPIOB->PUPDR`, `GPIOB->IDR`, `GPIOB->ODR`

---

### 004 — Two Push Buttons

**Description:** Independently controls two LEDs with two separate push buttons. Button 1 drives LED 1 and Button 2 drives LED 2, each operating on different GPIO ports.

| Role | Pin |
|---|---|
| Button 1 (input) | **PA4** |
| Button 2 (input) | **PA5** |
| LED 1 (output) | **PB4** |
| LED 2 (output) | **PB5** |

**Key Registers:** `RCC->AHB1ENR` (GPIOA + GPIOB), `GPIOA->MODER`, `GPIOB->MODER`, `GPIOA->IDR`, `GPIOB->ODR`

---

### 005 — Push Button State (Toggle)

**Description:** Introduces **state-aware input reading**. Instead of controlling the LED while the button is held, each press **toggles** the LED state. Includes a basic 50 ms software debounce.

| Role | Pin |
|---|---|
| Button (input) | **PA4** |
| LED (output) | **PB4** |

**Key Concepts:** Rising-edge detection via `previousState` / `currentState` comparison, software debounce with `HAL_Delay(50)`

---

### 006 — 2 Push Button State (Toggle)

**Description:** Extends project 005 to two independent buttons, each toggling its own LED with debounce. Both buttons are tracked simultaneously using separate state variables.

| Role | Pin |
|---|---|
| Button 1 (input) | **PA4** |
| Button 2 (input) | **PA5** |
| LED 1 (output) | **PB4** |
| LED 2 (output) | **PB5** |

**Key Concepts:** Dual independent rising-edge detection with debounce

---

### 007 — Rising & Falling Edge Detection

**Description:** Demonstrates detecting both edges on two separate buttons. Button 1 uses **rising-edge** (press) detection to toggle LED 1; Button 2 uses **falling-edge** (release) detection to toggle LED 2.

| Role | Pin |
|---|---|
| Button 1 (input, rising edge) | **PA4** |
| Button 2 (input, falling edge) | **PA5** |
| LED 1 (output) | **PB4** |
| LED 2 (output) | **PB5** |

**Key Concepts:** Rising edge — `current==1 && previous==0`; Falling edge — `previous==1 && current==0`

---

### 008 — Work With BSRR

**Description:** Demonstrates the **Bit Set/Reset Register (BSRR)** for atomic GPIO writes. Two LEDs alternate using `BSRR` instead of read-modify-write on `ODR`, which is safer in interrupt-driven environments.

| Role | Pin |
|---|---|
| LED 1 (output) | **PB4** |
| LED 2 (output) | **PB5** |

**Key Registers:** `GPIOB->BSRR` — uses `GPIO_BSRR_BS4` / `GPIO_BSRR_BR4` for atomic set and reset

---

### 009 — Interrupts 1 (EXTI on PA4)

**Description:** First introduction to **External Interrupts (EXTI)**. A button on PA4 triggers the `EXTI4_IRQHandler`, which toggles an LED — the main loop is completely empty, demonstrating interrupt-driven design.

| Role | Pin |
|---|---|
| Button (input, EXTI4 rising edge) | **PA4** |
| LED (output) | **PB4** |

**Key Registers/Concepts:** `SYSCFG->EXTICR`, `EXTI->RTSR`, `EXTI->IMR`, `EXTI->PR`, `NVIC_EnableIRQ(EXTI4_IRQn)`

---

### 010 — Working With Microphone Module 1

**Description:** Interfaces a **digital microphone/sound detection module** (with digital output). When the module detects a sound pulse (rising edge on its digital output), the LED toggles — implementing a clap-activated light.

| Role | Pin |
|---|---|
| Microphone module DO (input) | **PA4** |
| LED (output) | **PB5** |

**Key Concepts:** Rising-edge detection via polling on the microphone digital output; state tracking to avoid re-triggering

---

### 011 — Interrupts 2 (EXTI on PA5)

**Description:** Second interrupt exercise, this time using pin **PA5** which shares the `EXTI9_5_IRQHandler` (shared for lines 5–9). Demonstrates how to handle the shared IRQ and toggle an LED on button press.

| Role | Pin |
|---|---|
| Button (input, EXTI5 rising edge) | **PA5** |
| LED (output) | **PB5** |

**Key Registers/Concepts:** `EXTI9_5_IRQHandler`, `SYSCFG->EXTICR[1]`, `EXTI->PR` (check and clear PR5), `NVIC_EnableIRQ(EXTI9_5_IRQn)`

---

### 012 — Counter With Interrupts

**Description:** A binary counter displayed on **4 LEDs**. Each button press (interrupt-driven) increments a `volatile` counter variable (0–15). The main loop reads the counter and lights the LEDs to represent its binary value (LSB = PB3).

| Role | Pin |
|---|---|
| Button (input, EXTI5 rising edge) | **PA5** |
| LED bit 0 / LSB (output) | **PB3** |
| LED bit 1 (output) | **PB4** |
| LED bit 2 (output) | **PB5** |
| LED bit 3 / MSB (output) | **PB6** |

**Key Concepts:** `volatile` shared variable between ISR and main loop, binary representation across 4 LEDs, counter wrap-around at 15

---

### 013 — Button Debounce (LCD Parallel Data Driver)

> **Note:** Despite the folder name `button-debounce`, this project is an **8-bit parallel LCD data driver**. It outputs a character (`'W'`) to an LCD's 8 data lines using a custom `LCDFunctions` abstraction layer.

| Role | Pin |
|---|---|
| LCD Data Bit 0 (output) | **PA1** |
| LCD Data Bit 1 (output) | **PA2** |
| LCD Data Bit 2 (output) | **PA3** |
| LCD Data Bit 3 (output) | **PA4** |
| LCD Data Bit 4 (output) | **PA5** |
| LCD Data Bit 5 (output) | **PA6** |
| LCD Data Bit 6 (output) | **PA7** |
| LCD Data Bit 7 (output) | **PA8** |

**Key Concepts:** Bitwise decomposition of a character across 8 output pins; reusable `SetupPinsAndPortsForOutput()` and `SendBitToThePin()` helpers; GPIO high-speed push-pull output

---

### 014 — Timers 1 (Basic TIM2 Counter Read)

**Description:** First timer project. Configures **TIM2** with a prescaler to tick at 1 kHz and an auto-reload value of 999, making the counter roll over every 1 second. The current counter value is read into a `volatile` variable for live debugging via a watch window.

| Role | Component |
|---|---|
| Timer | **TIM2** |
| Prescaler | 16 000 → 1 kHz tick |
| Auto-Reload | 1000 (1-second period) |

**Key Registers:** `RCC->APB1ENR`, `TIM2->PSC`, `TIM2->ARR`, `TIM2->CR1`, `TIM2->CNT`

---

### 015 — Timers 2 (Timer Interrupt → LED Blink)

**Description:** Uses TIM2's **update interrupt** (UIF) to toggle an LED at a precise interval. The `TIM2_IRQHandler` fires on every counter overflow, toggling the LED without any polling in the main loop.

| Role | Pin / Component |
|---|---|
| LED (output) | **PA3** |
| Timer | **TIM2** (PSC=15999, ARR=999 → 1 s period) |

**Key Registers:** `TIM2->DIER` (UIE bit), `TIM2->SR` (UIF clear), `NVIC_EnableIRQ(TIM2_IRQn)`

---

### 016 — Timers 3 (Multi-Rate LED Blink — 1 Timer, 3 LEDs)

**Description:** Demonstrates **software timer multiplexing**: a single TIM2 interrupt fires every 10 ms (base tick) and three separate software counters within the ISR control three LEDs at different rates — 250 ms, 500 ms, and 1000 ms.

| Role | Pin |
|---|---|
| LED 1 — 250 ms toggle (output) | **PA1** |
| LED 2 — 500 ms toggle (output) | **PA2** |
| LED 3 — 1000 ms toggle (output) | **PA3** |
| Timer | **TIM2** (10 ms base tick) |

**Key Concepts:** Software counter multiplexing inside `TIM2_IRQHandler`, single hardware timer driving multiple independent timing channels

---

### 017 — Timers 4 (Multi-Rate LED Blink — 1 Timer, 4 LEDs)

**Description:** Extends project 016 to **four LEDs**, each blinking at a different rate — 250 ms, 500 ms, 750 ms, and 1000 ms — all driven from a single TIM2 interrupt with four independent software counters.

| Role | Pin |
|---|---|
| LED 1 — 250 ms toggle (output) | **PA1** |
| LED 2 — 500 ms toggle (output) | **PA2** |
| LED 3 — 750 ms toggle (output) | **PA3** |
| LED 4 — 1000 ms toggle (output) | **PA4** |
| Timer | **TIM2** (10 ms base tick) |

---

### 018 — Timers 5 (Button-Triggered Timer / Auto-Off LED)

**Description:** Combines a **button interrupt** and a **timer interrupt**. Pressing the button (via EXTI on PA5) immediately turns ON an LED and starts TIM2. After exactly 3 seconds, the timer ISR turns OFF the LED and stops the timer — a one-shot timed event.

| Role | Pin / Component |
|---|---|
| Button (input, EXTI5 rising edge) | **PA5** |
| LED (output, auto-off after 3 s) | **PA3** |
| Timer | **TIM2** (10 ms tick x 300 counts = 3 s) |

**Key Concepts:** EXTI starts the timer; TIM2 ISR stops itself after a count threshold; uses `GPIOA->BSRR` for atomic LED control

---

### 019 — Timers 6 (Software Clock — HH:MM:SS)

**Description:** Implements a simple **software clock** using TIM2. The timer fires every 1 second (PSC=15999, ARR=999). The ISR increments a `seconds` variable, rolling it into `minutes` at 60 and `minutes` into `hours` at 60 — all tracked in `volatile` globals readable via a debugger.

| Role | Component |
|---|---|
| Timer | **TIM2** (1-second period) |
| Time Variables | `volatile hours`, `volatile minutes`, `volatile seconds` |

**Key Concepts:** Cascaded rollover logic inside ISR, timer-based software timekeeping with no display hardware

---

### 020 — Timers PWM 1 (Servo Motor Control)

**Description:** First PWM project. Configures TIM2 Channel 1 in **PWM Mode 1** and outputs a 50 Hz PWM signal on **PA5** (TIM2_CH1, AF1). The duty cycle cycles through four preset positions (500 µs, 1000 µs, 1500 µs, 2000 µs) every 500 ms, sweeping a servo motor through its full range.

| Role | Pin / Component |
|---|---|
| PWM Output (Servo signal) | **PA5** (TIM2_CH1, Alternate Function 1) |
| Timer | **TIM2** (PSC=15, ARR=19999 → 50 Hz / 20 ms period) |
| Servo Positions (CCR1) | 500, 1000, 1500, 2000 (µs pulse width) |

**Key Registers:** `GPIOA->AFR[0]`, `TIM2->CCMR1` (PWM Mode 1 = 0x6), `TIM2->CCR1`, `TIM2->CCER`

---

## 🗂️ Project Directory Structure

```
NNN-project-name/
├── Core/
│   ├── Inc/              # Header files (main.h, etc.)
│   └── Src/
│       ├── main.c        # Application logic (register-level code)
│       ├── stm32f4xx_it.c
│       └── ...           # HAL MSP, syscalls, sysmem
├── Drivers/              # CMSIS + STM32F4xx HAL drivers
├── NNN-project.ioc       # STM32CubeMX project config
├── CMakeLists.txt        # Build definition (early projects)
├── STM32F411xx_FLASH.ld  # Linker script
└── startup_stm32f411xe.s # Startup assembly file
```

---

## 🚀 Building & Flashing

### CMake Projects (001–012)
```bash
cmake -B build -G Ninja
cmake --build build
# Flash with ST-Link via OpenOCD
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
  -c "program build/<project>.elf verify reset exit"
```

### STM32CubeIDE Projects (013–020)
Open the project folder directly in **STM32CubeIDE** and use  
**Run → Debug As → STM32 Cortex-M C/C++ Application**.

---

## 📈 Learning Progression

```
GPIO Basics               Interrupts (EXTI)       Timers (TIM2)            PWM / Peripherals
─────────────────         ─────────────────       ─────────────────        ─────────────────
001  Blink                009  EXTI on PA4        014  TIM2 CNT Read       020  Servo PWM
002  Blink 2 LEDs         011  EXTI on PA5        015  Timer IRQ Blink
003  Push Button          012  Binary Counter      016  3 LEDs, 1 Timer
004  Two Buttons                                   017  4 LEDs, 1 Timer
005  State Toggle         Sensors / Drivers        018  Button + Timer
006  Dual Toggle          010  Microphone Module   019  Software Clock
007  Edge Detection       013  LCD Parallel Bus
008  BSRR Register
```

---

## 📋 Notes

- All projects use **direct register access** — no HAL GPIO wrappers in the core logic (`HAL_Init()` and `HAL_Delay()` used only where noted).
- External pull-down resistors are used on button inputs; internal pull-ups/pull-downs are disabled in software.
- The **STM32F411 Black Pill** on-board LED is active-low on **PC13**.
- Timer base clock is the default **16 MHz HSI** internal oscillator (no external crystal configured in these projects).
