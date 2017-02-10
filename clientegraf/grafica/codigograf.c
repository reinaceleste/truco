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
* \version 1.0
* \date 7/2/2017
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
* \version 1.0
* \date 7/2/2017
*
*******************************************************/

int main()
{
    BITMAP *portada,*portadaregis,*portadainic,*portadajugar,*portadalideres,*portadasalir,*portadavolver1,*portadavolver2;
    BITMAP *buffer,*cursor;
    FONT *font;
    char salir=NO,opcion=NO,chartostr[2]={0},palabra[MAX_LONG]={0},limpiobuf=NO,encabezado[MAX_REP];
    //int i;
    //int tecla;
    int cantenters;
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
                    //textout_centre_ex(buffer,font,"Ingrese nombre de usuario",ANCHO/2,ALTO/4,makecol(238,187,136),makecol(0,0,0));
                    switch(cantenters)
                    {
                        case 0:
                            strcpy(encabezado,"Ingrese su nombre de usuario");
                            break;
                        case 1:
                            strcpy(encabezado,"Ingrese su contraseña");
                            break;
                        case 2:
                            strcpy(encabezado,"Confirmar contraseña");
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
                            strcpy(encabezado,"Ingrese su nombre de usuario");
                            break;
                        case 1:
                            strcpy(encabezado,"Ingrese su contraseña");
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
                            strcpy(encabezado,"Ingrese su modalidad de juego");
                            break;
                        case 1:
                            strcpy(encabezado,"Ingrese cantidad de jugadores por equipo");
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
                            strcpy(encabezado,"Proximamente");
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
            textout_centre_ex(buffer,font,encabezado,ANCHO/2,ALTO/4,makecol(238,187,136),makecol(0,0,0));
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
                    if(opcion!=NO)
                    {
                        strcpy(palabra,chartostr);
                    }
                }
                else
                {
                    strcat(palabra,chartostr);
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
            }
            else if(chartostr[0]=='\r')
            {
                cantenters++;
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