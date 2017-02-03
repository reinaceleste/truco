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
#include <signal.h>


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
#define ERR_INSES -1
#define PASS_OK 10
#define REVISANDO 30
#define ERR_NOM -1
#define ERR_LONGNOM -2
#define ERR_FILE 99
#define ERR_PUNT 5
#define ERR_LOG 8
#define FILEOK 0
#define NULLCHAR '\0'
#define SOLOBUSCAR 0
#define BUSCARAGREGAR 1
#define BUSCARBORRAR 2
#define BUSCARMODIFICAR 3
#define BUSCARPASS 4
#define ENCONTRO 1
#define NOENCONTRO 0
#define SI 1
#define NO 0
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
#define LOGS1 "trucoS1"
#define LOGN1 "trucoN1"
#define LOGS2 "trucoS2"
#define LOGN2 "trucoN2"
#define LOGS3 "trucoS3"
#define LOGN3 "trucoN3"
#define MAX_DATOS 1000

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
 * \details Nombre de usuario, contraseña (ambos son vectores de chars) y puntos acumulados (entero)
* \author Federico Marinzalda
* \version 1.1
* \date 22/12/2016
 */
/**
******************************************************
*  \typedef struct usuario DATO
*  \brief Typedef que sirve como alias de la estructura creada usuario
* \details Se crea el alias ya que el mismo se utiliza en varios prototipos de funciones de manejo de archivos y listas
* \author Federico Ariel Marinzalda
* \version 1.1
* \date 22/12/2016
*
*
*******************************************************/
typedef struct usuario{
    char user[MAX_USER+1];
    char password[MAX_PASS+1];
    int puntos;
} DATO;

/**
 *	\struct nodo
 *	\brief Creación del nodo para ser utilizado en listas
 * \details Dato (Estructura usuario) y dirección del siguiente nodo de la lista (Puntero a la estructura nodo)
* \author Federico Marinzalda
* \version 1.1
* \date 22/12/2016
 */
/**
******************************************************
*  \typedef struct usuario NODO
*  \brief Typedef que sirve como alias de la estructura creada nodo
* \details Se crea el alias ya que el mismo se utiliza en varios prototipos de funciones de manejo de archivos y listas
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 22/12/2016
*
*
*******************************************************/
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
int ingresolog(DATO *usu,char opflor,int opjug);
void salidalog(DATO *usu);
int puntuaciones(DATO *usu,char *respuesta);
void AgregarNodoAlFinal (NODO **h,NODO *aux,NODO **last);
int BuscarNodo (NODO **h,NODO *aux,NODO **last,int instruccion);
void BorrarLista (NODO **p);
int my_strlen (char* palabra);
void Parsear(DATO d,UNION *u);
void CambiarDato (DATO *d,int op);
int myStrncpy (char* dest,char* origen,int n);
int mystructcmp (const char *s1,const char *s2,size_t n);
int myStrncmp (const char* s1,const char* s2,int n);
void mydectostr (int num,char *buf);
void stringReverse (char* palabra);
int CargarArchivo (char *ruta,NODO **h,NODO **last);
int GuardarLista (NODO **p,char *ruta);
void OrdenarLista (NODO *h);
void siginthandler(int signal);
void sigchldhandler(int signal);

#endif
