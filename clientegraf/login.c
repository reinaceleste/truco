/**
*	\file login.c
*	\brief Archivo con la función de logueo al servidor
* \version 1.0
* \date 21/11/2016
*/

//--------------
//-- Includes --
//--------------

#include "conexion.h"
/**
*	\fn int login(void)
*	\brief Función de logueo al servidor
* \version 1.0
* \date 21/11/2016 
* \param[out] sockfd_cliente Socket del cliente que se conecta (toma valor -1 en caso de error)
*	\return Un número entero
*/

int login(void){
     
	int sockfd_cliente;                    
    struct sockaddr_in datosServer;     
    struct datos configuracion;                       
        
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

    

