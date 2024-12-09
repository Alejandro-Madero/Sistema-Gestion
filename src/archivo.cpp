#include "../include/archivo.h"
#include <cstdio>
#include <iostream>
Archivo::Archivo(size_t tamanioRegistro, std::string nombreArchivo) {
	this->_tamanioRegistro = tamanioRegistro;
	this->_nombreArchivo = nombreArchivo;
	this->setCantidadRegistros(true);
}

bool Archivo::crear() {
	FILE* pArchivo = fopen(this->_nombreArchivo.c_str(), "wb+");
	if (pArchivo == NULL) {
		return false;
	}
	fclose(pArchivo);
	return true;
}

int Archivo::calcularCantidadRegistros() {
	FILE* pArchivo = fopen(this->_nombreArchivo.c_str(), "rb");
	if (pArchivo == NULL) {
		return 0;
	}
	fseek(pArchivo, 0, SEEK_END);
	int cantidadRegistros = ftell(pArchivo) / _tamanioRegistro;
	fclose(pArchivo);


	return cantidadRegistros;
}

void Archivo::setCantidadRegistros(bool abrirArchivo, int cantidadRegistros) {
	if (abrirArchivo) {
		this->_cantidadRegistros = this->calcularCantidadRegistros();
		return;
	}

	this->_cantidadRegistros = cantidadRegistros;

}


int Archivo::aumentarRegistros() {
	this->_cantidadRegistros++;
	return this->_cantidadRegistros;
}

int Archivo::getCantidadRegistros() {
	return this->_cantidadRegistros;
};

