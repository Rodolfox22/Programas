// Interrupciones
/*Existen de tipo harware y software
Arduino UNO tiene 2 entradas de interrupciones--> 2 y 3
ESP32 todas las GPIO tienen interrupciones

Las interrupciones de software son temporizadores que realizan una funcion al finalizar el conteo, no lo estan integradas en una linea de código
*/

/* Cada rutina tiene un numero de operación, si en esa rutina existe una interrupcion, el programa ejecuta la interrupcion y al finalizar sigue ejecutando en la posicion que estuvo realizando antes de la interrupcion

Hay que tener cuidado con las variables que que se modifican en la interrupcion, ya que pede mandar error*/

/*En las interrupciones se deben utilizar funciones que no demanden mucho tiempo, como por ejemplo Serial.print(), ni gran cantidad de datos como matrices
Es necesario utilizar variables de tipo volatile ya que se va a modificar en varios lugares del programa*/

/*Lo primero que tego que definir es un pin de interrupcion*/

#define PIN_INTERRUPCION 2

volatile int interrupcion = 0;
volatile bool evento = 0;

void setup()
{
  // La forma adecuada de dar de alta el pin de interrupcion es utilizar la funcion digitalPinToInterrupt()
  // attachInterrupt(digitalPinToInterrupt(pin), function, mode);
  /*Modo:
  LOW se activa en 0
  RISSING se activa con el flanco ascendente
  FALLING se activa con el flanco descendente
  CHANGE se activa con ambos flancos
  HIGH, no disponile en arduino UNO, si en ESP
  Se utilizan los flancos para qu no se lea el bouncing mecanico de los pulsadores
  */
  attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPCION), ISR, FALLING);
}

void loop()
{
}

void ISR()
{
  interrupcion++;
  evento = !evento;
}

/*OTA over the air
sirve para actualizar el firmware del micro
solicita una pagina y actualiza el programa*/