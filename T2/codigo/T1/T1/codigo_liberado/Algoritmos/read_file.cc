#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class ProcessParams
{
public:
	ProcessParams(int c, int d, int p) { 
		creation_time = c;
		duration = d;
		priority = p;
	}

	friend ostream &operator<<(ostream& os, const ProcessParams& p) {
		os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
		return os;
	}
	
	// getters provisórios, só para perguntar pro professor se podemos usar isso aqui
	int get_creation_time() const {return creation_time;};
	int get_duration() const {return duration;};
	int get_priority() const {return priority;};

private:	
	int creation_time;
	int duration; //seconds
	int priority;
};

class File
{

public:
	File() {
		myfile.open("entrada.txt");
		if (!myfile.is_open()) {
			cout << "Erro ao abrir o arquivo!\n";
		}
	}
	
	void read_file() {
	
		int a, b, c;
		
		if (!myfile.is_open()) {
			cout << "Arquivo não está aberto!" << endl;
		}
		
		while (myfile >> a >> b >> c) {
			ProcessParams *p = new ProcessParams(a, b, c);
			processes.push_back(p);
		}

		cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
	}

	void print_processes_params() {
		vector<ProcessParams *>::iterator iter = processes.begin();

		for(iter; iter < processes.end(); iter++) {
			ProcessParams *p = *iter;
			cout << *p;
		}
	}
	
	// Perguntar para o professor se posso fazer isso aqui:
	// retorna uma tupla de informações do processo
	std::vector<std::tuple<int, int, int>> get_process_params() {
		std::vector<std::tuple<int, int, int>> params;

		for (auto iter = processes.begin(); iter != processes.end(); ++iter) {
			ProcessParams *p = *iter;
			params.push_back(std::tuple<int, int, int>(p->get_creation_time(), p->get_duration(), p->get_priority()));
		}

    	return params;
	}


	~File() {
		for(int i = 0; i < processes.size() ; i++) {
			ProcessParams *p = processes[i];
			delete p;
		}
	}

private:
	ifstream myfile; 
	vector<ProcessParams *> processes;
};

// int main()
// {
// 	File f;
// 	f.read_file();
// 	f.print_processes_params();
// }