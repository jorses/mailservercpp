#include "sesion.h"
using namespace std;
void Bandeja(const tSesion & sesion){

	string rekt;
	int pos;
	tListaBandeja *bandejaux;
	string titleaux;
		if (sesion.puntUsuario->recibidos){
		bandejaux = &sesion.puntUsuario->listaRecibidos;
		titleaux = "Entrada";
		}
		else{
		
		bandejaux= &sesion.puntUsuario->listaEnviados;
		titleaux = "Salida";
		}
			cout << endl <<  "Correo de " << sesion.puntUsuario->nombre << endl;
		

			cout << setfill(' ') << right << setw(44)  <<  "Bandeja de "<< titleaux  << setw(37) << endl;
			cout << setfill('-') << setw(86);
			cout << "L N   " << setfill(' ') << left <<  setw(EMISOR_CAP) << "EMISOR" << left << setw(ASUNTO_CAP) << "ASUNTO" << right << setw(20) << "FECHA";
			cout << endl << endl;
			// EMISOR_CAP Y ASUNTO CAP DEFINIDAS COMO CONSTANTES DEL ANCHO DE CAMPO EN CORREO.H
			cout << setfill('-') << setw(82) << endl;
	
	
				for (int i = bandejaux->contador-1; i >=0; i--){
					
					if(buscar(sesion.puntGestor->listaCorreos, bandejaux->lista[i].id, pos)){
						
						if(bandejaux->lista[i].leido){
							 rekt = "  ";
						}
						else {
							 rekt = "* ";
						}
						
						cout  << rekt << bandejaux->contador-i << " - " << cabecera (sesion.puntGestor->listaCorreos.arrayCorreos[pos]); //No lee bien el asunto
						
					}
					
				}
			

}

bool iniciarSesion(tSesion & sesion, tGestor* gestor, tUsuario* usuario){/* Inicia la sesión y muestra la pantalla del menú principal de la
	sesión.	*/
	
	bool output = false;
	string rekt, cabeza;

	if  (gestor != nullptr && usuario != nullptr){
		output = true;
		sesion.puntGestor = gestor;
		sesion.puntUsuario = usuario;

		Bandeja(sesion);

	}

	return output; 
}

void leerCorreo(tSesion & sesion){/* Solicita el correo que el usuario
	quiere leer (será el número con el que el correo es mostrado por pantalla en la
	bandeja correspondiente), valida que existe y si es así, lo marca como correo
	leído. A continuación, busca el correo en la lista de correos y si lo encuentra
	muestra en la pantalla el menú de lectura del correo (aparece el correo y las
	opciones: contestar,…).*/
		int number;
		int pos;
		int option;
		string idAux, toString;
		bool encontrado = false;
		tListaBandeja *bandejaux;
		tCorreo newCorreo;
		if (sesion.puntUsuario->recibidos){
		bandejaux = &sesion.puntUsuario->listaRecibidos;
		
		}
		else{
		
		bandejaux = &sesion.puntUsuario->listaEnviados;
		}
		cout << "Introduzca el correo que desea leer." << endl;
		cin >> number;
				
		cin.sync();
		cin.clear();
		

		while(number < 1 || bandejaux->contador < number){
			cout << "Introduzca un correo existente." << endl;
			cin >> number;
				
			cin.sync();
			cin.clear();
		}
		clearConsole();

		number = bandejaux->contador-number;
		if(buscar(sesion.puntGestor->listaCorreos, bandejaux->lista[number].id, pos )){//comprobamos que existe
			
			toString = to_string(sesion.puntGestor->listaCorreos.arrayCorreos[pos]);
			cout << toString;
			correoLeido(*bandejaux, bandejaux->lista[number].id);
			encontrado = true;
		}

	
	
	if(encontrado == true){

			cout << left << setw(80) << setfill('-') << '-';
			cout << "Elija una opcion: " << endl;
			cout << "1 - Contestar al correo." << endl;
			cout << "2 - Reenviar correo." << endl;
			cout << "0 - Volver a la bandeja." << endl;
			cout << left << setw(80) << setfill('-') << '-';
			cout << "Introduzca una opcion: ";
			cin >> option;
					
			cin.sync();
			cin.clear();

			while(option < 0 || 2 < option){
				cout << left << setw(80) << setfill('-') << '-';
				cout << "Elija una opcion valida: " << endl;
				cout << "1 - Contestar al correo." << endl;
				cout << "2 - Reenviar correo." << endl;
				cout << "0 - Volver a la bandeja." << endl;
				cout << left << setw(80) << setfill('-') << '-';
				cout << "Introduzca una opcion valida: ";
				cin >> option;
					
				cin.sync();
				cin.clear();
			}
			clearConsole();

			if(option == 1){			
				correoContestacion(sesion.puntGestor->listaCorreos.arrayCorreos[pos], newCorreo, sesion.puntUsuario->nombre);
				enviarCorreo(*sesion.puntGestor, *sesion.puntUsuario, newCorreo);
				clearConsole();
			}

			else if(option == 2){
				correoForward(sesion.puntGestor->listaCorreos.arrayCorreos[pos], newCorreo, sesion.puntUsuario->nombre);
				enviarCorreo(*sesion.puntGestor, *sesion.puntUsuario, newCorreo);
				clearConsole();
			}
	}
}

