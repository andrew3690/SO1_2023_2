#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <list>


class CPU{

    public:

        class Context{

            public:
                Context();// Construtor vazio
                ~Context(); // Destrutor do contexto

                Context* save(); // método para salvar o processo
                Context* load(); // método para carregar o processo
            
                char *_stack; // Process Stack (manter aqui ou nao ?)
                uint64_t SP; // STACK POINTER
                uint64_t PC; // PROGRAM COUNTER
                uint64_t ST; // STATUS REGISTER
                uint64_t registers[6]; // R1,R2,R3,R4,R5,R6

                static std::list<Context*> pointerList; // Definition
                static int context_counter; // Definition
                Context *pointer;    // pointeiro para o contexto atual
        };

        Context *cpu; // Contexto da CPU, para realizacao da troca de contexto       
        int switch_context(Context *from, Context *to);

    private:
        char *_stack; // CPU Process Stack (manter aqui ou nao ?)
        uint64_t SP; // STACK POINTER
        uint64_t PC; // PROGRAM COUNTER
        uint64_t ST; // STATUS REGISTER
        uint64_t registers[6]; // R1,R2,R3,R4,R5,R6
};

#endif // CPU_H
