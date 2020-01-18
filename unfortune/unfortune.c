#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void type_help(){
    fprintf(stderr, "unfortune usage: [unfortune] -t unfortunes_path\n-t = Use external unfortunes file.\n");
}

void read_unfortune(FILE* file){

    fclose(file);
}

int main(int argc, char** argv){
    if(argc > 1 && argc < 3){
        type_help();
    }
    if(argc > 2){
        if(!strcmp(argv[1], "-t")){
            FILE* file;
            if(fopen(argv[2], "r")){

            }
            else{
                fprintf(stderr, "Invalid path!\n");
            }
        }
        else{
            type_help();
        }
    }else{
        FILE* file = fopen("common_unfortunes.txt", "r");
        read_unfortune(file);
    }
    return 0;
}