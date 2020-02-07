
/**
 * @algorithm - Kruskal algorithm 
 * @brief Arvore Geradora Minima - Kruskal.
 *        Dado um gafo G(E), não direcionado
 *        e ponderado. Retornar o caminho 
 *        mais curto com base nas ponderações.
 *
 * @link - https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
 * @By Robson Silva 
 */

#include <iostream>
#include <vector>
#include <algorithm> 
#include <string.h> 

using namespace std;

class Aresta{
private:
		int verticeOrigem;
		int verticeDestino;
		int arestaPeso;
public:
	Aresta(int _verticeOrigem, int _verticeDestino, int _arestaPeso){
		this->verticeOrigem = _verticeOrigem;
		this->verticeDestino = _verticeDestino;
		this->arestaPeso = _arestaPeso;
	}
	int getVerticeOrigem(){ return this->verticeOrigem; }
	int getVerticeDestino() { return this->verticeDestino; }
	int obterPeso() { return this->arestaPeso; }
	bool operator < (const Aresta& arestaOBJ) const { return (this->arestaPeso < arestaOBJ.arestaPeso); }
};

class Grafo : public Aresta{
private:
	int quantidadeVertices; 
	vector<Aresta> arestas; 
public:
	Grafo(int _quantidadeVertices) : Aresta(0, 0, 0) {
		this->quantidadeVertices = _quantidadeVertices+1;
	}

	void adicionarAresta(int _verticeOrigem, int _verticeDestino, int _arestaPeso){
		Aresta aresta(_verticeOrigem, _verticeDestino, _arestaPeso);
		this->arestas.push_back(aresta);
	}

	int pesquisar(int subConjunto[], int i){
		if(subConjunto[i] == -1)
			return i;
		return pesquisar(subConjunto, subConjunto[i]);
	}

	int getCusto(int _sizeAvore, vector <Aresta> _arvore){
		int custo = 0;
		for(int i = 0; i < _sizeAvore; i++){
			custo += _arvore[i].obterPeso();
		}
		return custo;
	}

	void setUnion(int * subConjunto, int size_arestas, 
				  vector<Aresta> arestas, 
				  vector<Aresta> _arvore ){

		for(int i = 0; i < size_arestas; i++)
		{
			int verticeOrigem = pesquisar(subConjunto, arestas[i].getVerticeOrigem());
			int verticeDestino = pesquisar(subConjunto, arestas[i].getVerticeDestino());

			if(verticeOrigem != verticeDestino){
				_arvore.push_back(arestas[i]);
				int verticeOrigemBusca = pesquisar(subConjunto, verticeOrigem);
				int verticeDestinomBusca = pesquisar(subConjunto, verticeDestino);
				subConjunto[verticeOrigemBusca] = verticeDestinomBusca;
			}
		}	
	}

	int kruskalMin(){
		vector<Aresta> arvore;
		int size_arestas = arestas.size();
		int * subConjunto = new int[quantidadeVertices];
		sort(arestas.begin(), arestas.end());
		memset(subConjunto, -1, sizeof(int) * quantidadeVertices);

		for(int i = 0; i < size_arestas; i++) {

			int verticeOrigem = pesquisar(subConjunto, arestas[i].getVerticeOrigem());
			int verticeDestino = pesquisar(subConjunto, arestas[i].getVerticeDestino());

			if(verticeOrigem != verticeDestino){
				arvore.push_back(arestas[i]);
				int verticeOrigemBusca = pesquisar(subConjunto, verticeOrigem);
				int verticeDestinomBusca = pesquisar(subConjunto, verticeDestino);
				subConjunto[verticeOrigemBusca] = verticeDestinomBusca;
			}
		}
		return getCusto(arvore.size(), arvore);
	}
};

int main()
{ 
	int quantidadeVertices;
	int quantidadeArestas;
	int verticeOrigem;
	int verticeDestino;
	int arestaPeso;

	while(1){
		cin >> quantidadeVertices >> quantidadeArestas;

		Grafo g(quantidadeVertices); 

		while(quantidadeArestas--){
			cin >> verticeOrigem >> verticeDestino >> arestaPeso;

			g.adicionarAresta(verticeOrigem, 
							  verticeDestino, 
							  arestaPeso);
		}
		cout << g.kruskalMin() << endl;
	}
	return 0;
} 
