#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Review {
    int day;
    int month;
    int year;
    int points;
    char description[4097];
};

/**
 * Determine if year is a leap year.
 * @return 1 if year is a leap year, otherwise 0
 */
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
/**
 * Determine how many leap years are in the interval <1800,int a> where int a is parameter
 * @return the number of leap years in that period
 */

int countLeapYears(int y) {

    int leapYears = 0;
// Input years are entered in a reasonable range (1800 - 3000), that's why we started iterating from 1800.
    for (int i = 1800; i < y; ++i) {
        if (leapYear(i) == 1) { leapYears++; }
    }

    return leapYears;

}
/**
 * Determine how many days are in a given month
 * @return the number of days in a given month
 */
int daysInOneMonth(int year, int month) {

    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (leapYear(year) == 1) { monthDays[1] = 29; }
    return monthDays[month - 1];

}
/**
 * Determine the number of days in the previous months within the specified year and a month
 * @return the number of days in the previous months
 */
int daysInMonths(int y, int m) {

    int days = 0;

    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (leapYear(y) == 1) { monthDays[1] = 29; }

    for (int i = 0; i < m - 1; ++i) {
        days += monthDays[i];
    }

    return days;

}
/**
 * Determine if a given date is valid.
 * @return 1 if a date is valid, otherwise 0
 */
int validateDate(int y, int m, int d) {
    // Input years are entered in a reasonable range (1800 - 3000), that's why years before 1800 are not valid
    if (y < 1800) {

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
/**
 * Determine if a given struct Review is valid.
 * @return 1 if a date is valid, otherwise 0
 */
int validateStruct(struct Review *reviewArr, int size) {

    if (size > 0) {
        //check if the date entered in the review is smaller than the date in the previous review,
        int sum2 = (reviewArr[size].year - 1800) * 365 + reviewArr[size].day +
                   daysInMonths(reviewArr[size].year, reviewArr[size].month) + countLeapYears(reviewArr[size].year);
        int sum1 = (reviewArr[size - 1].year - 1800) * 365 + reviewArr[size - 1].day +
                   daysInMonths(reviewArr[size - 1].year, reviewArr[size - 1].month) +
                   countLeapYears(reviewArr[size - 1].year);
        if (sum2 < sum1) {

            return 0;
        }

    }
    //check if the points are at least 1.
    if (reviewArr[size].points <= 0) {

        return 0;
    }
    return 1;


}

void printInterval(struct Review *reviewArr, int targetSum, int size, int printReview) {

    int count = 0;
    int bestDiff = INT_MAX;
    int bestStart = 0, bestEnd = 0;
    int start;
    int i, x = 0;
    int nextSkip = INT_MAX;
    for (int g = 0; g < size; ++g) {

        int currentSum = 0;
        start = g;
        if (g == nextSkip) {
            while (g < size && reviewArr[g].day == reviewArr[start].day &&
                   reviewArr[g].month == reviewArr[start].month &&
                   reviewArr[g].year == reviewArr[start].year) {

                g++;
            }

        }
        nextSkip = INT_MAX;
        for (i = g; i < size; ++i) {


            start = i;
            x = 0;

            while (i < size && reviewArr[i].day == reviewArr[start].day &&
                   reviewArr[i].month == reviewArr[start].month &&
                   reviewArr[i].year == reviewArr[start].year) {
                currentSum += reviewArr[i].points;

                i++;
                x++;
                if (x == 2 && nextSkip == INT_MAX) {

                    nextSkip = i - 1;
                }
            }
            if (x >= 1) {
                i--;
            }

            int currentDiff = abs(targetSum - currentSum);

            if (currentDiff < bestDiff || (currentDiff == bestDiff && i > bestEnd)) {
                bestDiff = currentDiff;
                count = currentSum;
                bestStart = g;
                bestEnd = i;

            }

        }

    }
    printf("%d-", reviewArr[bestStart].year);
    if (reviewArr[bestStart].month < 10) { printf("0%d-", reviewArr[bestStart].month); }
    else {
        printf("%d-", reviewArr[bestStart].month);
    }
    if (reviewArr[bestStart].day < 10) { printf("0%d - ", reviewArr[bestStart].day); }
    else {
        printf("%d - ", reviewArr[bestStart].day);
    }
    printf("%d-", reviewArr[bestEnd].year);

    if (reviewArr[bestEnd].month < 10) { printf("0%d-", reviewArr[bestEnd].month); }
    else {
        printf("%d-", reviewArr[bestEnd].month);
    }
    if (reviewArr[bestEnd].day < 10) { printf("0%d: ", reviewArr[bestEnd].day); }
    else {
        printf("%d: ", reviewArr[bestEnd].day);
    }
    printf("%d\n", count);

    if (printReview == 1)
        for (int j = bestStart; j <= bestEnd; ++j) {

            printf("  %d: %s\n", reviewArr[j].points, reviewArr[j].description);


        }



}

struct Review scanReview() {
    struct Review review;
    scanf("%d-%d-%d %d %4096s", &review.year, &review.month, &review.day, &review.points, review.description);

    return review;
}


int main(void) {


    int memCapacity = 5;
    int size = 0, inputNum, res;
    char c, newline;
    struct Review *reviewArr = (struct Review *) malloc(memCapacity * sizeof(struct Review));


    if (reviewArr == NULL) {
        exit(EXIT_FAILURE);
    }
    printf("Recenze:\n");
    while (size < memCapacity) {

        if (size == memCapacity - 1) {
            memCapacity = 2 * size;
            reviewArr = (struct Review *) realloc(reviewArr, memCapacity * sizeof(struct Review));
        }


        res = scanf("%c", &c);
        // printf("%c\n", c);


        if (res == EOF) {

            free(reviewArr);
            return 0;
        } else if (res != 1) {

            printf("Nespravny vstup.\n");
            free(reviewArr);
            return 0;
        }
        if (c == '+') {
            reviewArr[size] = scanReview();

            if (validateDate(reviewArr[size].year, reviewArr[size].month, reviewArr[size].day) == 0 ||
                validateStruct(reviewArr, size) == 0) {

                printf("Nespravny vstup.\n");
                free(reviewArr);
                return 0;
            }
            size++;

        } else if (c == '?') {


            res=scanf("%d", &inputNum);
            if (res == EOF) {

                free(reviewArr);
                return 0;
            } else if (res != 1) {

                printf("Nespravny vstup.\n");
                free(reviewArr);
                return 0;
            }
            if (size == 0 || inputNum <= 0) {
                printf("Nespravny vstup.\n");
                free(reviewArr);
                return 0;
            }

            printInterval(reviewArr, inputNum, size, 1);

        } else if (c == '#') {

            res=scanf("%d", &inputNum);
            if (res == EOF) {

                free(reviewArr);
                return 0;
            } else if (res != 1) {

                printf("Nespravny vstup.\n");
                free(reviewArr);
                return 0;
            }
            if (size == 0 || inputNum <= 0) {
                printf("Nespravny vstup.\n");
                free(reviewArr);
                return 0;
            }

            printInterval(reviewArr, inputNum, size, 0);


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