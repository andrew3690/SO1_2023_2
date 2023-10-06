#ifndef SUBSALGORIHTM_H
#define SUBSALGORIHTM_H

namespace Simulador {
	class SubsAlgorihtm {

	private:
		int Acessmemoryqtd;
		int Pagefaultqtd;

	public:
		void ExecutePageSubs();

		void getAcessmemoryqtd();

		void setAcessmemoryqtd(int Acessmemoryqtd);

		void getPagefaultqtd();

		void setPagefaultqtd(int Pagefaultqtd);

		void UpdateFrame();

		void SubsPage();

		void nextPagetoReplace();
	};
}

#endif
