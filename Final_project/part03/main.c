#include "part03.c"

int main(int argc, char** argv){
    char src[14] = "../maps/";
    char* input = strcat(src, argv[1]);
    int err = 0;
    size_t f_size = 0;
    char* the_file = c_read_file(input, &err, &f_size);
    char** handy_file = strsplit(the_file, 10);
    city* cities = all_cities(handy_file);
    path_list L = (path_cell*)malloc(sizeof(path_cell));
    L->following = NULL;
    L->max_lenght = atoi(handy_file[1]);
    L->nb = 1;
    L->total_visits = 0;
    L->path = (city*)malloc(sizeof(city)*atoi(handy_file[1]));
    L->path[0] = cities[check_city(cities, atoi(handy_file[1]), "S")];
    path_list oui = L;
    int nb = shortest_path(cities, oui, 0);
    L=L->following;
    path_list T = handy_list(cities, L, nb);
    totaly_normal_sort(T);
    path_list humu = the_good_paths(T);
    circuit(atoi(handy_file[0]), humu);
}