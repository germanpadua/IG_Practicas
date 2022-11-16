// *********************************************************************
// **
// ** Gestión de una grafo de escena (implementación)
// ** Copyright (C) 2016 Carlos Ureña
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "grafo-escena.h"
#include "malla-ind.h"
#include "malla-revol.h"

using namespace std ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != NULL );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const Matriz4f & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new Matriz4f() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != NULL );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL( ContextoVis & cv )
{
   // COMPLETAR: práctica 3: recorrer las entradas y visualizar cada nodo.
   // ........
   Tupla4f col;
   col = leerFijarColVertsCauce( cv );


   // guarda modelview actual
   cv.cauce->pushMM();

   // recorrer todas las entradas del array que hay en el nodo:
   for( unsigned i = 0; i < entradas.size(); i++){
      switch( entradas[i].tipo ){
         case TipoEntNGE::objeto:                         // entrada objeto
            entradas[i].objeto->visualizarGL(cv);        // visualizar objeto
            break;
         case TipoEntNGE::transformacion:                // entrada transf.:
            // cv.cauce->compMM( *(entradas[i].matriz) );   // componer matriz
            cv.cauce->compMM(*leerPtrMatriz(i));
            break;
         /*
         case TipoEntNGE::material:
            cv.cauce->compMM( *(entradas[i].matriz) );          // cambiar material
            break; 
         */  
      }
   }

   


   cv.cauce->popMM() ; // restaura modelview

   cv.cauce->fijarColor( col ); // restaura color


   

   // COMPLETAR: práctica 4: en la práctica 4, si 'cv.iluminacion' es 'true',
   // se deben de gestionar los materiales:
   //   1. guardar puntero al material activo al inicio (está en cv.material_act)
   //   2. si una entrada des de tipo material, activarlo y actualizar 'cv.material_act'
   //   3. al finalizar, restaurar el material activo al inicio (si es distinto del actual)



}




// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL( ContextoVis & cv )
{
   // comprobar que hay un cauce en 'cv' 
   assert( cv.cauce != nullptr );
  

   // COMPLETAR: práctica 3
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarGeomGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)

   // .......

   // guarda modelview actual
   cv.cauce->pushMM();

   // recorrer todas las entradas del array que hay en el nodo:
   for( unsigned i = 0; i < entradas.size(); i++){
      switch( entradas[i].tipo ){
         case TipoEntNGE::objeto:                            // entrada objeto
            entradas[i].objeto->visualizarGeomGL(cv);        // visualizar objeto
            break;
         case TipoEntNGE::transformacion:                // entrada transf.:
            //cv.cauce->compMM( *(entradas[i].matriz) );   // componer matriz
            cv.cauce->compMM(*leerPtrMatriz(i));
            break;
         default:
            break;
      }
   }
   
   cv.cauce->popMM() ; // restaura modelview

}



// -----------------------------------------------------------------------------

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   // ........
   entradas.push_back(entrada);
   return entradas.size()-1;

   // return 0 ; // sustituir por lo que corresponda ....

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const Matriz4f & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
Matriz4f * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: devolver puntero la matriz en ese índice
   //   (debe de dar error y abortar si no hay una matriz en esa entrada)
   // ........(sustituir 'return nullptr' por lo que corresponda)

   if( entradas[indice].tipo == TipoEntNGE::transformacion ){
      return entradas[indice].matriz;
   }
   else{
      std::cout << "ERROR: No hay una matriz en esa entrada" << std::endl;
      return nullptr;
   }

}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int         ident_busc, // identificador a buscar
   const Matriz4f &  mmodelado,  // matriz de modelado
   Objeto3D       ** objeto,     // (salida) puntero al puntero al objeto
   Tupla3f &         centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........


   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........


   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}

// -----------------------------------------------------------------------------


