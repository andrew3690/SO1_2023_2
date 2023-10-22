#include "definers/OPT.h"
#include <iostream>

using namespace Simulador;

//construtor
OPT::OPT(int frameqtd) {
	framequantity = frameqtd;
}

//destrutor
OPT::~OPT() {}

void OPT::UpdateFrame(int page) {
	// TODO - implement OPT::UpdateFrame
	throw "Not yet implemented";

}

/* Retorna um registro de quando uma página (page) será referenciada no futuro -> sera a etiqueta*/
int OPT::findNextReferenceOfPage(int page, int start, std::vector<int>& references) {
	int lenght = 0;
	for (int i = start+1; i < references.size(); i++ ) {
		auto future_page = references[i];
		if (future_page == page) {
			return lenght;
		} else {
			lenght++;
		}
	}
	return lenght;
}

/* Algoritmo principal para substituição de páginas -> itera sobre lista de referências de páginas */
void OPT::ExecutePageSubs(std::vector<int>& to_be_referenced_pages) {
	int increment = 0;
	for (const int& page: to_be_referenced_pages) {
		int lenght_until_next_reference = findNextReferenceOfPage(page, increment, to_be_referenced_pages);

		if (map_of_pages_in_memory.empty()) {
			// std::cout << "referencia (pagina) autal: " << page << "\n";
			// std::cout << "tamanho ate proxima referencia: " << lenght_until_next_reference << "\n";
			map_of_pages_in_memory[page] = lenght_until_next_reference;
			// page fault
			setPagefaultqtd();
			increment++;
			continue;
		}
		decrementTimeUntilNextReference(); // atualiza as etiquetas
		auto in_memory = map_of_pages_in_memory.find(page); // procura se pagina referenciada está na RAM

		if (in_memory != map_of_pages_in_memory.end()) {
			map_of_pages_in_memory[page] = lenght_until_next_reference;
		} else {
			//página não está na ram -> deve-se substituir/alocar uma moldura
			// page fault
			setPagefaultqtd();
			if (map_of_pages_in_memory.size() == framequantity) {
				nextPagetoReplace(page);
			}
			map_of_pages_in_memory[page] = lenght_until_next_reference;
		}
		increment++;
	}
}

/* descobre a pagina a ser substituida */
void OPT::nextPagetoReplace(int page) {
	int max_number = 0;
	int page_to_replace = -1;
	for (auto& page_in_memory: map_of_pages_in_memory) {
		if (page_in_memory.second > max_number) {
			max_number = page_in_memory.second;
			page_to_replace = page_in_memory.first;
		}
	}
	SubsPage(page_to_replace);
}

/* remove a pagina do parâmetro */
void OPT::SubsPage(int page_to_replace) {
	auto it = map_of_pages_in_memory.find(page_to_replace);

	if (it != map_of_pages_in_memory.end()) {
		map_of_pages_in_memory.erase(it); // substitui a pagina
	} else {
		std::cout << "erro ao remover\n";
	}
}

/* atualiza a etiqueta de todas as paginas em menos 1 quando avança uma iteração no tempo -> antes de realizar a substituição */
void OPT::decrementTimeUntilNextReference() {
	for (auto& pair : map_of_pages_in_memory) {
        map_of_pages_in_memory[pair.first] = pair.second - 1;
    }
}
