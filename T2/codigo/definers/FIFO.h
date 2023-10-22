#ifndef FIFO_H
#define FIFO_H
#include "SubsAlgorithm.h"

namespace Simulador {
	class FIFO : public SubsAlgorithm {
	private:
		std::list<int> pageseq;
		int pagehitcnt;
		int pagefaultcnt;
		int pageqtd;
	
	public:
		FIFO(int pageframes);

		/**
		 * enfileira um item na fila de páginas
		 */
		void enqueue(char page);

		/**
		 * desenfileira um item da fila
		 */
		void dequeue();

		// Metodo para setar a quantidade de paginas
		void setpageqtd(int pageqtd_){pageqtd = pageqtd_;};

		// Metodo para obter a quantidade de paginas
		int getpageqtd(){return pageqtd;};

		// método que verifica se uma página já está na fila de páginas
		bool isPageInQueue(std::list<int> pageFrames, char page);

		// método que verifica se a fila de páginas está cheia
		bool isQueueFull(int pageframes);

		// métodos abstratos da classe subsalgortihm
		void SubsPage(int page) override;

		void UpdateFrame(int page) override;

		void nextPagetoReplace(int page) override;

		std::list<int> getpageseq();

		void ExecutePageSubs(std::list<int>& ref_list);


	};
}

#endif