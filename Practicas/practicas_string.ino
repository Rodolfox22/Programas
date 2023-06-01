void setup()
{
  Serial.begin(9600);
  Serial.print("using a constant String:\t");
  String stringOne = "Hello String";
  Serial.println(stringOne);
  
  Serial.print("converting a constant char into a String:\t");
  stringOne = String('a');
  Serial.println(stringOne);

  Serial.print("converting a constant string into a String object:\t");
  String stringTwo = String("This is a string:\t");
  Serial.println(stringTwo);

  Serial.print("concatenating two strings:\t");
  stringOne = String(stringTwo + " with more");
  Serial.println(stringOne);

  Serial.print("using a constant integer:\t");
  stringOne = String(13);
  Serial.println(stringOne);

  Serial.print("using an int and a base:\t");
  stringOne = String(230, DEC);
  Serial.println(stringOne);

  Serial.print("using an int and a base (hexadecimal):\t");
  stringOne = String(45, HEX);
  Serial.println(stringOne);

  Serial.print("using an int and a base (binary):\t");
  stringOne = String(255, BIN);
  Serial.println(stringOne);

  Serial.print("using a long and a base (millis()):\t");
  stringOne = String(millis(), DEC);
  Serial.println(stringOne);

  Serial.print("using a float and the decimal places:\t");
  stringOne = String(5.698, 3);
  Serial.println(stringOne);

}

void loop()
{
}