#ifndef LISTACORREO_H
#define LISTACORREO_H

#include "correo.h"
#include <string>
#include <fstream>
const int MAX_CORREOS = 100;
typedef tCorreo tArrayCorreos[MAX_CORREOS];

typedef struct{
	tArrayCorreos arrayCorreos;
	int contador;

}tListaCorreos;

// FUNCIONES
inline void iniciar(tListaCorreos & correos){
	
	correos.contador= 0; 

}

inline bool llena(const tListaCorreos & correos){
	return correos.contador == MAX_CORREOS; 
}

inline int longitud(const tListaCorreos & correos){
	return correos.contador; 
	}
void guardar(const tListaCorreos & correos, const string & nombre);
// Guarda la lista de correos en el fichero de correos nombre (ver ejemplo de la sección 3.2).
bool cargar(tListaCorreos & correos, const string & nombre);
//Carga de la lista de correos desde el fichero de correos nombre.
bool insertar(tListaCorreos & correos, const tCorreo & correo);/*Dado un correo, si hay espacio en la lista, lo coloca en la posición de la lista que
le corresponda de acuerdo con su identificador y devuelve true. Si no lo ha
podido insertar devuelve false.*/
bool buscar(const tListaCorreos & correos, const string & idMail, int & pos);/* Dado un identificador de correo y la lista, devuelve, si
dicho identificador existe en la lista, su posición y el valor true, y si no existe en
la lista, la posición que le correspondería y el valor false.*/
bool eliminar(tListaCorreos & correos, const string & idMail);
/*Dado un identificador de correo y la lista, elimina de la lista el correo
correspondiente al identificador (¡sin dejar huecos!). Devuelve false si el
correo no existía, en otro caso devuelve true.*/
#endif