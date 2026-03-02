#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;


class Monetar
{
	map<int, int> bacnote;

public:
	Monetar(){ 
		this->bacnote[10] = 0;
		this->bacnote[50] = 0;
		this->bacnote[100] = 0;
		this->bacnote[200] = 0;
	}
	Monetar(int n10, int n50 , int n100 , int n200 )
	{
		this->bacnote[10] = n10;
		this->bacnote[50] = n50;
		this->bacnote[100] = n100;
		this->bacnote[200] = n200;
	}

	int getBacnota(int _tip)const
	{
		return this->bacnote.at(_tip); //at folosit ca []
	}

	int total()const
	{
		int suma = 0;
		for (const auto& it : this->bacnote)
			suma += it.first * it.second;
		return suma;
	}
	void setBacnota(int tip, int nr)
	{
		if (tip == 10 || tip == 50 || tip == 100 || tip == 200)
		{
			this->bacnote[tip] = nr;
		}
	}

	map<int, int> getMap()
	{
		return this->bacnote;
	}

	Monetar& operator+=(const Monetar& m)
	{
		for (auto& it : m.bacnote)
		{
			this->bacnote[it.first] += it.second;
		}
		return*this;
	}
	friend ostream& operator<<(ostream& out, const Monetar& m)
	{
		for (auto& it : m.bacnote)
		{
			out << it.first << " " << it.second;
		}
		out << "Total" << m.total();
		return out;
	}

};

class Atm
{
	int id;
	Monetar numerar;

public:
	Atm(int _id):id(_id){ }

	Monetar getNumerar()const { return this->numerar; }

	friend ostream& operator<<(ostream& out, const Atm& a)
	{
		out << "id:" << a.id << endl;
		out << a.numerar;
		return out;

	}

	Atm& operator+=(const Monetar& m)
	{
		this->numerar += m;
		return *this;
	}

	int operator[](int _tip)
	{
		return this->numerar.getBacnota(_tip);
	}

	Monetar operator()(int suma)
	{
		if (suma % 10 != 0)
			throw runtime_error("Suma invalida");

		if (suma > this->numerar.total())
			throw runtime_error("fonduri insuf");

		Monetar rezultat;
		int ramas = suma;

		int bacnote[] = { 200,100,50,10 };

		for (int b : bacnote)
		{
			int disponibil = this->numerar.getBacnota(b);
			int necesar = min(disponibil, ramas / b);

			rezultat.setBacnota(b, necesar);
			this->numerar.setBacnota(b, disponibil - necesar);
			ramas -= necesar * b;
		}
		return rezultat;
	}
};
