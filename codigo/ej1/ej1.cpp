#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef vector<int> TrabajosFinales;
typedef int Indice;
typedef vector<vector<int> > Costos;

int cantTrabajos;
Costos cs;
vector<vector<int> > matriz;

int minimizacionDeCostos(int m1, int m2)  {
	int sigTrabajo = max(m1, m2)+1; //calculo el siguiente trabajo
	if (sigTrabajo > cantTrabajos)
		return 0;
	if (matriz[m1][m2]>-1)
		return matriz[m1][m2];
	else {
		int costo1 = cs[sigTrabajo-1][m1] + minimizacionDeCostos(sigTrabajo, m2);
		int costo2 = cs[sigTrabajo-1][m2] + minimizacionDeCostos(m1, sigTrabajo);
		if (costo1 < costo2) {
			matriz[m1][m2] = costo1;
			matriz[m2][m1] = costo1;
			return costo1;
		} else {
			matriz[m1][m2] = costo2;
			matriz[m2][m1] = costo2;
			return costo2;
		}
	}
}

void inicializarMinimizacionDeCostos() {
	//caso base: No hay trabajos
	if(cantTrabajos == 0){
		cout << 0 << " " << 0 <<endl;
		return;
	}
	matriz.resize(cantTrabajos);
	for(int i = 0; i < cantTrabajos; i++)
		matriz[i].resize(cantTrabajos, -1);

	cout << minimizacionDeCostos(0,0) << " ";

	int m1=0, m2=0;
	vector<int> maquina1;

	for (int i = 1; i < cantTrabajos; ++i)
		if (matriz[i][m2] < matriz[m1][i])
			m1 = i;
		else {
			m2 = i;
			maquina1.push_back(i);
		}
	
	if (cs[cantTrabajos-1][m2] < cs[cantTrabajos-1][m1]) 
		maquina1.push_back(cantTrabajos);

	cout << maquina1.size() << " ";

	for (unsigned int i = 0; i < maquina1.size(); ++i)
		cout << maquina1[i] << " ";
	cout << endl;

	return;
}

int main() {
	// stdin = freopen("./ej1.in", "r", stdin);
	int termino = '1';
	while (termino != '0') {
		int c;
		cs.clear(); //Limpio cs para las proximas instancias
		cin >> cantTrabajos; //Me guardo la cantidad de trabajos

		cs.resize(cantTrabajos); //Mi matriz de costos tiene una fila por cada trabajo
		for (int i=0;i<cantTrabajos;++i)  { //En cada trabajo tiene una cantidad de costos escalonada depdendiente el i-ésimo trabajo
			for (int j=0;j<=i;++j)  {
				cin >> c;
				cs[i].push_back(c);
			}
		}

		auto t1 = chrono::high_resolution_clock::now();
		inicializarMinimizacionDeCostos();
		auto t2 = chrono::high_resolution_clock::now();
		auto x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
		cerr << cantTrabajos << " " << x << endl;
		termino = (cin >> ws).peek();
	}
	return 0;
}
