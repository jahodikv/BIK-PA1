#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
struct Student
{

    char status;
    char name1[33];
    char name2[33];
    char name3[33];
    char wholeName[33];
};

int isWhite(char x)
{

    if (x == ' ' || x == '\t' || x == '\n' || x == '\0')
    {

        return 1;
    }
    return 0;
}
int skipWhite(char *line, int pos)
{

    for (int i = pos; i <= strlen(line); i++)
    {
        if (isWhite(line[i]) == 0)
        {
            pos = i;
            break;
        }
    }

    return pos;
}

void handleError(char *line, struct Student *registered, struct Student *present)
{

    printf("Nespravny vstup.\n");
    free(line);
    free(registered);
    free(present);
    exit(0);
}

int skipNonWhite(char *line, int pos, char *student)
{

    int size = 0;
    for (int i = pos; i <= strlen(line); i++)
    {
        if (isWhite(line[i]) == 1)
        {
            pos = i;
            break;
        }
        student[size] = line[i];
        size++;
    }

    student[size] = '\0';
    // printf("%s\n",student);
    return pos;
}
int compare_strings(const void *a, const void *b)
{
    return strcasecmp(*(const char **)a, *(const char **)b);

    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}

// Funkce pro třídění slov v řetězci podle abecedy
char *seradSlova(const char *retezec)
{
    const char *delimiters = " \t\n\r"; // Mezery, tabulátory, nové řádky, návraty

    // Získání počtu slov
    int pocetSlov = 0;
    char *kopie = strdup(retezec);
    char *token = strtok(kopie, delimiters);
    while (token != NULL)
    {
        pocetSlov++;
        token = strtok(NULL, delimiters);
    }
    free(kopie);

    // Vytvoření pole ukazatelů na slova
    char **slova = (char **)malloc(pocetSlov * sizeof(char *));
    if (slova == NULL)
    {
        fprintf(stderr, "Chyba alokace paměti.\n");
        exit(EXIT_FAILURE);
    }

    // Kopírování slov do pole ukazatelů
    int index = 0;
    token = strtok(strdup(retezec), delimiters);
    while (token != NULL)
    {
        slova[index] = strdup(token);
        if (slova[index] == NULL)
        {
            fprintf(stderr, "Chyba alokace paměti.\n");
            exit(EXIT_FAILURE);
        }
        index++;
        token = strtok(NULL, delimiters);
    }

    // Třídění slov podle abecedy
    qsort(slova, pocetSlov, sizeof(char *), compare_strings);

    // Sestavení seřazeného řetězce
    char *serazenyRetezec = (char *)malloc(strlen(retezec) + 1);
    if (serazenyRetezec == NULL)
    {
        fprintf(stderr, "Chyba alokace paměti.\n");
        exit(EXIT_FAILURE);
    }

    serazenyRetezec[0] = '\0';
    for (int i = 0; i < pocetSlov; i++)
    {
        strcat(serazenyRetezec, slova[i]);
        if (i < pocetSlov - 1)
        {
            strcat(serazenyRetezec, " ");
        }
        free(slova[i]); // Uvolnění paměti alokované pro jednotlivá slova
    }

    free(slova); // Uvolnění paměti alokované pro pole ukazatelů

    return serazenyRetezec;
}

