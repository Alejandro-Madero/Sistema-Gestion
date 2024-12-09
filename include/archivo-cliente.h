#pragma once
#include <string>
#include "cliente.h"
#include "archivo.h"

class ArchivoCliente : public Archivo{        
    public:
        ArchivoCliente(); 
        ArchivoCliente(size_t tamanioRegistro, std::string nombreArchivo);      
        bool guardar(Cliente cliente);
        bool guardar(Cliente cliente, int posicion);
        int buscar(int IDCliente);
        Cliente leer(int posicion);       
        void leer(int cantidadRegistros, Cliente *vector);
        const char* getNombreArchivo() const override;
};