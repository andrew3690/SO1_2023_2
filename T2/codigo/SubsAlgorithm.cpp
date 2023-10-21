#include "definers/SubsAlgorithm.h"

void Simulador::SubsAlgorithm::ExecutePageSubs() {
	// TODO - implement SubsAlgorihtm::ExecutePageSubs
	throw "Not yet implemented";
}

void Simulador::SubsAlgorithm::getAcessmemoryqtd() {
	// TODO - implement SubsAlgorihtm::getAcessmemoryqtd
	throw "Not yet implemented";
}

// void Simulador::SubsAlgorihtm::setAcessmemoryqtd(int Acessmemoryqtd, int Acessmemoryqtd) {
// 	// TODO - implement SubsAlgorihtm::setAcessmemoryqtd
// 	throw "Not yet implemented";
// }

int Simulador::SubsAlgorithm::getPagefaultqtd() {
	// TODO - implement SubsAlgorihtm::getPagefaultqtd
	//throw "Not yet implemented";
	return Pagefaultqtd;
}

void Simulador::SubsAlgorithm::setAcessmemoryqtd(int Acessmemoryqtd) {
	// TODO - implement SubsAlgorihtm::setAcessmemoryqtd
	acessmemoryqtd = Acessmemoryqtd;
}

void Simulador::SubsAlgorithm::setPagefaultqtd(int pagefaultqtd) {
	// TODO - implement SubsAlgorihtm::setPagefaultqtd
	//throw "Not yet implemented";
	Pagefaultqtd = pagefaultqtd;
}
