#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "freertos/timers.h"
#include "driver/ledc.h"  

// "driver/ledc.h" libreria para el pwm 

#define led1 2

uint8_t led_level = 0;
uint8_t count = 0;
static const char *tag = "Main";
int interval = 50;
int timerId = 1;

TimerHandle_t xTimers;
// for pwm duty
int dutyR = 0;
int dutyG = 0;
int dutyB = 0;

esp_err_t init_led(void);
esp_err_t blink_led(void);
esp_err_t set_timer(void);
esp_err_t set_pwm(void);
esp_err_t set_pwm_duty(void);


void vTimerCallback(TimerHandle_t pxTimer)
{
    ESP_LOGI(tag, "R  : %i", dutyR);
    ESP_LOGI(tag, "G  : %i", dutyG);
    ESP_LOGI(tag, "B  : %i", dutyB);

    dutyR += 64 ;
    dutyG += 64 ;
    dutyB += 64;
    
    if (dutyR>1023)
    {
        dutyR = 0 ;
    }
    
    if (dutyG >1023)
    {
        dutyG = 0 ;
    }

    if (dutyB >1023)
    {
        dutyB = 0 ;
    }

    blink_led() ;
    set_pwm_duty() ;
}

void app_main(void)
{
    init_led();
    set_timer();
    set_pwm() ;
}

esp_err_t init_led(void)
{
    gpio_reset_pin(led1);
    gpio_set_direction(led1, GPIO_MODE_OUTPUT);
    return ESP_OK;
}

esp_err_t blink_led(void)
{
    led_level = !led_level;
    gpio_set_level(led1, led_level);
    return ESP_OK;
}

esp_err_t set_timer(void)
{
    ESP_LOGI(tag, "Timer init configuration");
    xTimers = xTimerCreate("Timer",                   // Just a text name, not used by the kernel.
                           (pdMS_TO_TICKS(interval)), // The timer period in ticks.
                           pdTRUE,                    // The timers will auto-reload themselves when they expire.
                           (void *)timerId,           // Assign each timer a unique id equal to its array index.
                           vTimerCallback             // Each timer calls the same callback when it expires.
    );

    if (xTimers == NULL)
    {
        ESP_LOGE(tag, "The timer was not created ");
        // The timer was not created.
    }

    else
    {
        if (xTimerStart(xTimers, 0) != pdPASS)
        {
            ESP_LOGE(tag, "The timer could not be set into the Active state");
            // The timer could not be set into the Active state.
        }
    }

    return ESP_OK;
}

esp_err_t set_pwm(void)
{
    ledc_channel_config_t channelIcongifR = {0} ;
    channelIcongifR.gpio_num = 33 ;
    channelIcongifR.speed_mode = LEDC_HIGH_SPEED_MODE ;
    channelIcongifR.channel = LEDC_CHANNEL_0 ; // canal 1
    channelIcongifR.intr_type =  LEDC_INTR_DISABLE ;  // SIN INTERRUPCIONES
    channelIcongifR.timer_sel =  LEDC_TIMER_0 ;
    channelIcongifR.duty = 0 ;

    ledc_channel_config_t channelIcongifG = {0} ;
    channelIcongifG.gpio_num = 25 ;
    channelIcongifG.speed_mode = LEDC_HIGH_SPEED_MODE ;
    channelIcongifG.channel = LEDC_CHANNEL_1 ;  // canal 2
    channelIcongifG.intr_type =  LEDC_INTR_DISABLE ;  // SIN INTERRUPCIONES
    channelIcongifG.timer_sel =  LEDC_TIMER_0 ;
    channelIcongifG.duty = 0 ;

    ledc_channel_config_t channelIcongifB = {0} ;
    channelIcongifB.gpio_num = 26 ;
    channelIcongifB.speed_mode = LEDC_HIGH_SPEED_MODE ;
    channelIcongifB.channel = LEDC_CHANNEL_2 ;  // canal 3 
    channelIcongifB.intr_type =  LEDC_INTR_DISABLE ;  // SIN INTERRUPCIONES
    channelIcongifB.timer_sel =  LEDC_TIMER_0 ;
    channelIcongifB.duty = 0 ;

    ledc_channel_config(&channelIcongifB) ;
    ledc_channel_config(&channelIcongifR) ;
    ledc_channel_config(&channelIcongifG) ;

    ledc_timer_config_t timerConfig = {0};
    timerConfig.speed_mode = LEDC_HIGH_SPEED_MODE;
    timerConfig.duty_resolution = LEDC_TIMER_10_BIT ;
    //timerConfigR.bit_num = LEDC_TIMER_10_BIT ;
    timerConfig.timer_num = LEDC_TIMER_0 ;
    timerConfig.freq_hz = 20000 ; // 20 KHz ;
 
    ledc_timer_config(&timerConfig)  ;

    return ESP_OK;
}

esp_err_t set_pwm_duty(void)
{

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, dutyR) ;
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, dutyG) ;
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, dutyB) ;
    
    ledc_update_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_0) ;
    ledc_update_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_1) ;
    ledc_update_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_2) ;

    return ESP_OK;
}