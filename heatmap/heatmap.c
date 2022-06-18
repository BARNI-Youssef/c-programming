#include "heatmap.h"

map createMap(unsigned size){
    map M = {size, (char**)malloc(sizeof(char*)*size)};
    for(int i = 0; i < size; i++) M.head[i] = (char*)malloc(sizeof(char)*size);
    for(int j = 0; j < size; j++){
        for(int e = 0; e < size; e++){
            M.head[j][e] = '.';
        } 
    }
    return M;
}

heatmap createHeatMap(unsigned size){
    heatmap M = {size, (int**)malloc(sizeof(int*)*size)};
    for(int i = 0; i < size; i++) M.head[i] = (int*)malloc(sizeof(int)*size);
    for(int j = 0; j < size; j++){
        for(int e = 0; e < size; e++){
            M.head[j][e] = -1;
        } 
    }
    return M;
}

void showMap(map M){
    for(int i = 0; i < M.dim; i++){
        printf("||");
        for(int j = 0; j < M.dim; j++) printf("%c ", M.head[i][j]);
        printf("||\n");        
    }
    printf("\n");
}

void showHeatMap(heatmap M){
    for(int i = 0; i < M.dim; i++){
        printf("||");
        for(int j = 0; j < M.dim; j++){
            if(M.head[i][j] == 'A') printf("%c ", M.head[i][j]);
            if(M.head[i][j] == 'B') printf("%c ", M.head[i][j]);
            if(M.head[i][j] != 'A' && M.head[i][j] != 'B') printf("%d ", M.head[i][j]);
        }
        printf("||\n");        
    }
    printf("\n");
}

unsigned scanMap(heatmap M){
    for(int i = 0; i < M.dim; i++){
        for(int j = 0; j < M.dim; j++){
            if(M.head[i][j] == -1) return 1;
        }
    }
    return 0;
}


heatmap makeheatmap(map M){
    heatmap final = createHeatMap(M.dim);
    while(scanMap(final) != 0){
        for(int i = 0; i < M.dim; i++){
            for(int j = 0; j < M.dim; j++){
                if(M.head[i][j] == 'B') final.head[i][j] = M.head[i][j];
                else{
                    if(M.head[i][j] == 'A'){
                        if(i > 0){
                            if(M.head[i-1][j] != 'A' && M.head[i-1][j] != 'B') final.head[i-1][j] = 0;
                            if(j < final.dim-1){
                                if(M.head[i-1][j+1] != 'A' && M.head[i-1][j+1] != 'B'){
                                    final.head[i-1][j+1] = 0;
                                }
                                if(M.head[i][j+1] != 'A' && M.head[i][j+1] != 'B'){
                                    final.head[i][j+1] = 0;                                
                                }
                            }                        
                            if(j > 0){
                                if(M.head[i-1][j-1] != 'A' && M.head[i-1][j-1] != 'B'){
                                    final.head[i-1][j-1] = 0;                                
                                }
                                if(M.head[i][j-1] != 'A' && M.head[i][j-1] != 'B'){
                                    final.head[i][j-1] = 0;                                
                                }
                            }
                        }
                        if(i < final.dim-1){
                            if(M.head[i+1][j] != 'A' && M.head[i+1][j] != 'B') final.head[i+1][j] = 0;
                            if(j < final.dim){
                                if(M.head[i+1][j+1] != 'A' && M.head[i+1][j+1] != 'B'){
                                    final.head[i+1][j+1] = 0;                                
                                }
                            }
                            if(j > 0){
                                if(M.head[i+1][j-1] != 'A' && M.head[i+1][j-1] != 'B'){
                                    final.head[i+1][j-1] = 0;                                
                                }
                            }
                        }
                        final.head[i][j] = M.head[i][j];
                    }
                    else{
                        if(final.head[i][j] != -1){
                            int next = final.head[i][j];
                            if(i > 0){
                                if(M.head[i-1][j] != 'A' && M.head[i-1][j] != 'B' && (next+1 < final.head[i-1][j] ||final.head[i-1][j] < 0)) M.head[i-1][j] = next+1;
                                if(j < final.dim-1){
                                    if(M.head[i-1][j+1] != 'A' && M.head[i-1][j+1] != 'B' && (next+1 < final.head[i-1][j+1] || final.head[i-1][j+1] < 0)){
                                        final.head[i-1][j+1] = next+1;
                                    }
                                    if(M.head[i][j+1] != 'A' && M.head[i][j+1] != 'B' && (next+1 < final.head[i][j+1] || final.head[i][j+1] < 0)){
                                        final.head[i][j+1] = next+1;
                                    }
                                }
                                if(j > 0){
                                    if(M.head[i-1][j-1] != 'A' && M.head[i-1][j-1] != 'B' && (next+1 < final.head[i-1][j-1] || final.head[i-1][j-1] < 0)){
                                        final.head[i-1][j-1] = next+1;                                    
                                    }
                                    if(M.head[i][j-1] != 'A' && M.head[i][j-1] != 'B' && (next+1 < final.head[i][j-1] || final.head[i][j-1] < 0)){
                                        final.head[i][j-1] = next+1;                                    
                                    }
                                }
                            }
                            if(i < final.dim-1){
                                if(M.head[i+1][j] != 'A' && M.head[i+1][j] != 'B' && (next+1 < final.head[i+1][j] || final.head[i+1][j] < 0)) final.head[i+1][j] = next+1;
                                if(j < final.dim-1){
                                    if(M.head[i+1][j+1] != 'A' && M.head[i+1][j+1] != 'B' && (next+1 < final.head[i+1][j+1] || final.head[i+1][j+1] < 0)){
                                        final.head[i+1][j+1] = next+1;
                                    }
                                }                        
                                if(j > 0){
                                    if(M.head[i+1][j-1] != 'A' && M.head[i+1][j-1] != 'B' && (next+1 < final.head[i+1][j-1] || final.head[i+1][j-1] < 0)){
                                        final.head[i+1][j-1] = next+1;
                                    }
                                }
                            }
                        }
                    }
                }
                showHeatMap(final);
                usleep(10000);
                system("clear");
            } 
        }
    }
    return final;
}