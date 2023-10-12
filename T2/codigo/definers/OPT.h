#ifndef OPT_H
#define OPT_H

#include "SubsAlgorithm.h"

namespace Simulador {
	class OPT: public SubsAlgorithm {
		public:

			//construtor 
			OPT();
			void UpdateFrame() override;
			void SubsPage() override;

	};
}

#endif
