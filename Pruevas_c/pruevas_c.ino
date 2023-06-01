#include <Arduino.h>
#define LED1 4
#define LED2 6
#define LED3 7
#define LED4 8

int enciende[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}};

int leds[4] = {LED1, LED2, LED3, LED4};

void setup()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      digitalWrite(leds[j], enciende[i][j]);
    }
    delay(1000);
  }
}