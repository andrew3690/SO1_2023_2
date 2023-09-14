// #include <iostream>
#include "definers/Process.h"
#include "definers/CPU.h"
#include "definers/FCFS.h"
#include "read_file.cc"
#include "definers/SJF.h"
#include "definers/NonPreemptivePriority.h"
#include "definers/Round_robin.h"

#include <memory>
#include <vector>

int main (){
    // idéia:
    //  criar um loop que aplique a cada entrada diferente um algoritmo de escalonamento do processador
    //  FCFS (FIRST Come First Served): 1
    //  Shortest Job First (SJF): 2
    //  Por prioridade sem preempção: 3
    //  Por prioridade com preempção: 4
    //  Round Robin com quantum, de 2s sem prioridade: 5
    //  Finalizar: 6
    
    File f; // Instanciando objeto de arquivo
    f.read_file(); // leitura dos dados do arquivo

    int input; // entrada que define qual escalonador utilizar
    
    CPU::Context* cpu; // criacao do contexto da cpu
    int count = 0; // contador
    std::vector<std::tuple<int, int, int>> params = f.get_process_params(); // obtencao dos parametros dos processos
    std::vector<std::shared_ptr<Process>> processes; // vetor de processos que mantem os ponteiros dos objetos dos processos
        
    // Instanciação dos escalonadores para cada lista de processos. 
    FCFS_Scheduler fcfsScheduler(processes);
    SJF_Scheduler sjfScheduler(processes);
    NonPPriorityScheduler npremptive(processes);
    Round_robin round_robin(processes);
    
    while(true){
        // Carregar os processo na fila de bloqueados da CPU

        std::cout << " Digite qual algoritmo de escalonamento deseja usar: \n";
        std::cout << "1-FCFS, 2- SJF, 3- Por prioridade sem preempção, 4- Por prioridade com preempção \n", 
        std::cout << "5- Round Robin com quantum, de 2s sem prioridade, 6-Finalizar \n";
        std::cin >> input;


        for (const auto& tuple : params) {
            int creation_time = std::get<0>(tuple);
            int duration = std::get<1>(tuple);
            int priority = std::get<2>(tuple);

            count++;

            // Cria novos processos e os insere na lista de processos compartilhados
            auto process = std::make_shared<Process>(count, creation_time, duration, priority);
            processes.push_back(process);

            // Se o usuário opta por finalizar os escalonadores
            if (input == 6) {
                break;
            } 
            else {


                // Os algoritmos de escalonamento entram aqui
                switch (input) {
                    case 1:
                        // FCFS
                        fcfsScheduler.escalonate();
                        break;
                    case 2:
                        // SJF
                        sjfScheduler.escalonate();
                        break;
                    case 3:
                        // Non-preemptive com preempção 
                        npremptive.escalonate();
                        break;
                    case 4:
                        // Non-preempotive sem preempção
                        npremptive.escalonate();
                        break;
                    case 5:
                        // Round robin com quantum 2
                        round_robin.escalonate();
                        break;
                    default:
                        break;
                }
            };
        };
    
        if (input == 6){
            break;
        }   
    };
}