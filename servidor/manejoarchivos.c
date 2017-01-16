#include "conexion.h"

NODO *h;
FILE *fp;

int comprobarnombre(char *nom)
{
    //NODO *h=NULL,*last=NULL;
    NODO aux,*last=NULL;
    h=NULL;
    if(CargarArchivo(PATH_REG,&h,&last)==ERR_FILE)
    {
        perror(PATH_REG);
        return ERR_FILE;
    }
    myStrncpy(aux.dato.user,nom,my_strlen(nom));
    if(BuscarNodo(&h,&aux,&last,SOLOBUSCAR)==ENCONTRO)
    {
        BorrarLista(&h);
        return ERR_NOM;
    }
    else if(my_strlen(nom)>32)
    {
        BorrarLista(&h);
        return ERR_LONGNOM;
    }
    else
    {
        BorrarLista(&h);
        return 0;
    }
}

int comprobarpass(DATO *usu)
{
    //NODO *h=NULL,*last=NULL;
    NODO aux,*last=NULL;
    h=NULL;
    int res;
    if(CargarArchivo(PATH_REG,&h,&last)==ERR_FILE)
    {
        perror(PATH_REG);
        return ERR_FILE;
    }
    aux.dato=*usu;
    res=BuscarNodo(&h,&aux,&last,BUSCARPASS);
    BorrarLista(&h);
    return res;
}

int validarpass(char *pass)
{
    int i,l,fmayus=0,fminus=0,fnum=0;
    l=my_strlen(pass);
    if(l>16)
    {
        return ERR_16CAR;
    }
    else if(l<8)
    {
        return ERR_8CAR;
    }
    else
    {
        for(i=0;i<l;i++)
        {
            if(*(pass+i)>='A' && *(pass+i)<='Z')
            {
                fmayus=1;
            }
            else if(*(pass+i)>='a' && *(pass+i)<='z')
            {
                fminus=1;
            }
            else if(*(pass+i)>='0' && *(pass+i)<='9')
            {
                fnum=1;
            }
        }
    }
    if(fmayus==0)
    {
        return ERR_MAYUS;
    }
    if(fminus==0)
    {
        return ERR_MINUS;
    }
    if(fnum==0)
    {
        return ERR_NUM;
    }
    return 0;
}

int registrar(DATO *usu)
{
    //FILE *fp;
    if((fp=fopen(PATH_REG,"a+b"))==NULL)
    {
        perror(PATH_REG);
        return ERR_FILE;
    }
    usu->puntos=0;
    fwrite(usu,sizeof(DATO),1,fp);
    fclose(fp);
    return 0;
}

int iniciarsesion(DATO *usu)
{
    //FILE *fp;
    //NODO *h=NULL,*last=NULL;
    NODO aux,*last=NULL;
    h=NULL;
    if(CargarArchivo(PATH_INSES,&h,&last)==ERR_FILE)
    {
        perror(PATH_INSES);
        return ERR_FILE;
    }
    aux.dato=*usu;
    if(BuscarNodo(&h,&aux,&last,SOLOBUSCAR)==ENCONTRO)//Para evitar dos inicios de sesión al mismo tiempo de un mismo usuario
    {
        BorrarLista(&h);
        return ERR_INSES;
    }
    BorrarLista(&h);
    if((fp=fopen(PATH_INSES,"a+b"))==NULL)
    {
        perror(PATH_INSES);
        return ERR_FILE;
    }
    fwrite(usu,sizeof(DATO),1,fp);
    fclose(fp);
    return 0;
}

