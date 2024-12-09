#pragma once
#include <string>
#include "orden-compra.h"
#include "archivo.h"

class ArchivoOrdenCompra : public Archivo{   
    public:
        ArchivoOrdenCompra(); 
        ArchivoOrdenCompra(size_t tamanioRegistro, std::string nombreArchivo);       
        bool guardar(OrdenCompra ordenCompra);
        bool guardar(OrdenCompra ordenCompra, int posicion);
        int buscar(int idProveedor);
        OrdenCompra Leer(int posicion);        
        void Leer(int cantidadRegistros, OrdenCompra *vector);
        const char* getNombreArchivo() const override; 
};