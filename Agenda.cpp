/*****************************
 Librerï¿½as utilizadas
*****************************/
#include <fstream>
#include <vector>
#include <string>
#include <iostream>					/*Flujo de entrada y salida de datos*/
#include <string.h>					/*Funciones de manejo de cadenas*/
//#include <windows.h>				/*Permite usar comandos de Windows Console*/
#include <stdio.h>


#define CANTIDAD 500 				/*Cantidad mï¿½xima de contactos: 500*/

using namespace std;

/*
	Variables globales que representan
	contactos registrados, eliminados y
	una variable Regla que presentara una
	mejor vista en el programa.
*/
int ContactosRegistrados = 0;
int ContactosEliminados = 0;
string Regla = "=============================================================";

/*****************************
Estructura de fecha y Agenda
*****************************/
/*Estructura de fecha de nacimiento*/
struct Cumple {
	string Nacimiento;
};

/*Estructura de Agenda, contiene todos los atributos*/
struct Agenda {
	string Nombre;
	string Telefono;
	string Celular;
	string Email;
	Cumple Fecha;					/*Referencia a la estructura Cumple*/
	Agenda();  						/*Declaraci?n del constructor*/
};

/*****************************
	FUNCIONES PRINCIPALES
*****************************/

int MenuPrimario();					/*Se muestra cuando no hay contactos*/
int MenuSecundario();				/*Se muestra cuando hay contactos que gestionar*/

/*Relevante e importante*/
void Insertar(struct Agenda Contactos[]);			/*Inserta contactos en la agenda*/

/*Relevante e importante*/
void Buscar(struct Agenda Contactos[]);				/*Busca contactos en la agenda*/
int BuscarMenuCategoria();							/*Se muestra un menï¿½ para buscar por categorï¿½as*/
void BuscarPorNombre(struct Agenda Contactos[]);	/*Aplica una bï¿½squeda por nombre de contacto*/
void BuscarPorTelefono(struct Agenda Contactos[]);	/*Aplica una bï¿½squeda por telï¿½fono de contacto*/
void BuscarPorCelular(struct Agenda Contactos[]);	/*Aplica una bï¿½squeda por celular de contacto*/
void BuscarPorEmail(struct Agenda Contactos[]);		/*Aplica una bï¿½squeda por email de contacto*/

/*Relevante e importante*/
void Listar(struct Agenda Contactos[]);				/*Lista todos los contactos existentes*/
void Imprimir(struct Agenda Contactos[], int);		/*Mostrar un contacto seleccionado*/

/*Relevante e importante*/
void Actualizar(struct Agenda Contactos[], int);	/*Actualiza un contacto seleccionado en la agenda*/
/*Relevante e importante*/
void Eliminar(struct Agenda Contactos[], int);		/*Elimina un contacto seleccionado en la agenda*/

int VerificarContacto(struct Agenda Contactos[], string);	/*Verifica si el contacto especificado existe*/

/*
Esta funci?n es interesante, tiene como objetivo
cargar datos (contactos) en la agenda para pruebas
r?pidas en la ejcuci?n del programa.
*/
void CargarContactos(struct Agenda Contactos[]);
bool HayContactos(struct Agenda Contactos[]);		/*Verifica si hay contactos en la agenda*/


/*Funcion para guardar contactos en los archivos*/
//void GuardarContactos();

/*****************************
	FUNCIONES SECUNDARIAS
*****************************/
void Detenerse();									/*Detiene la ejecuci?n, hasta que se presione una tecla*/
void LimpiarPantalla();								/*Limpia la pantalla para mostrar un nuevo Menï¿½*/
void Dormir(int);									/*Aplica un retraso temporal*/
int Salir();										/*Centinela que pregunta por la salida de los Menï¿½es*/

/*****************************
 DEFINICI?N DEL CONSTRUCTOR
-----------------------------
Inicializando la estructura.
*****************************/
Agenda::Agenda() {
	Nombre = " ";								/*Para nombre, dejar un espacio en blanco*/
	Telefono = "0";								/*Para tel?fono, dejar 0 como contenido*/
	Celular = "0";								/*Para celular, dejar 0 como contenido*/
	Email = " ";								/*Para email, dejar un espacio en blanco*/
	Fecha.Nacimiento = " ";							/*Para fecha, dejar un espacio en blanco*/
}

