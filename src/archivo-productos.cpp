#include "../include/archivo-productos.h"

#include <cstring>

ArchivoProducto::ArchivoProducto() {}

bool ArchivoProducto::crear(){
    FILE *pArchivo = fopen(_nombreArchivo, "wb+");
    if(pArchivo == NULL){
        return false;
    }
    fclose(pArchivo);
    return true;
}

bool ArchivoProducto::guardar(Producto Producto){
    FILE *pArchivo = fopen(_nombreArchivo, "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&Producto, sizeof(Producto), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoProducto::guardar(Producto Producto, int posicion){
    FILE *pArchivo = fopen(_nombreArchivo, "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Producto) * posicion, SEEK_SET);
    bool ok = fwrite(&Producto, sizeof(Producto), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoProducto::buscar(std::string IdProducto){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return -1;
    }
    Producto Producto;
    int i = 0;
    while(fread(&Producto, sizeof(Producto), 1, pArchivo)){
        if(Producto.getCodigo() == IdProducto){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

Producto ArchivoProducto::leer(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return Producto();
    }
    Producto Producto;
    fseek(pArchivo, sizeof(Producto) * posicion, SEEK_SET);
    fread(&Producto, sizeof(Producto), 1, pArchivo);
    fclose(pArchivo);
    return Producto;
}

int ArchivoProducto::CantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Producto);
    fclose(pArchivo);
    return cantidadRegistros;
}

void ArchivoProducto::leer(int cantidadRegistros, Producto *vector){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(Producto), 1, pArchivo);
    }
    fclose(pArchivo);
}