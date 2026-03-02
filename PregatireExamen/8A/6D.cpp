#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Punct
{
	string nume="-";
	double x = 0;
	double y = 0;

public:
	Punct(){ }
	Punct(string _nume, double _x, double _y)
	{
		this->nume = _nume;
		this->x = _x;
		this->y = _y;
	}

	string getNume()const { return this->nume; }
	void setNume(string _nume) { this->nume = _nume; }

	double getX()const { return this->x; }
	void setX(double _x) { this->x = _x; }

	double getY()const { return this->y; }
	void setY(double _y) { this->y = _y; }

	double operator()(const Punct& p)const
	{
		return sqrt((this->x - p.x)*(this->x - p.x) + (this->y - p.y) * (this->y - p.y));
	}

	friend ostream& operator<<(ostream& out, const Punct& p);
};

ostream& operator<<(ostream& out, const Punct& p)
{
	out << "{" << p.nume << ", (" << p.x << "," << p.y << ") }"<<endl;
	return out;
}

class Traseu
{
	string nume="-";
	vector<Punct> puncte;

public:
	Traseu() { }
	Traseu(string _nume):nume(_nume){ }

	string getNume() { return this->nume; }
	vector<Punct> getPuncte() { return this->puncte;}

	Traseu& operator<<(const Punct& p)
	{
		this->puncte.push_back(p);
		return *this;
	}


	Punct* operator[](string _nume)
	{
		for (auto& p : this->puncte)
		{
			if (p.getNume() == _nume)return &p;
		}
		return nullptr;
	}

	operator double()const
	{
		double lungime = 0;
		for (size_t i = 1; i < this->puncte.size(); i++)
			lungime += this->puncte[i-1](puncte[i]);

		return lungime;
	}

	friend ostream& operator<<(ostream& out, const Traseu& t);
	friend ofstream& operator<<(ofstream& fout, const Traseu& t);

};
ostream& operator<<(ostream& out, const Traseu& t)
{
	out << "Traseu " << t.nume << endl;
	for (auto p : t.puncte)
	{
		out << "\t" << p << endl;
	}
	out << "Lungime traseu: "<<(double)t;
	return out;
}

ofstream& operator<<(ofstream& fout, const Traseu& t)
{
	fout << "Traseu " << t.nume << endl;
	for (auto p : t.puncte)
	{
		fout << "\t" << p << endl;
	}
	fout << "Lungime traseu: " << (double)t;
	return fout;
}