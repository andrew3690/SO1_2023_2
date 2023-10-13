#include "definers/SubsAlgorithm.h"

int Simulador::SubsAlgorithm::getAcessmemoryqtd() {
	// TODO - implement SubsAlgorihtm::getAcessmemoryqtd
	return Acessmemoryqtd_;
}

int Simulador::SubsAlgorithm::getPagefaultqtd() {
	// TODO - implement SubsAlgorihtm::getPagefaultqtd
	return Pagefaultqtd_;
}

void Simulador::SubsAlgorithm::setAcessmemoryqtd(int Acessmemoryqtd) {
	// TODO - implement SubsAlgorihtm::setAcessmemoryqtd
	Acessmemoryqtd_++;
}

void Simulador::SubsAlgorithm::setPagefaultqtd(int Pagefaultqtd) {
	// TODO - implement SubsAlgorihtm::setPagefaultqtd
	Pagefaultqtd_;
}
