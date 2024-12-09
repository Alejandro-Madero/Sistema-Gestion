#include <iostream>
#include <string>
#include "../include/menu.h"
#include "../include/manager.h"
#include "../include/ui-console.h"
#include "../include/usuario.h"

void Menu::menuPrincipal(Manager& manager, UiConsole& ui)
{
	int op;
	do
	{
		op = ui.mostrarMenuPrincipal();
		switch (op)
		{
		case 1:		
			this->menuProductos(manager, ui);
			break;
		case 2:
			this->menuClientes(manager, ui);
			break;
		case 3:
			this->menuVentas(manager, ui);
			break;
		case 4:
			this->menuUsuarios(manager, ui);
			break;
		case 5:
			this->menuEstadisticas(manager, ui);
			break;
		case 6:
			this->menuSeguridad(manager, ui);
			break;
		case 0:			
			break;
		default:			
			ui.opcionIncorrecta();
			break;
		}
	} while (op != 0);
}

bool Menu::menuLogin(Manager& manager, UiConsole& ui)
{
	std::string user, pass;
	int intentos = 5;
	bool formatoUsuarioValido, formatoContraseniaValida, credencialesCorrectas;
	while (intentos > 0)
	{
		ui.mostrarMenuLogin(user, pass, intentos);
		formatoUsuarioValido = Usuario::validarUsuario(user);
		formatoContraseniaValida = Usuario::validarContrasenia(pass);
		if (formatoUsuarioValido && formatoContraseniaValida)
		{
			credencialesCorrectas = manager.login(user, pass);
			if (credencialesCorrectas)
			{
				return true;
			}
		}
		intentos--;
	};
	return false;
}
void Menu::menuProductos(Manager& manager, UiConsole& ui)
{
	auto agregarProducto = [&]() -> void
		{
			ui.limpiarConsola();
			if (!manager.esAdmin())
			{
				std::cout << "No tiene permisos para dar de alta un nuevo producto." << std::endl;
				ui.pausa();
				return;
			}

			std::string codigoProducto = ui.pedirCodigoProducto();
			if (codigoProducto == "")
			{
				std::cout << UiConsole::ROJO << "El producto no pudo ser agregado correctamente. Intentelo nuevamente" << UiConsole::RESET << std::endl; 
				ui.pausa();
				return;
			}

			int posicionProducto = manager.buscarProducto(codigoProducto);
			if (posicionProducto >= 0)
			{
				std::cout << UiConsole::ROJO << "El codigo de producto ya existe. Intentelo nuevamente." << UiConsole::RESET << std::endl;
				ui.pausa();
				return;
			}
			
			Producto producto = ui.agregarProducto(codigoProducto, true);
			if (producto.getCodigo() == "")
			{
				ui.pausa();
				return;
			}
			if (manager.guardarProductoBaseDatos(producto) == true )
			{
				std::cout << UiConsole::VERDE <<"Producto dado de alta correctamente." << UiConsole::RESET <<std::endl;
			}
			else
			{
				std::cout << UiConsole::ROJO <<"El producto no se pudo dar de alta. Intentelo nuevamente." << UiConsole::RESET <<std::endl;
			}
			ui.pausa();
			return;
		};
	auto borrarProducto = [&]() -> void
		{
			ui.limpiarConsola();
			if (!manager.esAdmin())
			{
				std::cout << "No tiene permisos para borrar productos" << std::endl;
				ui.pausa();
				return;
			}
			std::string codigoProducto = ui.pedirCodigoProducto();
			if (codigoProducto == "")
			{
				std::cout << UiConsole::ROJO << "El producto no pudo ser borrado correctamente. Intentelo nuevamente" << UiConsole::RESET << std::endl;
				ui.pausa();
				return;
			}
			
			int posicionProducto = manager.buscarProducto(codigoProducto);
			if (posicionProducto < 0)
			{
				std::cout << UiConsole::ROJO <<  "El codigo de producto ingresado no existe. Intentelo nuevamente." << UiConsole::RESET<< std::endl;
				ui.pausa();
				return;
			}

			Producto producto = manager.getProducto(posicionProducto); 

			if (producto.getEstaBorrado()) {
				std::cout << UiConsole::ROJO << "El Producto ya se encuentra eliminado." << UiConsole::RESET <<std::endl;
				ui.pausa(); 
				return;
			}

			if (manager.borrarProducto(producto,posicionProducto))
			{
				std::cout << UiConsole::VERDE <<"El Producto se borro correctamente." << UiConsole::RESET << std::endl;
			}
			else
			{
				std::cout << UiConsole::ROJO << "No se pudo borrar el producto. Intentelo nuevamente." << UiConsole::RESET <<  std::endl;
			}
			ui.pausa();
			return;
		};
	auto modificarProducto = [&]() -> void
		{
			ui.limpiarConsola();
			if (!manager.esAdmin())
			{
				std::cout << "No tiene permisos para modificar productos" << std::endl;
				ui.pausa();
				return;
			}
			std::string codigo = ui.pedirCodigoProducto();
			if (codigo == "")
			{
				std::cout << "codigo incorrecto" << std::endl;
				ui.pausa();
				return;
			}
			int pos = manager.buscarProducto(codigo);
			if (pos == -3)
			{
				std::cout << "El codigo se esta usando como insumo" << std::endl;
				ui.pausa();
				return;
			}
			if (pos == -2)
			{
				std::cout << "El codigo esta mal escrito y no cumple con los criterios" << std::endl;
				ui.pausa();
				return;
			}
			if (pos == -4)
			{
				std::cout << "El producto esta borrado" << std::endl;
				ui.pausa();
				return;
			}
			if (pos < 0)
			{
				std::cout << "El producto no existe" << std::endl;
				ui.pausa();
				return;
			}
			Producto* producto = new Producto(manager.getProducto(pos));
			if (producto == nullptr)
			{
				std::cout << "no hay memoria disponible" << std::endl;
				ui.pausa();
				return;
			}
			std::cout << "Valor actual del producto : " << std::endl;
			ui.mostrarProductos(producto, 1);
			delete producto;
			std::cout << "Valor nuevo del producto : " << std::endl;
			Producto productoModificado = ui.agregarProducto(codigo, false);
		
			/*if (manager.modificarInsumo(productoModificado, pos))
			{
				std::cout << "Producto modificado correctamente" << std::endl;
			}
			else
			{
				std::cout << "No se pudo modificar el Producto" << std::endl;
			}*/
			ui.pausa();
			return;
		};
	auto stockProducto = [&]() -> void
		{
			ui.limpiarConsola();
			std::string codigoProducto = ui.pedirCodigoProducto();
			if (codigoProducto == "")
			{
				ui.pausa();
				return;
			}
			int pos = manager.buscarProducto(codigoProducto);
			if (pos == -3)
			{
				std::cout << "El codigo se esta usando como insumo" << std::endl;
				ui.pausa();
				return;
			}
			if (pos == -2)
			{
				std::cout << "El codigo esta mal escrito y no cumple con los criterios" << std::endl;
				ui.pausa();
				return;
			}
			if (pos == -4)
			{
				std::cout << "El producto esta borrado" << std::endl;
				ui.pausa();
				return;
			}
			if (pos < 0)
			{
				std::cout << "El producto no existe" << std::endl;
				ui.pausa();
				return;
			}
			Producto* producto = new Producto(manager.getProducto(pos));
			if (producto == nullptr)
			{
				std::cout << "no hay memoria disponible" << std::endl;
				ui.pausa();
				return;
			}
			ui.mostrarProductos(producto, 1);
			delete producto;
			int stock = ui.stockProducto();
			if (stock < 0)
			{
				ui.pausa();
				return;
			}
			if (!manager.esAdmin())
			{
				ui.pausa();
				return;
			}
			/*if (manager.modificarStockInsumo(stock, pos))
			{
				std::cout << "Stock modificado correctamente" << std::endl;
			}
			else
			{
				std::cout << "No se pudo modificar el stock" << std::endl;
			}*/
			ui.pausa();
			return;
		};
	auto listaProductos = [&]() -> void
		{
			ui.limpiarConsola();			
			
			Producto* productos = manager.leerProductos(); 
			int cantidadProductos = manager.getCantidadProductos(); 

			ui.mostrarProductos(productos, cantidadProductos); 
			
			ui.pausa();
			return; 
		};
	auto buscarProducto = [&]() -> void
		{
			ui.limpiarConsola();
			std::string codigoProducto = ui.pedirCodigoProducto();
			if (codigoProducto == "")
			{
				ui.pausa();
				return;
			}
			int pos = manager.buscarProducto(codigoProducto);
			if (pos == -3)
			{
				std::cout << "El codigo se esta usando como insumo" << std::endl;
				ui.pausa();
				return;
			}
			if (pos == -2)
			{
				std::cout << "El codigo esta mal escrito y no cumple con los criterios" << std::endl;
				ui.pausa();
				return;
			}
			if (pos == -4)
			{
				std::cout << "El producto esta borrado" << std::endl;
				ui.pausa();
				return;
			}
			if (pos < 0)
			{
				std::cout << "El producto no existe" << std::endl;
				ui.pausa();
				return;
			}
			Producto* producto = new Producto(manager.getProducto(pos));
			if (producto == nullptr)
			{
				std::cout << "no hay memoria disponible" << std::endl;
				ui.pausa();
				return;
			}
			ui.mostrarProductos(producto, 1);
			delete producto;
			ui.pausa();
			return;
		};

	int op;
	do
	{
		op = ui.mostrarMenuProductos();
		switch (op)
		{
		case 1:
			agregarProducto();
			break;
		case 2:
			borrarProducto();
			break;
		case 3:
			modificarProducto();
			break;
		case 4:
			stockProducto();
			break;
		case 5:
			listaProductos();
			break;
		case 6:
			buscarProducto();
			break;
		case 0:
			break;
		default:
			ui.opcionIncorrecta();
			break;
		}

	} while (op);
}




