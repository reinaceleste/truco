

//--------------
//-- Includes --
//--------------

#include "conexion.h"

char *gets_s(char *s, int size){
     int len;
     
     if (!fgets(s, size, stdin)){
	    if (size > 0)
		   s[0] = '\0';
	    return NULL;
     }
     else{
	    len = strlen(s);		
	    if (len && s[len-1] == '\n')
		   s[len-1] = '\0';
	    return s;
     }
}
