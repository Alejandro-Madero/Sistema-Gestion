#include "../include/ui-console.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include<algorithm>
#include <cctype>

#include "../include/manager.h"

#ifdef _WIN32
#include <windows.h>
#endif

void UiConsole::configurarConsola()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#else

#endif
}

const char* UiConsole::RESET = "\033[0m";
const char* UiConsole::ROJO = "\033[31m";
const char* UiConsole::VERDE = "\033[32m";
const char* UiConsole::AZUL = "\033[34m";
const char* UiConsole::AMARILLO = "\033[33m";
const char* UiConsole::BOLD = "\033[1m";
const char* UiConsole::SUBRAYADO = "\033[4m";

void UiConsole::limpiarConsola()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void UiConsole::pausa()
{

#ifdef _WIN32
	system("pause");
#else
	std::cout << "Presione Enter para continuar" << std::endl;
	std::string op;
	std::getline(std::cin, op);
#endif
}

void UiConsole::opcionIncorrecta()
{
	std::cout << UiConsole::ROJO << "La opción ingresada es incorrecta. Ingresela nuevamente." << UiConsole::RESET << std::endl;
	this->pausa();
}

const char* LOG_IN = R"(
╔══════════════════════════════════════════╗
║                                          ║ 
║                 LOG IN                   ║ 
║                                          ║ 
╚══════════════════════════════════════════╝
)";

const char* MENU_PRINCIPAL = R"(
╔══════════════════════════════════════════╗
║                                          ║ 
║            SISTEMA DE GESTIÓN            ║ 
║                                          ║ 
╚══════════════════════════════════════════╝
)";
const char* MENU_PRODUCTOS = R"(
╔══════════════════════════════════════════╗
║                                          ║
║       SISTEMA DE GESTIÓN - PRODUCTOS     ║
║                                          ║
╚══════════════════════════════════════════╝
)";
const char* MENU_PROVEEDORES = R"(
╔══════════════════════════════════════════╗
║                                          ║
║     SISTEMA DE GESTIÓN - PROVEEDORES     ║
║                                          ║
╚══════════════════════════════════════════╝
)";

const char* MENU_CLIENTES = R"(
╔══════════════════════════════════════════╗
║                                          ║
║       SISTEMA DE GESTIÓN - CLIENTES      ║
║                                          ║
╚══════════════════════════════════════════╝
)";

const char* MENU_PRODUCCION = R"(
╔══════════════════════════════════════════╗
║                                          ║
║      SISTEMA DE GESTIÓN - PRODUCCIÓN     ║
║                                          ║
╚══════════════════════════════════════════╝
)";
const char* MENU_VENTAS_FACTURACION = R"(
╔══════════════════════════════════════════╗
║                                          ║
║ SISTEMA DE GESTIÓN - VENTAS Y FACTURACIÓN║
║                                          ║
╚══════════════════════════════════════════╝
)";
const char* MENU_GESTION_USUARIOS = R"(
╔══════════════════════════════════════════╗
║                                          ║
║  SISTEMA DE GESTIÓN - USUARIOS Y ROLES   ║
║                                          ║
╚══════════════════════════════════════════╝
)";

const char* MENU_AGREGAR_USUARIO = R"(
╔══════════════════════════════════════════╗
║                                          ║
║            AGREGAR USUARIO               ║
║                                          ║
╚══════════════════════════════════════════╝
)";

const char* MENU_EDITAR_USUARIO = R"(
╔══════════════════════════════════════════╗
║                                          ║
║             EDITAR USUARIO               ║
║                                          ║
╚══════════════════════════════════════════╝
)";

const char* MENU_EDITAR_PRODUCTO = R"(
╔══════════════════════════════════════════╗
║                                          ║
║             EDITAR PRODUCTO              ║
║                                          ║
╚══════════════════════════════════════════╝
)";


const char* MENU_ESTATISTICAS = R"(
╔══════════════════════════════════════════╗
║                                          ║
║    SISTEMA DE GESTIÓN - ESTADISTICAS     ║
║                                          ║
╚══════════════════════════════════════════╝
)";

