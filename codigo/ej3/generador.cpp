#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

typedef int Peso;
struct Nodo {
	int tipo;
	vector<Peso> adyacentes;
	Nodo() {
		tipo = 0;
	}
};
typedef vector<Nodo> Grafo;

void mostrarGrafo(Grafo g) {
	cout << "\t\t";
	for (int i = 0; i < g.size(); ++i)
	{
		if (g[i].tipo)
			cout << "F" << i << "  \t";
		else
			cout << "C" << i << "  \t";
		/* code */
	}
	cout << endl;
	for (int i = 0; i < g.size(); ++i)
	{
		if (g[i].tipo)
			cout << "F" << i << ":  \t";
		else
			cout << "C" << i << ":  \t";
		for (int j = 0; j < g[i].adyacentes.size(); ++j)
		{
			if (i>j || i<j)
				cout << g[i].adyacentes[j] << "\t";
			else
				cout << "-\t";
		}
		cout << endl;
	}
	cout << endl;
}

bool dfs(int n, Grafo& g, vector<bool>& v) {
	v[n] = true;
	bool r = false;
	for (int i = 0; i < g[n].adyacentes.size(); ++i)
		if (g[n].adyacentes[i]>0 && i!=n)
			if (g[i].tipo)
				return true;
			else if (!v[i])
				r = r || dfs(i,g,v);
	return r;
}

int main(int argc, char const *argv[])
{
	int cantNodos = atoi(argv[1]);
	int porcentajeFabricas = atoi(argv[2]);
	int porcentajeRutas = atoi(argv[3]);
	int pesoMaximo = atoi(argv[4]);
	int seed = atoi(argv[5]);
	srand(seed);

	// int cantNodos = 10;
	// int porcentajeFabricas = 20;
	// int porcentajeRutas = 30;
	// int pesoMaximo = 150;
	// int seed = time(0);
	// srand(time(0));s

	// cout << "Cant nodos: " << cantNodos << endl;
	// cout << "Cant Fabricas: " << porcentajeFabricas << endl;
	// cout << "Cant Rutas: " << porcentajeRutas << endl;
	// cout << "Peso Max: " << pesoMaximo << endl;

	unsigned long int maxAristas = cantNodos;
	maxAristas *= maxAristas-1;
	maxAristas /= 2;
	maxAristas *= porcentajeRutas;
	maxAristas /= 100;

	// cout << "MAX ARISTAS " << maxAristas; 


	// unsigned long long int maxAristas = (porcentajeRutas * ((cantNodos*(cantNodos-1))/2)) / 100;
	// cout << maxAristas << endl << endl;

	// return 0;

	int F=(porcentajeFabricas*cantNodos)/100, C=cantNodos-F;
	unsigned long int R=0;
	if (!F) {
		cout << "No hay fabricas!";
		return 0;
	}
	Grafo g;
	g.resize(cantNodos);
	for (int i = 0; i < cantNodos; ++i)
		g[i].adyacentes.resize(cantNodos, 0);

	for (int i = 0; i < ((porcentajeFabricas*cantNodos)/100); ++i) 
		g[i].tipo = 1;

	random_device rd;
	mt19937 gr(rd());

	shuffle(g.begin(), g.end(), gr);

	int i=0;
	while(maxAristas>R) {
		int c = rand() % cantNodos;
		i = (i + 1) % cantNodos;
		if (c != i) {
			if (g[i].adyacentes[c]==0) {
				g[i].adyacentes[c] = (rand() % pesoMaximo) + 1;
				R++;
			} else {
				for (int j = 0; j < cantNodos; ++j)
				{
					c = (c+1) % cantNodos;
					if (g[i].adyacentes[c]==0 && c != i) {
						g[i].adyacentes[c] = (rand() % pesoMaximo) + 1;
						R++;
						break;
					}
				}
			}
			g[c].adyacentes[i] = g[i].adyacentes[c];
		}
	}

	vector<int> lleganAFabrica;
	vector<bool> v; //VISITADOS
	for (int i = 0; i < cantNodos; ++i)	{
		if (g[i].tipo)
			lleganAFabrica.push_back(i);
		else {
			v.clear(); v.resize(cantNodos, false);
			if (dfs(i, g, v))
				lleganAFabrica.push_back(i);
		}
	}


	//----------------------------------------------------------------------------------
	// mostrarGrafo(g);
	// cout << "NODOS QUE LLEGAN A FABRICAS: \t";
	// for (int i = 0; i < lleganAFabrica.size(); ++i)
	// 	cout << lleganAFabrica[i] << "\t";
	// cout << endl;
	//----------------------------------------------------------------------------------

	for (int i = 0; i < cantNodos; ++i)
	{
		auto r1 = find(lleganAFabrica.begin(), lleganAFabrica.end(), i);
		if (r1 == lleganAFabrica.end()) {
			int candidato = lleganAFabrica[rand() % lleganAFabrica.size()];
			R++;
			// cout << g[i].adyacentes[ca.ndidato] << endl << endl;
			// cout << "a " << i << " lo conecte con " << candidato << endl;
			g[i].adyacentes[candidato] = (rand() % pesoMaximo) + 1;
			g[candidato].adyacentes[i] = g[i].adyacentes[candidato];
			lleganAFabrica.push_back(i);
		}
	}


	//----------------------------------------------------------------------------------
	// cout << "TODOS LLEGAN A FABRICAS: \t\t";
	// for (int i = 0; i < lleganAFabrica.size(); ++i)
	// 	cout << lleganAFabrica[i] << "\t";
	// cout << endl << endl;
	// mostrarGrafo(g);
	//----------------------------------------------------------------------------------

	cout << F << " " << C << " " << R << endl;
	for (int i = 0; i < cantNodos; ++i)
		for (int j = 0; j < i; ++j)
			if (g[i].adyacentes[j]>0)
				cout << i+1 << " " << j+1 << " " <<	g[i].adyacentes[j] << endl;
	cout << 0;
	


	return 0;
}