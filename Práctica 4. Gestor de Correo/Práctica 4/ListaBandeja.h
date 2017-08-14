#ifndef LISTABANDEJA_H
#define LISTABANDEJA_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_ELEMS = 100;

typedef struct{
	string id;
	bool leido;
}tElemBandeja;

typedef tElemBandeja tListabandeja[MAX_ELEMS];

typedef struct{
	tListabandeja lista;
	int contador;
}tListaBandeja;


	//Recibidos y enviados son dos variables de tipo ListaBandeja --> Son otros dos arrays que cogen los datos de otra variable de listaBandeja

inline void inicializar(tListaBandeja & listElems){
 listElems.contador = 0;
}

inline bool llena(const tListaBandeja & listElems){
return listElems.contador == MAX_ELEMS; 
}

inline int longitud(const tListaBandeja & listElems){
return listElems.contador; 
}


void guardar(const tListaBandeja & listElems, ofstream & archivo);
//Dado un flujo de archivo de salida (ya abierto), guarda los datos de
//los elementos de la lista(ver ejemplo de la sección 1.3)

void cargar(tListaBandeja & listElems, ifstream & archivo);
//Dado un flujo de archivo de entrada (ya abierto), lee los datos que corresponden a 
//una lista y la devuelve.

bool insertar(tListaBandeja & listElems, const tElemBandeja & elem);
//Dado un elemento lo inserta al final de la lista. Si la lista está llena
//devuelve false, en otro caso devuelve true. Este subprograma se ejecutará
//cuando un usuario envíe un correo, ya que se insertará un nuevo elemento en
//su bandeja de salida, y también en las listas de las bandejas de entrada de cada
//uno de los destinatarios del correo.

int buscar(const tListaBandeja & listElems, const string & idMail);
//Dado un identificador de correo y la lista, devuelve, si dicho
//identificador existe en la lista, su posición, y si no existe devuelve -1.

bool eliminar(tListaBandeja & listElems, const string & idMail);
/*Dado un identificador de correo, lo busca en la lista y si lo encuentra lo elimina
de la lista (¡sin dejar huecos!). Si no lo encuentra, devuelve false, en otro caso
devuelve true. Este subprograma representa la acción de borrar un correo de
una de sus bandejas del usuario. OJO: esta operación sólo supone que el
elemento se elimina de la bandeja, pero el correo puede seguir existiendo en la
lista de correos del gestor.*/

bool correoLeido(tListaBandeja & listElems, const string & idMail);
/*Dado un identificador de correo, lo busca en la lista y pone el
indicador de leído a true. La operación devuelve un booleano indicando si se
encontró o no el identificador.*/
#endif