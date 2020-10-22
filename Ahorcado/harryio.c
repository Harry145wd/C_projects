#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "harryio.h"
int getInt(char msj[],char error[],int min, int max, int limit)
{
int num;
int acum=0;
printf("%s",msj);
while(acum!=2)
    {
    acum=0;
    if (scanf("%d",&num)!=1)
        {
        fflush(stdin);
        printf("%s",error);
        }
    else
        {
        acum++;
        if(limit==1)
            {
            if(num<min || num>max)
                {
                fflush(stdin);
                printf("%s",error);
                }
            else
                {
                acum++;
                }
            }
        else
            {
            acum++;
            }
        }
    fflush(stdin);
    }
fflush(stdin);
return num;
}

float getFloat(char msj[],char error[],float min,float max,int limit)
{
float num;
int acum=0;
printf("%s",msj);
while(acum!=2)
    {
    acum=0;
    if(scanf("%f",&num)!=1)
        {
        printf("%s",error);
        }
    else
        {
        acum++;
        if(limit==1)
            {
            if(num<min || num>max)
                {
                fflush(stdin);
                printf("%s",error);
                }
            else
                {
                acum++;
                }
            }
        else
            {
            acum++;
            }
        }
    fflush(stdin);
    }
fflush(stdin);
return num;
}

char getChar(char msj[],char error[],char min,char max,int limite)
{
char caracter;
printf("%s",msj);
scanf("%c",&caracter);
if (limite==1)
    {
    while(caracter<min || caracter>max)
        {
        fflush(stdin);
        printf("%s",error);
        scanf("%c",&caracter);
        }
    }
fflush(stdin);
return caracter;
}

void getString(char string[],char msj[])
{
printf("%s",msj);
gets(string);
fflush(stdin);
}

int normalizeAndCapitalize(char string[])
{
int ret=-1;
int i;
int len=strlen(string);
strlwr(string);
if(strlen>0)
    {
    for(i=0;i<len;i++)
        {
        if(string[i-1]==' '||i==0 )
            {
            string[i]=toupper(string[i]);
            }
        }
    ret=1;
    }
return ret;
}
