//DigitalClock.c is a YT Tutorial from https://www.youtube.com/watch?v=4GeYKi7IWDA 

#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t currentTime = time(NULL);
    char *time_string = ctime(&currentTime);

    printf("Current time: %s\n", time_string);

    return 0;
}