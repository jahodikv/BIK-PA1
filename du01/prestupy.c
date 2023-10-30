#include <stdio.h>
#include <stdlib.h>

#define DAY 1440

int Transfer(int arrivalA, int arrivalB, int departureB) {
    int x = 0;
    int timeDifference = abs(arrivalA - departureB);

    if ((arrivalA < departureB && timeDifference >= 5 && timeDifference <= 180) ||
        //odjezd je pozdeji nez prijezd a zaroven v limitu pet minut az tri hodiny
        (arrivalB - arrivalA <= 180 && arrivalB > arrivalA+5) ||
        //
        (arrivalB + DAY - arrivalA <= 180 && arrivalB + DAY - arrivalA >= 5))
    //osetreni prechodu pres pulnoc
    {
        x = 1;
    }

    return x;
}

int validateInput(int hours, int minutes, int x) {

    if (x != 2) {
        printf("Nespravny vstup.\n");
        exit(0);
    }
    if (minutes > 59 || minutes < 0 || hours > 23 || hours < 0) {
        printf("Nespravny vstup.\n");
        exit(0);
    }

    return 0;
}

int scanInputArr(int *arrivalMinutes, int *arrivalHours, char c) {

    printf("Cas prijezdu vlaku %c:\n", c);

    int x = scanf(" %d :  %d", arrivalHours, arrivalMinutes);
    if (getchar() == EOF) {
        printf("Nespravny vstup.\n");
        exit(0);
    }

    return x;
}

int scanInputDep(int *departureMinutes, int *departureHours, char c) {

    printf("Cas odjezdu vlaku %c:\n", c);

    int x = scanf(" %d :  %d", departureHours, departureMinutes);
    if (getchar() == EOF) {
        printf("Nespravny vstup.\n");
        exit(0);
    }
    return x;
}

int main(void) {

    int arrivalMinutesA, arrivalMinutesB, arrivalMinutesC, arrivalHoursA, arrivalHoursB, arrivalHoursC, departureMinutesA, departureMinutesB, departureMinutesC, departureHoursA, departureHoursB, departureHoursC;
    int arrivalA, arrivalB, arrivalC, departureA, departureB, departureC;
    int x;

    //---------- scanning train A --------------------
    char c = 'A';
    x = scanInputArr(&arrivalMinutesA, &arrivalHoursA, c);
    validateInput(arrivalHoursA, arrivalMinutesA, x);

    x = scanInputDep(&departureMinutesA, &departureHoursA, c);
    validateInput(departureHoursA, departureMinutesA, x);

    //---------- scanning train B --------------------
    c = 'B';
    x = scanInputArr(&arrivalMinutesB, &arrivalHoursB, c);
    validateInput(arrivalHoursB, arrivalMinutesB, x);

    x = scanInputDep(&departureMinutesB, &departureHoursB, c);
    validateInput(departureHoursB, departureMinutesB, x);

    //---------- scanning train C --------------------
    c = 'C';
    x = scanInputArr(&arrivalMinutesC, &arrivalHoursC, c);
    validateInput(arrivalHoursC, arrivalMinutesC, x);

    x = scanInputDep(&departureMinutesC, &departureHoursC, c);
    validateInput(departureHoursC, departureMinutesC, x);

    arrivalA = arrivalHoursA * 60 + arrivalMinutesA;
    arrivalB = arrivalHoursB * 60 + arrivalMinutesB;
    arrivalC = arrivalHoursC * 60 + arrivalMinutesC;

    departureA = departureHoursA * 60 + departureMinutesA;
    departureB = departureHoursB * 60 + departureMinutesB;
    departureC = departureHoursC * 60 + departureMinutesC;

    if (Transfer(arrivalA, arrivalB, departureB) && Transfer(arrivalA, arrivalC, departureC)) {
        printf("Z vlaku A lze prestoupit na vlaky B a C.\n");
    } else if (Transfer(arrivalA, arrivalB, departureB)) {
        printf("Z vlaku A lze prestoupit na vlak B.\n");
    } else if (Transfer(arrivalA, arrivalC, departureC)) {
        printf("Z vlaku A lze prestoupit na vlak C.\n");
    } else {
        printf("Z vlaku A nelze prestupovat.\n");
    }

    if (Transfer(arrivalB, arrivalA, departureA) && Transfer(arrivalB, arrivalC, departureC)) {
        printf("Z vlaku B lze prestoupit na vlaky A a C.\n");
    } else if (Transfer(arrivalB, arrivalA, departureA)) {
        printf("Z vlaku B lze prestoupit na vlak A.\n");
    } else if (Transfer(arrivalB, arrivalC, departureC)) {
        printf("Z vlaku B lze prestoupit na vlak C.\n");
    } else {
        printf("Z vlaku B nelze prestupovat.\n");
    }

    if (Transfer(arrivalC, arrivalA, departureA) && Transfer(arrivalC, arrivalB, departureB)) {
        printf("Z vlaku C lze prestoupit na vlaky A a B.\n");
    } else if (Transfer(arrivalC, arrivalA, departureA)) {
        printf("Z vlaku C lze prestoupit na vlak A.\n");
    } else if (Transfer(arrivalC, arrivalB, departureB)) {
        printf("Z vlaku C lze prestoupit na vlak B.\n");
    } else {
        printf("Z vlaku C nelze prestupovat.\n");
    }
    return 0;
}
