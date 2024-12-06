#pragma once
#include <iostream>
#include "fecha.h"

class Persona{
  public:
   Persona();
   Persona(int id, int telefono,
               char tipoFJ, std::string nombre, std::string direccion, std::string email);
   Fecha getFecha();
   void setFecha(Fecha f);
   char getTipoFJ();
   void setTipoFJ(char tipoFJ);
   int getId();
   int getTelefono(); 
   void setId(int id);
   std::string getNombre();
   void setNombre(std::string nombre);
   std::string getDireccion();
   void setDireccion(std::string direccion);
   std::string getEmail();
   void setEmail(std::string email);
   static bool validarNombreCompleto(std::string nombreCompleto);
   static bool validarEmail(std::string email);
   static bool validarDireccion(std::string direccion);
   static bool validarTelefono(std::string telefono);
   bool actualizarNombre();
   bool actualizarEmail(Manager& manager);
   bool actualizarDireccion(); 

  protected:
   int _id;
   int _telefono;
   char tipoFJ; //fisica F , juridica J
   char _nombre[30];
   char _direccion[50];
   char _email[60];
   bool _activo;
   Fecha _fechaIngreso;
};