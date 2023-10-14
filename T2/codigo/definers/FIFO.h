#ifndef FIFO_H
#define FIFO_H

#include "SubsAlgorithm.h"
#include <string>
#include <queue>

namespace Simulador {
	class FIFO : public SubsAlgorithm {

	public:
		char* pageseq;

		FIFO(int pageframes, std::queue<std::string> pagesequence);

		/**
		 * enfileira um item na fila de páginas
		 */
		void enqueue();

		/**
		 * desenfileira um item da fila
		 */
		void dequeue();

		/**
		 * obtém o tamanho da fila
		 */
		void getqueuesize();

		/**
		 * seta um novo tamanho da fila
		 */
		void setqueuesize();

		void UpdateFrame() override;
		void SubsPage() override;
		void nextPagetoReplace(int page) override;
	};
}

#endif
