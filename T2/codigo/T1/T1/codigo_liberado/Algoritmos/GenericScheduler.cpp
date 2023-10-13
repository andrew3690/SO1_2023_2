#include "definers/GenericScheduler.h"


Generic_Scheduler::Generic_Scheduler() {};

Generic_Scheduler::~Generic_Scheduler() {};

void Generic_Scheduler::exec(Process* process, int time)
{
    std::cout << "Processo {" << process->getid() << "} executou no tempo: " << time << "\n";
    process->dectime(); // decrementa a duração restante
}