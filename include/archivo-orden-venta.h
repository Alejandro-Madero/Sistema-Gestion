#pragma once
#include <string>
#include "orden-venta.h"
#include "archivo.h"

class ArchivoOrdenVenta : public Archivo{        
    public:
        ArchivoOrdenVenta(); 
        ArchivoOrdenVenta(size_t tamanioRegistro, std::string nombreArchivo);      
        bool guardar(OrdenVenta ordenventa);
        bool guardar(OrdenVenta ordenventa, int posicion);
        int buscar(int idCliente);
        OrdenVenta leer(int posicion);        
        void leer(int cantidadRegistros, OrdenVenta *vector);
        const char* getNombreArchivo() const override; 
};