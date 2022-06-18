#include "map.h"

list L = {NULL, NULL, 0};
int f = 0;

map createMap(unsigned size){
    map M = {size, (int**)malloc(sizeof(int*)*size)};
    for(int i = 0; i < size; i++) M.head[i] = (int*)malloc(sizeof(int)*size);
    for(int j = 0; j < size; j++){
        for(int e = 0; e < size; e++){
            M.head[j][e] = 0;
        } 
    }
    return M;
}

piece createPiece(unsigned row, unsigned col){
    piece P = {row, col, (int**)malloc(sizeof(int*)*row)};
    for(int i = 0; i < row; i++) P.head[i] = (int*)malloc(sizeof(int)*col);
    return P;
}

void fillPiece(piece* P){
    printf("draw your piece, it's shaped like a %u %u matrix\n", P->row, P->col);
    for(int i = 0; i < P->row; i++){
        printf("\n");
        for(int j = 0; j < P->col; j++){
            scanf("%d", &P->head[i][j]); 
            while(P->head[i][j] != 0 && P->head[i][j] != 1){
                printf("invalid input, please retry\n");
                scanf("%d", &P->head[i][j]);
            }
        }
    }
}

void showMap(map M){
    for(int i = 0; i < M.dim; i++){
        printf("||");
        for(int j = 0; j < M.dim; j++) printf("%d ", M.head[i][j]);
        printf("||\n");        
    }
    printf("\n");
}

int addMap(Piece_cell* P, map* M, unsigned x, unsigned y){
    if(x+P->pc.row > M->dim || y+P->pc.col > M->dim) return 1;
    for(int i = x; i < x+P->pc.row; i++){
        for(int j = y; j < y+P->pc.col; j++){
            if(M->head[i][j] == 0){
                M->head[i][j] = P->pc.head[i-x][j-y];
                addfill(i, j, &(P->fill));
            }
            else{
                if(P->pc.head[i-x][j-y] == 1){
                    while(P->fill != NULL){
                        M->head[P->fill->x][P->fill->y] = 0;
                        coord* temp = P->fill;
                        P->fill = P->fill->following;
                        free(temp);
                    }
                    P->fill = NULL;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int adjustPiece(Piece_cell* P, map* M){
    int i = 0; 
    int j = 0;
    while(addMap(P, M, i, j) == 1){
        if(i < M->dim) i++;
        else{
            i=0;
            if(j < M->dim) j++;
            else return 1;
        }
    }
    return 0;
}

/*
void reshapePiece(piece* P){
    for(int i =  0; i < P->row; i++){
        int e = 0;                        printf("(%d %d)\n", P->fill->x, P->fill->y);
                        printf("|%p|\n", temp);
        for(int j = 0; j < P->col) if(P->head[i][j] == 0) e++;
        if(e = P->col){

        }
    } 
}*/

void addPiece(piece P, list* E){
    Piece_cell* C = (Piece_cell*)malloc(sizeof(Piece_cell));
    C->pc = P;
    C->fill = NULL;
    if(E->size == 0){
        C->following = NULL;
        C->previous = NULL;
        E->head = C;
        E->tail = C;
        E->size++;
    }
    else{
        C->previous = E->tail;
        C->following = NULL;
        E->tail->following = C;
        E->tail = C;
        E->size++;
    }
}

void addfill(int x, int y, coord** X){
    if(*X == NULL){
        coord* C = (coord*)malloc(sizeof(coord));
        C->x = x;
        C->y = y;
        C->following = NULL;
        *X = C;
    }
    else{
        coord* temp = *X;
        while(temp->following != NULL) temp = temp->following;
        coord* C = (coord*)malloc(sizeof(coord));
        C->x = x;
        C->y = y;
        temp->following = C;
        C->following = NULL;
    }
}

void removePiece(Piece_cell* P, map* M){
    if(P == NULL) return;
    coord* temp = P->fill;
    while(temp != NULL){
        M->head[temp->x][temp->y] = 0;
        coord* temp1 = temp;
        temp = temp->following;
        free(temp1);
    }
    P->fill = NULL;
}

int arrangeMap(piece P, map* M){
    addPiece(P,&L);
    if(arrangeList(L.tail, M) == 0) return 0;
    else{
        *M = createMap(M->dim+1);
        arrangeList(L.head, M);
    }
}

int arrangeList(Piece_cell* P, map* M){
    if(P == NULL) return 0;
    if(adjustPiece(P, M) == 0) arrangeList(P->following, M);
    else{
        if(P->previous == NULL) return -1;
        if(movePiece(P->previous, M) == 0) arrangeList(P, M);
        else{
            if(P->following == NULL) return 1;
            Piece_cell* temp = P;
            toTheEnd(P);
            arrangeList(temp->previous, M);
        }
    }
}

int movePiece(Piece_cell* P, map* M){
    if(P->fill == NULL) return -1;
    int x = P->fill->x +1;
    int y = P->fill->y;
    removePiece(P, M);
    while(x < M->dim || y < M->dim){
        if(x < M->dim){
            if(addMap(P, M, x, y) == 0) return 0;
            else x++;
        }
        else{
            x = 0;
            y++;
            if(addMap(P, M, x, y) == 0) return 0;
        }
    }
    return 1;
}

int toTheEnd(Piece_cell* P){
    if(P->following == NULL) return 1;
    if(P->previous == NULL){
        P->following->previous =  NULL;
        L.head = P->following;
        P->previous = L.tail;
        P->following = NULL;
        L.tail->following = P;
        L.tail = P;
    }
    P->previous->following = P->following;
    P->following->previous = P->previous;
    P->following = NULL;
    P->previous = L.tail;
    L.tail->following = P;
    L.tail = P;
    return 0;
}