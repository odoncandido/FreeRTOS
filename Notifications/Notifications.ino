#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


static TaskHandle_t receptorHandle = NULL;

void emissor(void *params){
  while(true){
    xTaskNotifyGive(receptorHandle);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void receptor(void *params){
  while(true){
    int quantidade = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);    
    printf("Notificacoes recebidas %d\n", quantidade);
  }
}

void setup() {
  
  xTaskCreate(&receptor, "Receptor", 2048, NULL, 2, &receptorHandle);
  xTaskCreate(&emissor, "Emissor 1", 2048, NULL, 2, NULL);
  xTaskCreate(&emissor, "Emissor 2", 2048, NULL, 2, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}
