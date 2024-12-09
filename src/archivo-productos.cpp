#include "../include/archivo-productos.h"

#include <cstring>

ArchivoProducto::ArchivoProducto() : Archivo(sizeof(Producto), "db/productos.dat") {}
ArchivoProducto::ArchivoProducto(size_t tamanioRegistro, std::string nombreArchivo): Archivo(tamanioRegistro, nombreArchivo) {}
bool ArchivoProducto::guardar(Producto Producto){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&Producto, sizeof(Producto), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}
bool ArchivoProducto::guardar(Producto Producto, int posicion){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Producto) * posicion, SEEK_SET);
    bool ok = fwrite(&Producto, sizeof(Producto), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}
int ArchivoProducto::buscar(std::string IdProducto){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
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
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return Producto();
    }
    Producto Producto;
    fseek(pArchivo, sizeof(Producto) * posicion, SEEK_SET);
    fread(&Producto, sizeof(Producto), 1, pArchivo);
    fclose(pArchivo);
    return Producto;
}
void ArchivoProducto::leer(int cantidadRegistros, Producto *vector){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(Producto), 1, pArchivo);
    }
    fclose(pArchivo);
}
const char* ArchivoProducto::getNombreArchivo() const {
    return "db/productos.dat"; 
}



Producto* ArchivoProducto::leerTodos() {
    FILE* pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if (pArchivo == NULL) {
        return nullptr;
    }
    fseek(pArchivo, 0, SEEK_END);
    int tamanoArchivo = ftell(pArchivo);
    int cantidadRegistros = tamanoArchivo / sizeof(Producto);

    //Actualizamos la cantidad de registros

    this->setCantidadRegistros(false, cantidadRegistros);

    if (tamanoArchivo % sizeof(Producto) != 0) {
        fclose(pArchivo);
        cantidadRegistros = 0;
        return nullptr;
    }
    Producto* vectorProductos = new Producto[cantidadRegistros];
    if (vectorProductos == NULL) {
        fclose(pArchivo);
        return nullptr;
    }

    fseek(pArchivo, 0, SEEK_SET);
    for (int i = 0; i < cantidadRegistros; i++) {
        fread(&vectorProductos[i], sizeof(Producto), 1, pArchivo);
    }
    fclose(pArchivo);

    return vectorProductos;
}