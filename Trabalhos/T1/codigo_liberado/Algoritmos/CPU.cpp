#include "definers/CPU.h"
#include <iostream>

CPU::Context::Context(){
    Context *pointer = new Context(); // Criacao de novo contexto
    pointerList.push_back(pointer);   // Inserindo no fim da lista
}

void CPU::Context::save(){
    // salva o contexto

};

void CPU::Context::load(){
    Context *pointer = pointerList.pop_front();// carrega o contexto
};

CPU::Context::~Context()
{
    delete _stack; // Libera a memoria alocada pelo processo
};

int CPU::switch_context(Context *from, Context *to)
{
    return ; // troca de contexto
};