/*****************************
	  FUNCIÃ“N PRINCIPAL
*****************************/
int main(int argc, char* argv[]) {
	setlocale(LC_CTYPE, "spanish");
	int x;											/*Almacena las opciones seleccionadas*/
	int salir = 0;                                  /*bandera para salir*/
	Agenda Contactos[CANTIDAD]; 					/*Definici?n de la variable Contactos con la cantidad*/
	CargarContactos(Contactos);						/*Menï¿½ para cargar datos o iniciar una nueva agenda*/

	do {											/*Etiqueta para retornar al Menu recursivamente*/
		if (HayContactos(Contactos)) {				/*Verifica si no hay contactos*/
			ContactosRegistrados = 0;
			ContactosEliminados = 0;
			/*No hay contactos*/
			do {
				x = MenuPrimario();					/*Primer Menï¿½ donde la agenda est? vac?a*/
			} while (x < 1 || x > 2);

			switch (x) {								/*En este Menï¿½ se validan 2 opciones (Insertar, Salir)*/
			case 1:
				Insertar(Contactos);			/*Menï¿½ para insertar datos*/
				break;
			case 2:
				salir = Salir();				/*Centinela para Salir*/
				break;
			default:
				cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
				system("PAUSE>NUL");
				break;
			}

		}
		else {
			/*Si hay contactos*/
			do {
				x = MenuSecundario();				/*Segundo Menï¿½ donde la agenda contiene contactos*/
			} while (x < 1 || x > 4);

			switch (x) {								/*Este Menï¿½ contiene mï¿½s opciones (Insertar, buscar, listar)*/
			case 1:
				Insertar(Contactos);
				break;
			case 2:
				Buscar(Contactos);				/*Menï¿½ para realizar una bï¿½squeda de contactos por categor?as*/
				break;
			case 3:
				Listar(Contactos);				/*Listar todos los contactos existentes de manera interactiva*/
				break;
			case 4:
				salir = Salir();				/*Centinela para Salir*/
				break;
			default:
				cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
				system("PAUSE>NUL");
				break;
			}
		}
	} while (salir == 0);						/*Se retorna al Menï¿½ principal en caso de que no haya seleccionado Salir*/

	return 0;
}

int MenuPrimario() {
	int x;										/*Sirve para almacenar la respuesta (opci?n)*/

	LimpiarPantalla();

	cout << Regla << endl;
	cout << "|\tBienvenido a tu Agenda Electronica (Contactos)\t    |" << endl;
	cout << Regla << endl;

	cout << "|\t\t\t\t\t\t\t    |" << endl;
	cout << "|\t\t       No hay contactos\t\t\t    |" << endl;
	cout << "|\t\t\t\t\t\t\t    |" << endl;

	cout << Regla << endl;
	cout << "| (1) Nuevo contacto           |        (2) Salir           |" << endl;
	cout << Regla << endl;

	cout << "Esperando respuesta: ";
	cin >> x;

	return x;									/*Convierte y retorna la opci?n seleccionada*/
}

int MenuSecundario() {
	int x;

	LimpiarPantalla();

	cout << Regla << endl;
	cout << "|\tBienvenido a tu Agenda Electronica (Contactos)\t    |" << endl;
	cout << Regla << endl;

	cout << "|\t\t\t\t\t\t\t    |" << endl;
	cout << "|\t\t      Si hay contactos" << " (" << (ContactosRegistrados - ContactosEliminados) << ")\t\t    |" << endl;
	cout << "|\t\t\t\t\t\t\t    |" << endl;

	cout << Regla << endl;
	cout << "| (1) Nuevo   | (2) Buscar   |  (3) Listar   |  (4) Salir   |" << endl;
	cout << Regla << endl;

	cout << "Esperando respuesta: ";
	cin >> x;
	return x;
}

