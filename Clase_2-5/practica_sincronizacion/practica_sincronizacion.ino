#define CANTLED 6

unsigned long ultimo_millis[CANTLED] = {0, 0, 0, 0, 0, 0};
bool estado_led[CANTLED] = {0, 0, 0, 0, 0, 0};
bool valor_anterior[CANTLED] = {0, 0, 0, 0, 0, 0};
int salidas[CANTLED] = {8, 9, 10, 11, 12, 13};
String estado[] = {" apagado", " encendido"};
int maximo[2] = {0, 0};

void parpadeo(int led, int tiempo);
void detener();
void detener(int miliseg);

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < CANTLED; i++)
  {
    pinMode(salidas[i], OUTPUT);
  }
}

void loop()
{
  parpadeo(0, 125);
  parpadeo(1, 250);
  parpadeo(2, 500);
  parpadeo(3, 1000);
  parpadeo(4, 2000);
  parpadeo(5, 4000);
  // detener();
  // detener(30000);
}
// Con esta funcion quiero decir que si este led esta en flanco descendente, active el siguiente
void activarLed(int actual)
{
  int siguiente = 0;
  if (actual == CANTLED)
  {
    siguiente = 0;
  }
  else
  {
    siguiente++;
  }
}

void parpadeo(int led, int tiempo)
{
  if (millis() - ultimo_millis[led] >= tiempo)
  {
    ultimo_millis[led] = millis();
    int tiempo_perdido = ultimo_millis[led] % tiempo;
    if (maximo[0] < tiempo_perdido)
    {
      maximo[0] = tiempo_perdido;
      maximo[1] = salidas[led];
    }
    Serial.print(String(tiempo_perdido) + "\t");
    ultimo_millis[led] -= tiempo_perdido;
    Serial.print(ultimo_millis[led]);
    estado_led[led] = !estado_led[led];
    digitalWrite(salidas[led], estado_led[led]);
    Serial.print("\tEstado led ");
    Serial.print(salidas[led]);
    Serial.println(estado[estado_led[led]]);
  }
}

// El programa se detiene cuando se encienden todos los leds
void detener()
{
  int suma = 0;
  for (int j = 0; j < CANTLED; j++)
  {
    suma += estado_led[j];
  }

  // if (suma == CANTLED)
  {
    Serial.print(String(maximo[0]) + "\t");
    Serial.print(maximo[1]);
    Serial.println("\tEl programa se detuvo");
    while (1)
    {
    }
  }
  suma = 0;
}

// El programa se detiene luego de x milisegundos
void detener(int miliseg)
{
  int suma = 0;
  for (int j = 0; j < CANTLED; j++)
  {
    suma += estado_led[j];
  }

  if (millis() >= miliseg)
  {
    Serial.print(String(maximo[0]) + "\t");
    Serial.print(maximo[1]);
    Serial.println("\tEl programa se detuvo");
    while (1)
    {
    }
  }
  suma = 0;
}