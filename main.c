#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/led.h"
 
void app_main(void)
{
    /* Initialize led objects */
    led_t onboard_led = { .pin = 2, .state = OFF};
    led_t external_led = { .pin = 16, .state = OFF};
    
    /* Enable led */
    led_enable(&onboard_led);
    led_enable(&external_led);
 
    while(1)
    {
 
        led_toggle(&onboard_led);               /* toggle onboard led */
        led_on(&external_led);                  /* turn on external led */
        vTaskDelay(1000 / portTICK_PERIOD_MS);  /* 1 second delay */
        led_off(&external_led);                 /* turn off external led */
        vTaskDelay(100 / portTICK_PERIOD_MS);   /* 100 ms delay */
 
    }
}