const char* MENU_SEGURIDAD = R"(
╔══════════════════════════════════════════╗
║                                          ║
║   SISTEMA DE GESTIÓN - SEGURIDAD         ║
║                                          ║
╚══════════════════════════════════════════╝
)";

const char* MODIFICAR_USUARIO = R"(
╔══════════════════════════════════════════╗
║                                          ║
║           MODIFICAR USUARIO              ║
║                                          ║
╚══════════════════════════════════════════╝
)";

UiConsole::UiConsole()
{
}
void UiConsole::setUsuario(std::string usuario)
{
	this->_nombreUsuario = usuario;
}

void UiConsole::mostrarMenuLogin(std::string& user, std::string& pass, int intentos)
{

	if (intentos == 5)
	{
		std::cout << LOG_IN << std::endl;
	}

	if (intentos < 5)
	{
		std::cout << BOLD << ROJO << "Usuario o contraseña incorrectos" << RESET << std::endl;
		std::cout << "Intentos restantes: " << BOLD << ROJO << intentos << RESET << std::endl
			<< std::endl;
	}

	std::cout << "Ingrese su usuario: ";
	std::getline(std::cin, user);
	std::cout << "Ingrese su contrasena: ";
	std::getline(std::cin, pass);
	std::cout << std::endl;
}

int UiConsole::mostrarMenuPrincipal()
{
	limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MENU_PRINCIPAL << std::endl;	
	std::cout << RESET << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Gestión de Productos" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Gestion de Clientes" << std::endl;
	std::cout << RESET << ROJO << "3. " << RESET << SUBRAYADO << BOLD << "Gestion de Ventas" << std::endl;
	std::cout << RESET << ROJO << "4. " << RESET << SUBRAYADO << BOLD << "Gestion de Usuarios" << std::endl;
	std::cout << RESET << ROJO << "5. " << RESET << SUBRAYADO << BOLD << "Estadisticas" << std::endl;
	std::cout << RESET << ROJO << "6. " << RESET << SUBRAYADO << BOLD << "Seguridad" << std::endl;
	std::cout << RESET << "0. " << SUBRAYADO << BOLD << "Salir" << RESET << std::endl
		<< std::endl;
	std::cout << "Opción elegida: ";

	std::string opcion;
	std::getline(std::cin, opcion);

	try {
		int numero = std::stoi(opcion);
		if (numero >= 0 && numero < 7) {
			return numero;
		}
		else {
			return -1;
		}
	}
	catch (const std::invalid_argument& e) {
		return -1;
	}


}



int UiConsole::mostrarMenuProductos()
{
	limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MENU_PRODUCTOS << std::endl;

	std::cout << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Dar de alta producto" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Dar de baja producto" << std::endl;
	std::cout << RESET << ROJO << "3. " << RESET << SUBRAYADO << BOLD << "Editar producto" << std::endl;
	std::cout << RESET << ROJO << "4. " << RESET << SUBRAYADO << BOLD << "Listar productos" << std::endl;
	std::cout << RESET << ROJO << "5. " << RESET << SUBRAYADO << BOLD << "Buscar producto" << std::endl;
	std::cout << RESET << "0. " << SUBRAYADO << BOLD << "Volver al menú principal" << RESET << std::endl
		<< std::endl;
	std::cout << "Opción elegida: ";

	std::string opcion;
	std::getline(std::cin, opcion);

	try {
		int numero = std::stoi(opcion);
		if (numero >= 0 && numero < 7) {
			return numero;
		}
		else {
			return -1;
		}
	}
	catch (const std::invalid_argument& e) {
		return -1;
	}

}

