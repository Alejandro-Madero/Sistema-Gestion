#pragma once
#include <string>
#include "movimientos.h"
#include "archivo.h"

class ArchivoMovimientos : public Archivo{ 
        
    public:
        ArchivoMovimientos();
        ArchivoMovimientos(size_t tamanioRegistro, std::string nombreArchivo);        
        bool guardar(Movimientos movimientos);
        bool guardar(Movimientos movimientos, int posicion);
        int buscar(int nroMovimiento);
        Movimientos leer(int posicion);        
        void leer(int cantidadRegistros, Movimientos *vector);
        const char* getNombreArchivo() const override; 

};