#ifndef OPT_H
#define OPT_H
#include <unordered_map>
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

		int findNextReferenceOfPage(int page, int start, std::vector<int>& references);
		void UpdateFrame(int page) override;

		void SubsPage(int page) override;
		void ExecutePageSubs(std::vector<int>& ref_list);
		void nextPagetoReplace(int page) override;
	private:
		int framequantity;
		std::unordered_map<int, int> map_of_pages_in_memory; // hash table para as paginas que "apontam" à uma etiqueta
	};
}

#endif
