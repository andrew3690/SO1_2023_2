#include "definers/FIFO.h"
using namespace Simulador;

FIFO::FIFO(int pageframes){
	// enquanto a sequencia de páginas nãop estiver vazia...
	setpageqtd(pageframes);
}

void FIFO::SubsPage(int page){
	pageseq.push_back(page);
}

void FIFO::ExecutePageSubs(std::list<int>& ref_list) {
    int pageframes = getpageqtd();
    int pagefaultqtd = 0; // Inicializa o contador de faltas de página
	// int pagehitqtd = 0;
	// int iter = 0;

    for (int page : ref_list) {
        // Verifica se a página de referência já está na fila de páginas
        if (!isPageInQueue(pageseq, page)) {
            // Se a fila estiver cheia, remova o elemento mais antigo (o primeiro)
            if (isQueueFull(pageframes)) {
                dequeue();
            }
            // Adicione a página à fila de páginas (a mais recente)
            enqueue(page);
            // Aumenta o contador de faltas de página
            pagefaultqtd++;
			// std::cout << iter <<" Pagina: " << page <<" Quantidade de faltas de pagina: " << pagefaultqtd <<"\n";
			setPagefaultqtd(pagefaultqtd);
        }else{
			// Caso a página já esteja na fila, nenhuma ação é necessária, pois é um "hit".
        	// pagehitqtd++;
			// std::cout << iter <<" Pagina: " << page <<" Quantidade de faltas de pagina:" << pagehitqtd<<" sem falta de pagina\n";
			setAcessmemoryqtd(page);
		}
		// iter++;
    }
}


std::list<int> Simulador::FIFO::getpageseq(){
	return pageseq;
}

void Simulador::FIFO::enqueue(char page) {
	SubsPage(page);
}

void Simulador::FIFO::dequeue() {
	pageseq.pop_front();
}

bool Simulador::FIFO::isQueueFull(int pageframes) {
    return pageseq.size() == static_cast<size_t>(pageframes);
}

bool Simulador::FIFO::isPageInQueue(std::list<int> pageFrames, char page) {
    while (!pageFrames.empty()) {
        if (pageFrames.front() == page) {
            return true;
        }
        pageFrames.pop_front();
    }
    return false;
}

void Simulador::FIFO::UpdateFrame(int page){
    // metodo virtual que nao eh implementado nesta funcao
}

void Simulador::FIFO::nextPagetoReplace(int page){
    // metodo virtual que nao eh implementado nesta funcao
}