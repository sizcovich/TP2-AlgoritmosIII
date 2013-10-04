#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <list> // http://www.cplusplus.com/reference/list/list/
#include <vector> // http://www.cplusplus.com/reference/vector/vector/
#include <algorithm>
using namespace std;


//grafo
struct Arista{
	int nodo_a;
	int nodo_b;
	int peso;
};
int cant_nodos;
int cantFabricas;
//Fin grafo

#include "../ej2/kruskal.h"

vector<Arista> filtrar(int ghost, vector<Arista>& ady) //O(R)
{
	vector<Arista> res;
	res.reserve(ady.size()-cantFabricas);
	for (int i=0;i<ady.size();++i)
	{
	if (ady[i].nodo_a != ghost)
		res.push_back(ady[i]);
	}
	--cant_nodos; //elimino el nodo ghost
	return res;
}

int agregarNodo()
{
	++cant_nodos;
	return (cant_nodos);
}

vector<Arista> seleccionDeRutas(vector<Arista>& adyacencias)
{
	if (adyacencias.empty()) {
		vector<Arista> res;
		return res;
	}
	int ghost = agregarNodo();

	for (int i=1;i<=cantFabricas;++i) //solo le agrego aristas a los nodos fabricas, O(F)
	{
	Arista arista;
	arista.nodo_a = ghost;
	arista.nodo_b = i;
	arista.peso = 0;
		adyacencias.push_back(arista); //O(1)
	}
	vector<Arista> res;
	res = kruskal(cant_nodos,adyacencias);
	res = filtrar(ghost,res); //O(R+F)=O(R)
	return res;
}



int main() {
 // stdin = freopen("./ej3.in","r", stdin);
 vector<Arista> adyacencias;
 char termino = ' ';
	while (termino != '0') {

		adyacencias.clear();
		cant_nodos = 0;
		cantFabricas = 0;

		int F,C,R;
		cin >> F;
		cin >> C;
		cin >> R;
		adyacencias.reserve(R+F); //+F porque voy a agregar esas aristas con el nodo fantasma
		cantFabricas = F; // O(1)
		cant_nodos = F + C; // O(1)
		for (int i = 0; i < R; ++i) //O(R)
		{
			Arista arista;
			cin >> arista.nodo_a; //inicio arista
			cin >> arista.nodo_b; //fin arista
			cin >> arista.peso; //peso
			adyacencias.push_back(arista); //O(1)
		}
		
		auto t1 = chrono::high_resolution_clock::now();
		vector<Arista> res;
		res = seleccionDeRutas(adyacencias);
		auto t2 = chrono::high_resolution_clock::now();
		auto x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
		cerr << x << endl;


		cout<<costoTotal(res)<<" "<<res.size()<<" ";
		for (int i = 0; i < res.size(); ++i)
			cout << res[i].nodo_a << " " << res[i].nodo_b << " ";
		cout << endl;
		termino = (cin >> ws).peek();
	}

	return 0;
}
