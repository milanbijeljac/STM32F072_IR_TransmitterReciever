# STM32F072_IR_TransmitterReciever

Bare-metal firmware for an **STM32F072RBT6 (Nucleo-F072RB)** that turns an air conditioner ON/OFF
based on a measured room temperature, by replaying the AC remote's IR codes.

The project is written **without STM32 HAL/LL** — every peripheral (RCC/PLL, GPIO, EXTI, TIM, ADC,
USART) is driven through direct register access using hand-written drivers, on top of the plain
CMSIS Cortex-M0 core headers.

## What it does

1. Reads an analog temperature sensor (KY-013 thermistor) on **PB1** via `ADC1_IN9`.
2. Runs a small state machine that debounces the reading against two thresholds
   (`UPPER_TEMP_THRESHOLD = 28.0 °C`, `LOWER_TEMP_THRESHOLD = 23.5 °C`).
3. When a threshold is crossed, it transmits the AC remote's NEC-style IR frame through an
   IR LED (KY-005) on **PA0**, driven by a 38 kHz PWM carrier from `TIM2_CH1`.
4. After sending, it waits and re-measures; if the temperature moved the wrong way it assumes the
   AC missed the frame and re-sends it.

A separate **capture mode** (`CAPTURE_MODE`) reverses the flow: an IR receiver (KY-022) on **PB12**
raises an EXTI interrupt and the handler decodes the pulse train back into raw 32-bit words, so you
can learn the codes off your own remote and paste them into `main.c`.

## Hardware

| Function             | Part    | Pin  | Peripheral                  |
|----------------------|---------|------|-----------------------------|
| Temperature sensor   | KY-013  | PB1  | `ADC1` channel 9 (analog)   |
| IR transmitter (LED) | KY-005  | PA0  | `TIM2_CH1` PWM, AF2         |
| IR receiver          | KY-022  | PB12 | EXTI4_15, falling edge, pull-up |
| Debug UART TX        | —       | PA2  | `USART2_TX`, AF1            |
| Debug UART RX        | —       | PA3  | `USART2_RX`, AF1            |

System clock: HSI/2 × PLLMUL4 → **16 MHz**. UART runs at **115200 baud**.
`TIM3` is prescaled to a 1 MHz tick and used as the microsecond time base for all delays and for
measuring IR pulse widths.

## Repository layout

```
stm32f072rbt6_driver/
├── Src/main.c                     AC control state machine + pin configuration
├── Globals/Inc/
│   ├── config.h                   Feature switches (see below)
│   ├── types.h                    uint8/uint16/uint32/sint8, STD_ON/STD_OFF, OK/NOK
│   ├── stm32f072x8.h              Device register definitions
│   └── cortex_m0_config.h         NVIC / core helpers
├── CMSIS/Inc/                     core_cm0.h and friends
├── drivers/
│   ├── stm32f0xx_gpio_driver.*    GPIO + EXTI + NVIC config, read/write pin
│   ├── stm32f0xx_usart_driver.*   USART2 init + 50-byte RX ring buffer
│   ├── sys_adc.*                  ADC calibration, init, blocking read
│   ├── sys_frequency.*            PLL_Enable() — clock tree setup
│   └── sys_timer.*                TIM3 delays (us/ms/s), TIM2 38 kHz IR carrier
├── IR_Handling/                   NEC frame encoder (NEC_v_SendMessage)
├── IRQ_Handling/Src/IRQ_Handler.c EXTI4_15 IR decoder, USART2 RX ISR
├── Temperature_Handling/          ADC counts → °C (linear thermistor model)
├── ErrorHandler/                  Error_v_Report() + error code enum
├── ESP01Library/Inc/              ESP-01 WiFi AT command / type definitions
├── Startup/startup_stm32f072rbtx.s
└── STM32F072RBTX_FLASH.ld         128K flash, 16K RAM
```

## Configuration

All compile-time switches live in `Globals/Inc/config.h`:

| Macro             | Default   | Meaning |
|-------------------|-----------|---------|
| `DEBUGG_MODE`     | `STD_ON`  | Stores decoded pulse widths in `u_timeDiffMatrix` for inspection in the debugger |
| `STANDARD_REMOTE` | `STD_OFF` | Classic single-word (32-bit) NEC protocol: 9 ms burst / 4.5 ms space |
| `ZHJT03_REMOTE`   | `STD_ON`  | ZHJT-03 AC remote: 3 × 32-bit words, 6.1 ms burst / 7.3 ms space, extra trailing burst |
| `CAPTURE_MODE`    | `STD_OFF` | `STD_ON` = receive/decode IR; `STD_OFF` = run the AC control state machine |

`STANDARD_REMOTE` and `ZHJT03_REMOTE` are mutually exclusive — the guards in
`NEC_transmission.c` and `IRQ_Handler.c` only take effect when exactly one of them is `STD_ON`.

The IR codes themselves are hardcoded in `main.c`:

```c
uint32 u_powerOnCodes[3]  = {0xFF00FF00u, 0xFF00AB54u, 0x1BE454ABu};
uint32 u_powerOffCodes[3] = {0xFF00FF00u, 0xFF00EB14u, 0xFE0154ABu};
```

These match one specific ZHJT-03 remote (no timer, horizontal swing, fast fan, 23 °C cooling).
For a different AC, build with `CAPTURE_MODE = STD_ON`, point your remote at the KY-022, and read
the decoded words out of `u_code[3]` in `IRQ_Handler.c`.

## Building and flashing

The project is an **STM32CubeIDE / Eclipse CDT managed-make** project (`.project` / `.cproject`),
with `Debug` and `Release` configurations.

1. Open STM32CubeIDE → *File ▸ Import ▸ Existing Projects into Workspace* → select
   `stm32f072rbt6_driver/`.
2. Build (`Project ▸ Build Project`).
3. Flash/debug with the supplied ST-LINK launch configurations
   (`stm32f072rbt6_driver.launch`, `stm32f072rbt6_driver Debug.launch`); the OpenOCD board files
   `stm32f072rbt6_driver.cfg` / `stm32f072rbt6_driver Debug.cfg` target `STM32F072RBTx` over
   SWD with connect-under-reset.

`main()` calls `initialise_monitor_handles()`, so the build expects **semihosting** to be linked in
(`--specs=rdimon.specs`). If you flash a standalone binary without a debugger attached, remove that
call or the firmware will hang at startup.

## Notes and known rough edges

- **Blocking design.** IR transmission and IR decoding are done with busy-wait delays and spin loops
  on the input pin — the EXTI handler blocks inside the ISR for the length of a whole frame.
  It works because the device has nothing else to do, but it is not a general-purpose approach.
- **`Delay_v_us` resolution.** `TIM3->CNT` is reset and polled, so a delay call has ~1 µs granularity
  and no protection against ARR wraparound for values above 65535 µs.
- **NEC bit timing.** `NEC_v_SendWholePulse` uses a fixed 499 µs mark followed by a variable space —
  the mark length is a tuned constant rather than a derived one.
- **Temperature model** is a straight line fitted through two points (10 kΩ @ 25 °C, 12.5 kΩ @ 30 °C)
  against a 5 V reference, which is only accurate near that range. `V_REF` is an integer macro
  while the ADC is 12-bit; the divider assumes a 10 kΩ series resistor.
- **`CHECK_IF_AC_IS_ON/OFF` waits `Delay_v_seconds(60u)`** despite the comment saying 6 minutes —
  the comment carries a `TODO: Change this logic`.
- **ESP-01 support is headers-only.** `ESP01Library/Inc/` defines the AT command strings, status
  enums, and connection structures, but there is no `.cpp`/`.c` implementation yet and nothing in
  `main.c` uses it. The USART2 RX ring buffer and ISR are the groundwork for it.
- Most driver headers still carry `TODO` Doxygen stubs for their parameter documentation.
