#include "../include/archivo-usuario.h"
#include <cstdio>

ArchivoUsuario::ArchivoUsuario() : Archivo(sizeof(Usuario),"db/usuario.dat" ) {};
ArchivoUsuario::ArchivoUsuario(size_t tamanioRegistro, std::string nombreArchivo) : Archivo(tamanioRegistro, nombreArchivo) {
}

bool ArchivoUsuario::guardar(Usuario usuario){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    bool ok = fwrite(&usuario, sizeof(usuario), 1, pArchivo);
    if (ok) {        
        this->aumentarRegistros();
    }
    fclose(pArchivo);
    return ok;
}
bool ArchivoUsuario::guardar(Usuario usuario, int posicion){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb+");
    if(pArchivo == NULL){
        return false;
    }
    fseek(pArchivo, sizeof(Usuario) * posicion, SEEK_SET);
    bool ok = fwrite(&usuario, sizeof(Usuario), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}
int ArchivoUsuario::buscar(std::string busqueda, int tipoDeBusqueda){

    // tipoDeBusqueda indica lo que queremos buscar:
    // 1- usuario
    // 2- email
    // 3- telefono

    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return -1;
    }
    Usuario usuario;
    int pos = 0; 

    while(fread(&usuario, sizeof(Usuario), 1, pArchivo)){ 
        switch (tipoDeBusqueda) {
        case 1: {
            if (usuario.getNombreUsuario() == busqueda) {
                fclose(pArchivo);
                return pos;                
            }
            break;
        }
        case 2: {
            if (usuario.getEmail() == busqueda) {
                fclose(pArchivo);
                return pos;
            }
            break;
        }
          case 3: {
              if (usuario.getTelefono() == busqueda){
                  fclose(pArchivo);
                  return pos;
              }
              break;
        }
        }  
        pos++;
    }
    fclose(pArchivo);
    return -1;
}
Usuario ArchivoUsuario::Leer(int posicion){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return Usuario();
    }
    Usuario usuario;
    fseek(pArchivo, sizeof(Usuario) * posicion, SEEK_SET);
    fread(&usuario, sizeof(Usuario), 1, pArchivo);
    fclose(pArchivo);
    return usuario;
}
void ArchivoUsuario::Leer(int cantidadRegistros, Usuario *vector){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){
        return;
    }
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vector[i], sizeof(Usuario), 1, pArchivo);
    }
    fclose(pArchivo);
}
Usuario* ArchivoUsuario::LeerTodos(){
    FILE *pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
    if(pArchivo == NULL){        
        return nullptr;
    }
    fseek(pArchivo, 0, SEEK_END);
    int tamanoArchivo = ftell(pArchivo);
    int cantidadRegistros = tamanoArchivo / sizeof(Usuario);

    //Actualizamos la cantidad de registros

    this->setCantidadRegistros(false, cantidadRegistros);

    if (tamanoArchivo % sizeof(Usuario) != 0) {        
        system("pause"); 
        fclose(pArchivo);
        cantidadRegistros = 0;
        return nullptr;
    }
    Usuario* vectorUsuarios = new Usuario[cantidadRegistros];
    if(vectorUsuarios == NULL){
        fclose(pArchivo);
        return nullptr;
    }

    fseek(pArchivo, 0, SEEK_SET);
    for(int i = 0; i < cantidadRegistros; i++){
        fread(&vectorUsuarios[i], sizeof(Usuario), 1, pArchivo);
    }
    fclose(pArchivo);

    return vectorUsuarios;
}
const char* ArchivoUsuario::getNombreArchivo() const {
    return "db/usuario.dat";
}