void Insertar(struct Agenda Contactos[]) {
	int x;
	int salir = 0;						/*bandera para salir*/

	do { 									/*Etiqueta de Menï¿½ para insertar contactos*/

		/*Se verifica si hay espacio en la agenda*/
		if (ContactosRegistrados < CANTIDAD) {
			cout << "\n\tNumero de contacto: " << (ContactosRegistrados + 1) << endl;
			cout << "\tNombre:   ";
			cin >> Contactos[ContactosRegistrados].Nombre;

			/*Se verifica si el contacto que est? intentando insertar, existe en la agenda*/
			if (VerificarContacto(Contactos, Contactos[ContactosRegistrados].Nombre)) {
				cout << "\n\tEl contacto \"" << Contactos[ContactosRegistrados].Nombre << "\" ya existe!" << endl;

				Contactos[ContactosRegistrados].Nombre = " ";

				/*Si existe se intenta ingresar otro*/
				do {
					cout << "\n\tDesea agregar otro contacto?" << endl;
					cout << "\t(1) Si, (2) No: ";
					cin >> x;

				} while (x < 1 || x > 2);

				switch (x) {
				case 1:
					// volvemos a InsertarMenu
					break;
				case 2:
					Detenerse();
					break;
				default:
					cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
					Detenerse();
					break;
				}
			}

			cout << "\tTel?fono: ";
			cin >> Contactos[ContactosRegistrados].Telefono;	/*Agregando valor a atributo Telefono*/

			cout << "\tCelular:  ";
			cin >> Contactos[ContactosRegistrados].Celular;	/*Agregando valor a atributo Celular*/

			cout << "\tEmail:    ";
			cin >> Contactos[ContactosRegistrados].Email;	/*Agregando valor a atributo Email*/

			cout << "\tFecha de Nacimiento (DD/MM/AAAA): ";
			cin >> Contactos[ContactosRegistrados].Fecha.Nacimiento;	/*Agregando valor a atributo de Fecha*/

			ContactosRegistrados++;									/*Se incrementa la variable, indicando nuevo contacto*/

			cout << "\n\t?Agregado con exito!" << endl << endl;


			do {
				cout << "\n\tDesea agregar otro contacto?" << endl;
				cout << "\t(1) Si, (2) No: ";
				cin >> x;

			} while (x < 1 || x > 2);

			switch (x) {
			case 1:
				// volvemos a InsertarMenu
				break;
			case 2:
				Detenerse();
				return;
				break;
			default:
				cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
				Detenerse();
				break;
			}

		}
		else {
			cout << "Llego al limite de contactos permitidos en la agenda." << endl << endl;
			Detenerse();
			MenuSecundario();
		}
	} while (salir == 0);

	Detenerse();
	return;
}

void Buscar(struct Agenda Contactos[]) {
	int x;
	int salir = 0;                                      /*bandera para salir*/

	do {
		LimpiarPantalla();

		do {
			x = BuscarMenuCategoria();				/*Menï¿½ para buscar contactos por categor?as*/
		} while (x < 1 || x > 5);

		switch (x) {
		case 1:
			BuscarPorNombre(Contactos);			/*Buscar por nombre*/
			break;
		case 2:
			BuscarPorTelefono(Contactos);		/*Buscar por tel?fono*/
			break;
		case 3:
			BuscarPorCelular(Contactos);		/*Buscar por celular*/
			break;
		case 4:
			BuscarPorEmail(Contactos);			/*Buscar por email*/
			break;
		case 5:
			salir = Salir();
			break;
		default:
			cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
			system("PAUSE>NUL");
			break;
		}

	} while (salir == 0);

	Detenerse();
	return;
}

int BuscarMenuCategoria() {
	int x;

	cout << endl << "\n\t\t     Realizar busqueda por:" << endl << endl;
	cout << "(1)Nombre | (2)Telefono | (3)Celular | (4)Email | (5)Volver" << endl;
	cout << Regla << endl;

	cout << "Esperando respuesta: ";
	cin >> x;


	return x;
}

void BuscarPorNombre(struct Agenda Contactos[]) {
	int i = 0; 					/*Iterador en el ciclo*/
	int c = 0;					/*Coincidencias*/

	string PorNombre;

	cout << "\n\tDigite el nombre: ";
	cin >> PorNombre;
	cout << endl;

	/*Recorrer la cantidad de contactos registrados en la agenda*/
	for (i = 0; i < ContactosRegistrados; i++) {
		if ((Contactos[i].Nombre == PorNombre)) {				/*Si lo encuentra*/
			Imprimir(Contactos, i);							/*Muestra la informaci?n del contacto*/
			c++;
			break;
		}
		else {
			cout << "\n\tEl contacto \"" << PorNombre << "\" no se ha encontrado." << endl << endl;
			Detenerse();
			return;
		}
	}

	if (c == 0)
		cout << "\n\tEl contacto \"" << PorNombre << "\" no se ha encontrado." << endl << endl;

	Detenerse();
	return;
}


