#include "definers/Round_robin.h"

Round_robin::Round_robin(){
    std::cout << "Chamada do escalonador Round-Robin \n";
}

Round_robin::~Round_robin(){

}

void Round_robin::escalonate(){
    std::cout << "Iniciando o escalonamento \n";
    std::cout << clock_counter;
}

// void Round_robin::sort(){

// }

// void Round_robin::schedule(){

// }