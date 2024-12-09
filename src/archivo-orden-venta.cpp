#include "../include/archivo-orden-venta.h"

ArchivoOrdenVenta::ArchivoOrdenVenta() : Archivo(sizeof(OrdenVenta), "db/orden-venta.dat") {}
ArchivoOrdenVenta::ArchivoOrdenVenta(size_t tamanioRegistro, std::string nombreArchivo) : Archivo(tamanioRegistro, nombreArchivo){

}

bool ArchivoOrdenVenta::guardar(OrdenVenta orden){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&orden, sizeof(orden), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}
bool ArchivoOrdenVenta::guardar(OrdenVenta orden, int posicion){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(OrdenVenta) * posicion, SEEK_SET);
    bool ok = fwrite(&orden, sizeof(OrdenVenta), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}
int ArchivoOrdenVenta::buscar(int IDCliente){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }
    OrdenVenta orden;
    int i = 0;
    while(fread(&orden, sizeof(OrdenVenta), 1, pArchivo)){
        if(orden.getIdCliente() == IDCliente){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}
OrdenVenta ArchivoOrdenVenta::leer(int posicion){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return OrdenVenta();
    }
    OrdenVenta orden;
    fseek(pArchivo, sizeof(OrdenVenta) * posicion, SEEK_SET);
    fread(&orden, sizeof(OrdenVenta), 1, pArchivo);
    fclose(pArchivo);
    return orden;
}
void ArchivoOrdenVenta::leer(int cantidadRegistros, OrdenVenta *vector){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(OrdenVenta), 1, pArchivo);
    }
    fclose(pArchivo);
}
const char* ArchivoOrdenVenta::getNombreArchivo() const {
    return "db/orden-venta.dat";
}