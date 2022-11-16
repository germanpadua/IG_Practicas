// Nombre: Germán José , Apellidos: Padua Pleguezuelo , Titulación: GIM .
// email: germanpadua@correo.ugr.es , DNI: 77437393G

// *********************************************************************
// **
// ** Informática Gráfica, curso 2020-21
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

#include "ig-aux.h"
#include "malla-ind.h" // declaración de 'ContextoVis'
#include "lector-ply.h"

// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd(const std::string &nombreIni)
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni);
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size();
   assert(1 <= nt);
   if (0 < nor_tri.size())
   {
      assert(nt == nor_tri.size());
      return;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....
}

// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......
}

// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL(ContextoVis &cv)
{

   using namespace std;
   assert(cv.cauce != nullptr);
   CError();

   if (triangulos.size() == 0 || vertices.size() == 0)
   {
      cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl
           << flush;
      return;
   }

   // guardar el color previamente fijado y fijar el color del objeto actual
   const Tupla4f color_previo = leerFijarColVertsCauce(cv);

   // COMPLETAR: práctica 1: si el nombre del VAO es 0, crear el VAO con sus VBOs:
   //   * en primer lugar se crea y activa el VAO , con 'CrearVAO'.
   //   * después se añade el VBO con la tabla de coordenadas de posición, 'CrearVBOAtrib'.
   //   * se añade el VBO con la tabla de índices (la tabla de triángulos), con 'CrearVBOInd'.
   //   * finalmente se añaden al VAO los VBOs con tablas de atributos (opcionales) que haya, con 'CrearVBOAtrib'.
   // si el VAO ya está creado, (nombre_vao > 0), activarlo, con 'glBindVertexArray'
   //
   //  hay que tener en cuenta que el nombre del VAO y los nombres de losVBOs deben quedar en las correspondientes
   //  variables de instancia. Estos nombres son los devueltos por las
   //  funciones 'CrearVAO', 'CrearVBOAtrib' y 'CrearVBOInd'.
   //

   if (nombre_vao == 0)
   {
      nombre_vao = CrearVAO();
      nombre_vbo_pos = CrearVBOAtrib(ind_atrib_posiciones, vertices);
      nombre_vbo_tri = CrearVBOInd(triangulos);
      if (col_ver.size() > 0)
         nombre_vbo_col = CrearVBOAtrib(ind_atrib_colores, col_ver);

      if (nor_ver.size() > 0)
         nombre_vbo_nor = CrearVBOAtrib(ind_atrib_normales, nor_ver);
        
      if (cc_tt_ver.size() > 0)
         nombre_vbo_cct = CrearVBOAtrib(ind_atrib_coord_text, cc_tt_ver);

        
      // CrearVBOAtrib( nombre_vao, tablaatributos opcional );
   }
   else if (nombre_vao > 0)
   {
      glBindVertexArray(nombre_vao);
   }

   // COMPLETAR: práctica 1: visualizar con 'glDrawElements' y desactivar VAO.

   glDrawElements(GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, 0);

   glBindVertexArray(0);

   // restaurar el color previamente fijado
   cv.cauce->fijarColor(color_previo);
}

// -----------------------------------------------------------------------------
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
// (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)

void MallaInd::visualizarGeomGL(ContextoVis &cv)
{
   // COMPLETAR: práctica 1: asegurarnos de que el VAO de geometría está creado y activado
   // ....

   if (nombre_vao_geo == 0)
   {
      nombre_vao_geo = CrearVAO();

      glBindBuffer(GL_ARRAY_BUFFER, nombre_vbo_pos);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nombre_vbo_tri);

      glVertexAttribPointer(ind_atrib_posiciones, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(ind_atrib_posiciones);

   }
   else if (nombre_vao_geo > 0)
   {
      glBindVertexArray(nombre_vao_geo);
   }

   // COMPLETAR: práctica 1. Visualizar la malla y desactivar VAO
   // ....

   glDrawElements(GL_TRIANGLES, triangulos.size() * 3, GL_UNSIGNED_INT, 0);

   glBindVertexArray(0);

   CError();
}

// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY(const std::string &nombre_arch)
{
   ponerNombre(std::string("malla leída del archivo '") + nombre_arch + "'");

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch, vertices, triangulos);
   
   
   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................
}

// ****************************************************************************
// Clase 'CuboColores

