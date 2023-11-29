#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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

int readInput(struct Phonebook **book, int *bookLength, int *bookCapacity) {

    char action, phoneNumber[21], name[256], space1, space2, query[INT_MAX];

    while (scanf("%c", &action) != EOF) {
        if(action == '\n'){
            continue;
        }
        if (action == '+') {
            if (scanf("%c%20s%c%255s", &space1, phoneNumber, &space2, name) != 4) {
                printf("Nespravny vstup.\n");
                return 0;
            } else {
                if (space1 != ' ' || space2 != ' ') {
                    printf("Nespravny vstup.\n");
                    return 0;
                }
                int exists = 0;
                int isPhoneNum;
                isPhoneNum = isNumber(phoneNumber);
                if (isPhoneNum == 1 || name[0] == '\0' || name[0] == ' ' || name[strlen(name) - 1] == ' ') {
                    printf("Nespravny vstup.\n");
                    return 0;
                }
                for (int i = 0; i < *bookLength; i++) {
                    if (strcmp((*book)[i].phoneNumber, phoneNumber) == 0 && strcmp((*book)[i].name, name) == 0) {
                        exists = 1;
                        break;
                    }

                }

                if (exists == 1) {
                    printf("Kontakt jiz existuje.\n");
                } else {
                    if (*bookLength == *bookCapacity) {
                        *bookCapacity *= 2;
                        *book = realloc(*book, (*bookCapacity) * sizeof(struct Phonebook));


                        strcpy((*book)[*bookLength].phoneNumber, phoneNumber);
                        strcpy((*book)[*bookLength].name, name);
                        (*bookLength)++;

                    }
                }
            }
        }else if (action == '?') {
            if (scanf("%c%[^\n]",&space1, query) != 2) {
                printf("Nespravny vstup.\n");
                return 0;
            } else {
                if(space1!=' '){
                    printf("Nespravny vstup.\n");
                    return 0;
                }

                find(*book, *bookLength, query);
            }
        } else {
            printf("Nespravny vstup.\n");
            return 0;
        }
    }

    return 0;
}


int main(void) {


    int bookCapacity = 5;
    int bookLength = 0;


    struct Phonebook *book = (struct Phonebook *) malloc(bookCapacity * sizeof(struct Phonebook));
    readInput(&book,&bookLength,&bookCapacity);

    free(book);
    return 0;
}