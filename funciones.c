/**
******************************************************
*  \file funciones.c
*  \brief Contiene las funciones utilizadas en el TP
* \author Federico Ariel Marinzalda
* \version 1.2
* \date 12/12/2016
*
*
*******************************************************/
#include"prototipos.h"
#include<stdio.h>
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
*  \fn void inicializaracciones (unsigned char(*acciones)[6],unsigned char jugadoresporequipo,unsigned char hayflor)
*  \brief Función que inicializa la matriz de acciones
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 12/12/2016
* \param [in] **acciones Puntero a puntero a unsigned char que contiene la dirección de comienzo de la matriz de acciones posibles para cada jugador
* \param [in] jugadoresporequipo Indica cuántos jugadores hay por equipo
* \param [in] hayflor Indica si se juega con flor o no
*******************************************************/
void inicializaracciones (unsigned char(*acciones)[6],unsigned char jugadoresporequipo,unsigned char hayflor)
{
    unsigned char i,j;
    for(i=JUG1;i<=JUG6;i++)
    {
        for(j=JUGARCARTA;j<=NADA;j++)
        {
            if(j==CONTRAFLOR || j==CONTRAFLORALRESTO || j==QUIERO || j==NOQUIERO || j==CONFLORMEACHICO || j==CANTARTANTO || j== QUIERORETRUCO || j== QUIEROVALECUATRO || j==NADA)
            {
                acciones[j-JUGARCARTA][i-JUG1]=NO;
            }
            else
            {
                acciones[j-JUGARCARTA][i-JUG1]=SI;
            }
        }
    }
    if(jugadoresporequipo==1)
    {
        for(i=JUG1;i<=JUG6;i++)
        {
            acciones[CHATEQUIPO-JUGARCARTA][i-JUG1]=NO;
        }
    }
    if(hayflor==NO)
    {
        acciones[FLOR-JUGARCARTA][i-JUG1]=NO;
    }
    if(jugadoresporequipo<3)
    {
        for(i=2*jugadoresporequipo;i<6;i++)
        {
            for(j=JUGARCARTA;j<=NADA;j++)
            {
                acciones[j-JUGARCARTA][i+JUG1]=NO;
            }
        }
    }
}

/**
******************************************************
*  \fn void inicializarmano (char *tantoenvido,char *tantoflor,char *penalizacionflor,char *cantobienflor,char *cartasjugadastruco,char *jugcantoenvido,unsigned char *mazo,unsigned char(*ordencartasjugadas)[3],unsigned char jugadoresporequipo)
*  \brief Función que inicializa la mano a jugar
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 12/12/2016
* \param [in] *tantoenvido Puntero a char que contiene la dirección de comienzo de un vector con los tantos de cada jugador para el envido (si un jugador tiene flor, habrá un -1 en su elemento correspondiente)
* \param [in] *tantoflor Puntero a char que contiene la dirección de comienzo de un vector con los tantos de cada jugador para la flor (si un jugador no tiene flor, habrá un -1 en su elemento correspondiente)
* \param [in] *penalizacionflor Puntero a char que contiene la dirección de comienzo de un vector con los flags de penalización de cada jugador por flor mal cantada
* \param [in] *cantobienflor Puntero a char que contiene la dirección de comienzo de un vector con los flags que indican si un jugador decidió bien en cantar o no una flor
* \param [in] *cartasjugadastruco Puntero a char que contiene la dirección de comienzo de un vector con las cartas jugadas por cada jugador en una baza
* \param [in] *jugcantoenvido Puntero a char que contiene la dirección de comienzo de un vector con los flags que indican si un jugador cantó en el envido
* \param [in] *mazo Puntero a unsigned char que contiene la dirección de comienzo de un vector con los flags que indican si un jugador se fue al mazo
* \param [in] **ordencartasjugadas Puntero a puntero unsigned char que contiene la dirección de comienzo de una matriz con los daatos de las cartas jugadas por cada jugador y en qué orden (la primer carta jugada estará en la posición 0)
* \param [in] jugadoresporequipo Indica cuántos jugadores hay por equipo
*******************************************************/
void inicializarmano (char *tantoenvido,char *tantoflor,char *penalizacionflor,char *cantobienflor,char *cartasjugadastruco,char *jugcantoenvido,unsigned char *mazo,unsigned char(*ordencartasjugadas)[3],unsigned char jugadoresporequipo)
{
    unsigned char i,j;
    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
    {
        tantoenvido[i-JUG1]=-1;
        tantoflor[i-JUG1]=-1;
        penalizacionflor[i-JUG1]=NO;
        cantobienflor[i-JUG1]=NO;
        cartasjugadastruco[i-JUG1]=-2;
        jugcantoenvido[i-JUG1]=NO;
        mazo[i-JUG1]=NO;
        for(j=0;j<3;j++)
        {
            ordencartasjugadas[i-JUG1][j]=0;
        }
    }
}

/**
******************************************************
*  \fn void informarcartas(unsigned char mostrarcartas,unsigned char(*cartasrepartidas)[3],unsigned char hayflor,unsigned char mano)
*  \brief Función que informa las cartas y los tantos de un jugador
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 12/12/2016
* \param [in] mostrarcartas PCódigo del jugador cuyas cartas y tanto se van a informar
* \param [in] **cartasrepartidas Puntero a puntero unsigned char que contiene la dirección de comienzo de una matriz con los daatos de las cartas repartidas a cada jugador
* \param [in] hayflor Indica si se juega con flor o no
* \param [in] mano Código del jugador que es mano
* \param [in] *tantoenvido Puntero a char que contiene la dirección de comienzo de un vector con los tantos de cada jugador para el envido (si un jugador tiene flor, habrá un -1 en su elemento correspondiente)
* \param [in] *tantoflor Puntero a char que contiene la dirección de comienzo de un vector con los tantos de cada jugador para la flor (si un jugador no tiene flor, habrá un -1 en su elemento correspondiente)
*******************************************************/
void informarcartas(unsigned char mostrarcartas,unsigned char(*cartasrepartidas)[3],unsigned char hayflor,unsigned char mano,char *tantoenvido,char *tantoflor)
{
    unsigned char i,palo;
    printf("Jugador %d (Equipo %d)",mostrarcartas+1,mostrarcartas%2+1);
    if(mostrarcartas==mano-JUG1)
    {
        printf(" (es mano)");
    }
    printf(":\n");
    for(i=0;i<3;i++)
    {
        printf("%d° carta: ",i+1);
        printf("%d de ",cartasrepartidas[mostrarcartas][i]%FACTOR);
        palo=cartasrepartidas[mostrarcartas][i]/FACTOR;
        switch(palo)
        {
            case BASTO:
                printf("basto\n");
                break;
            case COPA:
                printf("copa\n");
                break;
            case ESPADA:
                printf("espada\n");
                break;
            case ORO:
                printf("oro\n");
                break;
            default:
                break;
        }
    }
    printf("\n");
    printf("Para el envido: %d",tantoenvido[mostrarcartas]);
    if(hayflor==SI)
    {
        printf("\tPara la flor: %d",tantoflor[mostrarcartas]);
    }
    printf("\n\n");
}

