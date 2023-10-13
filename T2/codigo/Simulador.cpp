#include "definers/Simulador.h"


Simulador::Simulador::Simulador(int argc, char* argv[])
{
	// obtendo as referencias das entradas 
	this->InputHandler(argc,argv);
	// Chamada dos algoritmos é realizada aqui;
	this->Callalgorithm();
}


int Simulador::Simulador::InputHandler(int agrc, char* file[]) {
	// TODO - implement Simulador::InputHandler

	// Idéia do método, obtém a entrada de listas de refeencias do arquivo passado	
	// primeira verifica se o nome passado pelo usuário é válido
	if(agrc != 3){
		std::cerr<< "Uso: " << file[0] << " nome do arquivo" <<std::endl;
	};

	//seta a quantidade de quadros de página, que o usuário deseja
	setFrameqtd(std::stoi(file[1]));

	//Obtém o nome do arquivo nos argumentos
	std::string NomedoArquivo = file[2];

	//Abre o arquivo para leitura
	std::ifstream arquivo;
	arquivo.open(NomedoArquivo);
	std::cout << "filename:   " << NomedoArquivo << "\n";

	// Verifica se o arquivo foi aberto com sucesso
	if(!arquivo.is_open()){
		std::cerr << "Erro ao abrir o arquivo" << NomedoArquivo << std::endl;
		return 1;
	}

	// Obtém as linhas do arquivo e insere as referencias de páginas na fila de páginas 
	std::string linha;
	while(!arquivo.eof()){
		std::getline(arquivo, linha);
		std::cout << linha << std::endl;
		addToQueue(linha); // Adiciona a linha a fila de referencias
	}

	// Fechamento dos arquivos
	arquivo.close();

}

void Simulador::Simulador::addToQueue(const std::string& newItem)
{
	if (newItem != "") {
		filaDepgs.push(newItem);
	}
}

void Simulador::Simulador::Showresult() {
	// TODO - implement Simulador::Showresult
	std::cout << this->frameqtd <<"quadros" <<std::endl;
	std::cout << this->filaDepgs.size() <<"refs" <<std::endl;
	std::cout << "FIFO: " <<"PFs" <<std::endl;
	std::cout << "LRU: " <<"PFs" <<std::endl;
	std::cout << "OPT: " <<"PFs" <<std::endl;
}

void Simulador::Simulador::Callalgorithm() {
	// Chamada do FIFO
	
	// Chamada do LRU

	// Chamada do OPT
}

Simulador::Simulador::~Simulador(){
	std::cout << "Finalizando o simulador" <<std::endl; 
}

/*void Simulador::Simulador::main(int argc, char* argv[]) {
	// Instanciando o simulador
	Simulador simul;
	// obtendo as referencias das entradas 
	simul.InputHandler(argc,argv);
	// Chamada dos algoritmos é realizada aqui;
	simul.Callalgorithm();
}*/
