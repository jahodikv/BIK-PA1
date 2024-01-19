#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Storage
{
    int quantity;
    char ean[101];
};
int compare_ints(const void *a, const void *b)
{
    char *arg1 = (*(struct Storage *)a).ean;
    char *arg2 = (*(struct Storage *)b).ean;

    return strcmp(arg1, arg2);
}

int eanCheck(char *ean)
{

    int len = strlen(ean);

    if (len > 100 || len < 5)
    {

        return 1;
    }

    for (size_t i = 0; i < len; i++)
    {

        if (ean[i] < '0' || ean[i] > '9')
        {

            return 1;
        }
    }

    return 0;
}
void handleError(struct Storage *items)
{

    printf("Nespravny vstup.\n");
    free(items);
    exit(0);
}

int main(void)
{
    int itemsSize = 0;
    int itemsCap = 2;
    struct Storage *items = (struct Storage *)malloc(sizeof(struct Storage) * itemsCap);
    int res;
    int quantity;
    char eanBuff[101];
    char action;
struct Storage *result=NULL;
    printf("Zbozi:\n");

    while (1)
    {

        res = scanf(" %c %dx %100s", &action, &quantity, eanBuff);
        if (res != 3 || (action != '+' && action != '-') || quantity < 0 || eanCheck(eanBuff) == 1)
        {

            handleError(items);
        }
        if(itemsSize>0){
           struct Storage temporery;
           strcpy(temporery.ean,eanBuff);
            result = (struct Storage *)bsearch(&temporery, items, itemsSize, sizeof(struct Storage), compare_ints);
        }
        
        if (result != NULL)
        {

            int index = result - items;
            //printf("%d", index);
            if (action == '+')
            {

                items[index].quantity = items[index].quantity + quantity;
                printf(">%dx\n", items[index].quantity);
                continue;
            }
            else
            {
                if (items[index].quantity - quantity >= 0)
                {
                    items[index].quantity = items[index].quantity - quantity;
                    printf(">%dx\n", items[index].quantity);
                    continue;
                }
                else
                {

                    printf("Nedostatecne zasoby.\n");
                    continue;
                }
            }
        }
        else
        {

            if (action == '+')
            {
                if (itemsSize == itemsCap)
                {

                    itemsCap = itemsCap * 2;
                    items = (struct Storage *)realloc(items, sizeof(struct Storage) * itemsCap);
                }
                strcpy(items[itemsSize].ean, eanBuff);
                items[itemsSize].quantity = quantity;
                printf(">%dx\n", items[itemsSize].quantity);
                itemsSize++;

                qsort(items, itemsSize, sizeof(struct Storage), compare_ints);

                // printf(">%dx %s\n", items[0].quantity, items[0].ean);
                // printf(">%dx %s\n", items[1].quantity, items[1].ean);
            }
            else
            {
                printf("Nedostatecne zasoby.\n");
                continue;
            }
        }

        if (feof(stdin))
        {

            break;
        }
    }

    free(items);
    return 0;
}
