#define A 2
#define B 4

int anterior = 0;

void encoder();

volatile int conteo = 50;

void setup()
{
  Serial.begin(9600);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  attachInterrupt(digitalPinToInterrupt(A), encoder, FALLING);
}

void loop()
{
  if (conteo != anterior)
  {
    conteo = max(0, min(conteo, 100));
    anterior = conteo;
    Serial.println(conteo);
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