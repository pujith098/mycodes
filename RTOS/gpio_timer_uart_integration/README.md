# System Integration PoC: GPIO + UART + Timer + FreeRTOS

## Overview
This project demonstrates **system integration** using FreeRTOS tasks on an STM32 microcontroller:

- **GPIO**: Control an LED.
- **UART**: Communicate sensor and LED status to a terminal.
- **Timer (simulated)**: Periodic sensor reading.
- **FreeRTOS**: Tasks, queues, and semaphores.

Two FreeRTOS tasks are implemented:

1. **SensorTask**: Simulates a sensor and sends data to a queue.
2. **LedTask**: Receives data from the queue and toggles an LED.

A **binary semaphore** ensures safe UART communication.

---

## Hardware Requirements
- STM32 Nucleo board (e.g., Nucleo-F446RE)
- LED connected to GPIOA_PIN_5
- UART2 connected to PC via USB

---

## Software Requirements
- STM32 HAL library
- FreeRTOS kernel
- ARM cross-compiler (e.g., `arm-none-eabi-gcc`)
- Optional: STM32CubeIDE for easy build/flash

---

## How to Run
1. Configure GPIO and UART using STM32CubeMX or HAL.
2. Compile and flash the `system_integration.c` to your board.
3. Open a UART terminal at 115200 baud.
4. Observe LED toggling and sensor value printout every second.

---

## Features Demonstrated
- FreeRTOS **task creation and scheduling**
- Inter-task communication using **queue**
- Shared resource protection using **semaphore**
- GPIO control for **LED**
- UART communication

---

## References
- [FreeRTOS Documentation](https://www.freertos.org/)
- [STM32 HAL Documentation](https://www.st.com/en/embedded-software/stm32cube-mcu-packages.html)


