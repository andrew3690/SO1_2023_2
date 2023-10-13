#ifndef SIMULADOR_H
#define SIMULADOR_H

namespace Simulador {
	class Simulador {

	private:
		int frameqtd;
		int refsequence;

	public:
		void main();

		void getFrameqtd();

		void setFrameqtd(int frameqtd);

		void getRefsequence();

		void setRefsequence(int refsequence);

		void Showresult();

		void Callalgorithm();

		void InputHandler(char* file);
	};
}

#endif
