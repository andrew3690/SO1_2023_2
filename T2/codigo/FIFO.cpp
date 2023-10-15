#include "definers/FIFO.h"
using namespace Simulador;

FIFO::FIFO(int pageframes, std::list<int> pagesequence){
	// enquanto a sequencia de páginas nãop estiver vazia...
	while(!pagesequence.empty())
	{
		// percorre-se a fila de páginas...
		for(int pageiter = 0; pageiter <= pageframes;pageiter++){
			// obtém a página que está no topo da sequencia de páginas
			int page_ = pagesequence.front();
			// retira a página que está no topo da sequencia...
			pagesequence.pop_front();
			//verifica se a fila está cheia:....
			if(isQueueFull(pageframes))
			{
					// se a fila está cheia, verifica se a página já está na fila.. (Chamada de isPageInQueue)
					if(isPageInQueue(getpageseq(),page_)){
						// se a página estiver na fila é um page hit...
						Simulador::FIFO::SubsAlgorithm::setAcessmemoryqtd(page_);
					}else{
						// se a página não estiver na fila, é um page fault,substitui a página... (Chamda de Subspage e Nextpagetoreplace)
						Simulador::FIFO::SubsAlgorithm::setPagefaultqtd(page_);
						dequeue();
					}
			}else{
				// se a fila não está cheia, a página deve ser inserida no fim da fila... (UpdateFrame)
				UpdateFrame(page_);
			}
		}
	}
}

std::list<int> Simulador::FIFO::getpageseq(){
	return pageseq;
}

void Simulador::FIFO::enqueue(char page) {
	pageseq.push_back(page);
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

void Simulador::FIFO::SubsPage(int page){
	// desnefileira a página
	dequeue();
}

void Simulador::FIFO::UpdateFrame(int page){
	enqueue(page);
}

void Simulador::FIFO::nextPagetoReplace(int page){
	// acessa a fila de referencias de página e o obtém a próxima página a sr executada.
}