#include <iostream>
#include <string>
#include <map>
using namespace std;

class Material
{
	int cod = 0;
	string denumire = "-";
	string unitate = "-";
	float pret = 0;

public:
	Material() {}
	Material(int _cod, string _denumire, string _unitate, float _pret)
	{
		this->cod = _cod;
		this->denumire = _denumire;
		this->unitate = _unitate;
		this->pret = _pret;
	}

	int getCod()const { return this->cod; }
	void setCod(int _cod) { this->cod = _cod; }

	string getDenumire()const  { return this->denumire; }
	void setDenumire(string _den) { this->denumire = _den; }

	string getUnitate()const { return this->unitate; }
	void setUnitate(string _unitate) { this->unitate = _unitate; }

	float getPret()const { return this->pret; }
	void setPret(float _pret) { this->pret = _pret; }

	friend ostream& operator<<(ostream& out, const Material& m);
};
ostream& operator<<(ostream& out, const Material& m)
{
	out << "Cod:" << m.cod << " " << "Denumire:" << m.denumire << " " << "Unitate:" << m.unitate << " " << "Pret" << m.pret << endl;
	return out;
}

class Produs
{
	int codProdus = 0;
	string nume = "-";
	string um = "-";
	map<Material*, double> material;

public:
	Produs() {} 
	Produs(int _codProdus, string _nume, string _um):codProdus(_codProdus),nume(_nume),um(_um) { }

	int getCodProdus() { return this->codProdus; }
	
	string getNume() { return this->nume; }
	string getUm() { return this->um; }


	double& operator[](string _denumireMat)
	{
		for (auto& m : this->material)
		{
			if (m.first->getDenumire() == _denumireMat) return m.second;
		}
		throw runtime_error("denumire inexistenta");
	}
	 operator double() const
	{
		double total = 0;
		for (auto& m : this->material)
		{
			total += (m.first->getPret() * m.second);
		}
		return total;
	}

	operator string() const
	{
		string numeMax = "-";
		double maxi = -1;

		for (auto& m : this->material)
		{
			double val = m.first->getPret() * m.second;
			if (val >= maxi)
			{
				maxi = val;
				numeMax = m.first->getDenumire();
			}
		}
		return numeMax;
	}

	void adaugaConsum(Material* m, double _cantitate)
	{
		if (m != nullptr)
		{
			this->material[m] += _cantitate;
		}
	}

	friend ostream& operator<<(ostream& out, const Produs& p);
};
ostream& operator<<(ostream& out, const Produs& p)
{
	out << "\n---Produse----";
	out << "\nCodProdus: " << p.codProdus;
	out << "\nDenumire Produs: " << p.nume;
	out << "\nUnitate Produs: " << p.um;

	out << "\nLista materiale: ";
	for (const auto& pi : p.material)
	{
		out << "\t" << pi.first->getCod() << " " << pi.first->getDenumire() << " " << pi.first->getUnitate() << " " << pi.first->getPret() << " " << pi.second<<"\t";

	}
	return out;
}

int main()
{

	Material m1(10, "Faina", "kg", 8);
	Material m2(20, "Drojdie", "kg", 10);

	Produs paine(100, "Paine", "kg");
	paine.adaugaConsum(&m1, 1.5);
	paine.adaugaConsum(&m2, 0.3);

	cout << "\nDetalii produs: ";
	cout << paine << endl;

	double cost_paine = (double)paine;
	cout << "\nCost total: " << cost_paine<<endl;

	string matScump = (string)paine;
	cout << "\nMaterial scump max:" << matScump << endl;

	

	return 0;
}