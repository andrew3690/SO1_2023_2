#ifndef SUBSALGORIHTM_H
#define SUBSALGORIHTM_H
#include <queue>
#include <string>

namespace Simulador {
	class SubsAlgorithm {

	private:
		int Acessmemoryqtd_;
		int Pagefaultqtd_;

	public:
		/**
		 * Obtém a quantidade de acessos na memória
		 */
		int getAcessmemoryqtd();

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
		void setPagefaultqtd(int Pagefaultqtd);

		/**
		 * Atualização do quadro de página a ser utilizado
		 */
		virtual void UpdateFrame(char page) = 0;

		/**
		 * Método que decide qual página deve ser substituída
		 */
		virtual void SubsPage(char page) = 0;

		/**
		 * Obtenção da próxima página a ser executada
		 */
		virtual void nextPagetoReplace(char page) = 0;
	};
}

#endif
