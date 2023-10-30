#include <stdio.h>
#include <stdlib.h>

int colorChange(int color) {

    if (color == 0) {
        color = 1;
    } else { color = 0; }
    return color;
}


int main(void) {


    int fieldNum;
    int fieldSize;
    int color;

    printf("Zadejte pocet poli:\n");

    if (scanf("%d", &fieldNum) != 1 || fieldNum <= 0) {

        printf("Nespravny vstup.\n");
        return 0;
    }

    printf("Zadejte velikost pole:\n");

    if (scanf("%d", &fieldSize) != 1 || fieldSize <= 0) {

        printf("Nespravny vstup.\n");
        return 0;
    }

    color = 0;
    printf("+");
    for (int i = 0; i < fieldSize * fieldNum; ++i) {
        printf("-");
    }
    printf("+\n");

    for (int q = 0; q < fieldNum; ++q) {


        for (int i = 0; i < fieldSize; ++i) {

            for (int x = 0; x < fieldNum; ++x) {

                if (x == 0) {

                    printf("|");
                }
                if (color == 0 || (fieldNum == 1)) {

                    for (int j = 0; j < fieldSize; ++j) {
                        printf(" ");
                    }

                    color = 1;

                } else {

                    for (int z = 0; z < fieldSize; ++z) {
                        printf("X");
                    }
                    color = 0;
                }


                if (x == fieldNum - 1) {

                    printf("|\n");
                }


            }


            if (fieldNum % 2 != 0 && fieldSize % 2 != 0) {//liche liche
                if (i + 1 != fieldSize) {

                    color = colorChange(color);
                }
            }

            if (fieldNum % 2 == 0 && fieldSize % 2 == 0) {//sude sude

                if (i + 1 == fieldSize) {

                    color = colorChange(color);
                }


            }
            if (fieldNum % 2 != 0 && fieldSize % 2 == 0) {
                if (i + 1 != fieldSize) {

                    color = colorChange(color);
                }
            }//liche sude
            if (fieldNum % 2 == 0 && fieldSize % 2 != 0) {

                if (i + 1 == fieldSize) {

                    color = colorChange(color);
                }
            }//sude liche






        }

    }
    printf("+");
    for (int i = 0; i < fieldSize * fieldNum; ++i) {
        printf("-");
    }
    printf("+\n");

}