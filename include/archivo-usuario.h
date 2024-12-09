#pragma once
#include <string>
#include  "usuario.h"
#include "archivo.h"

class ArchivoUsuario : public Archivo{
    public:
        ArchivoUsuario();
        ArchivoUsuario(size_t tamanioRegistro, std::string nombreArchivo);      
        bool guardar(Usuario usuario);
        bool guardar(Usuario usuario, int posicion);
        int buscar(std::string busqueda, int tipoDeBuqueda);        
        Usuario Leer(int posicion);
        Usuario* LeerTodos();              
        void Leer(int cantidadRegistros, Usuario *vector);    
        const char* getNombreArchivo() const override; 

    private:        
        int _cantidadRegistros = -1;         
};