/**
******************************************************
*  \fn void juegamano (baraja_t(*cartas)[10],baraja_t(*cartasrepartidas)[3],unsigned char(*acciones)[6],unsigned char mano,char *tantoenvido,char *tantoflor,char *penalizacionflor,char *cantobienflor,char *cartasjugadastruco,char *jugcantoenvido,unsigned char *mazo,unsigned char(*ordencartasjugadas)[3],unsigned char(*valorcartaparasegunda)[10],unsigned char jugadoresporequipo,unsigned char hayflor,unsigned char estilo,unsigned char *eqganaprimera,unsigned char *eqganasegunda,unsigned char *floresnegadaseq1,unsigned char *floresnegadaseq2,unsigned char *puntosprimera,unsigned char *puntossegunda,unsigned char puntoseq1,unsigned char puntoseq2)
*  \brief Función que inicializa la mano a jugar
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 12/12/2016
* \param [in] **cartas Puntero a puntero a baraja_t que contiene la dirección de comienzo de la matriz de cartas
* \param [in] **cartasrepartidas Puntero a puntero a baraja_t que contiene la dirección de comienzo de la matriz con los códigos de las cartas repartidas para los jugadores
* \param [in] **acciones Puntero a puntero a unsigned char que contiene la dirección de comienzo de la matriz de acciones posibles para cada jugador
* \param [in] mano Código del jugador que es mano
* \param [in] *tantoenvido Puntero a char que contiene la dirección de comienzo de un vector con los tantos de cada jugador para el envido (si un jugador tiene flor, habrá un -1 en su elemento correspondiente)
* \param [in] *tantoflor Puntero a char que contiene la dirección de comienzo de un vector con los tantos de cada jugador para la flor (si un jugador no tiene flor, habrá un -1 en su elemento correspondiente)
* \param [in] *penalizacionflor Puntero a char que contiene la dirección de comienzo de un vector con los flags de penalización de cada jugador por flor mal cantada
* \param [in] *cantobienflor Puntero a char que contiene la dirección de comienzo de un vector con los flags que indican si un jugador decidió bien en cantar o no una flor
* \param [in] *cartasjugadastruco Puntero a char que contiene la dirección de comienzo de un vector con las cartas jugadas por cada jugador en una baza
* \param [in] *jugcantoenvido Puntero a char que contiene la dirección de comienzo de un vector con los flags que indican si un jugador cantó en el envido
* \param [in] *mazo Puntero a unsigned char que contiene la dirección de comienzo de un vector con los flags que indican si un jugador se fue al mazo
* \param [in] **ordencartasjugadas Puntero a puntero unsigned char que contiene la dirección de comienzo de una matriz con los daatos de las cartas jugadas por cada jugador y en qué orden (la primer carta jugada estará en la posición 0)
* \param [in] jugadoresporequipo Indica cuántos jugadores hay por equipo
* \param [in] hayflor Indica si se juega con flor o no
* \param [in] estilo Indica si se juega una mano redonda o un pica-pica
* \param [in] *eqganaprimera Puntero con el dato del equipo que ganó la primera
* \param [in] *eqganasegunda Puntero con el dato del equipo que ganó la segunda
* \param [in] *floresnegadaseq1 Puntero con el dato de las flores negadas o mal cantadas por el equipo 1
* \param [in] *floresnegadaseq2 Puntero con el dato de las flores negadas o mal cantadas por el equipo 2
* \param [in] *puntosprimera Puntero con el dato de los puntos obtenidos en la primera
* \param [in] *puntossegunda Puntero con el dato de los puntos obtenidos en la segunda
* \param [in] puntoseq1 Puntos obtenidos por el equipo 1
* \param [in] puntoseq2 Puntos obtenidos por el equipo 2
*******************************************************/
void juegamano (baraja_t(*cartas)[10],baraja_t(*cartasrepartidas)[3],unsigned char(*acciones)[6],unsigned char mano,char *tantoenvido,char *tantoflor,char *penalizacionflor,char *cantobienflor,char *cartasjugadastruco,char *jugcantoenvido,unsigned char *mazo,unsigned char(*ordencartasjugadas)[3],unsigned char(*valorcartaparasegunda)[10],unsigned char jugadoresporequipo,unsigned char hayflor,unsigned char estilo,unsigned char *eqganaprimera,unsigned char *eqganasegunda,unsigned char *floresnegadaseq1,unsigned char *floresnegadaseq2,unsigned char *puntosprimera,unsigned char *puntossegunda,unsigned char puntoseq1,unsigned char puntoseq2)
{
    unsigned char i,j,k;
    unsigned char maxeq1,maxeq2,ganabaza;
    unsigned char flag,n,malcanto,jugganaprimera;
    char max,maxtanto;
    int opcion,opcvalida,naipe,tanto;
    unsigned char palo,valida;
    unsigned char equltimaflor,eqachico,eqcantotruco,cantotruco,cantoenvido,cantoflor;
    unsigned char floresbiencantadas;
    unsigned char enmazo,enmazoeq1,enmazoeq2,juega;
    unsigned char sejuegaprimera,sejuegasegunda,ultimoenjugarcarta;
    char mensaje[LARGOMSG+1];
    unsigned char baza[3],bazaseq1,bazaseq2,bazasjugadas;
    unsigned char bazaterminada,senal;
    juega=mano-JUG1;
    *puntosprimera=0;
    *puntossegunda=1;
    bazaseq1=bazaseq2=bazasjugadas=0;
    *eqganaprimera=*eqganasegunda=NO;
    enmazo=enmazoeq1=enmazoeq2=0;
    sejuegaprimera=sejuegasegunda=NO;
    ultimoenjugarcarta=NADIE;
    cantotruco=cantoenvido=cantoflor=NO;
    *eqganaprimera=eqcantotruco=NADIE;
    maxtanto=-1;
    floresbiencantadas=0;
    *floresnegadaseq1=*floresnegadaseq2=0;
    malcanto=NO;
    senal=0;
    for(i=0;i<3;i++)
    {
        baza[i]=PARDA;
    }
    while(enmazo<2*jugadoresporequipo)//Hacer función de juego
    {
        printf("Opciones para jugador %d:\n",juega+1);
        for(n=JUGARCARTA;n<=NADA;n++)
        {
            if(acciones[n-JUGARCARTA][juega]==SI)
            {
                printf("%d: ",n);
                switch(n)
                {
                    case JUGARCARTA:
                        printf("Jugar carta\n");
                        break;
                    case ENVIDO:
                        printf("Envido\n");
                        break;
                    case REALENVIDO:
                        printf("Real envido\n");
                        break;
                    case FALTAENVIDO:
                        printf("Falta envido\n");
                        break;
                    case FLOR:
                        printf("Flor\n");
                        break;
                    case CONTRAFLOR:
                        printf("Contraflor\n");
                        break;
                    case CONTRAFLORALRESTO:
                        printf("Contraflor al resto\n");
                        break;
                    case TRUCO:
                        printf("Truco\n");
                        break;
                    case QUIERO:
                        printf("Quiero\n");
                        break;
                    case NOQUIERO:
                        printf("No quiero\n");
                        break;
                    case CONFLORMEACHICO:
                        printf("Con flor me achico\n");
                        break;
                    case CANTARTANTO:
                        printf("Cantar tanto\n");
                        break;
                    case QUIERORETRUCO:
                        printf("Quiero retruco\n");
                        break;
                    case QUIEROVALECUATRO:
                        printf("Quiero vale cuatro\n");
                        break;
                    case ALMAZO:
                        printf("Irse al mazo\n");
                        break;
                    case CHATTODOS:
                        printf("Hablarle a todos\n");
                        break;
                    case CHATEQUIPO:
                        printf("Hablarle al equipo\n");
                        break;
                    case NADA:
                        printf("No hacer nada\n");
                        break;
                    default:
                        break;
                }
            }
        }
        opcvalida=NOVALE;
        do
        {
            printf("Opción elegida: ");
            scanf("%d",&opcion);
            for(k=JUGARCARTA;k<=NADA && opcvalida==NOVALE;k++)
            {
                if(opcion==k)
                {
                    opcvalida=opcion;
                }
            }
            if(opcvalida==NOVALE)
            {
                printf("Opción no válida\n");
            }
            else if(acciones[opcvalida-JUGARCARTA][juega]==NO)
            {
                printf("Opción no válida\n");
                opcvalida=NOVALE;
            }
        } while(opcvalida==NOVALE);
        switch(opcvalida)
        {
            case JUGARCARTA:
                do
                {
                    valida=CARTANOVALIDA;
                    printf("Carta a jugar: ");
                    scanf("%d",&naipe);
                    if(naipe<1 || naipe>3)
                    {
                        printf("Carta no válida\n");
                    }
                    else
                    {
                        valida=CARTAVALIDA;
                        for(i=0;i<3 && ordencartasjugadas[juega][i]!=0;i++)
                        {
                            if(naipe==ordencartasjugadas[juega][i])
                            {
                                valida=CARTANOVALIDA;
                                printf("Ya jugó esa carta\n");
                            }
                        }
                        if(valida==CARTAVALIDA)
                        {
                            ordencartasjugadas[juega][i]=naipe;
                            flag=0;
                            for(i=BASTO;i<=ORO && flag==0;i++)
                            {
                                for(j=0;j<10 && flag==0;j++)
                                {
                                    if(cartasrepartidas[juega][naipe-1]==cartas[i-BASTO][j])
                                    {
                                        flag=1;
                                        cartasjugadastruco[juega]=valorcartaparasegunda[i-BASTO][j];
                                    }
                                }
                            }
                        }
                    }
                } while(valida==CARTANOVALIDA);
                if(sejuegasegunda==NO)
                {
                    sejuegasegunda=SI;
                }
                ultimoenjugarcarta=juega;
                printf("%d juega el ",juega+1);
                printf("%d de ",cartasrepartidas[juega][naipe-1]%FACTOR);
                palo=cartasrepartidas[juega][naipe-1]/FACTOR;
                switch(palo)
                {
                case BASTO:
                    printf("basto\n");
                    break;
                case COPA:
                    printf("copa\n");
                    break;
                case ESPADA:
                    printf("espada\n");
                    break;
                case ORO:
                    printf("oro\n");
                    break;
                default:
                    break;
                }
                if(ordencartasjugadas[juega][0]*ordencartasjugadas[juega][1]*ordencartasjugadas[juega][2]!=0)
                {
                    acciones[JUGARCARTA-JUGARCARTA][juega]=NO;
                }
                if(hayflor==SI)
                {
                    if(tantoflor[juega]!=-1)
                    {
                        if(penalizacionflor[juega]==NO && cantobienflor[juega]==NO && ordencartasjugadas[juega][1]<=VALORTRUCO4)
                        {
                            penalizacionflor[juega]=SI;
                            if(juega%2==EQ1%2)
                            {
                                (*floresnegadaseq1)++;
                            }
                            else
                            {
                                (*floresnegadaseq2)++;
                            }
                        }
                    }
                    else if(cantobienflor[juega]==NO)
                    {
                        cantobienflor[juega]=SI;
                    }
                    for(j=FLOR;j<=CONTRAFLORALRESTO;j++)
                    {
                        acciones[j-JUGARCARTA][juega]=NO;
                    }
                }
                senal=0;
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                {
                    if(cartasjugadastruco[i]<=VALORTRUCO4)
                    {
                        senal=1;
                    }
                }
                if(senal==0)
                {
                    sejuegaprimera=TERMINO;
                }
                juega++;
                juega%=2*jugadoresporequipo;
                break;
            case ENVIDO:
                printf("%d canta envido\n",juega+1);
                acciones[NADA-JUGARCARTA][juega]=SI;
                if(jugcantoenvido[juega]==NO)
                {
                    jugcantoenvido[juega]=SI;
                }
                if(sejuegaprimera==NO)
                {
                    cantoenvido=ENVIDO;
                    sejuegaprimera=SI;
                    *puntosprimera=1;
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        acciones[ALMAZO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NADA-JUGARCARTA][i-JUG1]=SI;
                        if(juega%2==i%2)
                        {
                            acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                            acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                            acciones[ENVIDO-JUGARCARTA][i-JUG1]=NO;
                            acciones[REALENVIDO-JUGARCARTA][i-JUG1]=NO;
                            acciones[FALTAENVIDO-JUGARCARTA][i-JUG1]=NO;
                        }
                        else
                        {
                            acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                            acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                            acciones[ENVIDO-JUGARCARTA][i-JUG1]=SI;
                            acciones[REALENVIDO-JUGARCARTA][i-JUG1]=SI;
                            acciones[FALTAENVIDO-JUGARCARTA][i-JUG1]=SI;
                            acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                            acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                            acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                        }
                    }
                }
                else
                {
                    cantoenvido=ENVIDOENVIDO;
                    *puntosprimera=2;
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        acciones[ALMAZO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NADA-JUGARCARTA][i-JUG1]=SI;
                        if(juega%2==i%2)
                        {
                            acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                            acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                            acciones[ENVIDO-JUGARCARTA][i-JUG1]=NO;
                            acciones[REALENVIDO-JUGARCARTA][i-JUG1]=NO;
                            acciones[FALTAENVIDO-JUGARCARTA][i-JUG1]=NO;
                        }
                        else
                        {
                            acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                            acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                            acciones[ENVIDO-JUGARCARTA][i-JUG1]=NO;
                            acciones[REALENVIDO-JUGARCARTA][i-JUG1]=SI;
                            acciones[FALTAENVIDO-JUGARCARTA][i-JUG1]=NO;
                            acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                            acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                            acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                        }
                    }
                }
                for(j=ENVIDO;j<=CONTRAFLORALRESTO;j++)
                {
                    acciones[j-JUGARCARTA][juega]=NO;
                }
                acciones[CONFLORMEACHICO-JUGARCARTA][juega]=NO;
                if(cantotruco!=NO)
                {
                    if(estilo==REDONDA)
                    {
                        juega++;
                        juega%=2*jugadoresporequipo;
                    }
                    else
                    {
                        juega+=3;
                        juega%=6;
                    }
                }
                break;
            case REALENVIDO:
                printf("%d canta real envido\n",juega+1);
                if(jugcantoenvido[juega]==NO)
                {
                    jugcantoenvido[juega]=SI;
                }
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                {
                    acciones[ALMAZO-JUGARCARTA][i-JUG1]=NO;
                    acciones[NADA-JUGARCARTA][i-JUG1]=SI;
                    if(juega%2==i%2)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[ENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[REALENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[FALTAENVIDO-JUGARCARTA][i-JUG1]=NO;
                    }
                    else
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[ENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[REALENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[FALTAENVIDO-JUGARCARTA][i-JUG1]=SI;
                        acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    }
                }
                if(cantoenvido==ENVIDO)
                {
                    *puntosprimera=2;
                }
                else if(cantoenvido==ENVIDOENVIDO)
                {
                    *puntosprimera=4;
                }
                else if(cantoenvido==NO)
                {
                    sejuegaprimera=SI;
                    *puntosprimera=1;
                }
                cantoenvido=REALENVIDO;
                if(cantotruco!=NO)
                {
                    if(estilo==REDONDA)
                    {
                        juega++;
                        juega%=2*jugadoresporequipo;
                    }
                    else
                    {
                        juega+=3;
                        juega%=6;
                    }
                }
                break;
            case FALTAENVIDO:
                printf("%d canta falta envido\n",juega+1);
                if(jugcantoenvido[juega]==NO)
                {
                    jugcantoenvido[juega]=SI;
                }
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                {
                    acciones[ALMAZO-JUGARCARTA][i-JUG1]=NO;
                    acciones[NADA-JUGARCARTA][i-JUG1]=SI;
                    if(juega%2==i%2)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[ENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[REALENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[FALTAENVIDO-JUGARCARTA][i-JUG1]=NO;
                    }
                    else
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[ENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[REALENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[FALTAENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    }
                }
                if(cantoenvido==ENVIDO)
                {
                    *puntosprimera=2;
                }
                else if(cantoenvido==REALENVIDO)
                {
                    if(*puntosprimera==1)
                    {
                        *puntosprimera=3;
                    }
                    if(*puntosprimera==2)
                    {
                        *puntosprimera=5;
                    }
                    if(*puntosprimera==4)
                    {
                        *puntosprimera=7;
                    }
                }
                else if(cantoenvido==NO)
                {
                    sejuegaprimera=SI;
                    *puntosprimera=1;
                }
                cantoenvido=FALTAENVIDO;
                if(cantotruco!=NO)
                {
                    if(estilo==REDONDA)
                    {
                        juega++;
                        juega%=2*jugadoresporequipo;
                    }
                    else
                    {
                        juega+=3;
                        juega%=6;
                    }
                }
                break;
            case FLOR:
                printf("%d canta flor\n",juega+1);
                acciones[NADA-JUGARCARTA][juega]=SI;
                if(sejuegaprimera==NO)
                {
                    sejuegaprimera=SI;
                }
                cantoenvido=NO;
                if(cantoflor==NO)
                {
                    cantoflor=FLOR;
                }
                acciones[FLOR-JUGARCARTA][juega]=NO;
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                {
                    acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=NO;
                    acciones[ENVIDO-JUGARCARTA][i-JUG1]=NO;
                    acciones[REALENVIDO-JUGARCARTA][i-JUG1]=NO;
                    acciones[FALTAENVIDO-JUGARCARTA][i-JUG1]=NO;
                    if(juega%2!=i%2)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[CONTRAFLOR-JUGARCARTA][i-JUG1]=SI;
                        acciones[CONTRAFLORALRESTO-JUGARCARTA][i-JUG1]=SI;
                        acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    }
                    else
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[CONTRAFLOR-JUGARCARTA][i-JUG1]=NO;
                        acciones[CONTRAFLORALRESTO-JUGARCARTA][i-JUG1]=NO;
                    }
                }
                if(tantoflor[juega]==-1 && penalizacionflor[juega]==NO)
                {
                    penalizacionflor[juega]=SI;
                    if(juega%2==EQ1%2)
                    {
                        (*floresnegadaseq1)++;
                    }
                    else
                    {
                        (*floresnegadaseq2)++;
                    }
                }
                else
                {
                    cantobienflor[juega]=SI;
                    floresbiencantadas++;
                    if(juega%2==EQ1%2)
                    {
                        equltimaflor=EQ1;
                    }
                    else
                    {
                        equltimaflor=EQ2;
                    }
                }
                break;
            case CONTRAFLOR:
                cantoflor=CONTRAFLOR;
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                {
                    if(juega%2!=i%2)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[CONTRAFLOR-JUGARCARTA][i-JUG1]=NO;
                        acciones[CONTRAFLORALRESTO-JUGARCARTA][i-JUG1]=SI;
                        acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    }
                    else
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[CONTRAFLOR-JUGARCARTA][i-JUG1]=NO;
                        acciones[CONTRAFLORALRESTO-JUGARCARTA][i-JUG1]=NO;
                    }
                }
                if(tantoflor[juega]==-1 && penalizacionflor[juega]==NO)
                {
                    penalizacionflor[juega]=SI;
                    if(juega%2==EQ1%2)
                    {
                        (*floresnegadaseq1)++;
                    }
                    else
                    {
                        (*floresnegadaseq2)++;
                    }
                }
                else
                {
                    cantobienflor[juega]=SI;
                    if(floresbiencantadas==1)
                    {
                        floresbiencantadas++;
                    }
                    if(juega%2==EQ1%2)
                    {
                        equltimaflor=EQ1;
                    }
                    else
                    {
                        equltimaflor=EQ2;
                    }
                }
                break;
            case CONTRAFLORALRESTO:
                cantoflor=CONTRAFLORALRESTO;
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                {
                    if(juega%2!=i%2)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[CONTRAFLOR-JUGARCARTA][i-JUG1]=NO;
                        acciones[CONTRAFLORALRESTO-JUGARCARTA][i-JUG1]=NO;
                        acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    }
                    else
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[CONTRAFLOR-JUGARCARTA][i-JUG1]=NO;
                        acciones[CONTRAFLORALRESTO-JUGARCARTA][i-JUG1]=NO;
                    }
                }
                if(tantoflor[juega]==-1 && penalizacionflor[juega]==NO)
                {
                    penalizacionflor[juega]=SI;
                    if(juega%2==EQ1%2)
                    {
                        (*floresnegadaseq1)++;
                    }
                    else
                    {
                        (*floresnegadaseq2)++;
                    }
                }
                else
                {
                    cantobienflor[juega]=SI;
                    if(floresbiencantadas==1)
                    {
                        floresbiencantadas++;
                    }
                    if(juega%2==EQ1%2)
                    {
                        equltimaflor=EQ1;
                    }
                    else
                    {
                        equltimaflor=EQ2;
                    }
                }
                break;
            case TRUCO:
                printf("%d canta truco\n",juega+1);
                sejuegasegunda=SI;
                cantotruco=TRUCO;
                eqcantotruco=juega%2;
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)//Este for puede ir en una función
                {
                    acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=NO;
                    acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                    acciones[NADA-JUGARCARTA][i-JUG1]=SI;
                    if(juega%2!=i%2)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=SI;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    }
                    else
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    }
                }
                if(estilo==REDONDA)
                {
                    juega++;
                    juega%=2*jugadoresporequipo;
                }
                else
                {
                    juega+=3;
                    juega%=6;
                }
                break;
            case QUIERO:
                printf("%d canta quiero\n",juega+1);
                if(cantoenvido!=NO)
                {
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        for(j=JUGARCARTA;j<=ALMAZO;j++)
                        {
                            acciones[j-JUGARCARTA][i-JUG1]=NO;
                        }
                        acciones[CANTARTANTO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NADA-JUGARCARTA][i-JUG1]=SI;
                        acciones[CHATTODOS-JUGARCARTA][i-JUG1]=SI;
                        if(jugadoresporequipo>1)
                        {
                            acciones[CHATEQUIPO-JUGARCARTA][i-JUG1]=SI;
                        }
                    }
                    if(cantoenvido==ENVIDO)
                    {
                        *puntosprimera=2;
                    }
                    else if(cantoenvido==ENVIDOENVIDO)
                    {
                        *puntosprimera=4;
                    }
                    else if(cantoenvido==REALENVIDO)
                    {
                        if(*puntosprimera==1)
                        {
                            *puntosprimera=3;
                        }
                        if(*puntosprimera==2)
                        {
                            *puntosprimera=5;
                        }
                        if(*puntosprimera==4)
                        {
                            *puntosprimera=7;
                        }
                    }
                    else if(cantoenvido==FALTAENVIDO)
                    {
                        if(puntoseq1>puntoseq2)
                        {
                            *puntosprimera=30-puntoseq1;
                        }
                        else
                        {
                            *puntosprimera=30-puntoseq2;
                        }
                    }
                    juega=mano-JUG1;
                    break;
                }
                else if(cantoflor!=NO)
                {
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        for(j=JUGARCARTA;j<=ALMAZO;j++)
                        {
                            acciones[j-JUGARCARTA][i-JUG1]=NO;
                        }
                        acciones[CANTARTANTO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NADA-JUGARCARTA][i-JUG1]=SI;
                        acciones[CHATTODOS-JUGARCARTA][i-JUG1]=SI;
                        if(jugadoresporequipo>1)
                        {
                            acciones[CHATEQUIPO-JUGARCARTA][i-JUG1]=SI;
                        }
                    }
                    if(cantoflor==CONTRAFLORALRESTO)
                    {
                        *puntosprimera=3*floresbiencantadas;
                        if(puntoseq1>puntoseq2)
                        {
                            *puntosprimera=*puntosprimera+30-puntoseq1;
                        }
                        else
                        {
                            *puntosprimera=*puntosprimera+30-puntoseq2;
                        }
                    }
                }
                else if(cantotruco==TRUCO)//Esto puede ir en una función
                {
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=SI;
                        acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                        cantotruco=TRUCOQUERIDO;
                    }
                }
                else if(cantotruco==QUIERORETRUCO)
                {
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=SI;
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                        cantotruco=RETRUCOQUERIDO;
                    }
                }
                else if(cantotruco==QUIEROVALECUATRO)
                {
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=SI;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                        cantotruco=VALECUATROQUERIDO;
                    }
                }
                (*puntossegunda)++;
                if(ultimoenjugarcarta!=NADIE)
                {
                    juega=ultimoenjugarcarta+1;
                    juega%=2*jugadoresporequipo;
                }
                else
                {
                    juega=mano-JUG1;
                }
                break;
            case NOQUIERO:
                printf("%d canta no quiero\n",juega+1);
                if(cantoenvido!=NO)
                {
                    if(cantoenvido==CANTARTANTO)
                    {
                        if(malcanto==SI)
                        {
                            if(*puntosprimera<4)
                            {
                                *puntosprimera=4;
                            }
                            if(jugganaprimera%2==EQ1%2)
                            {
                                *eqganaprimera=EQ2;
                            }
                            else
                            {
                                *eqganaprimera=EQ1;
                            }
                        }
                        else
                        {
                            if(jugganaprimera%2==EQ1%2)
                            {
                                *eqganaprimera=EQ1;
                            }
                            else
                            {
                                *eqganaprimera=EQ2;
                            }
                        }
                    }
                    else
                    {
                        if(juega%2==EQ1%2)
                        {
                            *eqganaprimera=EQ2;
                        }
                        else
                        {
                            *eqganaprimera=EQ1;
                        }
                    }
                    if(ultimoenjugarcarta!=NADIE)
                    {
                        juega=ultimoenjugarcarta+1;
                        juega%=2*jugadoresporequipo;
                    }
                    else
                    {
                        juega=mano-JUG1;
                    }
                    cantoenvido=TERMINO;
                }
                else if(cantoflor!=NO)
                {
                    if(cantoflor==CANTARTANTO)
                    {
                        if(malcanto==NO)
                        {
                            if(jugganaprimera%2==EQ1%2)
                            {
                                *eqganaprimera=EQ1;
                            }
                            else
                            {
                                *eqganaprimera=EQ2;
                            }
                        }
                        else
                        {
                            *puntosprimera=0;
                        }
                    }
                    else if(cantoflor==FLOR)
                    {
                        *eqganaprimera=equltimaflor;
                        *puntosprimera=3*floresbiencantadas;
                        if(floresbiencantadas==0)
                        {
                            *eqganaprimera=NADIE;
                        }
                    }
                    else if(cantoflor==eqachico)
                    {
                        *eqganaprimera=JUG1+(eqachico+1)%2;
                        *puntosprimera=3*floresbiencantadas-2;
                        if(*puntosprimera<4)
                        {
                            *puntosprimera=4;
                        }
                    }
                    cantoflor=TERMINO;
                }
                if(sejuegasegunda==SI)
                {
                    i=juega+1;
                    i%=2*jugadoresporequipo;
                    while(i!=juega)
                    {
                        if(tantoflor[i]!=-1 && penalizacionflor[juega]==NO && cantobienflor[juega]==NO)
                        {
                            penalizacionflor[juega]=SI;
                            if(i%2==EQ1%2)
                            {
                                (*floresnegadaseq1)++;
                            }
                            else
                            {
                                (*floresnegadaseq2)++;
                            }
                        }
                        i++;
                        i%=2*jugadoresporequipo;
                    }
                    if(sejuegaprimera==TERMINO)
                    {
                        sejuegasegunda=TERMINO;
                        if(juega%2==EQ1%2)
                        {
                            bazaseq1=0;
                            bazaseq2=3;
                        }
                        else
                        {
                            bazaseq1=3;
                            bazaseq2=0;
                        }
                    }
                    if(ultimoenjugarcarta!=NADIE)
                    {
                        juega=ultimoenjugarcarta+1;
                        juega%=2*jugadoresporequipo;
                    }
                    else
                    {
                        juega=mano-JUG1;
                    }
                }
                break;
            case CONFLORMEACHICO:
                printf("%d canta con flor me achico\n",juega+1);
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                {
                    for(j=ENVIDO;j<=CONTRAFLORALRESTO;j++)
                    {
                        acciones[j-JUGARCARTA][i-JUG1]=NO;
                    }
                    acciones[CONFLORMEACHICO-JUGARCARTA][i-JUG1]=NO;
                }
                if(juega%2==EQ1%2)
                {
                    eqachico=EQ1;
                    if(tantoflor[juega]!=-1 && penalizacionflor[juega]==NO)
                    {
                        penalizacionflor[juega]=SI;
                        (*floresnegadaseq1)++;
                    }
                }
                else
                {
                    eqachico=EQ2;
                    if(tantoflor[juega]!=-1 && penalizacionflor[juega]==NO)
                    {
                        penalizacionflor[juega]=SI;
                        (*floresnegadaseq2)++;
                    }
                }
                break;
            case CANTARTANTO:
                printf("Indicar tanto: ");
                scanf("%d",&tanto);
                if(cantoenvido!=NO)
                {
                    if(cantoenvido!=CANTARTANTO)
                    {
                        cantoenvido=CANTARTANTO;
                    }
                    if((char)tanto>maxtanto)
                    {
                        maxtanto=(char)tanto;
                        jugganaprimera=juega;
                        if((char)tanto!=tantoenvido[juega])
                        {
                            malcanto=SI;
                        }
                        else
                        {
                            malcanto=NO;
                        }
                    }
                }
                else if(cantoflor!=NO)
                {
                    if(cantoflor!=CANTARTANTO)
                    {
                        cantoflor=CANTARTANTO;
                    }
                    if((char)tanto>maxtanto)
                    {
                        maxtanto=(char)tanto;
                        jugganaprimera=juega;
                        if((char)tanto!=tantoflor[juega])
                        {
                            malcanto=SI;
                            if(juega%2==EQ1%2)
                            {
                                if(penalizacionflor[juega]==NO)
                                {
                                    penalizacionflor[juega]=SI;
                                    (*floresnegadaseq1)++;
                                }
                            }
                            else
                            {
                                if(penalizacionflor[juega]==NO)
                                {
                                    penalizacionflor[juega]=SI;
                                    (*floresnegadaseq2)++;
                                }
                            }
                    }
                    else
                    {
                        malcanto=NO;
                    }
                }
                }
                acciones[CANTARTANTO-JUGARCARTA][juega]=NO;
                senal=0;
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)//Este for puede ir en una función
                {
                    acciones[NADA-JUGARCARTA][i-JUG1]=SI;
                    if(juega%2!=i%2 && acciones[CANTARTANTO-JUGARCARTA][i-JUG1]==SI)
                    {
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                        senal=1;
                    }
                }
                if(senal==0)
                {
                    if(cantoenvido==CANTARTANTO)
                    {
                        cantoenvido=TERMINO;
                        if(malcanto==NO)
                        {
                            if(jugganaprimera%2==EQ1%2)
                            {
                                *eqganaprimera=EQ1;
                            }
                            else
                            {
                                *eqganaprimera=EQ2;
                            }
                        }
                        else
                        {
                            if(jugganaprimera%2==EQ1%2)
                            {
                                *eqganaprimera=EQ2;
                            }
                            else
                            {
                                *eqganaprimera=EQ1;
                            }
                            if(*puntosprimera<4)
                            {
                                *puntosprimera=4;
                            }
                        }
                    }
                    if(cantoflor==CANTARTANTO)
                    {
                        cantoflor=TERMINO;
                        if(jugganaprimera%2==EQ1%2)
                        {
                            *eqganaprimera=EQ1;
                        }
                        else
                        {
                            *eqganaprimera=EQ2;
                        }
                        if(malcanto==SI)
                        {
                            *eqganaprimera=NADIE;
                        }
                    }
                }
                if(estilo==REDONDA)
                {
                    juega++;
                    juega%=2*jugadoresporequipo;
                }
                else
                {
                    juega+=3;
                    juega%=6;
                }
                break;
            case QUIERORETRUCO:
                printf("%d canta quiero retruco\n",juega+1);
                eqcantotruco=juega%2;
                if(cantotruco==TRUCO)
                {
                    (*puntossegunda)++;
                }
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)//Este for puede ir en una función
                {
                    acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                    if(juega%2!=i%2)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=SI;
                    }
                    else
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    }
                }
                cantotruco=QUIERORETRUCO;
                if(estilo==REDONDA)
                {
                    juega++;
                    juega%=2*jugadoresporequipo;
                }
                else
                {
                    juega+=3;
                    juega%=6;
                }
                break;
            case QUIEROVALECUATRO:
                printf("%d canta quiero vale cuatro\n",juega+1);
                eqcantotruco=juega%2;
                if(cantotruco==QUIERORETRUCO)
                {
                    (*puntossegunda)++;
                }
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)//Este for puede ir en una función
                {
                    acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    if(juega%2!=i%2)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                    }
                    else
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                    }
                }
                cantotruco=QUIEROVALECUATRO;
                if(estilo==REDONDA)
                {
                    juega++;
                    juega%=2*jugadoresporequipo;
                }
                else
                {
                    juega+=3;
                    juega%=6;
                }
                break;
            case ALMAZO:
                enmazo++;
                if(juega%2==EQ1%2)
                {
                    enmazoeq1++;
                    if(enmazoeq1==jugadoresporequipo && sejuegasegunda!=TERMINO)
                    {
                        sejuegasegunda=TERMINO;
                        bazaseq2=3;
                        bazaseq1=0;
                    }
                }
                if(juega%2==EQ2%2)
                {
                    enmazoeq2++;
                    if(enmazoeq2==jugadoresporequipo && sejuegasegunda!=TERMINO)
                    {
                        sejuegasegunda=TERMINO;
                        bazaseq1=3;
                        bazaseq2=0;
                    }
                }
                for(j=JUGARCARTA;j<=ALMAZO;j++)
                {
                    acciones[j-JUGARCARTA][juega]=NO;
                }
                cartasjugadastruco[juega]=VALORTRUCO4-1;
                mazo[juega]=SI;
                if(enmazo<2*jugadoresporequipo)
                {
                    if(estilo==REDONDA)
                    {
                        juega++;
                        juega%=2*jugadoresporequipo;
                    }
                    else
                    {
                        juega+=3;
                        juega%=6;
                    }
                }
                break;
            case CHATTODOS:
                printf("Mensaje: ");
                scanf(" %[^\n]",mensaje);//Esto puede ir en una función
                while(myStrlen(mensaje)>LARGOMSG)
                {
                    printf("Mensaje muy largo. Acórtelo\n");
                    printf("Mensaje: ");
                    scanf(" %[^\n]",mensaje);
                }
                printf("%d dice: %s\n",juega,mensaje);
                acciones[NADA-JUGARCARTA][juega]=SI;
                break;
            case CHATEQUIPO:
                printf("Mensaje: ");
                scanf(" %[^\n]",mensaje);//Esto puede ir en una función
                while(myStrlen(mensaje)>LARGOMSG)
                {
                    printf("Mensaje muy largo. Acórtelo\n");
                    printf("Mensaje: ");
                    scanf(" %[^\n]",mensaje);
                }
                printf("%d dice: %s\n",juega,mensaje);
                acciones[NADA-JUGARCARTA][juega]=SI;
                break;
            case NADA:
                if(hayflor==SI)
                {
                    acciones[FLOR-JUGARCARTA][juega]=NO;
                    if(tantoflor[juega]!=-1 && cantobienflor[juega]==NO)
                    {
                        if(juega%2==EQ1%2)
                        {
                            if(penalizacionflor[juega]==NO)
                            {
                                penalizacionflor[juega]=SI;
                                (*floresnegadaseq1)++;
                            }
                        }
                        else
                        {
                            if(penalizacionflor[juega]==NO)
                            {
                                penalizacionflor[juega]=SI;
                                (*floresnegadaseq2)++;
                            }
                        }
                    }
                }
                for(i=0;i<2*jugadoresporequipo;i++)
                {
                    if(juega==mazo[i])
                        cartasjugadastruco[juega]=VALORTRUCO4-1;
                }
                if(estilo==REDONDA)
                {
                    juega++;
                    juega%=2*jugadoresporequipo;
                }
                else
                {
                    juega+=3;
                    juega%=6;
                }
                break;
            default:
                break;
        }
        if(cantoenvido==TERMINO || cantoflor==TERMINO)
        {
            if(cantoenvido==TERMINO)
            {
                cantoenvido=NO;
            }
            else
            {
                cantoflor=NO;
            }
            sejuegaprimera=TERMINO;
            for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
            {
                for(j=ENVIDO;j<=CONTRAFLORALRESTO;j++)
                {
                    acciones[j-JUGARCARTA][i-JUG1]=NO;
                }
                acciones[ALMAZO-JUGARCARTA][i-JUG1]=SI;
                if(cantotruco==NO)
                {
                    acciones[TRUCO-JUGARCARTA][i-JUG1]=SI;
                    acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                    acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                }
                else if(cantotruco==TRUCO)
                {
                    acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    if(eqcantotruco==i%2)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                    }
                    else
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                    }
                }
                else if(cantotruco==TRUCOQUERIDO)
                {
                    acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                    acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    if(eqcantotruco==i%2)
                    {
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                    }
                    else
                    {
                        acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=SI;
                    }
                }
                else if(cantotruco==QUIERORETRUCO)
                {
                    acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                    if(eqcantotruco==i%2)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                    }
                    else
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                    }
                }
                else if(cantotruco==RETRUCOQUERIDO)
                {
                    acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                    acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                    if(eqcantotruco==i%2)
                    {
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    }
                    else
                    {
                        acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=SI;
                    }
                }
                else if(cantotruco==QUIEROVALECUATRO)
                {
                    acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                    if(eqcantotruco==i%2)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                    }
                    else
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=SI;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                    }
                }
                else if(cantotruco==VALECUATROQUERIDO)
                {
                    acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                    acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIERORETRUCO-JUGARCARTA][i-JUG1]=NO;
                    acciones[QUIEROVALECUATRO-JUGARCARTA][i-JUG1]=NO;
                }
                acciones[CONFLORMEACHICO-JUGARCARTA][i-JUG1]=NO;
                acciones[CANTARTANTO-JUGARCARTA][i-JUG1]=NO;
            }
        }
        else
        {
            for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
            {
                if(jugcantoenvido[i-JUG1]==SI)
                {
                    acciones[FLOR-JUGARCARTA][i-JUG1]=NO;
                    acciones[CONTRAFLOR-JUGARCARTA][i-JUG1]=NO;
                    acciones[CONTRAFLORALRESTO-JUGARCARTA][i-JUG1]=NO;
                    acciones[CONFLORMEACHICO-JUGARCARTA][i-JUG1]=NO;
                }
            }
        }
        if(sejuegasegunda==SI)
        {
            bazaterminada=SI;
            for(i=0;i<2*jugadoresporequipo;i++)
            {
                if(cartasjugadastruco[i]==-2)
                {
                    bazaterminada=NO;
                }
            }
            if(bazaterminada==SI)
            {
                max=cartasjugadastruco[0];
                ganabaza=JUG1;
                for(i=1;i<2*jugadoresporequipo;i++)
                {
                    if(cartasjugadastruco[i]>max)
                    {
                        max=cartasjugadastruco[i];
                        ganabaza=i;
                    }
                }
                maxeq1=maxeq2=NO;
                for(i=0;i<2*jugadoresporequipo;i++)
                {
                    if(cartasjugadastruco[i]==max)
                    {
                        if(i%2==EQ1%2)
                        {
                            maxeq1=SI;
                        }
                        else if(i%2==EQ2%2)
                        {
                            maxeq2=SI;
                        }
                    }
                }
                if(maxeq1==SI && maxeq2==NO)
                {
                    bazaseq1++;
                    baza[bazasjugadas]=EQ1;
                }
                if(maxeq2==SI && maxeq1==NO)
                {
                    bazaseq2++;
                    baza[bazasjugadas]=EQ2;
                }
                juega=ganabaza;
                for(i=0;i<2*jugadoresporequipo;i++)
                {
                    cartasjugadastruco[i]=-2;
                }
                bazasjugadas++;
                if(bazasjugadas==3)
                {
                    sejuegasegunda=TERMINO;
                }
            }
            if(bazasjugadas==2)
            {
                if((baza[0]==baza[1] && baza[0]!=PARDA) || (baza[0]!=PARDA && baza[1]==PARDA) || (baza[1]!=PARDA && baza[0]==PARDA))
                {
                    sejuegasegunda=TERMINO;
                    for(i=0;i<2*jugadoresporequipo;i++)
                    {
                        for(j=0;j<14;j++)
                        {
                            acciones[j][i]=NO;
                        }
                        for(j=14;j<18;j++)
                        {
                            acciones[j][i]=SI;
                        }
                    }
                }
            }
        }
        if(sejuegasegunda==TERMINO)
        {
            for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
            {
                for(j=JUGARCARTA;j<=QUIEROVALECUATRO;j++)
                {
                    acciones[j-JUGARCARTA][i-JUG1]=NO;
                }
                if(jugadoresporequipo>1)
                {
                    acciones[CHATEQUIPO-JUGARCARTA][i-JUG1]=NO;
                }
            }
        }
        else
        {
            for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
            {
                if(mazo[i-JUG1]==NO && ordencartasjugadas[juega][0]*ordencartasjugadas[juega][1]*ordencartasjugadas[juega][2]==0)
                {
                    acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=SI;
                }
                else
                {
                    acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=NO;
                }
                if(bazasjugadas>0)
                {
                    for(j=ENVIDO;j<=CONTRAFLORALRESTO;j++)
                    {
                        acciones[j-JUGARCARTA][i-JUG1]=NO;
                    }
                    acciones[CONFLORMEACHICO-JUGARCARTA][i-JUG1]=NO;
                    acciones[CANTARTANTO-JUGARCARTA][i-JUG1]=NO;
                }
            }
        }
    }
    if(bazaseq1>bazaseq2)
        *eqganasegunda=EQ1;
    else if(bazaseq2>bazaseq1)
        *eqganasegunda=EQ2;
    else if(bazaseq1==0)
    {
        if(mano%2==EQ1%2)
            *eqganasegunda=EQ1;
        else if(mano%2==EQ2%2)
            *eqganasegunda=EQ2;
    }
    else if(baza[0]==EQ1)
        *eqganasegunda=EQ1;
    else
        *eqganasegunda=EQ2;
    if(ultimoenjugarcarta==NADIE && *eqganaprimera==NADIE)
    {
        if(cantoflor==NO)
        {
            *puntosprimera=1;
            if(mano%2==EQ1%2)
            {
                *eqganaprimera=EQ2;
            }
            else
            {
                *eqganaprimera=EQ1;
            }
        }
    }
}

