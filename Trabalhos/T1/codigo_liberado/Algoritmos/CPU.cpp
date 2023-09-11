#include "definers/CPU.h"
#include <iostream>

// Definitions for static members of CPU::Context
std::list<CPU::Context*> CPU::Context::pointerList;
int CPU::Context::context_counter;


CPU::Context::Context(){
    Context *pointer = new Context(); // Criacao de novo contexto
    pointerList.push_back(pointer);   // Inserindo no fim da lista de processos prontos
    context_counter++; // incrementa o contador de contextos, na criacao de um dado contexto
}


CPU::Context* CPU::Context::save(){
    // Salva o contexto atual na fila de contextos bloqueados
    pointerList.push_back(this);
    // Retorna o próprio contexto
    return this;
}

CPU::Context* CPU::Context::load(){  // metodo para carregar o contexto

    if (!pointerList.empty()) {
        return pointerList.front();
    }
    // caso a lista esteja vazia, retorna o ponteiro vazio
    return nullptr;
};

CPU::Context::~Context()
{
    delete pointer; // Libera a memoria alocada pelo processo
    context_counter--; // decrementa o contador na destruicao de uma contexto
    // se contador estiver zerado, a lista deve ser destruída, para liberar espaço de memória
    if (context_counter == 0){
        pointerList.clear();
    }
};

int CPU::switch_context(Context *from, Context *to)
{
    // ideia:
    // salvar o contexto `from` na lista de contextos
    // trocando os valores dos registradores, como fazer isso de forma que os atributos sejam privados ?
    // colocar o contexto `to` para rodar

    from->save(); // Salva o contexto da cpu na lista de contextos

    // realiza a troca dos valores de registradores e pilha de contexto
    std::swap(from->SP,to->SP);
    std::swap(from->PC,to->PC);
    std::swap(from->ST,to->ST);
    std::swap(from->registers,to->registers);
    std::swap(from->_stack,to->_stack);

    to->load(); // Carrega o contexto a ser trocado para execucao
    return 0;
};