#include <stdio.h>
#include <math.h>
#include <float.h>
int checkInput(char c, double a, double b) {

    if (c == '/' && b == 0) {

        return 0;
    }
    if (c != '/') {
        if (c != '*') {
            if (c != '-') {
                if (c != '+') {
                    return 0;
                }
            }
        }
    }


    return 1;


}

double count(char c, double a, double b) {
    double result=0;
    if (c == '+') {

        result = a + b;

    }
    if (c == '-') {

        result = a - b;
    }


    if (c == '*') {

        result = a * b;
    }
    if (c == '/') {


        result = a / b;


    }

    return result;


}


int main(void) {


    char c,eq;
    double a, b;
    int x;
    printf("Zadejte vzorec:\n");
    x = scanf(" %lf %c %lf %c", &a, &c, &b, &eq );
    if (x != 4 || checkInput(c, a, b) == 0) {

        printf("Nespravny vstup.\n");
        return 0;

    }
    if (eq!='='){
        printf("Nespravny vstup.\n");
        return 0;}
    double res=count(c, a, b);
    int y = (int)res;
    if (c=='/'){



        res= floor(res);
        y = (int)res;
        printf("%d\n", y);
        return 0;
    }
    if (y==res){

        printf("%d\n", y);
    }
    else{

        printf("%g\n", res);
    }



    return 0;
}