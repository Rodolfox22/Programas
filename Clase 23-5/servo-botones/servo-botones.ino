#include <Servo.h>

#define PIN_SERVO 10
#define BT_CCW 6
#define BT_CENTER 4
#define BT_CW 2

#define CCW 1
#define CENTER 0
#define CW 2
#define DELAY_BT 100
#define DELAY_MUESTREO 500

Servo superServo;
int mover(int modo, int pos);

int posicion = 90;
int posAnterior = 0;
unsigned long anterior = 0;
unsigned long anteriorBotones = 0;

void setup()
{
  int posServo = 0;
  
  Serial.begin(9600);
  superServo.attach(PIN_SERVO, 500, 2500);

  pinMode(BT_CCW, INPUT);
  pinMode(BT_CENTER, INPUT);
  pinMode(BT_CW, INPUT);

  superServo.write(posicion);
  posServo = superServo.read();
  Serial.println(posServo);

  while (posicion != 90)
  {
    posServo = superServo.read();
    Serial.print(".");
  }
  Serial.println(".");

}

void loop()
{
  int posActual = 0;
  superServo.write(posicion);
  posActual = superServo.read();

  if (millis() - anteriorBotones >= DELAY_BT)
  {
    anteriorBotones = millis();

    if (!digitalRead(BT_CENTER))
    {
      posicion = mover(CENTER, posicion);
    }

    if (!digitalRead(BT_CCW))
    {
      posicion = mover(CCW, posicion);
    }

    if (!digitalRead(BT_CW))
    {
      posicion = mover(CW, posicion);
    }
  }

  if (millis() - anterior >= DELAY_MUESTREO)
  {
    anterior = millis();

    // Este if se agrega para no sobrecargar el puerto serie con datos repetidos
    if (posAnterior != posActual)
    {
      Serial.println(posActual);
      posAnterior = posActual;
    }
  }
}

int mover(int modo, int pos)
{
  String movimiento[3] = {"Al centro", "Derecha", "Izquierda"};

  switch (modo)
  {
  case CENTER:
    pos = 90;
    break;

  case CCW:
    pos -= 10;
    break;

  case CW:
    pos += 10;
    break;

  default:
    break;
  }

  Serial.println(movimiento[modo]);
  pos = max(0, min(pos, 180));

  return pos;
}
