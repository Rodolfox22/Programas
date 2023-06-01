// Realizar un programa que imprima en pantalla los números enteros del 0 al 9, uno debajo de otro en líneas distintas.

void setup()
{
  Serial.begin(9600);
  for (int i = 1; i < 10; i++)
  {
    Serial.print(String(i) + "\n\n");
  }
}

void loop()
{
}