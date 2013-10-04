vector<int> raiz;
vector<int> rango;
vector<bool> aristaMarcada;

int costoTotal(vector<Arista>& aristas)
{
	int res = 0;
	for(int i=0;i<aristas.size();++i)
		res += aristas[i].peso;
	return res;
}

bool comparation(Arista a,Arista b){
	return (a.peso<b.peso);
}

int find(int nodo){
    if(nodo == raiz[nodo]) //Si estoy en la raiz, la devuelvo
        return nodo;        
    else 
		return raiz[nodo] = find(raiz[nodo]); //busco al padre de forma recursiva y hago un paso de compresion
}


void Union (int nodoA, int nodoB, int find_a, int find_b){
	if(rango[find_a] > rango[find_b]) //altura de la componente del vértice a es mayor que la de la componente del vértice b
	    raiz[find_b] = find_a;            
    else{                    //la altura de la componente del vértice b es mayor o igual que la de a
	    raiz[find_a] = find_b;         
     	if(rango[find_a] == rango[find_b] ) //si poseen la misma altura incremento el rango de la nueva raíz
			rango[find_b]++;
	}
}

//entra aristas

vector<Arista> kruskal (int cantnodos, vector<Arista>& aristas) {
	//ordeno las aristas segun su peso
	sort(aristas.begin(), aristas.end(), comparation); //O(mlogm) con m=#aristas

	//inicializo los arreglos
	raiz.resize(aristas.size()); //O(m) con m=#aristas
	rango.resize(aristas.size()); //O(m) con m=#aristas
	aristaMarcada.resize(aristas.size()); //O(m) con m=#aristas

	for (int i = 0; i < cantnodos; i++) { //O(n) con n=#nodos
		raiz[i] = i;
		rango[i] = 0;
		aristaMarcada[i] = false;
	}
	int cant_enlaces = 0;
	
	for (int i = 0; i < aristas.size(); i++) { //O(m) con m=#aristas
		aristas[i].nodo_a--;
		aristas[i].nodo_b--;
	}
	
	//Verifico si estan o no en la misma componente conexa
	for( int i = 0 ; i < aristas.size(); i++ ){ //O(m) con m=#aristas
		int find_a = find(aristas[i].nodo_a);
		int find_b = find(aristas[i].nodo_b);
		if(find_a != find_b){ //si no estan en la misma componente conexa los uno
			Union(aristas[i].nodo_a , aristas[i].nodo_b, find_a, find_b);  //Union de ambas componentes en una sola
			cant_enlaces++;
			aristaMarcada[i] = true;
		}
	}
	
	for (int i = 0; i < aristas.size(); i++) { //O(m) con m=#aristas
		aristas[i].nodo_a++;
		aristas[i].nodo_b++;
	}
	
	vector<Arista> aristasDeKruskal;
	aristasDeKruskal.resize(cant_enlaces); //O(m) con m=#aristas
	int j = 0;
	for (int i = 0; i < aristas.size(); i++){
		if(aristaMarcada[i]){
			aristasDeKruskal[j] = aristas[i];
			j++;
		}			
	}
	return aristasDeKruskal;
	
}
