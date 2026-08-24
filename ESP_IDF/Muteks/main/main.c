#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

SemaphoreHandle_t printSerial;
SemaphoreHandle_t printDisplay;

void task_n1(void * params){
	while(pdTRUE){
		xSemaphoreTake(printDisplay, portMAX_DELAY);
		//
		xSemaphoreGive(printDisplay);
		vTaskDelay(1/portTICK_PERIOD_MS);
		if(xSemaphoreTake(printSerial, portMAX_DELAY)){
			//
		}
	}

}
void task_n2(void * params){
	while(pdTRUE){
		xSemaphoreTake(printSerial, portMAX_DELAY);
		//
		vTaskDelay(1/portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
	printDisplay = xSemaphoreCreateMutex();
	printSerial  = xSemaphoreCreateBinary();

}
