#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

struct option long_options[] =  {
    {"a123", required_argument, 0, 'a'},
    {"c456", no_argument, 0, 'c'},
};

int main(int argc, char *argv[]) {

    int c ;
    while((c = getopt_long(argc, argv, "a:c:", long_options, NULL)) != -1) {
        switch(c) {
            case 'n':
                printf("comand is n");
                break;
            case 'a':
                printf("command is a : %s", optarg);
                break;
            case 'c':
                printf("command is c: %s", optarg);
                break;
        }
    }

    return 0;
}
