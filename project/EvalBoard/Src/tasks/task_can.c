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
//#include "can.h"

#include "tasks.h"

extern CAN_HandleTypeDef hcan;

void can_task(void *pvParameters)
{
	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
	HAL_CAN_StateTypeDef state;
	volatile uint32_t error;

	// Define the init structure for the output LED pin

    // Init output LED GPIO.
	CanTxMsgTypeDef txMsg;

	txMsg.ExtId = 0x18ff0213;
	txMsg.DLC = 4;
	txMsg.Data[0] = 0xff;
	txMsg.Data[1] = 0x12;
	txMsg.Data[2] = 0x31;
	txMsg.Data[3] = 01;
	txMsg.RTR = CAN_RTR_DATA;
	txMsg.IDE = CAN_ID_EXT;
	hcan.pTxMsg = &txMsg;
	HAL_CAN_Init(&hcan);
    for (;;)
    {
       state = HAL_CAN_GetState(&hcan);
       error = HAL_CAN_GetError(&hcan);
       if(HAL_CAN_STATE_READY == state )//&& HAL_CAN_ERROR_NONE == error){
    	   if( HAL_OK != HAL_CAN_Transmit_IT(&hcan))
    	   {
    		   while(1);
    	   }
       }

       vTaskDelay(xDelay);
    }


void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan){
	uint32_t error = HAL_CAN_GetError(&hcan);
	uint8_t state = 0;
	if(HAL_CAN_ERROR_NONE != error){
		switch(error){
		case HAL_CAN_ERROR_EWG:
			state = 1;
			break;
		case HAL_CAN_ERROR_EPV:
			state = 2;
			break;
		case HAL_CAN_ERROR_BOF:
			state = 3;
			break;
		case HAL_CAN_ERROR_STF:
			state = 4;
			break;
		case HAL_CAN_ERROR_FOR:
			state = 5;
			break;
		case HAL_CAN_ERROR_ACK:
			state = 6;
			break;
		case HAL_CAN_ERROR_BR:
			state = 7;
			break;
		case HAL_CAN_ERROR_BD:
			state = 8;
			break;
		case HAL_CAN_ERROR_CRC:
			state = 9;
			break;
		case HAL_CAN_ERROR_FOV0:
			state = 10;
			break;
		case HAL_CAN_ERROR_FOV1:
			state = 11;
			break;
		case HAL_CAN_ERROR_TXFAIL:
			state = 12;
			break;
		}

	hcan->Instance->TSR |= CAN_TSR_ABRQ0; //cancel the transmission.
	}
}
