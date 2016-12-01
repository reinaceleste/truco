/**
******************************************************
*  \file funciones.c
*  \brief Contiene las funciones utilizadas en el TP
* \author Federico Ariel Marinzalda
* \version 1.1
* \date 1/12/2016
*
*
*******************************************************/
#include"prototipos.h"
#include<stdlib.h>
#include<time.h>

/**
******************************************************
*  \fn void configurarcartas (baraja_t(*cartas)[10])
*  \brief Función que completa una matriz con códigos de cartas
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 24/9/2016
* \param [in] **cartas Puntero a puntero a baraja_t que contiene la dirección de comienzo de la matriz de cartas
*******************************************************/
void configurarcartas (baraja_t(*cartas)[10])
{
    unsigned char i,j;
    for(i=BASTO;i<=ORO;i++)
    {
        for(j=1;j<=12;j++)
        {
            if(j<=7)
            {
                cartas[i-BASTO][j-1]=FACTOR*i+j;
            }
            else if(j>9)
            {
                cartas[i-BASTO][j-3]=FACTOR*i+j;
            }
        }
    }
}

/**
******************************************************
*  \fn void calcularvalorescartas (baraja_t(*cartas)[10],unsigned char(*valorcartaparaprimera)[10],unsigned char(*valorcartaparasegunda)[10])
*  \brief Función que completa matrices con códigos de valores de las cartas para el envido y para el truco
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 24/9/2016
* \param [in] **cartas Puntero a puntero a baraja_t que contiene la dirección de comienzo de la matriz de cartas
* \param [in] **valorcaraparaprimera Puntero a puntero a unsigned int que contiene la dirección de comienzo de la matriz con el valor de cada carta para el envido o la flor
* \param [in] **valorcaraparasegunda Puntero a puntero a unsigned int que contiene la dirección de comienzo de la matriz con el valor de cada carta para el truco
*******************************************************/
void calcularvalorescartas (baraja_t(*cartas)[10],unsigned char(*valorcartaparaprimera)[10],unsigned char(*valorcartaparasegunda)[10])
{
    unsigned char i,j,aux,aux2;
    for(i=BASTO;i<=ORO;i++)
    {
        for(j=0;j<10;j++)
        {
            if(cartas[i-BASTO][j]%FACTOR>0 && cartas[i-BASTO][j]%FACTOR<=7)
            {
                valorcartaparaprimera[i-BASTO][j]=cartas[i-BASTO][j]%FACTOR;
            }
            else
            {
                valorcartaparaprimera[i-2][j]=0;
            }
            aux=cartas[i-BASTO][j]%FACTOR;
            switch(aux)
            {
                case 1:
                    aux2=cartas[i-BASTO][j]/FACTOR;
                    switch(aux2)
                    {
                        case BASTO:
                            valorcartaparasegunda[i-BASTO][j]=VALORTRUCOANCHOBASTO;
                            break;
                        case COPA:
                            valorcartaparasegunda[i-BASTO][j]=VALORTRUCOANCHOFALSO;
                            break;
                        case ESPADA:
                            valorcartaparasegunda[i-BASTO][j]=VALORTRUCOANCHOESPADA;
                            break;
                        case ORO:
                            valorcartaparasegunda[i-BASTO][j]=VALORTRUCOANCHOFALSO;
                            break;
                    }
                    break;
                case 2:
                    valorcartaparasegunda[i-BASTO][j]=VALORTRUCO2;
                    break;
                case 3:
                    valorcartaparasegunda[i-BASTO][j]=VALORTRUCO3;
                    break;
                case 4:
                    valorcartaparasegunda[i-BASTO][j]=VALORTRUCO4;
                    break;
                case 5:
                    valorcartaparasegunda[i-BASTO][j]=VALORTRUCO5;
                    break;
                case 6:
                    valorcartaparasegunda[i-BASTO][j]=VALORTRUCO6;
                    break;
                case 7:
                    aux2=cartas[i-BASTO][j]/FACTOR;
                    switch(aux2)
                    {
                        case BASTO:
                            valorcartaparasegunda[i-BASTO][j]=VALORTRUCO7FALSO;
                            break;
                        case COPA:
                            valorcartaparasegunda[i-BASTO][j]=VALORTRUCO7FALSO;
                            break;
                        case ESPADA:
                            valorcartaparasegunda[i-BASTO][j]=VALORTRUCO7ESPADA;
                            break;
                        case ORO:
                            valorcartaparasegunda[i-BASTO][j]=VALORTRUCO7ORO;
                            break;
                    }
                    break;
                case 10:
                    valorcartaparasegunda[i-BASTO][j]=VALORTRUCOSOTA;
                    break;
                case 11:
                    valorcartaparasegunda[i-BASTO][j]=VALORTRUCOCABALLO;
                    break;
                case 12:
                    valorcartaparasegunda[i-BASTO][j]=VALORTRUCOREY;
                    break;
                default:
                    break;
            }
        }
    }
}

