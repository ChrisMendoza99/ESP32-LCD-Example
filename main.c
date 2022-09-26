#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LOW  0  /* LOGIC LOW*/
#define HIGH 1  /* LOGIC HIGH*/
#define ONBOARD_LED 2 /* ONBOARD LED GPIO Pin*/

void task1(void *pvParameters){
    /* Select the GPIO pin that is going to be used */
    esp_rom_gpio_pad_select_gpio(ONBOARD_LED);
    /* Set the direction of the GPIO pin as OUTPUT */
    gpio_set_direction(ONBOARD_LED, GPIO_MODE_OUTPUT);

    while(1){
        /*Set the ONBOARD_LED as HIGH | 1 */
        gpio_set_level(ONBOARD_LED, HIGH);
        vTaskDelay(2000 / portTICK_PERIOD_MS); /* 2 second delay */

        /*Set the ONBOARD_LED as LOW | 0 */
        gpio_set_level(ONBOARD_LED, LOW);
        vTaskDelay(2000 / portTICK_PERIOD_MS); /* 2 second delay */
    }
}
void app_main(void){
    /* Create task 1 */
    xTaskCreate(&task1, "task1", 2048, NULL, 5, NULL);
}