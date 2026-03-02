#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;

class Carte
{
	int cod=0;
	string autor = "-";
	string titlu = "-";

public:
	Carte(){ }
	Carte(int _cod, string _titlu, string _autor)
	{
		this->cod = _cod;
		this->autor = _autor;
		this->titlu = _titlu;
	}

	int getCod()const { return this->cod; }
	void setCod(int _cod) { this->cod = _cod; }

	string getAutor()const { return this->autor; }
	void setAutor(string _autor) { this->autor = _autor; }
	
	string getTitlu()const { return this->titlu; }
	void setTitlu(string _titlu) { this->titlu = _titlu; }

	friend ostream& operator<<(ostream& out, const Carte& c);
	friend ofstream& operator<<(ofstream& fout, const Carte& c);
};
ostream& operator<<(ostream& out, const Carte& c)
{
	out << "Cod:" << c.cod << " "<< "Titlu " << c.titlu << " Autor " << c.autor << endl;
	return out;
}
ofstream& operator<<(ofstream& fout, const Carte& c)
{
	fout << "Cod:" << c.cod << " " << "Titlu " << c.titlu << " Autor " << c.autor << endl;
	return fout;
 }

class Sala
{
	int id = 0;
	string nume = "-";
	map<Carte*, int> fond;

public:
	Sala() {}
	Sala(int _id, string _nume)
	{
		this->id = _id;
		this->nume = _nume;
	}

	int getId() { return this->id; }
	void setId(int _id) { this->id = _id; }

	string getNume() { return this->nume; }
	void setNume(string _nume) { this->nume = _nume; }


	void adaugareCarte(Carte* c, int _nrExemplare)
	{
		if (c != nullptr)
		{
			this->fond[c] += _nrExemplare;
		}
	}


	int& operator[](int _cod)
	{
		for (auto& f : this->fond)
		{
			if (f.first->getCod() == _cod)return f.second;
		}
		throw runtime_error("nu exista");
	}
	
	int operator()()
	{
		int maxi = 0;

		for (auto& f : this->fond)
		{
			if (f.second > maxi)maxi = f.second;
		}
		for (const auto& f : this->fond)
		{
			if (f.second == maxi)
			{
				cout << f.first->getCod() << " " << maxi << endl;
			}
		}
		return maxi;
	}

	Sala& operator-=(int _cod)
	{

		for (auto it = this->fond.begin(); it != this->fond.end();++it)
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
	friend ofstream& operator<<(ofstream& fout, const Sala& s);

};
ostream& operator<<(ostream& out, const Sala& s)
{
	out << "Id sala: " << s.id << " Numele sala" << s.nume << endl;
	for (const auto& it : s.fond)
	{
		out << "\t" << it.first->getCod() << "," << it.first->getTitlu() << "," << it.first->getAutor() << "," << it.second << endl;

	}
	return out;
}

ofstream& operator<<(ofstream& fout, const Sala& s)
{
	fout << "Id sala: " << s.id << " Numele sala" << s.nume << endl;
	for (const auto& it : s.fond)
	{
		fout << "\t" << it.first->getCod() << "," << it.first->getTitlu() << "," << it.first->getAutor() << "," << it.second << endl;

	}
	return fout;
}

int main()
{

	Carte c1(10, "Crima", "Dos");
	Carte c2(20, "Idiotul", "Dos");
	Carte c3(30, "Fratii", "Dos");
	Carte c4(40, "Oameni", "Dos");

	cout << c1 << endl;
	cout << c2 << endl;
	cout << c3 << endl;
	cout << c4 << endl;

	Sala s1(101, "Sala_1");
	s1.adaugareCarte(&c1, 5);
	s1.adaugareCarte(&c2, 10);
	cout << s1 << endl;


	Sala s2(102, "Sala_2");
	s2.adaugareCarte(&c3, 4);
	s2.adaugareCarte(&c4, 7);
	s2.adaugareCarte(&c1, 2);
	cout << s2 << endl;

	cout << "cele mai multe exemplare" << endl;
	s1();

	s1[10] = 50;
	cout << "Dupa modifica cod1: " << s1;

	s1 -=20 ;
	cout << "Dupa sterge cod2: " << s1;


	return 0;
}
