#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H
/*#include <fstream>
#include <iostream>
#include <string>*/
//#include "sesion.h"
//#include "gestor.h"
#include "usuario.h"

using namespace std;

//const int MAX_ELEMS = 100;

typedef tUsuario tUsuarios[MAX_ELEMS];

typedef struct{
	tUsuarios datos;
	int contador;
}tListaUsuarios;

inline void iniciar(tListaUsuarios & usuarios){
	usuarios.contador = 0;
}

inline bool llena(const tListaUsuarios & usuarios){
	return usuarios.contador == MAX_ELEMS; 
}

inline int longitud(const tListaUsuarios & usuarios){
	return usuarios.contador; 
}
bool cargar(tListaUsuarios & usuarios, const string & nombre);
//Carga la lista de usuarios desde el fichero de usuarios nombre (ver ejemplo de
// sección 1.3).

void guardar(const tListaUsuarios & usuarios, const string & nombre);
//Guarda de la lista de usuarios en el fichero de usuarios nombre.

bool insertar(tListaUsuarios & usuarios, const tUsuario & usuario);
/*Añade un usuario en la posición de la lista que le corresponde, si
hay sitio para ello. Además devuelve un booleano indicando si la operación
tuvo éxito o no.*/

bool buscar(const tListaUsuarios & usuarios, const string & idUser, int & posicion);
/*Dado un identificador de usuario y la lista,
devuelve, si dicho identificador existe en la lista, su posición y el valor true, y
si no existe en la lista, la posición que le correspondería y el valor false.*/
#endif