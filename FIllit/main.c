#include "map.c"

int main(){
    map M = createMap(3);
    M.head[2][0] = 1;
    showMap(M);
    piece P = createPiece(2,1);
    fillPiece(&P);
    arrangeMap(P, &M);
    movePiece(L.head, &M);
    showMap(M);
    piece R = createPiece(2,2);
    fillPiece(&R);
    arrangeMap(R,&M);
    piece Q = createPiece(2,3);
    fillPiece(&Q);
    arrangeMap(Q,&M);
    showMap(M);
    return 0;
}