#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <list>

class Context{
    public:
        Context();// Construtor vazio
        ~Context(); // Destrutor do contexto

        Context* save(); // método para salvar o processo
        Context* load(); // método para carregar o processo
        
        // Getters:
        char getstack() {return *_stack;};
        uint64_t getSP() {return SP;};
        uint64_t getPC() {return PC;};
        uint64_t getST() {return ST;};
        uint64_t getregisters() {return registers[6];};

        //Setters:
        void setstack(char *_stack) {this->_stack = _stack;};
        void setSP(uint64_t SP){this->SP = SP;};
        void setPC(uint64_t PC){this->PC = PC;};
        void setST(uint64_t ST){this->ST = ST;};
        void setregisters(uint64_t registers[6]) {this->registers[6] = registers[6];};

        // static std::list<Context*> pointerList; // Lista de contextos
        Context *pointer;    // pointeiro para o contexto atual
    
    private:
        char *_stack; // Process Stack (manter aqui ou nao ?)
        uint64_t SP; // STACK POINTER
        uint64_t PC; // PROGRAM COUNTER
        uint64_t ST; // STATUS REGISTER
        uint64_t registers[6]; // R1,R2,R3,R4,R5,R6
};

class CPU: public Context{

    public:
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
