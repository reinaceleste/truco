/**
*	\file handlers.c
*	\brief Archivo con handlers de señales
* \version 1.0
* \date 5/1/2017
*/

#include "conexion.h"

extern int listener;
extern int cliente;
extern NODO *h;
extern FILE *fp;

/**
*	\fn void siginthandler(int signal)
*	\brief Función (handler) que se ejecuta al llegar la señal de interrupción
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 5/1/2017
*	\param[in] signal Número de la señal de interrupción (SIGINT)
*/
void siginthandler(int signal)
{
    close(cliente);
    close(listener);
    if(h!=NULL)
    {
        BorrarLista(&h);
    }
    if(fp!=NULL)
    {
        fclose(fp);
    }
}

/**
*	\fn void sigchldhandler(int signal)
*	\brief Función (handler) que se ejecuta al llegar la señal de muerte de proceso hijo
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 5/1/2017
*	\param[in] signal Número de la señal de muerte de proceso hijo (SIGCHLD)
*/
void sigchldhandler(int signal)
{
    close(cliente);
    wait(NULL);
}