void BuscarPorTelefono(struct Agenda Contactos[]) {
	int i = 0;
	int c = 0;

	string PorTelefono;

	cout << "\n\tDigite el numero de telefono: ";
	cin >> PorTelefono;
	cout << endl;

	for (i = 0; i < ContactosRegistrados; i++) {
		if ((Contactos[i].Telefono == PorTelefono)) {
			Imprimir(Contactos, i);
			c++;
			break;
		}
	}

	if (c == 0) {
		cout << "\n\tEl contacto \"" << PorTelefono << "\" no se ha encontrado." << endl << endl;
	}

	Detenerse();
	return;
}

void BuscarPorCelular(struct Agenda Contactos[]) {
	int i = 0;
	int c = 0;					/*Coincidencias*/

	string PorCelular;

	cout << "\n\tDigite el numero de celular: ";
	cin >> PorCelular;
	cout << endl;

	for (i = 0; i < ContactosRegistrados; i++) {
		if ((Contactos[i].Celular == PorCelular)) {
			Imprimir(Contactos, i);
			c++;
			break;
		}
	}

	if (c == 0) {
		cout << "\n\tEl contacto \"" << PorCelular << "\" no se ha encontrado." << endl << endl;
	}

	Detenerse();
	return;
}

void BuscarPorEmail(struct Agenda Contactos[]) {
	int i = 0;
	int c = 0;					/*Coincidencias*/

	string PorEmail;

	cout << "\n\tDigite el Email: ";
	cin >> PorEmail;
	cout << endl;

	for (i = 0; i < ContactosRegistrados; i++) {
		if ((Contactos[i].Email == PorEmail)) {
			Imprimir(Contactos, i);
			c++;
			break;
		}
	}

	if (c == 0) {
		cout << "\n\tEl contacto \"" << PorEmail << "\" no se ha encontrado." << endl << endl;
	}

	Detenerse();
	return;
}


void Listar(struct Agenda Contactos[]) {
	int i = 0;									/*Iterador del ciclo*/
	int x = 0; 									/*N?mero de contacto*/
	int contactos_restantes = 0;				/*Contactos restantes*/

	/*Se recorren todos los contactos registrados*/
	for (; i < ContactosRegistrados; i++) {

		/*Si se encuentran contactos registrados*/
		if (Contactos[i].Nombre != " ") {
			if (i > 1) {
				contactos_restantes = (ContactosRegistrados - x) - ContactosEliminados;
				Dormir(1);						/*Aplicar retraso de 1 segundo*/

				if (contactos_restantes > 1)
					cout << "\t-- Aun quedan " << contactos_restantes << " por visualizar --" << endl;
				else if (contactos_restantes == 1)
					cout << "\t-- Solo queda " << contactos_restantes << " por visualizar --" << endl;

				Detenerse();
				cout << endl;
			}

			/*Impresi?n de todos los datos de los contactos resultates*/
			cout << "\n\tNumero de contacto: " << (x + 1) << endl;
			cout << "\t\tNombre:   " << Contactos[i].Nombre << endl;
			cout << "\t\tTelefono: " << Contactos[i].Telefono << endl;
			cout << "\t\tCelular:  " << Contactos[i].Celular << endl;
			cout << "\t\tEmail:    " << Contactos[i].Email << endl;
			cout << "\t\tFecha N.: " << Contactos[i].Fecha.Nacimiento << endl << endl;

			x++;			/*Incremento de la variable de n?mero de contacto*/
		}
	}

	cout << "\t <-- Regresar" << endl;
	Detenerse();
	return;
}
void Imprimir(struct Agenda Contactos[], int posicion) {
	int x;

	/*Imprime el contacto que est? en una posici?n espec?fica de la agenda*/
	cout << "\n\t\tNombre:   " << Contactos[posicion].Nombre << endl;
	cout << "\t\tTelefono: " << Contactos[posicion].Telefono << endl;
	cout << "\t\tCelular:  " << Contactos[posicion].Celular << endl;
	cout << "\t\tEmail:    " << Contactos[posicion].Email << endl;
	cout << "\t\tFecha N.: " << Contactos[posicion].Fecha.Nacimiento << endl << endl;

	/*CENTINELA: Opciones Actualizar y Elmiminar contacto*/
	do {
		cout << "\t  Opciones del contacto \"" << Contactos[posicion].Nombre << "\"" << endl;
		cout << "\t(1) Actualizar | (2) Eliminar | (3) Volver " << endl;
		cout << Regla << endl;

		cout << "Esperando respuesta: ";
		cin >> x;

		cout << endl;

	} while (x < 1 || x > 3);

	switch (x) {
	case 1:
		Actualizar(Contactos, posicion);				/*Actualiza el contacto seleccionado*/
		break;
	case 2:
		Eliminar(Contactos, posicion);					/*Elimina el contacto seleccionado*/
		break;
	case 3:
		if (Salir() == 1)
			return;
	default:
		cout << "\n\tUp's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
		Detenerse();
		break;
	}

	return;
}