int ingresolog(DATO *usu,char opflor,int opjug)
{
    //FILE *fp;
    //NODO *h=NULL,*last=NULL;
    NODO aux,*last=NULL;
    h=NULL;
    int i;
    char *archivoslog[6]={LOGS1,LOGN1,LOGS2,LOGN2,LOGS3,LOGN3};
    for(i=0;i<6;i++)
    {
    if(CargarArchivo(archivoslog[i],&h,&last)==ERR_FILE)
    {
        perror(archivoslog[i]);
        return ERR_FILE;
    }
    aux.dato=*usu;
    if(BuscarNodo(&h,&aux,&last,SOLOBUSCAR)==ENCONTRO)//Para evitar dos logs al mismo tiempo de un mismo usuario (debe haber uno solo y no debe aparecer en dos archivos al mismo tiempo)
    {
        BorrarLista(&h);
        return ERR_LOG;
    }
    BorrarLista(&h);
    last=NULL;
    }
    switch(opjug)
    {
        case 1:
            if(opflor=='S')
            {
                if((fp=fopen(LOGS1,"a+b"))==NULL)
                {
                    perror(LOGS1);
                    return ERR_FILE;
                }
            }
            else
            {
                if((fp=fopen(LOGN1,"a+b"))==NULL)
                {
                    perror(LOGN1);
                    return ERR_FILE;
                }
            }
            break;
        case 2:
            if(opflor=='S')
            {
                if((fp=fopen(LOGS2,"a+b"))==NULL)
                {
                    perror(LOGS2);
                    return ERR_FILE;
                }
            }
            else
            {
                if((fp=fopen(LOGN2,"a+b"))==NULL)
                {
                    perror(LOGN2);
                    return ERR_FILE;
                }
            }
            break;
        case 3:
            if(opflor=='S')
            {
                if((fp=fopen(LOGS3,"a+b"))==NULL)
                {
                    perror(LOGS3);
                    return ERR_FILE;
                }
            }
            else
            {
                if((fp=fopen(LOGN3,"a+b"))==NULL)
                {
                    perror(LOGN3);
                    return ERR_FILE;
                }
            }
            break;
    }
    fwrite(usu,sizeof(DATO),1,fp);
    fclose(fp);
    return 0;
}

void salidalog(DATO *usu)
{
    //FILE *fp;
    //NODO *h=NULL,*last=NULL;
    NODO aux,*last=NULL;
    h=NULL;
    int i;
    char *archivoslog[6]={LOGS1,LOGN1,LOGS2,LOGN2,LOGS3,LOGN3};
    aux.dato=*usu;
    for(i=0;i<6;i++)
    {
    if(CargarArchivo(archivoslog[i],&h,&last)==ERR_FILE)
    {
        perror(archivoslog[i]);
        return;
    }
    BuscarNodo(&h,&aux,&last,BUSCARBORRAR);
    GuardarLista(&h,archivoslog[i]);
    BorrarLista(&h);
    last=NULL;
    }
}

void cerrarsesion(DATO *usu)
{
    //NODO *h=NULL,*last=NULL;
    NODO aux,*last=NULL;
    h=NULL;
    if(CargarArchivo(PATH_INSES,&h,&last)==ERR_FILE)
    {
        perror(PATH_INSES);
        return;
    }
    aux.dato=*usu;
    BuscarNodo(&h,&aux,&last,BUSCARBORRAR);
    GuardarLista(&h,PATH_INSES);
    BorrarLista(&h);
    salidalog(usu);
}

