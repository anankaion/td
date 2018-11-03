#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#include "todo.h"

int main(int argc, char** argv){
    int c;

    while ((c = getopt(argc, argv, "a:l")) != -1){
        switch (c){
            case 'a':
                add(optarg);
                break;

            case 'l':
                list();
                break;

            default:
                printf("Wrong arguments.\n");
                exit(EXIT_FAILURE);
        }
    }
}