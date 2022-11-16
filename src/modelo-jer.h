# include "grafo-escena.h"
#include "tup_mat.h"
#include "objeto3d.h"

class C: public NodoGrafoEscena
{
   public:
      C();
      unsigned leerNumParametros() const;
      void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class Embellecedor : public NodoGrafoEscena
{
   public:
   Embellecedor();
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
   Matriz4f *puntero = nullptr;

   public:
   Rueda();
   virtual unsigned leerNumParametros() const;
   virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class Ruedas : public NodoGrafoEscena
{
   protected:
   unsigned int num_parametros = 1;
   Matriz4f *puntero = nullptr;
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
   Matriz4f *puntero = nullptr;
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
   Matriz4f *puntero = nullptr;

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