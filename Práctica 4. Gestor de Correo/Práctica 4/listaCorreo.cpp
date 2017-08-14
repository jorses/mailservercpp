#include "listaCorreo.h"



void guardar(const tListaCorreos & correos, const string & nombre){
	ofstream write;
	
	write.open(nombre);
	if (write.is_open() ){// si existe...
	
		for (int i =0; i< correos.contador; i++){
			guardar(correos.arrayCorreos[i], write);
			
			
		}
		write << "XXX";
	}

	write.close();

}
	 	
bool insertar(tListaCorreos & correos, const tCorreo & correo){
	bool insertado = false;
	if (!llena(correos)){
	if (correos.contador < MAX_CORREOS ){
	int position;
		if( !buscar (correos, correo.idMail,position)){
			for (int i = correos.contador; i >=position; i--){
			correos.arrayCorreos[i+1]= correos.arrayCorreos[i];
			}
			correos.arrayCorreos[position] = correo;
			correos.contador++;
			insertado = true;
		}
	}

	}
	return insertado;

	};

bool cargar(tListaCorreos & correos, const string & nombre){
	ifstream read;
	tCorreo aux;
	read.open(nombre);
	bool toreturn = true;
	int i = 0;
	if (read.is_open() ){
			
			iniciar(correos);
			while (	cargar (correos.arrayCorreos[i], read) && i < MAX_CORREOS ){
				correos.contador++;
				i++;
			}
			if (read.fail() ){
			
				toreturn = false;
			}
		
	}

	read.close();

return toreturn;
}

bool buscar(const tListaCorreos & correos, const string & idMail, int & pos){/* Dado un identificador de correo y la lista, devuelve, si
	dicho identificador existe en la lista, su posición y el valor true, y si no existe en
	la lista, la posición que le correspondería y el valor false.*/

	bool encontrado = false;
	int ini = 0;
	int fin = correos.contador-1;
	int mitad;

	while(ini <= fin && encontrado == false){
		mitad = (ini+fin)/2;
		
		if(idMail < correos.arrayCorreos[mitad].idMail){
			fin = mitad-1;
		}

		else if(idMail > correos.arrayCorreos[mitad].idMail){
			ini = mitad+1;
		}

		else{
			encontrado = true;
		}

	}

		if(encontrado == true){
			pos = mitad;
			
		}

		else{
			pos = ini;
			
		}

return encontrado;
}

bool eliminar(tListaCorreos & correos, const string & idMail){/*Dado un identificador de correo y la lista, elimina de la lista el correo
	correspondiente al identificador (¡sin dejar huecos!). Devuelve false si el
	correo no existía, en otro caso devuelve true.*/
	bool toreturn;
			int pos;
			if(buscar (correos, idMail, pos)){ // si está...
					for(int i = pos; pos < correos.contador-1;i++){
						correos.arrayCorreos[i] = correos.arrayCorreos[i+1];
					}
				correos.contador--;
				toreturn =  true;
				
			}
			else{ // si no existe...

				toreturn =  false;
			}
			return toreturn;
}