void Actualizar(struct Agenda Contactos[], int posicion) {
	int x;
	string Nombre, Telefono, Celular, Email;			/*Declaraci?n de variables que almacenar?n una copia*/
	int salir = 0;                                      /*bandera para salir*/

	do { 												//ActualizarOtroContacto: 

		Nombre = Contactos[posicion].Nombre;
		Telefono = Contactos[posicion].Telefono;
		Celular = Contactos[posicion].Celular;
		Email = Contactos[posicion].Email;

		/*Menï¿½ para seleccionar qu? atributos desean actualizar*/
		do {
			cout << "\n\t¿Que dato le gustaria actualizar de este contacto?" << endl;
			cout << "  (1)Nombre | (2)Telefono | (3)Celular (4)Email | (5)Ninguno" << endl;
			cout << Regla << endl;

			cout << "Esperando respuesta: ";
			cin >> x;

			cout << endl;

		} while (x < 1 || x > 5);

		/*Modificaci?n para los correspondientes atributos seleccionados*/
		switch (x) {
		case 1:
			cout << "\tDigite el nuevo nombre: ";
			cin >> Contactos[posicion].Nombre;
			cout << "   Se ha actualizado de \"" << Nombre << "\" a " << "\"" << Contactos[posicion].Nombre << "\"" << endl;
			break;
		case 2:
			cout << "\tDigite el nuevo tel?fono: ";
			cin >> Contactos[posicion].Telefono;
			cout << "   Se ha actualizado de \"" << Telefono << "\" a " << "\"" << Contactos[posicion].Telefono << "\"" << endl;
			break;
		case 3:
			cout << "\tDigite el nuevo celular: ";
			cin >> Contactos[posicion].Celular;
			cout << "   Se ha actualizado de \"" << Celular << "\" a " << "\"" << Contactos[posicion].Celular << "\"" << endl;
			break;
		case 4:
			cout << "\tDigite el nuevo email: ";
			cin >> Contactos[posicion].Email;
			cout << "   Se ha actualizado de \"" << Email << "\" a " << "\"" << Contactos[posicion].Email << "\"" << endl;
			break;
		case 5:
			salir = Salir();
		default:
			cout << "\n\tUp's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
			Detenerse();
			break;
		}
	} while (salir == 0);

	return;
}

void Eliminar(struct Agenda Contactos[], int posicion) {
	string Nombre;

	Nombre = Contactos[posicion].Nombre;

	/*Despu?s de ejecutar la centinela, se resetean los valores de esa posici?n
	  y no se vuelven a tomar en cuenta. Este algoritmo est? trabajado para que
	  no perjudique en ning?n momento en la ejecuci?n del programa.
	*/
	if (Salir() == 1) {
		Contactos[posicion].Nombre = " ";
		Contactos[posicion].Telefono = "0";
		Contactos[posicion].Celular = "0";
		Contactos[posicion].Email = " ";
		ContactosEliminados++;

		cout << "\n?El ex-contacto \"" << Nombre << "\" ha sido eliminado con ?xito!\n\n";
	}

	return;
}

int VerificarContacto(struct Agenda Contactos[], string Nombre) {
	int i = 0;
	int c = 0;

	/*Verifica si existe un contacto en espec?fico*/
	for (; i < ContactosRegistrados; i++) {
		if (Contactos[i].Nombre == Nombre) {
			c++;
			break;
		}
	}

	if (c == 0)
		return false;

	return true;
}

