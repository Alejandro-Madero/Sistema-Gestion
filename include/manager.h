#pragma once
#include <iostream>
#include "fecha.h"
#include "persona.h"
#include "Producto.h"
#include "cliente.h"
#include "usuario.h"
#include "orden.h"
#include "orden-compra.h"
#include "orden-venta.h"
#include "movimientos.h"
#include "archivo-cliente.h"
#include "archivo-movimientos.h"
#include "archivo-orden-compra.h"
#include "archivo-orden-venta.h"
#include "archivo-productos.h"
#include "archivo-usuario.h"
#include "manager.h"


class Manager {

public:
	Manager();
	~Manager();
	// Funcionalidades Usuario
	bool login(std::string user, std::string pass);
	bool agregarUsuario(Usuario usuario);
	Usuario* getListaUsuarios();
	int cantidadUsuarios();
	std::string getNombreUsuario();
	int buscarUsuario(std::string nombreUsuario);
	int buscarUsuario(std::string nombreUsuario, bool buscarEnCache);
	Usuario leerUsuario(int posicion);
	bool reescribirUsuario(Usuario usuario, int posicion);
	int buscarEmail(std::string email, bool buscarEnCache);
	int buscarTelefono(std::string telefono, bool buscarEnCache);
	void actualizarCacheUsuarios();
	int buscar(std::string busqueda, int tipoDeBusqueda);
	Usuario* getCacheListadoUsuarios();
	bool esAdmin();
	bool esComprador();
	bool esVendedor();
	Usuario getUsuarioLoggeado();
	void setUsarioLoggeado(Usuario usuario);

	//funcionalidades insumos
	
	int buscarInsumo(std::string codigo);
	int agregarInsumo(Producto insumo);
	bool borrarInsumo(int pos);	
	bool modificarInsumo(Producto insumo, int pos);
	bool modificarStockInsumo(int stock, int pos);
	
	
	
	Producto getProducto(int pos);
	bool listaProductos(int pos, int cantidad, bool isProducto, bool borrado, Producto*& vector, int& vectorSize);
	//funcionalidades productos
	int buscarProducto(std::string codigo);
	int agregarProducto(Producto producto);
	bool borrarProducto(int pos);
	bool modificarStockProducto(int stock, int pos);	
	
private:
	ArchivoCliente archivoCliente;			
	ArchivoMovimientos archivoMovimientos;
	ArchivoOrdenCompra archivoOrdenCompra;
	ArchivoOrdenVenta archivoOrdenVenta;
	ArchivoUsuario archivoUsuario;
	ArchivoProducto archivoProductos; 
	char _rolUsuario;	
	std::string _nombreUsuario;
	Usuario* _cacheListadoUsuarios;
	Usuario _usuarioLoggeado; 
};