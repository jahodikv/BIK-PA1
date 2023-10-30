#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int safeAdd(int a, int b) {
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {

        printf("Nelze dosahnout.\n");
        exit(0);
    } else {
        return a + b;
    }
}

int myPow(int base, int exponent) {
    int result = 1;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}

int scanInput(int i) {
    int z, result = 0, num = 1;
    char x;

    x = ' ';
    while (1) {
        z = scanf("%c", &x);
        // printf("%c", x);

        if (feof(stdin) && i == 1 && z == -1 && x == ' ') { break; }
        if (z == 0 || x == ' ' || (i == 0 && (x == '\n' || feof(stdin)))) {
            printf("Nespravny vstup.\n");
            exit(0);
        }
        if (i == 0 && x == '|') {
            break;
        }
        if (i == 1 && (x == '\n' || feof(stdin))) {
            break;

        }
        if (x >= 'a' && x <= 'z') {
            num = x - 'a';
            result = safeAdd(result, myPow(2, num));
        } else {

            printf("Nespravny vstup.\n");
            exit(0);
        }
    }

    return result;

}

int countUnits(int a1, int a2, int b1, int b2) {

    int aRes, bRes, a12, b12, units;
    a12 = a1 + a2;
    b12 = b1 + b2;
    aRes = a1;
    bRes = b1;
    units = 0;
    int runs = 0;
    if ((a1 == 0 && b1 == 0) || (a2 == 0 && b2 == 0)) {
        return units;
    }
    if ((a12 == 0 && b12 > 0) || (b12 == 0 && a12 > 0)) {

        printf("Nelze dosahnout.\n");
        exit(0);


    }
        if ((a1 == 0 && a2 > 0 && b1 > 0 && b2 == 0) || (a2 == 0 && a1 > 0 && b2 > 0 && b1 == 0)) {


        return units;
    }
    while (1) {
        if (aRes == bRes) {
            units = bRes;
            break;
        }
        if (aRes > bRes) {
            if (runs == 0) { aRes += a12; }

            while (aRes > bRes) {
                bRes = safeAdd(bRes, b12);
            }
            units = aRes;
        } else {

            if (runs == 0) { bRes += b12; }

            while (bRes > aRes) {
                aRes = safeAdd(aRes, a12);
            }

            units = bRes;
        }
        if (runs > 1000000) {
            printf("Nelze dosahnout.\n");
            exit(0);

        }
        runs++;
    }
    return units;
};


int main(void) {

    int a1, a2, b1, b2, units;
    printf("Zpravy:\n");
    a1 = scanInput(0);
    a2 = scanInput(1);
    if(a1==0&&a2==0){ printf("Nespravny vstup.\n");
        exit(0);}
    b1 = scanInput(0);
    b2 = scanInput(1);
    if(b1==0&&b2==0){ printf("Nespravny vstup.\n");
        exit(0);}
    units = countUnits(a1, a2, b1, b2);
    //printf("%d,%d|%d,%d", a1, a2, b1, b2);
    printf("Synchronizace za: %d\n", units);

    return 0;


}