// #include <iostream>
#include "definers/Process.h"
#include "definers/CPU.h"
#include "definers/FCFS.h"
#include "read_file.cc"
#include <memory>

int main (){
    // idéia:
    //  criar um loop que aplique a cada entrada diferente um algoritmo de escalonamento do processador
    //  FCFS (FIRST Come First Served): 1
    //  Shortest Job First (SJF): 2
    //  Por prioridade sem preempção: 3
    //  Por prioridade com preempção: 4
    //  Round Robin com quantum, de 2s sem prioridade: 5
    //  Finalizar: 6
    
    File f; // Instanciando objeto de arquivp
    f.read_file(); // leitura dos dados do arquivo

    int input; // entrada que define qual escalonador utilizar
    CPU::Context* cpu; // criacao do contexto da cpu
    
    while(true){
        // Carregar os processo na fila de bloqueados da CPU

        std::cout << " Digite qual algoritmo de escalonamento deseja usar \n";
        std::cout << "1-FCFS, 2- SJF, 3- Por prioridade sem preempção, 4- Por prioridade com preempção, 5- Round Robin com quantum, de 2s sem prioridade, 6-Finalizar \n";
        std::cin >> input;

        int count = 0; // contador
        std::vector<std::tuple<int, int, int>> params = f.get_process_params(); // obtencao dos parametros dos processos

        for (const auto& tuple : params) {
            int creation_time = std::get<0>(tuple);
            int duration = std::get<1>(tuple);
            int priority = std::get<2>(tuple);

            count++;
            
            std::cout << "Id: " << count << " Creation Time: " << creation_time << " Duration :" << duration << " Priority: " <<priority <<"\n";
            Process(count,creation_time,duration,priority);
        }

        // estrutura de escolha do processo
        if(input == 6){
            break;
        }
        else {
            switch(input){
                case 1:
                    // FCFS
                    // realiza uma iteração do loop para cada processo na lista de processo
                case 2:
                    // SJF
                    // sjf_instance->schedule();
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
    delete cpu;

};