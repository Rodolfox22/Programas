// C++ code
//

#define ARRX 3
#define ARRY 3

int entero = 99;
int a = 9, b = 10;
float flotante = 6.99998;
char nombre[] = "Lalo";
int array[ARRX][ARRY] = {{2, 1, 0}, {3, 2}, {7}};

unsigned long tiempoAnterior = millis();
unsigned long tiempo = 500;
bool estado = 0;

void impresionArray();

void setup()
{
  Serial.begin(9600);
  float resultado = float(entero) + flotante;

  Serial.println("Valor entero\t: " + String(entero));
  Serial.println("Valor flotante\t: " + String(flotante));
  Serial.println("Suma\t\t: " + String(resultado));

  Serial.println("\nchar Array\t: " + String(nombre) + "\n");

  impresionArray();

  int c = entero / b;
  Serial.println("El entero dividido en b es: " + String(c));
  float e = float(entero) / float(b);
  Serial.println("El entero dividido en b es: " + String(e));
  int d = entero % a;
  Serial.print("El modulo del entero es: " + String(d));
  Serial.println();

  array[1][2] = 99;
  array[2][1] = 54;
  array[2][2] = -1;

  impresionArray();
}

void loop()
{
  Serial.print("Ingrese datos: ");
  while (Serial.avaliable() == 0)
  {
  }
  String datoStr=Serial.readString();
  Serial.println(datoStr);
  datoStr.trim();
  long numero=datoStr.toInt();
  if (numero==0)
  {
    Serial.println("El valor ingresado es cero o caracter.");
  }
  else
  {
    Serial.println("El valor ingresado es distinto de cero.")
  }
  
}

void impresionArray()
{

  for (int i = 0; i < ARRY; i++)
  {
    for (int j = 0; j < ARRX; j++)
    {
      Serial.print(String(array[i][j]));
      if (j < ARRY - 1)
        Serial.print("\t");
    }
    Serial.println();
  }
}