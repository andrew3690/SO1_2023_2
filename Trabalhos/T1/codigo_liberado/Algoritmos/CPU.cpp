#include "definers/CPU.h"
#include <iostream>

CPU::Context::Context(){
    Context *pointer = new Context(); // Criacao de novo contexto
    pointerList.push_back(pointer);   // Inserindo no fim da lista de processos prontos
    context_counter++; // incrementa o contador de contextos, na criacao de um dado contexto
}


void CPU::Context::save(){
    // salva o contexto atual na fila de contextos
    return pointerList.push_back(this);
};

void CPU::Context::load(){
    // retorna o contexto a ser retirado da fila de prontos
    return pointerList.remove(this);
};

CPU::Context::~Context()
{
    context_counter--; // decrementa o contador na destruicao de uma contexto
    delete pointer; // Libera a memoria alocada pelo processo
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
};