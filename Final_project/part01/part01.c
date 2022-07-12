#include "part01.h"

unsigned len(char** str){
    unsigned n = 0;
    while(strcmp(str[n], "\0") != 0) n++;   
    return n;
}

char * c_read_file(const char * f_name, int * err, size_t * f_size) {
    char * buffer;
    size_t length;
    FILE * f = fopen(f_name, "rb");
    size_t read_length;
    
    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        
        // 1 GiB; best not to load a whole large file in one string
        if (length > 1073741824) {
            *err = FILE_TOO_LARGE;
            
            return NULL;
        }
        
        buffer = (char *)malloc(length + 1);
        
        if (length) {
            read_length = fread(buffer, 1, length, f);
            
            if (length != read_length) {
                 free(buffer);
                 *err = FILE_READ_ERROR;

                 return NULL;
            }
        }
        
        fclose(f);
        
        *err = FILE_OK;
        buffer[length] = '\0';
        *f_size = length;
    }
    else {
        *err = FILE_NOT_EXIST;
        
        return NULL;
    }
    
    return buffer;
}

char** strsplit(char* str, char delim){
    int count = 0;
    charlist L = NULL;
    charlist temp = L;
    int f = 0;
    int i = 0;
    while(str[i] != '\0'){
        int j = i;
        while(str[j] != delim && str[j] != '\0') j++;
        if(j != i){
            charcell* C;
            C = (charcell*)malloc(sizeof(charcell));
            C->following = NULL;
            C->X = (char*)malloc(sizeof(char)*(j-i+1));
            int e = 0;
            for(e = 0; e < j-i; e++) C->X[e] = str[e+i];          
            C->X[e+1] == '\0';
            if( f == 0){
                L = C;
                temp = C;
                f = 2;
            }
            temp->following = C;
            temp = temp->following;
            temp->size = j-i;
            count ++;
        }
        if(str[j] != '\0') j++;
        i = j;
    }
    char** final = (char**)malloc(sizeof(char*)*(count+1));
    temp = L;
    for(int e = 0; e < count; e++){
        final[e] = malloc(sizeof(char)*(temp->size));
        final[e] = temp->X;
        final[e][temp->size] = '\0';
        temp = temp->following;
        free(L);
    }
    final[count] = "\0";
    return final;
}
    
int check_city(city* list, int size, char* name){
    for(int i = 0; i < size; i++){
        if(strcmp(list[i].name, name) == 0) return i;
    }
    return -1;
}

city* all_cities(char** ch){
    city* final = (city*)malloc(atoi((ch[1]))*sizeof(city));
    int i = 0; 
    for(int j = 2; j < len(ch); j++){
        char** names = strsplit(ch[j], '-');
        if(check_city(final, i, names[0]) == -1){
            city* add = (city*)malloc(sizeof(city));
            add->name = names[0];
            add->sourding = (city*)malloc(atoi(ch[1])*sizeof(city));
            add->nb_sourding = 0;
            if(strcmp("E", add->name) == 0) add->dist_to_E = 0;
            else add->dist_to_E = INT_MAX;
            final[i] = *add;
            i++;
        }
        if(check_city(final, i, names[1]) == -1){
            city* add = (city*)malloc(sizeof(city));
            add->name = names[1];
            add->sourding = (city*)malloc(sizeof(ch[1])*sizeof(city));
            add->nb_sourding = 0;
            if(strcmp("E", add->name) == 0) add->dist_to_E = 0;
            else add->dist_to_E = INT_MAX;
            final[i] = *add;
            i++;
        }
        int ind_city_A = check_city(final, i, names[0]);
        int ind_city_B = check_city(final, i, names[1]);
        if(check_city(final[ind_city_A].sourding, final[ind_city_A].nb_sourding, names[1]) == -1){
            final[ind_city_A].sourding[final[ind_city_A].nb_sourding] = final[ind_city_B];
            final[ind_city_A].nb_sourding ++;
        }
        if(check_city(final[ind_city_B].sourding, final[ind_city_B].nb_sourding, names[0]) == -1){
            final[ind_city_B].sourding[final[ind_city_B].nb_sourding] = final[ind_city_A];
            final[ind_city_B].nb_sourding ++;
        }
    }
    return final;
}

int count = 0;

int all_paths(city* cities, path_list list, int ind){
    int n = list->nb-1;
    for(int i = ind; i < list->path[n].nb_sourding; i++){
        if(check_city(list->path, list->nb, list->path[n].sourding[i].name) == -1){
            list->path[n+1] = cities[check_city(cities,list->max_lenght,list->path[n].sourding[i].name)];
            list->nb++;
            if(strcmp(list->path[n+1].name, "E") == 0){
                path_list temp = list;
                while (temp->following != NULL) temp = temp->following;
                temp->following = (path_cell*)malloc(sizeof(path_cell));
                temp->following->max_lenght = list->max_lenght;
                temp->following->nb = list->nb;
                temp->following->path = (city*)malloc(sizeof(city)*temp->max_lenght);
                for(int i = 0; i < temp->following->nb; i++){
                    temp->following->path[i] = list->path[i];
                }
                temp->following->following = NULL;
                count++;
                all_paths(cities, list->following, i+1);
            }
            else{
                all_paths(cities, list, 0);
            }
            list->nb--;
        }
    }
    return count;
}