CuboColores::CuboColores()
    : MallaInd("cubo de colores 8 vértices")
{

   vertices =
       {
           {-1.0, -1.0, -1.0}, // 0
           {-1.0, -1.0, +1.0}, // 1
           {-1.0, +1.0, -1.0}, // 2
           {-1.0, +1.0, +1.0}, // 3
           {+1.0, -1.0, -1.0}, // 4
           {+1.0, -1.0, +1.0}, // 5
           {+1.0, +1.0, -1.0}, // 6
           {+1.0, +1.0, +1.0}, // 7
       };

   triangulos =
       {
           {0, 1, 3}, {0, 3, 2}, // X-
           {4, 7, 5},
           {4, 6, 7}, // X+ (+4)

           {0, 5, 1},
           {0, 4, 5}, // Y-
           {2, 3, 7},
           {2, 7, 6}, // Y+ (+2)

           {0, 6, 4},
           {0, 2, 6}, // Z-
           {1, 5, 7},
           {1, 7, 3} // Z+ (+1)
       };

   col_ver =
       {
           {-1.0, -1.0, -1.0}, // 0
           {-1.0, -1.0, +1.0}, // 1
           {-1.0, +1.0, -1.0}, // 2
           {-1.0, +1.0, +1.0}, // 3
           {+1.0, -1.0, -1.0}, // 4
           {+1.0, -1.0, +1.0}, // 5
           {+1.0, +1.0, -1.0}, // 6
           {+1.0, +1.0, +1.0}, // 7}

       };
}

   // ****************************************************************************
   // Clase 'Cubo

   Cubo::Cubo()
       : MallaInd("cubo 8 vértices")
   {

      vertices =
          {
              {-1.0, -1.0, -1.0}, // 0
              {-1.0, -1.0, +1.0}, // 1
              {-1.0, +1.0, -1.0}, // 2
              {-1.0, +1.0, +1.0}, // 3
              {+1.0, -1.0, -1.0}, // 4
              {+1.0, -1.0, +1.0}, // 5
              {+1.0, +1.0, -1.0}, // 6
              {+1.0, +1.0, +1.0}, // 7
          };

      triangulos =
          {
              {0, 1, 3}, {0, 3, 2}, // X-
              {4, 7, 5},
              {4, 6, 7}, // X+ (+4)

              {0, 5, 1},
              {0, 4, 5}, // Y-
              {2, 3, 7},
              {2, 7, 6}, // Y+ (+2)

              {0, 6, 4},
              {0, 2, 6}, // Z-
              {1, 5, 7},
              {1, 7, 3} // Z+ (+1)
          };
   }

   // ****************************************************************************
   // Clase 'CuboTejado'

   CuboTejado::CuboTejado()
       : MallaInd("cubo tejado")
   {

      vertices =
          {
              {-1.0, -1.0, -1.0}, // 0
              {-1.0, -1.0, +1.0}, // 1
              {-1.0, +1.0, -1.0}, // 2
              {-1.0, +1.0, +1.0}, // 3
              {+1.0, -1.0, -1.0}, // 4
              {+1.0, -1.0, +1.0}, // 5
              {+1.0, +1.0, -1.0}, // 6
              {+1.0, +1.0, +1.0}, // 7
              {+0.0, +2.0, +0.0}, // 8
          };

      for (Tupla3f &v : vertices)
         v = 2.0f * v + Tupla3f({0.0, 2.0, 0.0});

      triangulos =
          {
              {0, 1, 3}, {0, 3, 2}, // X-
              {4, 7, 5},
              {4, 6, 7}, // X+ (+4)

              {0, 5, 1},
              {0, 4, 5}, // Y-
              //{2,3,7}, {2,7,6}, // Y+ (+2)   // quito cara superior
              {2, 3, 8},
              {3, 7, 8},
              {7, 6, 8},
              {6, 2, 8}, // añado tejado

              {0, 6, 4},
              {0, 2, 6}, // Z-
              {1, 5, 7},
              {1, 7, 3} // Z+ (+1)
          };
   }

   // ****************************************************************************
   // Clase 'Tetraedro

   Tetraedro::Tetraedro()
       : MallaInd("tetraedro de 4 vértices")
   {

      vertices =
          {
              {0.0, 0.0, 0.0},  // 0
              {0.0, +1.0, 0.0}, // 1
              {+1.0, 0.0, 0.0}, // 2
              {0.0, 0.0, +1.0}, // 3
          };

      triangulos =
          {
              {0, 1, 2}, // X-
              {0, 3, 1}, // X+ (+4)
              {0, 2, 3}, // Y-
              {1, 3, 2}, // Y+ (+2)

          };

      // Objeto3D::ponerColor({0.0,0.0,1.0});
      col_ver =
          {
              {0.0, 0.0, 1.0},
              {0.0, 1.0, 0.0},
              {1.0, 0.0, 0.0},
              {1.0, 1.0, 0.0},
          };
   }

   // ****************************************************************************
   // Clase 'CasaX'

   CasaX::CasaX()
       : MallaInd("casa X")
   {

      vertices =
          { 
              {0.0, 0.0, 0.0},     // 0
              {0.0, 0.0, +0.7},    // 1
              {0.0, +0.7, 0.0},    // 2
              {0.0, +0.7, +0.7},   // 3
              {+1.0, 0.0, 0.0},    // 4
              {+1.0, 0.0, +0.7},   // 5
              {+1.0, +0.7, 0.0},   // 6
              {+1.0, +0.7, +0.7},  // 7
              {0.0, +1.0, +0.35},  // 8
              {+1.0, +1.0, +0.35}, // 9

          };

        col_ver = 
            {
              {0.0, 0.0, 0.0},     // 0
              {0.0, 0.0, +0.7},    // 1
              {0.0, +0.7, 0.0},    // 2
              {0.0, +0.7, +0.7},   // 3
              {+1.0, 0.0, 0.0},    // 4
              {+1.0, 0.0, +0.7},   // 5
              {+1.0, +0.7, 0.0},   // 6
              {+1.0, +0.7, +0.7},  // 7
              {0.0, +1.0, +0.35},  // 8
              {+1.0, +1.0, +0.35}, // 9
            };

      triangulos =
          {
              {0, 1, 3}, {0, 3, 2}, // X-
              {4, 7, 5},
              {4, 6, 7}, // X+ (+4)

              {0, 5, 1},
              {0, 4, 5}, // Y-
              // {2,3,7}, {2,7,6}, // Y+ (+2) quito cara superior
              {2, 3, 8},
              {6, 7, 9},
              {2, 6, 9},
              {2, 8, 9},
              {3, 8, 9},
              {3, 7, 9},

              {0, 6, 4},
              {0, 2, 6}, // Z-
              {1, 5, 7},
              {1, 7, 3} // Z+ (+1)
          };
   }

    // ****************************************************************************
    // Clase 'EstrellaZ'

