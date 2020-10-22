
#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED

typedef struct
{
int id;
char name[20];
int word_points;
int total_points;
int lifes;
int rounds;
}sPlayer;

void hardcodeIDsFile(char path[], int mode);
void startup(int* players_amount , int* rounds_amount ,int* lifes_amount,int* process_verifier);
sPlayer* allocatePlayers(int players_amount, int* process_verifier);
void fillPlayers(sPlayer* players, int players_amount, int lifes_amount, int rounds_amount, char id_file_path[], int* process_verifier);
int searchMaxIdFromFile(char path[]);

// FUNCIONES DE DEBBUGEO
void showProcessVerifier(int process_verifier[], int len);
void showPlayers(sPlayer* players, int players_amount);
void hardcodePlayers(sPlayer* players ,int players_amount);

#endif // PLAYERS_H_INCLUDED
