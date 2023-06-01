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
  double Volumen();
};
