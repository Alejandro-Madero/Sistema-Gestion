#pragma once
#include <string>
#include "orden-compra.h"

class ArchivoOrdenCompra{
    private:
        const char * _nombreArchivo  = "db/orden-compra.dat";
        
    public:
        ArchivoOrdenCompra();
        bool crear();
        bool guardar(OrdenCompra ordenCompra);
        bool guardar(OrdenCompra ordenCompra, int posicion);
        int buscar(int idProveedor);
        OrdenCompra leer(int posicion);
        int CantidadRegistros();
        void leer(int cantidadRegistros, OrdenCompra *vector);
};