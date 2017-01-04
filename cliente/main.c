/**
*	\file main.c
*	\fn int main(void)
*	\brief Función principal del cliente
 *	\author Pose, Fernando Ezequiel. (Fernandoepose@gmail.com)
 *	\date 2015.05.05  (última revisión: 2015.05.06)
*	\return Retorna 0
*	\version 1.3.1
*/

//--------------
//-- Includes --
//--------------

#include "conexion.h"

#define MAX_NOM 50
#define MAX_REP 600

int main(void){
    
	int sockfd_cliente;
    int nBytes;
    char nombre[MAX_NOM];
    char respuesta[MAX_REP];
    char op='E';
    struct usuario us;
     
    /*system("clear"); 
     
    printf("*****************************************************\n");
    printf("*										  		    *\n");
    printf("*      .:Trabajo Practico I - Clente/Servidor:.		*\n");
    printf("*					CLIENTE				  			*\n");
    printf("*****************************************************\n");*/
    
     
	/*printf("Ingrese continuar o salir (minusculas) para cerrar la aplicacion: \r\n"); 
	gets_s(nombre,MAX_NOM);
	 
	if(strcmp(nombre,"continuar")){
		puts("\r\nCliente desconectado del servidor.\r\n");
		return(0);
	}*/
	    
	sockfd_cliente = login();

	//nBytes = recv(sockfd_cliente,&respuesta,sizeof(respuesta),0);
        nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
	if(nBytes<=0){            									
		puts("Error en recv\r\n");
                close(sockfd_cliente);
		return(-1);
	}
	else{                                                        
		while(op!='S')
                {
                    printf("Respuesta del servidor: %s\r\n",respuesta);
                    scanf(" %c",&op);
                    send(sockfd_cliente, &op, sizeof(op), 0);
                    //nBytes = recv(sockfd_cliente,&respuesta,sizeof(respuesta),0);
                    nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
                    if(nBytes<=0){            									
                        puts("Error en recv\r\n");
                        close(sockfd_cliente);
                        return(-1);
                    }
                    else{
                        switch(op)
                        {
                            case 'R':
                                /*nBytes = recv(sockfd_cliente,&respuesta,sizeof(respuesta),0);
                                if(nBytes<=0){            									
                                    puts("Error en recv\r\n");
                                    close(sockfd_cliente);
                                    return(-1);
                                }*/
                                printf("Respuesta del servidor: %s\r\n",respuesta);
                                scanf("%s",us.user);
                                send(sockfd_cliente, us.user, strlen(us.user)+1, 0);
                                //nBytes = recv(sockfd_cliente,&respuesta,sizeof(respuesta),0);
                                nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
                                //printf("nBytes = %d\n",nBytes);
                                if(nBytes<=0){            									
                                    puts("Error en recv\r\n");
                                    close(sockfd_cliente);
                                    return(-1);
                                }
                                printf("Respuesta del servidor: %s\r\n",respuesta);
                                scanf("%s",us.password);
                                send(sockfd_cliente, us.password, strlen(us.password)+1, 0);
                                //nBytes = recv(sockfd_cliente,&respuesta,sizeof(respuesta),0);
                                nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
                                if(nBytes<=0){            									
                                    puts("Error en recv\r\n");
                                    close(sockfd_cliente);
                                    return(-1);
                                }
                                //TODO Tengo que comprobar que el servidor me pida ingresar contraseña, luego que me avise que sea válida para confirmarla y vverificar que el servidor aceptó la contraseña TODO
                                printf("Respuesta del servidor: %s\r\n",respuesta);
                        }
                    }
                }
                //recv(sockfd_cliente,&respuesta,sizeof(respuesta),0);
                nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
		close(sockfd_cliente);
		puts("Cliente desconectado del servidor.\r\n");
	}
	return(0);
}
