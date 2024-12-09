#include "../include/archivo-orden-compra.h"

ArchivoOrdenCompra::ArchivoOrdenCompra(){

}

bool ArchivoOrdenCompra::crear(){
    FILE *pArchivo = fopen(_nombreArchivo, "wb+");
    if(pArchivo == NULL){
        return false;
    }
    fclose(pArchivo);
    return true;
}

bool ArchivoOrdenCompra::guardar(OrdenCompra orden){
    FILE *pArchivo = fopen(_nombreArchivo, "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&orden, sizeof(orden), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoOrdenCompra::guardar(OrdenCompra orden, int posicion){
    FILE *pArchivo = fopen(_nombreArchivo, "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(OrdenCompra) * posicion, SEEK_SET);
    bool ok = fwrite(&orden, sizeof(OrdenCompra), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoOrdenCompra::buscar(int IDCliente){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
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

OrdenCompra ArchivoOrdenCompra::leer(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return OrdenCompra();
    }
    OrdenCompra orden;
    fseek(pArchivo, sizeof(OrdenCompra) * posicion, SEEK_SET);
    fread(&orden, sizeof(OrdenCompra), 1, pArchivo);
    fclose(pArchivo);
    return orden;
}

int ArchivoOrdenCompra::CantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(OrdenCompra);
    fclose(pArchivo);
    return cantidadRegistros;
}

void ArchivoOrdenCompra::leer(int cantidadRegistros, OrdenCompra *vector){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(OrdenCompra), 1, pArchivo);
    }
    fclose(pArchivo);
}

