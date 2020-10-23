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
hardcodeFiles(ids_file_path);
int choice;
int process_verifier[5]={BAD,BAD,BAD,BAD,BAD};
showProcessVerifier(process_verifier,5);
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
            showProcessVerifier(process_verifier,5);
            players=allocatePlayers(players_amount,process_verifier);
            showProcessVerifier(process_verifier,5);
            fillPlayers(players,players_amount,lifes_amount,rounds_amount,ids_file_path,process_verifier);
            showProcessVerifier(process_verifier,5);
            gameStage(players,players_amount,lifes_amount,rounds_amount,process_verifier);
            showProcessVerifier(process_verifier,5);
            showPlayers(players,players_amount);
            break;
            }
        case 2:
            {

            break;
            }
        case 3:
            {

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
