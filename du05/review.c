#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
struct Review {
    int day;
    int month;
    int year;
    int daysInDate;
    int points;
    char description[4096];
};



int leapYear(int a) {

    if (a % 4000 == 0) {
        return 1;
    } else if (a % 400 == 0) {
        return 1;
    } else if (a % 100 == 0) {
        return 0;
    } else if (a % 4 == 0) {
        return 1;
    } else {
        return 0;
    }

}
int countLeapYears(int y) {

    int leapYears = 0;
    for (int i = 2000; i < y; ++i) {
        if (leapYear(i) == 1) { leapYears++; }
    }

    //printf("%d", leapYears);
    return leapYears;

}

int daysInOneMonth(int y, int m) {

    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (leapYear(y) == 1) { monthDays[1] = 29; }
    return monthDays[m - 1];

}
int daysInMonths(int y, int m) {

    int d = 0;

    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (leapYear(y) == 1) { monthDays[1] = 29; }

    for (int i = 0; i < m - 1; ++i) {
        d += monthDays[i];
    }

    return d;

}
int validateDate(int y, int m, int d) {
    if (y < 2000) {

        return 0;
    }
    if (m < 1 || m > 12) {
        return 0;
    }
    if (d < 1) {
        return 0;
    }
    if (d > daysInOneMonth(y, m)) {
        return 0;
    }
    return 1;

}


struct Review scanReview() {
    struct Review review;
    scanf("%d-%d-%d %d %4095s", &review.year, &review.month, &review.day, &review.points, review.description);

    return review;
}



int main(void){


    int reviewCount = 5;
    int count;
    char c;
    struct Review* reviewArr = (struct Review*)malloc(reviewCount * sizeof(struct Review));


    if (reviewArr == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < reviewCount; i++) {
        scanf("%c",&c);
        if(c=='+'){
        reviewArr[i] = scanReview();
        validateStruct(reviewArr[i]);}
        else if(c=='?'){

            scanf("%d",&count);
            printInterval();
            printTotal();
            printReviews();
        }
        else if(c=='#'){

            scanf("%d",&count);
            printInterval();
            printTotal();

        }
        else{

            printf("Nespravny vstup.\n");
            free(reviewArr);
            return 0;
        }

    }

    free(reviewArr);
    return 0;
}