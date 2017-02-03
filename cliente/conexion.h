/**
 *	\file conexion.h
 *	\brief Contiene los prototipos de las funciones, las constantes simbólicas, typedefs y estructuras utilizadas en esta parte del TPO
* \author Reina Celeste Chaves y Federico Ariel Marinzalda
* \version 1.2
* \date 4/1/2017
 */
 
#ifndef CONEXION_H
#define CONEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>


//-------------
//-- Defines --
//-------------

#define MAX_BUFFER 1024
#define MAX_IP 14
#define MAX_CONEXIONES 10
#define PATH_CONFIG "config.txt"
#define MAX_USER 40
#define MAX_PASS 24
#define NULLCHAR '\0'
#define NADA 0
#define ENSESION 1
#define VIENDOPUNTUACIONES 2
#define ENLOG 3
#define JUGANDO 4
#define SI 1
#define NO 0
#define MAX_NOM 50
#define MAX_REP 1000

//-----------------
//-- Estructuras --
//-----------------

/**
 *	\struct datos
 *	\brief Datos del servidor
 * \details Dirección IP (vector de chars) y Puerto (entero)
* \author Reina Celeste Chaves
* \version 1.0
* \date 21/11/2016
 */
struct datos{  
     char ip[MAX_IP];
     int  puerto;
};
/**
 *	\struct usuario
 *	\brief Datos del usuario
 * \details Nombre de usuario y contraseña (ambos son vectores de chars)
* \author Federico Marinzalda
* \version 1.1
* \date 22/12/2016
 */
struct usuario{
    char user[MAX_USER+1];
    char password[MAX_PASS+1];
};
     
//-----------------
//-- Prototipes --
//-----------------

void datos_server(struct datos* configuracion);
int login(void);
char *gets_s(char *s, int size);
int myStrncmp (const char* s1,const char* s2,int n);
int my_strlen (char* palabra);

#endif