int UiConsole::mostrarMenuProveedores()
{
	limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MENU_PROVEEDORES << std::endl;
	std::cout << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Agregar proveedor" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Modificar proveedor" << std::endl;
	std::cout << RESET << ROJO << "3. " << RESET << SUBRAYADO << BOLD << "Eliminar proveedor" << std::endl;
	std::cout << RESET << ROJO << "4. " << RESET << SUBRAYADO << BOLD << "Consultar proveedor" << std::endl;
	std::cout << RESET << ROJO << "5. " << RESET << SUBRAYADO << BOLD << "Registrar orden de compra" << std::endl;
	std::cout << RESET << ROJO << "6. " << RESET << SUBRAYADO << BOLD << "Historial de órdenes de compra" << std::endl;
	std::cout << RESET << ROJO << "7. " << RESET << SUBRAYADO << BOLD << "Evaluación de proveedores" << std::endl;
	std::cout << RESET << "0. " << SUBRAYADO << BOLD << "Volver al menú principal" << RESET << std::endl
		<< std::endl;
	std::cout << "Opción elegida: ";

	std::string op;
	std::getline(std::cin, op);
	if (op == "0")
	{
		return 0;
	}
	else if (op == "1")
	{
		return 1;
	}
	else if (op == "2")
	{
		return 2;
	}
	else if (op == "3")
	{
		return 3;
	}
	else if (op == "4")
	{
		return 4;
	}
	else if (op == "5")
	{
		return 5;
	}
	else if (op == "6")
	{
		return 6;
	}
	else if (op == "7")
	{
		return 7;
	}
	else
	{
		return -1;
	}
}

int UiConsole::mostrarMenuClientes()
{
	limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MENU_CLIENTES << std::endl;

	std::cout << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Agregar cliente" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Modificar cliente" << std::endl;
	std::cout << RESET << ROJO << "3. " << RESET << SUBRAYADO << BOLD << "Eliminar cliente" << std::endl;
	std::cout << RESET << ROJO << "4. " << RESET << SUBRAYADO << BOLD << "Consultar cliente" << std::endl;
	std::cout << RESET << "0. " << SUBRAYADO << BOLD << "Volver al menú principal" << RESET << std::endl
		<< std::endl;
	std::cout << "Opción elegida: ";

	std::string opcion;
	std::getline(std::cin, opcion);

	try {
		int numero = std::stoi(opcion);
		if (numero >= 0 && numero < 5) {
			return numero;
		}
		else {
			return -1;
		}
	}
	catch (const std::invalid_argument e) {
		return -1;
	}
}

int UiConsole::mostrarMenuProduccion()
{
	limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MENU_PRODUCCION << std::endl;

	std::cout << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Generar orden de producción" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Actualizar estado de orden de producción"
		<< std::endl;
	std::cout << RESET << ROJO << "3. " << RESET << SUBRAYADO << BOLD << "Asignar Productos a producción" << std::endl;
	std::cout << RESET << ROJO << "4. " << RESET << SUBRAYADO << BOLD << "Historial de producción" << std::endl;
	std::cout << RESET << "0. " << SUBRAYADO << BOLD << "Volver al menú principal" << RESET << std::endl
		<< std::endl;
	std::cout << "Opción elegida: ";

	std::string op;
	std::getline(std::cin, op);
	if (op == "0")
	{
		return 0;
	}
	else if (op == "1")
	{
		return 1;
	}
	else if (op == "2")
	{
		return 2;
	}
	else if (op == "3")
	{
		return 3;
	}
	else if (op == "4")
	{
		return 4;
	}
	else
	{
		return -1;
	}
}

int UiConsole::mostrarMenuVentas()
{
	limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MENU_VENTAS_FACTURACION << std::endl;
	std::cout << RESET << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Generar reporte de ventas" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Historial de ventas" << std::endl;
	std::cout << RESET << "0. " << SUBRAYADO << BOLD << "Volver al menú principal" << RESET << std::endl
		<< std::endl;
	std::cout << "Opción elegida: ";

	std::string opcion;
	std::getline(std::cin, opcion);

	try {
		int numero = std::stoi(opcion);
		if (numero >= 0 && numero < 3) {
			return numero;
		}
		else {
			return -1;
		}
	}
	catch (const std::invalid_argument& e) {
		return -1;
	}
}

