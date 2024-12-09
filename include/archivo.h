#pragma once
#include <string>

class Archivo {
public:
	Archivo(size_t tamanioRegistro, std::string nombreArchivo);
	bool crear();
	int calcularCantidadRegistros();
	int aumentarRegistros();
	int getCantidadRegistros();
	void setCantidadRegistros(bool abrirArchivo = true, int cantidadRegistros = 0);
	virtual const char* getNombreArchivo() const = 0;

private:
	size_t _tamanioRegistro;
	int _cantidadRegistros = -1;
protected: 
	std::string _nombreArchivo;
};