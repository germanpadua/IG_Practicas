// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std;

// *****************************************************************************

// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar(
    const std::vector<Tupla3f> &perfil, // tabla de vértices del perfil original
    const unsigned num_copias           // número de copias del perfil
)
{
   // COMPLETAR: Práctica 2: completar: creación de la malla....
   cout << endl
        << "Creando malla de revolución con " << perfil.size() << " vértices y " << num_copias << " copias." << endl;

   vertices.empty();

   for (int i = 0; i < num_copias; i++)
   {
      for (int j = 0; j < perfil.size(); j++)
      {
         Tupla3f vertice = perfil[j];
         float x = vertice[0];
         float y = vertice[1];
         float z = vertice[2];
         float angulo = (2 * M_PI * i) / (num_copias - 1);
         float x_rotado = x * cos(angulo) + z * sin(angulo);
         float z_rotado = -x * sin(angulo) + z * cos(angulo);

         vertices.push_back({x_rotado, y, z_rotado});
      }
   }

   for (int i = 0; i < num_copias - 1; i++)
   {
      for (int j = 0; j < perfil.size() - 1; j++)
      {
         int v1 = i * perfil.size() + j;
         int v2 = v1 + perfil.size();
         int v3 = v2 + 1;
         int v4 = v1 + 1;
         triangulos.push_back({v1, v2, v3});
         triangulos.push_back({v1, v3, v4});
      }
   }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY(
    const std::string &nombre_arch,
    const unsigned nperfiles)
{
   ponerNombre(std::string("malla por revolución del perfil en '" + nombre_arch + "'"));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   std::vector<Tupla3f> perfil;

   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);
}

// -----------------------------------------------------------------------------

Cilindro::Cilindro(
    const int num_vert_perfil,
    const unsigned nperfiles)
{
   ponerNombre(std::string("cilindro con " + std::to_string(num_vert_perfil) + " vértices en el perfil"));

   std::vector<Tupla3f> perfil;
   perfil.push_back({0.0, 1.0, 0.0});

   for (int i = 0; i < num_vert_perfil - 2; i++)
   {
      perfil.push_back({1.0, 1.0 - i / (num_vert_perfil - 3), 0.0});
   }

   perfil.push_back({0.0, 0.0, 0.0});

   inicializar(perfil, nperfiles);
}

// -----------------------------------------------------------------------------

Esfera::Esfera(
    const int num_vert_perfil,
    const unsigned nperfiles)
{
   ponerNombre(std::string("esfera con " + std::to_string(num_vert_perfil) + " vértices en el perfil"));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // .......................
   std::vector<Tupla3f> perfil;

   for (int i = 0; i < num_vert_perfil; i++)
   {
      float angulo = M_PI / 2 - i * M_PI / (num_vert_perfil - 1);
      float x = cos(angulo);
      float y = sin(angulo);
      perfil.push_back({x, y, 0.0});
   }

   inicializar(perfil, nperfiles);
}

// -----------------------------------------------------------------------------

Cono::Cono(
    const int num_vert_perfil,
    const unsigned nperfiles)
{
   ponerNombre(std::string("cono con " + std::to_string(num_vert_perfil) + " vértices en el perfil"));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // .......................
   std::vector<Tupla3f> perfil;

   perfil.push_back({0.0, 1.0, 0.0});

   for (int i = 0; i < num_vert_perfil - 2; i++)
   {
      perfil.push_back({float(i) / float((num_vert_perfil - 3)), 1.0 - float(i) / float((num_vert_perfil - 3)), 0.0});
   }

   perfil.push_back({0.0, 0.0, 0.0});

   inicializar(perfil, nperfiles);
}
