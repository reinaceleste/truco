/**
*	\file datos_server.c
*	\brief Archivo con función para obtener datos del servidor
* \version 1.0
* \date 21/11/2016
*/

//--------------
//-- Includes --
//--------------

#include "conexion.h"

//---------------
//--  Defines  --
//---------------

/**
*	\fn void datos_server(struct datos*)
*	\brief Función que carga del archivo config.txt los datos de ip y puerto del servidor.
* \author Reina Celeste Chaves
* \version 1.0
* \date 21/11/2016
*	\param[in] configuración puntero a los datos del servidor.
*/
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
