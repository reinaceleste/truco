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
* \version 1.3
* \date 12/12/2016
*
*
*******************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"prototipos.h"
int main (int argc,char **argv)
{
    unsigned char acciones[18][6];
    unsigned char i,jugadoresporequipo,cont;
    unsigned char mano=JUG1,manopicapica;
    unsigned char hayflor,haypicapica=NO,estilo=REDONDA;
    unsigned char mostrarcartas;
    unsigned char puntosprimera,puntossegunda;
    unsigned char eqganaprimera,eqganasegunda;
    unsigned char floresnegadaseq1,floresnegadaseq2;
    unsigned char puntoseq1=0,puntoseq2=0,puntoseq1picapica,puntoseq2picapica;
    char tantoenvido[6],tantoflor[6],penalizacionflor[6],cantobienflor[6];
    unsigned char valorcartaparaprimera[4][10]={0},valorcartaparasegunda[4][10]={0};
    baraja_t cartas[4][10],cartasrepartidas[6][3];
    unsigned char mazo[6];
    unsigned char ordencartasjugadas[6][3];
    char cartasjugadastruco[6],jugcantoenvido[6];
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
    printf("Bienvenidos a TrucoC\n");
    printf("\nCantidad de jugadores por equipo = %u\n",jugadoresporequipo);
    printf("\nCargando ...\n");
    configurarcartas(cartas);
    calcularvalorescartas(cartas,valorcartaparaprimera,valorcartaparasegunda);
    printf("\nRepartiendo cartas ...\n\n");
    while(!((puntoseq1>=30 || puntoseq2>=30) && puntoseq1!=puntoseq2))
    {
        inicializaracciones(acciones,jugadoresporequipo,hayflor);
        inicializarmano(tantoenvido,tantoflor,penalizacionflor,cantobienflor,cartasjugadastruco,jugcantoenvido,mazo,ordencartasjugadas,jugadoresporequipo);
        repartircartas(cartas,cartasrepartidas,mano,jugadoresporequipo);
        calculotanto(cartas,cartasrepartidas,valorcartaparaprimera,tantoenvido,tantoflor,jugadoresporequipo,hayflor);
        cont=0;
        mostrarcartas=mano-JUG1;
        while(cont<2*jugadoresporequipo)
        {
            informarcartas(mostrarcartas,cartasrepartidas,hayflor,mano,tantoenvido,tantoflor);
            mostrarcartas++;
            mostrarcartas%=2*jugadoresporequipo;
            cont++;
        }
        if(estilo==REDONDA)
        {
            juegamano(cartas,cartasrepartidas,acciones,mano,tantoenvido,tantoflor,penalizacionflor,cantobienflor,cartasjugadastruco,jugcantoenvido,mazo,ordencartasjugadas,valorcartaparasegunda,jugadoresporequipo,hayflor,estilo,&eqganaprimera,&eqganasegunda,&floresnegadaseq1,&floresnegadaseq2,&puntosprimera,&puntossegunda,puntoseq1,puntoseq2);
            informarmano(eqganaprimera,eqganasegunda,floresnegadaseq1,floresnegadaseq2,puntosprimera,puntossegunda,&puntoseq1,&puntoseq2);
        }
        else
        {
            puntoseq1picapica=puntoseq2picapica=0;
            for(i=0;i<3;i++)
            {
                manopicapica=mano+i;
                juegamano(cartas,cartasrepartidas,acciones,manopicapica,tantoenvido,tantoflor,penalizacionflor,cantobienflor,cartasjugadastruco,jugcantoenvido,mazo,ordencartasjugadas,valorcartaparasegunda,1,hayflor,estilo,&eqganaprimera,&eqganasegunda,&floresnegadaseq1,&floresnegadaseq2,&puntosprimera,&puntossegunda,puntoseq1,puntoseq2);
                informarmano(eqganaprimera,eqganasegunda,floresnegadaseq1,floresnegadaseq2,puntosprimera,puntossegunda,&puntoseq1picapica,&puntoseq2picapica);
            }
            informarpicapica(puntoseq1picapica,puntoseq2picapica,&puntoseq1,&puntoseq2);
        }
        if(haypicapica==SI && (puntoseq1>=5 || puntoseq2>=5) && (puntoseq1<=25 || puntoseq2<=25))
        {
            if(estilo==REDONDA)
            {
                estilo=PICAPICA;
            }
            else
            {
                estilo=REDONDA;
            }
        }
        else
        {
            estilo=REDONDA;
        }
        printf("Resultado:\n\nEquipo 1: %d\nEquipo 2: %d\n\n",puntoseq1,puntoseq2);
        mano++;
        mano%=2*jugadoresporequipo;
        mano+=JUG1;
    }
    return 0;
}