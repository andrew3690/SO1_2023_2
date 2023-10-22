#ifndef LRU_H
#define LRU_H

#include "SubsAlgorithm.h"
#include <vector>

namespace Simulador {
	class LRU: public SubsAlgorithm {
		public:
			LRU(int framequantity);
			~LRU();
			void UpdateFrame(int page) override;
			void SubsPage(int page) override;
			void nextPagetoReplace(int page) override;
			void ExecutePageSubs(std::vector<int>& ref_list);

		private:
			int framequantity;
			std::list<int> ordered_list;
	};
}

#endif
