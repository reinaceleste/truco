/**
******************************************************
*  \file prototipos.h
*  \brief Contiene los prototipos de las funciones, las constantes simbólicas, typedefs y estructuras utilizadas en el TP
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 24/9/2016
*
*
*******************************************************/

//Typedef utilizados en el TP
typedef unsigned char baraja_t;

//Prototipos de funciones usadas en el TP
void configurarcartas (baraja_t(*)[10]);
void calcularvalorescartas (baraja_t(*)[10],unsigned char(*)[10],unsigned char(*)[10]);
void repartircartas (baraja_t(*)[10],baraja_t(*)[3],unsigned char,unsigned char);
void calculotanto (baraja_t(*)[10],baraja_t(*)[3],unsigned char(*)[10],char*,char*,unsigned char,unsigned char);
int myStrlen (const char*);

//Constantes simbólicas usadas en el TP
#define BASTO 2
#define COPA (BASTO+1)
#define ESPADA (BASTO+2)
#define ORO (BASTO+3)
#define FACTOR 40
#define CARTAVALIDA 1
#define CARTANOVALIDA 0
#define JUG1 0
#define JUG2 (JUG1+1)
#define JUG3 (JUG1+2)
#define JUG4 (JUG1+3)
#define JUG5 (JUG1+4)
#define JUG6 (JUG1+5)
#define NADIE (JUG6+10)
#define EQ1 JUG1
#define EQ2 JUG2
#define PARDA (10+JUG1)
#define SI 1
#define NO 0
#define JUGARCARTA 1
#define ENVIDO (JUGARCARTA+1)
#define REALENVIDO (JUGARCARTA+2)
#define FALTAENVIDO (JUGARCARTA+3)
#define FLOR (JUGARCARTA+4)
#define CONTRAFLOR (JUGARCARTA+5)
#define CONTRAFLORALRESTO (JUGARCARTA+6)
#define TRUCO (JUGARCARTA+7)
#define QUIERO (JUGARCARTA+8)
#define NOQUIERO (JUGARCARTA+9)
#define CONFLORMEACHICO (JUGARCARTA+10)
#define CANTARTANTO (JUGARCARTA+11)
#define QUIERORETRUCO (JUGARCARTA+12)
#define QUIEROVALECUATRO (JUGARCARTA+13)
#define ALMAZO (JUGARCARTA+14)
#define CHATTODOS (JUGARCARTA+15)
#define CHATEQUIPO (JUGARCARTA+16)
#define NADA (JUGARCARTA+17)
#define NOVALE -1
#define REDONDA 0
#define PICAPICA 1
#define VALORTRUCO4 0
#define VALORTRUCO5 (VALORTRUCO4+1)
#define VALORTRUCO6 (VALORTRUCO4+2)
#define VALORTRUCO7FALSO (VALORTRUCO4+3)
#define VALORTRUCOSOTA (VALORTRUCO4+4)
#define VALORTRUCOCABALLO (VALORTRUCO4+5)
#define VALORTRUCOREY (VALORTRUCO4+6)
#define VALORTRUCOANCHOFALSO (VALORTRUCO4+7)
#define VALORTRUCO2 (VALORTRUCO4+8)
#define VALORTRUCO3 (VALORTRUCO4+9)
#define VALORTRUCO7ORO (VALORTRUCO4+10)
#define VALORTRUCO7ESPADA (VALORTRUCO4+11)
#define VALORTRUCOANCHOBASTO (VALORTRUCO4+12)
#define VALORTRUCOANCHOESPADA (VALORTRUCO4+13)
#define LARGOMSG 200
#define TERMINO 2
#define NULLCHAR '\0'
