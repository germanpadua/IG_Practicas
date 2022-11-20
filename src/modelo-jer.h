// Nombre: Germán José , Apellidos: Padua Pleguezuelo , Titulación: GIM .
// email: germanpadua@correo.ugr.es , DNI: 77437393G

#include "grafo-escena.h"
#include "tup_mat.h"
#include "objeto3d.h"


class Llanta : public NodoGrafoEscena
{
   public:
   Llanta();
};

class Traccion : public NodoGrafoEscena
{
   public:
   Traccion();
};


class ParteDeAbajo : public NodoGrafoEscena
{
   public:
   ParteDeAbajo();
};

class ParteDeArriba : public NodoGrafoEscena
{
   public:
   ParteDeArriba();
};

class Techo : public NodoGrafoEscena
{
   public:
   Techo();
};

class LadosCoche : public NodoGrafoEscena
{
   public:
   LadosCoche();
};

class Caja : public NodoGrafoEscena
{
   public:
   Caja();
};

class Rueda : public NodoGrafoEscena
{
   protected:
   unsigned int num_parametros = 1;
   Matriz4f *giroRueda = nullptr;

   public:
   Rueda();
   virtual unsigned leerNumParametros() const;
   virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class Ruedas : public NodoGrafoEscena
{
   protected:
   unsigned int num_parametros = 1;
   Rueda *r1 = new Rueda();
   Rueda *r2 = new Rueda();
   Rueda *r3 = new Rueda();
   Rueda *r4 = new Rueda();
   public:
   Ruedas();
   virtual unsigned leerNumParametros() const;
   virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);
   
};

class TraccionConRuedas : public NodoGrafoEscena
{
   protected:
   unsigned int num_parametros = 1;
   Matriz4f *escaladoTraslacionTraccion = nullptr;
   Ruedas *r = new Ruedas();
   public:
   TraccionConRuedas();
   virtual unsigned leerNumParametros() const;
   virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};


class Capo : public NodoGrafoEscena
{
   public:
   Capo();
};

class CapoRotacion : public NodoGrafoEscena
{
   protected:
   unsigned int num_parametros = 1;
   Matriz4f *giroCapo = nullptr;

public:
   CapoRotacion();
   virtual unsigned leerNumParametros() const;
   virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);

};

class Faro : public NodoGrafoEscena
{
   public:
   Faro();
};

class Faros : public NodoGrafoEscena
{
   public:
   Faros();
};

class Pared : public NodoGrafoEscena
{
   public:
   Pared();
};


class Coche : public NodoGrafoEscena
{
   protected:
   unsigned int num_parametros = 3;
   Matriz4f *ptr_matriz = nullptr;
   CapoRotacion *capor = new CapoRotacion();
   TraccionConRuedas *traccion = new TraccionConRuedas();
   

public:
   Coche();
   virtual unsigned leerNumParametros() const;
   virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);

};