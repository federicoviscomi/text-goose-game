
#include <stdlib.h>
#include <string.h>

#include "playersManager.h"
#include "board.h"
#include "ioInterface.h"

static char *states[5] = {
    "attivo",
    "terminato",
    "fermo un turno",
    "da attivare",
    "prova superata"
};

/* struttura che rappresenta un singolo giocatore */
struct player_t {
    /* nome del giocatore */
    char *name;
    /* caselle in cui si trova il giocatore al turno corrente */
    int box;
    /* stato del giocatore */
    unsigned char state;
    /* turno in cui il giocatore termina il gioco */
    int turn;
    /* numero di prove superate */
    int won;
    /* numero di prove perse */
    int lost;
};


/* giocatori che non hanno terminato il gioco al turno corrente */
static int unDonePlayers;
static int totalPlayersNumber;
/*
 * indice del giocatore corrente che fa da parametro implicito 
 * di metodi che lavorano su un giocatore specifico. questo 
 * valore viene usato nal metodo nextPlayer per implementare un
 * iteratore su tutta la collezzione dei giocatori 
*/
static int current;
static struct player_t **playersArray;

void initPlayersManager(int num)
{
    if ((playersArray =
         (struct player_t **) calloc(num,
                                     sizeof(struct player_t *))) ==
        NULL) {
        printErr("unable to allocate memory for players\n");
        exit(EXIT_FAILURE);
    }
    totalPlayersNumber = num;
    current = -1;
    unDonePlayers = 0;
}


void addPlayer(char *newPlayerName)
{
    struct player_t *newPlayer;
    if ((newPlayer =
         (struct player_t *) calloc(1,
                                    sizeof(struct player_t))) ==
        NULL) {
        printErr("unable to allocate memory for a new player");
        exit(EXIT_FAILURE);
    }
    newPlayer->name = newPlayerName;
    newPlayer->state = ACTIVE;
    playersArray[unDonePlayers] = newPlayer;
    unDonePlayers++;
}

bool nextPlayer()
{
    current++;
    if (current == totalPlayersNumber) {
        current = -1;
        return false;
    }
    return true;
}

int getActivePlayersNumber()
{
    int activePlayer, i;

    for (activePlayer = 0, i = 0; i < totalPlayersNumber; i++)
        if (playersArray[i]->state == ACTIVE)
            activePlayer++;
    return activePlayer;
}

static int comparePlayers(const void *arg1, const void *arg2)
{
    struct player_t *player1 = *((struct player_t **) arg1);
    struct player_t *player2 = *((struct player_t **) arg2);
    if (player1->turn != player2->turn)
        return player1->turn - player2->turn;
    return player2->box - player1->box;
}

void setPlayerState(int state, int turn)
{
    playersArray[current]->state = state;
    if (state == OUT_OF_TURN)
        playersArray[current]->lost++;
    else if (state == TEST_PASSED)
        playersArray[current]->won++;
    else if (state == DONE) {
        unDonePlayers--;
        playersArray[current]->turn = turn;
        if (unDonePlayers == 0)
            qsort(playersArray, totalPlayersNumber,
                  sizeof(struct player_t *), comparePlayers);
    }
}

int getPlayerState()
{
    return playersArray[current]->state;
}

void setCurrentPlayer(int currentPlayer)
{
    current = currentPlayer - 1;
}

void movePlayer(int dice)
{
    playersArray[current]->box += dice;
}

int getPlayerBox()
{
    return playersArray[current]->box;
}

char *getPlayerName()
{
    return playersArray[current]->name;
}

int getPlayerTurn()
{
    return playersArray[current]->turn;
}

int getPlayerWinning()
{
    return playersArray[current]->won;
}

int getPlayerFailure()
{
    return playersArray[current]->lost;
}

bool allPlayersDone()
{
    return unDonePlayers == 0;
}

char *getPlayerStateName()
{
    return states[playersArray[current]->state];
}
