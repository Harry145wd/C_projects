#include "players.h"
#define GOOD 1
#define OKAY 0
#define BAD -1
int startup(int* players_amount , int* rounds_amount ,int* lifes_amount)
{
int ret=BAD;
*players_amount=getInt("Cuantos jugadores tendra esta partida? (1 a 10): ","Por favor introduzca una cantidad valida de jugadores (1 a 10): ",1,10,1);
*rounds_amount=getInt("Cuantas rondas por jugador tendra esta partida? (1 a 5): ","Por favor introduzca una cantidad valida de rondas por jugador (1 a 5): ",1,5,1);
*lifes_amount=getInt("Cuantas vidas tendra cada jugador por ronda? (1 a 3)","Por favor introduzca una cantidad valida de vidas por ronda (1 a 3): ",1,3,1);
ret=GOOD;
return ret;
}

int allocatePlayers(sPlayer* players_pointer, int* players_amount)
{
int ret=BAD;
players_pointer=(sPlayer*)malloc(sizeof(sPlayer)*(*players_amount));
if(players_pointer!=NULL)
    {
    ret=GOOD;
    }
return ret;
}
