#ifndef LRU_H
#define LRU_H

#include "SubsAlgorithm.h"
#include <list>

namespace Simulador {
	class LRU: public SubsAlgorithm {
		public:
			LRU(int framequantity);
			void UpdateFrame() override;
			void SubsPage() override;
			void nextPagetoReplace(int page) override;
			void ExecutePageSubs(std::list<int>& ref_list);

		private:
			int framequantity;
			std::list<int> ordered_list;
	};
}

#endif
