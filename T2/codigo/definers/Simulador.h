#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

namespace Simulador {
	class Simulador {

	private:
		int frameqtd;
		std::queue<std::string> filaDepgs; // Fila para armazenar as linhas


	public:
		// construtor
		Simulador(int agrc, char* agrv[]);

		// obtém a quantidade de frames
		int getFrameqtd(){
			return frameqtd;
		};

		// seta a quantidade de frames
		void setFrameqtd(int frameqtd){
			this->frameqtd = frameqtd;
		};

		// obtém a fila de páginas
		std::queue<std::string> getQueue() const {
        	return filaDepgs;
    	}

		// insere a página na fila de páginas
		void addToQueue(const std::string& newItem) {
        	filaDepgs.push(newItem);
    	}

		// mostra o resultado do processamento do algoritmo de paginação
		void Showresult();

		// Função de chamada dos algoritmos
		void Callalgorithm();

		// Gerenciador de entradas dos arquivos
		int InputHandler(int agrc, char* file[]);

		// Método de execução das funções do simulador
		//void main(int agrc, char* agrv[]);

		// Destrutor da classe
		~Simulador();

	};



}

#endif
