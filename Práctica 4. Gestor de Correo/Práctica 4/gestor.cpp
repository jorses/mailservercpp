#include "gestor.h"
#include "listaCorreo.h"
#include"correo.h"

bool arrancar ( tGestor & gestor, const string & dominio){

	bool output=false;

	string archivoCorreos = dominio + "_correos.txt";

	string archivoUsuarios = dominio + "_usuarios.txt";

	

	if (cargar (gestor.listaCorreos, archivoCorreos) && cargar (gestor.listaUsuarios, archivoUsuarios)){

		output = true;
	}

	return output;
}
 
void apagar (const tGestor & gestor){/*Esta operación apaga el gestor y
	guarda para ello las listas de usuarios y de correos del dominio activo. Los
	nombres de los archivos son los mismos que al arrancar.*/

	string archivoCorreos = gestor.dominio + "_correos.txt";
	string archivoUsuarios = gestor.dominio + "_usuarios.txt";
	guardar (gestor.listaCorreos, archivoCorreos); 

	guardar (gestor.listaUsuarios, archivoUsuarios);
	
}

tUsuario * registraUsuario (tGestor & gestor){

	tUsuario * usuario = nullptr;
	
	string id, contraseña;
	int pos;

	cout << endl << "Introduzca su nombre de Usuario: ";
	
	cin>> id;
	
	cin.sync();
	cin.clear();

	cout << endl <<  "Introduzca su contraseña: ";
	cin >> contraseña;
		
	cin.sync();
	cin.clear();
	if (buscar(gestor.listaUsuarios, id, pos)){

		if (validarContrasenia(gestor.listaUsuarios.datos[pos], contraseña)){

			usuario = &gestor.listaUsuarios.datos[pos];
			usuario->nombre = id;
			usuario->password = contraseña;

		}

		else{ 
			usuario=nullptr;
			cout << "La contraseña introducida no es correcta." << endl;
		}

	}

	else{ 
		usuario=nullptr;
		cout << endl << "El nombre usuario introducido no existe." << endl << endl;
	}


	return usuario;

}

tUsuario * crearCuenta (tGestor & gestor){

	tUsuario * usuario = nullptr;
	tUsuario auxUsuario;
	char charaux;
	string stringaux;
	string id, contraseña;
	bool ok =false;
	int pos;
	cout << endl << "Nombre de usuario: ";
	
	while ( !ok ){
		
		cin >> id;
				
		cin.sync();
		cin.clear();
	
		istringstream valido(id); //tomamos como valido cualquiera que acabe con @fdimail.com
		while (valido >> charaux){
			
			if (charaux == '@'){
				valido >> stringaux;
				
				if(stringaux == dominio+".com"){
					ok = true;
				}
		
		
			}

		}
		if (ok == false){
		
		clearConsole();
		cout << "Usuario erroneo, introduzca un nombre valido(acabado en @fdimail.com)\n";
		
		}
	}
		


		auxUsuario.nombre = id;
		usuario = &auxUsuario;
		
		if(insertar(gestor.listaUsuarios, *usuario)){
			
			if(buscar(gestor.listaUsuarios, auxUsuario.nombre, pos)){
			
			cout << endl << "Contrasenia: ";
			cin >> contraseña;
			
			cin.sync();
			cin.clear();
			iniciar(gestor.listaUsuarios.datos[pos], id, contraseña);
			
			
			usuario =&gestor.listaUsuarios.datos[pos];
			}
			else{
			cout << "Ese nombre de usuario ya esta registrado.\n";
			cout << "Pulse intro para continuar..." << endl;
			cin.get();
			
			usuario=nullptr;
		
		
			}
		}

		else{ 
			
			usuario=nullptr;
		}


	
	
return usuario;
}

void enviarCorreo ( tGestor & gestor, tUsuario & usuario, const tCorreo & correo){
	int pos;
	tElemBandeja correoBandeja;
	bool insertado, insertadoEnviados, insertadoRecibidos;
	correoBandeja.id = correo.idMail;
	correoBandeja.leido = false;

	

	if (!llena(gestor.listaCorreos)){
		

	

		if(buscar(gestor.listaUsuarios, correo.Destinatario, pos)){//Buscamos si el destinatario existe y obtenemos su pos en la lista

			insertadoEnviados = insertar(usuario.listaEnviados, correoBandeja);
			//Insertamos el correo en la bandeja de salida del usuario que nos llega por referencia

			insertadoRecibidos = insertar(gestor.listaUsuarios.datos[pos].listaRecibidos, correoBandeja);
			//Insertamos el correo en la bandeja de entrada del usuario al que se lo hemos enviado
				if(insertadoEnviados == false || insertadoRecibidos == false){

				cout << endl << "El mensaje no pudo ser enviado, pulse intro para continuar..." << endl;
				cin.get();
				

				}
				else{
				insertar(gestor.listaCorreos, correo); 
				
				}
		}

		else{
		cout << "\nEl usuario al que intenta enviar el correo no existe\n";
		cout << "Pulse intro para continuar..." << endl;
		cin.get();
		}

	

	}
	else{
	cout << "\nNo hay sitio para el correo en el gestor\n";
	}
}

void eliminarCorreo (tGestor & gestor, tUsuario & usuario, const string & idMail){
	/*Elimina de la bandeja activa del usuario el elemento
	correspondiente al identificado de correo. Además, disminuye el número de
	usuarios con acceso al correo y en caso de que quede a cero lo elimina de la lista
	de correos del gestor. (OJO: el correo sólo se elimina de la lista de correos del
	gestor en caso de que el número de usuarios con acceso al mismo sea cero).*/
	int posicionId;
	int posicionUser;
	tListaBandeja* bandejaux;
	tListaBandeja auxi;
	if(usuario.recibidos){
		bandejaux = &usuario.listaRecibidos;		
	}
	else{
		bandejaux = &usuario.listaEnviados;			
	}

	if(buscar(gestor.listaUsuarios, usuario.nombre, posicionUser) && buscar(gestor.listaCorreos, idMail, posicionId)){
		cout << endl << "entrabuscar" << endl;
			 
			if (eliminar(*bandejaux, idMail)) {
				cout << endl <<"entraeliminarbandeja" << endl;
			gestor.listaCorreos.arrayCorreos[posicionId].numAccs =disminuirNumAccs(gestor.listaCorreos.arrayCorreos[posicionId]);
			
			}
			
			if (gestor.listaCorreos.arrayCorreos[posicionId].numAccs==0){
			
			eliminar(gestor.listaCorreos, idMail);

			}
	}
}
