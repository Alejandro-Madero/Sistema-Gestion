#pragma once
#include <string>
#include  "Producto.h"

class ArchivoProducto{
    private:
        const char * _nombreArchivo  = "db/productos.dat";
        
    public:
        ArchivoProducto();
        bool crear();
        bool guardar(Producto Productos);
        bool guardar(Producto Productos, int posicion);
        int buscar(std::string codigo);
        Producto leer(int posicion);
        int CantidadRegistros();
        void leer(int cantidadRegistros, Producto *vector);
};