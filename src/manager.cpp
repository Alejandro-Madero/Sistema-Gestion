#include "../include/manager.h"

#include <direct.h>

Manager::Manager() {
   this->_cacheListadoUsuarios = nullptr;  
   this->archivoCliente = ArchivoCliente();   
   
   this->archivoMovimientos = ArchivoMovimientos();
   this->archivoOrdenCompra = ArchivoOrdenCompra(); 
   this->archivoOrdenVenta = ArchivoOrdenVenta();
   
   this->archivoUsuario = ArchivoUsuario();
   if (archivoUsuario.getCantidadRegistros() < 1) {
      if (_mkdir("db") != 0) {
        return; // Directorio creado exitosamente
      } 
      this->archivoCliente.Crear();          
      this->archivoMovimientos.Crear();
      this->archivoOrdenCompra.Crear();     
      this->archivoOrdenVenta.Crear();     
      this->archivoUsuario.Crear();
      this->archivoUsuario.Guardar(Usuario('a',"pass","root",Fecha(1,1,2000),0,"0", 'F', "root", "root", "root"));
   }
}

bool Manager::login(std::string user, std::string pass) {
	int posicionUsuario = this->buscarUsuario(user, false);
	if (posicionUsuario < 0) {
		return false;
	}

	Usuario usuario = this->archivoUsuario.Leer(posicionUsuario);

    bool usuarioActivo = usuario.getEstadoUsuario();

    if (!usuarioActivo) {
        return false; 
    }

	if (usuario.getPassword() != pass) {
		return false;
	}

	this->setUsarioLoggeado(usuario);
	this->_nombreUsuario = usuario.getNombreUsuario();
	this->_rolUsuario = usuario.getRol();
	return true;
}


std::string Manager::getNombreUsuario() {
	return this->_nombreUsuario;
}
int Manager::buscarUsuario(std::string nombreUsuario) {
   return this->archivoUsuario.Buscar(nombreUsuario,1);
}
int Manager::buscarUsuario(std::string nombreUsuario, bool buscarEnCache) {
	if (buscarEnCache) {
		return this->buscar(nombreUsuario, 1);
	}
	else {
		return this->archivoUsuario.Buscar(nombreUsuario, 1);
	}


}

int Manager::buscarEmail(std::string email, bool buscarEnCache) {
	if (buscarEnCache) {
		return this->buscar(email, 2);
	}
	else {
		return this->archivoUsuario.Buscar(email, 2);
	}
}

int Manager::buscarTelefono(std::string telefono, bool buscarEnCache) {
	if (buscarEnCache) {
		return this->buscar(telefono, 3);
	}
	else {
		return this->archivoUsuario.Buscar(telefono, 3);
	}
}

bool Manager::agregarUsuario(Usuario usuario) {
	return this->archivoUsuario.Guardar(usuario);
}

Usuario* Manager::getListaUsuarios() {
	return this->archivoUsuario.LeerTodos();
}

int Manager::cantidadUsuarios() {
	return this->archivoUsuario.getCantidadRegistros();
}

Manager::~Manager() {
   if(_cacheListadoUsuarios!= nullptr){
	   delete[] _cacheListadoUsuarios;
   }
}

void Manager::actualizarCacheUsuarios() {
	this->_cacheListadoUsuarios = this->getListaUsuarios();
}

Usuario* Manager::getCacheListadoUsuarios() {
	return this->_cacheListadoUsuarios;
}
int Manager::buscar(std::string busqueda, int tipoDeBusqueda) {
	// tipoDeBusqueda indica lo que queremos buscar:
	// 1- usuario
	// 2- email
	// 3- telefono

	int cantidadRegistros = this->archivoUsuario.getCantidadRegistros();

	int i = 0;
	while (i < cantidadRegistros) {
		switch (tipoDeBusqueda) {
		case 1: {		
			if (this->_cacheListadoUsuarios[i].getNombreUsuario() == busqueda) {
				return i;
			}
			break;
		}
		case 2: {
			if (this->_cacheListadoUsuarios[i].getEmail() == busqueda) {
				return i;
			}
			break;
		}
		case 3: {
			if (this->_cacheListadoUsuarios[i].getTelefono() == busqueda) {
				return i;
			}
			break;
		}
		}
		i++;
	}
	return -1;
}

Usuario Manager::leerUsuario(int posicion) {
	return this->archivoUsuario.Leer(posicion);
}

bool Manager::reescribirUsuario(Usuario usuario, int posicion) {
	return this->archivoUsuario.Guardar(usuario, posicion);
}


bool Manager::esAdmin() {
   if (this->_rolUsuario == 'A' || this->_rolUsuario == 'a') {
      return true;
   }
   return false;
}

bool Manager::esComprador() {
   if (this->_rolUsuario == 'C' || this->_rolUsuario == 'c') {
      return true;
   }
   return false;
}

bool Manager::esVendedor() {
   if (this->_rolUsuario == 'V' || this->_rolUsuario == 'v') {
      return true;
   }
   return false;
}

// funcionalidades insumos




bool Manager::listaRecursos(int pos, int cant, bool isProducto, bool borrado, Recurso*& vector, int &vectorSize) {
   
	return true; 
}




// funcionalidades productos

int Manager::buscarProducto(std::string codigo) {
	return 1;
}

int Manager::agregarProducto(Recurso producto) {
	return 1;
}

bool Manager::borrarProducto(int pos) {
  // return this->borrarInsumo(pos);

	return true;
}
bool Manager::modificarStockRecurso(int stock, int pos) {
    ////return this->modificarStockInsumo(stock, pos);
	return true;
}





Usuario Manager::getUsuarioLoggeado() {
    return this->_usuarioLoggeado;
}


void Manager::setUsarioLoggeado(Usuario usuario) {
    this->_usuarioLoggeado = usuario;
}

Recurso Manager::getRecurso(int pos) {
	return Recurso();
}
	int Manager::buscarInsumo(std::string codigo) {
		return 1;
	};

int Manager::agregarInsumo(Recurso insumo) {
	return 1;
};

bool Manager::borrarInsumo(int pos) { return true; };
bool Manager::modificarInsumo(Recurso insumo, int pos) {
	return true;
}
bool Manager::modificarStockInsumo(int stock, int pos) { return true; };