#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <fstream>
#include <string>
#include "listaBandeja.h"

using namespace std;

typedef struct{
	string nombre;
	string password;
	tListaBandeja listaRecibidos;
	tListaBandeja listaEnviados;
	bool recibidos; //Tenemos que iniciarlo a true nada más empezar 
}tUsuario;

void iniciar(tUsuario & usuario, const string & idUser, const string & contrasenia);
//Recibe un identificador de usuario y una contraseña e inicia el usuario. La bandeja activa inicial es la de entrada.

void guardar(const tUsuario & usuario, ofstream & archivo);
//Dado un flujo de archivo (ya abierto), guarda el usuario en fichero

bool cargar(tUsuario & usuario, ifstream & archivo);
//Dado un flujo de archivo (ya abierto), carga el usuario del fichero.

bool validarContrasenia(const tUsuario & usuario, const string & contrasenia);
//Recibe una contraseña y un usuario y devuelve si la contraseña es correcta o no.

void cambiarBandeja(tUsuario & usuario);
//Cambia la bandeja activa del usuario.

#endif