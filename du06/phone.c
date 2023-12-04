#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

struct Phonebook {
    char phoneNumber[21];
    char *name;
};

void convertNameToT9(const char *name, char **nameT9) {

    size_t len = 0;
    while (name[len] != '\0') {
        len++;
    }

    *nameT9 = (char *) realloc(*nameT9, (len + 1) * sizeof(char));


    size_t i = 0;
    while (*name) {
        char current = *name;
        if (isalpha(current)) {
            char converted = tolower(current);
            if (converted == 'a' || converted == 'b' || converted == 'c') {
                (*nameT9)[i++] = '2';
            } else if (converted == 'd' || converted == 'e' || converted == 'f') {
                (*nameT9)[i++] = '3';
            } else if (converted == 'g' || converted == 'h' || converted == 'i') {
                (*nameT9)[i++] = '4';
            } else if (converted == 'j' || converted == 'k' || converted == 'l') {
                (*nameT9)[i++] = '5';
            } else if (converted == 'm' || converted == 'n' || converted == 'o') {
                (*nameT9)[i++] = '6';
            } else if (converted == 'p' || converted == 'q' || converted == 'r' || converted == 's') {
                (*nameT9)[i++] = '7';
            } else if (converted == 't' || converted == 'u' || converted == 'v') {
                (*nameT9)[i++] = '8';
            } else if (converted == 'w' || converted == 'x' || converted == 'y' || converted == 'z') {
                (*nameT9)[i++] = '9';
            }
        } else if (current == ' ') {
            (*nameT9)[i++] = '1';
        }
        ++name;
    }
    (*nameT9)[i++] = '\0';
}


void find(struct Phonebook *book, int bookLength, char *query) {
    int z = 0;

    int findAlready[10];


    for (int i = 0; i < bookLength; ++i) {
        char *nameT9 = NULL;
        convertNameToT9(book[i].name, &nameT9);

        if (strncmp(book[i].phoneNumber, query, strlen(query)) == 0 || strncmp(nameT9, query, strlen(query)) == 0) {


            findAlready[z] = i;

            z++;
        }

        free(nameT9);


    }

    if (z > 10) {
        printf("Celkem: %d\n", z);
    } else {

        for (int i = 0; i < z; ++i) {
            printf("%s %s\n", book[findAlready[i]].phoneNumber, book[findAlready[i]].name);
        }
        printf("Celkem: %d\n", z);


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


int main(void) {


    int bookCapacity = 3;
    int bookLength = 0;
    int nameLength = 0;
    int nameCapacity = 3;
    int queryLength = 0;
    int queryCapacity = 3;
    int c;
    struct Phonebook *book = (struct Phonebook *) malloc(bookCapacity * sizeof(struct Phonebook));


    char action, phoneNumber[21], space1, space2;

    start:
    while (scanf("%c", &action) != EOF) {

        if (action == '+') {
            if (scanf("%c%20s%c", &space1, phoneNumber, &space2) != 3) {
                printf("Nespravny vstup.\n");
                while ((c = getchar()) != '\n' && c != EOF);

                goto start;

            } else {
                nameLength = 0;
                char *name = NULL;
                name = (char *) malloc(nameCapacity * sizeof(char));
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
                        while ((c = getchar()) != '\n' && c != EOF);
                        free(name);
                        goto start;


                    }
                    if (name[nameLength] == ' ' && nameLength == 0) {

                        printf("Nespravny vstup.\n");
                        while ((c = getchar()) != '\n' && c != EOF);
                        free(name);
                        goto start;


                    }
                    if ((name[nameLength] >= 'A' && name[nameLength] <= 'Z') ||
                        (name[nameLength] >= 'a' && name[nameLength] <= 'z') || name[nameLength] == ' ') {
                        nameLength++;
                        continue;
                    } else if (name[nameLength] == '\n') {


                        name[nameLength] = '\0';
                        ungetc('\n', stdin);
                        break;

                    } else {

                        printf("Nespravny vstup.\n");
                        while ((c = getchar()) != '\n' && c != EOF);
                        free(name);
                        goto start;


                    }


                }


                if (space1 != ' ' || space2 != ' ') {
                    printf("Nespravny vstup.\n");
                    while ((c = getchar()) != '\n' && c != EOF);
                    free(name);
                    goto start;
                }
                int exists = 0;
                int isPhoneNum;
                isPhoneNum = isNumber(phoneNumber);

                if (isPhoneNum == 1 || name[0] == '\0' || name[0] == ' ' ||
                    name[strlen(name) - 1] == ' ') {
                    while ((c = getchar()) != '\n' && c != EOF);
                    free(name);
                    goto start;
                }
                for (int i = 0; i < bookLength; i++) {
                    if (strcmp(book[i].phoneNumber, phoneNumber) == 0 && strcmp(book[i].name, name) == 0) {
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
                free(name);
            }
        } else if (action == '?') {

            if (scanf("%c", &space1) != 1) {
                printf("Nespravny vstup.\n");
                while ((c = getchar()) != '\n' && c != EOF);
                goto start;

            } else if (space1 == '\n') {
                printf("Nespravny vstup.\n");
                goto start;

            } else if (space1 != ' ') {
                printf("Nespravny vstup.\n");
                while ((c = getchar()) != '\n' && c != EOF);
                goto start;
            } else{

                queryLength = 0;
                queryCapacity = 3;
                char *query = NULL;

                while (1) {

                    if (queryLength == queryCapacity || queryLength == 0) {
                        queryCapacity *= 2;
                        query = (char *) realloc(query, queryCapacity * sizeof(char));

                    }
                    int res = scanf("%c", &query[queryLength]);
                    if (res == EOF) {

                        break;

                    } else if (res != 1) {

                        printf("Nespravny vstup.\n");
                        while ((c = getchar()) != '\n' && c != EOF);
                        free(query);
                        goto start;


                    }
                    if (query[queryLength] >= '0' && query[queryLength] <= '9') {
                        queryLength++;
                        continue;
                    } else if (query[queryLength] == '\n') {


                        query[queryLength] = '\0';
                        ungetc('\n', stdin);
                        break;

                    } else {

                        printf("Nespravny vstup.\n");
                        while ((c = getchar()) != '\n' && c != EOF);
                        free(query);
                        goto start;


                    }
                }
                find(book, bookLength, query);

                free(query);
            }
        } else {
            printf("Nespravny vstup.\n");


            while ((c = getchar()) != '\n' && c != EOF);

            if (c == EOF) {

                return 0;
            }

            goto start;

        }

        if (scanf("%c", &space1) == EOF) {

            for (int i = 0; i < bookLength; i++) {
                free(book[i].name);
            }
            free(book);


            return 0;
        } else if (space1 == '\n') {

            continue;
        } else {
            printf("Nespravny vstup.\n");

            while ((c = getchar()) != '\n' && c != EOF);
            goto start;
        }

    }

    for (int i = 0; i < bookLength; i++) {
        free(book[i].name);
    }
    free(book);

    return 0;
}