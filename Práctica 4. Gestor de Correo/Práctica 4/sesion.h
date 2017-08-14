#ifndef SESION_H
#define SESION_H

#include <iostream>
#include <string>
#include <iomanip>
#include "gestor.h"
#include "usuario.h"

typedef struct {
	tGestor * puntGestor;
	tUsuario * puntUsuario;
}tSesion;

typedef tCorreo * puntCorreos[MAX_CORREOS];

typedef struct{
	puntCorreos arrayCorreos;
	int contador;
}tPuntCorreos; // creados porque en el email que nos mandaste nos pedías un 'array de punteros a tCorreo' para implementar la lectura rápida de correos;

bool iniciarSesion(tSesion & sesión, tGestor* gestor, tUsuario* usuario);/* Inicia la sesión y muestra la pantalla del menú principal de la
	
	sesión.	*/
void leerCorreo(tSesion & sesión);/* Solicita el correo que el usuario
	quiere leer (será el número con el que el correo es mostrado por pantalla en la
	bandeja correspondiente), valida que existe y si es así, lo marca como correo
	leído. A continuación, busca el correo en la lista de correos y si lo encuentra
	muestra en la pantalla el menú de lectura del correo (aparece el correo y las
	opciones: contestar,…).*/
void enviarCorreo(tSesion & sesión);/* Solicita los datos del nuevo

	correo (destinatario, asunto, cuerpo, …) y lo envía a través del gestor.*/
void borrarCorreo(tSesion & sesión);/* Solicita el correo que el usuario
	quiere borrar (será el número con el que el correo es mostrado por pantalla en la
	bandeja correspondiente), valida que existe y si es así, indica al gestor que lo
	borre.*/
void lecturaRapida(tSesion & sesión);/* Este subprograma implementa
	la lectura rápida de correos sin leer. El resultado es que muestra en una pantalla
	todos los correos sin leer (de la bandeja activa) ordenados por asunto
	(ignorando todos los “Re: ”) y por fecha. Al finalizar su ejecución los correos sin
	leer quedarán marcados como leídos.*/
void ordenarSeleccion(tPuntCorreos &correos, int longitud);
string quitaRes(const tCorreo & noLeido);

int menuBandeja(const tSesion & sesion);

void Bandeja(const tSesion & sesion);
string ignorarREyFW (tCorreo &correo);
#endif