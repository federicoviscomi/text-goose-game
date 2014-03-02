#ifndef IOINTERFACE_H_
#define IOINTERFACE_H_

#include <stdbool.h>
#include <stdio.h>

#include "playersManager.h"
#include "board.h"

/*
 * Chiede all'utente il numero di un giocatore (> 0) e l'esito della
 * sua prova. memorizza tale numero nel valore puntato dal parametro
 * playerNumber e restituisce true in caso il giocatore abbia 
 * superato la prova, false altrimenti. prima di chiedere il numero
 * di un giocatore l'interfaccia deve assicurare di mostrare quale
 * numero corrisponde a quale giocatore.
 */
bool askPlayerResult(int *playerNumber);

/*
 * chiede conferma di prosugire con il turno successivo
 */
bool nextStep();

/*
 * visualizza una descrizione dello stato del gioco
 */
void showGame();

/*
 * visualizza la classifica
 */
void printScore();

/*
 * visualizza un messaggio d'errore secondo il formato format 
 */
void printErr(const char *format, ...);

/*
 * visualizza un messaggio secondo il formato format
 */
void printMessage(const char *format, ...);

/*
 * visualizza una descrizione del tabellone
 */
void printBoard();

/*
 * chiude l'interfaccia di I/O
 */
void closeIoInterface();

/*
 * inizializza l'interfaccia di I/O 
 */
void initIoInterface(char *logFileName);

#endif                          /* IOINTERFACE_H_ */
