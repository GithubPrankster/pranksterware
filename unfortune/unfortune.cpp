//Lord may have mercy on my soul, for I have done something terrible.
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <string>
#include <random>
#include <cstring>
#include <fstream>
#include <vector>
//Now that THAT is out of the way...

//Mersenne Twister! Everybody loves MT engine.
static std::random_device rd;
static std::mt19937 eng(rd());

//The main function.
void read_unfortune(std::ifstream& file){
    //Get the very creepy and scary unfortunes and a buffer ready.
    std::vector<std::string> unfortunes;
    std::string buffer;
    //Loop through each line *on a buffer* and delimitate with the %s.
    while(getline(file, buffer, '%')){
        unfortunes.push_back(buffer);
    }
    //Make an uniform distribution with the size of that stuff.
    std::uniform_int_distribution<> distr(0, unfortunes.size());
    //Print it!
    printf("%s", unfortunes[distr(eng)].c_str());
}

void print_out_help(){
    printf("[unfortune] -H -T\n-h = Prints out this very helper.\n-t = Allows you to specify a path to separate source of unfortunes.\n");
}

int main(int argc, char** argv){
    //Read off common_unfortunes.
    if(argc > 1){
        if(!strcmp(argv[1], "-h")){
            print_out_help();
        }
        else if(!strcmp(argv[1], "-t")){
            if(argc < 3){
                fprintf(stderr, "No path specified...\n");
            }
            else{
                std::ifstream file(argv[2]);
                if(file.is_open()){
                    read_unfortune(file);
                }
                else{
                    fprintf(stderr, "Path invalid...\n");
                } 
            }
        }
        else{
            print_out_help();
        }
    }
    else{
        std::ifstream file("common_unfortunes.txt");
        read_unfortune(file);
    }
    return 0;
}