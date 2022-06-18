#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct map{
    unsigned dim;
    int** head;
};

struct piece{
    unsigned row;
    unsigned col;
    int** head;
};

struct coord{
    int x;
    int y;
    struct coord* following;
};

struct Piece_cell{
    struct piece pc;
    struct Piece_cell* following;
    struct Piece_cell* previous;
    struct coord* fill;
};

struct list{
    struct Piece_cell* head;
    struct Piece_cell* tail;
    int size;
};

typedef struct map map;
typedef struct piece piece;
typedef struct coord coord;
typedef struct Piece_cell Piece_cell;
typedef struct list list;

map createMap(unsigned);                            /*does what it says*/
piece createPiece(unsigned, unsigned);              /*create the structure if the piece, the returned piece is empty tho*/
void fillPiece(piece*);                             /*take the input from the user to fill the piece*/
void reshapePiece(piece*);                          /*wip*/ /*resize a given shape to avoid illegal inputs*/
void showMap(map);                                  /*does what it says*/
int addMap(Piece_cell*, map*, unsigned, unsigned);  /*add a given piece to a map, at x and y coordinate*/
int adjustPiece(Piece_cell*, map*);                 /*keep trying to add a piece till it succed, if it can't, unlucky :/*/
void addPiece(piece, list*);                        /*add a piece to a list of pieces (list will be used to add the pieces one by one)*/
void addfill(int, int, coord**);                    /*add the coodinate that a piece occupies in a map*/
int arrangeMap(piece, map*);                       /*wip*/ /*add a piece to a map, removing previous pieces to try to fit it*/
void removePiece(Piece_cell*, map*);                /*remove a piece from the map*/
int arrangeList(Piece_cell*, map*);                 /*wip*/ /*tries to fit all the pieces of a given list in the map*/
int movePiece(Piece_cell*, map*);                   /*move a piece by one step*/
int toTheEnd(Piece_cell*);                          /*move a piece to the end of the list, return 0 if succed, 1 if not*/