/**
******************************************************
*  \fn void informarmano (unsigned char eqganaprimera,unsigned char eqganasegunda,unsigned char floresnegadaseq1,unsigned char floresnegadaseq2,unsigned char puntosprimera,unsigned char puntossegunda,unsigned char *puntoseq1,unsigned char *puntoseq2)
*  \brief Función que inicializa la mano a jugar
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 12/12/2016
* \param [in] eqganaprimera Equipo que ganó la primera
* \param [in] eqganasegunda Equipo que ganó la segunda
* \param [in] floresnegadaseq1 Flores negadas o mal cantadas por el equipo 1
* \param [in] floresnegadaseq2 Flores negadas o mal cantadas por el equipo 2
* \param [in] puntosprimera Puntos obtenidos en la primera
* \param [in] puntossegunda Puntos obtenidos en la segunda
* \param [in] *puntoseq1 Puntero con el dato de los puntos del equipo 1
* \param [in] *puntoseq2 Puntero con el dato de los puntos del equipo 2
*******************************************************/
void informarmano (unsigned char eqganaprimera,unsigned char eqganasegunda,unsigned char floresnegadaseq1,unsigned char floresnegadaseq2,unsigned char puntosprimera,unsigned char puntossegunda,unsigned char *puntoseq1,unsigned char *puntoseq2)
{
    if(eqganaprimera==EQ1)//Puede hacerse una función que calcule el ganador de la "primera"
    {
        *puntoseq1+=puntosprimera;
        printf("Equipo 1 gana %d puntos de la primera\n",puntosprimera);
    }
    else if(eqganaprimera==EQ2)
    {
        *puntoseq2+=puntosprimera;
        printf("Equipo 2 gana %d puntos de la primera\n",puntosprimera);
    }
    if(floresnegadaseq1>0 || floresnegadaseq2>0)
    {
        printf("Hubo %d flores negadas o mal cantadas del equipo 1 y %d del equipo 2\n",floresnegadaseq1,floresnegadaseq2);
        if(floresnegadaseq1>floresnegadaseq2)
        {
            printf("Equipo 2 gana %d puntos\n",3*(floresnegadaseq1-floresnegadaseq2));
            *puntoseq2+=3*(floresnegadaseq1-floresnegadaseq2);
        }
        else if(floresnegadaseq1<floresnegadaseq2)
        {
            printf("Equipo 1 gana %d puntos\n",3*(floresnegadaseq2-floresnegadaseq1));
            *puntoseq1+=3*(floresnegadaseq2-floresnegadaseq1);
        }
        else
        {
            printf("Al haber la misma cantidad, nadie suma puntos\n");
        }
    }
    if(eqganasegunda==EQ1)//Puede hacerse una función que calcule el ganador de la "segunda"
    {
        *puntoseq1+=puntossegunda;
        printf("Equipo 1 gana %d puntos del truco\n",puntossegunda);
    }
    else if(eqganasegunda==EQ2)
    {
        *puntoseq2+=puntossegunda;
        printf("Equipo 2 gana %d puntos del truco\n",puntossegunda);
    }
}

