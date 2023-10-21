#include "definers/SubsAlgorithm.h"

void Simulador::SubsAlgorithm::ExecutePageSubs() {
	// TODO - implement SubsAlgorihtm::ExecutePageSubs
	throw "Not yet implemented";
}

int Simulador::SubsAlgorithm::getAcessmemoryqtd() {
	// TODO - implement SubsAlgorihtm::getAcessmemoryqtd
	return Acessmemoryqtd_;
}

// void Simulador::SubsAlgorihtm::setAcessmemoryqtd(int Acessmemoryqtd, int Acessmemoryqtd) {
// 	// TODO - implement SubsAlgorihtm::setAcessmemoryqtd
// 	throw "Not yet implemented";
// }

int Simulador::SubsAlgorithm::getPagefaultqtd() {
	// TODO - implement SubsAlgorihtm::getPagefaultqtd
	//throw "Not yet implemented";
	return Pagefaultqtd_;
}

void Simulador::SubsAlgorithm::setAcessmemoryqtd(int Acessmemoryqtd) {
	// TODO - implement SubsAlgorihtm::setAcessmemoryqtd
	if(Acessmemoryqtd > 0){
		Acessmemoryqtd_++;
	}
}

void Simulador::SubsAlgorithm::setPagefaultqtd() {
	// TODO - implement SubsAlgorihtm::setPagefaultqtd
	//throw "Not yet implemented";
	Pagefaultqtd_++;
}
