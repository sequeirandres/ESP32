#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define led1 2
#define ledR 33
#define ledG 25
#define ledB 26

#define STACK_SIZE 1024*8 // size in memory

#define LED_delay 500
#define R_delay 1000
#define G_delay 1500
#define B_delay 750

esp_err_t init_led(void);
esp_err_t init_RGB(void);

void blink_led(void);

esp_err_t create_tasks(void);

void vTaskR(void *pvParameters);
void vTaskG(void *pvParameters);
void vTaskB(void *pvParameters);

static const char *tag = "Main";

void app_main(void)
{
    init_led();
    init_RGB() ;
    //create_tasks();

    while (1)
    {
        blink_led();
        //vTaskDelay(pdMS_TO_TICKS(LED_delay));
        printf("Blink \n") ;
        //ESP_LOGE(tag, "Blink");
    }
    // set_timer();
}

esp_err_t init_led(void)
{
    gpio_reset_pin(led1);
    gpio_set_direction(led1, GPIO_MODE_OUTPUT);
    return ESP_OK;
}


esp_err_t init_RGB(void)
{
    gpio_reset_pin(ledR);
    gpio_set_direction(ledR, GPIO_MODE_OUTPUT);
    
    gpio_reset_pin(ledG);
    gpio_set_direction(ledG, GPIO_MODE_OUTPUT);

    gpio_reset_pin(ledB);
    gpio_set_direction(ledB, GPIO_MODE_OUTPUT);

    return ESP_OK;
}

void blink_led(void)
{
    gpio_set_level(led1, 1);
    vTaskDelay(pdMS_TO_TICKS(LED_delay));
    gpio_set_level(led1, 0);
    vTaskDelay(pdMS_TO_TICKS(LED_delay));
}

// TASK FOR LED R
void vTaskR(void *pvParameters)
{
    gpio_set_level(ledR, 1);
    vTaskDelay(pdMS_TO_TICKS(R_delay));
    gpio_set_level(ledR, 0);
    vTaskDelay(pdMS_TO_TICKS(R_delay));
    ESP_LOGE(tag, "RED");
}

// TASK FOR LED G
void vTaskG(void *pvParameters)
{
    gpio_set_level(ledG, 1);
    vTaskDelay(pdMS_TO_TICKS(G_delay));
    gpio_set_level(ledG, 0);
    vTaskDelay(pdMS_TO_TICKS(G_delay));
     ESP_LOGE(tag, "GREEN");
}

// TASK FOR LED B
void vTaskB(void *pvParameters)
{
    gpio_set_level(ledB, 1);
    vTaskDelay(pdMS_TO_TICKS(B_delay));
    gpio_set_level(ledB, 0);
    vTaskDelay(pdMS_TO_TICKS(B_delay));
     ESP_LOGE(tag, "BLUE");
}

esp_err_t create_tasks(void)
{

    static uint8_t ucParameterToPass;
    TaskHandle_t xHandle = NULL;

    xTaskCreate(vTaskR,
                "TaskR",
                STACK_SIZE, // TAMANIO EN MEMORIA
                &ucParameterToPass,
                1, // PRIORIDAD
                &xHandle);

//    xTaskCreate(vTaskG,
//                "Task G",
//                STACK_SIZE, // TAMANIO EN MEMORIA
//                &ucParameterToPass,
//                1, // PRIORIDAD
//                &xHandle);

//    xTaskCreate(vTaskB,
//                "Task B",
//                STACK_SIZE, // TAMANIO EN MEMORIA
//                &ucParameterToPass,
//                1, // PRIORIDAD
//                &xHandle);

    return ESP_OK;
}