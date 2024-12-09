#pragma once
#include <string>
#include "movimientos.h"

class ArchivoMovimientos{
    private:
        const char * _nombreArchivo  = "db/movimientos.dat";
        
    public:
        ArchivoMovimientos();
        bool crear();
        bool guardar(Movimientos movimientos);
        bool guardar(Movimientos movimientos, int posicion);
        int buscar(int nroMovimiento);
        Movimientos leer(int posicion);
        int CantidadRegistros();
        void leer(int cantidadRegistros, Movimientos *vector);
};