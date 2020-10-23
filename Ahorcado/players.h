
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

void hardcodeFiles(char ids_file_path[]);
void hardcodeIDsFile(char path[], int mode);
void startup(int* players_amount , int* rounds_amount ,int* lifes_amount,int* process_verifier);
sPlayer* allocatePlayers(int players_amount, int* process_verifier);
void fillPlayers(sPlayer* players, int players_amount, int lifes_amount, int rounds_amount, char id_file_path[], int* process_verifier);
int searchMaxIdFromFile(char path[]);
void gameStage(sPlayer* players, int players_amount, int lifes_amount, int rounds_amount, int* process_verifier);
void displayData(int lifes);
char* gettingTheWord(int* word_length);
char* gettingTheHiddenWord(int* word_length, char word[]);
void gameChoices(sPlayer* player,int* choice,int* character_counter, char* character_guess, char* word_guess, char* character_guessed, char* word, char* word_hidden, int word_length);

// FUNCIONES DE DEBBUGEO
void showProcessVerifier(int process_verifier[], int len);
void showPlayers(sPlayer* players, int players_amount);
void hardcodePlayers(sPlayer* players ,int players_amount);

#endif // PLAYERS_H_INCLUDED