/**
******************************************************
*  \fn void informarpicapica (unsigned char puntoseq1picapica,unsigned char puntoseq2picapica,unsigned char *puntoseq1,unsigned char *puntoseq2)
*  \brief Función que inicializa la mano a jugar
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 12/12/2016
* \param [in] puntoseq1picapica Puntos obtenidos por el equipo 1 en el pica-pica
* \param [in] puntoseq2picapica Puntos obtenidos por el equipo 2 en el pica-pica
* \param [in] *puntoseq1 Puntero con el dato de los puntos del equipo 1
* \param [in] *puntoseq2 Puntero con el dato de los puntos del equipo 2
*******************************************************/
void informarpicapica (unsigned char puntoseq1picapica,unsigned char puntoseq2picapica,unsigned char *puntoseq1,unsigned char *puntoseq2)
{
    printf("Luego del pica-pica, ");
    if(puntoseq1picapica==puntoseq2picapica)
    {
        printf("ambos equipos obtuvieron los %d puntos, por lo que niguno suma\n",puntoseq1picapica);
    }
    else
    {
        printf("el Equipo 1 consiguió %d puntos, mientras que el Equipo 2 obtuvo %d. ",puntoseq1picapica,puntoseq2picapica);
    }
    if(puntoseq1picapica>puntoseq2picapica)
    {
        printf("El Equipo 1 suma %d puntos en el partido\n",puntoseq1picapica-puntoseq2picapica);
        *puntoseq1+=(puntoseq1picapica-puntoseq2picapica);
    }
    else
    {
        printf("El Equipo 2 suma %d puntos en el partido\n",puntoseq2picapica-puntoseq1picapica);
        *puntoseq2+=(puntoseq2picapica-puntoseq1picapica);
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