void enviarCorreo(tSesion & sesion){/* Solicita los datos del nuevo
	correo (destinatario, asunto, cuerpo, …) y lo envía a través del gestor.*/
	tCorreo nuevo;
	correoNuevo(nuevo, sesion.puntUsuario->nombre);
	
	enviarCorreo(*sesion.puntGestor, *sesion.puntUsuario, nuevo);
	
	clearConsole();

}

void borrarCorreo(tSesion & sesion){/* Solicita el correo que el usuario
	quiere borrar (será el número con el que el correo es mostrado por pantalla en la
	bandeja correspondiente), valida que existe y si es así, indica al gestor que lo
	borre.*/

	int number;
	tListaBandeja * bandejaux;
			cout << "Que correo quiere eliminar?\n";
			cin >> number;
			
			cin.sync();
			cin.clear();

			
			
			if(sesion.puntUsuario->recibidos){
				bandejaux = &sesion.puntUsuario->listaRecibidos;
				cout <<endl<< "detecta que estamos en entrada" << endl;
			
			}
			else{
				bandejaux = &sesion.puntUsuario->listaEnviados;
				cout <<endl<< "detecta que estamos en salida" << endl;
			}
			number = bandejaux->contador-number;
			if(buscar(*bandejaux, bandejaux->lista[number].id)!= -1){
					cout <<endl << "encuentra el correo en la bandeja" << endl;
						
				eliminarCorreo(*sesion.puntGestor, *sesion.puntUsuario, bandejaux->lista[number].id);
				
					
				}
}

