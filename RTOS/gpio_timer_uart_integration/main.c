/*
 * System Integration PoC: GPIO + UART + Timer + FreeRTOS
 * Author: Pujit Kumar
 * Board: STM32 Nucleo (example)
 */

#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

// Hardware Definitions
#define LED_PIN GPIO_PIN_5
#define LED_PORT GPIOA
#define UART_HANDLE huart2

extern UART_HandleTypeDef huart2;

// Queue and Semaphore
QueueHandle_t sensorQueue;
SemaphoreHandle_t uartSemaphore;

// Function to send string over UART safely
void uart_send(const char *msg) {
    xSemaphoreTake(uartSemaphore, portMAX_DELAY);
    HAL_UART_Transmit(&UART_HANDLE, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
    xSemaphoreGive(uartSemaphore);
}

// Simulated sensor read task
void SensorTask(void *pvParameters) {
    int sensorValue = 0;
    char buf[50];

    while(1) {
        sensorValue++;
        xQueueSend(sensorQueue, &sensorValue, portMAX_DELAY);

        sprintf(buf, "Sensor Task: Sent value %d\r\n", sensorValue);
        uart_send(buf);

        vTaskDelay(pdMS_TO_TICKS(1000)); // 1 sec delay
    }
}

// LED control task: toggles LED based on sensor value
void LedTask(void *pvParameters) {
    int receivedValue;

    while(1) {
        if(xQueueReceive(sensorQueue, &receivedValue, portMAX_DELAY) == pdPASS) {
            HAL_GPIO_TogglePin(LED_PORT, LED_PIN);

            char buf[50];
            sprintf(buf, "LED Task: Toggled LED, Sensor value %d\r\n", receivedValue);
            uart_send(buf);
        }
    }
}

// Main function
int main(void) {
    HAL_Init();
    SystemClock_Config();    // Initialize system clock
    MX_GPIO_Init();          // Initialize GPIO
    MX_USART2_UART_Init();   // Initialize UART2

    // Create queue and semaphore
    sensorQueue = xQueueCreate(5, sizeof(int));
    uartSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(uartSemaphore);

    // Create FreeRTOS tasks
    xTaskCreate(SensorTask, "SensorTask", 128, NULL, 2, NULL);
    xTaskCreate(LedTask, "LedTask", 128, NULL, 1, NULL);

    // Start scheduler
    vTaskStartScheduler();

    // Should never reach here
    while(1);
}

