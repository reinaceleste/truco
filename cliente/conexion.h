/**
 *	\file conexion.h
 *	\brief Prototipos de funciones conexion.
 *	\brief Defines y prototipos de las funciones sobre conexion.
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


//-------------
//-- Defines --
//-------------

#define MAX_BUFFER 1024
#define MAX_IP 14
#define MAX_CONEXIONES 10
#define PATH_CONFIG "config.txt"
#define MAX_USER 32
#define MAX_PASS 24

//-----------------
//-- Estructuras --
//-----------------

struct datos{  
     char ip[MAX_IP];
     int  puerto;
};
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

#endif
