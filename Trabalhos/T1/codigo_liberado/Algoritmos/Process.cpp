#include "definers/Process.h"
// Fora do escopo da classe, inicialize nextId como 0
int Process::id = 0;

Process::Process(int data, int time, int priority)
    : id(nextId++), data_init(data), data_end(0), duration(time), timeexec(0), priority(priority), state("Ready") {
    // Restante do seu código de inicialização
}