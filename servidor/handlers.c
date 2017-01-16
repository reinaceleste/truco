#include "conexion.h"

extern int listener;
extern int cliente;
extern NODO *h;
extern FILE *fp;

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

void sigchldhandler(int signal)
{
    close(cliente);
    wait(NULL);
}