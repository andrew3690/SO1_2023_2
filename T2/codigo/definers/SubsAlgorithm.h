#ifndef SUBSALGORIHTM_H
#define SUBSALGORIHTM_H
#include <queue>
#include <string>
#include <list>

namespace Simulador {
	class SubsAlgorithm {

	protected:
		int acessmemoryqtd;
		int Pagefaultqtd;
		int frame_quantity;

	public:
		/**
		 * Método de execução da troca de páginas
		 */
		void ExecutePageSubs();

		/**
		 * Obtém a quantidade de acessos na memória
		 */
		void getAcessmemoryqtd();

		/**
		 * incrementa a quantidade de acessos na memória
		 */
		void setAcessmemoryqtd(int Acessmemoryqtd);

		/**
		 * Obtém a quantidade de faltas de páginas no algoritmo
		 */
		int getPagefaultqtd();

		/**
		 * incrementa a quantidade de faltas de página
		 */
		void setPagefaultqtd(int pagefaultqtd);

		/**
		 * Atualização do quadro de página a ser utilizado
		 */
		virtual void UpdateFrame(int page) = 0;

		/**
		 * Método que decide qual página deve ser substituída
		 */
		virtual void SubsPage(int page) = 0;

		/**
		 * Obtenção da próxima página a ser executada
		 */
		virtual void nextPagetoReplace(int page) = 0;
	};
}

#endif
