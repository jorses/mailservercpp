#include "usuario.h"

int menuEntrada(){
	
	int option;

	cout << "Elija una opcion:" << endl
		 << "1- Leer correo." << endl
		 << "2- Enviar correo." << endl
		 << "3- Borrar correo." << endl
		 << "4- Ver bandeja de salida." << endl
		 << "5- Lectura rapida de correos sin leer." << endl
		 << "0- Cerrar sesion." << endl;

	cin >> option;
			
	cin.sync();
	cin.clear();
	while(option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 0){
		cout << "Elija una opcion valida:" << endl
			 << "1- Leer correo." << endl
			 << "2- Enviar correo." << endl
			 << "3- Borrar correo." << endl
			 << "4- Ver bandeja de salida." << endl
			 << "5- Lectura rapida de correos sin leer." << endl
			 << "0- Cerrar sesion." << endl;

		cin >> option;
				
		cin.sync();
		cin.clear();
	}

return option;
}

void iniciar(tUsuario & usuario, const string & idUser, const string & contrasenia){
//Recibe un identificador de usuario y una contraseña e inicia el usuario. La bandeja activa inicial es la de entrada.

		usuario.nombre = idUser;
		usuario.password = contrasenia;
		inicializar(usuario.listaRecibidos);
		inicializar(usuario.listaEnviados);
		usuario.recibidos = true;
}

void guardar(const tUsuario & usuario, ofstream & archivo){
//Dado un flujo de archivo (ya abierto), guarda el usuario en fichero

	archivo << usuario.nombre << endl;
	archivo << usuario.password << endl;

	guardar(usuario.listaRecibidos, archivo);
	guardar(usuario.listaEnviados, archivo);

}

bool cargar(tUsuario & usuario, ifstream & archivo){ //Está bien
//Dado un flujo de archivo (ya abierto), carga el usuario del fichero.

	//Esta función tiene que llamar a la de cargar de ListaBandeja para cargar las bandejas de entrada y salida.

	bool cargado = false;
	int i;
	string nombre;
	string pass;
	tListaBandeja listElems;

	archivo >> nombre;
	archivo >> pass;

	if(nombre != "XXX"){

		cargado = true;

		usuario.nombre = nombre;
		usuario.password = pass;
		usuario.recibidos = true;

		cargar(listElems, archivo);

		usuario.listaRecibidos.contador = listElems.contador;

		for(i = 0; i < usuario.listaRecibidos.contador; i++){
			usuario.listaRecibidos.lista[i].id = listElems.lista[i].id;
			usuario.listaRecibidos.lista[i].leido = listElems.lista[i].leido;
		}

		cargar(listElems, archivo);

		usuario.listaEnviados.contador = listElems.contador;

		for(i = 0; i < usuario.listaEnviados.contador; i++){
			usuario.listaEnviados.lista[i].id = listElems.lista[i].id;
			usuario.listaEnviados.lista[i].leido = listElems.lista[i].leido;
		}

	}

return cargado;
}

bool validarContrasenia(const tUsuario & usuario, const string & contrasenia){
//Recibe una contraseña y un usuario y devuelve si la contraseña es correcta o no.
	return usuario.password == contrasenia;
}

void cambiarBandeja(tUsuario & usuario){
//Cambia la bandeja activa del usuario.

	if(usuario.recibidos == true){
			usuario.recibidos = false;
		}

	else{
		usuario.recibidos = true;
	}

}