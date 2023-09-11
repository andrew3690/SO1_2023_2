// #include <iostream>
#include "definers/Process.h"
#include "definers/CPU.h"
#include "read_file.cc"
#include "FCFS.h"



int main (){
    // idéia:
    //  criar um loop que aplique a cada entrada diferente um algoritmo de escalonamento do processador
    //  FCFS (FIRST Come First Served): 1
    //  Shortest Job First (SJF): 2
    //  Por prioridade sem preempção: 3
    //  Por prioridade com preempção: 4
    //  Round Robin com quantum, de 2s sem prioridade: 5
    //  Finalizar: 6

    int input; // entrada que define qual escalonador utilizar
    while(true){
        // Carregar os processo na fila de bloqueados da CPU

        std::cout << " Digite qual algoritmo de escalonamento deseja usar \n";
        std::cout << "1-FCFS, 2- SJF, 3- Por prioridade sem preempção, 4- Por prioridade com preempção, 5- Round Robin com quantum, de 2s sem prioridade, 6-Finalizar \n";
        std::cin >> input;

        // Criando Objeto de Arquivo, e processando os parametros do arquivo
        File f;
        f.read_file();

        std::vector<std::tuple<int, int, int>> params = f.get_process_params();
        int count = 0;
        std::vector<FCFS_Scheduler> schedulerInstances;

        if(input == 6){
            break;
        }
        else {
            switch(input){
                case 1:
                    // FCFS
                    // realiza uma iteração do loop para cada processo na lista de processo
                    for (const auto& tuple : params) {
                            int creation_time = std::get<0>(tuple);
                            int duration = std::get<1>(tuple);
                            int priority = std::get<2>(tuple);

                            // count
                            count++;

                            std::cout <<"Creation Time: " <<creation_time <<" Duration: "<<duration <<" Priority: "<< priority<<"\n";
                            
                            FCFS_Scheduler schedulerInstance(count,creation_time,duration,priority);
                    };
                case 2:
                    // SJF
                        break;
                case 3:
                    // Prioridade sem preempção
                        break;
                case 4:
                    // Prioridade com preempção
                        break;
                case 5:
                    // Round Robin com quantum, de 2s sem prioridade
                        break;
            };
        };
    };
};