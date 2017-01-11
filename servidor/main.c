/**
 *	\file main.c
 *	\fn int main(void)
 *	\brief Función principal del servidor.
 *	\author Chaves, Reina Celeste
 *	\return Retorna 0.
 */

//--------------
//-- Includes --
//--------------

#include <signal.h>
#include "conexion.h"

//---------------
//--  Defines  --
//---------------

#define MAX_DATOS 1000

int main(void){
     
	int listener;                      	    //Socket que recibe las conexiones.
    int cliente;                           //cliente que se conecta.
    struct sockaddr_in datosServer;       //Datos del servidor.
    struct sockaddr_in datosCliente;     //Datos del cliente.
    int clienteConectado;               //Flag que indica que el cliente se conecto.
    fd_set master;                     //Conjunto maestro de descriptores de fichero.
    fd_set readset;                   //Conjunto temporal de descriptores de fichero para select()
    int fdmax;                       //Número mayor descriptor de fichero.
    int i;                          //Para el for del select.
    int on = 1;                    //Necesario para setsockopt (setear las opciones del socket).
    socklen_t addrlen;                  //Necesito para el accept.
    struct datos configuracion;  //IP y PUERTO del servidor.
    int nbytes;					//Respuesta del servidor			    
    char respuesta[MAX_DATOS]; //Respuesta del servidor como que el cliente se conecto.
    struct usuario us;
    pid_t pid;
    char op='E';
    int nBytes;
    int check;
    char checkpass[MAX_PASS+1];
    int intentos;
     
          
    /*printf("*****************************************************\n");
    printf("*										  		    *\n");
    printf("*                   .: SERVIDOR :.          		*\n");
    printf("*								  			        *\n");
    printf("*****************************************************\n");*/
     
	//Si recibo una señal señal SIGPIPE la ignóro.
    //signal(SIGPIPE, SIG_IGN);
        
    //Cargo ip y puerto en las variables.
     
    datos_server(&configuracion);
     
    //Creo el socket que escucha las conexiones.
     
    listener = socket(AF_INET,SOCK_STREAM,0);// Socket(domain, tipoDeTransmicion, protocol)=>(ipv4, stream, defaultForDomain)
    if(listener == -1){
	    printf("Error en listener");
	    return(-1);
     }
     
    //Lleno la estructura con la información del servidor.
     
    printf("Datos del server\nip:\"%s\"\npuerto:\"%d\"\n",configuracion.ip, configuracion.puerto);
    datosServer.sin_family = AF_INET; 
    datosServer.sin_addr.s_addr = inet_addr(configuracion.ip);
    datosServer.sin_port = htons(configuracion.puerto);
    memset(datosServer.sin_zero,0,8);// copia 0 dentro de los primeros 8 caracteres del string
     
    //Si el server se cierra bruscamente queda ocupado el puerto y se debe reiniciar el servidor, con setsockp se soluciona.
     
    // if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR,&on, sizeof(int)) == -1){
	   // 	printf("Error en setsockopt");
	   //  return(-1);
    // } 
    //PUERTO BASE CCEPT DEVUELVE UN SOCKET, (NEW), GENERO EL FORK, PADRE SE QUEDA ESCUCHANDO,
    // PROCESO HIJO SERVER SE COMUNICA CON EL CLIENTE, TRABAJA CON NEW
     
    //Enlazo el socket a la ip:puerto contenida en la estructura datosServer.
     
    if(bind(listener, (struct sockaddr*) &datosServer, sizeof datosServer) == -1){ 
		printf("Error en bind");
	    return(-1);
    }
     
    //Pongo el server a la escucha (enciendo el servidor)
     
    if((listen(listener,MAX_CONEXIONES)) == -1){
		printf("Error en listen");
		return(-1);
    }
     
    //Aviso que el servidor está conectado.
     
    puts("Servidor conectado");
     
    //FD_ZERO(&master);  
    //FD_ZERO(&readset);
     
    //Añado el listener al set maestro.
     
    //FD_SET(listener,&master); //(innecesario)
     
    //Mayor descriptor de fichero como es único es el máximo.
     
    //fdmax = listener;
     
    //Bucle principal.
     
	while(1){              //Bucle principal.
	
		//readset = master;
	    
	    /*if(select(fdmax+1,&readset, NULL, NULL, NULL)== -1){
			printf("Error en select");
			return(-1);
	    }*/
	    
	    //Exploro conexiones existentes en busca de datos que leer.
	    /*if((listen(listener,MAX_CONEXIONES)) == -1){
		printf("Error en listen");
		return(-1);
    }*/
		//for(i = 0; i <= fdmax; i++){
		  
		//	if(FD_ISSET(i,&readset)){
		//		if(i == listener){     //Tengo conexión para aceptar.
					addrlen = sizeof(datosCliente);
					
					cliente = accept(listener, (struct sockaddr*) &datosCliente, &addrlen);  //TODO Hasta acá es el login de parte del cliente.
					if(cliente == -1){ 
						printf("Error en accept");	     
					}
					else
                                        {
					//FD_SET(cliente, &master); //Añado la nueva conexion al conjunto maestro.
					//if(cliente > fdmax){     //actualizo el máximo fichero.
					//	fdmax = cliente;
					//}
					pid=fork();
                                        if(pid)
                                        {
                                            close(cliente);
					printf("La siguiente IP se ha conectado IP: %s\n",inet_ntoa((struct in_addr)datosCliente.sin_addr));
					wait(NULL);
                                        }
                                        else
                                        {
                                            close(listener);
                                            strcpy(respuesta,"Conexion aceptada\n\nR: Registrarse\nI: Iniciar sesion\nT: Jugar TrucoC\nD: Salir del log del juego\nP: Ver puntuaciones\nN: No ver más las puntuaciones\nS: Cerrar sesion\n\n");
                                            send(cliente, respuesta, strlen(respuesta)+1, 0);
                                            nBytes = recv(cliente,&op,sizeof(op),0);  
                                            while(op!='S')
                                            {
                                                if(nBytes<=0){            									
                                                    puts("Error en recv\r\n");
                                                    close(cliente);
                                                    return -1;
                                                }
                                                else
                                                {
                                                    switch(op)
                                                    {
                                                        case 'R':
                                                            strcpy(respuesta,"Ingrese su nombre de usuario (hasta 32 caracteres)\n");
                                                            send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            intentos=1;
                                                            do{
                                                            nBytes = recv(cliente,us.user,MAX_USER+1,0);   
                                                            if(nBytes<=0){            									
                                                                puts("Error en recv\r\n");
                                                                close(cliente);
                                                                return -1;
                                                            }
                                                            check=comprobarnombre(us.user);
                                                            if(check==ERR_NOM)
                                                            {
                                                                strcpy(respuesta,"Nombre de usuario existente. ");
                                                                if(intentos<5)
                                                                {
                                                                    strcat(respuesta,"Ingrese otro\n");
                                                                    send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                }
                                                            }
                                                            else if(check==ERR_LONGNOM)
                                                            {
                                                                strcpy(respuesta,"Nombre muy largo. ");
                                                                if(intentos<5)
                                                                {
                                                                    strcat(respuesta,"Ingrese uno de hasta 32 caracteres\n");
                                                                    send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                }
                                                            }
                                                            else if(check==ERR_FILE)
                                                            {
                                                                strcpy(respuesta,"Error inesperado\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                close(cliente);
                                                                return -1;
                                                            }
                                                            intentos++;
                                                            } while(check && intentos<6);
                                                            if(intentos==6)
                                                            {
                                                                strcat(respuesta,"5 intentos fallidos. Registro incorrecto\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                break;
                                                            }
                                                            strcpy(respuesta,"Ingrese su contraseña (debe ser de entre 8 y 16 caracteres, combinando mayúsculas, minúsculas y números)\n");
                                                            send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            intentos=1;
                                                            do{
                                                            nBytes = recv(cliente,us.password,MAX_PASS+1,0);  
                                                            if(nBytes<=0){            									
                                                                puts("Error en recv\r\n");
                                                                close(cliente);
                                                                return -1;
                                                            }
                                                            check=validarpass(us.password);
                                                            if(check)
                                                            {
                                                                switch(check)
                                                                {
                                                                    case ERR_NUM:
                                                                        strcpy(respuesta,"Su contraseña no posee números. ");
                                                                        break;
                                                                    case ERR_8CAR:
                                                                        strcpy(respuesta,"Su contraseña tiene menos de 8 caracteres. ");
                                                                        break;
                                                                    case ERR_MAYUS:
                                                                        strcpy(respuesta,"Su contraseña no posee mayúsculas. ");
                                                                        break;
                                                                    case ERR_MINUS:
                                                                        strcpy(respuesta,"Su contraseña no posee minúsculas. ");
                                                                        break;
                                                                    case ERR_16CAR:
                                                                        strcpy(respuesta,"Su contraseña tiene más de 16 caracteres. ");
                                                                        break;
                                                                }
                                                                if(intentos<5)
                                                                {
                                                                strcat(respuesta,"Ingrese otra\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                }
                                                            }
                                                            else
                                                            {
                                                                strcpy(respuesta,"Confirmar contraseña\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                nBytes = recv(cliente,checkpass,MAX_PASS+1,0);  
                                                                if(nBytes<=0){            									
                                                                    puts("Error en recv\r\n");
                                                                    close(cliente);
                                                                    return -1;
                                                                }
                                                                if(strcmp(checkpass,us.password))
                                                                {
                                                                    check=1;
                                                                    strcpy(respuesta,"Las contraseñas ingresadas no coinciden\n");
                                                                    if(intentos<5)
                                                                    {
                                                                    strcat(respuesta,"Ingrese su contraseña (debe ser de entre 8 y 16 caracteres, combinando mayúsculas, minúsculas y números)\n");
                                                                    send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                    }
                                                                }
                                                            }
                                                            intentos++;
                                                            } while(check && intentos<6);
                                                            if(intentos==6)
                                                            {
                                                                strcat(respuesta,"5 intentos fallidos. Registro incorrecto\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                break;
                                                            }
                                                            if(registrar(&us))
                                                            {
                                                                strcpy(respuesta,"Error al completar el registro. ");
                                                                strcat(respuesta,"Intente más tarde\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            }
                                                            else
                                                            {
                                                                strcpy(respuesta,"Exito al registrarse\n");
                                                                strcat(respuesta,"Nombre de usuario: ");
                                                                strcat(respuesta,us.user);
                                                                strcat(respuesta,"\nContraseña: ");
                                                                strcat(respuesta,us.password);
                                                                strcat(respuesta,"\n\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            }
                                                            break;
                                                        case 'I':
                                                            strcpy(respuesta,"Ingrese su nombre de usuario\n");
                                                            send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            intentos=1;
                                                            do{
                                                            nBytes = recv(cliente,us.user,MAX_USER+1,0);   
                                                            if(nBytes<=0){            									
                                                                puts("Error en recv\r\n");
                                                                close(cliente);
                                                                return -1;
                                                            }
                                                            check=comprobarnombre(us.user);
                                                            if(check==0)
                                                            {
                                                                strcpy(respuesta,"Nombre de usuario incorrecto. ");
                                                                if(intentos<5)
                                                                {
                                                                    strcat(respuesta,"Ingrese su nombre de usuario\n");
                                                                    send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                }
                                                            }
                                                            else if(check==ERR_FILE)
                                                            {
                                                                strcpy(respuesta,"Error inesperado\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                close(cliente);
                                                                return -1;
                                                            }
                                                            intentos++;
                                                            } while(check!=ERR_NOM && intentos<6);
                                                            if(intentos==6)
                                                            {
                                                                strcpy(respuesta,"5 intentos fallidos. Inicio de sesión interrumpida\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                break;
                                                            }
                                                            intentos=1;
                                                            strcpy(respuesta,"Ingrese su contraseña\n");
                                                            send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            do{
                                                            nBytes = recv(cliente,us.password,MAX_PASS+1,0);  
                                                            if(nBytes<=0){            									
                                                                puts("Error en recv\r\n");
                                                                close(cliente);
                                                                return -1;
                                                            }
                                                            check=comprobarpass(&us);
                                                            if(check==ERR_PASS)
                                                            {
                                                                strcpy(respuesta,"Contraseña incorrecta. ");
                                                                if(intentos<5)
                                                                {
                                                                    strcat(respuesta,"Ingrese su contraseña\n");
                                                                    send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                }
                                                            }
                                                            else if(check==ERR_FILE)
                                                            {
                                                                strcpy(respuesta,"Error inesperado\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                close(cliente);
                                                                return -1;
                                                            }
                                                            intentos++;
                                                            } while(check!=PASS_OK && intentos<6);
                                                            if(intentos==6)
                                                            {
                                                                strcpy(respuesta,"5 intentos fallidos. Inicio de sesión interrumpida\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                break;
                                                            }
                                                            check=iniciarsesion(&us);
                                                            if(check)
                                                            {
                                                                if(check==ERR_INSES)
                                                                {
                                                                    strcpy(respuesta,"Este usuario ya inició sesión\n");
                                                                    send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                }
                                                                else
                                                                {
                                                                    strcpy(respuesta,"Error al iniciar sesion. ");
                                                                    strcat(respuesta,"Intente más tarde\n");
                                                                    send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                }
                                                            }
                                                            else
                                                            {
                                                                strcpy(respuesta,"Exito al iniciar sesión\n");
                                                                strcat(respuesta,"Nombre de usuario: ");
                                                                strcat(respuesta,us.user);
                                                                strcat(respuesta,"\nContraseña: ");
                                                                strcat(respuesta,us.password);
                                                                strcat(respuesta,"\n\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            }
                                                            break;
                                                        case 'T':
                                                            strcpy(respuesta,"Cliente quiere jugar\n");
                                                            send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            break;
                                                        case 'P':
                                                            if(puntuaciones(&us,respuesta)==ERR_PUNT)
                                                            {
                                                                strcpy(respuesta,"Error inesperado\n");
                                                                send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                                close(cliente);
                                                                return -1;
                                                            }
                                                            send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            break;
                                                        case 'N':
                                                            strcpy(respuesta,"Cliente quiere dejar de ver puntuaciones\n");
                                                            send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            break;
                                                        case 'D':
                                                            strcpy(respuesta,"Cliente quiere desconectarse del log\n");
                                                            send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            break;
                                                        case 'S':
                                                            strcpy(respuesta,"Cliente cierra sesion\n");
                                                            send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            break;
                                                        default:
                                                            strcpy(respuesta,"Opción no válida\n");
                                                            send(cliente, respuesta, strlen(respuesta)+1, 0);
                                                            break;
                                                    }
                                                }
                                                nBytes = recv(cliente,&op,sizeof(op),0);
                                            }
                                            cerrarsesion(&us);
                                            strcpy(respuesta,"Desconexion del cliente ");
                                            strcat(respuesta,inet_ntoa((struct in_addr)datosCliente.sin_addr));
                                            strcat(respuesta,"\n");
                                            send(cliente, &respuesta, sizeof(respuesta), 0);
                                            return 0;
                                        }
				//}
        //}
			//}
     	}	    
     }
	return(0);
}



