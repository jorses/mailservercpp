#ifndef GESTOR_H
#define GESTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <Windows.h>
#include "ListaUsuarios.h"
#include "listaCorreo.h"
#include "correo.h"
#include "usuario.h"


using namespace std;

//const string archivoCorreos = "fdimail_correos.txt";
//const string archivoUsuarios = "fdimail_usuarios.txt";
const string dominio = "fdimail";

typedef struct {

	string dominio;

	tListaCorreos listaCorreos;

	tListaUsuarios listaUsuarios;

} tGestor;

inline void clearConsole() {
	system("cls");
}

inline void cpConsoleOut (int cp) {
	SetConsoleOutputCP(cp);
}
bool arrancar (tGestor & gestor, const string & dominio);
void apagar (const tGestor & gestor);
tUsuario * registraUsuario (tGestor & gestor);
tUsuario * crearCuenta (tGestor & gestor);
void enviarCorreo ( tGestor & gestor, tUsuario & usuario, const tCorreo & correo);
void eliminarCorreo (tGestor & gestor, tUsuario & usuario, const string & idMail);



#endif