#define Sal_analog 11

int valor = 1;

void setup()
{
  pinMode(Sal_analog, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  analogWrite(Sal_analog, valor);
  delay(1000);
  while (!Serial.available())
  {
  }
  valor = Serial.parseInt();
  Serial.println("Valor=" + String(valor));
}