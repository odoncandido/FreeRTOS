#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <esp_log.h>

float temperatura;
xSemaphoreHandle mutexI2C;
float acessa_i2c(int comando){
  if(comando == 1){
    printf("I2C, Leitura de sensor de Temperatura\n");
    return 20.0 * ((float) rand()/ (float) (RAND_MAX/10)); // retorna valor aleatorio entre 10 e 20
  }else{
    printf("I2C, Escrita no LCD\n");
    printf("Tela de LCD Temperatura = %f\n", temperatura);
  }
  return 0;
}

void le_sensor(void * params){
  while (true){
    if(xSemaphoreTake(mutexI2C, 1000/portTICK_PERIOD_MS)){
      temperatura = acessa_i2c(1);
      printf("Leitura, Temperatura lida: %f\n", temperatura);
      xSemaphoreGive(mutexI2C);
    }else{
      printf("Leitura, Nao foi possivel ler o sensor\n");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void lcd_display(void * params){
  while (true){
    if(xSemaphoreTake(mutexI2C, 1000/portTICK_PERIOD_MS)){
      
      printf("Display, Escrever no LCD\n");
      acessa_i2c(2);
      xSemaphoreGive(mutexI2C);
    }else{
      printf("Display, Nao foi possivel escrever no display\n");
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  delay(2000);
  mutexI2C = xSemaphoreCreateMutex();
  xTaskCreate(&le_sensor, "Leitura de sensor 1", 2048, NULL, 2, NULL);
  xTaskCreate(&lcd_display, "Atualizacao do display", 2048, NULL, 2, NULL);

}

void loop() {
  // put your main code here, to run repeatedly:

}
