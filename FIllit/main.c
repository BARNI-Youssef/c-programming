#include "map.c"

int main(){
    map M = createMap(3);
    showMap(M);
    piece P = createPiece(1,1);
    fillPiece(&P);
    arrangeMap(P, &M);
    movePiece(L.head, &M);
    showMap(M);
    piece R = createPiece(2,2);
    fillPiece(&R);
    arrangeMap(R,&M);
    showMap(M);
    piece Q = createPiece(3,3);
    fillPiece(&Q);
    arrangeMap(Q,&M);
    showMap(M);
    return 0;
}