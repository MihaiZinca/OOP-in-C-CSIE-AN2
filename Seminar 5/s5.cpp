#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

class Produs
{
	//to do home(denumire initializata cu Anonim)
	// char* denumire=new char[8]{"Anonim"};
	char* denumire=nullptr; //elimin ramura de else
	int stoc=0;
	double pret=0;

public:
	//constructori
	Produs()
	{

		cout << "\nApel constructor fara param";
		//le am initializat in class la inceput
	}
	//DP Builder care ofera posibilitatea de construire obj
	Produs(const char* _denumire, int _stoc, double _pret)
	{
		cout << "\nApel constructor cu toti param";
		if (_denumire!=nullptr && strlen(_denumire) > 3)
		{
			this->denumire = new char[strlen(_denumire) + 1];
			strcpy_s(this->denumire, strlen(_denumire)+1, _denumire);
		}
		if (_stoc > 0)
			this->stoc = _stoc;
		if (_pret > 0)
			this->pret = _pret;
	}

	//constructor copiere pe baza unui obiect existent!!

	//transfer prin valoarea face o copie, copia necesita un const de copiere (Produs p)
	//home: chiar daca e const ce anume putem modifica? -obiectul sursa (p) este const, nu putem modifica continutul lui, dar putem modifica membrii obiectului curent (*this)
	Produs(const Produs& p) //se trasnfera prin referinta, ca sa ocolim copierea si sa nu depinda de alta copiere(ca sa modific obiectul), const protejam pe p
	{
		cout << "\nApel copy constructor:";
		//this se va construi pe baza lui p;
		if (p.denumire != nullptr)
		{
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy_s(this->denumire, strlen(p.denumire)+1, p.denumire);
		}
			this->stoc = p.stoc;
			this->pret = p.pret;
			//nu mai trebuie sa punem validari, deja sunt validate pana la constru de copiere
	}



	//destructor sa nu avem memory leaks
	~Produs()
	{
		cout << "\nApel destructor";
		if (this->denumire != nullptr) //in plus if ul, functioneaza si fara if!!
		{
			delete[] this->denumire; //sa nu avem memory leaks
			this->denumire = nullptr; // sa nu aveam dangling pointer
		}

	}

	
	//operator=   -supraincaracrea operator =specializarea op existeti sa gestioneze si alte obiecte
	
	Produs& operator=(const Produs& p) //primeste al doilea operator gen primu e "inghitit" de thits //transfer prin referinta sa ocolim copierea si const sa nu l modificam
	{

		//obj this deja exista
		//destructor
		//constructor de copiere
		if (this != &p) // ssa nu ne aflam in auto-asignare
		{
			if (this->denumire != nullptr)
			{
				delete[] this->denumire;
				this->denumire = nullptr;
			}

			if (p.denumire != nullptr)
			{
				this->denumire = new char[strlen(p.denumire) + 1];
				strcpy_s(this->denumire, strlen(p.denumire) + 1, p.denumire);
			}
			else
			{
				//de adaugat caci nu mai este constructor si nu mai intializat de la inceput gen
				this->denumire = nullptr;
			}
			this->stoc = p.stoc;
			this->pret = p.pret;
		}
			return *this;  //facem prin referinta& ca sa ocolim copierea .si sa permita compunerea
		
		//  !! de ce dam return la operator = pt apel in compunere


	}

	//meth afisare
	void afisare()
	{
		cout << "\nDenumire: ";
		if (this->denumire != nullptr)
		{
			cout << this->denumire;
		}
		else
			cout << "-";
		cout << "\n Stoc:" << this->stoc;
		cout << "\nPret " << this->pret;
	}
};

Produs fctGlobala(Produs p) 
{
	return p;
}

int main()
{
	Produs p1;
	Produs p2("Carte", 100, 120);
	p1.afisare();
	p2.afisare();
	Produs p3 = p2; //il ia pe p2 si il atribuie unuei forme de constructor atribuirea unuicul 
	Produs p4(p3);

	cout << "\n------------------------";
	Produs p5;
	fctGlobala(p5);
	cout << "\n------------------------";

	Produs* pp = new Produs(); //pointer ul il creaaza, dar nu il si distruge!! // noi trebuie sa l dezalocam
	delete pp;
	pp = nullptr;

	p3 = p2; // operanzi (p3 si p2) pentru 


	//daca p1=p3=p2; nu merge deci trebuie sa facem operatorul sa returneze this.

	p1 = p1; //auto-asignare(nasoala daca am alocat mem)


	//supraincarcarea operatorilor nu trebuie sa devieze de la logica!!
	
	//REGULI SUPRAINCARCARE OPERATORI
	//p1.Se identifica operanzii
	//p2.Daca primul operand este de tipul clasei, atunci se poate supraincarca printr o metoda a clasei, iar primul operand este "inghitit" de this
	//else la p2,(aka cout<<p), daca primul operand nu este de tipul clasei atunci se supraincarca obligatoriu prin functie globala (no more this)
	//p3.Ce returneaza operatorul?
	//p4.CE SE MODIFICA?!!!!

	return 0;
}