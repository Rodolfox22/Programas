/*Realizar un programa en framework de Arduino que:
- evalúe los números del 1 al 199 y imprima en terminal serial los números múltiplos de 5, pero no los imprima sin son múltiplos de 10.

*/

#define VISUALIZAR 4

int mostrar = 0;

void setup()
{
  Serial.begin(9600);
  for (int i = 1; i <= 199; i++)
  {
    if (i % 5 == 0 && i % 10 != 0)
    {
      Serial.print(String(i) + "\t");
      mostrar++;
    }

    if (VISUALIZAR == mostrar)
    {
      Serial.print("\n");
      mostrar = 0;
    }
  }
}

void loop()
{
}