#include <LiquidCrystal.h>

#define POTEV A0
#define POTEA A1
#define POTER A2

void imprimirLCD();

// Definir los pines utilizados para la pantalla LCD
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long tiempo_anterior = 0;

int ledV = 9,
    ledA = 10,
    ledR = 11;
int verde = 0, azul = 0, rojo = 0, anterior = 0;

void setup()
{
  pinMode(ledV, OUTPUT);
  pinMode(ledA, OUTPUT);
  pinMode(ledR, OUTPUT);

  pinMode(POTEV, INPUT);
  pinMode(POTEA, INPUT);
  pinMode(POTER, INPUT);

  // Inicializar puerto serie
  Serial.begin(9600);

  // Inicializar la pantalla LCD
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Hola mundo");
  lcd.setCursor(8, 1);
  lcd.print("by Polos");
  delay(2000);
}

void loop()
{

  verde = map(analogRead(POTEV), 0, 1023, 255, 0);
  azul = map(analogRead(POTEA), 0, 1023, 255, 0);
  rojo = map(analogRead(POTER), 0, 1023, 255, 0);

  analogWrite(ledV, verde);
  analogWrite(ledA, azul);
  analogWrite(ledR, rojo);

  Serial.print("Rojo: " + String(rojo));
  Serial.print("\tVerde: " + String(verde));
  Serial.println("\tAzul: " + String(azul));
  int cambio = rojo + verde + azul;
  if (cambio != anterior)
  {
    anterior = cambio;
    imprimirLCD();
  }
}

void imprimirLCD()
{
  if (millis() - tiempo_anterior >= 200)
  {
    tiempo_anterior = millis();

    // Limpiar la pantalla LCD
    lcd.clear();

    // Imprimir la variable en la primera línea de la pantalla
    lcd.setCursor(0, 0);
    lcd.print("Rojo Azul Verde");

    // Imprimir el valor de la variable en la segunda línea de la pantalla
    lcd.setCursor(1, 1);
    lcd.print(rojo);
    lcd.setCursor(6, 1);
    lcd.print(azul);
    lcd.setCursor(11, 1);
    lcd.print(verde);
  }
}
