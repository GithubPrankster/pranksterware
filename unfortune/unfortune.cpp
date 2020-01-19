//Lord may have mercy on my soul, for I have done something terrible.
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <string>
#include <random>
#include <cstring>
#include <fstream>
#include <vector>


static std::random_device rd;
static std::mt19937 eng(rd());

void read_unfortune(std::ifstream& file){
    std::vector<std::string> unfortunes;
    std::string buffer;
    while(getline(file, buffer, '%')){
        unfortunes.push_back(buffer);
    }
    std::uniform_int_distribution<> distr(0, unfortunes.size());
    printf("%s", unfortunes[distr(eng)].c_str());
}

int main(){
    srand(time(0));
    std::ifstream file("common_unfortunes.txt");
    read_unfortune(file);
    return 0;
}