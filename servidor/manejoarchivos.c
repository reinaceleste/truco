#include "conexion.h"

int comprobarnombre(char *nom)
{
    NODO *h=NULL,*last=NULL;
    NODO aux;
    if(CargarArchivo(PATH_REG,&h,&last)==ERR_FILE)
    {
        perror(PATH_REG);
        return ERR_FILE;
        //Descomentar return si me interesa interrumpir el programa al no poder abrir el archivo
    }
    myStrncpy(aux.dato.user,nom,my_strlen(nom));
    if(BuscarNodo(&h,&aux,&last,SOLOBUSCAR)==ENCONTRO)
    {
        return ERR_NOM;
    }
    else
    {
        return 0;
    }
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
    FILE *fp;
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

int CargarArchivo (char *ruta,NODO **h,NODO **last)
{
    FILE *fp;
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
* \version 1.0
* \date 19/11/2016
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
  int op;
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
        free(aux);
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