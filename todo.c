//
// Created by sus on 11/3/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "todo.h"

int add(const char* todo){
    FILE *fp;
    char date[MAXDATE];
    char filename[MAXFILENAME];

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    strftime(date, MAXFILENAME, "%Y_%b_%d_%H_%M_%S", tm);

    strcpy(filename, PATH);
    strcat(filename, date);

    if ((fp = fopen(filename, "w")) == NULL){
        printf("Could not open file to write.\n");
        return -1;
    }

    fprintf(fp, "%s\n", date);
    fprintf(fp, "%s\n", getlogin());
    fprintf(fp, "%s\n", todo);

    fclose(fp);

    return 0;
}

int list(){
    DIR *d;
    struct dirent *dir;

    FILE *fp;

    char filename[MAXFILENAME];
    char *line = NULL;
    size_t size = 0;
    int missedfiles = 0;

    if (!(d = opendir(PATH))){
        printf("Could not open directory.\n");
        return -1;
    }

    while ((dir = readdir(d)) != NULL){
        if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0)){
            strcpy(filename, PATH);
            strcat(filename, dir->d_name);

            if ((fp = fopen(filename, "r"))){
                getline(&line, &size, fp);
                printf("Date:\t%s", line);

                getline(&line, &size, fp);
                printf("User:\t%s", line);

                getline(&line, &size , fp);
                printf("ToDo:\t%s\n", line);
            } else{
                missedfiles++;
            }
        }

    }

    return missedfiles;
}