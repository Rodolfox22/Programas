/*Realizar un programa que:
- Declare e Inicialice un vector con su nombre y apellido como contenido.
- Imprima dicho vector en pantalla.
- Debajo imprima el texto “Cantidad de A en el texto: “ y luego al lado imprima la cantidad de dicha vocal que contenga el vector.
- Debajo imprima el texto “Cantidad de E en el texto: “ y luego al lado imprima la cantidad de dicha vocal que contenga el vector.
- Debajo imprima el texto “Cantidad de I en el texto: “ y luego al lado imprima la cantidad de dicha vocal que contenga el vector.
- Debajo imprima el texto “Cantidad de O en el texto: “ y luego al lado imprima la cantidad de dicha vocal que contenga el vector.
- Debajo imprima el texto “Cantidad de U en el texto: “ y luego al lado imprima la cantidad de dicha vocal que contenga el vector.
*/

#define LARGONOM 13

char nombre[LARGONOM] = "PABLO CORREA";
char vocales[] = "AIEOU";
int contar[] = {0, 0, 0, 0, 0};

void setup()
{
  Serial.begin(9600);
  for (int j = 0; j < LARGONOM; j++)
  {
    if (nombre[j] != '\0')
    {
      Serial.print(nombre[j]);

      for (int k = 0; k < 5; k++)
      {
        if (nombre[j] == vocales[k])
        {
          contar[k]++;
        }
      }
    }
  }
  Serial.println("");
  for (int letra = 0; letra < 5; letra++)
  {
    Serial.print("Cantidad de: ");
    Serial.print(vocales[letra]);
    Serial.print(" en el texto: ");
    Serial.println(contar[letra]);
  }
}

void loop()
{
}