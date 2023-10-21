#include "definers/OPT.h"

using namespace Simulador;

//construtor
OPT::OPT(int frameqtd) {
	frame_quantity = frameqtd;
}

//destrutor
OPT::~OPT() {

}

void OPT::UpdateFrame(int page) {
	// TODO - implement OPT::UpdateFrame
	throw "Not yet implemented";

}

int OPT::findNextReferenceOfPage(int page, int start, std::list<int>& references) {
	int lenght = 0;
	for (int &future_page: references ) {
		if (future_page == page) {
			return lenght;
		} else {
			lenght++;
		}
	}
	return lenght;
}

void OPT::ExecutePageSubs(std::list<int>& to_be_referenced_pages) {
	int fault_quantity = 0;
	for (int& page: to_be_referenced_pages) {

		auto page_position = std::find(to_be_referenced_pages.begin(), to_be_referenced_pages.end(), page);

		if (list_of_pages_in_memory.empty()) {
			int lenght_until_next_reference = findNextReferenceOfPage(page, 0, to_be_referenced_pages);
			std::cout << "tamanho ate proxima referencia: " << lenght_until_next_reference << "\n";
			//list_of_pages_in_memory.push_front(page);
			fault_quantity++;
			continue;
		}
	}
}

void OPT::nextPagetoReplace(int page) {

}

void OPT::SubsPage(int page) {
	// TODO - implement OPT::SubsPage
	throw "Not yet implemented";
}
