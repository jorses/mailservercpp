#ifndef CORREO_H
#define CORREO_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstring>

using namespace std;
const int EMISOR_CAP = 25;
const int ASUNTO_CAP = 23;
typedef time_t tFecha;
typedef struct {

	string idMail;
	tFecha fecha;
	string Emisor;
	string Destinatario;
	string Asunto;
	string Cuerpo;
	int numAccs;

} tCorreo;

void correoForward (const tCorreo & correoOriginal, tCorreo & correo, const string & emisor);
string leerCuerpo();
string cargarCuerpo(ifstream & archivo);
void correoNuevo (tCorreo & correo, const string & emisor);
void correoContestacion (const tCorreo & correoOriginal, tCorreo & correo, const string & emisor);
void guardar ( const tCorreo & correo, ofstream & archivo);
bool cargar (tCorreo & correo, ifstream & archivo);
int disminuirNumAccs( tCorreo & correo);
string to_string (const tCorreo & correo);
string cabecera (const tCorreo & correo);
string mostrarFecha(tFecha fecha);
string mostrarSoloDia(tFecha fecha);
string truncAsunto( string asunto);
string truncEmisor(string emisor);

#endif