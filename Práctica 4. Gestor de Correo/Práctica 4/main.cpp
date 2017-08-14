/*
1º Doble grado de Ingeniería Informática y Matemáticas.
Juan Bosque Romero
Jorge Osés Grijalba
Manuel Sánchez Torrón
*/
#include "sesion.h"
#include "gestor.h"
#include "usuario.h" 

using namespace std;

int menu();

void opcionBandeja(tSesion & sesion, int & option);

int main(){
	
	int option, option2;
	bool iniciada;
	tGestor gestor;
	tSesion sesion = {nullptr, nullptr};

	gestor.dominio = dominio;

	if(arrancar(gestor, dominio)){

		option = menu();
	
		while(option != 0){
		
			if(option == 1){				
			
			sesion.puntUsuario = registraUsuario(gestor);	
			clearConsole();
			
			}
		
			else if(option == 2){
				sesion.puntUsuario = crearCuenta(gestor);
				//clearConsole();
			}

			else{
				apagar(gestor);
			}

			if(sesion.puntUsuario != nullptr){
				sesion.puntGestor = &gestor;
			}

			else{
				sesion.puntGestor = nullptr;
			}
			iniciada = iniciarSesion(sesion, sesion.puntGestor, sesion.puntUsuario); 
			if(iniciada == false) {
			cout << endl << "No se ha podido iniciar la sesion, pulse intro..." << endl;
			cin.get();
			clearConsole();
			}
			while(iniciada == true){
				
				opcionBandeja(sesion, option2);
				if (option2 != 0){
				iniciada = iniciarSesion(sesion, sesion.puntGestor, sesion.puntUsuario);
				
				}
				if (option2 == 0){
				iniciada = false;
				}
			}

			
			option = menu();

		}
		apagar(gestor);
	}

	else{
		cout << "\nHubo un problema al cargar los archivos.";
	}


return 0;
}

int menu(){

	int option;

		cout << endl << "Elija la opcion deseada: ";
		cout	 << "\n   1- Acceder a mi cuenta de correo";
		cout	 << "\n   2-Crear cuenta de correo\n";
		cout	 << "\n   0-Salir\n";

		cout << " ";
		cin >> option;
		
		cin.sync();
		cin.clear();
		clearConsole();
		while(option < 0 || option > 2){
			cout << endl << "Elija la opcion deseada: ";
			cout << "\n   1- Acceder a mi cuenta de correo";
			cout << "\n   2-Crear cuenta de correo\n";
			cout << "\n   0-Salir\n";

			cin >> option;
			
			cin.sync();
			cin.clear();
			clearConsole();
		}

return option;
}

void opcionBandeja (tSesion & sesion,int & option){
	
	int posicion;
	option = menuBandeja(sesion);//menuBandeja en módulo sesion

		if(option == 1){//leer correo 
			if(sesion.puntUsuario->recibidos == true){//Bandeja de entrada

				if(sesion.puntUsuario->listaRecibidos.contador != 0){
					leerCorreo(sesion);
				}

			}

			else{//Bandeja de salida

				if(sesion.puntUsuario->listaEnviados.contador != 0){
					leerCorreo(sesion);
				}

			}

		}

		else if(option == 2){//enviar correo
			clearConsole();
			enviarCorreo(sesion);
			
		}

		else if(option == 3){//borrar correo
			borrarCorreo(sesion);
			clearConsole();
		}

		else if(option == 4 ){//cambiar de bandeja
			clearConsole();
			cambiarBandeja(*sesion.puntUsuario);
		}

		else if(option == 5){//Lectura rápida de correos sin leer
			clearConsole();
			lecturaRapida(sesion);
		}

		else{//Cerrar sesión
			clearConsole();
		}

}