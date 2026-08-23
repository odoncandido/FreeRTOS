#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <esp_log.h>

xQueueHandle fila_de_temperaturas;
float temperatura_media;

void leitura_de_sensores(void *params){
  float temperatura;
  while(true){
    temperatura = 20.0 * ((float) rand() / (float)(RAND_MAX/1.0));
    long resposta = xQueueSend(fila_de_temperaturas, &temperatura, 1000/portTICK_PERIOD_MS); // se a fila nao esiver respondendo espera 1s para fazer o envio
    if(resposta){
      printf("\nLeitura, Temperatura adicionada na fila\n");
    }else printf("Leitura, ERRO nao foi possivel adicionar a temperatura na fila\n");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void calcular_media_movel(void *params){
  float temperatura = 0.0;
  float temperatura_anterior = 0.0;
  while(true){
    if(xQueueReceive(fila_de_temperaturas, &temperatura, 5000 / portTICK_PERIOD_MS)){
      temperatura_media = (temperatura_anterior  + temperatura)/2.0;
      temperatura_anterior = temperatura;
      printf("Temperatura media %f\n", temperatura_media);
    }else {
      printf("Calculo, Fila nao disponivel\n");
    }
  }
}

void setup() {
  fila_de_temperaturas = xQueueCreate(5, sizeof(float));
  xTaskCreate(&leitura_de_sensores, "Le Temperatura", 2048, NULL, 2, NULL);
  xTaskCreatePinnedToCore(&calcular_media_movel, "Calcula temperatura media", 2048, NULL, 1, NULL, 0);
}

void loop() {
  //
}
