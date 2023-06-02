/*Realizar un programa que al introducir por teclado en el terminal serie un valor de ángulo en º, el motor paso a paso gire esa cantidad de grados hacia la derecha, y si ingresa un número de grados con signo negativo, gire la cantidad de grados en forma anti-horaria*/

#define PASOS_PV 2048
#define RPM 10
#define CANTPASOS 8

#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5

void moverPasos(int pasos);
void contarVueltas(int posicion);
int moverDerecha(int restantes, int anteriorPaso);
int moverIzquierda(int restantes, int anteriorPaso);
void salida(int step);

int posicion = 0, anterior = 0, vuelta = 0;
float factorConversionGP = 0.0;
int matrizPasos[CANTPASOS] = {B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001};
// int matrizPasos[CANTPASOS] = {B1000, B0100, B0010, B0001};
unsigned long demora = 0;

void setup()
{
  Serial.begin(9600);

  // Incicializamos pines
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);

  // Calculamos constantes
  factorConversionGP = float(PASOS_PV) / 360.0;
  demora = PASOS_PV * 1000 / RPM / 60;
}

void loop()
{
  // Leemos puerto
  if (Serial.available())
  {
    int lectura = Serial.parseInt();
    posicion += lectura;
    lectura *= factorConversionGP; // Conversion de grados a pasos
    moverPasos(lectura);
  }

  // Imprimimos posicion
  contarVueltas(posicion);
}

// Imprimir en puerto la posicion del servo
void contarVueltas(int grados)
{
  if (grados < 0)
  {
    grados += 360;
    vuelta--;
  }

  if (grados > 360)
  {
    grados -= 360;
    vuelta++;
  }

  if (grados != anterior)
  {
    anterior = grados;
    Serial.print("Posicion: ");
    Serial.print(grados);
    Serial.print(" grados.\tVuelta:");
    Serial.println(vuelta);
  }
}

// Selecciono hacia que lado gira el servo y le indico la cantidad de pasos que debe girar
void moverPasos(int pasos)
{
  int pasosRestantes = abs(pasos);
  static int ultimoPaso = 0;
  if (pasos > 0)
  {
    ultimoPaso = moverDerecha(pasosRestantes, ultimoPaso);
    return;
  }
  ultimoPaso = moverIzquierda(pasosRestantes, ultimoPaso);
}

// Girar a la izquierda
int moverIzquierda(int restantes, int anteriorPaso)
{
  for (int i = 0; i < restantes; i++)
  {
    anteriorPaso++;
    if (anteriorPaso > CANTPASOS - 1)
    {
      anteriorPaso = 0;
    }
    salida(anteriorPaso);
    Serial.println(anteriorPaso);
    delay(demora);
  }
  return anteriorPaso;
}

// Girar a la derecha
int moverDerecha(int restantes, int anteriorPaso)
{
  for (int i = restantes; i > 0; i--)
  {
    anteriorPaso--;
    if (anteriorPaso < 0)
    {
      anteriorPaso = CANTPASOS - 1;
    }
    salida(anteriorPaso);
    Serial.println(anteriorPaso);
    delay(demora);
  }
  return anteriorPaso;
}

//Setea las GPIO
void salida(int step)
{
  digitalWrite(PIN_1, bitRead(matrizPasos[step], 0));
  digitalWrite(PIN_2, bitRead(matrizPasos[step], 1));
  digitalWrite(PIN_3, bitRead(matrizPasos[step], 2));
  digitalWrite(PIN_4, bitRead(matrizPasos[step], 3));
}