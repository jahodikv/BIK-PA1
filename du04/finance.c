#include  <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 25000

int getMaxLenght(int balance[], int size) {

    int currentLength = 0;
    int maxLength = 0;
    int bestIntervals[MAX_INPUT][2];
    int count = 0;
    int finalCount = 0;
    int best;
    for (int i = 0; i <= size; ++i) {

        for (int j = size - 1; j > i; --j) {

            if (balance[j] >= balance[i]) {

                currentLength = j - i + 1;
                if (currentLength >maxLength) {
                    //printf("%d\n", i);
                    count=0;
                    bestIntervals[count][0] = i;
                    bestIntervals[count][1] = j;
                    maxLength = currentLength;
                    count++;
                } else if(currentLength ==maxLength) {
                    //printf("%d\n", i);
                    bestIntervals[count][0] = i;
                    bestIntervals[count][1] = j;
                    maxLength = currentLength;
                    count++;
                }
                break;
            }

        }

    }
    if (count == 0) {

        printf("Nelze najit.\n");
        return 1;
    }
    for (int i = 0; i < count + 1; ++i) {
        best = bestIntervals[i][1] - bestIntervals[i][0] + 1;

        //printf("%d",bestIntervals[1][1]);
        if (best == maxLength) {


            printf("%d: %d - %d\n", maxLength, bestIntervals[i][0], bestIntervals[i][1]);

           finalCount++;
       }


    }


    printf("Moznosti: %d\n", finalCount);


    return 1;

}


int main(void) {
    int balance[MAX_INPUT];
    int x = 0;
    int size;
    printf("Hodnoty:\n");
    for (size = 0; size < MAX_INPUT; ++size) {


        x = scanf("%d", &balance[size]);
//if (balance[size]==-1){
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

    getMaxLenght(balance, size);
    return 0;


}