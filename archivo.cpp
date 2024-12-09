#include "../include/archivo.h"
#include <cstdio>

Archivo::Archivo() {
    this->_cantidadRegistros = this->calcularCantidadRegistros();
}

bool Archivo::crear() {
    FILE* pArchivo = fopen(_nombreArchivo, "wb+");
    if (pArchivo == NULL) {
        return false;
    }
    fclose(pArchivo);
    return true;
}
bool Archivo::guardar(Usuario usuario) {
    FILE* pArchivo = fopen(_nombreArchivo, "ab");
    if (pArchivo == NULL) {
        return false;
    }
    bool ok = fwrite(&usuario, sizeof(usuario), 1, pArchivo);
    if (ok) {
        this->aumentarRegistros();
    }
    fclose(pArchivo);
    return ok;
}

bool Archivo::guardar(Usuario usuario, int posicion) {
    FILE* pArchivo = fopen(_nombreArchivo, "rb+");
    if (pArchivo == NULL) {
        return false;
    }
    fseek(pArchivo, sizeof(Usuario) * posicion, SEEK_SET);
    bool ok = fwrite(&usuario, sizeof(Usuario), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

int Archivo::buscar(std::string busqueda, int tipoDeBusqueda) {

    // tipoDeBusqueda indica lo que queremos buscar:
    // 1- usuario
    // 2- email
    // 3- telefono

    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == NULL) {
        return -1;
    }
    Usuario usuario;
    int pos = 0;

    while (fread(&usuario, sizeof(Usuario), 1, pArchivo)) {
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
            if (usuario.getTelefono() == busqueda) {
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



int Archivo::setCantidadRegistros(int tamanioRegistro) {
    FILE* pArchivo = fopen(this->_nombreArchivo, "rb");
    if (pArchivo == NULL) {
        return 0;
    }
    fseek(pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(pArchivo) / sizeof(tamanioRegistro);
    fclose(pArchivo);
    return cantidadRegistros;
}



int Archivo::aumentarRegistros() {
    this->_cantidadRegistros++;
    return this->_cantidadRegistros;
}

int Archivo::getCantidadRegistros() {
    return this->_cantidadRegistros;
};

