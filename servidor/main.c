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

#define MAX_DATOS 600

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
    pid_t pid;
    char op='E';
    int nBytes;
     
          
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
	    if((listen(listener,MAX_CONEXIONES)) == -1){
		printf("Error en listen");
		return(-1);
    }
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
                                            strcpy(respuesta,"Conexion aceptada");
                                            while(op!='S')
                                            {
                                                strcat(respuesta,"\n\nR: Registrarse\nI: Iniciar sesion\nT: Jugar TrucoC\nS: Cerrar sesion\n\n");
                                                send(cliente, &respuesta, sizeof(respuesta), 0);
                                                nBytes = recv(cliente,&op,sizeof(op),0);   
                                                if(nBytes<=0){            									
                                                    puts("Error en recv\r\n");
                                                    close(cliente);
                                                }
                                                else
                                                {
                                                    switch(op)
                                                    {
                                                        case 'R':
                                                            strcpy(respuesta,"Cliente quiere registrarse\n");
                                                            break;
                                                        case 'I':
                                                            strcpy(respuesta,"Cliente quiere iniciar sesion\n");
                                                            break;
                                                        case 'T':
                                                            strcpy(respuesta,"Cliente quiere jugar\n");
                                                            break;
                                                        case 'S':
                                                            strcpy(respuesta,"Cliente cierra sesion\n");
                                                            break;
                                                        default:
                                                            break;
                                                    }
                                                }
                                            }
                                            strcpy(respuesta,"Desconexion del cliente ");
                                            strcat(respuesta,inet_ntoa((struct in_addr)datosCliente.sin_addr));
                                            strcat(respuesta,"\n");
                                            send(cliente, &respuesta, sizeof(respuesta), 0);
                                            
                                        }
				//}
        //}
			//}
     	}	    
     }
	return(0);
}



