#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Domino {

    char identifier;
    int aa;
    int ab;
    int ba;
    int bb;


};

void editDomino(struct Domino *dominoArr, int sizeArr) {

    for (int i = 0; i <= sizeArr; ++i) {

        for (int j = 0; j < 5; ++j) {


            if (dominoArr[i].aa <= dominoArr[i].ab && dominoArr[i].aa <= dominoArr[i].ba &&
                dominoArr[i].aa <= dominoArr[i].bb) {

                break;


            } else {

                int temp1 = dominoArr[i].aa;
                int temp2 = dominoArr[i].ab;
                int temp3 = dominoArr[i].ba;
                int temp4 = dominoArr[i].bb;

                dominoArr[i].aa = temp4;
                dominoArr[i].ab = temp1;
                dominoArr[i].ba = temp2;
                dominoArr[i].bb = temp3;


            }
        }


    }


}

int compare_ints(const void *a, const void *b) {
    int arg1 = (*(struct Domino *) a).aa;
    int arg2 = (*(struct Domino *) b).aa;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}

void findDuplicates(struct Domino *dominoArr, int sizeArr) {


    // int duplicatesCap = 5;
    // int duplicatesSize = 0;
    // struct Same *duplicates = (struct Same *) malloc(duplicatesCap * sizeof(struct Same));
    int uniques = 0;
    int capacityChar = sizeArr + 1;
    int sizeChar = 0;
    int pass = 0;


    for (int i = 0; i < sizeArr - 1; ++i) {


        if ((dominoArr[i].aa == dominoArr[i + 1].aa && dominoArr[i].ab == dominoArr[i + 1].ab &&
             dominoArr[i].ba == dominoArr[i + 1].ba && dominoArr[i].bb == dominoArr[i + 1].bb) ||
            (dominoArr[i].aa == dominoArr[i + 1].ba && dominoArr[i].ab == dominoArr[i + 1].bb &&
             dominoArr[i].ba == dominoArr[i + 1].aa && dominoArr[i].bb == dominoArr[i + 1].ab)) {

            if (i == 0) {


                uniques++;
            }

        } else {

            uniques++;

        }


    }

    printf("Unikatni: %d\nDuplikaty:\n", uniques);

    for (int i = 0; i < sizeArr - 1; ++i) {


        if ((dominoArr[i].aa == dominoArr[i + 1].aa && dominoArr[i].ab == dominoArr[i + 1].ab &&
             dominoArr[i].ba == dominoArr[i + 1].ba && dominoArr[i].bb == dominoArr[i + 1].bb) ||
            (dominoArr[i].aa == dominoArr[i + 1].ba && dominoArr[i].ab == dominoArr[i + 1].bb &&
             dominoArr[i].ba == dominoArr[i + 1].aa && dominoArr[i].bb == dominoArr[i + 1].ab)) {

            if (i == 0 || !((dominoArr[i].aa == dominoArr[i - 1].aa && dominoArr[i].ab == dominoArr[i - 1].ab &&
                             dominoArr[i].ba == dominoArr[i - 1].ba && dominoArr[i].bb == dominoArr[i - 1].bb) ||
                            (dominoArr[i].aa == dominoArr[i - 1].ba && dominoArr[i].ab == dominoArr[i - 1].bb &&
                             dominoArr[i].ba == dominoArr[i - 1].aa && dominoArr[i].bb == dominoArr[i - 1].ab))) {

                printf("%c", dominoArr[i].identifier);

            }
            printf(" = %c", dominoArr[i + 1].identifier);

        } else {
            if ((dominoArr[i].aa == dominoArr[i - 1].aa && dominoArr[i].ab == dominoArr[i - 1].ab &&
                 dominoArr[i].ba == dominoArr[i - 1].ba && dominoArr[i].bb == dominoArr[i - 1].bb) ||
                (dominoArr[i].aa == dominoArr[i - 1].ba && dominoArr[i].ab == dominoArr[i - 1].bb &&
                 dominoArr[i].ba == dominoArr[i - 1].aa && dominoArr[i].bb == dominoArr[i - 1].ab)) {

                printf("\n");

            }


        }


    }
}

int main(void) {

    int res = 0;
    int capacityArr = 5;
    int sizeArr = 0;
    char newline;
    struct Domino *dominoArr;
    dominoArr = (struct Domino *) malloc(capacityArr * sizeof(struct Domino));


    while (1) {

        if (sizeArr == capacityArr) {
            capacityArr = capacityArr * 2;
            dominoArr = (struct Domino *) realloc(dominoArr, capacityArr * sizeof(struct Domino));


        }


        res = scanf("%c [%d, %d, %d, %d]%c", &dominoArr[sizeArr].identifier, &dominoArr[sizeArr].aa,
                    &dominoArr[sizeArr].ab, &dominoArr[sizeArr].ba, &dominoArr[sizeArr].bb, &newline);
        sizeArr++;
        if (feof(stdin)) {

            editDomino(dominoArr, sizeArr);
            qsort(dominoArr, sizeArr, sizeof(struct Domino), compare_ints);
            findDuplicates(dominoArr, sizeArr);
            break;

        }

        if (res != 6) {

            printf("Nespravny vstup.\n");
            free(dominoArr);
            return 0;


        }


    }

    //  for (int i = 0; i <= sizeArr; ++i) {
    //    printf("%c [%d, %d, %d, %d]\n", dominoArr[i].identifier, dominoArr[i].aa, dominoArr[i].ab, dominoArr[i].ba,
    //         dominoArr[i].bb);
    // }
    free(dominoArr);
    return 0;
}