int UiConsole::mostrarMenuUsuarios()
{
	this->limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MENU_GESTION_USUARIOS << std::endl;

	std::cout << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Agregar usuario" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Modificar usuario" << std::endl;
	std::cout << RESET << ROJO << "3. " << RESET << SUBRAYADO << BOLD << "Editar mi perfil" << std::endl;
	std::cout << RESET << ROJO << "4. " << RESET << SUBRAYADO << BOLD << "Eliminar usuario" << std::endl;
	std::cout << RESET << ROJO << "5. " << RESET << SUBRAYADO << BOLD << "Modificar contraseña root" << std::endl;
	std::cout << RESET << ROJO << "6. " << RESET << SUBRAYADO << BOLD << "Lista de usuarios" << std::endl;
	std::cout << RESET << ROJO << "7. " << RESET << SUBRAYADO << BOLD << "Recuperar usuario borrado" << std::endl;
	std::cout << RESET << ROJO << "8. " << RESET << SUBRAYADO << BOLD << "buscar usuario" << std::endl;
	std::cout << RESET << "0. " << SUBRAYADO << BOLD << "Volver al menú principal" << RESET << std::endl
		<< std::endl;
	std::cout << "Opción elegida: ";

	std::string opcion;
	std::getline(std::cin, opcion);

	try {
		int numero = std::stoi(opcion);
		if (numero >= 0 && numero < 9) {
			return numero;
		}
		else {
			return -1;
		}

	}
	catch (const std::invalid_argument& e) {
		return -1;
	}


}

int UiConsole::mostrarMenuEstadisticas()
{
	limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MENU_ESTATISTICAS << std::endl;

	std::cout << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Generar reporte de inventario productos" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Generar reporte de clientes" << std::endl;
	std::cout << RESET << ROJO << "3. " << RESET << SUBRAYADO << BOLD << "Generar reporte de ventas" << std::endl;
	std::cout << RESET << "0. " << SUBRAYADO << BOLD << "Volver al menú principal" << RESET << std::endl
		<< std::endl;
	std::cout << "Opción elegida: ";

	std::string opcion;
	std::getline(std::cin, opcion);

	try {
		int numero = std::stoi(opcion);
		if (numero >= 0 && numero < 4) {
			return numero;
		}
		else {
			return -1;
		}
	}
	catch (const std::invalid_argument& e) {
		return -1;
	}
}

int UiConsole::mostrarMenuSeguridad()
{
	limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MENU_SEGURIDAD << std::endl;

	std::cout << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Backup de datos" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Restauración de datos" << std::endl;
	std::cout << RESET << "0. " << SUBRAYADO << BOLD << "Volver al menú principal" << RESET << std::endl
		<< std::endl;
	std::cout << "Opción elegida: ";

	std::string op;
	std::getline(std::cin, op);
	if (op == "0")
	{
		return 0;
	}
	else if (op == "1")
	{
		return 1;
	}
	else if (op == "2")
	{
		return 2;
	}
	else
	{
		return -1;
	}
}

