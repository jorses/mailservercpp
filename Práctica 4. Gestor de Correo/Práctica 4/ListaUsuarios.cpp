#include "usuario.h"
#include "ListaUsuarios.h"

bool cargar(tListaUsuarios & usuarios, const string & nombre){
//Carga la lista de usuarios desde el fichero de usuarios nombre (ver ejemplo de
// sección 1.3).

	//Esta función va llamando a las de cargar de las otras para ir cargando todo.

	ifstream archivo;
	bool cargado, cargado2;
	tUsuario usuario;
	int i = 0;

	archivo.open(nombre);


	if(archivo.is_open()){
		cargado = true;
		cargado2 = true;//Pasará a ser false cuando sea false el cargar de usuario.cpp, y éste lo será cuando lea XXX (centinela)
		iniciar(usuarios);
		while(cargado2 == true && i < MAX_ELEMS){
			cargado2 = cargar(usuarios.datos[i], archivo);
			if(cargado2){
				usuarios.contador++;
			}
			i++;
		}

	}

	else{
		cargado = false;
	}

	archivo.close();

return cargado;
}

void guardar(const tListaUsuarios & usuarios, const string & nombre){
//Guarda de la lista de usuarios en el fichero de usuarios nombre.

	int i;
	ofstream archivo;

	archivo.open(nombre);

	if(archivo.is_open()){

		for(i = 0; i < usuarios.contador; i++){

			guardar(usuarios.datos[i], archivo);

		}

		archivo << "XXX";

	}

	archivo.close();

}

bool insertar(tListaUsuarios & usuarios, const tUsuario & usuario){
/*Añade un usuario en la posición de la lista que le corresponde, si
hay sitio para ello. Además devuelve un booleano indicando si la operación
tuvo éxito o no.*/
	
	bool insertado= false;
	
	int posicion;
	bool buscado = false;
	int i;

	if(!llena(usuarios)){
		
		buscado = buscar(usuarios, usuario.nombre, posicion); //Me devuelve la posición en la que tengo que poner al usuario.

		if(buscado == false){

			for(i = usuarios.contador; posicion < i; i--){
				usuarios.datos[i] = usuarios.datos[i-1];
			}

			usuarios.datos[posicion] = usuario;
			
			usuarios.contador++;
			insertado = true;
		}

	}
	
return insertado;
}


bool buscar(const tListaUsuarios & usuarios, const string & idUser, int & posicion){
/*Dado un identificador de usuario y la lista,
devuelve, si dicho identificador existe en la lista, su posición y el valor true, y
si no existe en la lista, la posición que le correspondería y el valor false.*/

	//Búsqueda binaria.

	bool encontrado = false;
	int ini = 0, fin = usuarios.contador-1, mitad;

	while(ini <= fin && encontrado == false){
		mitad = (ini+fin)/2;

		if(idUser < usuarios.datos[mitad].nombre){
			fin = mitad-1;
		}
		else if(usuarios.datos[mitad].nombre < idUser){
			ini = mitad+1;
		}
		else{
			encontrado = true;
		}

	}

	if(encontrado == true){
		posicion = mitad;
	}
	else{
		posicion = ini;
	}

return encontrado;
}