int puntuaciones(DATO *usu,char *respuesta)
{
    //NODO *h=NULL,*last=NULL;
    NODO aux,*last=NULL,*aux2;
    h=NULL;
    char buffaux[11];
    int finses=NO,ftop10=NO,i,j;
    if(CargarArchivo(PATH_INSES,&h,&last)==ERR_FILE)
    {
        perror(PATH_INSES);
        return ERR_PUNT;
    }
    aux.dato=*usu;
    if(BuscarNodo(&h,&aux,&last,SOLOBUSCAR)==ENCONTRO)
    {
        finses=SI;
    }
    BorrarLista(&h);
    last=NULL;
    if(CargarArchivo(PATH_REG,&h,&last)==ERR_FILE)
    {
        perror(PATH_REG);
        return ERR_PUNT;
    }
    OrdenarLista(h);
    strcpy(respuesta,"\nPos\tUsuario\tPuntos\n\n");
    for(j=0;j<11;j++)
    {
        buffaux[j]=0;
    }
    for(i=1,aux2=h;aux2!=NULL && i<=10;i++,aux2=aux2->sgte)
    {
        if(ftop10==NO)
        {
            if(myStrncmp(usu->user,aux2->dato.user,my_strlen(aux2->dato.user)==0))
            {
                ftop10=SI;
            }
        }
        mydectostr(i,buffaux);
        strncat(respuesta,buffaux,my_strlen(buffaux));
        for(j=0;j<11;j++)
        {
            buffaux[j]=0;
        }
        strcat(respuesta,"°\t");
        strcat(respuesta,aux2->dato.user);
        strcat(respuesta,"\t");
        mydectostr(aux2->dato.puntos,buffaux);
        strncat(respuesta,buffaux,my_strlen(buffaux));
        for(j=0;j<11;j++)
        {
            buffaux[j]=0;
        }
        strcat(respuesta,"\n");
    }
    if(aux2!=NULL)
    {
        if(finses==SI && ftop10==NO)
        {
            while(myStrncmp(usu->user,aux2->dato.user,my_strlen(aux2->dato.user)))
            {
                aux2=aux2->sgte;
                i++;
            }
            strcat(respuesta,"\n");
            mydectostr(i,buffaux);
            strncat(respuesta,buffaux,my_strlen(buffaux));
            for(j=0;j<11;j++)
            {
                buffaux[j]=0;
            }
            strcat(respuesta,")\t");
            strcat(respuesta,aux2->dato.user);
            strcat(respuesta,"\t");
            mydectostr(aux2->dato.puntos,buffaux);
            strncat(respuesta,buffaux,my_strlen(buffaux));
            for(j=0;j<11;j++)
            {
                buffaux[j]=0;
            }
            strcat(respuesta,"\n");
        }
        else if(finses==NO)
        {
            strcat(respuesta,"\nPara ver su puntuación, inicie sesión\n");
        }
    }
    else
    {
        if(finses==NO)
        {
            strcat(respuesta,"\nPara ver su puntuación, inicie sesión\n");
        }
    }
    BorrarLista(&h);
    return 0;
}

void mydectostr (int num,char *buf)
{
    int i;
    if(num==0)
    {
        buf[0]='0';
        buf[1]=NULLCHAR;
        return;
    }
    for(i=0;num;i++)
    {
        *(buf+i)=(num%10)+'0';
        num/=10;
    }
    *(buf+i)=NULLCHAR;
    stringReverse(buf);
}

/**
******************************************************
*  \fn void stringReverse (char* palabra)
*  \brief Función que recibe la palabra y la invierte
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 28/6/2016
* \param [in] *palabra Palabra a invertir
*******************************************************/
void stringReverse (char* palabra)
{
  int i,largo;
  char aux;
  largo=my_strlen(palabra);
  for (i=0;i<largo/2;i++)
  {
    aux=*(palabra+i);
    *(palabra+i)=*(palabra+largo-1-i);
    *(palabra+largo-1-i)=aux;
  }
}

/**
******************************************************
*  \fn void OrdenarLista (NODO *h)
*  \brief Ordena todos los nodos de la lista a un archivo
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 19/10/2016
* \param [in] *h Recibe dirección del primer nodo de la lista
* \param [in] *orden Recibe la dirección de la función a ejecutar según el criterio de ordenamiento
*******************************************************/
void OrdenarLista (NODO *h)
{
    int marca;
    NODO *aux;
    DATO buford;
    do
    {
        marca=0;
        for(aux=h;aux->sgte!=NULL;aux=aux->sgte)
        {
            if(aux->dato.puntos<aux->sgte->dato.puntos)
            {
                buford=aux->dato;
                aux->dato=aux->sgte->dato;
                aux->sgte->dato=buford;
                marca=1;
            }
        }
    } while (marca);
}

