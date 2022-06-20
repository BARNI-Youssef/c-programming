#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct map{
    unsigned dim;
    char** head;
};

struct heatmap
{    
    unsigned dim;
    int** head;
};


struct piece{
    unsigned row;
    unsigned col;
    char** head;
};

typedef struct map map;
typedef struct heatmap heatmap;
typedef struct piece piece;

map createMap(unsigned);    
void showMap(map);
int encercle(heatmap, map);
heatmap makeheatmap(map);