Usuario UiConsole::agregarUsuario(std::string nombreUsuario, Manager& manager)
{
	std::string nombre;
	std::string pass;
	std::string rol;
	std::string telefono;
	std::string direccion;
	std::string email;

	//NOMBRE:
	std::cout << "Nombre completo: ";
	std::getline(std::cin, nombre);
	//Validación del nombre completo: 
	bool nombreEsCorrecto = Usuario::validarNombreCompleto(nombre);

	while (!nombreEsCorrecto) {
		std::cout << ROJO << "El valor ingresado no es un nombre correcto. Formato correcto: 'Nombre Apellido'. Ingreselo nuevamente." << RESET << std::endl;
		std::cout << "Nombre completo:";
		std::getline(std::cin, nombre);
		nombreEsCorrecto = Usuario::validarNombreCompleto(nombre);
	}

	//CONTRASEÑA: 
	std::cout << "Contraseña: ";
	std::getline(std::cin, pass);
	//Validación de la contraseña: 
	bool contraseniaCorrecta = Usuario::validarContrasenia(pass);

	while (!contraseniaCorrecta) {
		std::cout << ROJO << "La contraseña debe tener como mínimo 4 caracteres y máximo 20. Ingresela nuevamente." << RESET << std::endl;
		std::cout << "Contraseña: ";
		std::getline(std::cin, pass);
		contraseniaCorrecta = Usuario::validarContrasenia(pass);
	}

	//ROL: 
	std::cout << BOLD << R"(
 Roles
 a: administrador
 u: usuario
 v: vendedor
 c: comprador: )"
		<< RESET << std::endl
		<< std::endl;

	std::cout << "Ingrese el rol: ";
	std::getline(std::cin, rol);
	bool rolValido = Usuario::validarRol(rol);
	// Validación del rol:
	while (!rolValido)
	{
		std::cout << ROJO << "El rol ingresado no es correcto, ingreselo nuevamente." << RESET << std::endl;
		std::cout << "Ingrese el rol: ";
		std::getline(std::cin, rol);
		rolValido = Usuario::validarRol(rol);
	}

	//TELEFONO: 
	std::cout << "Telefono: ";
	std::getline(std::cin, telefono);

	// Validación formato del numero de telefono: 

	bool telefonoValido = Usuario::validarTelefono(telefono);
	while (!telefonoValido)
	{
		std::cout << ROJO << "El valor ingresado no es un número. Ingreselo nuevamente." << RESET << std::endl;
		std::cout << "Telefono: ";
		std::getline(std::cin, telefono);
		telefonoValido = Usuario::validarTelefono(telefono);
	}

	//Validación de la existencia del numero de telefono en la base de datos : 
	int telefonoYaRegistrado = manager.buscarTelefono(telefono, true);

	while (telefonoYaRegistrado >= 0)
	{
		std::cout << ROJO << "El telefono ingresado " << VERDE << "'" << telefono << "'" << ROJO
			<< " ya está registrado para otro usuario. Ingrese otro telefono." << RESET << std::endl;
		std::cout << "Telefono: ";
		std::getline(std::cin, telefono);
		telefonoYaRegistrado = manager.buscarTelefono(telefono, true);
	}


	//DIRECCION: 
	std::cout << "Direccion: ";
	std::getline(std::cin, direccion);

	bool direccionValida = Usuario::validarDireccion(direccion);

	while (!direccionValida) {
		std::cout << ROJO << "La dirección ingresada es demasiado corta. Ingrese un valor válido" << RESET << std::endl;
		std::cout << "Direccion: ";
		std::getline(std::cin, direccion);
		direccionValida = Usuario::validarDireccion(direccion);
	}

	//EMAIL:
	std::cout << "Email: ";
	std::getline(std::cin, email);

	//Validacion del formato del email: 
	bool formatoCorrectoEmail = Usuario::validarEmail(email);

	while (!formatoCorrectoEmail) {
		std::cout << ROJO << "El valor ingresado no tiene un formato correcto (ejemplo: mimail@mailito.com). Ingrese nuevamente un valor." << RESET << std::endl;
		std::cout << "Email: ";
		std::getline(std::cin, email);
		formatoCorrectoEmail = Usuario::validarEmail(email);
	}
	int mailExiste = manager.buscarEmail(email, true);

	// Validación de la existencia del email en la base de datos:
	while (mailExiste >= 0)
	{
		std::cout << ROJO << "El mail ingresado " << VERDE << "'" << email << "'" << ROJO
			<< " ya está registrado para otro usuario. Ingrese otro email." << RESET << std::endl;
		std::cout << "Email: ";
		std::getline(std::cin, email);
		mailExiste = manager.buscarEmail(email, true);
	}

	return Usuario(rol[0], pass, nombreUsuario, Fecha(), 0, telefono, 'u', nombre, direccion, email);
}

