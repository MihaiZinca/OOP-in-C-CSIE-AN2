#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

class Carte
{
	int cod = 0;
	string autor = "-";
	string titlu = "-";

public:
	
	Carte(){ }
	Carte(int _cod, string _titlu, string _autor)
	{
		this->cod = _cod;
		this->titlu = _titlu;
		this->autor = _autor;
	}

	int getCod()const { return this->cod;}
	void setCod(int _Cod) { this->cod = _Cod;}

	string getAutor()const { return this->autor; }
	string getTitlu()const { return this->titlu; }

	friend ostream& operator<<(ostream& out, const Carte& c);
	friend ofstream& operator<<(ofstream& fout, const Carte& c);
};
ostream& operator<<(ostream& out, const Carte& c)
{
	out << "Cod: " << c.cod << " Titlu" << c.titlu << "  Autor" << c.autor << endl;
	return out;
}

ofstream& operator<<(ofstream& fout, const Carte& c)
{
	fout << "Cod: " << c.cod << " Titlu" << c.titlu << "  Autor" << c.autor << endl;
	return fout;
}

class Sala
{
	int id = 0;
	string nume = "-";
	map<Carte*, int> fond;

public:
	Sala(){ }
	Sala(int _id, string _nume)
	{
		this->id = _id;
		this->nume = _nume;
	}

	int getId() { return this->id; }
	void setId(int _id) { this->id = _id; }

	string getNume() { return this->nume; }
	void setNume(string _nume) { this->nume = _nume; }


	void adaugaCarte(Carte* c, int nrExemplare)
	{
		if (c != nullptr)
		{
			this->fond[c] += nrExemplare;
		}
	}

	int& operator[](int cod)
	{
		for (auto& it : this->fond)
		{
			if (it.first->getCod() == cod) return it.second;
		}
		throw runtime_error("invalid");
	}

	int operator()()
	{
		int nrMaxi = -1;
		for (auto& it : this->fond)
		{
			if (it.second >= nrMaxi)nrMaxi = it.second;
		}
		
		for (auto& it : this->fond)
		{
			if (it.second == nrMaxi)
			{
				cout << it.first->getCod() << " " << nrMaxi;
			}
		}
		return nrMaxi;
	}

	Sala& operator-=(int _cod)
	{
		for (auto it = this->fond.begin(); it != this->fond.end(); it++)
		{
			if (it->first->getCod() == _cod)
			{
				it = this->fond.erase(it);
				break;
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Sala& s);
	friend ofstream& operator<<(ofstream& out, const Sala& s);
};
ostream& operator<<(ostream& out, const Sala& s)
{
	out << s.id << " " << s.nume << endl;
	for (const auto& it : s.fond)
	{
		out <<"\t"<<it.first->getCod() << " " << it.first->getTitlu() << it.first->getAutor() << it.second << endl;

	}
	return out;
}
ofstream& operator<<(ofstream& fout, const Sala& s)
{
	fout << s.id << " " << s.nume << endl;
	for (const auto& it : s.fond)
	{
		fout << "\t" << it.first->getCod() << " " << it.first->getTitlu() << it.first->getAutor() << it.second << endl;

	}
	return fout;
}