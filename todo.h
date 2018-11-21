//
// Created by sus on 11/3/18.
//

#ifndef TD_TODO_H
#define TD_TODO_H

#define PATH "todos/"
#define PATH_TICKED "ticked/"
#define MAXBUF 50
#define MAXFILENAME 256

int tick(const char* todo);
int delete(const char* todo);
int add(const char* todo);
int list();

#endif //TD_TODO_H
