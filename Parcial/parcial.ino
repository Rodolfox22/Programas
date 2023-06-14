#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define A 2
#define BOT10 5
#define BOT100 6
#define MOTOR 3
#define RPV 159

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

void encoder();
int vueltas(int pulsos);
bool leerBotones();
void display();

int anterior = 0;
int giros = 0;

volatile int conteo = 0;
unsigned long tiempoVuelta = 0;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backLight();
  /*
  lcd.begin(16,2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  */
  lcd.setCursor(2, 0);
  lcd.print("Grupazo uno");

  pinMode(A, INPUT);
  pinMode(BOT10, INPUT);
  pinMode(BOT100, INPUT);
  pinMode(MOTOR, OUTPUT);

  delay(2000);
  attachInterrupt(digitalPinToInterrupt(A), encoder, FALLING);
}

void loop()
{
  static bool accion = false;
  if (!accion)
  {
    accion = leerBotones();
  }

  display();

  // Pregunta si se llego a la cuenta
  if (vueltas(conteo) >= giros)
  {
    digitalWrite(MOTOR, LOW);
    accion = false;
    giros = 0;
  }
}

void encoder()
{
  static unsigned long tiempoFiltro = 0;
  if (millis() - tiempoFiltro >= 5)
  {
    conteo++;
    tiempoFiltro = millis();
  }
}

int vueltas(int pulsos)
{
  return pulsos / RPV;
}

bool leerBotones()
{
  if (digitalRead(BOT10))
  {
    giros = 10;
    conteo = 0;
    digitalWrite(MOTOR, HIGH);
    tiempoVuelta = millis();
    return true;
  }

  if (digitalRead(BOT100))
  {
    giros = 100;
    conteo = 0;
    digitalWrite(MOTOR, HIGH);
    tiempoVuelta = millis();
    return true;
  }

  return false;
}

void display()
{
  static unsigned long muestreo = 0;

  if (millis() - muestreo >= 500)
  {
    Serial.println(conteo);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Giros:");
    lcd.setCursor(10, 0);
    lcd.print(vueltas(conteo));

    lcd.setCursor(0, 1);
    lcd.print("Tiempo:");
    lcd.setCursor(10, 1);
    lcd.print(millis() - tiempoVuelta);

    muestreo = millis();
  }
}