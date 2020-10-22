#include <stdio.h>
#include <stdlib.h>
#include "harryio.h"
#include "players.h"
int main()
{
int choice;
int players_amount;
int rounds_amount;
int lifes_amount;
sPlayer* players;
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
