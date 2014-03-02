#ifndef PLAYERSMANAGER_H_
#define PLAYERSMANAGER_H_

#include <stdbool.h>

#define ACTIVE 0                /* il concorrente e' correntemente attivo
                                 * e quindi partecipa al gioco */
#define DONE 1                  /* il concorrente ha terminato il gioco */
#define OUT_OF_TURN 2           /* il concorrente deve saltare il turno
                                 * corrente per cui riprendera' a
                                 * partecipare al gico al turno successivo 
                                 */
#define TO_BE_ACTIVATED 3       /* il concorrente ha saltato il turno
                                 * precedente dunque gioca nel turno
                                 * corrente */
#define TEST_PASSED 4           /* il concorrente ha superato la prova */

/*
 * inizializza il gestore dei giocatori 
 */
void initPlayersManager();

/*
 * agggiunge un nuovo giocatore nell'insieme dei giocatori 
 */
void addPlayer(char *newPlayerName);

/*
 * fornisce un iteratore sulla collezzione dei giocatori. 
 * restutuisce true se e' presente un giocatore non ancora
 * considerato e imposta tale giocatore come parametro implicito dei
 * metodi che agiscono su uno specifico giocatore cioe': 
 * 		void movePlayer(int dice); 
 * 		char *getPlayerName(); 
 * 		char *getPlayerStateName(); 
 * 		int getState(); 
 * 		int getPlayerBox(); 
 * 		int getPlayerTurn(); 
 * 		int getPlayerWinning(); 
 * 		int getPlayerFailure(); 
 * 		void setState(int state, int winTurn); 
 * se tutti i giocatori sono gia stati usati allora restituisce
 * false e agisce in modo che successive chiamate a nextPlayer
 * permettano di esaminare nuovamente tutti i giocatori una e una
 * sola volta.  
 */
bool nextPlayer();

/*
 * muove il giocatore corrente di un numero di casella pari al
 * parametro 
 */
void movePlayer(int dice);

/*
 * restituisce true se tutti i giocatori hanno terminato il gioco; 
 * false altrimenti 
 */
bool allPlayersDone();

/*
 * restituisce il nome del giocatore corrente 
 */
char *getPlayerName();

/*
 * restituisce una stringa che rappresenta lo stato del giocatore
 * corrente 
 */
char *getPlayerStateName();

/*
 * restituisce il numero di giocatori attivi 
 */
int getActivePlayersNumber();

/*
 * restituisce lo stato del giocatore corrente 
 */
int getPlayerState();

/*
 * restituisce la casella del giocatore corrente 
 */
int getPlayerBox();

/*
 * restituisce il turno di vincita del giocatore corrente 
 */
int getPlayerTurn();

/*
 * restituisce il numero di prove vinte del giocatore corrente 
 */
int getPlayerWinning();

/*
 * restituisce il numero di prove perse del giocatore corrente
 */
int getPlayerFailure();

/*
 * imposta lo stato del giocatore corrente a state e in caso il
 * giocatore abbia terminato il gioco memorizza il turno di vincita 
 */
void setPlayerState(int state, int winTurn);

/*
 * imposta il giocatore corrente a quello numero currentPlayer 
 */
void setCurrentPlayer(int currentPlayer);

#endif                          /* PLAYERSMANAGER_H_ */