/**
******************************************************
*  \fn void repartircartas (baraja_t(*cartas)[10],baraja_t(*cartasrepartidas)[3],unsigned char mano,unsigned char jugadoresporequipo)
*  \brief Función que reparte 3 cartas a cada jugador. La primera va a quien es mano
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 24/9/2016
* \param [in] **cartas Puntero a puntero a baraja_t que contiene la dirección de comienzo de la matriz de cartas
* \param [in] **cartasrepartidas Puntero a puntero a baraja_t que contiene la dirección de comienzo de la matriz con los códigos de las cartas repartidas para los jugadores
* \param [in] mano Indica qué jugador es mano (ese jugador recibe la primer carta)
* \param [in] jugadoresporequipo Indica cuántos jugadores hay por equipo
*******************************************************/
void repartircartas (baraja_t(*cartas)[10],baraja_t(*cartasrepartidas)[3],unsigned char mano,unsigned char jugadoresporequipo)
{
    unsigned char tomacarta,carta,valida,i,j,s,r;
    srand(time(NULL));
    tomacarta=mano-JUG1;
    carta=0;
    while(carta<3)
    {
        do
        {
            cartasrepartidas[tomacarta][carta]=FACTOR*(rand()%(ORO+2))+(rand()%20);
            valida=CARTANOVALIDA;
            for(i=BASTO;i<=ORO && valida==CARTANOVALIDA;i++)
            {
                for(j=0;j<=9 && valida==CARTANOVALIDA;j++)
                {
                    if(cartasrepartidas[tomacarta][carta]==cartas[i-2][j])
                        valida=CARTAVALIDA;
                }
            }
        } while(valida==CARTANOVALIDA);
        s=carta;
        r=tomacarta+1;
        r%=2*jugadoresporequipo;
        while(!(s==carta && r==tomacarta))
        {
            if(cartasrepartidas[tomacarta][carta]==cartasrepartidas[r][s])
            {
                do
                {
                    cartasrepartidas[tomacarta][carta]=FACTOR*(rand()%(ORO+2))+(rand()%20);
                    valida=CARTANOVALIDA;
                    for(i=BASTO;i<=ORO && valida==CARTANOVALIDA;i++)
                    {
                        for(j=0;j<=9 && valida==CARTANOVALIDA;j++)
                        {
                            if(cartasrepartidas[tomacarta][carta]==cartas[i-2][j])
                                valida=CARTAVALIDA;
                        }
                    }
                } while(valida==CARTANOVALIDA);
                s=carta;
                r=tomacarta+1;
                r%=2*jugadoresporequipo;
            }
            else
            {
                r++;
                r%=2*jugadoresporequipo;
                if(tomacarta==r)
                {
                    s++;
                    s%=3;
                }
            }
        }
        tomacarta++;
        tomacarta%=2*jugadoresporequipo;
        if(tomacarta==mano-JUG1)
            carta++;
    }
}

