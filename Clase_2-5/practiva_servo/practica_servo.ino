#include <Servo.h>
#define PINSERVO 9

int beta = 0;

Servo brazo1;

void setup()
{
  Serial.begin(9600);
  pinMode(PINSERVO, OUTPUT);
}

void loop()
{
  Serial.begin(9600);
  brazo1.attach(PINSERVO);
  brazo1.write(beta);
  while (!Serial.available())
  {
  }
  beta = Serial.parseInt();
  int gamma = beta;
  Serial.pintln("Ingrese angulo");
  while (!Serial.available())
  {
  }
  String instruccion = Serial.readString();
  Serial.println("Ingrese ok para volver al inicio");
  if (instruccion = "ok")
  {
    Serial.println("Volviendo al inicio");
    for (int i = 0; i < gamma; i++)
    {
      brazo1.write(beta--);
    }
  }
  Serial.println("Fin\n\n\n");
}