GrafoEstrellaX::GrafoEstrellaX(unsigned int n){
   // crear un nodo para la estrella:
   NodoGrafoEscena * nodo_estrella = new NodoGrafoEscena();
   EstrellaZ * estrella = new EstrellaZ(n);
   NodoGrafoEscena * objeto = new  NodoGrafoEscena();

   objeto->agregar(MAT_Rotacion(90, {0, 1, 0}));
   nodo_estrella->agregar (MAT_Escalado(2.6,2.6,1.0));
   nodo_estrella->agregar (MAT_Traslacion({-0.5,-0.5,0.0}));
   nodo_estrella->agregar( estrella );

   NodoGrafoEscena * nodo_cono = new NodoGrafoEscena();
   Cono * cono = new Cono(20, 20);
   nodo_cono->agregar (MAT_Escalado(0.25,0.25,0.25));
   nodo_cono->agregar (MAT_Traslacion({0.0 ,5.2, 0.0}));
   nodo_cono->agregar (cono);

   NodoGrafoEscena * nodo_conos = new NodoGrafoEscena();
   nodo_conos->agregar(MAT_Rotacion(-90, {0, 0, 1}));

   for(int i=0; i<n; i++){
      nodo_conos->agregar(nodo_cono);
      nodo_conos->agregar(MAT_Rotacion(360.0/n, {0,0,1}));
   }
   
   unsigned int ind = objeto->agregar(MAT_Rotacion(0, {1, 0, 0}));
   objeto->agregar(nodo_estrella);
   objeto->agregar(nodo_conos);
   

   agregar(objeto);
   puntero = objeto->leerPtrMatriz(ind);

}

unsigned int GrafoEstrellaX::leerNumParametros() const
{
   return num_parametros;
}

void GrafoEstrellaX::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
   switch(iParam){
      case 0:
         (*puntero) = MAT_Rotacion(360.0* t_sec * 2.5, {0,0,1});
         break;
      default:
         assert(false);
   }
}


// -----------------------------------------------------------------------------

GrafoCubos::GrafoCubos(){
   NodoGrafoEscena * cubo = new NodoGrafoEscena();
   NodoGrafoEscena * cuboRejilla = new NodoGrafoEscena();
   
   unsigned int ind = cubo->agregar(MAT_Rotacion(0, {0, 1, 0}));

   cubo->agregar(MAT_Traslacion({0.0,0.7,0.0}));
   cubo->agregar(MAT_Escalado(0.1,0.2,0.1));
   cubo->agregar(new Cubo());

   agregar(cubo);
   agregar(MAT_Rotacion(90, {1,0,0}));
   agregar(cubo);
   agregar(MAT_Rotacion(90, {1,0,0}));
   agregar(cubo);
   agregar(MAT_Rotacion(90, {1,0,0}));
   agregar(cubo);
   agregar(MAT_Rotacion(90, {0,0,1}));
   agregar(cubo);
   agregar(MAT_Rotacion(180, {0,0,1}));
   agregar(cubo);


   cuboRejilla->agregar(MAT_Traslacion({-0.5,-0.5,-0.5}));
   cuboRejilla->agregar(new RejillaY(5, 5));
   cuboRejilla->agregar(MAT_Traslacion({0.0,1.0,0.0}));
   cuboRejilla->agregar(new RejillaY(5, 5));
   cuboRejilla->agregar(MAT_Rotacion(-90, {0,0,1}));
   cuboRejilla->agregar(new RejillaY(5, 5));
   cuboRejilla->agregar(MAT_Traslacion({0.0,1.0,0.0}));
   cuboRejilla->agregar(new RejillaY(5, 5));
   cuboRejilla->agregar(MAT_Rotacion(90, {1,0,0}));
   cuboRejilla->agregar(new RejillaY(5, 5));
   cuboRejilla->agregar(MAT_Traslacion({0.0,1.0,0.0}));
   cuboRejilla->agregar(new RejillaY(5, 5));

   
   agregar(cuboRejilla);

   puntero = cubo->leerPtrMatriz(ind);
}

unsigned int GrafoCubos::leerNumParametros() const
{
   return num_parametros;
}

void GrafoCubos::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
   switch(iParam){
      case 0:
         (*puntero) = MAT_Rotacion(45* t_sec , {0,1,0});
         break;
      default:
         assert(false);
   }
}

