#pragma once
#include <iostream>

class Producto {
  public:  
	Producto();
   Producto(std::string codigo, std::string descripcion,  int stock);
   std::string getCodigo();
   void setCodigo(std::string codigo);
   std::string getDescripcion();
   void setDescripcion(std::string descripcion);  
   int getStock();
   void setStock(int stock);  
   //funcionalidase insumo  
   bool getEstaBorrado();
   void setEstaBorrado(bool borrado);

   //Validaciones:
   static bool validarCodigoProducto(std::string codigo); 
   static bool validarDescripcionProducto(std::string descripcion); 
   static bool validarStockProducto(std::string stock); 
  private:
   char _codigo[30];
   char _descripcion[51];
   int _stock; 
   bool _estaBorrado;
};