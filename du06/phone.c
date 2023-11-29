#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

struct Phonebook {
    char phoneNumber[21];
    char *name;
};

void find(struct Phonebook *book, int bookLength, char *query) {
    int findAlready = 0;

    for (int i = 0; i < bookLength; ++i) {


        if (strstr(book[i].phoneNumber, query) != NULL || strstr(book[i].name, query) != NULL) {

            printf("%s %s\n", book[i].phoneNumber, book[i].name);
            findAlready++;
        }


    }

    if (findAlready > 10) {
        printf("Celkem: %d\n", findAlready);
    }


}

int isNumber(char num[21]) {
    for (int i = 0; num[i] != '\0'; i++) {

        if (num[i] < '0' || num[i] > '9') {
            return 1;
        }
    }
    return 0;

}


int isName(char name[256]) {

    for (int i = 0; name[i] != '\0'; i++) {
        if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ') {
            continue;
        }
        return 1;

    }
    return 0;
}

int main(void) {


    int bookCapacity = 3;
    int bookLength = 0;
    int nameLength = 0;
    int nameCapacity = 3;


    struct Phonebook *book = (struct Phonebook *) malloc(bookCapacity * sizeof(struct Phonebook));


    char action, phoneNumber[21], space1, space2, query[223];
    char *name = (char *) malloc(nameCapacity * sizeof(char));
    while (scanf("%c", &action) != EOF) {

        if (action == '+') {
            if (scanf("%c%20s%c", &space1, phoneNumber, &space2) != 3) {
                printf("Nespravny vstup.\n");
                return 0;
            } else {
                nameLength = 0;
                while (1) {
                    if (nameLength == nameCapacity) {
                        nameCapacity *= 2;
                        name = (char *) realloc(name, nameCapacity * sizeof(char));

                    }
                    int res = scanf("%c", &name[nameLength]);
                    if (res == EOF) {

                        break;

                    } else if (res != 1) {

                        printf("Nespravny vstup.\n");
                        return 0;

                    }
                    if ((name[nameLength] >= 'A' && name[nameLength] <= 'Z') ||
                        (name[nameLength] >= 'a' && name[nameLength] <= 'z') || name[nameLength] == ' ') {
                        nameLength++;
                        continue;
                    } else if (name[nameLength] == '\n') {


                        name[nameLength] == '\0';
                        ungetc('\n', stdin);
                        break;

                    } else {

                        printf("Nespravny vstup.\n");
                        return 0;

                    }


                }


                if (space1 != ' ' || space2 != ' ') {
                    printf("Nespravny vstup.\n");
                    return 0;
                }
                int exists = 0;
                int isPhoneNum;
                //int isValidName;
                //isValidName = isName(name);
                isPhoneNum = isNumber(phoneNumber);

                if (isPhoneNum == 1 || name[0] == '\0' || name[0] == ' ' ||
                    name[strlen(name) - 1] == ' ') {
                    printf("Nespravny vstup.\n");
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
                    book[bookLength].name = (char *) malloc(strlen(name) + 1);
                    strcpy(book[bookLength].name, name);
                    bookLength++;
                    printf("OK\n");

                }
            }
        } else if (action == '?') {
            if (scanf("%c%[^\n]", &space1, query) != 2) {
                printf("Nespravny vstup.\n");
                return 0;
            } else {
                if (space1 != ' ') {
                    printf("Nespravny vstup.\n");
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