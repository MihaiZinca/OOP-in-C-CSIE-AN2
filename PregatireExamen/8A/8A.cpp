#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

class Produs
{
	int cod = 0;
	string denumire = "-";
	string unitate = "-";
	float pret = 0;

public:
	Produs() { }
	Produs(int _cod, string _denumire, string _unitate, float _pret)
	{
		this->cod = _cod;
		this->denumire = _denumire;
		this->unitate = _unitate;
		this->pret = _pret;
	}

	int getCod()const {
		return this->cod;
	}

	string getDenumire()const
	{
		return this->denumire;
	}
	
	void setDenumire(string _den)
	{
		this->denumire = _den;
	}
	string getUnitate()const
	{
		return this->unitate;
	}
	void setUnitate(string _unitate)
	{
		this->unitate = _unitate;
	}

	float getPret()const
	{
		return this->pret;
	}
	void setPret(float _pret)
	{
		this->pret = _pret;
	}

	friend ostream& operator<<(ostream& out, const Produs& p);
	friend ofstream& operator<<(ofstream& fout, const Produs& fp);
};

ostream& operator<<(ostream& out, const Produs& p)
{
	out << "Cod: " << p.cod;
	out << "|| Denumire: " << p.denumire;
	out << "|| Unitate de masura: " << p.unitate;
	out << "||Pret: " << p.pret;
	return out;
}

ofstream& operator<<(ofstream& fout, const Produs& fp)
{
	fout << fp.cod << " " << fp.denumire << " " << fp.unitate << " " << fp.pret;
	return fout;
}


class Cos
{
	int idClient = 0;
	string numeClient = "-";
	map<Produs*, double> produse; //adresa ob produs, cantitatea

public:
	Cos() {}
	Cos(int _idCLient,string _numeClient):idClient(_idCLient),numeClient(_numeClient) { }
	
	int getIdClient()
	{
		return this->idClient;
	}

	string getNumeClient()
	{
		return this->numeClient;
	}


	void adaugaProdus(Produs* p, double cantitate)
	{
		if (p!=nullptr)
		{
			this->produse[p] += cantitate;
		}
	}

	double& operator[](string denumire)
	{
		for (auto& p : this->produse)
		{
			if (p.first->getDenumire() == denumire) return p.second;
		}
		
		throw runtime_error("Produs inexistent");
	}

	double& operator[](int _cod)
	{
		for (auto& p : this->produse)
		{
			if (p.first->getCod() == _cod)return p.second;
		}
		double v = 0;
		return v;
	}

	
	Cos& operator-=(int _cod)
	{
		for (auto it = this->produse.begin(); it != this->produse.end();++it)
		{
			if (it->first->getCod() == _cod)
			{
				it = this->produse.erase(it);
				break;
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Cos& c);
	friend ofstream& operator<<(ofstream& fout, const Cos& c);
};

ostream& operator<<(ostream& out, const Cos& c)
{
	out << "\nIdClient: " << c.idClient;
	
	//nu am fct sortarea

	double total = 0;
	for (const auto& p : c.produse)
	{
		double v = p.first->getPret() * p.second;
		out << "\t" << p.first->getDenumire() << "\t" << p.second << "\t" << v << endl;
		total += v;
	}
	out << total << endl;
	return out;
}

ofstream& operator<<(ofstream& fout, const Cos& c)
{
	fout << "\nIdClient: " << c.idClient;
	fout << "\nNumeClient: " << c.numeClient;
	for (const auto& p : c.produse)
	{
		fout << p.first->getCod() << " " << p.second << endl;
	}
	return fout;
}

int main()
{
	Produs p1(10, "Banane", "kg", 8);
	Produs p2(20, "Apa", "l", 3);
	Produs p3(30, "Unt", "kg", 25);

	Cos Cosul(100, "Gigi");
	Cosul.adaugaProdus(&p1, 1);
	Cosul.adaugaProdus(&p2, 2);
	
	cout << Cosul;
	return 0;
}

