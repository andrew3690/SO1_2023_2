#include "definers/CPU.h"
#include <iostream>

CPU::Context::Context(){
    Context *pointer = new Context(); // Criacao de novo contexto
    pointerList.push_back(pointer);   // Inserindo no fim da lista de processos
}

void CPU::Context::save(){
    // salva o contexto atual na fila de contextos
    pointerList.push_back(this);
};

void CPU::Context::load(Context *cont){
    // Encontre o contexto a ser removido
    auto it = pointerList.begin();
    
    for (; it != pointerList.end(); ++it) {
        if (*it == cont) {
            break; // Encontrou o contexto, sai do loop
        }
    }

    if (it != pointerList.end()) {
        // Remova o contexto da lista
        pointerList.erase(it);
    }
};

CPU::Context::~Context()
{
    delete pointer; // Libera a memoria alocada pelo processo
};

int CPU::switch_context(Context *from, Context *to)
{
    // trocar o contexto, primeiro salvando o contexto anterior
    // depois trocando para o proximo contexto
    
    // ideia:
    // salvar o contexto `from` na lista de contextos
    // colocar o contexto `to` para rodar
    // trocando os valores dos registradores, como fazer isso ?
};