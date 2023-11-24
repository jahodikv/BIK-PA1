#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct Review {
    int day;
    int month;
    int year;
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

int validateStruct(struct Review *reviewArr, int size) {

    if (size > 0) {
        int sum2 = (reviewArr[size].year - 1800) * 365 + reviewArr[size].day +
                   daysInMonths(reviewArr[size].year, reviewArr[size].month) + countLeapYears(reviewArr[size].year);
        int sum1 = (reviewArr[size - 1].year - 1800) * 365 + reviewArr[size - 1].day +
                   daysInMonths(reviewArr[size - 1].year, reviewArr[size - 1].month) +
                   countLeapYears(reviewArr[size - 1].year);
        if (sum2 < sum1) {


            printf("Nespravny vstup.\n");
            return 0;
        }


    }
    if (reviewArr[size].points <= 0) {
        printf("Nespravny vstup.\n");
        return 0;
    }
    return 1;


}

void printInterval(struct Review *reviewArr, int inputNum, int size) {

    int closestNum = 0, count = 0, sameDay = 0;
int i;
int bestCount=0;
    int bestIntervals[size][3];

    for (int g = 0; g < size; ++g) {

        if (g > 0) {
            if (reviewArr[g].year == reviewArr[g - 1].year && reviewArr[g].month == reviewArr[g - 1].month &&
                reviewArr[g].day == reviewArr[g - 1].day) {

                continue;
            }
        }
        for ( i = g; i < size; ++i) {

            if (i > 0) {
            if (reviewArr[i].year == reviewArr[i - 1].year && reviewArr[i].month == reviewArr[i - 1].month &&
                reviewArr[i].day == reviewArr[i - 1].day) {
                sameDay += reviewArr[i].points;
                continue;
            }}

            if(sameDay==0){

                count += reviewArr[i].points;
            }
            else{
                count += sameDay;
                sameDay = 0;
                if (abs(count - inputNum) <= abs(closestNum - inputNum)) {


                    closestNum = count;
                    bestIntervals[bestCount][0]=g;
                    bestIntervals[bestCount][1]=i-1;
                    bestIntervals[bestCount][2]=closestNum;

                    bestCount++;

                }
                count += reviewArr[i].points;
            }


            if (abs(count - inputNum) <= abs(closestNum - inputNum)) {


                closestNum = count;
                bestIntervals[bestCount][0]=g;
                bestIntervals[bestCount][1]=i;
                bestIntervals[bestCount][2]=closestNum;

                bestCount++;

            }


        }
        i = g;

    }
    for (int j = bestCount; j > -1; --j) {
if(closestNum==bestIntervals[j][2]){

    bestCount=j;
    break;
}
    }
    printf("%d-%d-%d - %d-%d-%d: %d\n",reviewArr[bestIntervals[bestCount][0]].year,reviewArr[bestIntervals[bestCount][0]].month,reviewArr[bestIntervals[bestCount][0]].day,reviewArr[bestIntervals[bestCount][1]].year,reviewArr[bestIntervals[bestCount][1]].month,reviewArr[bestIntervals[bestCount][1]].day,bestIntervals[bestCount][2]);
    //printf("%d\n",bestIntervals[bestCount][2]);

}

struct Review scanReview() {
    struct Review review;
    scanf("%d-%d-%d %d %4095s", &review.year, &review.month, &review.day, &review.points, review.description);

    return review;
}


int main(void) {


    int memCapacity = 5;
    int size, inputNum;
    char c, newline;
    struct Review *reviewArr = (struct Review *) malloc(memCapacity * sizeof(struct Review));


    if (reviewArr == NULL) {
        exit(EXIT_FAILURE);
    }
    printf("Recenze:\n");
    for (size = 0; size < memCapacity; size++) {

        if (size == memCapacity - 1) {
            memCapacity = 2 * size;
            reviewArr = (struct Review *) realloc(reviewArr, memCapacity * sizeof(struct Review));
        }


        scanf("%c", &c);
        // printf("%c\n", c);
        if (c == '+') {
            reviewArr[size] = scanReview();

            if (validateDate(reviewArr[size].year, reviewArr[size].month, reviewArr[size].day) == 0 ||
                validateStruct(reviewArr, size) == 0) {
                free(reviewArr);
                return 0;
            }


        } else if (c == '?') {


            scanf("%d", &inputNum);
            if (size == 0 || inputNum <= 0) {
                printf("Nespravny vstup.\n");
                free(reviewArr);
                return 0;
            }
            printInterval(reviewArr, inputNum, size);
            //printTotal();
            //printReviews();
        } else if (c == '#') {

            scanf("%d", &inputNum);
            if (size == 0 || inputNum <= 0) {
                printf("Nespravny vstup.\n");
                free(reviewArr);
                return 0;
            }
            printInterval(reviewArr, inputNum, size);
            //printTotal();

        } else {

            printf("Nespravny vstup.\n");
            free(reviewArr);
            return 0;
        }
        if (scanf("%c", &newline) == EOF) {

            free(reviewArr);
            return 0;
        } else if (newline == '\n') {

            continue;
        } else {
            printf("Nespravny vstup.\n");
            free(reviewArr);
            return 0;
        }

    }

    free(reviewArr);
    return 0;
}