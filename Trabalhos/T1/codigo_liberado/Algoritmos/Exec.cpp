#include <iostream>
#include "definers/Process.h"
#include "definers/CPU.h"
#include "read_file.cc"
#include "Alg/FCFS.h"

    // idéia:
    //  criar um loop que aplique a cada entrada diferente um algoritmo de escalonamento do processador
    //  FCFS (FIRST Come First Served): 1
    //  Shortest Job First (SJF): 2
    //  Por prioridade sem preempção: 3
    //  Por prioridade com preempção: 4
    //  Round Robin com quantum, de 2s sem prioridade: 5
    //  Finalizar: 6



int main() {

    int input; // entrada que define qual escalonador utilizar

    while(true){
        std::cout << " Digite qual algoritmo de escalonamento deseja usar \n";
        std::cout << "1-FCFS, 2- SJF, 3- Por prioridade sem preempção, 4- Por prioridade com preempção, 5- Round Robin com quantum, de 2s sem prioridade, 6-Finalizar \n";
        std::cin >> input;

        if(input = 6){
            break;
        }
        else{
            switch(input){
                case 1:
                    // FCFS

                case 2:
                    // SJF

                case 3:
                    // Prioridade sem preempção

                case 4:
                    // Prioridade com preempção

                case 5:
                    // Round Robin com quantum, de 2s sem prioridade
            }
        }
    };
}