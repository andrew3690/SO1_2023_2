#ifndef OPT_H
#define OPT_H
#include <list>
#include "SubsAlgorithm.h"
#include <algorithm>

namespace Simulador {
	class OPT: public SubsAlgorithm {


	public:
		// class Page {
		// 	public:
		// 		int id;
		// 		int label = 0;
		// };
		OPT(int frameqtd);
		~OPT();

		int findNextReferenceOfPage(int page, int start, std::list<int>& references);
		void UpdateFrame(int page) override;

		void SubsPage(int page) override;
		void ExecutePageSubs(std::list<int>& ref_list);
		void nextPagetoReplace(int page) override;
	private:
		std::list<std::pair<int, int>> list_of_pages_in_memory;
	};
}

#endif
