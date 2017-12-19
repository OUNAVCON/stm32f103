/*
 * heartbeat.c
 *
 *  Created on: Dec 18, 2017
 *      Author: Isaac.Rose
 */

#include "FreeRTOS.h"
#include "task.h"

#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"

#include "tasks.h"

void heartbeat_task(void *pvParameters)
{
	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;


	// Define the init structure for the output LED pin

    // Init output LED GPIO.


    for (;;)
    {
       HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
       vTaskDelay(xDelay);
    }

}
