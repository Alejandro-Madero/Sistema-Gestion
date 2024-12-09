#include "../include/archivo-movimientos.h"

ArchivoMovimientos::ArchivoMovimientos(){

}

bool ArchivoMovimientos::crear(){
    FILE *pArchivo = fopen(_nombreArchivo, "wb+");
    if(pArchivo == NULL){
        return false;
    }
    fclose(pArchivo);
    return true;
}

bool ArchivoMovimientos::guardar(Movimientos movimientos){
    FILE *pArchivo = fopen(_nombreArchivo, "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&movimientos, sizeof(movimientos), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool ArchivoMovimientos::guardar(Movimientos movimientos, int posicion){
    FILE *pArchivo = fopen(_nombreArchivo, "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Movimientos) * posicion, SEEK_SET);
    bool ok = fwrite(&movimientos, sizeof(Movimientos), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int ArchivoMovimientos::buscar(int IDCliente){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return -1;
    }
    Movimientos movimientos;
    int i = 0;
    while(fread(&movimientos, sizeof(Movimientos), 1, pArchivo)){
        if(movimientos.getNroMovimiento() == IDCliente){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}

Movimientos ArchivoMovimientos::leer(int posicion){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return Movimientos();
    }
    Movimientos movimientos;
    fseek(pArchivo, sizeof(Movimientos) * posicion, SEEK_SET);
    fread(&movimientos, sizeof(Movimientos), 1, pArchivo);
    fclose(pArchivo);
    return movimientos;
}

int ArchivoMovimientos::CantidadRegistros(){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(Movimientos);
    fclose(pArchivo);
    return cantidadRegistros;
}

void ArchivoMovimientos::leer(int cantidadRegistros, Movimientos *vector){
    FILE *pArchivo = fopen(_nombreArchivo, "rb");
    if(pArchivo == NULL){
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(Movimientos), 1, pArchivo);
    }
    fclose(pArchivo);
}

