/**
* \file conexion.h
* \brief Prototipos de funciones conexion.
* \brief Defines y prototipos de las funciones sobre conexion.
* \author Chaves, Reina Celeste
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

//-----------------
//-- Estructuras --
//-----------------

struct datos{
     
     char ip[MAX_IP];
     int  puerto;
};
     
//-----------------
//-- Prototipes --
//-----------------

void datos_server(struct datos* configuracion);
int login(void);
int recibir(int socket,char *buffer,int tamano,fd_set *master);

#endif
