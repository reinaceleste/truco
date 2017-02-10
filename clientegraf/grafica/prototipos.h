/**
 *	\file prototips.h
 *	\brief Contiene los prototipos de las funciones, las constantes simbólicas, typedefs y estructuras utilizadas en la interfaz gráfica
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 7/2/2017
 */

#define ANCHO 640
#define ALTO 480
#define PORT "portada.tga"
#define PORTR "portadaregis.tga"
#define PORTI "portadainic.tga"
#define PORTJ "portadajugar.tga"
#define PORTL "portadalideres.tga"
#define PORTSALIR "portadasalir.tga"
#define PORTVOLV1 "portadavolver1.tga"
#define PORTVOLV2 "portadavolver2.tga"
#define FUENTE "trebuchetcursiva20.pcx"
#define CURSOR "cursor.bmp"
#define SI 1
#define NO 0
#define REG 1
#define INIC 2
#define JUG 3
#define LID 4
#define NULLCHAR '\0'
#define MAX_LONG 46
#define MAX_REP 1000
#define mouse_en_opciones mouse_x>=470&&((mouse_y>=190&&mouse_y<=230)||(mouse_y>=250&&mouse_y<=290)||(mouse_y>=310&&mouse_y<=350)||(mouse_y>=360&&mouse_y<=400)||(mouse_y>=410&&mouse_y<=450))
#define mouse_y_regis mouse_y>=190&&mouse_y<=230
#define mouse_y_inic mouse_y>=250&&mouse_y<=290
#define mouse_y_jugar mouse_y>=310&&mouse_y<=350
#define mouse_y_lideres mouse_y>=360&&mouse_y<=400
#define mouse_y_salir mouse_y>=410&&mouse_y<=450
#define mouse_en_volver mouse_x>=480&&mouse_x<=550&&mouse_y>=410&&mouse_y<=450

void abort_on_error(const char *message);
int my_strlen (char* palabra);
int myStrncpy (char* dest,char* origen,int n);