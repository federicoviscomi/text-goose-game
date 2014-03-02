
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "board.h"
#include "ioInterface.h"

#define MAX_BOXES_NUMBER 512

static char *descriptions[MAX_BOXES_NUMBER];
static int totalBoxesNumber;


void initBoard()
{
    memset(descriptions, '\0', sizeof(descriptions));
    totalBoxesNumber = 0;
}

void addBox(int boxNumber, char *description)
{
    int len;

    if (boxNumber > totalBoxesNumber)
        totalBoxesNumber = boxNumber;
    boxNumber--;
    if (boxNumber < 0 || boxNumber >= MAX_BOXES_NUMBER) {
        printErr("box number %d out of bounds [0; %d]\n", boxNumber,
                 MAX_BOXES_NUMBER - 1);
        exit(EXIT_FAILURE);
    }
    for (description++; isspace(*description); description++);
    if ((len = strlen(description)) == 0) {
        printErr("WARINING: empty description\n");
        return;
    }
    if (descriptions[boxNumber] != NULL) {
        printErr("readding description for box number %d\n",
                 boxNumber);
        exit(EXIT_FAILURE);
    }
    if ((descriptions[boxNumber] =
         (char *) malloc(sizeof(char) * (len + 1))) == NULL) {
        printErr("unable to allocate memory for a descritpion\n");
        exit(EXIT_FAILURE);
    }
    strcpy(descriptions[boxNumber], description);
}


char *getDescription(int boxNumber)
{
    if (boxNumber <= 0 || boxNumber > MAX_BOXES_NUMBER) {
        printErr("box number out of index\n");
        exit(EXIT_FAILURE);
    }
    return descriptions[boxNumber - 1] ? descriptions[boxNumber -
                                                      1] :
        "ATTENZIONE: nessuna descrizione associata alla casella\n";
}

int getTotalBoxesNumber()
{
    return totalBoxesNumber;
}
