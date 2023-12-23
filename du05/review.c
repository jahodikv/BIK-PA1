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
 * @param[in] year year to check
 * @return 1 if year is a leap year, otherwise 0
 */
int leapYear(int year) {

    if (year % 4000 == 0) {
        return 1;
    } else if (year % 400 == 0) {
        return 1;
    } else if (year % 100 == 0) {
        return 0;
    } else if (year % 4 == 0) {
        return 1;
    } else {
        return 0;
    }

}

/**
 * Determine how many leap years are in the interval <1800,int year>.
 * @param[in] year  year to check
 * @return the number of leap years in that period
 */

int countLeapYears(int year) {

    int leapYears = 0;
// Input years are entered in a reasonable range (1800 - 3000), that's why we started iterating from 1800.
    for (int i = 1800; i < year; ++i) {
        if (leapYear(i) == 1) { leapYears++; }
    }

    return leapYears;

}

/**
 * Determine how many days are in a given month
 * @param[in] year  year from date
 * @param[in] month  month from date
 * @return the number of days in a given month
 */
int daysInOneMonth(int year, int month) {

    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (leapYear(year) == 1) { monthDays[1] = 29; }
    return monthDays[month - 1];

}

/**
 * Determine the number of days in the previous months within the specified year and a month
 * @param[in] year  year from date
 * @param[in] month  month from date
 * @return the number of days in the previous months
 */
int daysInMonths(int year, int month) {

    int days = 0;

    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (leapYear(year) == 1) { monthDays[1] = 29; }

    for (int i = 0; i < month - 1; ++i) {
        days += monthDays[i];
    }

    return days;

}

/**
 * Determine if a given date is valid.
 * @param[in] year  year from date
 * @param[in] month  month from date
 * @param[in] day  day from date

 * @return 1 if a date is valid, otherwise 0
 */
int validateDate(int year, int month, int day) {
    // Input years are entered in a reasonable range (1800 - 3000), that's why years before 1800 are not valid
    if (year < 1800) {

        return 0;
    }
    if (month < 1 || month > 12) {
        return 0;
    }
    if (day < 1) {
        return 0;
    }
    if (day > daysInOneMonth(year, month)) {
        return 0;
    }
    return 1;

}

/**
 * Determine if a given struct Review is valid.
 * Non valid means:
 * - the date entered in the review is smaller than the date in the previous review
 * - non-numeric, zero or negative rating value in the review (rating must be at least 1)
 * @param[in] reviewArr  pointer to the Review
 * @param[in] numOfReviews number of reviews
 * @return 1 if a date is valid, otherwise 0
 */
int validateStruct(struct Review *reviewArr, int numOfReviews) {

    if (numOfReviews > 0) {
        //check if the date entered in the review is smaller than the date in the previous review,
        int sum2 = (reviewArr[numOfReviews].year - 1800) * 365 + reviewArr[numOfReviews].day +
                   daysInMonths(reviewArr[numOfReviews].year, reviewArr[numOfReviews].month) + countLeapYears(reviewArr[numOfReviews].year);
        int sum1 = (reviewArr[numOfReviews - 1].year - 1800) * 365 + reviewArr[numOfReviews - 1].day +
                   daysInMonths(reviewArr[numOfReviews - 1].year, reviewArr[numOfReviews - 1].month) +
                   countLeapYears(reviewArr[numOfReviews - 1].year);
        if (sum2 < sum1) {

            return 0;
        }

    }
    //check if the points are at least 1.
    if (reviewArr[numOfReviews].points <= 0) {

        return 0;
    }
    return 1;


}

/**
 * Function to print the points and the review description
 * Format:
 * 10: Short_review
 * @param[in] reviewArr  pointer to the Review
 */
void printReview(struct Review *review) {
    printf("  %d: %s\n", review->points, review->description);
}

/**
 * Function to print the date interval and the sum of points
 * Function printReview is used inside
 * Format:
 * 2023-11-10 - 2023-11-10: 78
 * or (based on value of print)
 * 2023-11-10 - 2023-11-10: 78
 * 10: Short_review
 * 53: Long_review
 * @param[in] reviewArr  pointer to the Review
 * @param[in] start starting position of the interval in the reviewArr
 * @param[in] end  ending position of the interval in the reviewArr
 * @param[in] totalPoints sum of the points from the interval
 * @param[in] print 1 if we want to print all the reviews from the interval else 0
 */
void printInterval(struct Review *reviewArr, int start, int end, int totalPoints, int print) {
    printf("%d-%02d-%02d - %d-%02d-%02d: %d\n",
           reviewArr[start].year, reviewArr[start].month, reviewArr[start].day,
           reviewArr[end].year, reviewArr[end].month, reviewArr[end].day,
           totalPoints);
    if (print == 1) {
        for (int j = start; j <= end; ++j) {
            printReview(&reviewArr[j]);
        }
    }

}

