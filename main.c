#include <stdio.h>
#include <time.h>
#include <windows.h>

void print_calendar(int, int);
const char* get_month_name(int);
int current_year();
int current_month();
time_t decrease_month();
time_t increase_month();
int first_week_day_of_month();
bool is_leap_year(int);
bool is_thirty_day_month(int);
int days_in_month(int, int);
int calendar_rows(int, int);

struct tm *selected_date;

void print_calendar(int year, int month) {
    const char* days_of_week[] = {
        "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"
    };

    int length = sizeof(days_of_week) / sizeof(days_of_week[0]);

    printf("==================================\n");
    printf("%12d, %s\n", year, get_month_name(month));
    printf("==================================\n");

    for (int day = 0; day < length; day++) {
        printf("%3s  ", days_of_week[day]);

        if (day == 6) {
            printf("\n");
        }
    }

    int first_week_day = first_week_day_of_month();
    int day = 1;
    int rows = calendar_rows(year, month);

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < 7; column++) {
            if (row == 0) {
                if (column < first_week_day) {
                    printf("     ");
                } else {
                    printf("%3d  ", day);
                    day++;
                }
            } else if (day <= days_in_month(year, month)) {
                printf("%3d  ", day);
                day++;
            }
        }

        printf("\n");
    }
}

int calendar_rows(int year, int month) {
    int days = days_in_month(year, month);
    int week_day = first_week_day_of_month();

    days -= (7 - week_day);

    return 35 - days < 7 ? 6 : 5;
}

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool is_thirty_day_month(int month) {
    return month == 3 || month == 5 || month == 8 || month == 10;
}

int days_in_month(int year, int month) {
    if (month == 1) {
        return is_leap_year(year) ? 29 : 28;
    } else if (is_thirty_day_month(month)) {
        return 30;
    } else {
        return 31;
    }
}

int first_week_day_of_month() {
    selected_date->tm_mday -= (selected_date->tm_mday - 1);

    time_t t = mktime(selected_date);

    return localtime(&t)->tm_wday;
}

const char* get_month_name(int month) {
    const char* months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    return months[month];
}

int current_year() {
    return selected_date->tm_year + 1900;
}

int current_month() {
    return selected_date->tm_mon;
}

time_t decrease_month() {
    selected_date->tm_mon--;

    return mktime(selected_date);
}

time_t increase_month() {
    selected_date->tm_mon++;

    return mktime(selected_date);
}

int main(void) {
    time_t t = time(NULL);

    selected_date = localtime(&t);


//    selected_date->tm_year -= 24;
//
//    time_t new_time = mktime(selected_date);
//
//    selected_date = localtime(&new_time);
//    system("cls");
    print_calendar(current_year(), current_month());

    while (true) {
        int ctrl_pressed = GetAsyncKeyState(VK_CONTROL) & 0x8000;
        int alt_pressed = GetAsyncKeyState(VK_MENU) & 0x8000;

        if (ctrl_pressed) {
            Sleep(500);
            t = decrease_month();
            selected_date = localtime(&t);
//            system("cls");
            print_calendar(current_year(), current_month());
        }

        if (alt_pressed) {
            break;
        }
    }

    return 0;
}
