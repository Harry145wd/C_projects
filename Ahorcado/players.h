#include <stdio.h>
#include <stdlib.h>
#include "harryio.h"
#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED

typedef struct
{
int id;
char name;
int word_points;
int total_points;
}sPlayer;

int startup(int* players_amount , int* rounds_amount ,int* lifes_amount);
int allocatePlayers(sPlayer* players_pointer, int* players_amount);
#endif // PLAYERS_H_INCLUDED
