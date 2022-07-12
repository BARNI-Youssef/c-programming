#include "part02.c"

int main(int argc, char** argv){
    char src[14] = "../maps/";
    char* input = strcat(src, argv[1]);
    int err = 0;
    size_t f_size = 0;
    char* the_file = c_read_file(input, &err, &f_size);
    char** handy_file = strsplit(the_file, 10);
    city* cities = all_cities(handy_file);
    path_cell path1;
    path1.path = (city*)malloc(sizeof(city)*(atoi(handy_file[1])));
    path1.path[0] = cities[check_city(cities, atoi(handy_file[1]), "S")];
    path1.max_lenght = atoi(handy_file[1]);
    path1.nb = 1;
    path_list Dawae = &path1;
    path_list path = Dawae;
    int number = shortest_path(cities, path, 0);
    printf("There's %d paths that are/is the shortest:\n\n", number);
    Dawae = Dawae->following;
    while(Dawae != NULL){
        for(int i = 0; i < Dawae->nb; i++){
            printf("%s ", Dawae->path[i].name);
        }
        printf("\n");
        Dawae = Dawae->following;
    }
}