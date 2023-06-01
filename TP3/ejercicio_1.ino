/*Realizar un programa en framework de Arduino que:
-	evalúe los números del 1 al 99 e imprima en terminal serial los números pares.
*/
#define MULTIPLO 2
#define VISUALIZAR 5

int mostrar = 0;

void setup()
{
  Serial.begin(9600);
  for (int i = 1; i <= 99; i++)
  {
    if (i % MULTIPLO == 0)
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