EstrellaZ::EstrellaZ(int n)
       : MallaInd("Estrella Z")
   {

    vertices.push_back({0.5,0.5,0.0}); // centro

    for (int i = 0; i < n; i++){
        
        vertices.push_back({ 0.5 + 0.5*cos((i*2*M_PI)/n) ,0.5 + 0.5*sin((i*2*M_PI)/n), 0.0 }); // añade las puntas
        
    }

    for (int i = 0; i < n; i++){
        
        vertices.push_back({0.5 + 0.25*cos(((i*2*M_PI)/n)+(M_PI/n)) , 0.5 + 0.25*sin(((i*2*M_PI)/n)+(M_PI/n)), 0.0 }); // añade los huecos
        
    }

    for(int i = 0; i < n;i++){
        
        triangulos.push_back({0, i+1, n+1 + i});
        if(i == n-1){
            triangulos.push_back({0, 1, n+1 + i});
        }else
            triangulos.push_back({0, i+2, n+1 + i});

    }

    col_ver.push_back({1.0,1.0,1.0});
    
    for(int i=1; i <= vertices.size() - 1; i++){
        col_ver.push_back(vertices.at(i));
    }

    
   }

    // ****************************************************************************

    // Clase 'MallaTriangulo'
MallaTriangulo::MallaTriangulo()
       : MallaInd("Malla Triangulo")
   {
      vertices =
          {
              {-0.5, 0.0, 0.0},    // 0
              {+0.5, 0.0, 0.0},    // 1
              {0.0, sqrt(2), 0.0}, // 2
          };

      triangulos =
          {
              {0, 1, 2},
          };
   }

MallaCuadrado::MallaCuadrado()
       : MallaInd("Malla Cuadrado")
   {
      vertices =
          {
              {-1.0, -1.0, 0.0},    // 0
              {+1.0, -1.0, 0.0},    // 1
              {+1.0, +1.0, 0.0},    // 2
              {-1.0, +1.0, 0.0},    // 3
          };

      triangulos =
          {
              {0, 1, 2},
              {0, 2, 3},
          };
   }

MallaPiramideL::MallaPiramideL()
        : MallaInd("Malla Piramide L")
    {
    vertices = {
        {0.0, 0.0, 0.0},    // 0
        {0.0, 0.0, -1.0},   // 1
        {+1.0, 0.0, 0.0},   // 2
        {+1.0, 0.0, -0.5},  // 3
        {+0.5, 0.0, -0.5},  // 4
        {+0.5, 0.0, -1.0},  // 5
        {+0.5, +1.0, -0.5}, // 6

    };

    triangulos = {
        {5, 4, 1},
        {3, 2, 4},
        {2, 0, 1},
        {5, 6, 1},
        {5, 4, 6},
        {4, 3, 6},
        {3, 2, 6},
        {0, 6, 2},
        {1, 6, 0},

    };
}
    

   // -----------------------------------------------------------------------------------------------

    // ****************************************************************************

