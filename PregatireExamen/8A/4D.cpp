#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Angajat
{
	int marca = 0;
	string nume = "-";
	
public:
	Angajat(){ }
	Angajat(int _marca, string _nume)
	{
		this->marca = _marca;
		this->nume = _nume;
	}

	 int getMarca()const
	{
		return this->marca;
	}
	 string getNume()const
	 {
		 return this->nume;
	 }

	 void setMarca(int _marca) { this->marca = _marca; }
	 void setNume(string _nume) { this->nume = _nume; }

	 virtual float salariu()const = 0;
	
	 friend ostream& operator<<(ostream& out, const Angajat& a);
};
ostream& operator<<(ostream& out, const Angajat& a)
{
	out << "Marca:" << a.marca << " " << "Numele:" << a.nume << " " << "Salariul:" << a.salariu();
	return out;
}

class Inginer :public Angajat
{
	int nrOre = 0;
	float salariuOra = 0;
	float spor = 0;

public:
	Inginer(){ }
	Inginer(int _marca, string _nume, int _nrOre, float _salariuOra, float _spor) :Angajat(_marca, _nume), nrOre(_nrOre), salariuOra(_salariuOra), spor(_spor) { }

	int getNrOre() { return nrOre; }
	float getSalariuOra() { return salariuOra; }
	float getSpor() { return spor; }

	float salariu()const override
	{
		return nrOre * salariuOra * spor;
	}
};

class Muncitor :public Angajat
{
	int nrPiese = 0;
	float manoperaPiesa = 0;

public:
	Muncitor(){ }
	Muncitor(int _marca, string _nume,int _nrPiese,float _man):Angajat(_marca,_nume),nrPiese(_nrPiese),manoperaPiesa(_man){ }

	int getNrPiese() { return nrPiese; }
	float getManopera() { return manoperaPiesa; }

	float salariu()const override
	{
		return nrPiese * manoperaPiesa;
	}
};

void afisare_stat(const vector<Angajat*>& v)
{
	for (auto a : v)
	{
		if (dynamic_cast<Inginer*>(a))
			cout << "I: ";
		else
			if (dynamic_cast<Muncitor*>(a))
				cout << "M: ";
		cout << *a << endl;
	}
}

int main() {
	vector<Angajat*> angajati;

	angajati.push_back(new Inginer(100, "Vasilica", 160, 20, 222));
	angajati.push_back(new Inginer(200, "Adam", 150, 14, 144));
	angajati.push_back(new Muncitor(300, "Elena", 160, 10));
	angajati.push_back(new Muncitor(550, "Virgil", 155, 10));

	afisare_stat(angajati);

	return 0;
}