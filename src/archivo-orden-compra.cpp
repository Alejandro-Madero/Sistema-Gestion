#include "../include/archivo-orden-compra.h"

ArchivoOrdenCompra::ArchivoOrdenCompra() : Archivo(sizeof(OrdenCompra), "db/orden-compra.dat") {

}
ArchivoOrdenCompra::ArchivoOrdenCompra(size_t tamanioRegistro, std::string nombreArchivo) : Archivo(tamanioRegistro, nombreArchivo){

}
bool ArchivoOrdenCompra::guardar(OrdenCompra orden){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&orden, sizeof(orden), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}
bool ArchivoOrdenCompra::guardar(OrdenCompra orden, int posicion){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(OrdenCompra) * posicion, SEEK_SET);
    bool ok = fwrite(&orden, sizeof(OrdenCompra), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}
int ArchivoOrdenCompra::buscar(int IDCliente){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }
    OrdenCompra orden;
    int i = 0;
    while(fread(&orden, sizeof(OrdenCompra), 1, pArchivo)){
        if(orden.getIdProveedor() == IDCliente){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}
OrdenCompra ArchivoOrdenCompra::Leer(int posicion){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return OrdenCompra();
    }
    OrdenCompra orden;
    fseek(pArchivo, sizeof(OrdenCompra) * posicion, SEEK_SET);
    fread(&orden, sizeof(OrdenCompra), 1, pArchivo);
    fclose(pArchivo);
    return orden;
}
void ArchivoOrdenCompra::Leer(int cantidadRegistros, OrdenCompra *vector){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(OrdenCompra), 1, pArchivo);
    }
    fclose(pArchivo);
}
const char* ArchivoOrdenCompra::getNombreArchivo() const {
    return  "db/orden-compra.dat";
}