/**
******************************************************
*  \fn void calculotanto (baraja_t(*cartas)[10],baraja_t(*cartasrepartidas)[3],unsigned char(*valorcartaparaprimera)[10],char* tantoenvido,char* tantoflor,unsigned char jugadoresporequipo,unsigned char hayflor)
*  \brief Función que calcula los tantos que tiene cada jugador para el envido o la flor
* \author Federico Ariel Marinzalda
* \version 1.1
* \date 1/12/2016
* \param [in] **cartas Puntero a puntero a baraja_t que contiene la dirección de comienzo de la matriz de cartas
* \param [in] **cartasrepartidas Puntero a puntero a baraja_t que contiene la dirección de comienzo de la matriz con los códigos de las cartas repartidas para los jugadores
* \param [in] **valorcaraparaprimera Puntero a puntero a unsigned int que contiene la dirección de comienzo de la matriz con el valor de cada carta para el envido o la flor
* \param [in] *tantoenvido Puntero a char que contiene la dirección de comienzo de un vector con los tantos de cada jugador para el envido (si un jugador tiene flor, habrá un -1 en su elemento correspondiente)
* \param [in] *tantoflor Puntero a char que contiene la dirección de comienzo de un vector con los tantos de cada jugador para la flor (si un jugador no tiene flor, habrá un -1 en su elemento correspondiente)
* \param [in] jugadoresporequipo Indica cuántos jugadores hay por equipo
* \param [in] hayflor Indica si se juega con flor o no
*******************************************************/
void calculotanto (baraja_t(*cartas)[10],baraja_t(*cartasrepartidas)[3],unsigned char(*valorcartaparaprimera)[10],char* tantoenvido,char* tantoflor,unsigned char jugadoresporequipo,unsigned char hayflor)
{
    unsigned char i,j,r,s,min,flag;
    char max;
    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
    {
        if((cartasrepartidas[i-JUG1][0]/FACTOR)==(cartasrepartidas[i-JUG1][1]/FACTOR) && (cartasrepartidas[i-JUG1][2]/FACTOR)==(cartasrepartidas[i-JUG1][1]/FACTOR) && hayflor==SI)
        {
            tantoflor[i-JUG1]=20;
            for(j=0;j<3;j++)
            {
                flag=0;
                for(r=BASTO;r<=ORO && flag==0;r++)
                {
                    for(s=0;s<10 && flag==0;s++)
                    {
                        if(cartasrepartidas[i-JUG1][j]==cartas[r-BASTO][s])
                        {
                            flag=1;
                            tantoflor[i-JUG1]+=valorcartaparaprimera[r-BASTO][s];
                        }
                    }
                }
            }
        }
        if((cartasrepartidas[i-JUG1][0]/FACTOR)==(cartasrepartidas[i-JUG1][1]/FACTOR) && (cartasrepartidas[i-JUG1][2]/FACTOR)==(cartasrepartidas[i-JUG1][1]/FACTOR))
        {
            tantoenvido[i-JUG1]=20;
            min=8;
            for(j=0;j<3;j++)
            {
                flag=0;
                for(r=BASTO;r<=ORO && flag==0;r++)
                {
                    for(s=0;s<10 && flag==0;s++)
                    {
                        if(cartasrepartidas[i-JUG1][j]==cartas[r-BASTO][s])
                        {
                            flag=1;
                            tantoenvido[i-JUG1]+=valorcartaparaprimera[r-BASTO][s];
                            if(valorcartaparaprimera[r-BASTO][s]<min)
                            {
                                min=valorcartaparaprimera[r-BASTO][s];
                            }
                        }
                    }
                }
            }
            tantoenvido[i-JUG1]-=min;
        }
        else if((cartasrepartidas[i-JUG1][0]/FACTOR)==(cartasrepartidas[i-JUG1][1]/FACTOR))
        {
            tantoenvido[i-JUG1]=20;
            for(j=0;j<3;j++)
            {
                if(j!=2)
                {
                    flag=0;
                    for(r=BASTO;r<=ORO && flag==0;r++)
                    {
                        for(s=0;s<10 && flag==0;s++)
                        {
                            if(cartasrepartidas[i-JUG1][j]==cartas[r-BASTO][s])
                            {
                                flag=1;
                                tantoenvido[i-JUG1]+=valorcartaparaprimera[r-BASTO][s];
                            }
                        }
                    }
                }
            }
        }
        else if((cartasrepartidas[i-JUG1][0]/FACTOR)==(cartasrepartidas[i-JUG1][2]/FACTOR))
        {
            tantoenvido[i-JUG1]=20;
            for(j=0;j<3;j++)
            {
                if(j!=1)
                {
                    flag=0;
                    for(r=BASTO;r<=ORO && flag==0;r++)
                    {
                        for(s=0;s<10 && flag==0;s++)
                        {
                            if(cartasrepartidas[i-JUG1][j]==cartas[r-BASTO][s])
                            {
                                flag=1;
                                tantoenvido[i-JUG1]+=valorcartaparaprimera[r-BASTO][s];
                            }
                        }
                    }
                }
            }
        }
        else if((cartasrepartidas[i-JUG1][2]/FACTOR)==(cartasrepartidas[i-JUG1][1]/FACTOR))
        {
            tantoenvido[i-JUG1]=20;
            for(j=0;j<3;j++)
            {
                if(j!=0)
                {
                    flag=0;
                    for(r=BASTO;r<=ORO && flag==0;r++)
                    {
                        for(s=0;s<10 && flag==0;s++)
                        {
                            if(cartasrepartidas[i-JUG1][j]==cartas[r-BASTO][s])
                            {
                                flag=1;
                                tantoenvido[i-JUG1]+=valorcartaparaprimera[r-BASTO][s];
                            }
                        }
                    }
                }
            }
        }
        else
        {
            max=-1;
            for(j=0;j<3;j++)
            {
                flag=0;
                for(r=BASTO;r<=ORO && flag==0;r++)
                {
                    for(s=0;s<10 && flag==0;s++)
                    {
                        if(cartasrepartidas[i-JUG1][j]==cartas[r-BASTO][s])
                        {
                            flag=1;
                            if(valorcartaparaprimera[r-BASTO][s]>max)
                            {
                                max=valorcartaparaprimera[r-BASTO][s];
                            }
                        }
                    }
                }
            }
            tantoenvido[i-JUG1]=max;
        }
    }
}

