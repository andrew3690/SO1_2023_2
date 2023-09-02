#include "definers/Process.h"

// construtor da classe de processo
Process::Process(int data, int time, int priority){
    // cria um o contexto do processo
    // incrementa o id do processo (FIXTHIS)
    ctxtpointer = new CPU::Context();
    id++; // incrementa o id do processo
}

// destrutor do processo
Process::~Process(){
    // deleta o pointeiro do contexto, decrementa o contador de id's
    delete ctxtpointer;
    id--;
}

// Método para parar o processo
void Process::stop(){
    // salva o contexto na fila de processo
    this->ctxtpointer->save();
    // Troca o estado do processo para bloqueado
    this->state = Blocked; 
    // realiza a troca de contexto
    // a idéia é trocar o contexto atual para o contexto da cpu
    CPU::switch_context(ctxtpointer, cpu);
}

// inicaliza o processo
void Process::start(){
    // carregamento do contexto 
    this->ctxtpointer->load();
    // troca o estado do contexto para running
    this->state = Ready;
    // realiza a troca do contexto da cpu para o contexto atual
    CPU::switch_context(cpu,ctxtpointer);
}

