#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/event_groups.h>
#include <esp_log.h>

EventGroupHandle_t eventGroupCOnectividade;
const int conexaowifi = BIT0;
const int conexaoMQTT = BIT1;

xSemaphoreHandle ligarMQTT;

void conectarwifi(void *params){
  while(true){
    printf("WiFi, Conectando ao WiFi\n");
    xEventGroupSetBits(eventGroupCOnectividade, conexaowifi);
    xSemaphoreGive(ligarMQTT);
    vTaskDelay(1000 /portTICK_PERIOD_MS);
  }
}

void conectarMQTT(void *params){
  while(true){
    xSemaphoreTake(ligarMQTT, portMAX_DELAY);
    printf("MQTT, Conectando ao MQTT\n");
    xEventGroupSetBits(eventGroupCOnectividade, conexaoMQTT);
  }
}

void processar_dados(void *params){
  while(true){
    xEventGroupWaitBits(eventGroupCOnectividade, conexaowifi | conexaoMQTT, true, true, portMAX_DELAY); // true _>Parametro clear ou next, pode ou nao liberar as flags// true -> Quer aguardar por todos os BITs, ate que todos sejam ativos.
    printf("\nProcessar dados\n\n");
    printf("Task, Desconecta da internet\n\n");
    vTaskDelay(1000 /portTICK_PERIOD_MS);
    

  }
}


void setup() {
  // put your setup code here, to run once:
  eventGroupCOnectividade = xEventGroupCreate();
  ligarMQTT = xSemaphoreCreateBinary();
  xTaskCreate(&conectarwifi, "Conecta ao WiFi", 2048, NULL, 1, NULL);
  xTaskCreate(&conectarMQTT, "Conecta ao servidor MQTT", 2048, NULL, 1, NULL);
  xTaskCreate(&processar_dados, "Processar dados", 2048, NULL, 1, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}
