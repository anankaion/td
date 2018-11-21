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

int tick(const char* todo){
    FILE *fp1;
    FILE *fp2;

    char* line = NULL;
    size_t lline = 0;

    char from[MAXFILENAME];
    char to[MAXFILENAME];

    strcpy(from, PATH);
    strcat(from, todo);

    strcpy(to, PATH_TICKED);
    strcat(to, todo);

    if ((fp1 = fopen(from, "r")) == NULL){
        printf("First file could not be openend.\n");
        exit(EXIT_FAILURE);
    }

    if ((fp2 = fopen(to, "w")) == NULL){
        printf("Second file could not be openend.\n");
        exit(EXIT_FAILURE);
    }

    while ((getline(&line, &lline, fp1)) != -1){
        fprintf(fp2, "%s", line);
    }

    fclose(fp1);
    fclose(fp2);

    if (remove(from)){
        return EXIT_SUCCESS;
    } else{
        return EXIT_FAILURE;
    }
}

int delete(const char* todo){
    char filename[MAXFILENAME];

    strcpy(filename, PATH);
    strcat(filename, todo);

    if (remove(filename)){
        return EXIT_SUCCESS;
    } else{
        printf("File not found.\n");
        return EXIT_FAILURE;
    }
}

int add(const char* todo){
    FILE *fp;
    char date[MAXBUF];
    char filename[MAXFILENAME];

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    strftime(date, MAXFILENAME, "%Y %b %d %H:%M:%S", tm);

    strcpy(filename, PATH);
    strcat(filename, todo);

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