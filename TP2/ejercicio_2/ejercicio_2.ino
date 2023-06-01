/*Realizar un programa en c++ que:
- solicite al usuario ingresar por teclado: nombre, apellido, edad y DNI
- almacene los valores introducidos en una matriz
- luego los imprima horizontalmente separados por una tabulación
*/

void esperarDato();

String datos[4];

void setup()
{
  Serial.begin(9600);
  Serial.println("Ingrese el nombre: ");
  esperarDato();
  if (Serial.available())
  {
    datos[0] = Serial.readString();
  }

  Serial.println("Ingrese el apellido: ");
  esperarDato();
  if (Serial.available())
  {
    datos[1] = Serial.readString();
  }

  Serial.println("Ingrese la edad: ");
  esperarDato();
  if (Serial.available())
  {
    datos[2] = Serial.readString();
  }

  Serial.println("Ingrese el DNI: ");
  esperarDato();
  if (Serial.available())
  {
    datos[3] = Serial.readString();
  }

  Serial.println("\n");

  for (int valor = 0; valor < 4; valor++)
  {
    Serial.print(datos[valor]);
    Serial.print("\t");
  }
}

void loop()
{
}

void esperarDato()
{
  while (Serial.available() == 0)
  {
  }
}