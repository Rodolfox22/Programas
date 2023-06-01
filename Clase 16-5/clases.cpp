// Columna1	                 Nombre
// miembros o atributos	    variables
// funciones	                metodos
// datos	                     campos o atributos

// Los nombres de las clases empiezan con mayuscula
class Caja
{

  // Los nombres de las variables, metodos, atributos empiezan con minuscula
  double largo;
  double ancho;
  double alto;
};

Caja caja1;

// Cuando genero un objeto reservo memoria para cada parte del objeto
// En C todo lo que esta dentro de la clase es privado

class Caja1
{
private:
  double largo;
  double ancho;
  double alto;

public:
  double Volumen()
  {
    return largo * ancho * alto;
  }
};

// Inline
class Caja2
{
private:
  double ancho;
  double alto;
  double largo;

public:
  double Volumen();
};

Caja2::Volumen()
{
  return largo * ancho * alto;
}

// Constructores
class Caja3
{
private:
  double ancho;
  double alto;
  double largo;

public:
  // Constructor
  Caja3(double lar, double an, double al)
  {
    // Asignacion
    largo = lar;
    ancho = an;
    alto = al;
  }
};

// En el programa se utiliza
Caja3 unaCaja(0.5, 0.6, 0.8);
Serial.print("El volumen de la caja será: ");
Serial.println(unaCaja.Volumen());

// Lista de inicializacion, variable de uso del constructor

Caja3(double lar, double an, double al = 0.8) : alto(al), ancho(an), largo(lar){};

// COnstructor de copia

Caja3 unaCaja(0.58, 0.25, 0.55);
Caja3 otraCaja = unaCaja; // Hay que tener cuidado cuando se hace este constructor, ya que se complica el funcionamiento conado existen punteros dentro del objeto

// Metodos
double getAlto()
{
  return alto;
}

double setAlto(double al)
{
  alto = al;
}


// atributos o metodos estaticos
// se crea por unica vez y es compartido por todos los metodos de la clase
// Si yo modifico un atributo en un objeto, se modificará en todos los objetos creados
// un atributo muy utilizado es un contador, si yo necesito contabilizar objetos lo puedo utilizar 
// es un atributo privado

// Clases derivadas
