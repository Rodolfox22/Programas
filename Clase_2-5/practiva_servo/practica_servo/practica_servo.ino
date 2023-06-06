#include <Servo.h>
#define PINSERVO 9

void avanzarHasta(int posicion);

int beta = 0;

Servo brazo1;

void setup()
{
  Serial.begin(9600);
  pinMode(PINSERVO, OUTPUT);
  brazo1.attach(PINSERVO);
  brazo1.write(beta);
}

void loop()
{
  
  if (Serial.available())
  {
    brazo1.attach(PINSERVO);
    beta = Serial.parseInt();
    Serial.print("Angulo ingresado: ");
    Serial.println(beta);
    avanzarHasta(beta);
    String resto = Serial.readString();
    brazo1.detach();
  }
}

void avanzarHasta(int posicion)
{
  int actual = brazo1.read();
  Serial.print(actual);
  if(actual >= posicion)
  {
    Serial.print(" mayor que ");
    Serial.println(posicion);
    for(int i = actual;i >= posicion; i--)
    {
      brazo1.write(i);
      delay(10);
      Serial.print(".");
    }
    Serial.println(".");
    return;
  }

  if(actual < posicion)
  {
    Serial.print(" menor que ");
    Serial.println(posicion);
    for(int i = actual;i <= posicion; i++)
    {
      brazo1.write(i);
      delay(10);
      Serial.print(".");
    }
    Serial.println(".");
    return;
  }
}
