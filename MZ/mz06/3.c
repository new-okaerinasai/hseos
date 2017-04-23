#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int year = atoi(argv[1]);
    int mday = atoi(argv[2]);
    int wday = atoi(argv[3]);

    time_t clock;
    time(&clock);
    struct tm* time = localtime(&clock);

    time->tm_year = year - 1900;
    time->tm_mday = mday;
    int count = 0;
    for (int i = 0; i != 12; ++i) {
        time->tm_mon = i;
        time_t now = mktime(time);
        time = localtime(&now);
        if (time->tm_wday == (wday % 7)) {
            ++count;
        }
    }
    printf("%d\n", count);
}