void UiConsole::listarUsuario(std::string nombreUsuario, char rolUsuario, std::string email, std::string telefono)
{

	std::cout << "| " << std::left << std::setw(20) << nombreUsuario;

	if (rolUsuario == 'a' || rolUsuario == 'A')
	{
		std::cout << "| " << std::left << std::setw(20) << "administrador";
	}
	else if (rolUsuario == 'u' || rolUsuario == 'U')
	{
		std::cout << "| " << std::left << std::setw(20) << "usuario";
	}
	else if (rolUsuario == 'v' || rolUsuario == 'V')
	{
		std::cout << "| " << std::left << std::setw(20) << "vendedor";
	}
	else if (rolUsuario == 'c' || rolUsuario == 'C')
	{
		std::cout << "| " << std::left << std::setw(20) << "comprador";
	}

	std::cout << "| " << std::left << std::setw(35) << email;
	std::cout << "| " << std::left << std::setw(20) << telefono << "|" << std::endl;
}


int UiConsole::menuEditarMiPerfil(Usuario& usuarioLoggeado) {
	this->limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MENU_EDITAR_USUARIO << std::endl;

	this->mostrarPerfil(usuarioLoggeado, false);


	std::cout << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Modificar nombre" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Modificar email" << std::endl;
	std::cout << RESET << ROJO << "3. " << RESET << SUBRAYADO << BOLD << "Modificar dirección" << std::endl;
	std::cout << RESET << ROJO << "4. " << RESET << SUBRAYADO << BOLD << "Modificar Telefono" << std::endl;
	std::cout << RESET << ROJO << "5. " << RESET << SUBRAYADO << BOLD << "Modificar contraseña" << std::endl;
	std::cout << RESET << "0. " << SUBRAYADO << BOLD << "Volver al menú anterior" << RESET << std::endl
		<< std::endl;
	std::cout << "Opción elegida: ";


	std::string opcion;
	std::getline(std::cin, opcion);

	try {
		int numero = std::stoi(opcion);
		if (numero >= 0 && numero < 6) {
			return numero;
		}
		else {
			return -1;
		}

	}
	catch (const std::invalid_argument& e) {
		return -1;
	}




}

void UiConsole::mostrarPerfil(Usuario& usuario, bool root) {

	std::string usuarioActivo = usuario.getEstadoUsuario() == true ? "Si" : "No";

	std::cout << std::endl << VERDE << "Nombre de usuario: " << RESET << usuario.getNombreUsuario() << std::endl;
	std::cout << VERDE << "Nombre: " << RESET << usuario.getNombre() << std::endl;
	std::cout << VERDE << "Email: " << RESET << usuario.getEmail() << std::endl;
	std::cout << VERDE << "Direccion: " << RESET << usuario.getDireccion() << std::endl;
	std::cout << VERDE << "Telefono: " << RESET << usuario.getTelefono() << std::endl;
	if (root) {
		std::cout << VERDE << "Contraseña: " << RESET << usuario.getPassword() << std::endl;
	}
	std::cout << VERDE << "Rol: " << RESET << mostrarRol(usuario.getRol()) << std::endl;
	std::cout << VERDE << "Perfil activo: " << RESET << usuarioActivo << std::endl << std::endl << std::endl;

}

std::string UiConsole::mostrarRol(char rol) {
	if (rol == 'a' || rol == 'A') return "Administrador";
	if (rol == 'u' || rol == 'U') return "Usuario";
	if (rol == 'c' || rol == 'C') return "Comprador";
	if (rol == 'v' || rol == 'V') return "Vendedor";
}

int UiConsole::mostrarMenuModificacionUsuario(Usuario& usuario)
{
	limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MODIFICAR_USUARIO << std::endl;

	this->mostrarPerfil(usuario, true);

	std::cout << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Nombre usuario" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Nombre completo" << std::endl;
	std::cout << RESET << ROJO << "3. " << RESET << SUBRAYADO << BOLD << "Email" << std::endl;
	std::cout << RESET << ROJO << "4. " << RESET << SUBRAYADO << BOLD << "Dirección" << std::endl;
	std::cout << RESET << ROJO << "5. " << RESET << SUBRAYADO << BOLD << "Telefono" << std::endl;
	std::cout << RESET << ROJO << "6. " << RESET << SUBRAYADO << BOLD << "Password" << std::endl;
	std::cout << RESET << ROJO << "7. " << RESET << SUBRAYADO << BOLD << "Rol" << std::endl;
	std::cout << RESET << "0. " << SUBRAYADO << BOLD << "Volver al menú principal" << RESET << std::endl
		<< std::endl;
	std::cout << "Opción elegida: ";

	std::string opcion;
	std::getline(std::cin, opcion);

	try {
		int numero = std::stoi(opcion);
		if (numero >= 0 && numero < 8) {
			return numero;
		}
		else {
			return -1;
		}

	}
	catch (const std::invalid_argument& e) {
		return -1;
	}
}

