/*Realizar un programa que al introducir por teclado en el terminal serie un valor de ángulo en º, el motor paso a paso gire esa cantidad de grados hacia la derecha, y si ingresa un número de grados con signo negativo, gire la cantidad de grados en forma anti-horaria*/
#define PASOS_PV 2048
#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5
#define RPM 10

bool moverPasos(int pasos);
void contarVueltas(int posicion);

int posicion = 0, anterior = 0, vuelta = 0;
float factorConversionGP = float(PASOS_PV) / 360.0;
int fase = 8;
int fase8pasos[fase] = {1000, 1100, 0100, 0110, 0010, 0011, 0001, 1001};

void setup()
{
  Serial.begin(9600);

  // Incicializamos pines
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);
}

void loop()
{

  if (Serial.available())
  {
    int lectura = Serial.parseInt();
    posicion += lectura;
    lectura *= factorConversionGP; // Conversion de grados a pasos
    moverPasos(lectura);
  }
  contarVueltas(posicion);
}

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
    Serial.print("Posicion: " + String(grados) + " grados.");
    Serial.println("\tVuelta:" + String(vuelta));
  }
}

int moverDerecha(int restantes, int anteriorPaso);
int moverDerecha(int restantes, int anteriorPaso);
int moverDerecha(int restantes, int anteriorPaso){}

/*
int stepCounter = 0;    // contador para los pasos
int stepsPerRev = 4076; // pasos para una vuelta completa


void loop()
{
  for (int i = 0; i < stepsPerRev * 2; i++)
  {
    clockwise();
    delayMicroseconds(motorSpeed);
  }
  for (int i = 0; i < stepsPerRev * 2; i++)
  {
    anticlockwise();
    delayMicroseconds(motorSpeed);
  }
  delay(1000);
}

void clockwise()
{
  stepCounter++;
  if (stepCounter >= numSteps)
    stepCounter = 0;
  setOutput(stepCounter);
}

void anticlockwise()
{
  stepCounter--;
  if (stepCounter < 0)
    stepCounter = numSteps - 1;
  setOutput(stepCounter);
}

void setOutput(int step)
{
  digitalWrite(motorPin1, bitRead(stepsLookup[step], 0));
  digitalWrite(motorPin2, bitRead(stepsLookup[step], 1));
  digitalWrite(motorPin3, bitRead(stepsLookup[step], 2));
  digitalWrite(motorPin4, bitRead(stepsLookup[step], 3));
}
*/