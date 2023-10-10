#ifndef FIFO_H
#define FIFO_H

namespace Simulador {
	class FIFO : Simulador::SubsAlgorihtm {

	public:
		char* pageseq;

		FIFO(int pageframes, char* pagesequence);

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
	};
}

#endif
