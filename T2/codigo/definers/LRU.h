#ifndef LRU_H
#define LRU_H

#include "SubsAlgorithm.h"

namespace Simulador {
	class LRU: public SubsAlgorithm {
		public:
			void UpdateFrame() override;
			void SubsPage() override;
	};
}

#endif
