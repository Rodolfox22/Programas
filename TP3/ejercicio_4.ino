/*Realizar un programa en framework de Arduino que:
- evalúe los años del 1970 al 2022 e imprima en terminal serial los años que fueron bisiestos. Tener en cuenta que para que el año sea bisiesto se debe dar la siguiente condición:
*/

#define VISUALIZAR 5

bool multiplo(int num, int multiplo);
int muestreo(int dato);

int fechaInicio = 1970;
int fechaFin = 2022;

int mostrar = 0;

void setup()
{
  Serial.begin(9600);

  bool xx4 = 0;
  bool xx100 = 0;
  bool xx400 = 0;

  for (int i = fechaInicio; i <= fechaFin; i++)
  {
    xx4 = multiplo(i, 4);
    xx100 = multiplo(i, 100);
    xx400 = multiplo(i, 400);

    if (xx4 && !(xx100 ^ xx400))
    {
      Serial.print(String(i) + "\t");
      mostrar++;
    }

    mostrar = muestreo(mostrar);
  }
  muestreo(VISUALIZAR);
  muestreo(VISUALIZAR);
  Serial.println(String (millis()) + " milisegundos de ejecucion");
}

void loop()
{
}

// Devuelve si un numero es multiplo o no
bool multiplo(int num, int multiploNum)
{
  if (num % multiploNum == 0)
  {
    return 1;
  }
  return 0;
}

// Devuelve si llegó la cuenta al valor visualizar
int muestreo(int dato)
{
  if (dato == VISUALIZAR)
  {
    Serial.print("\n");
    return 0;
  }
  return dato;
}