int main(void)
{

    int regCap = 5;
    int regSize = 0;
    int presentCap = 5;
    int presentSize = 0;
    int nameLen = 0;
    int state = 0;
    char *line = NULL;
    size_t cap = 5;
    int lineLen;
    char temp;
    int pos = 0;
    char nameBuffer[33];
    struct Student *registered = (struct Student *)malloc(sizeof(struct Student) * regCap);
    struct Student *present = (struct Student *)malloc(sizeof(struct Student) * presentCap);

    printf("Studenti:\n");
    while ((lineLen = getline(&line, &cap, stdin) != EOF))
    {
        pos = 0;
        lineLen = strlen(line);
        if (line[lineLen - 1] == '\n')
        {
            --lineLen;
            line[lineLen] = '\0';
        }
        pos = skipWhite(line, pos);
        if (line[pos] == 'P')
        {
            state = 1;
        }
        else if (line[pos] != 'R' || (line[pos] == 'R' && state == 1))
        {

            handleError(line, registered, present);
        }
        pos++;
        pos = skipWhite(line, pos);
        // printf("%d\n",pos);
        if (line[pos] != ':')
        {
            handleError(line, registered, present);
        }
        pos++;
        pos = skipWhite(line, pos);

        if (state == 0)
        {

            if (regSize == regCap)
            {
                regCap = regCap * 2;
                registered = (struct Student *)realloc(registered, sizeof(struct Student) * regCap);
            }

            pos = skipNonWhite(line, pos, registered[regSize].name1);
        }
        else
        {

            if (presentSize == presentCap)
            {
                presentCap = presentCap * 2;
                present = (struct Student *)realloc(present, sizeof(struct Student) * presentCap);
            }

            pos = skipNonWhite(line, pos, present[presentSize].name1);
        }
        pos++;
        if (line[pos] == ' ')
        {
            handleError(line, registered, present);
        }
        else if (line[pos] == '\0')
        {
            if (state == 0)
            {
                if (state == 0 && (strlen(registered[regSize].name1) > 32))
                {

                    handleError(line, registered, present);
                }
                else
                {
                    strcpy(registered[regSize].wholeName, registered[regSize].name1);
                    regSize++;
                    continue;
                }
            }

            if (state == 1)
            {

                if ((strlen(present[presentSize].name1) > 32))
                {
                    handleError(line, registered, present);
                }
                else
                {
                    strcpy(present[presentSize].wholeName, present[presentSize].name1);
                    presentSize++;
                    continue;
                }
            }
        }

        if (state == 0)
        {

            if (regSize == regCap)
            {
                regCap = regCap * 2;
                registered = (struct Student *)realloc(registered, sizeof(struct Student) * regCap);
            }

            pos = skipNonWhite(line, pos, registered[regSize].name2);
        }
        else
        {

            if (presentSize == presentCap)
            {
                presentCap = presentCap * 2;
                present = (struct Student *)realloc(present, sizeof(struct Student) * presentCap);
            }

            pos = skipNonWhite(line, pos, present[presentSize].name2);
        }
        pos++;
        if (line[pos] == ' ')
        {
            handleError(line, registered, present);
        }
        else if (line[pos] == '\0')
        {

            if (state == 0)
            {
                /* code */

                if ((strlen(registered[regSize].name1) + strlen(registered[regSize].name2) + 1 > 33))
                {
                    handleError(line, registered, present);
                }
                else
                {
                    strcpy(registered[regSize].wholeName, registered[regSize].name1);
                    registered[regSize].wholeName[strlen(registered[regSize].wholeName)] = ' ';
                    strcat(registered[regSize].wholeName, registered[regSize].name2);
                    regSize++;
                    continue;
                }
            }

            if (state == 1)
            {
                /* code */

                if ((strlen(present[presentSize].name1) + strlen(present[presentSize].name2) + 1 > 33))
                {

                    handleError(line, registered, present);
                }
                else
                {
                    strcpy(present[presentSize].wholeName, present[presentSize].name1);
                    present[presentSize].wholeName[strlen(present[presentSize].wholeName)] = ' ';
                    strcat(present[presentSize].wholeName, present[presentSize].name2);
                    presentSize++;
                    continue;
                }
            }
        }

        if (state == 0)
        {

            if (regSize == regCap)
            {
                regCap = regCap * 2;
                registered = (struct Student *)realloc(registered, sizeof(struct Student) * regCap);
            }

            pos = skipNonWhite(line, pos, registered[regSize].name3);
        }
        else
        {

            if (presentSize == presentCap)
            {
                presentCap = presentCap * 2;
                present = (struct Student *)realloc(present, sizeof(struct Student) * presentCap);
            }

            pos = skipNonWhite(line, pos, present[presentSize].name3);
        }
        if (state == 0)
        {
            if ((strlen(registered[regSize].name1) + strlen(registered[regSize].name2) + strlen(registered[regSize].name3) + 2 > 33))
            {

                handleError(line, registered, present);
            }
            else
            {
                strcpy(registered[regSize].wholeName, registered[regSize].name1);
                registered[regSize].wholeName[strlen(registered[regSize].wholeName)] = ' ';
                strcat(registered[regSize].wholeName, registered[regSize].name2);
                registered[regSize].wholeName[strlen(registered[regSize].wholeName)] = ' ';
                strcat(registered[regSize].wholeName, registered[regSize].name3);
                regSize++;
            }
        }
        if (state == 1)
        {
            /* code */

            if ((strlen(present[presentSize].name1) + strlen(present[presentSize].name2) + strlen(present[presentSize].name3) + 2 > 33))
            {

                handleError(line, registered, present);
            }
            else
            {
                strcpy(present[presentSize].wholeName, present[presentSize].name1);
                present[presentSize].wholeName[strlen(present[presentSize].wholeName)] = ' ';
                strcat(present[presentSize].wholeName, present[presentSize].name2);
                present[presentSize].wholeName[strlen(present[presentSize].wholeName)] = ' ';
                strcat(present[presentSize].wholeName, present[presentSize].name3);
                presentSize++;
            }
        }
    }

   

    // printf("%d\n",pos);
    // printf("\n");
    // printf("%s\n", registered[regSize-2].name1);
    // printf("%s\n", registered[regSize-2].name2);
    // printf("%s\n", registered[regSize-2].name3);
    printf("%s\n", sorted);

    //    printf("\n");
    //  for (int i = 0; i <= regSize; ++i)
    // {
    //    printf("%s\n", registered[i].name);
    // }
    // for (int i = 0; i <= presentSize; ++i)
    //{
    //    printf("%s\n", present[i].name);
    // }
    free(registered);
    free(present);
    return 0;
}