#pragma once
#include <iostream>
#include "fecha.h"

class Movimientos{
  public:
   Movimientos();
   Movimientos(Fecha fecha, std::string motivo,
               char tipo, std::string id);
   std::string getId();
   void setId(std::string id);
   Fecha getFecha();
   void setFecha(Fecha f);  
   char getTipoMovimiento();
   void setTipoMovimiento(char tipo);   
   int getNroMovimiento();
   void setNroMovimiento(int nroMovimiento);


  private:
   int _nroMovimiento;
   Fecha _fecha;   
   char _tipoMovimiento;  //'c' compra, 'v' venta   
   char _id[30]; // codigo unico 
};