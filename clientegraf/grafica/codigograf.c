/**
******************************************************
*  \file codigograf.c
*  \brief TP Obligatorio
* \details Interfaz gráfica
* Uso del make
* - Compilar con make new o make clientui
* - Ejecutar o compilar y ejecutar en un paso com make run o simplemente make (luego de la ejecución se borrarán los archivos objeto y el ejecutable)
* - Generar y abrir página web con documento Doxygen con make html
* - Borrar web con make no_html
* - Agregar archivos .c, Makefile y Doxyfile al repositorio con make git
* \author Federico Ariel Marinzalda
* \version 1.4
* \date 10/2/2017
*
*
*******************************************************/

#include<allegro.h>
#include"prototipos.h"
#include<stdio.h>
#include<string.h>

/**
******************************************************
*  \fn int main(void)
*  \brief Función principal de la interfaz gráfica
* \details Se crea una ventana a partir de imagenes bmp
* \n En terminal, compilar con gcc -o clientui codigograf.c -Wall `allegro-config --libs`
* \author Federico Ariel Marinzalda
* \version 3.0
* \date 11/2/2017
*
*******************************************************/

int main()
{
    BITMAP *portada,*portadaregis,*portadainic,*portadajugar,*portadalideres,*portadasalir,*portadavolver1,*portadavolver2;
    BITMAP *buffer,*cursor;
    FONT *font;
    char salir=NO,opcion=NO,chartostr[2]={0},palabra[MAX_LONG]={0},limpiobuf=NO,encabezado[MAX_RENG][MAX_REP],errorpass=NO,buffpass[MAX_LONG]={0},modook,cantjugok,conflor,jugstr[2]={0};
    //char buffuser[MAX_LONG];
    int i,y;
    //int tecla;
    int cantenters;
    struct usuario us;
    if(allegro_init())
    {
        abort_on_error("No se puede inicializar la biblioteca allegro\n");
    }
    set_color_depth(32);
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO, ALTO, 0, 0))
    {
        abort_on_error("No se puede usar una resolución de 32 bits\n");
    }
    install_keyboard();
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO, ALTO, 0, 0))
    {
        abort_on_error("Error al crear modo gráfico\n");
    }
    install_mouse();
    buffer=create_bitmap(ANCHO,ALTO);
    portada=load_bitmap(PORT,NULL);
    if(portada==NULL)
    {
        abort_on_error("No se cargó portada\n");
    }
    portadaregis=load_bitmap(PORTR,NULL);
    if(portadaregis==NULL)
    {
        abort_on_error("No se cargó portada regis\n");
    }
    portadainic=load_bitmap(PORTI,NULL);
    if(portadainic==NULL)
    {
        abort_on_error("No se cargó portada inic\n");
    }
    portadajugar=load_bitmap(PORTJ,NULL);
    if(portadajugar==NULL)
    {
        abort_on_error("No se cargó portada jugar\n");
    }
    portadalideres=load_bitmap(PORTL,NULL);
    if(portadalideres==NULL)
    {
        abort_on_error("No se cargó portada lideres\n");
    }
    portadasalir=load_bitmap(PORTSALIR,NULL);
    if(portadasalir==NULL)
    {
        abort_on_error("No se cargó portada salir\n");
    }
    portadavolver1=load_bitmap(PORTVOLV1,NULL);
    if(portadavolver1==NULL)
    {
        abort_on_error("No se cargó portada volver 1\n");
    }
    portadavolver2=load_bitmap(PORTVOLV2,NULL);
    if(portadavolver2==NULL)
    {
        abort_on_error("No se cargó portada volver 2\n");
    }
    cursor=load_bitmap(CURSOR,NULL);
    font=load_font(FUENTE,NULL,NULL);
    if(font==NULL)
    {
        abort_on_error("No se cargó la fuente\n");
    }
    while(salir==NO)
    {
        for(i=0;i<MAX_RENG;i++)
        {
            strcpy(encabezado[i],"NULL");
        }
        if(opcion==NO)
        {
            cantenters=0;
            if(mouse_en_opciones)
            {
                if(mouse_y_regis)
                {
                    blit(portadaregis, buffer, 0, 0, 0, 0, ANCHO, ALTO);
                    if(mouse_b & 1)
                    {
                        opcion=REG;
                    }
                }
                else if(mouse_y_inic)
                {
                    blit(portadainic, buffer, 0, 0, 0, 0, ANCHO, ALTO);
                    if(mouse_b & 1)
                    {
                        opcion=INIC;
                    }
                }
                else if(mouse_y_jugar)
                {
                    blit(portadajugar, buffer, 0, 0, 0, 0, ANCHO, ALTO);
                    if(mouse_b & 1)
                    {
                        opcion=JUG;
                    }
                }
                else if(mouse_y_lideres)
                {
                    blit(portadalideres, buffer, 0, 0, 0, 0, ANCHO, ALTO);
                    if(mouse_b & 1)
                    {
                        opcion=LID;
                    }
                }
                else if(mouse_y_salir)
                {
                    blit(portadasalir, buffer, 0, 0, 0, 0, ANCHO, ALTO);
                    if(mouse_b & 1)
                    {
                        salir=SI;
                    }
                }
            }
            else
            {
                blit(portada, buffer, 0, 0, 0, 0, ANCHO, ALTO);
            }
            masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13,22);
            blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
            if(key[KEY_ESC])
            {
                salir=SI;
            }
        }
        else
        {
            if(limpiobuf==NO)
            {
                clear_keybuf();
                limpiobuf=SI;
            }
            if(mouse_en_volver)
            {
                blit(portadavolver2, buffer, 0, 0, 0, 0, ANCHO, ALTO);
                if(mouse_b & 1)
                {
                    mouse_b=0;
                    opcion=NO;
                    limpiobuf=NO;
                    palabra[0]='\0';
                }
            }
            else
            {
                blit(portadavolver1, buffer, 0, 0, 0, 0, ANCHO, ALTO);
            }
            switch(opcion)
            {
                case REG:
                    switch(cantenters)
                    {
                        case 0:
                            strcpy(encabezado[0],"Ingrese su nombre de usuario");
                            strcpy(encabezado[1],"Luego presione enter");
                            break;
                        case 1:
                            strcpy(encabezado[0],"Ingrese su contrasena");
                            strcpy(encabezado[1],"Luego presione enter");
                            break;
                        case 2:
                            if(errorpass==NO)
                            {
                                strcpy(encabezado[0],"Confirmar su contrasena");
                                strcpy(encabezado[1],"Luego presione enter");
                            }
                            else
                            {
                                strcpy(encabezado[0],"Contrasena no coincide");
                                strcpy(encabezado[1],"Confirmar su contrasena");
                                strcpy(encabezado[2],"Luego presione enter");
                            }
                            break;
                        case 3:
                            if(myStrncmp(us.password,buffpass,my_strlen(us.password)+1)==0)
                            {
                                strcpy(encabezado[0],"Usuario registrado: ");
                                strcat(encabezado[0],us.user);
                                strcpy(encabezado[1],"Contrasena: ");
                                for(i=0;i<my_strlen(us.password);i++)
                                {
                                    strcat(encabezado[1],"*");
                                }
                                strcpy(encabezado[2],"Presione enter o haga clic en volver");
                                errorpass=NO;
                                if(keypressed())
                                {
                                    if(key[KEY_ENTER])
                                    {
                                        cantenters++;
                                    }
                                }
                            }
                            else
                            {
                                cantenters=2;
                                errorpass=SI;
                            }
                            break;
                        default:
                            cantenters=0;
                            opcion=NO;
                            limpiobuf=NO;
                            palabra[0]='\0';
                            break;
                    }
                    break;
                case INIC:
                    switch(cantenters)
                    {
                        case 0:
                            strcpy(encabezado[0],"Ingrese su nombre de usuario");
                            strcpy(encabezado[1],"Luego presione enter");
                            break;
                        case 1:
                            strcpy(encabezado[0],"Ingrese su contrasena");
                            strcpy(encabezado[1],"Luego presione enter");
                            break;
                        default:
                            cantenters=0;
                            opcion=NO;
                            limpiobuf=NO;
                            palabra[0]='\0';
                            break;
                    }
                    break;
                case JUG:
                    switch(cantenters)
                    {
                        case 0:
                            strcpy(encabezado[0],"Ingrese su modo de juego (en mayuscula)");
                            strcpy(encabezado[1],"S: jugar con flor");
                            strcpy(encabezado[2],"N: jugar sin flor");
                            strcpy(encabezado[3],"Luego presione enter");
                            break;
                        case 1:
                            if(modook==SI)
                            {
                                strcpy(encabezado[0],"Ingrese cantidad de jugadores por equipo");
                                strcpy(encabezado[1],"(de 1 a 3 jugadores por equipo)");
                                strcpy(encabezado[2],"Luego presione enter");
                            }
                            else
                            {
                                cantenters=0;
                            }
                            break;
                        case 2:
                            if(cantjugok==SI)
                            {
                                strcpy(encabezado[0],"Log");
                                strcpy(encabezado[1],"Modo: ");
                                if(conflor==SI)
                                {
                                    strcat(encabezado[1],"con flor");
                                }
                                else
                                {
                                    strcat(encabezado[1],"sin flor");
                                }
                                strcpy(encabezado[2],"Jugadores por equipo: ");
                                strcat(encabezado[2],jugstr);
                                strcpy(encabezado[3],"Espere conexion de otros jugadores");
                                strcpy(encabezado[4],"o bien oprima enter o haga clic en volver");
                                strcpy(encabezado[5],"para salir del log y volver al menu inicial");
                                if(keypressed())
                                {
                                    if(key[KEY_ENTER])
                                    {
                                        cantenters++;
                                    }
                                }
                            }
                            else
                            {
                                cantenters=1;
                            }
                            break;
                        default:
                            cantenters=0;
                            opcion=NO;
                            limpiobuf=NO;
                            palabra[0]='\0';
                            break;
                    }
                    break;
                case LID:
                    switch(cantenters)
                    {
                        case 0:
                            strcpy(encabezado[0],"Proximamente");
                            break;
                        default:
                            cantenters=0;
                            opcion=NO;
                            limpiobuf=NO;
                            palabra[0]='\0';
                            break;
                    }
                    break;
                default:
                    break;
            }
            for(i=0,y=ALTO/8;myStrncmp(encabezado[i],"NULL",my_strlen(encabezado[i])) && i<MAX_RENG;i++,y+=text_height(font))
            {
                textout_centre_ex(buffer,font,encabezado[i],ANCHO/2,y,makecol(238,187,136),makecol(0,0,0));
            }
            textout_centre_ex(buffer,font,palabra,ANCHO/2,3*ALTO/4,makecol(238,187,136),makecol(0,0,0));
            if(keypressed())
            {
                chartostr[0]=readkey();
            }
            else
            {
                chartostr[0]='|';
            }
            if((chartostr[0]>='a'&&chartostr[0]<='z')||(chartostr[0]>='A'&&chartostr[0]<='Z')||(chartostr[0]>='0'&&chartostr[0]<='9'))
            {
                if(my_strlen(palabra)==0)
                {
                    if(opcion==REG)
                    {
                        switch(cantenters)
                        {
                            case 0:
                                strcpy(palabra,chartostr);
                                break;
                            case 1:
                            case 2:
                                strcpy(palabra,"*");
                                strcpy(buffpass,chartostr);
                                break;
                            default:
                                break;
                        }
                    }
                    else if(opcion==JUG)
                    {
                        if(cantenters<2)
                        {
                            strcpy(palabra,chartostr);
                        }
                    }
                    else if(opcion!=NO)
                    {
                        strcpy(palabra,chartostr);
                    }
                }
                else
                {
                    if(opcion==REG)
                    {
                        switch(cantenters)
                        {
                            case 0:
                                strcat(palabra,chartostr);
                                break;
                            case 1:
                            case 2:
                                strcat(palabra,"*");
                                strcat(buffpass,chartostr);
                                break;
                            default:
                                break;
                        }
                    }
                    else if(opcion==JUG)
                    {
                        if(cantenters<2)
                        {
                            strcat(palabra,chartostr);
                        }
                    }
                    else if(opcion!=NO)
                    {
                        strcat(palabra,chartostr);
                    }
                }
            }
            else if(chartostr[0]=='\b' && my_strlen(palabra))
            {
                if(my_strlen(palabra)-1)
                {
                    myStrncpy(palabra,palabra,my_strlen(palabra)-1);
                }
                else
                {
                    palabra[0]='\0';
                }
                if(my_strlen(buffpass)-1)
                {
                    myStrncpy(buffpass,buffpass,my_strlen(buffpass)-1);
                }
                else
                {
                    palabra[0]='\0';
                }
            }
            else if(chartostr[0]=='\r')
            {
                if(my_strlen(palabra))
                {
                    cantenters++;
                }
                if(opcion==REG && cantenters==1)
                {
                    strcpy(us.user,palabra);
                }
                else if(opcion==REG && cantenters==2)
                {
                    strcpy(us.password,buffpass);
                }
                else if(opcion==JUG && cantenters==1)
                {
                    if(myStrncmp(palabra,"S",2) && myStrncmp(palabra,"N",2))
                    {
                        modook=NO;
                    }
                    else
                    {
                        modook=SI;
                        if(palabra[0]=='S')
                        {
                            conflor=SI;
                        }
                        else
                        {
                            conflor=NO;
                        }
                    }
                }
                else if(opcion==JUG && cantenters==2)
                {
                    if(myStrncmp(palabra,"1",2) && myStrncmp(palabra,"2",2) && myStrncmp(palabra,"3",2))
                    {
                        cantjugok=NO;
                    }
                    else
                    {
                        cantjugok=SI;
                        strcpy(jugstr,palabra);
                    }
                }
                palabra[0]='\0';
            }
            masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13,22);
            blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
        }
    }
    destroy_bitmap(cursor);
    destroy_bitmap(buffer);
    destroy_bitmap(portada);
    destroy_bitmap(portadaregis);
    destroy_bitmap(portadainic);
    destroy_bitmap(portadajugar);
    destroy_bitmap(portadalideres);
    destroy_bitmap(portadasalir);
    destroy_bitmap(portadavolver1);
    destroy_bitmap(portadavolver2);
    destroy_font(font);
    return 0;
}
END_OF_MAIN();


/**
******************************************************
*  \fn void abort_on_error(const char *message)
*  \brief Función utilizada para mostrar un mensaje de error y abortar el programa
* \details Se crea una ventana a partir de imagenes bmp
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 7/2/2017
* \param[in] message Mensaje a mostrar
*
*******************************************************/
void abort_on_error(const char *message)
      {
         if (screen != NULL)
            set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);

         allegro_message("%s.\nLast Allegro error `%s'\n",
                         message, allegro_error);
         exit(-1);
      }

/**
******************************************************
*  \fn int my_strlen (char* palabra)
*  \brief Función que calcula la longitud de una palabra
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 28/6/2016
* \param [in] *palabra Palabra cuya longitud quiere determinarse
* \param [out] i Longitud de la palabra
* \returns Devuelve número entero
*******************************************************/
int my_strlen (char* palabra)
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