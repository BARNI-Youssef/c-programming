#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

struct city{
    char* name;
    struct city* sourding;
    int nb_sourding;
    int dist_to_E;
};

struct path_cell{
    struct city* path;
    int nb;
    int max_lenght;
    struct path_cell* following;
};

struct charcell{
    char* X;
    struct charcell* following;
    int size;
};

typedef struct city city;
typedef struct path_cell path_cell;
typedef struct path_cell* path_list;
typedef struct charcell charcell;
typedef struct charcell* charlist;

#define FILE_OK 0
#define FILE_NOT_EXIST 1
#define FILE_TOO_LARGE 2
#define FILE_READ_ERROR 3

                    /*Nothing new here, a mere ctrl+C ctrl+V, lazyness at it peaks*/

unsigned len(char**);                          /*gives the size of an array of strings*/
char* c_read_file(const char*, int*, size_t*); /*takes a file and turn it into a string (shamelessly yoinked from internet)*/
char** strsplit(char*, char);                  /*takes a string and a delemiter and return a array of strings representing all the "words" in the string*/
int check_city(city*, int, char*);        /*check if a given city is in the n-th first elements of an array of cities, if so, return its index*/
city* all_cites(char**);                       /*takes an array of strings and return an array of cities with all the relevant informations*/

                    /*Don't get lured by the different name, it's the same as before...*/

int shortest_path(city*, path_list, int); /*takes a array of cities and returns all the shortest paths from S to E*/