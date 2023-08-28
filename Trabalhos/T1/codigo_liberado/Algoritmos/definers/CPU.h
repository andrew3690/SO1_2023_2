#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <list>


class CPU{
    public:

        class Context{

            public:
                Context() {_stack = 0;}; // Construtor vazio
                ~Context(); // Destrutor do contexto

                void save(); // metodo para salvar o contexto
                void load(); // metodo para carregar o contexto
            
            private:
                char *_stack; // Process Stack (manter aqui ou nao ?)
                uint64_t SP; // STACK POINTER
                uint64_t PC; // PROGRAM COUNTER
                uint64_t ST; // STATUS REGISTER
                uint64_t registers[6]; // R1,R2,R3,R4,R5,R6
            public:
                Context *pointer;      // pointeiro para o contexto atual
                Context *save_pointer; // ponteiro para salvar o contexto
                std::list<Context*> pointerList; // Fila de contexto
        };
    
    static int switch_context(Context *from, Context *to);
};

#endif // CPU_H
