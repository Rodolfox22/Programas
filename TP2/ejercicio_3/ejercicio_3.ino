/*Realizar un programa en c++ que:
- solicite al usuario ingresar por teclado: nombre, apellido, edad y DNI
- almacene los valores introducidos en una matriz
- luego los imprima horizontalmente separados por una tabulación
*/

void esperarDato();
void imprimirDatos();
struct Datos
{
  String nombre;
  String apellido;
  int edad;
  long dni;
};

Datos datos;

void setup()
{
  Serial.begin(9600);
  Serial.println("Ingrese el nombre: ");
  esperarDato();
  if (Serial.available())
  {
    datos.nombre = Serial.readString();
  }

  Serial.println("Ingrese el apellido: ");
  esperarDato();
  if (Serial.available())
  {
    datos.apellido = Serial.readString();
  }

  Serial.println("Ingrese la edad: ");
  esperarDato();
  if (Serial.available())
  {
    datos.edad = Serial.parseInt();
  }

  Serial.println("Ingrese el DNI: ");
  esperarDato();
  if (Serial.available())
  {
    datos.dni = Serial.parseInt();
  }
  imprimirDatos();
}

void loop()
{
}

void esperarDato()
{
  while (!Serial.available())
  {
  }
}

void imprimirDatos()
{
  Serial.println("\n");
  Serial.print(datos.nombre);
  Serial.print("\t");
  Serial.print(datos.apellido);
  Serial.print("\t");
  Serial.print(datos.edad);
  Serial.print("\t");
  Serial.print(datos.dni);
  Serial.print("\t");
}