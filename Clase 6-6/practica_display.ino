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

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C de la pantalla LCD y dimensiones (16 columnas, 2 filas)

void encoder();

int anterior = 0;

volatile int conteo = 50;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Grupazo este");

  pinMode(A, INPUT);
  pinMode(B, INPUT);
  attachInterrupt(digitalPinToInterrupt(A), encoder, FALLING);

  delay(3000);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("ENCODER");
}

void loop()
{

  if (conteo != anterior)
  {
    conteo = max(0, min(conteo, 100));
    anterior = conteo;
    Serial.println(conteo);
    lcd.setCursor(7, 1);
    lcd.print(conteo,%03d);
  }
}

void encoder()
{
  static unsigned long tiempo = 0;
  if (millis() - tiempo >= 5)
  {
    if (digitalRead(B))
    {
      conteo++;
    }
    else
    {
      conteo--;
    }
    tiempo = millis();
  }
}