#pragma once
#include <iostream>

class Producto {
  public:  
	Producto();
   Producto(std::string codigo, std::string descripcion,  int stock, int precio);
   std::string getCodigo();
   void setCodigo(std::string codigo);
   std::string getDescripcion();
   void setDescripcion(std::string descripcion);  
   int getStock();
   void setStock(int stock);   
   bool getEstaBorrado();
   void setEstaBorrado(bool borrado);
   void setPrecio(int precio);
   int getPrecio(); 
   void disminuirStock(int ventas);
   void aumentarStock(int ingresos); 

   //Validaciones:
   static bool validarCodigoProducto(std::string codigo); 
   static bool validarDescripcionProducto(std::string descripcion); 
   static bool validarStockYPrecioProducto(std::string stock); 
  private:
   char _codigo[30];
   char _descripcion[51];
   int _stock; 
   int _precio; 
   bool _estaBorrado;
};