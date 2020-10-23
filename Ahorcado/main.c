#include <stdio.h>
#include <stdlib.h>
#include "harryio.h"
#include "players.h"
#define GOOD 1
#define OKAY 0
#define BAD -1
int main()
{
char ids_file_path[]="ids.bin";
char players_file_path[]="players.bin";
hardcodeFiles(ids_file_path,players_file_path);
int choice;
int process_verifier[5]={BAD,BAD,BAD,BAD,BAD};
int players_amount;
int rounds_amount;
int lifes_amount;
sPlayer* players=NULL;
do
    {
    printf("| BIENVENIDOS AL JUEGO DEL AHORCADO |\n");
    printf("| 1.COMENZAR NUEVA PARTIDA          |\n");
    printf("| 2.VER HIGHSCORES                  |\n");
    printf("| 3.VER PLAYERS LOG                 |\n");
    printf("| 4.SALIR                           |\n");
    choice=getInt("| INGRESE SU ELECCION: ","| INGRESE UNA OPCION CORRECTA: ",1,4,1);
    system("cls");
    switch(choice)
        {
        case 1:
            {
            startup(&players_amount,&rounds_amount,&lifes_amount,process_verifier);
            players=allocatePlayers(players_amount,process_verifier);
            fillPlayers(players,players_amount,lifes_amount,rounds_amount,ids_file_path,process_verifier);
            showPlayers(players,players_amount);
            gameStage(players,players_amount,lifes_amount,rounds_amount,process_verifier);
            showPlayers(players,players_amount);
            savePlayersIntoFile(players,players_amount,lifes_amount,rounds_amount,process_verifier,ids_file_path,players_file_path);
            break;
            }
        case 2:
            {
            showPlayersLog(players_file_path,1);
            break;
            }
        case 3:
            {
            showPlayersLog(players_file_path,0);
            break;
            }
        case 4:
            {
            printf("HASTA LA PROXIMA!!!");
            break;
            }
        }
    }while(choice!=4);
}
