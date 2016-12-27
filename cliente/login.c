/**
*	\file login.c
*	\fn int login(void)
*	\brief Función de logueo al servidor
*	\return Retorna el socket si se conecto o errores.
*/

//--------------
//-- Includes --
//--------------

#include "conexion.h"


int login(void){
     
	int sockfd_cliente;                    
    struct sockaddr_in datosServer;     
    struct datos configuracion;      
    int nBytes;                           
        
    sockfd_cliente = socket(AF_INET,SOCK_STREAM,0);  
    if(sockfd_cliente == -1){
	    printf("Error al pedir un socket\n");
	    return(0);
    }
     
    //Cargo IP y Puerto desde el archivo configuración del sistema.
    datos_server(&configuracion);
    printf("Datos del server\nip:\"%s\"\npuerto:\"%d\"\n",configuracion.ip, configuracion.puerto);
     
    //Lleno la estructura.
    datosServer.sin_family = AF_INET;                           //Ordenación de bytes de la máquina
    datosServer.sin_addr.s_addr = inet_addr(configuracion.ip);  //Cargo la IP del servidor.
    datosServer.sin_port = htons (configuracion.puerto);        //Cargo el puerto del servidor.
    memset(datosServer.sin_zero,0,8);                           //Pongo en 0 el resto de la estructura.
     
    //Conecto al servidor & Compruebo errores.
    if((connect(sockfd_cliente, (struct sockaddr *) &datosServer, sizeof (struct sockaddr))) == -1){  
	    printf("Error en conecct");
		return(-1);
    }
	
	printf("Cliente conectado exitosamente\n");
	return (sockfd_cliente);
}

    

