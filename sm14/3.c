#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {
    char* name = argv[1];
    char buf[1000];
    FILE* fp = fopen(name, "r");
    int isfirst = 1;
    time_t now_abs, before_abs;
    while(fgets(buf, 1000, fp)) {
        int year, month, day, hour, minute, second;
        sscanf(buf, "%04d/%02d/%02d %02d:%02d:%02d", &year, &month, &day, &hour, &minute, &second);
        struct tm now;
        now.tm_year = year - 1900;
        now.tm_mday = day;
        now.tm_mon = month - 1;
        now.tm_sec = second;
        now.tm_min = minute;
        now.tm_hour = hour;
        now.tm_isdst = -1;
        now_abs = mktime(&now);
        if (!isfirst) {
            printf("%ld\n", now_abs - before_abs);
        }
        before_abs = now_abs;
        isfirst = 0;
    }
}
