/*
Display

Cristal liquido
  1602
    16 caracteres en 2 lineas
    alientacion y 14 pines de datos
    Mejora: I2C
  2004
    20 caracteres en 4 lineas
    I2C
Tecnologia LED RGB
  Qled
  Olde
  TFT

    0,94"     -> 160 x 120 px
    7" touch  ->
/////////////////////
I2C --> libreria <Wire.h>
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define A 2
#define B 4

#define Wokwi

#ifndef Wokwi
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7); // Fisico
#else
LiquidCrystal_I2C lcd(0x27, 16, 2); // Wokwi
#endif

void encoder();

int anterior = 0;

volatile int conteo = 50;

void setup()
{
  Serial.begin(9600);

#ifndef Wokwi
  lcd.begin(16, 2);                 // Fisico
  lcd.setBacklightPin(3, POSITIVE); // Fisico
  lcd.setBacklight(HIGH);           // Fisico*/

#else
  lcd.init();                       // Wokwi
  lcd.backlight();                  // Wokwi
#endif

  lcd.setCursor(2, 0);
  lcd.print("Grupazo este");

  pinMode(A, INPUT);
  pinMode(B, INPUT);

  delay(3000);
  attachInterrupt(digitalPinToInterrupt(A), encoder, FALLING);

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("ENCODER");
}

void loop()
{

  if (conteo != anterior)
  {

    anterior = conteo;
    Serial.println(conteo);
    lcd.setCursor(6, 1);
    char cadena[4];
    sprintf(cadena, "%03d", conteo);
    for (int i; i < 2; i++)
    {
      // Serial.println(cadena[i]);
      if (cadena[i] != '0')
      {
        break;
      }
      
      else
      {
        cadena[i] = ' ';
      }
    }

    lcd.print(cadena);
  }
}


void encoder()
{
  static unsigned long tiempo = 0;
  if (millis() - tiempo >= 5)
  {
    if (!digitalRead(B))
    {
      conteo++;
    }
    else
    {
      conteo--;
    }
    conteo = max(0, min(conteo, 100));
    tiempo = millis();
  }
}
