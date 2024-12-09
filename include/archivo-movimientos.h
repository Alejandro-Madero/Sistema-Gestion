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
        Movimientos Leer(int posicion);        
        void Leer(int cantidadRegistros, Movimientos *vector);
        const char* getNombreArchivo() const override; 

};