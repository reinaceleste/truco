/**
******************************************************
*  \file main.c
*  \brief TP Obligatorio
* \details Cliente
* Uso del make
* - Compilar con make new o make cliente
* - Ejecutar o compilar y ejecutar en un paso com make run o simplemente make (luego de la ejecución se borrarán los archivos objeto y el ejecutable)
* - Generar y abrir página web con documento Doxygen con make html
* - Borrar web con make no_html
* - Agregar archivos .c, Makefile y Doxyfile al repositorio con make git
* \author Federico Ariel Marinzalda
* \version 1.4
* \date 5/1/2017
*
*
*******************************************************/


#include "conexion.h"
/**
******************************************************
*  \fn int main(void)
*  \brief Función principal del cliente
* \details Puede elegir entre varias opciones (registrarse, iniciar sesión, jugar, ver puntuaciones, cerrar sesión)
* \author Federico Ariel Marinzalda
* \version 1.4
* \date 5/1/2017
*
*******************************************************/


int main(void){
    
    int sockfd_cliente;
    int nBytes,opjug,finicio=SI;
    char nombre[MAX_NOM];
    char respuesta[MAX_REP];
    char op='E',opvalida,opflor;
    char estado=NADA,ingreso=NO;
    struct usuario us;
	    
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
                    if(opvalida==SI || finicio==SI)
                    {
                        printf("Respuesta del servidor: %s\r\n",respuesta);
                    }
                    if(finicio==SI)
                    {
                        finicio=NO;
                    }
                    scanf(" %c",&op);
                    switch(op)
                    {
                        case 'R':
                            if(estado==NADA)
                            {
                                opvalida=SI;
                            }
                            else
                            {
                                opvalida=NO;
                            }
                            break;
                        case 'I':
                            if(estado==NADA)
                            {
                                opvalida=SI;
                            }
                            else
                            {
                                opvalida=NO;
                            }
                            break;
                        case 'P':
                            if(estado!=VIENDOPUNTUACIONES)
                            {
                                opvalida=SI;
                            }
                            else
                            {
                                opvalida=NO;
                            }
                            break;
                        case 'N':
                            if(estado==VIENDOPUNTUACIONES)
                            {
                                opvalida=SI;
                            }
                            else
                            {
                                opvalida=NO;
                            }
                            break;
                        case 'S':
                            opvalida=SI;
                            break;
                        case 'T':
                            if(estado==ENSESION)
                            {
                                opvalida=SI;
                            }
                            else
                            {
                                opvalida=NO;
                            }
                            break;
                        case 'D':
                            if(estado==ENLOG)
                            {
                                opvalida=SI;
                            }
                            else
                            {
                                opvalida=NO;
                            }
                            break;
                        default:
                            opvalida=NO;
                            break;
                    }
                    if(opvalida==SI)
                    {
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
                                    if(myStrncmp(respuesta,"Exito",5))
                                    {
                                        printf("Respuesta del servidor: %s\r\n",respuesta);
                                    }
                                }
                                /*if(myStrncmp(respuesta,"Exito",5))
                                {
                                    break;
                                }*/
                                break;
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
                                if(myStrncmp(respuesta,"Ingrese su contra",my_strlen("Ingrese su contra")))
                                {
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
                                    if(myStrncmp(respuesta,"Exito",5))
                                    {
                                        printf("Respuesta del servidor: %s\r\n",respuesta);
                                    }
                                }
                                if(myStrncmp(respuesta,"Exito",5))
                                {
                                    break;
                                }
                                estado=ENSESION;
                                ingreso=SI;
                                break;
                            case 'P':
                                //printf("Respuesta del servidor: %s\r\n",respuesta);
                                estado=VIENDOPUNTUACIONES;
                                break;
                            case 'N':
                                //printf("Respuesta del servidor: %s\r\n",respuesta);
                                if(ingreso==SI)
                                {
                                    estado=ENSESION;
                                }
                                else
                                {
                                    estado=NADA;
                                }
                                break;
                            case 'T':
                                printf("Respuesta del servidor: %s\r\n",respuesta);
                                scanf(" %c",&opflor);
                                send(sockfd_cliente,&opflor,sizeof(opflor), 0);
                                nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
                                if(nBytes<=0){            									
                                    puts("Error en recv\r\n");
                                    close(sockfd_cliente);
                                    return(-1);
                                }
                                while(!(opflor=='S' || opflor=='N' || opflor=='0'))
                                {
                                    printf("Respuesta del servidor: %s\r\n",respuesta);
                                    scanf(" %c",&opflor);
                                    send(sockfd_cliente,&opflor,sizeof(opflor), 0);
                                    nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
                                    if(nBytes<=0){            									
                                        puts("Error en recv\r\n");
                                        close(sockfd_cliente);
                                        return(-1);
                                    }
                                }
                                if(opflor=='0')
                                {
                                    break;
                                }
                                printf("Respuesta del servidor: %s\r\n",respuesta);
                                scanf("%d",&opjug);
                                send(sockfd_cliente,&opjug,sizeof(opjug), 0);
                                nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
                                if(nBytes<=0){            									
                                    puts("Error en recv\r\n");
                                    close(sockfd_cliente);
                                    return(-1);
                                }
                                while(opjug>3)
                                {
                                    printf("Respuesta del servidor: %s\r\n",respuesta);
                                    scanf("%d",&opjug);
                                    send(sockfd_cliente,&opjug,sizeof(opjug), 0);
                                    nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
                                    if(nBytes<=0){            									
                                        puts("Error en recv\r\n");
                                        close(sockfd_cliente);
                                        return(-1);
                                    }
                                }
                                if(opjug==0)
                                {
                                    break;
                                }
                                estado=ENLOG;
                                break;
                            case 'D':
                                estado=ENSESION;
                                break;
                        }
                    }
                    }
                    else
                    {
                        printf("Opción no válida\n");
                    }
                }
                nBytes = recv(sockfd_cliente,respuesta,MAX_REP,0);
		close(sockfd_cliente);
		puts("Cliente desconectado del servidor.\r\n");
	}
	return(0);
}
