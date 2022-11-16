
#include "modelo-jer.h"
#include "ig-aux.h"
#include "malla-ind.h"
#include "malla-revol.h"

unsigned C::leerNumParametros() const
{
   return 1;
}

void C::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
   assert(iParam < 1);
   // COMPLETAR: práctica 3: actualizar parámetro
   // ...
}

Coche::Coche(){
   agregar(new Faros());
   agregar(new Techo());
   agregar(new ParteDeAbajo());
   agregar(new ParteDeArriba());

   // Animaciones
   capor = new CapoRotacion();
   agregar(capor);
   traccion = new TraccionConRuedas();
   agregar(traccion);
}

unsigned Coche::leerNumParametros() const
{
   return num_parametros;
}

void Coche::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
   switch (iParam)
   {
   case 0:
      capor->actualizarEstadoParametro(0, tSec);
      break;
   case 1:
      std::cout << "Parametro 1: " << tSec << std::endl;
      traccion->actualizarEstadoParametro(0, tSec);
      break;
   case 2:
      std::cout << "Parametro 2: " << tSec << std::endl;
      traccion->actualizarEstadoParametro(1, tSec);
      break;
   }
}




Rueda::Rueda(){
   unsigned int ind = agregar(MAT_Rotacion(0, {0,1,0}));
   agregar(new Embellecedor());
   ponerColor({0.0,0.0,0.0});
   agregar(MAT_Rotacion(90.0, {1,0,0}));
   agregar (MAT_Escalado(0.4,0.25,0.4));
   agregar(new Cilindro(20, 20));

   puntero = leerPtrMatriz(ind);
}

unsigned Rueda::leerNumParametros() const
{
   return num_parametros;
}

void Rueda::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
  switch (iParam)
    {
    case 0:
        std::cout << "Rueda: " << tSec << std::endl;
        (*puntero) = MAT_Rotacion( 30 * sin(2 * M_PI * tSec ), {0, 1, 0});
        break;
    default:
        break;
    }
}

Embellecedor::Embellecedor(){
   ponerColor({1.0,1.0,1.0});
   agregar (MAT_Traslacion({0.0,0.0,-0.01}));
   agregar (MAT_Rotacion(90.0, {1,0,0}));
   agregar (MAT_Escalado(0.1,0.275,0.1)); 
   agregar(new Cilindro(20, 20));
}

Ruedas::Ruedas(){
   r1 = new Rueda();
   agregar(r1);
   //agregar(new Embellecedor());
   agregar(MAT_Traslacion({0.0,0.0,1.5}));
   r2 = new Rueda();
   agregar(r2);
   //agregar(new Embellecedor());
   agregar(MAT_Traslacion({2.5,0.0,0.0}));
   r3 = new Rueda();
   agregar(r3);
   //agregar(new Embellecedor());
   agregar(MAT_Traslacion({0.0,0.0,-1.5}));
   r4 = new Rueda();
   agregar(r4);
   //agregar(new Embellecedor());
}

unsigned Ruedas::leerNumParametros() const
{
   return num_parametros;
}

void Ruedas::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
   switch (iParam)
   {
   case 0:
      r1->actualizarEstadoParametro(0, tSec);
      r2->actualizarEstadoParametro(0, tSec);
      r3->actualizarEstadoParametro(0, tSec);
      r4->actualizarEstadoParametro(0, tSec);
      break;
   }
}

Traccion::Traccion(){
   ponerColor({0.5,0.54,0.53});
   agregar(MAT_Rotacion(90.0, {1,0,0}));
   agregar(MAT_Escalado(0.05,1.6,0.05)); 
   agregar(new Cilindro(20, 20));
}

TraccionConRuedas::TraccionConRuedas(){   
   unsigned int ind = agregar(MAT_Escalado(1,1,1) * MAT_Traslacion({0.0,0.0,0.0}));
   r = new Ruedas();
   agregar(r);
   agregar(new Traccion());
   agregar(MAT_Traslacion({2.5,0.0,0.0}));
   agregar(new Traccion());

   puntero = leerPtrMatriz(ind);
}

