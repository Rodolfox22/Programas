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

volatile int conteo = 0, muestraAnterior = -1;                   // Contador para el encoder
volatile unsigned long tiempoActual = 0;                         // Visualiza el tiempo que demora en dar una vuelta el motor
int giros = 0, acumulado = 0, vueltas = 0, vueltasActuales = -1; // Variables para el número de giros y vueltas y vueltas acumuladas
bool accion = false, primerPaso = true;                          // Bandera para indicar si se debe iniciar una acción y el primer ciclo del programa
unsigned long tiempoVuelta = 0;                                  // Tiempo de vuelta

// Prototipos de las funciones
void encoder();
int calcular();
bool leerBotones();
void pantalla();
void actualizarGiros();
void actualizarVueltas();
void resetear();
void detenerMotor();

void setup()
{

  // Configurar GPIOs
  pinMode(A, INPUT);             // Canal A encoder motor
  pinMode(BOT1, INPUT);          // Boton de una vuelta
  pinMode(BOT10, INPUT);         // Boton de 10 vueltas
  pinMode(MOTOR, OUTPUT);        // Motor
  digitalWrite(MOTOR, MOTOROFF); // Inicializando motor

  Serial.begin(9600);

  // Configurar pantalla LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Grupazo uno");
  delay(2000);

  // Inicializa la impresion de valores
  pantalla();

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
  vueltas = calcular();

  // Actualiza los datos en la pantalla
  actualizarVueltas();

  // Verifica si se ha alcanzado el número de vueltas requerido
  detenerMotor();

  // Imprime el conteo del encoder en el puerto serie
}

// Incrementa el contador del encoder
void encoder()
{
  conteo++;
  tiempoActual = millis() - tiempoVuelta;
}

// Calcula el número de vueltas en base al conteo del encoder
int calcular()
{
  float calculo = float(conteo) / float(RPV);
  return int(calculo);
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
void pantalla()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Rev tot:");

  lcd.setCursor(0, 1);
  lcd.print("R:");

  lcd.setCursor(6, 1);
  lcd.print("T:");

  lcd.setCursor(13, 1);
  lcd.print("ms");

  actualizarGiros();
  actualizarVueltas();
}

// Acualiza datos de variables en pantalla
void actualizarGiros()
{
  lcd.setCursor(2, 1);
  lcd.print(giros); // Muestra la cantidad de giros seteada
}

// Acualiza datos de variables en pantalla
void actualizarVueltas()
{
  if (conteo != muestraAnterior)
  {
    Serial.println(conteo);
    muestraAnterior = conteo;
  }

  if (vueltas != vueltasActuales)
  {
    vueltasActuales = vueltas;
    lcd.setCursor(11, 0);
    lcd.print(vueltas); // Muestra el número de vueltas actual en la pantalla LCD

    lcd.setCursor(8, 1);
    if (primerPaso)
    {
      tiempoActual = 0;
      primerPaso = false;
    }
    lcd.print(tiempoActual); // Muestra la cantidad de tiempo transcurrido entre vueltas
  }
}

// Reinicia valores de control globales
void resetear()
{
  Serial.println("Valores a cero");
  tiempoVuelta = millis();
  Serial.println("Motor on");
  digitalWrite(MOTOR, MOTORON);
  actualizarGiros();
}

// Detiene el motor y configura para un nuevo ciclo
void detenerMotor()
{
  if (vueltas == acumulado && accion)
  {
    Serial.print("Motor off. ");
    Serial.print("Acumulado: ");
    Serial.println(acumulado);
    digitalWrite(MOTOR, MOTOROFF); // Detiene el motor
    accion = false;                // Reinicia la bandera de acción
    giros = 0;                     // Reinicia el número de giros
  }
}