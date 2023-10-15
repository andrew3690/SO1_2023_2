#ifndef FIFO_H
#define FIFO_H
#include "SubsAlgorithm.h"

namespace Simulador {
	class FIFO : public SubsAlgorithm {
	private:
		std::list<int> pageseq;
		int pagehitcnt;
		int pagefaultcnt;
	
	public:
		FIFO(int pageframes, std::list<int> pagesequence);

		/**
		 * enfileira um item na fila de páginas
		 */
		void enqueue(char page);

		/**
		 * desenfileira um item da fila
		 */
		void dequeue();

		// método que verifica se uma página já está na fila de páginas
		bool isPageInQueue(std::list<int> pageFrames, char page);

		// método que verifica se a fila de páginas está cheia
		bool isQueueFull(int pageframes);

		// métodos abstratos da classe subsalgortihm
		void SubsPage(int page) override;

		void UpdateFrame(int page) override;

		void nextPagetoReplace(int page) override;

		std::list<int> getpageseq();


	};
}

#endif