// funcionalidades producto

std::string UiConsole::pedirCodigoProducto()
{
	bool salirDelMenu = false;

	while (!salirDelMenu) {
		std::string codigo;
		std::cout << "Ingrese codigo de producto o 'Q' para salir de este menu: ";
		std::getline(std::cin, codigo);

		salirDelMenu = UiConsole::volverAlMenuAnterior(codigo);
		if (salirDelMenu) return "";
		
		
		bool codigoValido = Producto::validarCodigoProducto(codigo); 

		if(!codigoValido) {
			std::cout << ROJO << "El codigo debe tener entre 1 y 20 caracteres alfanumericos. Ingreselo nuevamente." << RESET << std::endl;
			continue;
		}

		return codigo;
	}

}




Producto UiConsole::agregarProducto(std::string codigo, bool isInsumo)
{
	bool descripcionValida = false;
	std::string  descripcion;
	std::string stock; 

	while (!descripcionValida) {
	std::cout << "Ingrese descripcion del producto: ";
	std::getline(std::cin, descripcion);
	descripcionValida = Producto::validarDescripcionProducto(descripcion);

	if (!descripcionValida) {
		std::cout << UiConsole::ROJO << "La descripcion debe tener entre 3 y 50 caracteres alfanumericos." << UiConsole::RESET << std::endl; 
		continue; 
	}
	}
	
	bool stockValido = false; 
	
	while (!stockValido ) {
		std::cout << "Ingrese el stock del producto: ";
		std::getline(std::cin, stock);
		stockValido = Producto::validarStockYPrecioProducto(stock);
	}
	bool precioValido = false;
	std::string precio; 
	while (!precioValido) {
		std::cout << "Ingrese el precio del producto: ";
		std::getline(std::cin,precio);
		precioValido = Producto::validarStockYPrecioProducto(precio);
	}
	
	Producto producto(codigo, descripcion, std::stoi(stock), std::stoi(precio));
	return producto;
}

void UiConsole::mostrarProductos(Producto* productos, int cantidadProductos)
{
	std::cout << R"(
+--------------+----------------------------------+-------------+-------------------+
|    Codigo    |          Descripcion             |    Stock    |      Precio       | 
+--------------+----------------------------------+-------------+-------------------+)"
<< std::endl;

	for (size_t i = 0; i < cantidadProductos; i++) {
		if (productos[i].getEstaBorrado()) continue;
		std::cout << "| " << std::left << std::setw(13) << productos[i].getCodigo(); 
		std::cout << "| " << std::left << std::setw(33) << productos[i].getDescripcion();
		std::cout << "| " << std::left << std::setw(12) << productos[i].getStock();
		std::cout << "| " << std::left<<"$" << std::setw(17) << productos[i].getPrecio() << "|";
		std::cout <<std::endl;
	}

}

int UiConsole::stockProducto()
{
	std::cout << "desea modificar stock?(Y/N):";
	std::string opcion;
	std::getline(std::cin, opcion);
	if (opcion == "n" && opcion == "N")
	{
		return -1;
	}

	std::cout << "Ingrese el nuevo stock : ";
	int numero = 0;
	if (pedirNumero(numero))
	{
		return numero;
	}
	return -1;
}

bool UiConsole::pedirNumero(int& numResult)
{
	std::string numero;
	std::getline(std::cin, numero);
	const char* str = numero.c_str();
	char* endptr;
	long int value = strtol(str, &endptr, 10);
	if (endptr == str)
	{
		std::cout << "no se encontraron numeros" << std::endl;
	}
	else if (*endptr != '\0')
	{
		std::cout << "formato numerico no valido" << std::endl;
	}
	else
	{
		numResult = value;
		return true;
	}
	return false;
}


