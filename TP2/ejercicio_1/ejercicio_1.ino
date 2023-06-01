/*Dada el siguiente vector:
int matriz[]={23,12,3,4,5,67,100,2,44,32};
Realizar un programa que
- Imprima el “vector original: “ y el vector original
- Ordene el vector de menor a mayor el vector y lo guarde en un nuevo vector
- Imprima una nueva línea “vector ordenado: “ y el vector ordenado.
*/

#define VECTOR 10

int matriz[] = {23, 12, 3, 4, 5, 67, 100, 2, 44, 32};
int ordenado[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void ordenarMatriz();
void imprimirMatriz();

void setup()
{
  Serial.begin(9600);
  Serial.print("Vector original: ");
  imprimirMatriz();
  Serial.println("");
  Serial.print("Vector ordenado: ");
  ordenarMatriz();
  imprimirMatriz();
}

void loop()
{
}

void imprimirMatriz()
{
  for (int valor = 0; valor < VECTOR; valor++)
  {
    Serial.print(matriz[valor]);
    Serial.print("  ");
  }
}

void ordenarMatriz()
{
  int temporal;
  for (int i = 0; i < VECTOR - 1; i++)
  {
    for (int j = 0; j < VECTOR - i - 1; j++)
    {
      if (matriz[j] > matriz[j + 1])
      {
        // Intercambiar los elementos
        temporal = matriz[j];
        matriz[j] = matriz[j + 1];
        matriz[j + 1] = temporal;
      }
    }
  }
}