void CargarContactos(struct Agenda Contactos[]) {
	int x;

	/*Cargar datos por omisi?n para realizar pruebas r?pidas de las opciones
	  que presenta este programa sobre la gesti?n de contactos de la Agenda.
	*/
	do {
		LimpiarPantalla();

		cout << Regla << endl;
		cout << "|\tBienvenido a tu Agenda Electronica (Contactos)\t    |" << endl;
		cout << Regla << endl;

		cout << "(1) Cargar contactos previos | (2) Nueva agenda | (3) Salir |" << endl;
		cout << Regla << endl;

		cout << "Esperando respuesta: ";
		cin >> x;


	} while (x < 1 || x > 3);

	switch (x) {
	case 1:
		/*Primer contacto*/
		Contactos[ContactosRegistrados].Nombre = "Pedro";
		Contactos[ContactosRegistrados].Telefono = "+51222111";
		Contactos[ContactosRegistrados].Celular = "+51963852741";
		Contactos[ContactosRegistrados].Email = "pedropicapiedra@gmail.com";
		Contactos[ContactosRegistrados].Fecha.Nacimiento = "16/12/1986";
		ContactosRegistrados++;

		/*Segundo contacto*/
		Contactos[ContactosRegistrados].Nombre = "Pablo";
		Contactos[ContactosRegistrados].Telefono = "+51221133";
		Contactos[ContactosRegistrados].Celular = "+51987654321";
		Contactos[ContactosRegistrados].Email = "pablomarmol@gmail.com";
		Contactos[ContactosRegistrados].Fecha.Nacimiento = "22/08/1993";
		ContactosRegistrados++;

		/*Tercer contacto*/
		Contactos[ContactosRegistrados].Nombre = "Vilma";
		Contactos[ContactosRegistrados].Telefono = "+51223311";
		Contactos[ContactosRegistrados].Celular = "+51951874236";
		Contactos[ContactosRegistrados].Email = "vilmagrava@gmail.com";
		Contactos[ContactosRegistrados].Fecha.Nacimiento = "06/04/1996";
		ContactosRegistrados++;

		/*Cuarto contacto*/
		Contactos[ContactosRegistrados].Nombre = "Betty";
		Contactos[ContactosRegistrados].Telefono = "+51224433";
		Contactos[ContactosRegistrados].Celular = "+51951632478";
		Contactos[ContactosRegistrados].Email = "vilmacaliza@gmail.com";
		Contactos[ContactosRegistrados].Fecha.Nacimiento = "10/07/1999";
		ContactosRegistrados++;
		break;
	case 2:
		return;
	case 3:
		if (Salir() == 1)
			exit(0);
	default:
		cout << "\n\tUp's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
		Detenerse();
		break;
	}

	return;
}

bool HayContactos(struct Agenda Contactos[]) {
	int i = 0; 					/*Iterador*/
	int c = 0;					/*Coincidencias*/

	/*Verifica si hay contactos disponibles*/
	for (; i < CANTIDAD; i++)
		if (Contactos[i].Nombre != " ")
			c++;

	if (c > 0)
		return false; //Estï¿½ vaciï¿½

	return true;
}

void Detenerse() {
	cout << "\tPresione una tecla para continuar!";
	system("PAUSE");								/*Pausar la aplicaciï¿½n sin mensaje de salida*/
}

void LimpiarPantalla() {
	system("CLS");									/*Limpiar pantalla*/
}

void Dormir(int x) {
	//Sleep(x * 1000);							/*Dormir el programa*/
}


/*La función vector es un tipo de arreglo que se puede declarar en cierta longitud

Posteriormente se agregara a la salida del programa
*/

void GuardarContactos(const std::vector<Agenda>& contactos, const std::string& nombreArchivo) {
	std::ofstream Archivo(nombreArchivo);

	if (Archivo.is_open()) {								/*Abrir archivo*/
		for (const auto& contacto : contactos) {
			Archivo << "Nombre: " << contacto.Nombre << std::endl;
			Archivo << "Teléfono: " << contacto.Telefono << std::endl;
			Archivo << "Correo: " << contacto.Email << std::endl;
			Archivo << "Email: " << contacto.Email << std::endl;
			Archivo << "Fecha.Nacimiento: " << contacto.Email << std::endl;
			Archivo << std::endl;
		}
		Archivo.close();									/*Cerrar archivo*/
		std::cout << "Contactos guardados en el archivo: " << nombreArchivo << std::endl;
	}
	else {
		std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
	}
}

/*La salida confirma los contactos que quedan o fueron eliminados*/
int Salir() {
	int x;				/*Declaración de decision*/

	do {
		cout << "\n\tEstas seguro(a) de querer hacerlo?" << endl;
		cout << "\t(1) Si, (2) No: ";
		cin >> x;
		std::vector<Agenda> contactos;
		Agenda NuevoContacto;
		/*Los contactos nuevos deben agregarse al vector*/
		contactos.push_back(NuevoContacto);

		std::string NombreDeArchivo = "Contactos.txt";		/*Asignamos un nombre para guardar los archivos*/

		GuardarContactos(contactos, NombreDeArchivo);		/*Función que guarda los contactos en el archivo txt*/
	} while (x < 1 || x > 2);

	cout << endl;

	return x;
}
