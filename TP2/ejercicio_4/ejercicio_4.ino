/*IDEM ejercicio nº2, pero ahora solicitando los datos de 5 personas, y luego imprimiéndolos con el mismo formato anterior , pero los datos de una persona debajo de otro. */

#define CANTDATOS 5

void esperarDato();
void ingresarDatos(int posicion);
void imprimirDatos(int imprimirPosicion);

struct Datos
{
  String nombre;
  String apellido;
  int edad;
  long dni;
};

Datos datos[CANTDATOS];

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < CANTDATOS; i++)
  {
    Serial.println("Ingrese los datos del alumno: "+String(i));
    ingresarDatos(i);
  }

  for (int j = 0; j < CANTDATOS; j++)
  {
    imprimirDatos(j);
  }
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

void ingresarDatos(int posicion)
{
  Serial.println("Ingrese el nombre: ");
  esperarDato();
  if (Serial.available())
  {
    datos[posicion].nombre = Serial.readString();
  }

  Serial.println("Ingrese el apellido: ");
  esperarDato();
  if (Serial.available())
  {
    datos[posicion].apellido = Serial.readString();
  }

  Serial.println("Ingrese la edad: ");
  esperarDato();
  if (Serial.available())
  {
    datos[posicion].edad = Serial.parseInt();
  }

  Serial.println("Ingrese el DNI: ");
  esperarDato();
  if (Serial.available())
  {
    datos[posicion].dni = Serial.parseInt();
  }
}

void imprimirDatos(int imprimirPosicion)
{
  Serial.println("\n");
  Serial.print(datos[imprimirPosicion].nombre);
  Serial.print("\t");
  Serial.print(datos[imprimirPosicion].apellido);
  Serial.print("\t");
  Serial.print(datos[imprimirPosicion].edad);
  Serial.print("\t");
  Serial.print(datos[imprimirPosicion].dni);
  Serial.print("\t");
}