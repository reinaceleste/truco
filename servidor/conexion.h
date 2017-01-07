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
#include <sys/wait.h>


//-------------
//-- Defines --
//-------------

#define MAX_BUFFER 1024
#define MAX_IP 14
#define MAX_CONEXIONES 10
#define PATH_CONFIG "config.txt"
#define PATH_REG "usuariosregistrados"
#define PATH_INSES "ipensesion"
#define MAX_USER 40
#define MAX_PASS 24
#define ERR_MAYUS -3
#define ERR_MINUS -4
#define ERR_NUM -1
#define ERR_8CAR -2
#define ERR_16CAR -5
#define ERR_PASS -1
#define PASS_OK 10
#define REVISANDO 30
#define ERR_NOM -1
#define ERR_LONGNOM -2
#define ERR_FILE 99
#define FILEOK 0
#define NULLCHAR '\0'
#define SOLOBUSCAR 0
#define BUSCARAGREGAR 1
#define BUSCARBORRAR 2
#define BUSCARMODIFICAR 3
#define BUSCARPASS 4
#define ENCONTRO 1
#define NOENCONTRO 0
#define DATO1(x) (x.user)
#define DATO2(x) (x.password)
#define DATO3(x) (x.puntos)
#define DATOS(x) "%s %s %d\n",DATO1(x),DATO2(x),DATO3(x)
#define PRINTDATO(x) printf(DATOS(x))
#define PEDIRDATO1(x) printf("Usuario: ");scanf("%s",DATO1(x))
#define PEDIRDATO2(x) printf("Contraseña: ");scanf("%s",DATO2(x))
#define DT1 "Nombre de usuario"
#define DT2 "Contraseña"
#define PREGUNTA3 printf("¿Dato a cambiar?\n1: %s\n2: %s\n0: Salir\nOpción: ",DT1,DT2);
#define ENCABEZADO "Usuario\tContraseña\tPuntos\t\n"
#define PRINTENCABEZADO printf(ENCABEZADO)


//-----------------
//-- Estructuras --
//-----------------

struct datos{
     
     char ip[MAX_IP];
     int  puerto;
};

typedef struct usuario{
    char user[MAX_USER+1];
    char password[MAX_PASS+1];
    int puntos;
} DATO;

typedef struct nodo
{
    DATO dato;
    struct nodo* sgte;
} NODO;
typedef union uni
{
    DATO datouni;
    char parseo[sizeof(DATO)];
} UNION;
     
//-----------------
//-- Prototipes --
//-----------------

void datos_server(struct datos* configuracion);
int login(void);
int recibir(int socket,char *buffer,int tamano,fd_set *master);
void BuscarAgregarNodoAlFinal (NODO **h,NODO *aux,NODO **last);
int comprobarnombre(char* nom);
int comprobarpass(DATO *usu);
int validarpass(char *pass);
int registrar(DATO *usu);
int iniciarsesion(DATO *usu);
void cerrarsesion(DATO *usu);
void AgregarNodoAlFinal (NODO **h,NODO *aux,NODO **last);
int BuscarNodo (NODO **h,NODO *aux,NODO **last,int instruccion);
void BorrarLista (NODO **p);
int my_strlen (char* palabra);
void Parsear(DATO d,UNION *u);
void CambiarDato (DATO *d,int op);
int myStrncpy (char* dest,char* origen,int n);
int mystructcmp (const char *s1,const char *s2,size_t n);
int CargarArchivo (char *ruta,NODO **h,NODO **last);
int GuardarLista (NODO **p,char *ruta);

#endif
