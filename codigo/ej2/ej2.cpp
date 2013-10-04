#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector> // http://www.cplusplus.com/reference/vector/vector/
#include <queue>
#include <ctgmath>

using namespace std; 

//grafo
struct Arista{
    int nodo_a;
    int nodo_b;
    int peso;
};
vector<Arista> aristas;
//Fin grafo

#include "kruskal.h"

pair<int,int> bfs (int nodo_inicial, int cantNodos, vector<vector<int> >& listaDeAdyacencia){
	vector<bool> loAgregue (cantNodos, false);
	int cabeza =0; 
	queue<int> cola;
	pair<int, int> res;
	vector<int> distancias (cantNodos, 0);
	vector<int> padre (cantNodos, 0);
	
	cola.push(nodo_inicial);
	loAgregue[nodo_inicial-1] = true;
	distancias[nodo_inicial-1] = 0;
	while (!cola.empty()){
		cabeza = cola.front();
		cola.pop();
			
		//busco los nodos adyacentes y los coloco en la cola
		for (int i = 0; i < listaDeAdyacencia[cabeza-1].size(); i++){
			int nodo = listaDeAdyacencia[cabeza-1][i];
						
			if(!loAgregue[nodo-1]){ 
				padre[nodo-1]=cabeza;
				loAgregue[nodo-1] = true;
				distancias[nodo-1] = distancias[cabeza-1] + 1;
				cola.push(nodo);
			}		
		}	
	}
	
	res.first = cabeza;
	
	int nodo = padre[cabeza-1];
	int medio = (distancias[cabeza-1])/2;
	for (int i = 0; i < cantNodos; i++){
		medio--;
		if (medio == 0)	{
			res.second = nodo;
			break;
		}
		nodo = padre[nodo-1];
	}
	
	
	return res; //devuelvo el ultimo elemento que desencole y el del medio
}
	
int master (int cantNodos, vector<vector<int> >& listaDeAdyacencia){
	pair<int, int> resDeBFS;
	
	resDeBFS = bfs(1, cantNodos, listaDeAdyacencia);
	resDeBFS = bfs(resDeBFS.first, cantNodos, listaDeAdyacencia);
	return resDeBFS.second;
}	
	
vector<Arista> AGM (int cantNodos, vector<Arista>& aristas, vector<vector<int> >& listaDeAdyacencia){
	vector<Arista> res;
	res = kruskal(cantNodos, aristas);	
	for (int i = 0; i < res.size(); i++){
		int nodoA = res[i].nodo_a;
		int nodoB = res[i].nodo_b;
		listaDeAdyacencia[nodoA-1].push_back(nodoB);
		listaDeAdyacencia[nodoB-1].push_back(nodoA);
	}
	
	return res;    
}

int main() {
	char termino = ' ';
	int cant_aristas = 0;
	int cant_nodos = 0;
	int costo;
	int nodoMaster;
		
	while (termino != '0') {
		vector<Arista> res;
		vector<vector<int> > listaDeAdyacencia;
		costo = 0;
		nodoMaster = 0;
		//cargo datos
		cin >> cant_nodos;
		cin >> cant_aristas;
		
		aristas.resize(cant_aristas);
		listaDeAdyacencia.resize(cant_nodos);
		
		int nodoA, nodoB;
		for (int i = 0; i < cant_aristas; ++i) {
			Arista a;
			cin >> a.nodo_a;
			cin >> a.nodo_b;
			cin >> a.peso;
			aristas[i] = a;
		}
		
		if(cant_aristas != 0) { //por si no tengo aristas
			//item a
			res = AGM(cant_nodos, aristas, listaDeAdyacencia);
			costo = costoTotal(res);
			
			//item b
			nodoMaster = master(cant_nodos, listaDeAdyacencia);
		} 
		
		//imprimo costo
		cout << costo << " ";
		//imprimo nodo master
		cout << nodoMaster << " ";
		//imprimo la cantidad de enlaces
		cout << res.size() << " ";
		//imprimo aristas
		for (int i = 0; i < res.size(); i++){
			cout << res[i].nodo_a << " " << res[i].nodo_b << " ";
		}
		
		cout << endl;
		termino = (cin >> ws).peek();
	}

	return 0;
}
