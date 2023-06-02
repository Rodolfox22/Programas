/*Realizar un programa que al introducir por teclado en el terminal serie un valor de ángulo en º, el motor paso a paso gire esa cantidad de grados hacia la derecha, y si ingresa un número de grados con signo negativo, gire la cantidad de grados en forma anti-horaria*/
#include <Stepper.h>

#define PASOS_PV 2048
#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5
#define VELOCIDAD 10

Stepper pasitoApasito(PASOS_PV, PIN_1, PIN_2, PIN_3, PIN_4);

void contarVueltas(int grados);

int posicion = 0, anterior = 0, vuelta = 0;
float factorOmega = float(PASOS_PV)/360.0;

void setup()
{
  Serial.begin(9600);

  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);

  pasitoApasito.setSpeed(VELOCIDAD);
}

void loop()
{
  if (Serial.available())
  {
    int lectura = Serial.parseInt();
    posicion += lectura;
    lectura *= factorOmega; // Conversion de grados a pasos
    pasitoApasito.step(lectura);
  }
    contarVueltas(posicion);
}

void contarVueltas(int grados)
{
  if (grados < 0)
  {
    grados += 360;
    vuelta--;
  }

  if (grados > 360)
  {
    grados -= 360;
    vuelta++;
  }

   if (grados != anterior)
  {
    anterior = grados;
    Serial.print("Posicion: ");
    Serial.print(grados);
    Serial.print(" grados.\tVuelta:");
    Serial.println(vuelta);
  }
}