void Menu::menuClientes(Manager& manager, UiConsole& ui)
{
	int op;
	do
	{
		op = ui.mostrarMenuClientes();
		switch (op)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 0:
			break;
		default:
			ui.opcionIncorrecta();
			break;
		}

	} while (op);
}



void Menu::menuVentas(Manager& manager, UiConsole& ui)
{
	int op;
	do
	{
		op = ui.mostrarMenuVentas();
		switch (op)
		{
		case 1:
			break;
		case 2:
			break;
		case 0:
			break;
		default:
			ui.opcionIncorrecta();
			break;
		}

	} while (op);
}

void Menu::menuUsuarios(Manager& manager, UiConsole& ui)
{
	ui.limpiarConsola();
	//Cargamos en memoria un cache con los usuarios
	manager.actualizarCacheUsuarios();

	auto agregarUsuario = [&]() -> void
		{
			ui.limpiarConsola();
			if (!manager.esAdmin())
			{
				std::cout << UiConsole::ROJO << "No tiene privilegios para realizar esta acci�n." << UiConsole::RESET
					<< std::endl;
				ui.pausa();
				return;
			}
			bool agregandoUsuario = true;
			std::string nombreUsuario;
			do
			{
				std::cout << "Ingrese el nombre del usuario o 'Q' para salir de este menu: ";
				std::getline(std::cin, nombreUsuario);

				//Validar formato de usuario: 

				if (nombreUsuario.length() == 1 && (nombreUsuario == "q" || nombreUsuario == "Q")) {
					return;
				}

				bool formatoUsuarioValido = Usuario::validarUsuario(nombreUsuario);

				if (!formatoUsuarioValido) {
					std::cout << UiConsole::ROJO << "El nombre de usuario debe tener al menos 4 caracteres. Ingreselo nuevamente." << UiConsole::RESET
						<< std::endl;
					continue;
				}

				if (manager.buscarUsuario(nombreUsuario, true) >= 0)
				{
					std::cout << UiConsole::ROJO << "El nombre de usuario " << UiConsole::VERDE << "'" << nombreUsuario << "'"
						<< UiConsole::ROJO << " ya existe. Ingrese otro." << UiConsole::RESET << std::endl
						<< std::endl;
					continue;
				}

				else
				{
					Usuario usuario = ui.agregarUsuario(nombreUsuario, manager);
					std::cout << "¿Está seguro que desea agregar este usuario? (Y/N)" << std::endl;

					std::string opcion;
					std::getline(std::cin, opcion);

					while (opcion != "n" && opcion != "N" && opcion != "y" && opcion != "Y") {
						std::cout << UiConsole::ROJO << "Opción incorrecta." << UiConsole::RESET << " ¿Está seguro que desea agregar este usuario ? (Y/N) " << std::endl;
						std::getline(std::cin, opcion);
					}

					if (opcion == "n" || opcion == "N") return;


					bool agregadoCorrectamente = manager.agregarUsuario(usuario);
					if (agregadoCorrectamente)
					{
						manager.actualizarCacheUsuarios();
						std::cout << "El usuario se agrego correctamente" << std::endl;
					}
					else
					{
						std::cout << "El usuario no se pudo agregar" << std::endl;
					}
					agregandoUsuario = false;
				}
			} while (agregandoUsuario);

			ui.pausa();
			return;
		};
	auto modificarUsuario = [&]() -> void
		{
			ui.limpiarConsola();

			Usuario usuarioLoggeado = manager.getUsuarioLoggeado();

			if (usuarioLoggeado.getNombreUsuario() != "root") {
				std::cout << UiConsole::ROJO << "Solo el usuario root puede modificar otros perfiles." << UiConsole::RESET << std::endl;
				ui.pausa();
				return;
			}

			std::string nombreUsuario;
			bool usuarioExiste = false;
			bool volverAlMenuAnterior = false;
			int posicionUsuario = -1;

			while (!usuarioExiste) {
				std::cout << "Ingrese el nombre del usuario a modificar o 'Q' para salir de este menu: ";
				std::getline(std::cin, nombreUsuario);
				volverAlMenuAnterior = UiConsole::volverAlMenuAnterior(nombreUsuario);
				if (volverAlMenuAnterior) return;

				posicionUsuario = manager.buscarUsuario(nombreUsuario, true);

				if (posicionUsuario < 0)
				{
					std::cout << UiConsole::ROJO << "El usuario" << UiConsole::VERDE << "'" << nombreUsuario << "'"
						<< UiConsole::ROJO << " no existe. Ingrese nuevamente un usuario." << UiConsole::RESET
						<< std::endl;
					continue;
				}
				usuarioExiste = true;
			}

			bool modificandoUsuario = true;
			while (modificandoUsuario) {
				Usuario usuarioAModificar = manager.leerUsuario(posicionUsuario);

				int opcion = ui.mostrarMenuModificacionUsuario(usuarioAModificar);

				switch (opcion)
				{
				case 1: {
					//nombre usuario
					ui.limpiarConsola();
					bool nombreUsuarioModificado = usuarioAModificar.actualizarNombreUsuario(manager);

					if (!nombreUsuarioModificado) {
						std::cout << UiConsole::ROJO << "El nombre de usuario no pudo ser actualizado correctamente. Intentelo nuevamente." << UiConsole::RESET << std::endl;

						ui.pausa();
					}
					else {
						ui.procesarActualizacionUsuario(manager, usuarioAModificar, posicionUsuario, "nombre de usuario");

					}
					break;
				}
				case 2: {
					//nombre 
					ui.limpiarConsola();
					bool nombreModificado = usuarioAModificar.actualizarNombre();


					if (!nombreModificado) {
						std::cout << UiConsole::ROJO << "El nombre no pudo ser actualizado correctamente. Intentelo nuevamente." << UiConsole::RESET << std::endl;
						ui.pausa();
					}
					else {
						ui.procesarActualizacionUsuario(manager, usuarioAModificar, posicionUsuario, "nombre");
					}

					break;
				}
				case 3: {
					//email
					ui.limpiarConsola();
					bool mailActualizadoCorrectamente = usuarioAModificar.actualizarEmail(manager);

					if (!mailActualizadoCorrectamente) {
						std::cout << UiConsole::ROJO << "El mail no pudo ser actualizado correctamente. Intentelo nuevamente." << UiConsole::RESET << std::endl;
						ui.pausa();
					}
					else {
						ui.procesarActualizacionUsuario(manager, usuarioAModificar, posicionUsuario, "email");
					}

					break;
				}

				case 4: {
					//direccion
					ui.limpiarConsola();
					bool direccionModificada = usuarioAModificar.actualizarDireccion();

					if (!direccionModificada) {
						std::cout << UiConsole::ROJO << "La direccion no pudo ser actualizada correctamente. Intentelo nuevamente." << UiConsole::RESET << std::endl;
						ui.pausa();
					}
					else {
						ui.procesarActualizacionUsuario(manager, usuarioAModificar, posicionUsuario, "direccion");

					}
					break;
				}

				case 5: {
					//Telefono: 
					ui.limpiarConsola();
					bool telefonoActualizadoCorrectamente = usuarioAModificar.actualizarTelefono(manager);

					if (!telefonoActualizadoCorrectamente) {
						std::cout << UiConsole::ROJO << "El telefono no pudo ser actualizado correctamente. Intentelo nuevamente." << UiConsole::RESET << std::endl;
						ui.pausa();
					}
					else {
						ui.procesarActualizacionUsuario(manager, usuarioAModificar, posicionUsuario, "telefono");
					}
					break;
				}

				case 6: {
					//Password:
					ui.limpiarConsola();
					bool contraseniaModificada = usuarioAModificar.modificarContrasenia(true);
					if (!contraseniaModificada) {
						std::cout << UiConsole::ROJO << "La contraseña no pudo ser modificada. Intentelo nuevamente." << UiConsole::RESET << std::endl;
						ui.pausa();

					}
					else {
						ui.procesarActualizacionUsuario(manager, usuarioAModificar, posicionUsuario, "contraseña");
					}
					break;
				}
				case 7: {
					//ROL
					ui.limpiarConsola();
					bool rolModificado = usuarioAModificar.actualizarRol();

					if (!rolModificado) {
						std::cout << UiConsole::ROJO << "El Rol no pudo ser modificado. Intentelo nuevamente." << UiConsole::RESET << std::endl;
						ui.pausa();
					}
					else {
						ui.procesarActualizacionUsuario(manager, usuarioAModificar, posicionUsuario, "rol");
					}

					break;
				}
				case 0: {
					modificandoUsuario = false;
					break;
				}
				default:
				{
					std::cout << UiConsole::ROJO << "La opcion ingresada es incorrecta. Intentelo nuevamente." << UiConsole::RESET << std::endl;
					ui.pausa();
					break;
				}
				}


			}
		};
	auto eliminarUsuario = [&]() -> void
		{
			ui.limpiarConsola();

			if (!manager.esAdmin())
			{
				std::cout << UiConsole::ROJO << "No tiene privilegios para eliminar un usuario." << UiConsole::RESET
					<< std::endl;
				ui.pausa();
				return;
			}

			std::string nombreUsuario;
			bool eliminandoUsuario = true;
			do
			{
				std::cout << "Ingrese el nombre del usuario a eliminar o 'Q' para salir de este menu: ";
				std::getline(std::cin, nombreUsuario);

				if (nombreUsuario.length() == 1 && (nombreUsuario == "q" || nombreUsuario == "Q")) {
					return;
				}

				if (nombreUsuario == "root") {
					std::cout << UiConsole::ROJO << "El usuario " << UiConsole::VERDE << "'root'" << UiConsole::ROJO << " no puede ser eliminado." << UiConsole::RESET << std::endl;
					ui.pausa();
					return;
				}

				int posicionUsuario = manager.buscarUsuario(nombreUsuario, true);

				if (posicionUsuario < 0)
				{
					std::cout << UiConsole::ROJO << "El usuario" << UiConsole::VERDE << "'" << nombreUsuario << "'"
						<< UiConsole::ROJO << " no existe. Ingrese nuevamente un usuario o 'Q' para salir de este menu." << UiConsole::RESET
						<< std::endl;
					continue;
				}
				else
				{
					Usuario usuario = manager.leerUsuario(posicionUsuario);
					bool usuarioActivo = usuario.getEstadoUsuario();

					if (!usuarioActivo) {
						std::cout << "El usuario" << UiConsole::VERDE << "'" << nombreUsuario << "'" << UiConsole::RESET << "ya fue borrado previamente." << std::endl;
						ui.pausa();
						return;
					}



					std::cout << UiConsole::ROJO << "¿Está seguro que desea eliminar el usuario " << UiConsole::BOLD
						<< UiConsole::VERDE << "'" << nombreUsuario << "'" << UiConsole::ROJO << "?" << UiConsole::RESET
						<< "(Y/N)" << std::endl;

					bool opcionCorrecta = false;
					std::string opcion;
					std::getline(std::cin, opcion);

					while (!opcionCorrecta)
					{
						switch (opcion[0])
						{
						case 'y':
						case 'Y':
						{
							usuario.setEstadoUsuario(false);
							opcionCorrecta = true;
							bool guardadoCorrectamente = manager.reescribirUsuario(usuario, posicionUsuario);

							if (guardadoCorrectamente) {
								std::cout << "El usuario fue eliminado correctamente." << std::endl;
								manager.actualizarCacheUsuarios();
								ui.pausa();
							}
							else {
								std::cout << UiConsole::ROJO << "El usuario no pudo ser eliminado. Vuelva a intentarlo." << UiConsole::RESET << std::endl;
								ui.pausa();
							}
							break;
						}
						case 'n':
						case 'N':
						{
							opcionCorrecta = true;
							break;
						}
						{
						default:
						{
							std::cout
								<< UiConsole::ROJO
								<< "La opcion seleccionada es incorrecta. Ingrese 'Y' para eliminar o 'N' para cancelar."
								<< UiConsole::RESET << std::endl;
							std::cin >> opcion;
						}
						break;
						}
						}
					}
				}
				eliminandoUsuario = false;
			} while (eliminandoUsuario);

			return;
		};
	auto modificarContraseniaRoot = [&]() -> void
		{
			ui.limpiarConsola();
			Usuario usuarioRoot = manager.getUsuarioLoggeado();

			if (!(usuarioRoot.getNombreUsuario() == "root")) {
				std::cout << UiConsole::ROJO << "Solamente el usuario " << UiConsole::VERDE << "'root'" << UiConsole::ROJO << " puede modificar la contraseña root." << UiConsole::RESET << std::endl;
				ui.pausa();
				return;
			}

			bool contraseniaModificada = usuarioRoot.modificarContrasenia(true);

			if (contraseniaModificada) {
				bool usuarioActualizadoCorrectamente = manager.reescribirUsuario(usuarioRoot, 0);

				if (usuarioActualizadoCorrectamente) {
					std::cout << "La contraseña fue actualizada correctamente." << std::endl;
					ui.pausa();
				}
			}
			else {
				std::cout << UiConsole::ROJO << "La contraseña no pudo ser actualizada. Vuelva a intentarlo." << std::endl;
				ui.pausa();
			}

		};
	auto listarUsuarios = [&]() -> void
		{
			ui.limpiarConsola();

			Usuario* vectorUsuarios = manager.getCacheListadoUsuarios();
			if (!manager.esAdmin())
			{
				std::cout << UiConsole::ROJO << "No tiene privilegios para ver el listado de usuarios." << UiConsole::RESET
					<< std::endl;
				ui.pausa();
				return;
			}

			if (vectorUsuarios == nullptr)
			{
				std::cout << "Error al cargar el listado de usuarios." << std::endl;
				ui.pausa();
				return;
			}

			int cantidad = manager.cantidadUsuarios();

			std::cout << R"(
+---------------------+---------------------+------------------------------------+---------------------+
|      Usuario        |        Rol          |               Email                |      Telefono       |
+---------------------+---------------------+------------------------------------+---------------------+)"
<< std::endl;

			for (int i = 1; i < cantidad; i++)
			{
				if (vectorUsuarios[i].getEstadoUsuario())
				{
					ui.listarUsuario(vectorUsuarios[i].getNombreUsuario(), vectorUsuarios[i].getRol(),
						vectorUsuarios[i].getEmail(), vectorUsuarios[i].getTelefono());
				}
			}

			std::cout << std::endl;

			ui.pausa();
			
			return;
		};
	auto recuperarUsuario = [&]() {
		ui.limpiarConsola();

		if (!manager.esAdmin())
		{
			std::cout << UiConsole::ROJO << "No tiene privilegios para eliminar un usuario." << UiConsole::RESET
				<< std::endl;
			ui.pausa();
			return;
		}

		std::string nombreUsuario;
		bool eliminandoUsuario = true;
		do
		{
			std::cout << "Ingrese el nombre del usuario a recuperar o 'Q' para salir de este menu: ";
			std::getline(std::cin, nombreUsuario);

			if (nombreUsuario.length() == 1 && (nombreUsuario == "q" || nombreUsuario == "Q")) {
				return;
			}

			if (nombreUsuario == "root") {
				std::cout << UiConsole::ROJO << "El usuario " << UiConsole::VERDE << "'root'" << UiConsole::ROJO << " no puede ser recuperado ya que está activo." << UiConsole::RESET << std::endl;
				ui.pausa();
				return;
			}

			int posicionUsuario = manager.buscarUsuario(nombreUsuario, true);

			if (posicionUsuario < 0)
			{
				std::cout << UiConsole::ROJO << "El usuario" << UiConsole::VERDE << "'" << nombreUsuario << "'"
					<< UiConsole::ROJO << " no existe. Ingrese nuevamente un usuario o 'Q' para salir de este menu." << UiConsole::RESET
					<< std::endl;
				continue;
			}
			else
			{
				Usuario usuario = manager.leerUsuario(posicionUsuario);
				bool usuarioActivo = usuario.getEstadoUsuario();

				if (usuarioActivo) {
					std::cout << "El usuario" << UiConsole::VERDE << "'" << nombreUsuario << "'" << UiConsole::RESET << "se encuentra activo." << std::endl;
					ui.pausa();
					return;
				}


				bool opcionCorrecta = false;
				std::string opcion;

				while (!opcionCorrecta)
				{
					std::cout << UiConsole::ROJO << "¿Está seguro que desea recuperar el usuario " << UiConsole::BOLD
						<< UiConsole::VERDE << "'" << nombreUsuario << "'" << UiConsole::ROJO << "?" << UiConsole::RESET
						<< "(Y/N)" << std::endl;


					std::getline(std::cin, opcion);

					switch (opcion[0])
					{
					case 'y':
					case 'Y':
					{
						usuario.setEstadoUsuario(true);
						opcionCorrecta = true;

						bool guardadoCorrectamente = manager.reescribirUsuario(usuario, posicionUsuario);

						if (guardadoCorrectamente) {
							std::cout << "El usuario fue recuperado correctamente." << std::endl;
							manager.actualizarCacheUsuarios();
							ui.pausa();
						}
						else {
							std::cout << UiConsole::ROJO << "El usuario no pudo ser recuperado. Vuelva a intentarlo." << UiConsole::RESET << std::endl;
							ui.pausa();
						}

						break;
					}
					case 'n':
					case 'N':
					{
						opcionCorrecta = true;
						break;
					}
					default:
					{
						std::cout
							<< UiConsole::ROJO
							<< "La opción seleccionada es incorrecta."
							<< UiConsole::RESET << std::endl;
						break;
					}

					}
				}
			}
			eliminandoUsuario = false;
		} while (eliminandoUsuario);

		return;

		};
	auto editarMiPerfil = [&]() -> void {
		Usuario usuarioLoggeado = manager.getUsuarioLoggeado();
		int posicionUsuario = manager.buscarUsuario(usuarioLoggeado.getNombreUsuario(), true);


		bool editandoPerfil = true;

		while (editandoPerfil) {
			int opcionAModificar = ui.menuEditarMiPerfil(usuarioLoggeado);

			switch (opcionAModificar) {

			case 1: {
				//nombre
				ui.limpiarConsola();
				bool nombreActualizadoCorrectamente = usuarioLoggeado.actualizarNombre();

				if (!nombreActualizadoCorrectamente) {
					std::cout << UiConsole::ROJO << "El nombre no pudo ser actualizado correctamente. Intentelo nuevamente." << UiConsole::RESET << std::endl;
					ui.pausa();
				}
				else {
					ui.procesarActualizacionUsuario(manager, usuarioLoggeado, posicionUsuario, "nombre");
					manager.setUsarioLoggeado(usuarioLoggeado);
				}
				break;
			}
			case 2: {
				//email
				ui.limpiarConsola();
				bool mailActualizadoCorrectamente = usuarioLoggeado.actualizarEmail(manager);

				if (!mailActualizadoCorrectamente) {
					std::cout << UiConsole::ROJO << "El mail no pudo ser actualizado correctamente. Intentelo nuevamente." << UiConsole::RESET << std::endl;
					ui.pausa();
				}
				else {
					ui.procesarActualizacionUsuario(manager, usuarioLoggeado, posicionUsuario, "email");
					manager.setUsarioLoggeado(usuarioLoggeado);
				}
				break;
			}
			case 3: {
				//direccion
				ui.limpiarConsola();

				bool direccionActualizadaCorrectamente = usuarioLoggeado.actualizarDireccion();

				if (!direccionActualizadaCorrectamente) {
					std::cout << UiConsole::ROJO << "La direccion no pudo ser actualizada correctamente. Intentelo nuevamente." << UiConsole::RESET << std::endl;
					ui.pausa();
				}
				else {
					ui.procesarActualizacionUsuario(manager, usuarioLoggeado, posicionUsuario, "direccion");
					manager.setUsarioLoggeado(usuarioLoggeado);
				}
				break;
			}
			case 4: {
				//telefono
				ui.limpiarConsola();

				bool telefonoActualizadoCorrectamente = usuarioLoggeado.actualizarTelefono(manager);

				if (!telefonoActualizadoCorrectamente) {
					std::cout << UiConsole::ROJO << "El telefono no pudo ser actualizado correctamente. Intentelo nuevamente." << UiConsole::RESET << std::endl;
					ui.pausa();
				}
				else {
					ui.procesarActualizacionUsuario(manager, usuarioLoggeado, posicionUsuario, "telefono");
					manager.setUsarioLoggeado(usuarioLoggeado);
				}
				break;
			}
			case 5: {
				ui.limpiarConsola();
				bool contraseniaModificada = usuarioLoggeado.modificarContrasenia(false);
				if (!contraseniaModificada) {
					std::cout << UiConsole::ROJO << "La contraseña no pudo ser modificada. Intentelo nuevamente." << UiConsole::RESET << std::endl;
					ui.pausa();
					break;
				}
				else {
					ui.procesarActualizacionUsuario(manager, usuarioLoggeado, posicionUsuario, "contraseña");
					manager.setUsarioLoggeado(usuarioLoggeado);
				}
				break;
			}
			case 0: {
				editandoPerfil = false;
				break;
			}
			default: {
				std::cout << UiConsole::ROJO << "La opcion ingresada es incorrecta. Intentelo nuevamente." << UiConsole::RESET << std::endl;
				ui.pausa();
				break;
			}
			}

		}
		};
	auto mostrarInformacionUsuario = [&]()->void {
		ui.limpiarConsola();
		if (!manager.esAdmin())
		{
			std::cout << UiConsole::ROJO << "No tiene privilegios para realizar esta acción." << UiConsole::RESET
				<< std::endl;
			ui.pausa();
			return;
		}


		Usuario usuarioLoggeado = manager.getUsuarioLoggeado();
		bool usuarioLoggeadoEsRoot = usuarioLoggeado.getNombreUsuario() == "root";

		std::string nombreUsuario;
		bool usuarioExiste = false;
		bool volverAlMenuAnterior = false;
		int posicionUsuario = -1;

		while (!usuarioExiste) {
			std::cout << "Ingrese el nombre del usuario a buscar o 'Q' para salir de este menu: ";
			std::getline(std::cin, nombreUsuario);
			volverAlMenuAnterior = UiConsole::volverAlMenuAnterior(nombreUsuario);
			if (volverAlMenuAnterior) return;

			posicionUsuario = manager.buscarUsuario(nombreUsuario, true);

			if (posicionUsuario < 0)
			{
				std::cout << UiConsole::ROJO << "El usuario" << UiConsole::VERDE << "'" << nombreUsuario << "'"
					<< UiConsole::ROJO << " no existe. Ingrese nuevamente un usuario." << UiConsole::RESET
					<< std::endl;
				continue;
			}
			usuarioExiste = true;
		}


		Usuario usuarioAMostrar = manager.leerUsuario(posicionUsuario);
		ui.mostrarPerfil(usuarioAMostrar, usuarioLoggeadoEsRoot);
		ui.pausa();
		};

	int opcion;
	do
	{
		opcion = ui.mostrarMenuUsuarios();
		switch (opcion)
		{
		case 1:
			agregarUsuario();
			break;
		case 2:
			modificarUsuario();
			break;
		case 3:
			editarMiPerfil();
			break;
		case 4:
			eliminarUsuario();
			break;
		case 5:
			modificarContraseniaRoot();
			break;
		case 6:
			listarUsuarios();
			break;
		case 7:
			recuperarUsuario();
			break;
		case 8:
			mostrarInformacionUsuario();
			break;
		case 0:
			break;
		default:
			ui.opcionIncorrecta();
			break;
		}


	} while (opcion);
}

void Menu::menuEstadisticas(Manager& manager, UiConsole& ui)
{
	int op;
	do
	{
		op = ui.mostrarMenuEstadisticas();
		switch (op)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 0:
			break;
		default:
			ui.opcionIncorrecta();
			break;
		}

	} while (op);
}

void Menu::menuSeguridad(Manager& manager, UiConsole& ui)
{
	int op;
	do
	{
		op = ui.mostrarMenuSeguridad();
		switch (op)
		{
		case 1:
			break;
		case 2:
			break;
		case 0:
			break;
		default:
			ui.opcionIncorrecta();
			break;
		}

	} while (op);
}