void TraccionConRuedas::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
   float a1 = 0;
   float b1 = 1.5;
   float a2 = 0;
   float b2 = 0.5;
   float vel1 = a1 + fabs(sin(2* M_PI * tSec) * b1);
   float vel2 = a2 - fabs(sin(2* M_PI * tSec + M_PI) * b2);
   switch (iParam)
   {
   case 0:
      r->actualizarEstadoParametro(0, tSec);
      break;   
   case 1:
      std::cout << "Parametro 1 Traccion: " << tSec << std::endl;
      (*puntero) = MAT_Escalado(1,1,1 + vel1) * MAT_Traslacion({0.0,0.0,vel2});
      break;
   }
}

unsigned TraccionConRuedas::leerNumParametros() const
{
   return num_parametros;
}

LadosCoche::LadosCoche(){
   agregar(MAT_Traslacion({0.0,0.0,0.125}));
   agregar(MAT_Escalado(3, 1.0, 1.0));
   agregar(MAT_Rotacion(-90.0, {1,0,0}));
   agregar(new RejillaY(10,10));
   agregar(MAT_Traslacion({0.0,-1.5,0.0}));
   agregar(new RejillaY(10,10));
}

Caja::Caja(){
   agregar(new LadosCoche());
   agregar(MAT_Traslacion({0.0,0.0,0.125}));
   agregar(MAT_Escalado(3, 1.5, 1.5));
   agregar(new RejillaY(10,10));
   agregar(MAT_Rotacion(90.0, {0,0,1}));
   agregar(MAT_Escalado(0.666, 1.0, 1.0));
   agregar(new RejillaY(10,10));
   agregar(MAT_Traslacion({0.0,-1.0,0.0}));
   agregar(new RejillaY(10,10));
}

ParteDeAbajo::ParteDeAbajo(){
   agregar(new Caja());
   agregar(MAT_Traslacion({-0.75,0.0,0.0}));
   agregar(MAT_Escalado(0.25, 1.0, 1.0));
   agregar(new Caja());
}

ParteDeArriba::ParteDeArriba(){
   ponerColor({0.7,1.0,1.0});
   agregar(MAT_Traslacion({0.0,1.0,0.125}));
   agregar(MAT_Escalado(1.0, 0.5, 1.5));
   agregar(new Prisma());
   agregar(MAT_Traslacion({3.0,0.0,0.0}));
   agregar(MAT_Escalado(-0.75, 1.0, 1.0));
   agregar(new Prisma());
}

Techo::Techo(){
   ponerColor({0.0,0.5,0.25});
   agregar(MAT_Traslacion({1.62, 1.25, 0.875}));
   agregar(MAT_Escalado(0.62, 0.25, 0.75));
   agregar(new CuboColores());
}

Capo::Capo(){
   agregar(MAT_Traslacion({-0.75,1.0,0.125}));
   agregar(MAT_Escalado(0.75, 1.0, 1.5));
   agregar(new RejillaY(10,10));
}

CapoRotacion::CapoRotacion(){
   agregar(MAT_Traslacion({0.0, 1.0, 0.0}));
   //agregar(MAT_Rotacion(-30.0, {0,0,1}));
   unsigned int ind = agregar(MAT_Rotacion(0.0, {0,0,1}));
   agregar(MAT_Traslacion({0.0, -1.0, 0.0}));
   puntero = leerPtrMatriz(ind);
   agregar(new Capo());
}

void CapoRotacion::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{
   switch (iParam)
   {
   case 0:
      std::cout << "Parametro 0: " << tSec << std::endl;
      //(*puntero) = MAT_Traslacion({0.0, 1.0, 0.0}) MAT;
      (*puntero) = MAT_Rotacion(- 75 * fabs(sin(2 * M_PI * tSec )), {0, 0, 1});
      //(*puntero) = MAT_Traslacion({0.0, -1.0, 0.0});
      break;
   default:
      break;
   } 
}

unsigned CapoRotacion::leerNumParametros() const
{
   return num_parametros;
}


Faro::Faro(){
   ponerColor({1.0,1.0,0.25});
   agregar(MAT_Escalado(0.05, 0.1, 0.1));
   agregar(MAT_Rotacion(90.0, {0,0,1}));
   agregar(new Cilindro(20, 20));
}

Faros::Faros(){
   agregar(MAT_Traslacion({-0.76, 0.7, 0.36}));
   agregar(new Faro());
   agregar(MAT_Traslacion({0.0,0.0,1.0}));
   agregar(new Faro());
}

