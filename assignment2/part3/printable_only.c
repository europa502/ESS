// gcc -m32 -fno-stack-protector -z execstack -g -o printable_only printable_only.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#define LEN 90

// Handel buffering
void ignore_me_init_buffering()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

// Kill the program after 60 seconds
void kill_on_timeout(int sig)
{
    if (sig == SIGALRM)
    {
        printf("[!] Anti DoS Signal.\n");
        exit(0);
    }
}

void ignore_me_init_signal()
{
    signal(SIGALRM, kill_on_timeout);
    alarm(60);
}

void start(void)
{
    char buf[LEN] = "\0";
    int len;
    printf("You are dumping your trash in dumpster number: %p\n", buf);
    printf("Enter the size of trash you're throwing: ");
    scanf("%d", &len);
    fflush(stdin);
    if (len > LEN)
    {
        printf("I cannot accept to much trash in one go!\n");
        exit(0);
    }
    printf("Enter your trash: ");
    int input_len = read(0, buf, (unsigned)len);
    fflush(stdin);
    // Check if the input contains a non-printable character
    for (int i = 0; i < LEN; i++)
    {
        if (buf[i] < 0x20 || buf[i] > 0x7e)
        {
            printf("You are not allowed to throw non-printable characters.\n");
            exit(0);
        }
    }
    printf("Dumped your trash.\n");
}

void banner()
{
    printf("                                                                                \n           (/////////////////////////////////////////////////////////*          \n         (((//////////////////////////////////////////////////////////(/        \n        ((((////////////////////////////////////////////////////////((((*       \n       /(((((///////////////////////////////////////////////////////(((((,      \n      (((((((//////////////////////////////////////////////////////(((((((      \n      ,*******************************************************************      \n       *******************************************************************      \n       ******************************************************************,      \n       ******************************************************************.      \n       ,*****************************************************************       \n        *********/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*//       \n        /**********************//*,,/,         *////////////////////////*       \n        *////////////////////*/.      .,         ///////////////////////.       \n        ,////////////////////*         */          *////////////////////        \n         ///////////////////,         ////,       //////////////////////        \n         //////////////////////*    .////*****,,,//////////////////////*        \n         //////////////**,,*,,,////*//////////////.   /////////////////.        \n         .//////////////*       //////////////.        ,///////////////         \n          /////////////.         */////////////*         //////////////         \n          /////////////        //////////////////       ,//////////////         \n          (/////////////,    ,/////////////( //////**//*//////////////.         \n          ,///////////////. /          ///.           ////////////////          \n           ////////////////*.          //.          ./////////////////          \n           //////////////////,         (/(/        *//////////////////          \n           //(/(/(/(/(/(/(/(//(//(/(/(/(/(/(.//(///(/(/(/(/(/(/(/(/(/.          \n           ,(((((((((((((((((((((((((((((((((/(((((((((((((((((((((((           \n            ((((((((((((((((((((((((((((((((((((((((((((((((((((((((/           \n            ((((((((((((((((((((((((((((((((((((((((((((((((((((((((/           \n            /(((((((((((((((((((((((((((((((((((((((((((((((((((((((.           \n            ,(((((((((((((((((((((((((((((((((((((((((((((((((((((((            \n                                                                                \n");
}

int main()
{
    ignore_me_init_buffering();
    ignore_me_init_signal();
    banner();
    start();

    return 0;
}