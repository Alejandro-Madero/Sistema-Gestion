#include "../include/producto.h"
#include <cstring>
#include <regex>
Producto::Producto() {
	this->setDescripcion("");
	this->setCodigo("");
	this->setStock(0);
	this->setEstaBorrado(false);
};
Producto::Producto(std::string codigo, std::string descripcion, int stock) {
	this->setDescripcion(descripcion);
	this->setCodigo(codigo);
	this->setStock(stock);
	this->setEstaBorrado(false);
}

std::string Producto::getCodigo() {
	return std::string(this->_codigo);
}

void Producto::setCodigo(std::string codigo) {
	strcpy(this->_codigo, codigo.c_str());
}

std::string Producto::getDescripcion() {
	return std::string(this->_descripcion);
}

void Producto::setDescripcion(std::string descripcion) {
	strcpy(this->_descripcion, descripcion.c_str());
}

int Producto::getStock() {
	return this->_stock;
}

void Producto::setStock(int stock) {
	this->_stock = stock;
}

//funcionalidades insumo

bool Producto::getEstaBorrado() {
	return this->_estaBorrado;
}

void Producto::setEstaBorrado(bool borrado) {
	this->_estaBorrado = borrado;
}

bool Producto::validarCodigoProducto(std::string codigo) {
	if (codigo.length() > 20 || codigo.length() == 0)
	{
		return false;
	}

	return true;
}

bool Producto::validarDescripcionProducto(std::string descripcion) {	
	if (descripcion.length() > 50 || descripcion.length() < 3)
	{
		return false;
	}

	return true;
	
}
 bool Producto::validarStockProducto(std::string stock) {
	 return std::all_of(stock.begin(), stock.end(), ::isdigit);
 };