void lecturaRapida(tSesion & sesion){
	
	/* Este subprograma implementa
	la lectura rápida de correos sin leer. El resultado es que muestra en una pantalla
	todos los correos sin leer (de la bandeja activa) ordenados por asunto
	(ignorando todos los “Re: ” y "Fw: ") y por fecha. Al finalizar su ejecución los correos sin
	leer quedarán marcados como leídos.
	*/
	bool inter = true;
	int j;
	int k;
	tCorreo *auxCorreo=nullptr;
	tPuntCorreos auxCorreos;//array de punteros a tCorreo como nos pediste que implementáramos en el email que nos mandaste
	tListaBandeja * bandejaux;
	int posicion;
	if (sesion.puntUsuario->recibidos){
		bandejaux = &sesion.puntUsuario->listaRecibidos;
	}
	else{
		bandejaux = &sesion.puntUsuario->listaEnviados;
	}
	
	auxCorreos.contador = 0; // no hay inline para iniciar array de punteros, y realmente solo lo usamos una vez
	

	for (int i = 0; i< bandejaux->contador; i++){//los que no estan leidos los buscamos en el array de listaCorreos.arrayCorreos y los pasamos al de noleidos
		if(bandejaux->lista[i].leido == false){
			
			if(buscar(sesion.puntGestor->listaCorreos, bandejaux->lista[i].id, posicion)){
				
				auxCorreos.arrayCorreos[auxCorreos.contador] =  &sesion.puntGestor->listaCorreos.arrayCorreos[posicion];
				auxCorreos.contador++;
			}
		bandejaux->lista[i].leido = true;// los marcamos como leidos
		}
	}
	 k = auxCorreos.contador-1;//k es longitud-1
	
	 j = 0;
	while((j< k) && inter){
	
	inter = false; // comprobando si se realiza algún intercambio
		for ( int i = k; i > j; i--){//k es longitud-1
			if (quitaRes(*auxCorreos.arrayCorreos[i]) < quitaRes(*auxCorreos.arrayCorreos[i-1])) {
				 auxCorreo = auxCorreos.arrayCorreos[i];
				auxCorreos.arrayCorreos[i] = auxCorreos.arrayCorreos[i-1];
				auxCorreos.arrayCorreos[i-1] = auxCorreo;

			inter = true;
			}
			else if (auxCorreos.arrayCorreos[i]->Asunto == auxCorreos.arrayCorreos[i-1]->Asunto){
				if(auxCorreos.arrayCorreos[i]->fecha < auxCorreos.arrayCorreos[i-1]->fecha){
				auxCorreo = auxCorreos.arrayCorreos[i];
				auxCorreos.arrayCorreos[i] = auxCorreos.arrayCorreos[i-1];
				auxCorreos.arrayCorreos[i-1] = auxCorreo;
				inter = true;
				}
			}
	}
		
	j++; 
	}
	
	for (int i =0; i< auxCorreos.contador;i++){
		cout << to_string(*auxCorreos.arrayCorreos[i]);
		
	}

	cout << endl << "Pulsa intro para continuar..." << endl;
	cin.get();
	clearConsole();

}

string quitaRes(const tCorreo & noLeido){
	istringstream iss(noLeido.Asunto);
	string aux= "Re: ";
	string stringiss;
	//leer char a char->"Re: "
	while( !iss.eof()){
		iss >> stringiss;
		if (stringiss != "Re: " || stringiss != "Fw: "){
		aux = aux + " "+ stringiss;
		}
		
	}
	//aux = noLeido.Asunto;
	return aux;
}

int menuBandeja(const tSesion & sesion){

	int option;

			cout << fixed << setfill('-') << setw(81)<< right <<"\n";
			cout << "Elija una opcion: \n";
			cout << "1- Leer correo" << endl;
			cout << "2- Enviar correo"<< endl;
			cout << "3- Borrar correo"<<endl;

			if(sesion.puntUsuario->recibidos == true){
				cout << "4- Ver bandeja de Salida" << endl;
			}

			else{
				cout << "4- Ver bandeja de Entrada" << endl;
			}
			cout << "5- Lectura rapida de correos sin leer"<<endl;
			cout << "0- Cerrar sesion" << endl;
			cout << fixed << setfill('-') << setw(81)<< right <<"\n";
			cout << "Introduzca una opcion: " << endl;

			cin >> option;
					
			cin.sync();
			cin.clear();
			while(option < 0 || 5 < option){

				cout << fixed << setfill('-') << setw(81)<< right <<"\n";
				cout << "Elija una opcion: \n";
				cout << "1- Leer correo" << endl;
				cout << "2- Enviar correo"<< endl;
				cout << "3- Borrar correo"<<endl;

				if(sesion.puntUsuario->recibidos == true){
					cout << "4- Ver bandeja de Salida" << endl;
				}

				else{
					cout << "4- Ver bandeja de Entrada" << endl;
				}
				cout << "5- Lectura rapida de correos sin leer"<<endl;
				cout << "0- Cerrar sesion" << endl;
				cout << fixed << setfill('-') << setw(81)<< right <<"\n";
				cout << "Introduzca una opcion: " << endl;

				cin >> option;
							
				cin.sync();
				cin.clear();

			}	

return option;
}
