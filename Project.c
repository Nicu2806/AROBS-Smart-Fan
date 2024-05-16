#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "Adafruit_ILI9341.h"
#include "DHT.h"
#include "Servo.h"

#define TFT_CS_Pin GPIO_PIN_6
#define TFT_CS_GPIO_Port GPIOB
#define TFT_RST_Pin GPIO_PIN_7
#define TFT_RST_GPIO_Port GPIOB
#define TFT_DC_Pin GPIO_PIN_8
#define TFT_DC_GPIO_Port GPIOB

#define joyX_Pin GPIO_PIN_0
#define joyX_GPIO_Port GPIOC
#define joyY_Pin GPIO_PIN_1
#define joyY_GPIO_Port GPIOC
#define joyButton_Pin GPIO_PIN_2
#define joyButton_GPIO_Port GPIOC

#define AirQualityPin_Pin GPIO_PIN_2
#define AirQualityPin_GPIO_Port GPIOA

#define DHTPIN_Pin GPIO_PIN_5
#define DHTPIN_GPIO_Port GPIOA

#define IN1_Pin GPIO_PIN_4
#define IN1_GPIO_Port GPIOA
#define IN2_Pin GPIO_PIN_5
#define IN2_GPIO_Port GPIOA

#define DHTTYPE DHT11

SPI_HandleTypeDef hspi1;
DHT_HandleTypeDef hdht;
UART_HandleTypeDef huart2;

Adafruit_ILI9341 tft = Adafruit_ILI9341(&hspi1, TFT_CS_Pin, TFT_DC_Pin, TFT_RST_Pin);
DHT dht(&hdht, DHTPIN_Pin, DHTTYPE);
Servo myServo;

int currentPage = 0;
float temperature = 0;
float humidity = 0;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_DHT_Init(void);

int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  MX_DHT_Init();

  tft.begin();
  dht.begin();
  myServo.attach(D4);

  while (1) {
    HAL_Delay(5000);

    int joyXValue = HAL_ADC_GetValue(&hadc1);
    int joyYValue = HAL_ADC_GetValue(&hadc2);
    int buttonState = HAL_GPIO_ReadPin(joyButton_GPIO_Port, joyButton_Pin);

    if (buttonState == GPIO_PIN_RESET) {
      currentPage = (currentPage + 1) % 2;
      HAL_Delay(200);
    } else {
      if (joyYValue < 100) {
        currentPage = (currentPage + 1) % 2;
        HAL_Delay(200);
      } else if (joyYValue > 900) {
        currentPage = (currentPage + 2) % 2;
        HAL_Delay(200);
      }
    }

    myServo.write(180);
    HAL_Delay(2000);
    myServo.write(0);
    HAL_Delay(2000);

    HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);
  }
}

void SystemClock_Config(void) {
}

static void MX_GPIO_Init(void) {
}

static void MX_SPI1_Init(void) {
}

static void MX_USART2_UART_Init(void) {
}

static void MX_DHT_Init(void) {
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
}

void Error_Handler(void) {
}