int CargarArchivo (char *ruta,NODO **h,NODO **last)
{
    //FILE *fp;
    NODO *aux;
    DATO buffer;
    if((fp=fopen(ruta,"rb"))==NULL)
    {
        perror(ruta);
        return ERR_FILE;
    }
    else
    {
        PRINTENCABEZADO;
        fread(&buffer,sizeof(DATO),1,fp);
        while(!feof(fp))
        {
            PRINTDATO(buffer);
            if((aux=(NODO*)malloc(sizeof(NODO)))==NULL)
            {
                perror("malloc");
                return -1;
            }
            aux->dato=buffer;
            aux->sgte=NULL;
            AgregarNodoAlFinal(h,aux,last);
            fread(&buffer,sizeof(DATO),1,fp);
        }
        fclose(fp);
    }
    return FILEOK;
}

/**
******************************************************
*  \fn int GuardarLista (NODO **p,char *ruta)
*  \brief Guarda todos los nodos de la lista a un archivo
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 9/10/2016
* \param [in] **p Recibe dirección del primer nodo de la lista
* \param [in] *ruta Nombre del archivo donde se guardan los datos
*******************************************************/
int GuardarLista (NODO **p,char *ruta)
{
    NODO *aux,*aux2;
    //FILE *fp;
    if((fp=fopen(ruta,"w"))==NULL)//w o wt: texto; wb: binario
    {
      perror(ruta);
      return ERR_FILE;
    }
    for(aux=*p;aux!=NULL;aux=aux2)
    {
        fwrite(&(aux->dato),sizeof(aux->dato),1,fp);
        //fprintf(fp,"%s,%s,%s,%hu\n",aux->dato.datosinic.nombre,aux->dato.datosinic.apellido,aux->dato.datosinic.prof,aux->dato.intervencion);
        //GUARDARARCHIVO(aux->dato);
        aux2=aux->sgte;
        free(aux);
    }
    *p=aux;
    fclose(fp);
    return FILEOK;
}

/**
******************************************************
*  \fn void BuscarAgregarNodoAlFinal (NODO **h,NODO *aux,NODO **last)
*  \brief Función que busca un nodo y lo agrega si no lo encuentra
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 19/11/2016
* \param [in] **h Dirección de inicio de la lista
* \param [in] *aux Dirección del nodo a agregar/buscar
*******************************************************/
void BuscarAgregarNodoAlFinal (NODO **h,NODO *aux,NODO **last)
{
  if(BuscarNodo(h,aux,last,BUSCARAGREGAR)==ENCONTRO)
  {
      return;
  }
  else
  {
      aux->dato.puntos=0;
      AgregarNodoAlFinal(h,aux,last);
  }
}

