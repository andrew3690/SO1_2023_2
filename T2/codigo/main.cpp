#include "definers/Simulador.h"

int main(int argc, char* argv[])
{
    Simulador::Simulador* simulador_instance = new Simulador::Simulador(argc, argv);
    delete simulador_instance;
    return 0;
}