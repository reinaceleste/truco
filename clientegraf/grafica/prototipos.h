/**
 *	\file prototipos.h
 *	\brief Contiene los prototipos de las funciones, las constantes simbólicas, typedefs y estructuras utilizadas en la interfaz gráfica
* \author Federico Ariel Marinzalda
* \version 1.4
* \date 11/2/2017
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
#define MAX_RENG 11
#define MAX_USER 40
#define MAX_PASS 24
#define mouse_en_opciones mouse_x>=470&&((mouse_y>=190&&mouse_y<=230)||(mouse_y>=250&&mouse_y<=290)||(mouse_y>=310&&mouse_y<=350)||(mouse_y>=360&&mouse_y<=400)||(mouse_y>=410&&mouse_y<=450))
#define mouse_y_regis mouse_y>=190&&mouse_y<=230
#define mouse_y_inic mouse_y>=250&&mouse_y<=290
#define mouse_y_jugar mouse_y>=310&&mouse_y<=350
#define mouse_y_lideres mouse_y>=360&&mouse_y<=400
#define mouse_y_salir mouse_y>=410&&mouse_y<=450
#define mouse_en_volver mouse_x>=480&&mouse_x<=550&&mouse_y>=410&&mouse_y<=450
#define USUARIOSPRUEBA "federico","reina","marcelo","florencia","sebastian",NULL
#define PASSPRUEBA "abCD1234","info1Elec","R1022prof","cursoR1022","elec1022R",NULL
#define LIDERESPRUEBA "Usuario puntos","marcelo 155","reina 120","federico 105","florencia 100","sebastian 100","a 90","b 85","c 85","d 75","e 70","f 65","g 60"

/**
 *	\struct usuario
 *	\brief Datos del usuario
 * \details Nombre de usuario y contraseña (ambos son vectores de chars)
* \author Federico Marinzalda
* \version 1.1
* \date 22/12/2016
 */
struct usuario{
    char user[MAX_USER+1];
    char password[MAX_PASS+1];
};

void abort_on_error(const char *message);
int my_strlen (char* palabra);
int myStrncpy (char* dest,char* origen,int n);
int myStrncmp (const char* s1,const char* s2,int n);
void closebuttonhandler(void);