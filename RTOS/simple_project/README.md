# FreeRTOS Task, Queue, and Semaphore Example

## Overview
This project demonstrates the basic concepts of **FreeRTOS**:

- **Tasks**: Independent threads of execution.
- **Queues**: Communication between tasks (FIFO message buffer).
- **Semaphores**: Synchronization mechanism to protect shared resources.
- **Scheduler**: Determines which task runs based on priority.

In this example:

1. **Sensor Task** generates sensor data and sends it to a queue.
2. **Display Task** receives the data from the queue and prints it.
3. A **binary semaphore** is used to safely access the UART (shared resource).

## Hardware Requirements
- Any microcontroller with FreeRTOS support (STM32, LPC, etc.)
- UART or printf enabled for console output.

---

## Software Requirements
- FreeRTOS kernel
- Standard C compiler (e.g., arm-none-eabi-gcc for ARM)
- Optional: IDE or build system (STM32CubeIDE, Keil, etc.)

---

## How to Run
1. Include FreeRTOS headers and source files in your project.
2. Compile the `FreeRTOS_Tasks.c` code for your target MCU.
3. Flash the binary to your board.
4. Open a UART terminal to observe the output.

---

## Features Demonstrated
- **Task creation and scheduling**: `xTaskCreate()`, `vTaskStartScheduler()`
- **Queue communication**: `xQueueSend()`, `xQueueReceive()`
- **Semaphore synchronization**: `xSemaphoreTake()`, `xSemaphoreGive()`
- **Task delay**: `vTaskDelay()`

---

## Notes
- Task priorities affect which task executes first.
- The queue ensures no data is lost between tasks.
- Semaphores protect shared resources from race conditions.

---

## References
- [FreeRTOS Official Documentation](https://www.freertos.org/)
- [FreeRTOS Tutorial Examples](https://www.freertos.org/tutorial/index.html)

