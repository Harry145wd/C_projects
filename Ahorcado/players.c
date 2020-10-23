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
system("cls");
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
        system("cls");
        }
    else
        {
        system("cls");
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
    system("cls");
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
            if(*(id_array+j)>id_max || j==0)
                {
                id_max=*(id_array+j);
                }
            }
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
if(*(process_verifier+2)==GOOD)
   {
    int i;
    int j;
    char* word=NULL;
    char* word_hidden=NULL;
    int word_length=50;
    for(i=0;i<rounds_amount;i++)
        {
        for(j=0;j<players_amount;j++)
            {
            int choice;
            int word_score;
            int character_counter=0;
            char character_guess;
            char character_guessed[3]={'\n','\n','\n'};
            printf("Turno de %s:\n",(players+j)->name);
            word=gettingTheWord(&word_length);
            system("cls");
            printf("Turno de %s:\n",(players+j)->name);
            word_score=word_length*10;
            (players+j)->word_points=word_score+10;
            word_hidden=gettingTheHiddenWord(&word_length,word);
            char word_guess[word_length+1];
            do
                {
                switch((players+j)->lifes)
                    {
                     case 0:
                        {
                        displayData(players+j,word_score,word_hidden,character_guessed);
                        (players+j)->lifes--;
                        break;
                        }
                    case 1:
                        {
                        displayData(players+j,word_score,word_hidden,character_guessed);
                        gameChoices(players+j,&choice,&character_counter,&character_guess,word_guess,character_guessed,word,word_hidden,word_length);
                        break;
                        }
                    case 2:
                        {
                        displayData(players+j,word_score,word_hidden,character_guessed);
                        gameChoices(players+j,&choice,&character_counter,&character_guess,word_guess,character_guessed,word,word_hidden,word_length);
                        break;
                        }
                    case 3:
                        {
                        displayData(players+j,word_score,word_hidden,character_guessed);
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
                printf("FELICIDADES %s, GANASTE ESTA RONDA!!!\n",(players+j)->name);
                printf("TU TOTAL DE PUNTOS: %d\n",(players+j)->total_points);
                printf("PUNTOS QUE GANASTE EN ESTA PARTIDA: %d\n",(players+j)->word_points);
                system("pause");
                system("cls");
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
getString(word,"Ingrese/n la palabra que el jugador debe adivinar (NO DEJEN QUE LA VEA): ");
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
        player->word_points=player->word_points-10;
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
        system("cls");
        break;
        }
    case 2:
        {
        getString(word_guess,"Ingrese la palabra: ");
        if(strcmpi(word_guess,word)==0)
            {
            system("cls");
            printf("LA PALABRA INGRESADA ES CORRECTA\n");
            strcpy(word_hidden,word_guess);
            }
        else
            {
            system("cls");
            printf("LA PALABRA INGRESADA ES INCORRECTA, PIERDES ESTA RONDA\n");
            player->lifes=0;
            }
        break;
        }
    case 3:
        {
        system("cls");
        printf("%s abandona esta ronda\n",player->name);
        break;
        }
    }

}

void displayData(sPlayer* player, int word_score, char word_hidden[], char character_guessed[])
{
switch(player->lifes)
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
        printf("LA PALABRA A ADIVINAR ES: %s\n\n",word_hidden);
        printf("Puntaje total de esta palabra: %d\n",word_score);
        printf("Tu puntaje actual: %d\n",player->word_points);
        showCharactersGuessed(character_guessed);
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
        printf("%s\n",word_hidden);
        printf("Puntaje total de esta palabra: %d\n",word_score);
        printf("Tu puntaje actual: %d\n",player->word_points);
        showCharactersGuessed(character_guessed);
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
        printf("%s\n",word_hidden);
        printf("Puntaje total de esta palabra: %d\n",word_score);
        printf("Tu puntaje actual: %d\n",player->word_points);
        showCharactersGuessed(character_guessed);
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

void hardcodeFiles(char ids_file_path[], char players_file_path[])
{
FILE* pFile;
FILE* idFile;
pFile=fopen(ids_file_path,"rb");
if(pFile==NULL)
    {
    hardcodeIDsFile(ids_file_path,0);
    }
else
    {
    fclose(pFile);
    }
idFile=fopen(players_file_path,"rb");
if(idFile==NULL)
    {
    hardcodePlayersFile(players_file_path);
    }
else
    {
    fclose(idFile);
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
    else if(mode==0)
        {
        int id=1;
        fwrite(&id,sizeof(int),1,pFile);
        }
    }
fclose(pFile);
}

void hardcodePlayersFile(char path[])
{
sPlayer player={1,"All Might",300,300,3,5};
FILE* pFile;
pFile=fopen(path,"wb");
if(pFile!=NULL)
    {
    fwrite(&player,sizeof(sPlayer),1,pFile);
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

void showOnePlayer(sPlayer player)
{
printf("|%-8d|%-15s|%-10d|\n", player.id, player.name, player.total_points);
}

void showCharactersGuessed(char character_guessed[])
{
printf("Letras usadas: ");
int i;
for(i=0;i<3;i++)
    {
    if(character_guessed[i]!='\n')
        {
        printf("%c,",character_guessed[i]);
        }
    }
printf("\n");
}

void savePlayersIntoFile(sPlayer* players, int players_amount, int lifes_amount, int rounds_amount, int* process_verifier,char ids_file_path[], char players_file_path[])
{
if(*(process_verifier+3)==GOOD)
    {
    FILE* pFile;
    pFile=fopen(players_file_path,"rb");
    if(pFile!=NULL)
        {
        fclose(pFile);
        pFile=fopen(players_file_path,"ab");
        int i;
        for(i=0;i<players_amount;i++)
            {
            (players)->lifes=lifes_amount;
            (players)->rounds=rounds_amount;
            fwrite(players+i,sizeof(sPlayer),1,pFile);
            }
        }
    fclose(pFile);
    pFile=fopen(ids_file_path,"rb");
    if(pFile!=NULL)
        {
        fclose(pFile);
        pFile=fopen(ids_file_path,"ab");
        int i;
        for(i=0;i<players_amount;i++)
            {
            fwrite(&((players+i)->id),sizeof(int),1,pFile);
            }
        fclose(pFile);
        }
    *(process_verifier+4)=GOOD;
    }
}

void showPlayersLog(char path[], int mode)
{
FILE* pFile;
int counter=0;
int i;
sPlayer* players=NULL;
sPlayer player;
pFile=fopen(path,"rb");
if(pFile!=NULL)
    {
    while(!feof(pFile))
        {
        fread(&player,sizeof(sPlayer),1,pFile);
        counter++;
        }
    counter--;
    fclose(pFile);
    players=(sPlayer*)malloc(sizeof(sPlayer)*counter);
    pFile=fopen(path,"rb");
    if(players!=NULL && pFile!=NULL)
        {
        for(i=0;i<counter;i++)
            {
            fread(players+i,sizeof(sPlayer),1,pFile);
            }
        fclose(pFile);
        if(mode==0)
            {
            showPlayers(players,counter);
            }
        else if(mode==1)
            {
            sortPlayersByScore(players,counter,0);
            printf("         |ID      |NOMBRE         |PUNTOS    |\n");
            for(i=0;i<3&&i<counter;i++)
                {
                printf("NUMERO %1d ",i+1);
                showOnePlayer(*(players+i));
                }
            }
        }
    }
}


void sortPlayersByScore(sPlayer* players,int counter,int mode)
{
int i;
int j;
sPlayer aux_player;
for(i=0;i<counter-1;i++)
    {
    for(j=i+1;j<counter;j++)
        {
        if(mode==0)
            {
            if((players+i)->total_points<(players+j)->total_points)
                {
                aux_player=*(players+i);
                *(players+i)=*(players+j);
                *(players+j)=aux_player;
                }
            }
        else if(mode==1)
            {
            if((players+i)->total_points>(players+j)->total_points)
                {
                aux_player=*(players+i);
                *(players+i)=*(players+j);
                *(players+j)=aux_player;;
                }
            }
        }
    }
}
