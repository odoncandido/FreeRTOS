#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

EventGroupHandle_t eventg_example;
#define WIFI_CONN          1 << 0
#define HTTP_REQ          1 << 1
#define WIFI_AND_HTTP_DONE 1 << 2

void task_wifi_conn(void * params){
	while(pdTRUE){
		ESP_LOGI("WIFI", "Connecting wifi...");
		for(int i =0 ; i<10; i++){
			printf(".");
			vTaskDelay(500/portTICK_PERIOD_MS);

		}
		printf("\n");
		vTaskDelay(pdMS_TO_TICKS(300));
		ESP_LOGI("WIFI", "Wifi conected sucessfuly: IP[ 192.168.54.251 ]");
		vTaskDelay(pdMS_TO_TICKS(500));
		xEventGroupSetBits(eventg_example, WIFI_CONN);
		vTaskDelete(NULL);
	}
}
void task_http_req(void * params){
	while(pdTRUE){
		xEventGroupWaitBits(eventg_example, WIFI_CONN, pdFALSE, pdTRUE, portMAX_DELAY);
		char *url = "http://www.google.com";
		ESP_LOGI("http_req","Reuesting at %s", url);
		vTaskDelay(pdMS_TO_TICKS(1000));
		ESP_LOGI("http_req","HTTP Reuest [200]");
		printf("Request saved in buffer\n");
		vTaskDelay(pdMS_TO_TICKS(500));
		ESP_LOGI("http_req","Reuesting Done", url);
		xEventGroupSetBits(eventg_example, HTTP_REQ);
		vTaskDelay(pdMS_TO_TICKS(500));
		vTaskDelete(NULL);



	}
}
void app_main(void)
{
	eventg_example = xEventGroupCreate();
	xTaskCreate(&task_wifi_conn,
		"wifi_conn",
		1024 * 2,
		NULL,
		2,
		NULL
	);
	xTaskCreate(&task_http_req,
		"http_req",
		1024*2,
		NULL,
		4,
		NULL
		);
	xEventGroupWaitBits(eventg_example, WIFI_CONN | HTTP_REQ, pdTRUE, pdTRUE, portMAX_DELAY);
	ESP_LOGI("main","HTTP request is done!");
}
