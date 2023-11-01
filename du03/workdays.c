#ifndef __PROGTEST__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct {
    int m_TotalDays;
    int m_WorkDays;
} TResult;
#endif /* __PROGTEST__ */

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
        if (leapYear(i) == 1) { leapYears++; };
    }

    //printf("%d", leapYears);
    return leapYears;

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

int publicHoliday(int m, int d) {

    if (m == 1 && d == 1) { return 1; }

    if (m == 5 && d == 1) { return 1; }
    if (m == 5 && d == 8) { return 1; }
    if (m == 7 && d == 5) { return 1; }
    if (m == 7 && d == 6) { return 1; }
    if (m == 9 && d == 28) { return 1; }
    if (m == 10 && d == 28) { return 1; }
    if (m == 11 && d == 17) { return 1; }
    if (m == 12 && d == 24) { return 1; }
    if (m == 12 && d == 25) { return 1; }
    if (m == 12 && d == 26) { return 1; }


    return 0;

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

    int days = 31;
    if (m == 2) {
        days = 28;
        if (leapYear(y) == 1) {
            days = 29;
        }
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        days = 30;
    }

    if (d > days) {
        return 0;
    }
    return 1;

}
int checkDates(int y1, int m1, int d1,
               int y2, int m2, int d2){







}
bool isWorkDay(int y, int m, int d) {
    int day;
    int year = y;
    //Tomohiko Sakamoto method
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    day = (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;


    //printf("%d\n",day);

    if (day == 0 || day == 6) {

        // printf("weekend");
        return false;
    }
    if (publicHoliday(m, d) == 1) {
        //printf("hollidaz");
        return false;

    }
    if (validateDate(year, m, d) == 0) {

        return false;
    }

    return true;

}

TResult countDays(int y1, int m1, int d1,
                  int y2, int m2, int d2) {
    TResult r;

    if ((validateDate(y1,m1,d1)==false)||(validateDate(y2,m2,d2)==false)){
        r.m_TotalDays=-1;
        return r;

    }
    int sum1;
    int sum2;
    int sum;
    int q = daysInMonths(y1, m1);
    int z = countLeapYears(y1);
    sum1 = (y1 - 2000) * 365 + d1 + q + z;
    sum2 = (y2 - 2000) * 365 + d2 + daysInMonths(y2, m2) + countLeapYears(y2);
    if (sum2 - sum1 == 0) {
        r.m_TotalDays = 1;
    }
    if (sum2 - sum1 < 0) {
        r.m_TotalDays = -1;
        return r;
    }
    r.m_TotalDays = sum2 - sum1+1;
    //printf("%d", r);
    return r;

}


#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    TResult r;
    int y, m, d;
    int y1, m1, d1;
    int z;
    //  scanf("%d %d %d", &y, &m,&d);
    //   scanf("%d %d %d", &y1, &m1,&d1);
    // isWorkDay(y,m,d);
    //   countDays(y,m,d,y1,m1,d1);
    //z = countLeapYears(2023);
    //printf("%d", z);
    assert (isWorkDay(2023, 10, 10));

    assert (!isWorkDay(2023, 11, 11));

    assert (!isWorkDay(2023, 11, 17));

    assert (!isWorkDay(2023, 11, 31));

    assert (!isWorkDay(2023, 2, 29));

    assert (!isWorkDay(2004, 2, 29));

    assert (isWorkDay(2008, 2, 29));

    assert (!isWorkDay(2001, 2, 29));

    assert (!isWorkDay(1996, 1, 2));

    r = countDays(2023, 11, 1,
                  2023, 11, 30);
    assert (r.m_TotalDays == 30);
    //assert (r.m_WorkDays == 21);

    r = countDays(2023, 11, 1,
                  2023, 11, 17);
    assert (r.m_TotalDays == 17);
    //assert (r.m_WorkDays == 12);

    r = countDays(2023, 11, 1,
                  2023, 11, 1);
    assert (r.m_TotalDays == 1);
    //assert (r.m_WorkDays == 1);

    r = countDays(2023, 11, 17,
                  2023, 11, 17);
    assert (r.m_TotalDays == 1);
    //assert (r.m_WorkDays == 0);

    r = countDays(2023, 1, 1,
                  2023, 12, 31);
    assert (r.m_TotalDays == 365);
    //assert (r.m_WorkDays == 252);

    r = countDays(2024, 1, 1,
                  2024, 12, 31);
    assert (r.m_TotalDays == 366);
    //assert (r.m_WorkDays == 254);

    r = countDays(2000, 1, 1,
                  2023, 12, 31);
    assert (r.m_TotalDays == 8766);
    //assert (r.m_WorkDays == 6072);

    r = countDays(2001, 2, 3,
                  2023, 7, 18);
    assert (r.m_TotalDays == 8201);
    //assert (r.m_WorkDays == 5682);

    r = countDays(2021, 3, 31,
                  2023, 11, 12);
    assert (r.m_TotalDays == 957);
    //assert (r.m_WorkDays == 666);

    r = countDays(2001, 1, 1,
                  2000, 1, 1);
    assert (r.m_TotalDays == -1);
    //assert (r.m_WorkDays == -1);

    r = countDays(2001, 1, 1,
                  2023, 2, 29);
    assert (r.m_TotalDays == -1);
    //assert (r.m_WorkDays == -1);

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
