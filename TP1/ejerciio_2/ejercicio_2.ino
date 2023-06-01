/*Realizar un programa que:
- imprima en pantalla en una línea los números enteros del 0 al 9, uno al lado de otro, separados por dos lugares vacíos.
- Debajo de lo solicitado anteriormente, que imprima en pantalla en una línea los números enteros del 9 al 0, uno al lado de otro, separados por dos lugares vacíos.
*/
void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 10; i++)
  {
    Serial.print(i);
    if (i < 9)
    {
      Serial.print("  ");
    }
  }

  Serial.print("\n\n");

  for (int j = 9; j >= 0; j--)
  {
    Serial.print(j);
    if (j > 0)
    {
      Serial.print("\n\n");
    }
  }
  Serial.print();
}

void loop()
{
}