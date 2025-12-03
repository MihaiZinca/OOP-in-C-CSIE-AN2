#include <iostream>
using namespace std;

void eliminare_min(int* &v, int &n)
{
	//P1. se calculeaza dimensiune noua 
	int dim = n - 1;
	//P2. se aloca zona de memorie pentru noul vector(aux)
	int* aux = new int[dim];
	//P3. se copiaza in noul vector tot ce este nevoie
	// int min = INT_MAX;
	//int min = 9999;
	int min=v[0];
	for (int i = 0; i < n; i++)
	{
		if (v[i] < min)
			min = v[i];
	}
	int ok = 0,k=0;
	for (int i = 0; i < n; i++)
	{
		if (v[i] == min)
			if (ok == 0)ok = 1;
			else
				aux[k++] = v[i];
		else
			aux[k++] = v[i];
	}
	//P4. se dezaloca fostul v
	delete[] v;
	v = nullptr; //pentru ca new dangling pointer 
	//P5. vector vechi ponteaza catre vector nou + actualizare dimensiune
	v = aux;
	n = dim;
}

int main()
{
	int n, * v;
	cin >> n;
	v = new int[n];// aloc de n ori int ul
	int* p;
	p = new int(10);//aloc un int pe care il init cu 10
	
	for (int i = 0; i < n; i++)
		cin >> v[i];

	//ex1 functia care primeste un vector si elimina prima aparitie a val minime 
	eliminare_min(v, n);
	if (v != nullptr)
	{
		for (int i = 0; i < n; i++)
			cout << v[i] << " ";
	}
	else
		cout << "vectorul nu exista";

	
	delete[] v;
	delete p;

	return 0;
}
// Avem o lista de prieteni in care formatul este nume + lista prenume
//Sa se implementeze functia care primeste colectia de nume si dim si un nume de sfant su returnam cate cadouri trebuie sa cumparam
//zig-zag