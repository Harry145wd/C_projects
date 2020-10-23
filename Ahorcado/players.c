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
    else
        {
        printf("No se pudo reservar memoria para esa cantidad de jugadores, intente nuevamente\n");
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

void gameStage(sPlayer* players, int players_amount, int lifes_amount, int rounds_amount, int* process_verifier)
{
if(*(process_verifier+2)=GOOD)
   {
    int i;
    int j;
    int y;
    char* word=NULL;
    char* word_hidden=NULL;
    int word_length=50;
    for(i=0;i<rounds_amount;i++)
        {
        for(j=0;j<players_amount;j++)
            {
            int choice;
            int character_counter=0;
            char character_guess;
            char character_guessed[3]={'\n','\n','\n'};
            printf("Turno de %s:\n",(players+j)->name);
            word=gettingTheWord(&word_length);
            word_hidden=gettingTheHiddenWord(&word_length,word);
            char word_guess[word_length+1];
            do
                {
                switch((players+j)->lifes)
                    {
                     case 0:
                        {
                        displayData((players+j)->lifes);
                        (players+j)->lifes--;
                        break;
                        }
                    case 1:
                        {
                        displayData((players+j)->lifes);
                        printf("%s\n",word_hidden);
                        printf("Letras usadas: ");
                        for(y=0;y<3;y++)
                            {
                            if(character_guessed[y]!='\n')
                                {
                                printf("%c,",character_guessed[y]);
                                }
                            }
                        printf("\n");
                        gameChoices(players+j,&choice,&character_counter,&character_guess,word_guess,character_guessed,word,word_hidden,word_length);
                        break;
                        }
                    case 2:
                        {
                        displayData((players+j)->lifes);
                        printf("%s\n",word_hidden);
                        printf("Letras usadas: ");
                        for(y=0;y<3;y++)
                            {
                            if(character_guessed[y]!='\n')
                                {
                                printf("%c,",character_guessed[y]);
                                }
                            }
                        printf("\n");
                        gameChoices(players+j,&choice,&character_counter,&character_guess,word_guess,character_guessed,word,word_hidden,word_length);
                        break;
                        }
                    case 3:
                        {
                        displayData((players+j)->lifes);
                        printf("%s\n",word_hidden);
                        printf("Letras usadas: ");
                        for(y=0;y<3;y++)
                            {
                            if(character_guessed[y]!='\n')
                                {
                                printf("%c,",character_guessed[y]);
                                }
                            }
                        printf("\n");
                        gameChoices(players+j,&choice,&character_counter,&character_guess,word_guess,character_guessed,word,word_hidden,word_length);
                        break;
                        }
                    }
                }while((players+j)->lifes>=0 && strcmpi(word,word_hidden)!=0&&choice!=3);
            if((players+j)->lifes<0||choice==3)
                {
                (players+j)->word_points=0;
                }
            else
                {
                printf("FELICIDADES GANASTE ESTA RONDA!!!\nSE SUMARAN TUS PUNTOS :D\n");
                (players+j)->word_points=(word_length*10)-(character_counter*10)+10;
                }
            (players+j)->total_points=(players+j)->total_points+(players+j)->word_points;
            (players+j)->lifes=lifes_amount;
            }
        }
    *(process_verifier+3)=GOOD;
    }
}

char* gettingTheWord(int* word_length)
{
char* word;
 do
    {
    word=(char*)malloc(sizeof(char)*(*word_length));
    }while(word==NULL);
getString(word,"Ingrese/n la palabra que el jugador debe adivinar: ");
*word_length=strlen(word);
word=(char*)realloc(word,sizeof(char)*((*word_length)+1));
return word;
}

char* gettingTheHiddenWord(int* word_length, char word[])
{
char* word_hidden;
word_hidden=(char*)malloc(sizeof(char)*((*word_length)+1));
int i;
for(i=0;i<(*word_length);i++)
    {
    if(word[i]==' ')
        {
        *(word_hidden+i)=' ';
        }
    else
        {
        if(word[i+1]==' '|| word[i-1]==' '|| i==(*word_length)-1 ||i==0)
            {
            *(word_hidden+i)=word[i];
            }
        else
            {
            *(word_hidden+i)='-';
            }
        }
    }
*(word_hidden+(*word_length))='\0';
return word_hidden;
}

void gameChoices(sPlayer* player,int* choice,int* character_counter, char* character_guess, char* word_guess, char* character_guessed, char* word, char* word_hidden, int word_length)
{
printf("1- Adivinar letra\n");
printf("2- Adivinar palabra\n");
printf("3- Abandonar ronda\n");
*choice=getInt("Ingrese su opcion: ","Ingrese una opcion correcta: ",1,3,1);
switch(*choice)
    {
    case 1:
        {
        int counter=0;
        *character_guess=getChar("Ingrese la letra: ", "Ingrese una letra: ",' ',' ',0);
        *character_counter=*character_counter+1;
        int i;
        for(i=0;i<word_length;i++)
            {
            if(*(word+i)==*character_guess)
                {
                *(word_hidden+i)=*character_guess;
                counter++;
                }
            }
        if(counter==0)
            {
            player->lifes--;
            for(i=0;i<3;i++)
                {
                if(*(character_guessed+i)=='\n')
                    {
                    *(character_guessed+i)=*character_guess;
                    break;
                    }
                }
            }
        break;
        }
    case 2:
        {
        getString(word_guess,"Ingrese la palabra: ");
        if(strcmpi(word_guess,word)==0)
            {
            printf("LA PALABRA INGRESADA ES CORRECTA\n");
            strcpy(word_hidden,word_guess);
            }
        else
            {
            printf("LA PALABRA INGRESADA ES INCORRECTA, PIERDES ESTA RONDA\n");
            player->lifes=0;
            }
        break;
        }
    case 3:
        {
        printf("%s abandona esta ronda\n",player->name);
        break;
        }
    }
}

void displayData(int lifes)
{
switch(lifes)
    {
    case 0:
        {
        printf("VIDAS:</3 </3 </3\n");
        printf("  ______         \n");
        printf(" | /    |        \n");
        printf(" |/     O        \n");
        printf(" |    0( )0      \n");
        printf(" |    | | |      \n");
        printf(" |     / \\      \n");
        printf(" |     | |       \n");
        printf(" |     l l       \n");
        printf(" |               \n");
        printf("_A_________      \n");
        printf("AHORCADO\n\n");
        break;
        }
    case 1:
        {
        printf("VIDAS:<3 </3 </3\n");
        printf("  #########  \n");
        printf(" ########### \n");
        printf(" #|   ### |# \n");
        printf(" (  O   O  ) \n");
        printf("  |   C   |  \n");
        printf("  |   _   |  \n");
        printf("   \\_____/  \n\n");
        break;
        }
    case 2:
        {
        printf("VIDAS:<3 <3 </3\n");
        printf("  ######### \n");
        printf(" ########### \n");
        printf(" #|   ### |# \n");
        printf(" (  o   o  ) \n");
        printf("  |   C   |  \n");
        printf("  |  ___  |  \n");
        printf("   \\_____/   \n\n");
        break;
        }
    case 3:
        {
        printf("VIDAS:<3 <3 <3\n");
        printf("  ######### \n");
        printf(" ########### \n");
        printf(" #|   ### |# \n");
        printf(" (  -   -  ) \n");
        printf("  |   C   |  \n");
        printf("  | >---< |  \n");
        printf("   \\_____/   \n\n");
        break;
        }
    }
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

void hardcodeFiles(char ids_file_path[])
{
FILE* pFile;
pFile=fopen(ids_file_path,"rb");
if(pFile==NULL)
    {
    hardcodeIDsFile(ids_file_path,0);
    }
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
