#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <esp_log.h>

xSemaphoreHandle semafrobinario;

void conecxao_servido(void * param){
  while(true){
    printf("Servidor, Conectado ao servido\n");
    xSemaphoreGive(semafrobinario);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}
void processar_dados(void * param){
  while(true){
    xSemaphoreTake(semafrobinario, portMAX_DELAY);
    printf("Pagina caregada!\n");
  }
}


void setup() {
  // put your setup code here, to run once:
  semafrobinario = xSemaphoreCreateBinary();
  xTaskCreate(&conecxao_servido, "Conexcao com o servidor", 2048, NULL, 1, NULL);
  xTaskCreate(&processar_dados, "Processar dados", 2048, NULL, 1, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}
