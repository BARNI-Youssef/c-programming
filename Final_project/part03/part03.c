#include "part03.h"

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
            add->visited = 0;
            if(strcmp("E", add->name) == 0) add->dist_to_E = 0;
            else add->dist_to_E = INT_MAX-1;
            final[i] = *add;
            i++;
        }
        if(check_city(final, i, names[1]) == -1){
            city* add = (city*)malloc(sizeof(city));
            add->name = names[1];
            add->sourding = (city*)malloc(sizeof(ch[1])*sizeof(city));
            add->nb_sourding = 0;
            add->visited = 0;
            if(strcmp("E", add->name) == 0) add->dist_to_E = 0;
            else add->dist_to_E = INT_MAX-1;
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
    int changes = 0;
    for(int i = 0; i < atoi(ch[1]); i++){
        int dist = final[i].dist_to_E;
        for(int j = 0; j < final[i].nb_sourding; j++){
            if(dist+1 < final[check_city(final, atoi(ch[1]), final[i].sourding[j].name)].dist_to_E){
                final[check_city(final, atoi(ch[1]), final[i].sourding[j].name)].dist_to_E = dist+1;
                changes++;
            }
        }
    }
    while(changes != 0){
        changes = 0;
        for(int i = 0; i < atoi(ch[1]); i++){
            int dist = final[i].dist_to_E;
            for(int j = 0; j < final[i].nb_sourding; j++){
                if(dist+1 < final[check_city(final, atoi(ch[1]), final[i].sourding[j].name)].dist_to_E){
                    final[check_city(final, atoi(ch[1]), final[i].sourding[j].name)].dist_to_E = dist+1;
                    changes++;
                }
            }
        }
    }
    return final;
}

int count = 0;

int shortest_path(city* cities, path_list list, int ind){
    int n = list->nb-1;
    for(int i = ind; i < list->path[n].nb_sourding; i++){
        if(cities[check_city(cities, list->max_lenght, list->path[n].sourding[i].name)].dist_to_E < list->path[n].dist_to_E){
            cities[check_city(cities, list->max_lenght, list->path[n].sourding[i].name)].visited ++;
            list->path[n+1] = cities[check_city(cities, list->max_lenght, list->path[n].sourding[i].name)];
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
                    cities[check_city(cities,temp->max_lenght,temp->following->path[i].name)].visited++;
                }
                temp->following->following = NULL;
                count++;
                shortest_path(cities, list->following, i+1);
            }
            else{
                shortest_path(cities, list, 0);
            }
            list->path[n+1].visited--;
            cities[check_city(cities, list->max_lenght, list->path[n].sourding[i].name)].visited--;
            list->nb--;
        }
    }
    return count;
}

path_list handy_list(city* cities, path_list list, int size){
    path_list final = (path_cell*)malloc(sizeof(path_cell)*size);
    int num = size;
    for(int i = 0; i < size; i++){
        final[i].max_lenght = size;
        final[i].path = list->path;
        final[i].nb = list->nb;
        final[i].total_visits = 0;
        for(int j = 0; j < final[i].nb; j++){
            final[i].total_visits += cities[check_city(cities,list->max_lenght,final[i].path[j].name)].visited;
        }
        list = list->following;
    }
    return final;
}

void totaly_normal_sort(path_list good_list){
    for(int i = 0; i < good_list->max_lenght; i++){
        for(int j = 0; j < good_list->max_lenght-i-1; j++){
            if(good_list[j].total_visits > good_list[j+1].total_visits){
                good_list[j].total_visits += good_list[j+1].total_visits;
                good_list[j+1].total_visits = good_list[j].total_visits - good_list[j+1].total_visits;
                good_list[j].total_visits = good_list[j].total_visits - good_list[j+1].total_visits;
                good_list[j].nb += good_list[j+1].nb;
                good_list[j+1].nb = good_list[j].nb - good_list[j+1].nb;
                good_list[j].nb = good_list[j].nb - good_list[j+1].nb;
                city* aux = good_list[j].path;
                good_list[j].path = good_list[j+1].path;
                good_list[j+1].path = aux;
            }
        }
    }
}

path_list the_good_paths(path_list list){
    int size = 0;
    int delim = list[0].total_visits;
    int max = list->max_lenght;
    int i = 0;
    while(list[i].total_visits <= delim && i < max){
        size++;
        i++;
    }
    path_list final = (path_cell*)malloc(sizeof(path_cell)*size);
    for(int e = 0; e < size; e++){
        final[e].max_lenght = size;
        final[e].path = list[e].path;
        final[e].nb = list[e].nb;
    }
    return final;
}

void circuit(int nb_trains, path_list paths){
    train* all_trains = (train*)malloc(sizeof(train)*nb_trains);
    for(int i = 0; i < nb_trains; i++){
        all_trains[i].current_city = "S";
        all_trains[i].path_num = -1;
        all_trains[i].city_num = 0;
    }
    int hours = 0;
    int nb_paths =  paths->max_lenght;
    while(strcmp(all_trains[nb_trains-1].current_city, "E") != 0){
        for(int i = 0; i < nb_trains; i++){
            if(strcmp(all_trains[i].current_city, "E") != 0){
                if(all_trains[i].path_num == -1){
                    int j = 0;
                    for(j = 0; j < nb_paths; j++){
                        int e = 0;
                        int locket = 0;
                        for(e = 0; e < nb_trains; e++){
                            if(strcmp(all_trains[e].current_city, paths[j].path[1].name) == 0) locket = 1;
                        }
                        if(locket == 0){
                            all_trains[i].current_city = paths[j].path[1].name;
                            all_trains[i].city_num = 1;
                            all_trains[i].path_num = j;
                            printf("t%d:S->%s ", i, all_trains[i].current_city);
                            break;
                        }
                    } 
                }
                else{
                    char* next_city_name = paths[all_trains[i].path_num].path[all_trains[i].city_num+1].name;
                    if(strcmp(next_city_name, "E") != 0){
                        int j = 0;
                        int locket = 0;
                        for(j = 0; j < nb_trains; j++){
                            if(strcmp(all_trains[j].current_city, next_city_name) == 0) locket = 1;
                        }
                        if(locket == 0){
                            printf("t%d:%s->%s ", i, paths[all_trains[i].path_num].path[all_trains[i].city_num].name, next_city_name);
                            all_trains[i].current_city = next_city_name;
                            all_trains[i].city_num++;
                        }
                    }
                    else{
                        printf("t%d:%s->E ", i, paths[all_trains[i].path_num].path[all_trains[i].city_num].name);
                        all_trains[i].current_city = "E";
                        all_trains[i].city_num++;
                    }
                }
            }
        }
        printf("\n");
        hours++;
    }
    printf("\nTotal times spent for the arival of all trains: %d hours\n", hours);
}