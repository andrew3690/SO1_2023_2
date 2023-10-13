#ifndef FIFO_H
#define FIFO_H
#include <queue>
#include <string>
#include "SubsAlgorithm.h"

namespace Simulador {
	class FIFO : public SubsAlgorithm {
	private:
		std::queue<char> pageseq;
		int pagehitcnt;
		int pagefaultcnt;
	
	public:
		FIFO(int pageframes, std::queue<char> pagesequence);

		/**
		 * enfileira um item na fila de páginas
		 */
		void enqueue(char page);

		/**
		 * desenfileira um item da fila
		 */
		char dequeue();

		// método que verifica se uma página já está na fila de páginas
		bool isPageInQueue(std::queue<char> pageFrames, char page);

		// método que verifica se a fila de páginas está cheia
		bool isQueueFull(int pageframes);

		// métodos abstratos da classe subsalgortihm
		void SubsPage(char page) override;

		void UpdateFrame(char page) override;

		void nextPagetoReplace(char page) override;


	};
}

#endif
