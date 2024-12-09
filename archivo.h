#pragma once
#include <string>

class Archivo {
public:
    Archivo();
    bool crear();
    int buscar(std::string busqueda, int tipoDeBuqueda); 
    int setCantidadRegistros();
    int aumentarRegistros();
    int getCantidadRegistros();   

private:
    const char* _nombreArchivo = "db/usuario.dat";
    int _cantidadRegistros;

};