// Práctica 2 Ejercicio 1
    // Clase 'PiramideEstrellaZ'

PiramideEstrellaZ::PiramideEstrellaZ(unsigned m)
    : MallaInd("Piramide Estrella Z")
    {

    vertices.push_back({0.5,0.5,0.0}); // centro

    int n = m;

    for (int i = 0; i < n; i++){
        
        vertices.push_back({ 0.5 + 0.5*cos((i*2*M_PI)/n) ,0.5 + 0.5*sin((i*2*M_PI)/n), 0.0 }); // añade las puntas
        
    }

    for (int i = 0; i < n; i++){
        
        vertices.push_back({0.5 + 0.25*cos(((i*2*M_PI)/n)+(M_PI/n)) , 0.5 + 0.25*sin(((i*2*M_PI)/n)+(M_PI/n)), 0.0 }); // añade los huecos
        
    }

    for(int i = 0; i < n;i++){
        
        triangulos.push_back({0, i+1, n+1 + i});
        if(i == n-1){
            triangulos.push_back({0, 1, n+1 + i});
        }else
            triangulos.push_back({0, i+2, n+1 + i});

    }
    
    vertices.push_back({0.5,0.5,0.5}); // centro

    for(int i = 0; i < n;i++){
        
        triangulos.push_back({vertices.size() - 1, i+1, n+1 + i});
        if(i == n-1){
            triangulos.push_back({vertices.size() - 1, 1, n+1 + i});
        }else
            triangulos.push_back({vertices.size() - 1, i+2, n+1 + i});

    }

        
    for(int i=0; i < vertices.size() - 1; i++){
        col_ver.push_back(vertices.at(i));
    }
    col_ver.push_back({1.0,1.0,1.0});
    
}

// ****************************************************************************

// Práctica 2 Ejercicio 2
// Clase 'RejillaY'

RejillaY::RejillaY(unsigned n, unsigned m)
    : MallaInd("Rejilla Y")
    {

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            vertices.push_back({(float)i/(n - 1),0.0,(float)j/(m - 1)});
        }
    }

    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < m - 1; j++){
            triangulos.push_back({i*m+j,i*m+j+1,(i+1)*m+j});
            triangulos.push_back({(i+1)*m+j,(i+1)*m+j+1,i*m+j+1});
        }
    }

    for(int i=0; i <= vertices.size() - 1; i++){
        col_ver.push_back(vertices.at(i));
    }
    
}

// ****************************************************************************

// Clase 'MallaTorre'

MallaTorre::MallaTorre(int n)
    : MallaInd("Malla Torre")
{

    // 00 10
    // 01 11
    float contador = 0.0;
    for(int i=0; i < n; i++){
        vertices.push_back({0.0, contador, 0.0});
        vertices.push_back({1.0, contador, 0.0});
        vertices.push_back({1.0, contador, 1.0});
        vertices.push_back({0.0, contador, 1.0});
        contador ++;
        vertices.push_back({0.0, contador, 0.0});
        vertices.push_back({1.0, contador, 0.0});
        vertices.push_back({1.0, contador, 1.0});
        vertices.push_back({0.0, contador, 1.0});
    }

    for(int i=0; i < n; i++){
        triangulos.push_back({i*8+1,i*8+5,i*8+6});
        triangulos.push_back({i*8+1,i*8+6,i*8+2});
        triangulos.push_back({i*8+4,i*8+0,i*8+3});
        triangulos.push_back({i*8+3,i*8+7,i*8+2});
        triangulos.push_back({i*8+2,i*8+7,i*8+6});
        triangulos.push_back({i*8+4,i*8+5,i*8+0});
        triangulos.push_back({i*8+5,i*8+1,i*8+0});
        triangulos.push_back({i*8+4,i*8+3,i*8+7});
    }
}

// ****************************************************************************

// Clase 'Prisma'
Prisma::Prisma()
    : MallaInd("Prisma")
{    
    vertices.push_back({0.0, 0.0, 0.0});
    vertices.push_back({1.0, 0.0, 0.0});
    vertices.push_back({1.0, 1.0, 0.0});
    vertices.push_back({1.0, 1.0, 1.0});
    vertices.push_back({1.0, 0.0, 1.0});
    vertices.push_back({0.0, 0.0, 1.0});

    

    triangulos.push_back({0, 1, 2});
    triangulos.push_back({0, 2, 3});
    triangulos.push_back({0, 3, 5});
    triangulos.push_back({0, 5, 4});
    triangulos.push_back({0, 4, 1});
    triangulos.push_back({5, 3, 4});
    triangulos.push_back({4, 3, 1});
    triangulos.push_back({1, 3, 2});
    
}
