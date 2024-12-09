#include "../include/producto.h"
#include <cstring>

Producto::Producto(){
   strcpy(this->_codigo,"");
   strcpy(this->_descripcion,"");
   strcpy(this->_tipoMedicion,"");
   this->_stock = 0;
   this->_futuro = 0;
   this->_origenInterno = false;
}

Producto::Producto(std::string codigo, std::string descripcion,
                 std::string tipoMedicion, int stock, int futuro, bool origenInterno){
   strcpy(this->_codigo,codigo.c_str());
   strcpy(this->_descripcion,descripcion.c_str());
   strcpy(this->_tipoMedicion,tipoMedicion.c_str());
   this->_stock = 0;
   this->_futuro = futuro;
   this->_origenInterno = origenInterno;
}

std::string Producto::getCodigo(){
   return std::string(this->_codigo);
}

void Producto::setCodigo(std::string codigo){
   strcpy(this->_codigo,codigo.c_str());
}

std::string Producto::getDescripcion(){
   return std::string(this->_descripcion);
}

void Producto::setDescripcion(std::string descripcion){
   strcpy(this->_descripcion,descripcion.c_str());
}

std::string Producto::getTipoMedicion(){
   return std::string(this->_tipoMedicion);
}

void Producto::setTipoMedicion(std::string medicion){
   strcpy(this->_tipoMedicion,medicion.c_str());
}

int Producto::getStock(){
   return this->_stock;
}

void Producto::setStock(int futuro){
   this->_stock = futuro;
}

int Producto::getFuturo(){
   return this->_futuro;
}

void Producto::setFuturo(int futuro){
   this->_futuro = futuro;
}

bool Producto::isInsumo(){
   return !(this->_origenInterno);
}
bool Producto::isProducto(){
   return this->_origenInterno;
}

void Producto::setOrigen(bool origen){
   this->_origenInterno = origen;
}

//funcionalidades insumo

bool Producto::getEstaBorrado(){
   return this->_estaBorrado;
}

void Producto::setEstaBorrado(bool borrado){
   this->_estaBorrado = borrado;
}