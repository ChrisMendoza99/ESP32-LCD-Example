
/*
    This code utiliezes a 
    task, and can be used
    to create a little
    games!!!
    Made by Christopher A. Mendoza, UTEP 2023, 9/25/2022
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/esp_lcd.h"

#define debounce_cover 50

int i = 5; //This determines the starting position of "*-*/"

void lcd_task(void *pvParameters)
{ 
    /* Create LCD object */
    lcd_t lcd;
    /* Set lcd to default pins */
    lcdDefault(&lcd);
    /* Initialize LCD object */
    lcdInit(&lcd);
    /* Clear previous data on LCD */
    lcdClear(&lcd);
    int input_buttons[] = {15,5};
    for(int j = 0; j < 2; j++)
    {
        gpio_pad_select_gpio(input_buttons[j]);
        gpio_set_direction(input_buttons[j], GPIO_MODE_INPUT);
        gpio_set_pull_mode(input_buttons[j], GPIO_PULLDOWN_ONLY);
    }
    while(1)
    {
        /*Levels are set based on direction button*/
        int right = gpio_get_level(input_buttons[0]);
        int left= gpio_get_level(input_buttons[1]);
        /* Display text */
        lcdSetText(&lcd,"*-*/", i,0);
        /*These controls move the figure on screen*/
        if(right == 1) //Moves it right
        { 
            vTaskDelay(debounce_cover/ portTICK_PERIOD_MS);
            i++;
            lcdClear(&lcd); 
        }
        else if(left == 1) //Moves it left
        {
            vTaskDelay(debounce_cover/ portTICK_PERIOD_MS);
            i--;
            lcdClear(&lcd); 
        }
        else
        {
            vTaskDelay(100/portTICK_PERIOD_MS); /* avoid WDT trigger */
        }
    }
}
void app_main(void)
{
  xTaskCreate(lcd_task, "LCD task", 2048, NULL, 4, NULL);
}