bool UiConsole::volverAlMenuAnterior(std::string input) {
	return input == "q" || input == "Q";
}

void UiConsole::procesarActualizacionUsuario(Manager& manager, Usuario& usuario, int posicionUsuario, std::string campo) {

	std::string articulo = campo == "direccion" || campo == "contraseña" ? "La " : "El ";
	std::string modificacion = campo == "direccion" || campo == "contraseña" ? "modificada " : "modificado ";
	//Mensajes
	std::string mensajeExito = articulo + campo + " fue " + modificacion + "exitosamente";
	std::string mensajeFracaso = "Ocurrio un error al guardar los cambios. Intentelo nuevamente.";

	bool usuarioGuardadoExitosamente = manager.reescribirUsuario(usuario, posicionUsuario);
	if (usuarioGuardadoExitosamente) {
		std::cout << VERDE << mensajeExito << RESET << std::endl;
		manager.actualizarCacheUsuarios();
		this->pausa();
	}
	else {
		std::cout << ROJO << mensajeFracaso << RESET << std::endl;
		this->pausa();
	}
}

int UiConsole::mostrarMenuModificacionProducto(Producto& producto)
{
	limpiarConsola();
	std::cout << BOLD << "Usuario: " << VERDE << _nombreUsuario << RESET;
	std::cout << MENU_EDITAR_PRODUCTO << std::endl;

	this->mostrarProducto(producto);

	std::cout << std::endl << ROJO << "1. " << RESET << SUBRAYADO << BOLD << "Codigo" << std::endl;
	std::cout << RESET << ROJO << "2. " << RESET << SUBRAYADO << BOLD << "Descripcion" << std::endl;
	std::cout << RESET << ROJO << "3. " << RESET << SUBRAYADO << BOLD << "Stock" << std::endl;
	std::cout << RESET << ROJO << "4. " << RESET << SUBRAYADO << BOLD << "Precio" << std::endl;
	std::cout << RESET << ROJO << "0. " << RESET << SUBRAYADO << BOLD << "Volver al menú anterior" << RESET <<std::endl << std::endl;
	std::string opcion;
	std::cout << "Opción elegida:"; 
	std::getline(std::cin, opcion);

	try {
		int numero = std::stoi(opcion);
		if (numero >= 0 && numero < 5) {
			return numero;
		}
		else {
			return -1;
		}

	}
	catch (const std::invalid_argument& e) {
		return -1;
	}
}


void UiConsole::mostrarProducto(Producto& producto) {
	bool productoBorrado = producto.getEstaBorrado(); 

	std::cout << std::endl << VERDE << "Codigo: " << RESET << producto.getCodigo() << std::endl;
	std::cout << VERDE << "Descripcion: " << RESET << producto.getDescripcion() << std::endl;
	std::cout << VERDE << "Stock: " << RESET << producto.getStock() << std::endl;
	std::cout << VERDE << "Precio: " << RESET << producto.getPrecio() << std::endl;
	std::cout << VERDE << "Producto activo: " << RESET << (productoBorrado ? "No" : "Si") << std::endl;
	
}

void UiConsole::procesarActualizacionProducto(Manager& manager, Producto& producto, int posicionProducto, std::string campo) {

	std::string articulo = campo == "descripcion" ? "La " : "El ";
	std::string modificacion = campo == "descripcion" ? "modificada " : "modificado ";
	//Mensajes
	std::string mensajeExito = articulo + campo + " fue " + modificacion + "exitosamente";
	std::string mensajeFracaso = "Ocurrio un error al guardar los cambios. Intentelo nuevamente.";

	bool usuarioGuardadoExitosamente = manager.reescribirProducto(producto, posicionProducto);
	if (usuarioGuardadoExitosamente) {
		std::cout << VERDE << mensajeExito << RESET << std::endl;		
		this->pausa();
	}
	else {
		std::cout << ROJO << mensajeFracaso << RESET << std::endl;
		this->pausa();
	}
}