/**
******************************************************
*  \file main.c
*  \brief TP Obligatorio
* \details Juego de truco
* Uso del make
* - Compilar con make new o make tp4_7
* - Ejecutar o compilar y ejecutar en un paso com make run o simplemente make (luego de la ejecución se borrarán los archivos objeto y el ejecutable)
* - Generar y abrir página web con documento Doxygen con make html
* - Borrar web con make no_html
* - Agregar archivos .c, Makefile y Doxyfile al repositorio con make svn
* \author Federico Ariel Marinzalda
* \version 1.2
* \date 3/12/2016
*
*
*******************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"prototipos.h"
int main (int argc,char **argv)
{
    unsigned char i,j,k,jugadoresporequipo,carta,cont;
    unsigned char mano=JUG1,tomacarta,maxeq1,maxeq2,ganabaza;
    unsigned char r,s,aux,aux2,flag,min,n,malcanto=NO,jugganaprimera;
    char max,maxtanto;
    int opcion,opcvalida,naipe,tanto;
    unsigned char hayflor,haypicapica=NO,estilo=REDONDA;
    unsigned char mostrarcartas,palo,valida;
    unsigned char acciones[18][6]={{SI,SI,SI,SI,SI,SI},
                                    {SI,SI,SI,SI,SI,SI},
                                    {SI,SI,SI,SI,SI,SI},
                                    {SI,SI,SI,SI,SI,SI},
                                    {SI,SI,SI,SI,SI,SI},
                                    {NO,NO,NO,NO,NO,NO},
                                    {NO,NO,NO,NO,NO,NO},
                                    {SI,SI,SI,SI,SI,SI},
                                    {NO,NO,NO,NO,NO,NO},
                                    {NO,NO,NO,NO,NO,NO},
                                    {NO,NO,NO,NO,NO,NO},
                                    {NO,NO,NO,NO,NO,NO},
                                    {NO,NO,NO,NO,NO,NO},
                                    {NO,NO,NO,NO,NO,NO},
                                    {SI,SI,SI,SI,SI,SI},
                                    {SI,SI,SI,SI,SI,SI},
                                    {SI,SI,SI,SI,SI,SI},
                                    {NO,NO,NO,NO,NO,NO}};
    unsigned char puntosprimera,puntossegunda,cant;
    unsigned char eqganaprimera,eqganasegunda,equltimaflor,eqachico,eqcantotruco,cantotruco,cantoenvido,cantoflor;
    unsigned char floresbiencantadas,floresnegadaseq1,floresnegadaseq2;
    unsigned char puntoseq1=0,puntoseq2=0,enmazo,enmazoeq1,enmazoeq2,juega;
    unsigned char sejuegaprimera,sejuegasegunda,ultimoenjugarcarta;
    char tantoenvido[6]={-1,-1,-1,-1,-1,-1},tantoflor[6]={-1,-1,-1,-1,-1,-1},penalizacionflor[6]={NO,NO,NO,NO,NO,NO},cantobienflor[6]={NO,NO,NO,NO,NO,NO};
    unsigned char valorcartaparaprimera[4][10]={0},valorcartaparasegunda[4][10]={0};
    char mensaje[LARGOMSG+1];
    baraja_t cartas[4][10],cartasrepartidas[6][3]={0};
    unsigned char baza[3]={PARDA,PARDA,PARDA},bazaseq1,bazaseq2,mazo[6],bazasjugadas;
    unsigned char ordencartasjugadas[6][3]={0},bazaterminada,senal;
    char cartasjugadastruco[6]={-2,-2,-2,-2,-2,-2};
    if(argc<3)
    {
        printf("Error al iniciar el juego. Cerrando ...\n");
        return -1;
    }
    if(*(argv[1])!='S' && *(argv[1])!='N')
    {
        printf("Error al iniciar el juego. Cerrando ...\n");
        return -1;
    }
    if(*(argv[1])=='S')
    {
        hayflor=SI;
    }
    else
    {
        hayflor=NO;
    }
    jugadoresporequipo=(*(argv[2])-'0');
    if(jugadoresporequipo<1 || jugadoresporequipo>3)
    {
        printf("Error al iniciar el juego. Cerrando ...\n");
        return -1;
    }
    if(jugadoresporequipo==3)
    {
        haypicapica=SI;
    }
    else if(jugadoresporequipo==1)
    {
        for(i=JUG1;i<=JUG6;i++)
        {
            acciones[CHATEQUIPO-JUGARCARTA][i-JUG1]=NO;
        }
    }
    if(jugadoresporequipo<3)
    {
        for(i=2*jugadoresporequipo;i<6;i++)
        {
            for(j=0;j<18;j++)
            {
                acciones[j][i+JUG1]=NO;
            }
        }
    }
    printf("Bienvenidos a TrucoC\n");
    printf("\nCantidad de jugadores por equipo = %u\n",jugadoresporequipo);
    printf("\nCargando ...\n");
    configurarcartas(cartas);
    calcularvalorescartas(cartas,valorcartaparaprimera,valorcartaparasegunda);
    printf("\nRepartiendo cartas ...\n\n");
    repartircartas(cartas,cartasrepartidas,mano,jugadoresporequipo);
    calculotanto(cartas,cartasrepartidas,valorcartaparaprimera,tantoenvido,tantoflor,jugadoresporequipo,hayflor);
    cont=0;
    mostrarcartas=mano-JUG1;
    while(cont<2*jugadoresporequipo)
    {
        printf("Jugador %d (Equipo %d)",mostrarcartas+1,mostrarcartas%2+1);
        if(mostrarcartas==mano-JUG1)
            printf(" (es mano)");
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
        mostrarcartas++;
        mostrarcartas%=2*jugadoresporequipo;
        cont++;
    }
    juega=mano-JUG1;
    puntosprimera=0;
    puntossegunda=1;
    bazaseq1=bazaseq2=bazasjugadas=0;
    eqganaprimera=eqganasegunda=NO;
    cant=0;
    enmazo=enmazoeq1=enmazoeq2=0;
    sejuegaprimera=sejuegasegunda=NO;
    ultimoenjugarcarta=NADIE;
    cantotruco=cantoenvido=cantoflor=NO;
    eqganaprimera=eqcantotruco=NADIE;
    maxtanto=-1;
    floresbiencantadas=0;
    floresnegadaseq1=floresnegadaseq2=0;
    senal=0;
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
                    //if(tantoflor[juega]!=-1 && ordencartasjugadas[juega][0]*ordencartasjugadas[juega][1]*ordencartasjugadas[juega][2]==0)
                    {
                        if(penalizacionflor[juega]==NO && cantobienflor[juega]==NO && ordencartasjugadas[juega][1]<=VALORTRUCO4)
                        {
                            penalizacionflor[juega]=SI;
                            if(juega%2==EQ1%2)
                            {
                                floresnegadaseq1++;
                            }
                            else
                            {
                                floresnegadaseq2++;
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
                if(sejuegaprimera==NO)
                {
                    cantoenvido=ENVIDO;
                    sejuegaprimera=SI;
                    puntosprimera=1;
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
                        }
                    }
                }
                else
                {
                    cantoenvido=ENVIDOENVIDO;
                    puntosprimera=2;
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
                    juega++;
                    juega%=2*jugadoresporequipo;
                }
                break;
            case REALENVIDO:
                printf("%d canta real envido\n",juega+1);
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
                    }
                }
                if(cantoenvido==ENVIDO)
                {
                    puntosprimera=2;
                }
                else if(cantoenvido==ENVIDOENVIDO)
                {
                    puntosprimera=4;
                }
                else if(cantoenvido==NO)
                {
                    sejuegaprimera=SI;
                    puntosprimera=1;
                }
                cantoenvido=REALENVIDO;
                if(cantotruco!=NO)
                {
                    juega++;
                    juega%=2*jugadoresporequipo;
                }
                break;
            case FALTAENVIDO:
                printf("%d canta falta envido\n",juega+1);
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
                    }
                }
                if(cantoenvido==ENVIDO)
                {
                    puntosprimera=2;
                }
                else if(cantoenvido==REALENVIDO)
                {
                    if(puntosprimera==1)
                    {
                        puntosprimera=3;
                    }
                    if(puntosprimera==2)
                    {
                        puntosprimera=5;
                    }
                    if(puntosprimera==4)
                    {
                        puntosprimera=7;
                    }
                }
                else if(cantoenvido==NO)
                {
                    sejuegaprimera=SI;
                    puntosprimera=1;
                }
                cantoenvido=FALTAENVIDO;
                if(cantotruco!=NO)
                {
                    juega++;
                    juega%=2*jugadoresporequipo;
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
                        floresnegadaseq1++;
                    }
                    else
                    {
                        floresnegadaseq2++;
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
                        floresnegadaseq1++;
                    }
                    else
                    {
                        floresnegadaseq2++;
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
                        floresnegadaseq1++;
                    }
                    else
                    {
                        floresnegadaseq2++;
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
                juega++;
                juega%=2*jugadoresporequipo;
                break;
            case QUIERO:
                printf("%d canta quiero\n",juega+1);
                if(cantoenvido!=NO)
                {
                    /*for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        acciones[QUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[NOQUIERO-JUGARCARTA][i-JUG1]=NO;
                        acciones[ENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[REALENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[FALTAENVIDO-JUGARCARTA][i-JUG1]=NO;
                        acciones[CANTARTANTO-JUGARCARTA][i-JUG1]=SI;
                    }*/
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
                        puntosprimera=2;
                    }
                    else if(cantoenvido==ENVIDOENVIDO)
                    {
                        puntosprimera=4;
                    }
                    else if(cantoenvido==REALENVIDO)
                    {
                        if(puntosprimera==1)
                        {
                            puntosprimera=3;
                        }
                        if(puntosprimera==2)
                        {
                            puntosprimera=5;
                        }
                        if(puntosprimera==4)
                        {
                            puntosprimera=7;
                        }
                    }
                    else if(cantoenvido==FALTAENVIDO)
                    {
                        if(puntoseq1>puntoseq2)
                        {
                            puntosprimera=30-puntoseq1;
                        }
                        else
                        {
                            puntosprimera=30-puntoseq2;
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
                        puntosprimera=3*floresbiencantadas;
                        if(puntoseq1>puntoseq2)
                        {
                            puntosprimera=puntosprimera+30-puntoseq1;
                        }
                        else
                        {
                            puntosprimera=puntosprimera+30-puntoseq2;
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
                //cantotruco=QUIERO;
                puntossegunda++;
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
                    /*for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        acciones[CANTARTANTO-JUGARCARTA][i-JUG1]=NO;
                    }*/
                    //printf("Aca\n");
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        if(ordencartasjugadas[juega][0]*ordencartasjugadas[juega][1]*ordencartasjugadas[juega][2]==0)
                        {
                            acciones[JUGARCARTA-JUGARCARTA][juega]=SI;
                        }
                        //acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=SI;
                        acciones[ALMAZO-JUGARCARTA][i-JUG1]=SI;
                        /*for(j=0;j<18;j++)
                        {
                            acciones[j][i-JUG1]=NO;
                        }*/
                        for(j=JUGARCARTA+1;j<=CONTRAFLORALRESTO;j++)
                        {
                            acciones[j-JUGARCARTA][i-JUG1]=NO;
                        }
                        /*for(j=TRUCO;j<=QUIEROVALECUATRO;j++)
                        {
                            acciones[j-JUGARCARTA][i-JUG1]=SI;
                        }*/
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
                        //acciones[ALMAZO-JUGARCARTA][i-JUG1]=SI;
                        //acciones[CHATTODOS-JUGARCARTA][i-JUG1]=SI;
                        acciones[CONFLORMEACHICO-JUGARCARTA][i-JUG1]=NO;
                        acciones[CANTARTANTO-JUGARCARTA][i-JUG1]=NO;
                    }
                    /*if(juega%2==EQ1%2)
                    {
                        eqganaprimera=EQ2;
                    }
                    else
                    {
                        eqganaprimera=EQ1;
                    }
                    if(cantoenvido==CANTARTANTO && malcanto==SI)
                    {
                        if(puntosprimera<4)
                        {
                            puntosprimera=4;
                        }
                        
                    }*/
                    if(cantoenvido==CANTARTANTO)
                    {
                        if(malcanto==SI)
                        {
                            if(puntosprimera<4)
                            {
                                puntosprimera=4;
                            }
                            if(jugganaprimera%2==EQ1%2)
                            {
                                eqganaprimera=EQ2;
                            }
                            else
                            {
                                eqganaprimera=EQ1;
                            }
                        }
                        else
                        {
                            if(jugganaprimera%2==EQ1%2)
                            {
                                eqganaprimera=EQ1;
                            }
                            else
                            {
                                eqganaprimera=EQ2;
                            }
                        }
                    }
                    else
                    {
                        if(juega%2==EQ1%2)
                        {
                            eqganaprimera=EQ2;
                        }
                        else
                        {
                            eqganaprimera=EQ1;
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
                    //cantoenvido=NO;
                    cantoenvido=TERMINO;
                }
                else if(cantoflor!=NO)
                {
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        if(ordencartasjugadas[juega][0]*ordencartasjugadas[juega][1]*ordencartasjugadas[juega][2]==0)
                        {
                            acciones[JUGARCARTA-JUGARCARTA][juega]=SI;
                        }
                        //acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=SI;
                        acciones[ALMAZO-JUGARCARTA][i-JUG1]=SI;
                        /*for(j=0;j<18;j++)
                        {
                            acciones[j][i-JUG1]=NO;
                        }*/
                        for(j=JUGARCARTA+1;j<=CONTRAFLORALRESTO;j++)
                        {
                            acciones[j-JUGARCARTA][i-JUG1]=NO;
                        }
                        /*for(j=TRUCO;j<=QUIEROVALECUATRO;j++)
                        {
                            acciones[j-JUGARCARTA][i-JUG1]=SI;
                        }*/
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
                        //acciones[ALMAZO-JUGARCARTA][i-JUG1]=SI;
                        //acciones[CHATTODOS-JUGARCARTA][i-JUG1]=SI;
                        acciones[CONFLORMEACHICO-JUGARCARTA][i-JUG1]=NO;
                        acciones[CANTARTANTO-JUGARCARTA][i-JUG1]=NO;
                    }
                    if(cantoflor==CANTARTANTO)
                    {
                        if(malcanto==NO)
                        {
                            if(jugganaprimera%2==EQ1%2)
                            {
                                eqganaprimera=EQ1;
                            }
                            else
                            {
                                eqganaprimera=EQ2;
                            }
                        }
                        else
                        {
                            puntosprimera=0;
                        }
                    }
                    else if(cantoflor==FLOR)
                    {
                        eqganaprimera=equltimaflor;
                        puntosprimera=3*floresbiencantadas;
                        if(floresbiencantadas==0)
                        {
                            eqganaprimera=NADIE;
                        }
                    }
                    else if(cantoflor==eqachico)
                    {
                        eqganaprimera=JUG1+(eqachico+1)%2;
                        puntosprimera=3*floresbiencantadas-2;
                        if(puntosprimera<4)
                        {
                            puntosprimera=4;
                        }
                    }
                    //cantoflor=NO;
                    cantoflor=TERMINO;
                }
                //if(sejuegasegunda==NO)
                if(sejuegasegunda==SI)
                {
                    //printf("Aca\n");
                    i=juega+1;
                    i%=2*jugadoresporequipo;
                    while(i!=juega)
                    {
                        if(tantoflor[i]!=-1 && penalizacionflor[juega]==NO && cantobienflor[juega]==NO)
                        {
                            penalizacionflor[juega]=SI;
                            if(i%2==EQ1%2)
                            {
                                floresnegadaseq1++;
                            }
                            else
                            {
                                floresnegadaseq2++;
                            }
                        }
                        i++;
                        i%=2*jugadoresporequipo;
                    }
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        if(ordencartasjugadas[juega][0]*ordencartasjugadas[juega][1]*ordencartasjugadas[juega][2]==0)
                        {
                            acciones[JUGARCARTA-JUGARCARTA][juega]=SI;
                        }
                        //acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=SI;
                        acciones[ALMAZO-JUGARCARTA][i-JUG1]=SI;
                        /*for(j=0;j<18;j++)
                        {
                            acciones[j][i-JUG1]=NO;
                        }*/
                        for(j=JUGARCARTA+1;j<=CONTRAFLORALRESTO;j++)
                        {
                            acciones[j-JUGARCARTA][i-JUG1]=NO;
                        }
                        /*for(j=TRUCO;j<=QUIEROVALECUATRO;j++)
                        {
                            acciones[j-JUGARCARTA][i-JUG1]=SI;
                        }*/
                        /*for(j=TRUCO;j<=QUIEROVALECUATRO;j++)
                        {
                            acciones[j-JUGARCARTA][i-JUG1]=SI;
                        }*/
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
                        //acciones[ALMAZO-JUGARCARTA][i-JUG1]=SI;
                        //acciones[CHATTODOS-JUGARCARTA][i-JUG1]=SI;
                        acciones[CONFLORMEACHICO-JUGARCARTA][i-JUG1]=NO;
                        acciones[CANTARTANTO-JUGARCARTA][i-JUG1]=NO;
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
                /*else if(sejuegasegunda==SI)
                {
                    //sejuegasegunda=TERMINO;
                    sejuegasegunda=NO;
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
                        for(j=0;j<18;j++)
                        {
                            acciones[j][i-JUG1]=NO;
                        }
                        for(j=JUGARCARTA;j<=NADA;j++)
                        {
                            acciones[j-JUGARCARTA][i-JUG1]=NO;
                        }
                        acciones[ALMAZO-JUGARCARTA][i-JUG1]=SI;
                        acciones[CHATTODOS-JUGARCARTA][i-JUG1]=SI;
                        acciones[CHATEQUIPO-JUGARCARTA][i-JUG1]=SI;
                    }
                    if(juega%2==EQ1%2)
                    {
                        eqganasegunda=EQ2;
                    }
                    else
                    {
                        eqganasegunda=EQ1;
                    }
                }*/
                /*if(juega%2==EQ1%2)
                {
                    eqganasegunda=EQ2;
                }
                else
                {
                    eqganasegunda=EQ1;
                }*/
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
                        floresnegadaseq1++;
                    }
                }
                else
                {
                    eqachico=EQ2;
                    if(tantoflor[juega]!=-1 && penalizacionflor[juega]==NO)
                    {
                        penalizacionflor[juega]=SI;
                        floresnegadaseq2++;
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
                                    floresnegadaseq1++;
                                }
                            }
                            else
                            {
                                if(penalizacionflor[juega]==NO)
                                {
                                    penalizacionflor[juega]=SI;
                                    floresnegadaseq2++;
                                }
                            }
                    }
                    else
                    {
                        malcanto=NO;
                    }
                }
                }
                //acciones[CANTARTANTO-JUGARCARTA][i-JUG1]=NO;
                acciones[CANTARTANTO-JUGARCARTA][juega]=NO;
                senal=0;
                for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)//Este for puede ir en una función
                {
                    //acciones[JUGARCARTA-JUGARCARTA][i-JUG1]=NO;
                    //acciones[TRUCO-JUGARCARTA][i-JUG1]=NO;
                    acciones[NADA-JUGARCARTA][i-JUG1]=SI;
                    if(juega%2!=i%2 && acciones[CANTARTANTO-JUGARCARTA][i-JUG1]==SI)
                    //if(juega%2!=i%2)
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
                                eqganaprimera=EQ1;
                            }
                            else
                            {
                                eqganaprimera=EQ2;
                            }
                        }
                        else
                        {
                            if(jugganaprimera%2==EQ1%2)
                            {
                                eqganaprimera=EQ2;
                            }
                            else
                            {
                                eqganaprimera=EQ1;
                            }
                            if(puntosprimera<4)
                            {
                                puntosprimera=4;
                            }
                        }
                    }
                    if(cantoflor==CANTARTANTO)
                    {
                        cantoflor=TERMINO;
                        if(jugganaprimera%2==EQ1%2)
                        {
                            eqganaprimera=EQ1;
                        }
                        else
                        {
                            eqganaprimera=EQ2;
                        }
                        if(malcanto==SI)
                        {
                            eqganaprimera=NADIE;
                        }
                    }
                }
                /*for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)//Este for puede ir en una función
                {
                    if(acciones[CANTARTANTO-JUGARCARTA][i-JUG1]==SI && juega%2!=i%2)
                    {
                        //acciones[NOQUIERO-JUGARCARTA][i-JUG1]=SI;
                        senal=1;
                        printf("En el if\n");
                    }
                }
                if(senal==0)
                {
                    if(cantoenvido!=NO)
                    {
                        printf("Entró acá\n");
                        cantoenvido=TERMINO;
                    }
                    else if(cantoflor!=NO)
                    {
                        printf("Entró acá\n");
                        cantoflor=TERMINO;
                    }
                }*/
                /*if(senal==0)
                {
                    for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
                    {
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
                    }
                }*/
                juega++;
                juega%=2*jugadoresporequipo;
                break;
            case QUIERORETRUCO:
                printf("%d canta quiero retruco\n",juega+1);
                eqcantotruco=juega%2;
                if(cantotruco==TRUCO)
                {
                    puntossegunda++;
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
                juega++;
                juega%=2*jugadoresporequipo;
                break;
            case QUIEROVALECUATRO:
                printf("%d canta quiero vale cuatro\n",juega+1);
                eqcantotruco=juega%2;
                if(cantotruco==QUIERORETRUCO)
                {
                    puntossegunda++;
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
                juega++;
                juega%=2*jugadoresporequipo;
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
                for(j=0;j<15;j++)
                {
                    acciones[j][juega]=NO;
                }
                cartasjugadastruco[juega]=VALORTRUCO4-1;
                for(i=0;mazo[i]!=0 && i<2*jugadoresporequipo;i++);
                mazo[i]=juega;
                if(enmazo<2*jugadoresporequipo)
                {
                    juega++;
                    juega%=2*jugadoresporequipo;
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
                //if(cantoflor==FLOR)
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
                                floresnegadaseq1++;
                            }
                        }
                        else
                        {
                            if(penalizacionflor[juega]==NO)
                            {
                                penalizacionflor[juega]=SI;
                                floresnegadaseq2++;
                            }
                        }
                    }
                }
                for(i=0;i<2*jugadoresporequipo;i++)
                {
                    if(juega==mazo[i])
                        cartasjugadastruco[juega]=VALORTRUCO4-1;
                }
                juega++;
                juega%=2*jugadoresporequipo;
                break;
            default:
                break;
        }
        if(cantoenvido==TERMINO)
        {
            cantoenvido=NO;
            sejuegaprimera=TERMINO;
            for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
            {
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
            }
        }
        else if(cantoflor==TERMINO)
        {
            cantoflor=NO;
            sejuegaprimera=TERMINO;
            for(i=JUG1;i<JUG1+2*jugadoresporequipo;i++)
            {
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
                    //sejuegasegunda=NO;
                }
            }
            if(bazasjugadas==2)
            {
                if((baza[0]==baza[1] && baza[0]!=PARDA) || (baza[0]!=PARDA && baza[1]==PARDA) || (baza[1]!=PARDA && baza[0]==PARDA))
                {
                    sejuegasegunda=TERMINO;
                    //sejuegasegunda=NO;
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
    }
    if(bazaseq1>bazaseq2)
        eqganasegunda=EQ1;
    else if(bazaseq2>bazaseq1)
        eqganasegunda=EQ2;
    else if(bazaseq1==0)
    {
        if(mano%2==EQ1%2)
            eqganasegunda=EQ1;
        else if(mano%2==EQ2%2)
            eqganasegunda=EQ2;
    }
    else if(baza[0]==EQ1)
        eqganasegunda=EQ1;
    else
        eqganasegunda=EQ2;
    if(ultimoenjugarcarta==NADIE && eqganaprimera==NADIE)
    {
        if(cantoflor==NO)
        {
            puntosprimera=1;
            if(mano%2==EQ1%2)
            {
                eqganaprimera=EQ2;
            }
            else
            {
                eqganaprimera=EQ1;
            }
        }
    }
    if(eqganaprimera==EQ1)//Puede hacerse una función que calcule el ganador de la "primera"
    {
        puntoseq1+=puntosprimera;
        printf("Equipo 1 gana %d puntos de la primera\n",puntosprimera);
    }
    else if(eqganaprimera==EQ2)
    {
        puntoseq2+=puntosprimera;
        printf("Equipo 2 gana %d puntos de la primera\n",puntosprimera);
    }
    if(floresnegadaseq1>0 || floresnegadaseq2>0)
    {
        printf("Hubo %d flores negadas o mal cantadas del equipo 1 y %d del equipo 2\n",floresnegadaseq1,floresnegadaseq2);
        if(floresnegadaseq1>floresnegadaseq2)
        {
            printf("Equipo 2 gana %d puntos\n",3*(floresnegadaseq1-floresnegadaseq2));
            puntoseq2+=3*(floresnegadaseq1-floresnegadaseq2);
        }
        else if(floresnegadaseq1<floresnegadaseq2)
        {
            printf("Equipo 1 gana %d puntos\n",3*(floresnegadaseq2-floresnegadaseq1));
            puntoseq1+=3*(floresnegadaseq2-floresnegadaseq1);
        }
        else
        {
            printf("Al haber la misma cantidad, nadie suma puntos\n");
        }
    }
    if(eqganasegunda==EQ1)//Puede hacerse una función que calcule el ganador de la "segunda"
    {
        puntoseq1+=puntossegunda;
        printf("Equipo 1 gana %d puntos del truco\n",puntossegunda);
    }
    else if(eqganasegunda==EQ2)
    {
        puntoseq2+=puntossegunda;
        printf("Equipo 2 gana %d puntos del truco\n",puntossegunda);
    }
    return 0;
}