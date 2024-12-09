#include "../include/archivo-cliente.h"

ArchivoCliente::ArchivoCliente() : Archivo(sizeof(Cliente), "db/cliente.dat") {}
ArchivoCliente::ArchivoCliente(size_t tamanioRegistro, std::string nombreArchivo) : Archivo(tamanioRegistro, nombreArchivo){

}
bool ArchivoCliente::guardar(Cliente cliente){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&cliente, sizeof(cliente), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}
bool ArchivoCliente::guardar(Cliente cliente, int posicion){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Cliente) * posicion, SEEK_SET);
    bool ok = fwrite(&cliente, sizeof(Cliente), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}
int ArchivoCliente::buscar(int IDCliente){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }
    Cliente cliente;
    int i = 0;
    while(fread(&cliente, sizeof(Cliente), 1, pArchivo)){
        if(cliente.getId() == IDCliente){
            fclose(pArchivo);
            return i;
        }
        i++;
    }
    fclose(pArchivo);
    return -1;
}
Cliente ArchivoCliente::leer(int posicion){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return Cliente();
    }
    Cliente cliente;
    fseek(pArchivo, sizeof(Cliente) * posicion, SEEK_SET);
    fread(&cliente, sizeof(Cliente), 1, pArchivo);
    fclose(pArchivo);
    return cliente;
}
void ArchivoCliente::Leer(int cantidadRegistros, Cliente *vector){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(Cliente), 1, pArchivo);
    }
    fclose(pArchivo);
}
const char* ArchivoCliente::getNombreArchivo() const {
    return "db/cliente.dat";
}