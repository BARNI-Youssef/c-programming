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
    int visited;
};

struct path_cell{
    struct city* path;
    int nb;
    int max_lenght;
    int total_visits;
    struct path_cell* following;
};

struct charcell{
    char* X;
    struct charcell* following;
    int size;
};

struct train{
    char* current_city;
    int path_num;
    int city_num;
};

typedef struct city city;
typedef struct path_cell path_cell;
typedef struct path_cell* path_list;
typedef struct charcell charcell;
typedef struct charcell* charlist;
typedef struct train train;

#define FILE_OK 0
#define FILE_NOT_EXIST 1
#define FILE_TOO_LARGE 2
#define FILE_READ_ERROR 3

                    /*At this point, can't we just create a folder and put them there, instead of copying 3 times ?*/

unsigned len(char**);                          /*gives the size of an array of strings*/
char* c_read_file(const char*, int*, size_t*); /*takes a file and turn it into a string (shamelessly yoinked from internet)*/
char** strsplit(char*, char);                  /*takes a string and a delemiter and return a array of strings representing all the "words" in the string*/
int check_city(city*, int, char*);        /*check if a given city is in the n-th first elements of an array of cities, if so, return its index*/
city* all_cites(char**);                       /*takes an array of strings and return an array of cities with all the relevant informations*/

                    /*NOW THE FUN BEGINGS... or not, not that impressive either, huh*/

int shortest_path(city*, path_list, int);      /*wait a minute, I've seen this before... copypaste is humanity greatest invention since toilet paper right ?*/
path_list handy_list(city*, path_list, int);   /*transform a list of paths into an array of list, because pointers are annoying :^)*/
void totaly_normal_sort(path_list);            /*just an ordinary sort of paths... wait, can we sort paths ?*/
path_list the_good_paths(path_list);           /*takes the "best paths" among the multiple ones available. but how can we define 'best'?*/
void circuit(int, path_list);                  /*dictate, based on completely universal and unbiaised criterias, how each train should behave to reach his destination, FREEWILL IS AN ILLUSION*/