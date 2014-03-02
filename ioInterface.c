
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "ioInterface.h"

#define LINE_LEN (NUMBER_LEN + NAME_LEN + BOX_LEN + STATE_LEN + 13)
#define NUMBER_LEN 6
#define NAME_LEN 15
#define BOX_LEN 5
#define STATE_LEN 14
#define POS_LEN 10
#define WIN_LEN 14
#define FAIL_LEN 12
#define SCORE_LINE_LENGTH (POS_LEN + WIN_LEN + \
							FAIL_LEN + NAME_LEN + 13)
#define PRINT_LINE(character, output, line_length){\
	int i;\
	fprintf(output, "> ");\
	for (i = 0; i < line_length; i++)\
		fprintf(output, "%c", character);\
	fputc('\n', output);\
}

static FILE *logFile;

static void printGameStatusToFileP(FILE * out)
{
    int i = 1;
    PRINT_LINE('_', out, LINE_LEN);
    fprintf(out, "> | %*s | %*s | %*s | %*s |\n",
            NUMBER_LEN, "number", NAME_LEN, "name", BOX_LEN,
            "box", STATE_LEN, "state");
    PRINT_LINE('-', out, LINE_LEN);
    while (nextPlayer())
        fprintf(out,
                "> | %*d | %*s | %*d | %*s |\n",
                NUMBER_LEN, i++, NAME_LEN, getPlayerName(), BOX_LEN,
                getPlayerBox(), STATE_LEN, getPlayerStateName());
    PRINT_LINE('-', out, LINE_LEN);
}

static void printScoreToFileP(FILE * out)
{
    int position;
    int previous_box;
    int previous_turn;

    PRINT_LINE('_', out, SCORE_LINE_LENGTH);
    fprintf(out, "> | %*s | %*s | %*s | %*s |\n", POS_LEN,
            "posizione", NAME_LEN, "name", WIN_LEN,
            "prove superate", FAIL_LEN, "non superate");
    PRINT_LINE('-', out, SCORE_LINE_LENGTH);

    position = 1;
    previous_box = -1;
    previous_turn = -1;
    while (nextPlayer()) {
        fprintf(out, "> | %*d | %*s | %*d | %*d |\n", POS_LEN,
                position, NAME_LEN, getPlayerName(), WIN_LEN,
                getPlayerWinning(), FAIL_LEN, getPlayerFailure());
        if (getPlayerBox() != previous_box)
            position++;
        else if (getPlayerTurn() != previous_turn)
            position++;
        previous_box = getPlayerBox();
        previous_turn = getPlayerTurn();
    }
    PRINT_LINE('-', out, SCORE_LINE_LENGTH);
}


void printScore()
{
    printMessage("\n\n\nCLASSIFICA: \n\n");
    printScoreToFileP(logFile);
    printScoreToFileP(stdout);
}

void showGame()
{
    printGameStatusToFileP(logFile);
    printGameStatusToFileP(stdout);
}

bool askPlayerResult(int *playerNumber)
{
    char answer;

    do {
        printf("numero del giocatore seguito dall'esito "
               "della prova Y/N: \n");
        while (scanf("%d %c", playerNumber, &answer) != 2)
            scanf("%*[^\n]");
        if (*playerNumber <= 0 || strchr("YyNn", answer) == NULL)
            printf("valori inseriti non validi\n");
    }
    while (*playerNumber <= 0 || strchr("YyNn", answer) == NULL);
    putchar('\n');
    fprintf(logFile, "> inserire il numero del giocatore e"
            " l'esito della prova \n");
    fprintf(logFile, "< giocatore numero %d esito della prova %s\n",
            *playerNumber, (answer == 'Y'
                            || answer ==
                            'y') ? "SUPERATA" : "NON SUPERATA");
    return (answer == 'Y' || answer == 'y');
}

bool nextStep()
{
    char answer;

    do {
        fprintf(stdout, "next step?(Y/N): \n");
        scanf("%c", &answer);
    }
    while (strchr("YyNn", answer) == NULL);
    return (answer == 'Y' || answer == 'y');
}

void printMessage(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    fprintf(logFile, "> ");
    vfprintf(logFile, format, ap);
    va_end(ap);

    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);
}

void printErr(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    fprintf(logFile, "> ");
    vfprintf(logFile, format, ap);
    va_end(ap);

    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
}

void printBoard()
{
    int i;

    fprintf(stdout, "ci sono %d prove\n", getTotalBoxesNumber());
    fprintf(logFile, "> ci sono %d prove\n", getTotalBoxesNumber());
    for (i = 1; i <= getTotalBoxesNumber(); i++) {
        fprintf(stdout, "%3d : %s", i, getDescription(i));
        fprintf(logFile, "> %3d : %s", i, getDescription(i));
    }
}

void closeIoInterface()
{
    if (fclose(logFile) != 0) {
        perror("ERROR: in closing log file");
        exit(EXIT_FAILURE);
    }
}

void initIoInterface(char *logFileName)
{
    if ((logFile = fopen(logFileName, "w")) == NULL) {
        perror("ERROR: unable to open log file");
        exit(EXIT_FAILURE);
    }
}
