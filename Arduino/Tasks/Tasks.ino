#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

// criacao da primeira task
void task1(void *params){
  while(true){
    // ESP_LOGI("TASK1", "Leitura de sensores") // log de informacao
    // ESP_LOGE("TASK1", "Leitura de sensores") // log de erro
    // ESP_LOGW("TASK1", "Leitura de sensores") // log de warning
    // ESP_LOGD("TASK1", "Leitura de sensores") // lod ge debugind
    // ESP_LOGV("TASK1", "Leitura de sensores") // log de verbose
    printf("Leitura de sesores\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void *params){
  while(true){
    ESP_LOGI("TASK1", "Escrever no display");
    printf("Escrever no display\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  xTaskCreate(*task1, "Leitura", 2048, NULL, 1, NULL);
  xTaskCreatePinnedToCore(*task2, "Display", 2048, NULL, 1, NULL, 0); //Coloca o processo no nucleo 0
}

void loop() {
  // put your main code here, to run repeatedly:

}
