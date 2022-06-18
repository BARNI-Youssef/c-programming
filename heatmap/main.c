#include "heatmap.c"

int main(){
    map M = createMap(15);
    M.head[4][2] = 'A';
    M.head[4][3] = 'A';
    M.head[4][4] = 'A';
    M.head[5][2] = 'A';
    M.head[6][2] = 'A';
    M.head[6][3] = 'A';
    M.head[6][4] = 'A';
    M.head[6][5] = 'A';
    M.head[6][6] = 'A';
    M.head[10][11] = 'B';
    M.head[10][12] = 'B';
    M.head[10][13] = 'B';
    M.head[11][12] = 'B';
    M.head[12][12] = 'B';
    M.head[12][13] = 'B';
    showMap(M);    
    heatmap T = makeheatmap(M);
    showHeatMap(T);
    return 0;
}