/**
 * Function to find a interval with the closes sum of points to the int targetSum value.
 * Function printInterval is used inside
 * @param[in] reviewArr  pointer to the Review
 * @param[in] targetSum target sum of the interval
 * @param[in] numOfReviews number of reviews
 * @param[in] printReview 1 if we want to print all the reviews from the interval else 0
 */
void findClosestInterval(struct Review *reviewArr, int targetSum, int numOfReviews, int printReview) {


    int bestStart = 0, bestEnd = 0, count = 0, nextSkip = INT_MAX, bestDiff = INT_MAX;
    int currentDiff = 0, reviewsInDay = 0;
    for (int g = 0; g < numOfReviews; ++g) {
        int currentSum = 0;
        int start = g;

        if (g == nextSkip) {
            while (g < numOfReviews && reviewArr[g].day == reviewArr[start].day &&
                   reviewArr[g].month == reviewArr[start].month &&
                   reviewArr[g].year == reviewArr[start].year) {
                g++;
            }
        }

        nextSkip = INT_MAX;

        for (int i = g; i < numOfReviews; ++i) {
            start = i;
            reviewsInDay = 0;
            //cycle to skipping reviews from the same day
            while (i < numOfReviews && reviewArr[i].day == reviewArr[start].day &&
                   reviewArr[i].month == reviewArr[start].month &&
                   reviewArr[i].year == reviewArr[start].year) {
                currentSum += reviewArr[i].points;
                i++;
                reviewsInDay++;

                if (reviewsInDay == 2 && nextSkip == INT_MAX) {
                    nextSkip = i - 1;
                }
            }
            //If it has been processed for at least one day, it decrements i so that the same review is not processed repeatedly.
            if (reviewsInDay >= 1) {
                i--;
            }
            currentDiff = abs(targetSum - currentSum);
            //checking if current difference is the best
            if (currentDiff < bestDiff || (currentDiff == bestDiff && i > bestEnd)) {
                bestDiff = currentDiff;
                count = currentSum;
                bestStart = g;
                bestEnd = i;
            }
        }
    }

    printInterval(reviewArr, bestStart, bestEnd, count, printReview);
}

/**
 * Function to scan the user input
 * Ideal format of the input:
 * 2023-11-10 10 Short_review
 * @return the scanned review
 */
struct Review scanReview(void ) {
    struct Review review;
    scanf("%d-%d-%d %d %4096s", &review.year, &review.month, &review.day, &review.points, review.description);

    return review;
}

/**
 * Function prints error message, frees the memory and ends the program.
 * @param[in] reviewArr  pointer to the Review
 */
void handleError(struct Review *reviewArr) {
    printf("Nespravny vstup.\n");
    free(reviewArr);
    exit(1);
}

int main(void) {


    int memCapacity = 5;
    int numOfReviews = 0, inputNum, res;
    char c, newline;
    struct Review *reviewArr = (struct Review *) malloc(memCapacity * sizeof(struct Review));

    printf("Recenze:\n");
    while (numOfReviews < memCapacity) {

        if (numOfReviews == memCapacity - 1) {
            memCapacity = 2 * numOfReviews;
            reviewArr = (struct Review *) realloc(reviewArr, memCapacity * sizeof(struct Review));
        }
        //scanning the first character
        res = scanf("%c", &c);

        if (res == EOF) {

            free(reviewArr);
            return 0;
        } else if (res != 1) {
            handleError(reviewArr);
        }
        //choosing a state based on the first character
        if (c == '+') {
            reviewArr[numOfReviews] = scanReview();

            if (validateDate(reviewArr[numOfReviews].year, reviewArr[numOfReviews].month, reviewArr[numOfReviews].day) == 0 ||
                validateStruct(reviewArr, numOfReviews) == 0) {
                handleError(reviewArr);
            }
            numOfReviews++;

        } else if (c == '?' || c == '#') {

            //scanning target
            res = scanf("%d", &inputNum);
            if (res == EOF) {

                free(reviewArr);
                return 0;
            } else if (res != 1) {

                handleError(reviewArr);
            }
            if (numOfReviews == 0 || inputNum <= 0) {
                handleError(reviewArr);
            }
            if (c == '?') {
                findClosestInterval(reviewArr, inputNum, numOfReviews, 1);
            } else {

                findClosestInterval(reviewArr, inputNum, numOfReviews, 0);
            }


        } else {

            handleError(reviewArr);
        }
        //scanning the last character
        if (scanf("%c", &newline) == EOF) {

            free(reviewArr);
            return 0;
        } else if (newline == '\n') {
            continue;
        } else {
            handleError(reviewArr);
        }

    }

    free(reviewArr);
    return 0;
}