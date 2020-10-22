#include "players.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "harryio.h"
#define GOOD 1
#define OKAY 0
#define BAD -1
void startup(int* players_amount , int* rounds_amount ,int* lifes_amount,int* process_verifier)
{
*players_amount=getInt("Cuantos jugadores tendra esta partida? (1 a 10): ","Por favor introduzca una cantidad valida de jugadores (1 a 10): ",1,10,1);
*rounds_amount=getInt("Cuantas rondas por jugador tendra esta partida? (1 a 5): ","Por favor introduzca una cantidad valida de rondas por jugador (1 a 5): ",1,5,1);
*lifes_amount=getInt("Cuantas vidas tendra cada jugador por ronda? (1 a 3): ","Por favor introduzca una cantidad valida de vidas por ronda (1 a 3): ",1,3,1);
*(process_verifier+0)=GOOD;
printf("OKAY \n");
}

sPlayer* allocatePlayers(int players_amount, int* process_verifier)
{
sPlayer* players_pointer=NULL;
if(*(process_verifier+0)==GOOD)
    {
    players_pointer=(sPlayer*)malloc(sizeof(sPlayer)*players_amount);
    if(players_pointer!=NULL)
        {
        *(process_verifier+1)=GOOD;
        printf("OKAY \n");
        }
    }
return players_pointer;
}

void fillPlayers(sPlayer* players, int players_amount, int lifes_amount, int rounds_amount, char id_file_path[], int* process_verifier)
{
if(*(process_verifier+1)==GOOD)
    {
    int i;
    char name[20];
    int id_max=searchMaxIdFromFile(id_file_path);
    for(i=0;i<players_amount;i++)
        {
        printf("Ingrese el nombre del Jugador %d: ",i+1);
        gets(name);
        normalizeAndCapitalize(name);
        strcpy((players+i)->name,name);
        (players+i)->lifes=lifes_amount;
        (players+i)->rounds=rounds_amount;
        (players+i)->word_points=0;
        (players+i)->total_points=0;
        (players+i)->id=id_max+1;
        id_max=(players+i)->id;
        }
    *(process_verifier+2)=GOOD;
    }
}

int searchMaxIdFromFile(char path[])
{
FILE* pFile;
int* id_array=NULL;
int id_max=0;
int ids_amount=0;
int j;
pFile=fopen(path,"rb");
while(!feof(pFile))
    {
    fread(&id_max,sizeof(int),1,pFile);
    ids_amount++;
    }
ids_amount--;
fclose(pFile);
if(ids_amount>0)
    {
    id_array=(int*)malloc(sizeof(int)*ids_amount);
    if(id_array!=NULL)
        {
        fopen(path,"rb");
        for(j=0;j<ids_amount;j++)
            {
            fread(id_array+j,sizeof(int),1,pFile);
            }
        for(j=0;j<ids_amount;j++)
            {
            printf("%d,",*(id_array+j));
            if(*(id_array+j)>id_max || j==0)
                {
                id_max=*(id_array+j);
                }
            }
        printf("\nid maxima: %d\n",id_max);
        }
    }
else
    {
    printf("El archivo de IDs no contiene ningun valor\n");
    }
return id_max;
}
// FUNCIONES DE DEBBUGEO

void showProcessVerifier(int process_verifier[], int len)
{
int i;
printf("|");
for(i=0;i<len;i++)
    {
    printf(" %d|",process_verifier[i]);
    }
printf("\n");
}

void hardcodePlayers(sPlayer* players ,int players_amount)
{
int id[10]={1,2,3,4,5,6,7,8,9,10};
char name[10][20]={"Harry","Priscila","Mariela","Mario","Caffa","Martina","Bianca","Milagros","Lean","Noe"};
int total_points[10]={100,20,40,300,50,20,500,50,60,10};
int lifes[10]={3,2,1,3,2,1,3,2,1,3};
int i;
for(i=0;i<players_amount;i++)
    {
    strcpy((players+i)->name,name[i]);
    (players+i)->id=id[i];
    (players+i)->total_points=total_points[i];
    (players+i)->lifes=lifes[i];
    }
printf("OKAY\n");
}

void hardcodeIDsFile(char path[], int mode)
{
FILE* pFile;
pFile=fopen(path,"wb");
if(pFile!=NULL)
    {
    if(mode==1)
        {
        int id[10]={1,2,3,4,5,6,7,8,9,10};
        int i;
        for(i=0;i<10;i++)
            {
            fwrite(id+i,sizeof(int),1,pFile);
            }
        }
    }
fclose(pFile);
}

void showPlayers(sPlayer* players, int players_amount)
{
int i;
printf("|ID      |NOMBRE         |PUNTOS    |\n");
for(i=0; i<players_amount;i++)
    {
    printf("|%-8d|%-15s|%-10d|\n",(players+i)->id,(players+i)->name,(players+i)->total_points);
    }
}
