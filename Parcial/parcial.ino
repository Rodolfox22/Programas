/* En thinkercad esta el circuito:
https://www.tinkercad.com/things/4UIilOzASQ1-copy-of-parcial-integrador-2023/editel?sharecode=miHhWJGy-nkXlX8eAezv1sGNDaTTRJgwcqFRmCSwF5w*/

/*UNIVERSIDAD NACIONAL DE RAFAELA
Grupo 1:
Alexis Gon
Juan Ocampo
Emiliano Soria
Pablo Correa

Carrera: Licenciatura en automatismos y robótica
Asignatura: Programacion
Profesor: Gustavo Castro*/

// Librerias utilizadas
#include <LiquidCrystal_I2C.h>

// Definiciones
#define A 2
#define BOT1 5
#define BOT10 6
#define MOTOR 3
#define RPV 159

#define MOTORON 0
#define MOTOROFF 1

// Inicializo objeto de pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile int conteo = 0;                   // Contador para el encoder
volatile unsigned long tiempoActual = 0;   // Visualiza el tiempo que demora en dar una vuelta el motor
int giros = 0, vueltas = 0, acumulado = 0; // Variables para el número de giros y vueltas y vueltas acumuladas
bool accion = false, primerPaso = true;    // Bandera para indicar si se debe iniciar una acción y el primer ciclo del programa
unsigned long tiempoVuelta = 0;            // Tiempo de vuelta

// Prototipos de las funciones
void encoder();
bool leerBotones();
void display();
void resetear();

void setup()
{

  // Configurar GPIOs
  pinMode(A, INPUT); // Canal A encoder motor
  pinMode(BOT1, INPUT);
  pinMode(BOT10, INPUT);
  pinMode(MOTOR, OUTPUT);
  digitalWrite(MOTOR, MOTOROFF);
  delay(2000);

  Serial.begin(9600);

  // Configurar pantalla LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Grupazo uno");

  // Configura la interrupción para el encoder
  attachInterrupt(digitalPinToInterrupt(A), encoder, RISING);
}

void loop()
{
  // Espera de activacion de botones
  if (!accion)
  {
    accion = leerBotones();
  }

  // Calcula el número de vueltas en base al conteo del encoder
  float calculo = float(conteo) / float(RPV);
  vueltas = int(calculo);

  // Actualiza los datos en la pantalla
  display();

  // Verifica si se ha alcanzado el número de vueltas requerido
  if (vueltas >= acumulado && acumulado != 0)
  {
    Serial.println("Motor stop");
    digitalWrite(MOTOR, MOTOROFF); // Detiene el motor
    accion = false;                // Reinicia la bandera de acción
    giros = 0;                     // Reinicia el número de giros

    // Espera a que se inicie una nueva acción
    while (!accion)
    {
      accion = leerBotones();
    }
  }
}

// Incrementa el contador del encoder
void encoder()
{
  conteo++;
  tiempoActual = millis() - tiempoVuelta;
}

// Verifica si se debe iniciar una acción
bool leerBotones()
{
  if (!digitalRead(BOT1))
  {
    giros = 1; // Configura el número de giros a 1
    acumulado++;
    resetear(); // Reinicia los valores
    return true;
  }

  if (!digitalRead(BOT10))
  {
    giros = 10; // Configura el número de giros a 10
    acumulado += 10;
    resetear(); // Reinicia los valores
    return true;
  }

  return false;
}

// Actualiza la pantalla LCD
void display()
{
  // Variables locales de control para evitar refrescos de display hasta un nuevo cambio
  static int muestraAnterior = -1;
  static int vueltaAnterior = -1;
  static bool accionAnterior = true;

  int vueltasActuales = vueltas;

  // Imprime el conteo del encoder en el puerto serie
  if (conteo != muestraAnterior)
  {
    muestraAnterior = conteo;
    Serial.println(conteo);
  }

  if (vueltasActuales != vueltaAnterior)
  {
    vueltaAnterior = vueltasActuales;
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Rev tot:");
    lcd.setCursor(11, 0);
    lcd.print(vueltasActuales); // Muestra el número de vueltas actual en la pantalla LCD

    lcd.setCursor(0, 1);
    lcd.print("R:");

    lcd.setCursor(2, 1);
    lcd.print(giros); // Muestra la cantidad de giros seteada

    lcd.setCursor(6, 1);
    lcd.print("T:");

    lcd.setCursor(8, 1);
    if (primerPaso)
    {
      tiempoActual = 0;
      primerPaso = false;
    }
    lcd.print(tiempoActual); // Muestra la cantidad de tiempo transcurrido entre vueltas

    lcd.setCursor(13, 1);
    lcd.print("ms");
  }
}

// Reinicia valores de control globales
void resetear()
{
  Serial.println("Valores a cero");
  tiempoVuelta = millis();
  Serial.println("Motor on");
  digitalWrite(MOTOR, MOTORON);
}
