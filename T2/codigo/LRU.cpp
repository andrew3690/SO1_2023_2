#include "definers/LRU.h"
#include <algorithm>

Simulador::LRU::LRU(int frameqtd) {
	framequantity = frameqtd;
}

Simulador::LRU::~LRU() {}

void Simulador::LRU::SubsPage(int page) {
	// TODO - implement LRU::SubsPage
	throw "Not yet implemented";
}

void Simulador::LRU::UpdateFrame(int page) {
	// TODO - implement LRU::UpdateFrame
	throw "Not yet implemented";
}

void Simulador::LRU::nextPagetoReplace(int page) {
	if (ordered_list.size() == framequantity) {
		ordered_list.pop_back();
	}
	ordered_list.push_front(page);
}

void Simulador::LRU::ExecutePageSubs(std::vector<int>& ref_list) {

	for (const int& page : ref_list) {
		// iterador para a posição de pagina, se encontrada na lista ordenada do algoritmo
		if (ordered_list.empty()) {
			ordered_list.push_front(page);
			setPagefaultqtd();
			continue;
		}
		auto page_position = std::find(ordered_list.begin(), ordered_list.end(), page);
		// se pagina ja está na memória
		if (page_position != ordered_list.end()) {
			ordered_list.erase(page_position);
			ordered_list.push_front(page);
		} else {
			// caso pagina requisitada não está na memoria
			setPagefaultqtd();
			nextPagetoReplace(page);
		}
	}
}
