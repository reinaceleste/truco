/**
*	\file datos_server.c
*	\fn void datos_server(struct datos*)
*	\brief Función que carga del archivo config.txt los datos de ip y puerto del servidor.
*	\param struct datos* puntero a los datos del servidor.
*/

//--------------
//-- Includes --
//--------------

#include "conexion.h"

//---------------
//--  Defines  --
//---------------

void datos_server(struct datos* configuracion){
     
     FILE *fp;
     
     fp = fopen(PATH_CONFIG,"r");                
     if(fp==NULL){                               
	    printf("%s",strerror(errno));	        
     }                                
     while(!feof(fp)){                                                        
	    fscanf(fp,"ip: %s\r\npuerto: %d\r\n",configuracion->ip, &configuracion->puerto); 
     }
     fclose(fp);                                 
}
