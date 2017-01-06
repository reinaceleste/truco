#include "conexion.h"

/**
******************************************************
*  \fn int myStrncmp (const char*s1,const char*s2,int n)
*  \brief Función que recibe dos palabras y compara los primeos n caracteres
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 28/6/2016
* \param [in] *s1 Palabra a comparar
* \param [in] *s2 Palabra a comparar
* \param [in] n Cantidad de caracteres a comparar (en caso que sea mayor a la longitud de la palabra s1, se compara esa cantidad de caracteres en vez de n)
* \returns Diferencia de códigos ASCII de el primer caracter distinto entre s1 y s2, o la diferencia entre los ASCII del último caracter a comparar de cada uno como número entero
* \details Resulatados posibles
* \n >0 --> s1 está antes de s2 en el alfabeto
* \n ==0 --> s1 y s2 están en el mismo orden alfabético
* \n <0 --> s2 está antes de s1 en el alfabeto
*******************************************************/
int myStrncmp (const char* s1,const char* s2,int n)
{
  int i;
  for (i=0;i<n-1 && *(s1+i)!=NULLCHAR;i++)
  {
    if (*(s1+i)!=*(s2+i))
    {
      return (int)(*(s2+i)-*(s1+i)); //Si el caracter i de la palabra s1 es distinta al de la palabra s2 devuelve la diferencia de sus códigos ASCII como int
    }
  }
  return (int)(*(s2+i)-*(s1+i)); //Si estoy en esta línea, devuelvo la diferencia entre el último caracter a comparar de s1 y el último caracter a comparar de s2
}