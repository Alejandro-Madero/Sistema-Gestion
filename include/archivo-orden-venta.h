#pragma once
#include <string>
#include "orden-venta.h"

class ArchivoOrdenVenta{
    private:
        const char * _nombreArchivo  = "db/orden-venta.dat";
        
    public:
        ArchivoOrdenVenta();
        bool crear();
        bool guardar(OrdenVenta ordenventa);
        bool guardar(OrdenVenta ordenventa, int posicion);
        int buscar(int idCliente);
        OrdenVenta leer(int posicion);
        int CantidadRegistros();
        void leer(int cantidadRegistros, OrdenVenta *vector);
};