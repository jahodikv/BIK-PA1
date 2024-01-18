#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book
{

    char postcode[11];
    int salary;
};
void handleError(struct Book *payBook)
{

    printf("Nespravny vstup.\n");
    free(payBook);
    exit(0);
}
int postcodeCheck(char postcode[11])
{

    int size = strlen(postcode);

    for (size_t i = 0; i < size; i++)
    {

        if (postcode[i] < '0' || postcode[i] > '9')
        {

            return 1;
        }
    }
    return 0;
}
int compare(const void *a, const void *b)
{
    char *arg1 = (*(struct Book *)a).postcode;
    char *arg2 = (*(struct Book *)b).postcode;

    return strcmp(arg1, arg2);
}
int checkIfIsInRegion(char *buffer, char *b)
{
    for (size_t i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] != b[i])
            return 1;
    }
    return 0;
}

int checkAllregions(char *buffer, struct Book *payBook, int payBookSize)
{

    for (size_t i = 0; i < payBookSize; i++)
    {
        if (checkIfIsInRegion(buffer, payBook[i].postcode) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void findModus(struct Book *payBook, int payBookSize, char *buffer)
{
    int maxCount = 0;
    int maxValueCap = 2;
    int maxValueSize = 0;
    int state = 0;
    int *maxValue = (int *)malloc(sizeof(int) * maxValueCap);
    if (buffer[0] == '*')
    {

        for (int i = 0; i < payBookSize; i++)
        {
            int count = 0;
            for (int x = 0; x < payBookSize; x++)
            {
                if (payBook[i].salary == payBook[x].salary)
                {
                    count++;
                }
                if (count > maxCount)
                {
                    maxCount = count;
                    free(maxValue);

                    maxValueCap = 2;
                    maxValueSize = 0;
                    int *maxValue = NULL;
                    maxValue = (int *)malloc(sizeof(int) * maxValueCap);

                    maxValue[maxValueSize] = payBook[i].salary;
                    maxValueSize++;
                }
                else if (count == maxCount)
                {
                    state = 0;
                    for (size_t x = 0; x < maxValueSize; x++)
                    {
                        if (maxValue[x] == payBook[i].salary)
                        {
                            state = 1;
                        }
                    }
                    if (state == 0)
                    {

                        if (maxValueCap == maxValueSize)
                        {
                            maxValueCap = maxValueCap * 2;
                            maxValue = (int *)realloc(maxValue, sizeof(int) * maxValueCap);
                        }
                        maxValue[maxValueSize] = payBook[i].salary;
                        maxValueSize++;
                    }
                }
            }
        }
        printf("Modus: ");
        for (int i = 0; i < maxValueSize; i++)
        {
            printf("%d", maxValue[i]);
            if (i != maxValueSize - 1)
            {
                printf(", ");
            }
        }
        printf(" [%d]\n", maxCount);
        free(maxValue);
        return;
    }
    else
    {

        for (int i = 0; i < payBookSize; i++)
        {

            if (checkIfIsInRegion(buffer, payBook[i].postcode) == 1)
            {
                continue;
            }

            int count = 0;
            for (int x = 0; x < payBookSize; x++)
            {

                if (payBook[i].salary == payBook[x].salary && checkIfIsInRegion(buffer, payBook[x].postcode) == 0)
                {
                    count++;
                }
                if (count > maxCount)
                {
                    maxCount = count;
                    free(maxValue);

                    maxValueCap = 2;
                    maxValueSize = 0;
                    int *maxValue = NULL;
                    maxValue = (int *)malloc(sizeof(int) * maxValueCap);

                    maxValue[maxValueSize] = payBook[i].salary;
                    maxValueSize++;
                }
                else if (count == maxCount)
                {
                    state = 0;
                    for (size_t x = 0; x < maxValueSize; x++)
                    {
                        if (maxValue[x] == payBook[i].salary)
                        {
                            state = 1;
                        }
                    }
                    if (state == 0)
                    {

                        if (maxValueCap == maxValueSize)
                        {
                            maxValueCap = maxValueCap * 2;
                            maxValue = (int *)realloc(maxValue, sizeof(int) * maxValueCap);
                        }
                        maxValue[maxValueSize] = payBook[i].salary;
                        maxValueSize++;
                    }
                }
            }
        }
        printf("Modus: ");
        for (int i = 0; i < maxValueSize; i++)
        {
            printf("%d", maxValue[i]);
            if (i != maxValueSize - 1)
            {
                printf(", ");
            }
        }
        printf(" [%d]\n", maxCount);
        free(maxValue);
        return;
    }
}

int main(void)
{
    int res;
    int payBookCap = 2;
    int payBookSize = 0;
    char action;
    char buffer[11];
    int payBuffer;
    int state = 0;
    struct Book *payBook = (struct Book *)malloc(sizeof(struct Book) * payBookCap);
    printf("Data:\n");
    while (1)
    {
        res = scanf(" %c ", &action);
        if (res != 1)
        {
            handleError(payBook);
        }
        if (action == '?')
        {
            break;
        }
        else if (action != '+')
        {
            handleError(payBook);
        }

        res = scanf(" %10s %d ", buffer, &payBuffer);

        if (res != 2)
        {
            handleError(payBook);
        }
        if (payBuffer < 0 || postcodeCheck(buffer) == 1)
        {
            handleError(payBook);
        }

        if (payBookCap == payBookSize)
        {
            payBookCap = payBookCap * 2;
            payBook = (struct Book *)realloc(payBook, sizeof(struct Book) * payBookCap);
        }
        strcpy(payBook[payBookSize].postcode, buffer);
        payBook[payBookSize].salary = payBuffer;
        payBookSize++;
    }

    while (1)
    {

        if (state == 0)
        {

            res = scanf(" %10s", buffer);
        }
        else
        {

            res = scanf(" %c %10s", &action, buffer);
            if (res != 2 || action != '?')
            {
                handleError(payBook);
            }
        }

        if (buffer[0] == '*')
        {
            qsort(payBook, payBookSize, sizeof(struct Book), compare);
            findModus(payBook, payBookSize, buffer);
            state = 1;
            continue;
        }
        else if (postcodeCheck(buffer) == 0)
        {
            qsort(payBook, payBookSize, sizeof(struct Book), compare);

            if (checkAllregions(buffer,payBook,payBookSize)==1)
            {

                printf("Modus: N/A.\n");
                state = 1;
                continue;
            }
            else
            {

                findModus(payBook, payBookSize, buffer);
            }
        }
        else
        {

            handleError(payBook);
        }
        if (feof(stdin))
        {
            break;
        }
        state = 1;
    }

    /*
     for (size_t i = 0; i < payBookSize; i++)
     {
         printf("%s , %d\n", payBook[i].postcode, payBook[i].salary);
     }*/
    free(payBook);
    return 0;
}