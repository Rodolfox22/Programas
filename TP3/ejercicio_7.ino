/*Realizar un programa en framework de Arduino que:
- Imprima un mensaje en el Monitor Serial solicitando el ingreso de un carácter por teclado mediante el Monitor Serial
- Imprima el carácter ingresado y su valor en ASCII.
Ejemplo: “Carácter ingresado es el: A , su valor ASII es: 65”
*/

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  char caracter;
  Serial.println("\n\nIngrese un caracter:");
  while (!Serial.available())
  {
  }
  caracter = Serial.read();
  Serial.print("El caracter ingresado es: ");
  Serial.println(caracter);
  Serial.print("Su valor ASCII es: ");
  Serial.println(int(caracter));
}