/**
******************************************************
*  \fn int BuscarNodo (NODO **h,NODO *aux,NODO **last,int instruccion)
*  \brief Función que busca un nodo y lo agrega si no lo encuentra
* \author Federico Ariel Marinzalda
* \version 1.3
* \date 6/1/2017
* \param [in] **h Dirección de inicio de la lista
* \param [in] *aux Dirección del nodo a buscar
* \param [in] **last Dirección de fin de la lista
* \param [in] instruccion Acción a realixar al encontrar el nodo
*******************************************************/
int BuscarNodo (NODO **h,NODO *aux,NODO **last,int instruccion)
{
  NODO *comp,*prev;
  UNION datos1,datos2;
  Parsear(aux->dato,&datos2);
  int op,fpass=REVISANDO;
  if(instruccion==SOLOBUSCAR)
  {
      for(comp=(*h);comp!=NULL;comp=comp->sgte)
      {
          if(strcmp(comp->dato.user,aux->dato.user)==0)
          {
              return ENCONTRO;
          }
      }
      return NOENCONTRO;
  }
  if(instruccion==BUSCARPASS)
  {
      for(comp=(*h);comp!=NULL && fpass==REVISANDO;comp=comp->sgte)
      {
          if(strcmp(comp->dato.user,aux->dato.user)==0)
          {
              if(strcmp(comp->dato.password,aux->dato.password)==0)
              {
                return PASS_OK;
              }
              else
              {
                  return ERR_PASS;
              }
          }
      }
      return ERR_PASS;
  }
  for(comp=(*h);comp!=NULL;comp=comp->sgte)
  {
    Parsear(comp->dato,&datos1);
    if(mystructcmp(datos1.parseo,datos2.parseo,sizeof(UNION))==0)//Criterio de búsqueda (puede ser un dato identificatorio; de lo contrario, usar mystructcmp)
    {
        /*if(instruccion==BUSCARAGREGAR)
        {
            //comp->dato.cant++;
            //free(aux);//En caso de encontrar el nodo con los mismos datos, actualizo los datos y borro el nodo pedidio con malloc
        }*/
        /*if(instruccion==SOLOBUSCAR)
        {
            PRINTENCABEZADO;
            PRINTDATO(comp->dato);
        }*/
        if(instruccion==BUSCARBORRAR)
        {
            if(comp==*h)
            {
                *h=(*h)->sgte;
                free(comp);
            }
            else
            {
                prev->sgte=comp->sgte;
                free(comp);
                if(prev->sgte==NULL)
                {
                    *last=prev;
                }
                comp=prev;//Esta línea evita segmentation fault
            }
        }
        else if(instruccion==BUSCARMODIFICAR)
        {
            PREGUNTA3;
            scanf("%d",&op);
            while(op)
            {
                CambiarDato(&(comp->dato),op);//Envío puntero a DATO para no enviar demasiados bytes
                PREGUNTA3;
                scanf("%d",&op);
            }
        }
        return ENCONTRO;
    }
    prev=comp;
  }
  return NOENCONTRO;
}

void AgregarNodoAlFinal (NODO **h,NODO *aux,NODO **last)
{
  if(*h==NULL)
  {
    *h=aux;
  }
  else
  {
    (*last)->sgte=aux;
  }
  *last=aux;
}

void BorrarLista (NODO **p)
{
    NODO *aux,*aux2;
    for(aux=*p;aux!=NULL;aux=aux2)
    {
        aux2=aux->sgte;
        free(aux);
    }
    *p=aux;
}

void CambiarDato (DATO *d,int op)
{
    switch(op)
    {
        case 1:
            PEDIRDATO1((*d));
            break;
        case 2:
            PEDIRDATO2((*d));
            break;
        default:
            break;
    }
}

void Parsear(DATO d,UNION *u)
{
    int i;
    for(i=0;i<sizeof(UNION);i++)
    {
        u->parseo[i]=0;
    }
    //myStrncpy(u->datouni.nombre,d.nombre,my_strlen(u->datouni.nombre));
    myStrncpy(DATO1(u->datouni),DATO1(d),my_strlen(DATO1(d)));
    //myStrncpy(u->datouni.apellido,d.apellido,my_strlen(u->datouni.apellido));
    myStrncpy(DATO2(u->datouni),DATO2(d),my_strlen(DATO2(d)));
    //u->datouni.edad=d.edad;
    DATO3(u->datouni)=DATO3(d);
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
*  \fn int mystructcmp (const char *s1,const char *s2,size_t n)
*  \brief Borra datos repetidos en la lista
* \author Federico Ariel Marinzalda
* \version 1.0
* \date 11/10/2016
* \param [in] *s1 Recibe dirección de la primera estructura
* \param [in] *s2 Recibe dirección de la segunda estructura
* \param [in] n Cantidad de bytes a comparar
* \param [out] res Resultado de la comparación
* \details Valores posibles:
* - 0: Las estructuras son iguales
* - menor a 0: La primer estructura es mayor que la segunda
* - mayor a 0: La primer estructura es menor que la segunda
* \returns Un número entero
*******************************************************/
int mystructcmp (const char *s1,const char *s2,size_t n)
{
  int i,res=0;
  for(i=0;i<n && res==0;i++)
  {
    res=s2[i]-s1[i];
  }
  return res;
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