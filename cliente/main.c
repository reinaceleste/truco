/**
*	\file main.c
*	\fn int main(void)
*	\brief Función principal del cliente
 *	\author Federico Ariel Marinzalda
 *	\date 5/1/2017
*	\version 1.4
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
                                printf("Respuesta del servidor: %s\r\n",respuesta);
                                scanf("%s",us.user);
                                send(sockfd_cliente, us.user, strlen(us.user)+1, 0);
                                nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
                                if(nBytes<=0){            									
                                    puts("Error en recv\r\n");
                                    close(sockfd_cliente);
                                    return(-1);
                                }
                                printf("Respuesta del servidor: %s\r\n",respuesta);
                                while(myStrncmp(respuesta,"Exito",5))
                                {
                                scanf("%s",us.password);
                                send(sockfd_cliente, us.password, strlen(us.password)+1, 0);
                                nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
                                if(nBytes<=0){            									
                                    puts("Error en recv\r\n");
                                    close(sockfd_cliente);
                                    return(-1);
                                }
                                printf("Respuesta del servidor: %s\r\n",respuesta);
                                }
                        }
                    }
                }
                nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
		close(sockfd_cliente);
		puts("Cliente desconectado del servidor.\r\n");
	}
	return(0);
}
