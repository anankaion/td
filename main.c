#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <memory.h>

#include "todo.h"

int main(int argc, char** argv){
    int c;

    while ((c = getopt(argc, argv, "a:ld:")) != -1){
        switch (c){
            case 'a':
                add(optarg);
                break;

            case 'l':
                list();
                break;

            case 'd':
                delete(optarg);
                break;

            default:
                printf("Wrong arguments.\n");
                exit(EXIT_FAILURE);
        }
    }
}