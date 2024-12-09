#pragma once
#include <string>
#include "cliente.h"

class ArchivoCliente{
    private:
        const char * _nombreArchivo  = "db/Cliente.dat";
        
    public:
        ArchivoCliente();
        bool crear();
        bool guardar(Cliente cliente);
        bool guardar(Cliente cliente, int posicion);
        int buscar(int IDCliente);
        Cliente leer(int posicion);
        int CantidadRegistros();
        void leer(int cantidadRegistros, Cliente *vector);
};