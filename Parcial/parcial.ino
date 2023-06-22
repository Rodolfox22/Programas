/* En thinkercad esta el circuito:
https://www.tinkercad.com/things/4UIilOzASQ1-copy-of-parcial-integrador-2023/editel?sharecode=miHhWJGy-nkXlX8eAezv1sGNDaTTRJgwcqFRmCSwF5w*/

#include <LiquidCrystal_I2C.h>

#define A 2
#define BOT10 5
#define BOT100 6
#define MOTOR 3
#define RPV 159

LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile int conteo = 0;
int giros = 0, vueltas = 0;
bool accion = false;

unsigned long tiempoVuelta = 0;

void encoder();
bool leerBotones();
void display();
void resetear();

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Grupazo uno");

  pinMode(A, INPUT);
  pinMode(BOT10, INPUT);
  pinMode(BOT100, INPUT);
  pinMode(MOTOR, OUTPUT);

  delay(2000);
  attachInterrupt(digitalPinToInterrupt(A), encoder, RISING);
}

void loop()
{
  if (!accion)
  {
    accion = leerBotones();
  }
  
  vueltas = conteo / RPV;
  
  display();

  // Pregunta si se llegó a la cuenta
  if (vueltas >= giros && giros != 0)
  {
    Serial.println("Motor stop");
    digitalWrite(MOTOR, LOW);
    accion = false;
    giros = 0;
    while(!accion)
    {
      accion = leerBotones();
    }
  }
}

void encoder()
{
  conteo++;
}

bool leerBotones()
{
  if (digitalRead(BOT10))
  {
    giros = 10;
    resetear();
    return true;
  }

  if (digitalRead(BOT100))
  {
    giros = 100;
    resetear();
    return true;
  }

  return false;
}

void display()
{
  static int muestraAnterior = -1;
  static int vueltaAnterior = -1;
  static bool accionAnterior = true;
  
  int vueltasActuales = vueltas;
  String texto[2] = {"Off", "On "};

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
    lcd.print("Giros:");
    lcd.setCursor(10, 0);
    lcd.print(vueltasActuales);

    lcd.setCursor(1, 1);
    lcd.print("Tiempo:");
    lcd.setCursor(10, 1);
    lcd.print(millis() - tiempoVuelta);
  }

  if (accion != accionAnterior)
  {
    lcd.setCursor(13, 0);
    lcd.print(texto[accion]);
    accionAnterior = accion;
  }
}

void resetear()
{
  conteo = 0;
  digitalWrite(MOTOR, HIGH);
  tiempoVuelta = millis();
  Serial.println("Valores a cero");
  Serial.println("Motor on");
}
