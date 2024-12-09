#pragma once
#include <string>
#include  "Producto.h"
#include "archivo.h"

class ArchivoProducto: public Archivo {
  
        
    public:
        ArchivoProducto(); 
        ArchivoProducto(size_t tamanioRegistro, std::string nombreArchivo);       
        bool guardar(Producto Productos);
        bool guardar(Producto Productos, int posicion);
        int buscar(std::string codigo);
        Producto leer(int posicion);        
        void leer(int cantidadRegistros, Producto *vector);
        const char* getNombreArchivo() const override; 
        Producto* leerTodos();
};