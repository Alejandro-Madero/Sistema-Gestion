#pragma once
#include <string>
#include  "usuario.h"

class ArchivoUsuario{
    public:
        ArchivoUsuario();
        bool crear();
        bool guardar(Usuario usuario);
        bool guardar(Usuario usuario, int posicion);
        int buscar(std::string busqueda, int tipoDeBuqueda);        
        Usuario leer(int posicion);
        Usuario* leerTodos();
        int calcularCantidadRegistros();
        int aumentarRegistros();
        void leer(int cantidadRegistros, Usuario *vector);
        int getCantidadRegistros(); 

    private:
        const char * _nombreArchivo  = "db/usuario.dat";
        int _cantidadRegistros = -1; 
        
};