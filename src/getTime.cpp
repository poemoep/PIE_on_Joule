#include <iostream>
#include <string>
#include <time.h>
#define N 20

std::string getTime() {
    time_t timer;
    struct tm* tm;
    char datetime[N];
    timer = time(NULL);
    tm = localtime(&timer);
    strftime(datetime, N, "%Y%m%d_%H%M%S",tm );
//    std::cout << "DATETIME = " << datetime << std::endl;
    std::string str(datetime);
    return str;
}

/*
int main(){

    std::string str;
    
    str = getTime();

    std::cout << str << std::endl;

    return 0;
}
*/
