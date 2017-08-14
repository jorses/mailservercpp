#include "correo.h"


string leerCuerpo(){

	string cuerpo,linea;
	cout << endl << "Escribe el las lineas del cuerpo del correo (X para acabar)" << endl;

	getline(cin, linea);
	
	cin.sync();
	cin.clear();

	while (linea!="X"){

		cuerpo=cuerpo+"\n"+linea;
		
		getline(cin, linea);
		
		cin.sync();
		cin.clear();

	}

	return cuerpo;

}

string cargarCuerpo(ifstream & archivo){

	string cuerpo,linea;

	getline(archivo, linea);

	while (linea!="X"){

		cuerpo=cuerpo+"\n"+linea;
		
		getline(archivo, linea);

	}

	return cuerpo;

}

void correoNuevo (tCorreo & correo, const string & emisor){
	string asuntoaux;
	correo.fecha=time(0);
	correo.idMail=emisor+"_"+to_string(correo.fecha);
	correo.Emisor=emisor;
	cout << "Enviar a : ";
	cin >> correo.Destinatario;
	
	cin.ignore();
	cout << "Asunto: ";
	getline (cin, asuntoaux);
	correo.Asunto = asuntoaux;
	correo.Cuerpo=leerCuerpo();
	correo.numAccs=2;

}

void correoContestacion (const tCorreo & correoOriginal, tCorreo & correo, const string & emisor){
	
	ostringstream flujo;
	string añadir;

	flujo << endl << endl << mostrarFecha(correoOriginal.fecha) << endl; 
	flujo << correoOriginal.Emisor << endl;
	flujo << correoOriginal.Destinatario << endl;
	flujo << correoOriginal.Asunto << endl << endl;
	flujo << correoOriginal.Cuerpo << endl;

	añadir = flujo.str();

	correo.fecha=time(0);
	correo.idMail=emisor+"_"+to_string(correo.fecha);
	correo.Emisor=emisor;
	correo.Destinatario=correoOriginal.Emisor;
	correo.Asunto="Re: "+correoOriginal.Asunto;
	correo.Cuerpo=leerCuerpo()+"\n\n" + añadir;;
	correo.numAccs=2; 
	cout <<correoOriginal.Asunto; 
}

void guardar ( const tCorreo & correo, ofstream & archivo){
	
	archivo << correo.idMail << endl;
	archivo << correo.fecha << endl;
	archivo << correo.numAccs << endl;
	archivo << correo.Emisor << endl;
	archivo << correo.Destinatario << endl;
	archivo << correo.Asunto << endl;
	archivo << correo.Cuerpo;
	archivo <<endl << "X" << endl;
}

bool cargar (tCorreo & correo, ifstream & archivo){

	bool output=false;
	
	archivo >> correo.idMail;

	if (correo.idMail!="XXX"){

		archivo >> correo.fecha;
		archivo >> correo.numAccs;
		archivo >> correo.Emisor;
		archivo >> correo.Destinatario;
		archivo.ignore();
		getline(archivo, correo.Asunto);
		
		correo.Cuerpo=cargarCuerpo(archivo);

		output=true;

	}

	return output;
}

int disminuirNumAccs( tCorreo & correo){

	correo.numAccs= correo.numAccs-1;

	return correo.numAccs;

}

string to_string(const tCorreo & correo){/* Devuelve un string con el
	contenido completo del correo en el formato para mostrarlo en la consola (ver
	pantalla de la sección 1.3).*/
	ostringstream correoConsola;
	string aux;
	correoConsola << endl << "De:  " << correo.Emisor << right << setw(50) <<  mostrarFecha(correo.fecha) << "\n";
	correoConsola << "Para:  " << correo.Destinatario << "\n";
	correoConsola << "Asunto:  " << correo.Asunto << "\n" << "\n"; 
	correoConsola <<  correo.Cuerpo << "\n";
	aux = correoConsola.str();
	return aux;
	}

string cabecera(const tCorreo & correo){/* Devuelve un string que
	contiene la información que se mostrará en la bandeja de entrada/salida: emisor,
	asunto y fecha sin hora (ver pantalla de la sección 1.2).*/
	ostringstream cabeza;
	string aux;
	string auxAsunto;
	string auxEmisor;
	
	auxEmisor = truncEmisor(correo.Emisor);
	auxAsunto = truncAsunto(correo.Asunto);
	cabeza << left << setw(EMISOR_CAP) << auxEmisor << left << setw(ASUNTO_CAP) << auxAsunto << right << setw(24) << mostrarSoloDia(correo.fecha) << "\n";
	aux = cabeza.str();
	return aux;
}

string mostrarFecha(tFecha fecha){
	ostringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << '/' << 1 + ltm.tm_mon <<'/'<<ltm.tm_mday;
	resultado<<" ("<<ltm.tm_hour<< ':' <<ltm.tm_min<< ':' << ltm.tm_sec << ')';
	return resultado.str();
	}

string mostrarSoloDia(tFecha fecha){
	ostringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << '/' << 1 + ltm.tm_mon <<'/'<<ltm.tm_mday;
	return resultado.str();
	}

string truncAsunto(string asunto){
	string truncada;
	if(asunto.length() > ASUNTO_CAP){
		for(int i =0; i<ASUNTO_CAP-3;i++){
			
			truncada = truncada + asunto.at(i);
		
		}
		truncada = truncada + "...";
	}
	else{
	truncada = asunto;
	}

	return truncada;
}

string truncEmisor(string emisor){
	string truncada;
	if(emisor.length() > EMISOR_CAP){
		for(int i =0; i<EMISOR_CAP-6;i++){
			
			truncada = truncada + emisor.at(i);
		
		}
		truncada = truncada + "...";
	}
	else{
	truncada = emisor;
	}

	return truncada;
}

void correoForward (const tCorreo & correoOriginal, tCorreo & correo, const string & emisor){
	
	/*ostringstream flujo;
	string añadir;

	flujo << endl << endl << mostrarFecha(correoOriginal.fecha) << endl;
	flujo << correoOriginal.Emisor << endl;
	flujo << correoOriginal.Destinatario << endl;
	flujo << correoOriginal.Asunto << endl << endl;
	flujo << correoOriginal.Cuerpo << endl;

	añadir = flujo.str();
	*/
	correo.fecha=time(0);
	correo.idMail=emisor+"_"+to_string(correo.fecha);
	correo.Emisor=correoOriginal.Destinatario; // Hemos decidido que figure como emisor del correo reenviado el que lo había recibido en un principio(el que lo reenvía)
	cout << "\nA quién desea reenviar el correo?\n";
	cin>>correo.Destinatario;
	correo.Asunto="Fw: "+correoOriginal.Asunto;
	correo.Cuerpo=correoOriginal.Cuerpo;
	correo.numAccs=correoOriginal.numAccs+1; 
	//cout <<correoOriginal.Asunto; 
}