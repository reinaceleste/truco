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
                                while(myStrncmp(respuesta,"Ingrese su contraseña",my_strlen("Ingrese su contraseña")) && myStrncmp(respuesta,"Nombre de usuario existente. 5",my_strlen("Nombre de usuario existente. 5")) && myStrncmp(respuesta,"Nombre muy largo. 5",my_strlen("Nombre muy largo. 5")))
                                {
                                    fflush(stdin);
                                    scanf("%s",us.user);
                                send(sockfd_cliente, us.user, strlen(us.user)+1, 0);
                                nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
                                if(nBytes<=0){            									
                                    puts("Error en recv\r\n");
                                    close(sockfd_cliente);
                                    return(-1);
                                }
                                printf("Respuesta del servidor: %s\r\n",respuesta);
                                }
                                if(myStrncmp(respuesta,"Ingrese su contraseña",my_strlen("Ingrese su contraseña")))
                                {
                                    break;
                                }
                                while(myStrncmp(respuesta,"Exito",5) && myStrncmp(respuesta,"Su contraseña no posee números. 5",my_strlen("Su contraseña no posee números. 5")) && myStrncmp(respuesta,"Su contraseña tiene menos de 8 caracteres. 5",my_strlen("Su contraseña tiene menos de 8 caracteres. 5")) && myStrncmp(respuesta,"Su contraseña no posee mayúsculas. 5",my_strlen("Su contraseña no posee mayúsculas. 5")) && myStrncmp(respuesta,"Su contraseña no posee minúsculas. 5",my_strlen("Su contraseña no posee minúsculas. 5")) && myStrncmp(respuesta,"Su contraseña tiene más de 16 caracteres. 5",my_strlen("Su contraseña tiene más de 16 caracteres. 5")))
                                {
                                    fflush(stdin);
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
                                if(myStrncmp(respuesta,"Exito",5))
                                {
                                    break;
                                }
                            case 'I':
                                printf("Respuesta del servidor: %s\r\n",respuesta);
                                while(myStrncmp(respuesta,"Ingrese su contra",my_strlen("Ingrese su contra")) && myStrncmp(respuesta,"Nombre de usuario incorrecto. 5",my_strlen("Nombre de usuario incorrecto. 5")))
                                {
                                    fflush(stdin);
                                    scanf("%s",us.user);
                                send(sockfd_cliente, us.user, strlen(us.user)+1, 0);
                                nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
                                if(nBytes<=0){            									
                                    puts("Error en recv\r\n");
                                    close(sockfd_cliente);
                                    return(-1);
                                }
                                printf("Respuesta del servidor: %s\r\n",respuesta);
                                }
                                printf("Salí del while\n");
                                if(myStrncmp(respuesta,"Ingrese su contra",my_strlen("Ingrese su contra")))
                                {
                                    printf("Error\n");
                                    break;
                                }
                                while(myStrncmp(respuesta,"Exito",5) && myStrncmp(respuesta,"Contraseña incorrecta. 5",my_strlen("Contraseña incorrecta. 5")))
                                {
                                    fflush(stdin);
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
                                printf("Salí del while\n");
                                if(myStrncmp(respuesta,"Exito",5))
                                {
                                    printf("Error\n");
                                    break;
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
