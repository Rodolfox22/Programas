/* En thinkercad esta el circuito:
https://www.tinkercad.com/things/4UIilOzASQ1-copy-of-parcial-integrador-2023/editel?sharecode=miHhWJGy-nkXlX8eAezv1sGNDaTTRJgwcqFRmCSwF5w*/

#include <LiquidCrystal_I2C.h>

#define A 2
#define BOT10 5
#define BOT100 6
#define MOTOR 3
#define RPV 159

LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile int conteo = 0;    // Contador para el encoder
int giros = 0, vueltas = 0; // Variables para el número de giros y vueltas
bool accion = false;        // Bandera para indicar si se debe iniciar una acción

unsigned long tiempoVuelta = 0; // Tiempo de vuelta

//Prototipos de las funciones
void encoder();
bool leerBotones();
void display();
void resetear();

void setup()
{
  Serial.begin(9600);

  //Configurar pantalla LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Grupazo uno");

  //Configurar GPIOs
  pinMode(A, INPUT);
  pinMode(BOT10, INPUT);
  pinMode(BOT100, INPUT);
  pinMode(MOTOR, OUTPUT);

  delay(2000);

  // Configura la interrupción para el encoder
  attachInterrupt(digitalPinToInterrupt(A), encoder, RISING);
}

void loop()
{
  if (!accion)
  {
    accion = leerBotones();
  }

  vueltas = conteo / RPV; // Calcula el número de vueltas en base al conteo del encoder

  display();

  // Verifica si se ha alcanzado el número de vueltas requerido
  if (vueltas >= giros && giros != 0)
  {
    Serial.println("Motor stop");
    digitalWrite(MOTOR, LOW); // Detiene el motor
    accion = false;           // Reinicia la bandera de acción
    giros = 0;                // Reinicia el número de giros
    while (!accion)
    {
      accion = leerBotones(); // Espera a que se inicie una nueva acción
    }
  }
}

// Incrementa el contador del encoder
void encoder()
{
  conteo++;
}

// Verifica si se debe iniciar una acción
bool leerBotones()
{
  if (digitalRead(BOT10))
  {
    giros = 10; // Configura el número de giros a 10
    resetear(); // Reinicia los valores
    return true;
  }

  if (digitalRead(BOT100))
  {
    giros = 100; // Configura el número de giros a 100
    resetear();  // Reinicia los valores
    return true;
  }

  return false;
}

// Actualiza la pantalla LCD
void display()
{
  static int muestraAnterior = -1;
  static int vueltaAnterior = -1;
  static bool accionAnterior = true;

  int vueltasActuales = vueltas;
  String texto[2] = {"Off", "On "}; // Texto para mostrar el estado de la acción

  if (conteo != muestraAnterior)
  {
    muestraAnterior = conteo;
    Serial.println(conteo); // Imprime el conteo del encoder
  }

  if (vueltasActuales != vueltaAnterior)
  {
    vueltaAnterior = vueltasActuales;
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Giros:");
    lcd.setCursor(10, 0);
    lcd.print(vueltasActuales); // Muestra el número de vueltas actual en la pantalla LCD

    lcd.setCursor(1, 1);
    lcd.print("Tiempo:");
    lcd.setCursor(10, 1);
    lcd.print(millis() - tiempoVuelta); // Calcula y muestra el tiempo de vuelta en la pantalla LCD
    lcd.setCursor(13, 0);
    lcd.print(texto[accion]);
  }

  if (accion != accionAnterior)
  {
    lcd.setCursor(13, 0);
    lcd.print(texto[accion]); // Muestra el estado de la acción (On/Off) en la pantalla LCD
    accionAnterior = accion;
  }
}

// Reinicia valores de control
void resetear()
{
  Serial.println("Valores a cero");
  conteo = 0;
  tiempoVuelta = millis();
  Serial.println("Motor on");
  digitalWrite(MOTOR, HIGH);
}
