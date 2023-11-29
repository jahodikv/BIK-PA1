#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

struct Phonebook {
    char phoneNumber[21];
    char name[256];
};

void find(struct Phonebook *book, int bookLength, char *query) {


}

int isNumber(char num[21]) {
    for (int i = 0; num[i] != '\0'; i++) {

        if (num[i] < '0' || num[i] > '9') {
            return 1;
        }
    }
    return 0;

}


int main(void) {


    int bookCapacity = 3;
    int bookLength = 0;


    struct Phonebook *book = (struct Phonebook *) malloc(bookCapacity * sizeof(struct Phonebook));


    char action, phoneNumber[21], name[256], space1, space2, query[223];

    while (scanf("%c", &action) != EOF) {

        if (action == '+') {
            if (scanf("%c%20s%c%255[^\n]", &space1, phoneNumber, &space2, name) != 4) {
                printf("Nespravny vstup1.\n");
                return 0;
            } else {
                if (space1 != ' ' || space2 != ' ') {
                    printf("Nespravny vstup2.\n");
                    return 0;
                }
                int exists = 0;
                int isPhoneNum;
                isPhoneNum = isNumber(phoneNumber);
                if (isPhoneNum == 1 || name[0] == '\0' || name[0] == ' ' || name[strlen(name) - 1] == ' ') {
                    printf("Nespravny vstup3.\n");
                    return 0;
                }
                for (int i = 0; i < bookLength; i++) {
                    if (strcasecmp(book[i].phoneNumber, phoneNumber) == 0 && strcasecmp(book[i].name, name) == 0) {
                        exists = 1;
                        break;
                    }

                }

                if (exists == 1) {
                    printf("Kontakt jiz existuje.\n");
                } else {
                    if (bookLength == bookCapacity) {
                        bookCapacity *= 2;
                        book = (struct Phonebook *) realloc(book, bookCapacity * sizeof(struct Phonebook));
                    }

                    strcpy(book[bookLength].phoneNumber, phoneNumber);
                    strcpy(book[bookLength].name, name);
                    bookLength++;
                    printf("OK\n");

                }
            }
        } else if (action == '?') {
            if (scanf("%c%[^\n]", &space1, query) != 2) {
                printf("Nespravny vstup4.\n");
                return 0;
            } else {
                if (space1 != ' ') {
                    printf("Nespravny vstup5.\n");
                    return 0;
                }

                find(book, bookLength, query);
            }
        } else {
            printf("Nespravny vstup.\n");
            return 0;
        }

        if (scanf("%c", &space1) == EOF) {

            free(book);
            return 0;
        } else if (space1 == '\n') {

            continue;
        } else {
            printf("Nespravny vstup.\n");
            free(book);
            return 0;
        }

    }


    free(book);
    return 0;
}