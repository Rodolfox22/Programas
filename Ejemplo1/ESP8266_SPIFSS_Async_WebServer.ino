#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
//#include <Wire.h>

#include "instrucciones.h"

/*
const char *ssid = "xxxxxxxxx";
const char *password = "yyyyyyy";
*/

const char *ssid = "UNRaf_Libre";
const char *password = "unraf2021";

const char *ssid_AP = "Triciclo";
const char *password_AP = "unraf2022";

IPAddress ip(192, 168, 0, 10);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

const int Rele_Pin = 2;

unsigned long demora = 0;
unsigned long tiempo_solicitud = 5000;

String Estado_Pin;
String Velocidad = "10";
/*
 int num_Velocidad = 0;
 String Carga = "20";
 String Temp_bat = "35";
 String Retroceso;
 String Humedad = "75";
 String Temperatura = "10";
 String Trip = "52";
 String Odometro = "720";
 String Temporal;*/

AsyncWebServer server(80);

String processor(const String &var)
{

  if (var == "ESTADO_RELE")
  {
    if (digitalRead(Rele_Pin) == 0)
    {
      Estado_Pin = "Encendido";
    }
    else
    {
      Estado_Pin = "Apagado";
    }
    return Estado_Pin;
  }

  if (var == "VEL")
  {
    Serial.print("Velocidad: ");
    Serial.println(Velocidad);
    return Velocidad;
  }
  if (var == "ACT")
  {
    Serial.print("Velocidad: ");
    Serial.println(Velocidad);
    return actualizar;
  }
  /*
    if (var == "HUMEDAD")
    {
      Serial.print("Velocidad: ");
      Serial.println(Humedad);
      return Humedad;
    }

    if (var == "TEMP_BAT")
    {
      Serial.print("Temperatura bateria: ");
      Serial.println(Temp_bat);
      return Temp_bat;
    }

    if (var == "TEMPERATURA")
    {
      Serial.print("Temperatura: ");
      Serial.println(Temperatura);
      return Temperatura;
    }

    if (var == "RETROCESO")
    {
      return Retroceso;
    }

    if (var == "CARGA")
    {
      Serial.print("Carga: ");
      Serial.println(Carga);
      return Carga;
    }
    if (var == "ODOMETRO")
    {
      Serial.print("Odometro: ");
      Serial.println(Odometro);
      return Odometro;
    }
    if (var == "TRIP")
    {
      Serial.print("Trip: ");
      Serial.println(Trip);
      return Trip;
    }*/
}

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(Rele_Pin, OUTPUT);

  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  // Inicio I2C
  // Wire.begin();

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

  // Modo Acces point
  /*
      WiFi.mode(WIFI_AP);
      WiFi.softAP(ssid_AP, password_AP);

      Serial.print("Servidor: ");
      Serial.println(WiFi.softAPIP());
      Serial.print("Local: ");
      Serial.println(WiFi.localIP());
      delay(1000);
    */

  // TODO como conectar directamente? necesita una instruccion especial para que funcione como servidor?

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", String(), false, processor); });

  /*Por el momento no cargo el archivo CSS para que analizar en profundidad la funcionalidad
  // Route to load style.css file
  server.on("/estilos.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/estilos.css", "text/css"); });*/

  // Route to load main.js file
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/main.js", "text/js"); });

  // Route to set GPIO to HIGH
  server.on("/RELE=ON", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    digitalWrite(Rele_Pin, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor); });

  // Route to set GPIO to LOW
  server.on("/RELE=OFF", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    digitalWrite(Rele_Pin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor); });

  /*// Route to set GPIO to CHANGE
  server.on("/RELE=CHANGE", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if (digitalRead(Rele_Pin)==0)
      digitalWrite(Rele_Pin, HIGH);
    else
      digitalWrite(Rele_Pin, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor); });
*/

  /*
    server.on("/TEMP_BAT", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      //Temp_bat = leerDato('T');
      request->send(SPIFFS, "/index.html", String(), false, processor); });

    server.on("/TEMPERATURA", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      //Temperatura = leerDato('U');
      request->send(SPIFFS, "/index.html", String(), false, processor); });

    server.on("/HUMEDAD", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      //Humedad = leerDato('H');
      request->send(SPIFFS, "/index.html", String(), false, processor); });*/

  server.on("/VEL", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    /*Serial.println(millis());
if (millis()-demora>=tiempo_solicitud)
{
demora = millis();
num_Velocidad ++;
if (num_Velocidad >= 25)
{
num_Velocidad = 1;
}*/
    Velocidad = String(num_Velocidad);
  }

    request->send(SPIFFS, "/index.html", String(), false, processor);
});
/*
    server.on("/RETROCESO", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      //Retroceso = leerDato('R');
      request->send(SPIFFS, "/index.html", String(), false, processor); });

    server.on("/CARGA", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      //Carga = leerDato('C');
      request->send(SPIFFS, "/index.html", String(), false, processor); });
    server.begin();
  */
}

void loop()
{
}