/**
******************************************************
*  \fn int myStrlen (const char* palabra)
*  \brief Función que calcula la longitud de una palabra
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 28/6/2016
* \param [in] *palabra Palabra cuya longitud quiere determinarse
* \param [out] i Longitud de la palabra
* \returns Devuelve número entero
*******************************************************/
int myStrlen (const char* palabra)
{
  int i;
  for (i=0;*(palabra+i)!=NULLCHAR;i++);
  return i;
}

/**
******************************************************
*  \fn int myStrncpy (char* dest,char* origen,int n)
*  \brief Función que copia los primeros n caracteres de una palabra a otro string
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 25/8/2016
* \param [in] *dest Dirección del string al que se envía la palabra
* \param [in] *origen Dirección del string del que proviene la palabra
* \param [in] n Cantidad de caracteres a copiar
* \param [out] -1 En caso de error en la copia
* \param [out] 0 En caso de copia realizada correctamente
* \returns Devuelve número entero
*******************************************************/
int myStrncpy (char* dest,char* origen,int n)
{
  int i;
  if(dest==NULL || n<1)
      return -1;
  for(i=0;i<n && *(origen+i)!=NULLCHAR;i++)
      *(dest+i)=*(origen+i);
  *(dest+i)=NULLCHAR;
  return 0;
}

/**
******************************************************
*  \fn int myStrnlastcpy (char* dest,char* origen,int n)
*  \brief Función que copia los últimos n caracteres de una palabra a otro string
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 25/8/2016
* \param [in] *dest Dirección del string al que se envía la palabra
* \param [in] *origen Dirección del string del que proviene la palabra
* \param [in] n Cantidad de caracteres a copiar
* \param [out] -1 En caso de error en la copia
* \param [out] 0 En caso de copia realizada correctamente
* \returns Devuelve número entero
*******************************************************/
int myStrnlastcpy (char* dest,char* origen,int n)
{
  int i,l;
  if(dest==NULL || n<1)
      return -1;
  l=myStrlen(origen);
  if(l<=n)
  {
      for(i=0;i<l;i++)
          *(dest+i)=*(origen+i);
  }
  else
  {
      for(i=0;i<n;i++)
          *(dest+i)=*(origen+(l-n+i));
  }
  *(dest+i)=NULLCHAR;
  return 0;
}

/**
******************************************************
*  \fn int myStrcencpy (char* dest,char* origen,int n,int m)
*  \brief Función que copia los caracteres centrales de una palabra a otro string (no copia ni los n primeros ni los m últimos)
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 25/8/2016
* \param [in] *dest Dirección del string al que se envía la palabra
* \param [in] *origen Dirección del string del que proviene la palabra
* \param [in] n Cantidad de primeros caracteres que no se desean copiar
* \param [in] m Cantidad de últimos caracteres que no se desean copiar
* \param [out] control -1 En caso de error en la copia, 0 En caso de copia realizada correctamente
* \returns Devuelve número entero
*******************************************************/
int myStrcencpy (char* dest,char* origen,int n,int m)
{
  int l,control;
  l=myStrlen(origen);
  if(dest==NULL || n+m>l || n<0 || m<0)
      return -1;
  control=myStrncpy(dest,origen,l-m);
  if(control==-1)
      return control;
  control=myStrnlastcpy(dest,dest,l-m-n);
  return control;
}