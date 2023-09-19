#include <stdio.h>

const unsigned long millis_sec = 1000UL;
const unsigned long millis_minute = millis_sec * 60UL;
const unsigned long millis_hour = millis_minute * 60UL;
const unsigned long millis_day = millis_hour * 24UL;

int main() {
    unsigned long millis = 1000000000UL;
    unsigned long days, hours, minutes, secs;

    days = millis / millis_day;
    millis %= millis_day;

    hours = millis / millis_hour;
    millis %= millis_hour;

    minutes = millis / millis_minute;
    millis %= millis_minute;

    secs = millis / millis_sec;
    printf("%02lu-%02lu-%02lu-%02lu", days, hours, minutes, secs);
}