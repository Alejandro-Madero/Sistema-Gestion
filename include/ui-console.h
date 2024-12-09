#pragma once
#include <iostream>
#include <iomanip>

#include "manager.h"

class UiConsole {
  public:
   static const char* RESET ;
   static const char* ROJO ;
   static const char* VERDE;
   static const char* AZUL;
   static const char* AMARILLO;
   static const char* BOLD;
   static const char* SUBRAYADO;

   UiConsole();
   void setUsuario(std::string usuario);
   int mostrarMenuPrincipal();   
   int mostrarMenuProductos();
   int mostrarMenuProveedores();
   int mostrarMenuClientes();
   int mostrarMenuProduccion();
   int mostrarMenuVentas();
   int mostrarMenuUsuarios();
   int mostrarMenuEstadisticas();
   int mostrarMenuSeguridad();
   void mostrarMenuLogin(std::string& user, std::string& pass, int intentos);
   void configurarConsola();
   void limpiarConsola();
   void opcionIncorrecta();
   static bool volverAlMenuAnterior(std::string input);
   void pausa();
   bool pedirNumero(int& numResult);   

   //funcionalidades del menu usuarios
   Usuario agregarUsuario(std::string nombreUsuario, Manager& manager);
   int mostrarMenuModificacionUsuario(Usuario& usuario);     
   void listarUsuario(std::string nombreUsuario,char tipoUsuario, std::string email, std::string telefono);
   int menuEditarMiPerfil(Usuario& usuarioLoggeado);
   void procesarActualizacionUsuario(Manager& manager, Usuario& usuario, int posicionUsuario, std::string campo);
   void mostrarPerfil(Usuario& usuario, bool root);
   std::string mostrarRol(char rol); 


   std::string pedirCodigoProducto();
   Producto agregarProducto(std::string codigo,bool isInsumo);
   void mostrarProductos(Producto* insumos,int cantidad);
   int stockProducto();
 

  private:
   std::string _nombreUsuario;
};