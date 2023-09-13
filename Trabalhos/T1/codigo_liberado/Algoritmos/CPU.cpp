#include "definers/CPU.h"
#include <iostream>

// Definitions for static members of CPU::Context
// std::list<CPU::Context*> CPU::Context::pointerList;
// int CPU::Context::context_counter;


CPU::Context::Context(){
    std::cout << " Criacao do contexto\n";
    // pointerList.push_back(pointer);   // Inserindo no fim da lista de processos da CPU
    // context_counter++; // incrementa o contador de contextos, na criacao de um dado contexto
}

CPU::Context* CPU::Context::save(){
    // Salve o estado atual da CPU, incluindo SP, PC, ST e registradores
    SP = this->getSP();
    PC = this->getPC();
    ST = this->getST();
    // Salve os registradores de propósito geral
    for (int i = 0; i < 6; i++) {
        registers[i] = this->registers[i];
    }
    return this;
}

CPU::Context* CPU::Context::load(){  // metodo para carregar o contexto
    // Restaure o estado da CPU, incluindo SP, PC, ST e registradores
    /* configure SP, PC, ST com os valores salvos */;
    // Restaure os registradores de propósito geral
    this->setSP(SP);
    this->setPC(PC);
    this->setST(ST);
    for (int i = 0; i < 6; i++) {
        this->registers[i] = registers[i];
    }
    return this;
};

CPU::Context::~Context()
{
    // Libera a memoria alocada pelo processo
    // context_counter--; // decrementa o contador na destruicao de uma contexto
    // se contador estiver zerado, a lista deve ser destruída, para liberar espaço de memória
};

int CPU::switch_context(Context *from, Context *to) {
    // Salva o contexto atual no objeto 'from'
    from->save();

    // carrega o contexto `to`
    to->load();

    return 0; // Ou algum código de status apropriado
}