#include  <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 25000

int getMaxLenght(int balance[], int size) {

    int currentLength = 0;
    int maxLength = 0;


    for (int i = 0; i < size; ++i) {

        for (int j = size - 1; j > i; --j) {

            if (balance[j] >= balance[i]) {

                currentLength = j - i + 1;
                if (currentLength > maxLength) {
                    maxLength = currentLength;
                }
                break;
            }

        }

    }
    return maxLength;

}
void printInterval(int balance[],int size, int maxLength){
int count=0;
int currentLength=0;

    for (int i = 0; i < size; ++i) {

        for (int j = size - 1; j > i; --j) {

            if (balance[j] >= balance[i]) {

                currentLength = j - i + 1;
                if (currentLength == maxLength) {

                    printf("%d: %d - %d\n", maxLength, i, j);
                    count++;


                }
                break;
            }

        }

    }
    if (count == 0) {

        printf("Nelze najit.\n");
    } else {

        printf("Moznosti: %d\n", count);
    }



};

int main(void) {
    int balance[MAX_INPUT];
    int x = 0;
    int size;
    printf("Hodnoty:\n");
    for (size = 0; size < MAX_INPUT; ++size) {


        x = scanf("%d", &balance[size]);

        if (x == EOF) {
            if (size < 2) {
                printf("Nespravny vstup.\n");
                return 0;
            }
            break;
        } else if (x != 1) {
            printf("Nespravny vstup.\n");
            return 0;
        }


    }

    printInterval(balance,size, getMaxLenght(balance,size));
        return 0;


}