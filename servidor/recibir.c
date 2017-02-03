

//--------------
//-- Includes --
//--------------

#include "conexion.h"

int recibir(int socket,char *buffer,int tamano,fd_set *master){
     
     int nbytes;                                                //Cantidad de bytes recibidos
     
     nbytes=recv(socket,buffer,tamano,MSG_WAITALL);
     if(nbytes<=0){                                           
	    printf("Error en recv");                               //Marca el error
	    FD_CLR(socket,master);                                //Elimina el sockets del set maestro
	    close(socket);                                       //Desconecto el socket.
	    printf("Se desconecto el socket: %d\n",socket);     //Avisa que se desconecto el socket
	    nbytes = 0;
     }
     return (nbytes);
}
