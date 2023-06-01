/*Realizar un programa en framework de Arduino que:
- Solicite por medio del Monitor Serial que “Ingrese su Nombre y Apellido” y luego lo
imprima debajo en el Puerto Serial.
*/
String ingresar(String dato);
String filtrar(String palabra);
String capitalizar(String palabra);
bool esPresposicion(String preposicion);

void setup()
{
  String nombre_ejemplo = "maria de los anGEles dEL sagrado corazon de cristo";
  String apellido_ejemplo = "DEL BOSQUE";

  Serial.begin(9600);

  Serial.println("Ejemplo:\nIngrese nombre:\t\t" + nombre_ejemplo);
  Serial.println("Ingrese apellido:\t" + apellido_ejemplo);

  nombre_ejemplo = filtrar(nombre_ejemplo);
  apellido_ejemplo = filtrar(apellido_ejemplo);

  Serial.print("\nEl nombre ingresado es: ");
  Serial.println(nombre_ejemplo + apellido_ejemplo);
}

void loop()
{
  String nombre;
  String apellido;

  nombre = ingresar("nombre");
  apellido = ingresar("apellido");

  nombre = filtrar(nombre);
  apellido = filtrar(apellido);

  Serial.print("El nombre ingresado es: ");
  Serial.println(nombre + apellido);
}

String ingresar(String dato)
{
  Serial.print("\nIngrese ");
  Serial.println(dato + ":");
  while (!Serial.available())
  {
  }
  return Serial.readString();
}

String filtrar(String entrada)
{
  entrada.trim();
  int maxChar = 10;
  int ultChar[maxChar] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  String palabras[maxChar];
  int totPalabras = 0;

  // guardo los indices en una matriz
  for (int i = 0; i < maxChar; i++)
  {
    ultChar[i + 1] = entrada.indexOf(' ', ultChar[i] + 1);
  }

  // guardo las palabras en una matriz
  for (int j = 0; j < maxChar; j++)
  {
    if (ultChar[j] == -1)
    {
      break;
    }
    palabras[j] = entrada.substring(ultChar[j], ultChar[j + 1]);
    palabras[j].trim(); // Elimino espacios
    totPalabras++;      // Contabilizo las palabras ingresadas
  }

  // realizo capitalizar
  for (int i = 0; i < totPalabras; i++)
  {
    palabras[i].toLowerCase();
    if (!esPresposicion(palabras[i]) || i == 0)
    {
      palabras[i] = capitalizar(palabras[i]);
    }
  }

  entrada = "";

  // concateno palabras
  for (int k = 0; k < totPalabras; k++)
  {
    entrada += palabras[k] + " ";
  }

  return entrada;
}

// Capitaliza las palabras
String capitalizar(String palabra)
{
  char primera_letra;

  if (palabra.length())
  {
    primera_letra = palabra.charAt(0);
    primera_letra = toupper(primera_letra);
    palabra.setCharAt(0, primera_letra);
  }
  return palabra;
}

// Devuelve un uno si es una preposición
bool esPresposicion(String preposicion)
{
  int cantPreps = 5;
  String preposiciones[cantPreps] = {"del", "de", "los", "la", "las"};

  for (int preps = 0; preps < cantPreps; preps++)
  {
    if (preposicion == preposiciones[preps])
    {
      return 1;
    }
  }
  return 0;
}