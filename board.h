#ifndef BOARD_H_
#define BOARD_H_

/*
 * Inizializza le strutture dati che rappresentano il tabellone
 * del gioco. Quest'ultimo e' una funzione parziale: 
 *              T : {numeri naturali} ---> {stringhe}
 * dove
 *              T(i) = s
 * se e solo se la casella i del tabellone ha come prova quella
 * descritta da s
 */
void initBoard();

/*
 * aggiunge al tabellone l'associazione: casella numero boxNumber,
 * descrizione description se questa non era gia presente altrimenti
 * termina l'esecuzione del programma informando l'utente con un
 * messagio d'errore. 
 * In altri termini: 
 * 		se (boxNumber, description) non appartiene a T
 * 		allora T diventa T U {(boxNumber, description)}
 */
void addBox(int boxNumber, char *description);

/*
 * cerca nel tabellone la descrizione della casella numero boxNumber
 * Restituisce tale descrizione in caso di successo altrimenti
 * termina l'esecuzione del programma informando  l'utente con un 
 * messagio d'errore.
 * In altri termini:
 * 		se c'e' una stringa s tale che (boxNumber, s) appartiene a T
 *  	allora restituisce s
 *      altrimenti termina l'esecuzione del programma informando
 * 			l'utente con un messagio d'errore.
 */
char *getDescription(int boxNumber);

/*
 * Restituisce il numero totale di caselle contenute nel tabellone. 
 */
int getTotalBoxesNumber();

#endif                          /* BOARD_H_ */
