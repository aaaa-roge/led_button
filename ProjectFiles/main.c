#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "semphr.h"

static int taskCounter = 0;
static SemaphoreHandle_t mutex;

void led_task() {

    const uint LED_PIN = 18;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(1) {
        if(xSemaphoreTake(mutex, 0) == pdTRUE) {

            if(taskCounter > 0) {
                printf("task 1 - %d\n", taskCounter);
                gpio_put(LED_PIN, 1);
                vTaskDelay(50);
                gpio_put(LED_PIN, 0);
                vTaskDelay(50);
                taskCounter--;
            }
            xSemaphoreGive(mutex);
        }
    }
}

void led_task2() {
    
    const uint LED_PIN = 19;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(1) {
        if(xSemaphoreTake(mutex, 0) == pdTRUE) {

            if(taskCounter == 0) {
                printf("task 2 - %d\n", taskCounter);
                gpio_put(LED_PIN, 1);
                vTaskDelay(50);
                gpio_put(LED_PIN, 0);
                vTaskDelay(50);
                taskCounter = 3;
            }
            xSemaphoreGive(mutex);
        }
    }
}


int main() {
    stdio_init_all();

    printf("\nLED init\n");

    //create mutex before tasks
    mutex = xSemaphoreCreateMutex();

    // 256 = num of words allocated to the task stack
    // not passing args to the LED_Task function therefore NULL
    // task priority of 1
    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    xTaskCreate(led_task2, "LED_Task2", 256, NULL, 1, NULL);

    // start task scheduler
    vTaskStartScheduler();

    while(1) {
        printf("running task");
    };

}