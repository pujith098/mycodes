#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include <stdio.h>

// Global handles
QueueHandle_t xQueue;
SemaphoreHandle_t xSemaphore;

// Task prototypes
void vSensorTask(void *pvParameters);
void vDisplayTask(void *pvParameters);

int main(void)
{
    // Create a queue to hold integer values (sensor data)
    xQueue = xQueueCreate(5, sizeof(int));

    // Create a binary semaphore for resource protection
    xSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore); // Initially available

    // Create two tasks
    xTaskCreate(vSensorTask, "SensorTask", 1000, NULL, 2, NULL);
    xTaskCreate(vDisplayTask, "DisplayTask", 1000, NULL, 1, NULL);

    // Start the scheduler (never returns)
    vTaskStartScheduler();

    for (;;);
}

void vSensorTask(void *pvParameters)
{
    int sensor_value = 0;

    for (;;)
    {
        sensor_value++;

        // Send data to queue
        if (xQueueSend(xQueue, &sensor_value, portMAX_DELAY) == pdPASS)
        {
            // Use semaphore to access shared UART/printf safely
            if (xSemaphoreTake(xSemaphore, portMAX_DELAY))
            {
                printf("Sensor Task: Sent %d to queue\n", sensor_value);
                xSemaphoreGive(xSemaphore);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay 1 second
    }
}

void vDisplayTask(void *pvParameters)
{
    int received_value = 0;

    for (;;)
    {
        // Wait for data from queue
        if (xQueueReceive(xQueue, &received_value, portMAX_DELAY) == pdPASS)
        {
            if (xSemaphoreTake(xSemaphore, portMAX_DELAY))
            {
                printf("Display Task: Received %d from queue\n", received_value);
                xSemaphoreGive(xSemaphore);
            }
        }
    }
}

