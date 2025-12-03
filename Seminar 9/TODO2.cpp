
#include<iostream>
using namespace std;

//HOME2 ->ALOCARE DINAMICA HIBRID (LA INCEPUT ARE UN DEFAULT SPATIU PENTRU ARME DE 5. ATUNCI CAND IL UMPLE, REDIMENSIONEAZA PE DUBLU)
class Caracter {
	const int id;
	string denumire = "-";
	int nivelViata = 80;//apartine intervalului (0;100]

	int nrArme = 0;
	int capacitateArme = 5;
	double* putereArme = nullptr;
	
	static int minViata;

public:
	Caracter(int _id) :id(_id) {

		this->putereArme = new double[this->capacitateArme];
	}

	Caracter(int _id, string _denumire) :id(_id) {
		this->denumire = _denumire;
		this->putereArme = new double[this->capacitateArme];
	}

	Caracter(const Caracter& c) :id(c.id) 
	{

		this->denumire = c.denumire;
		this->nivelViata = c.nivelViata;

		this->capacitateArme = c.capacitateArme;

		if (c.nrArme > 0 && c.putereArme != nullptr)
		{
			this->nrArme = c.nrArme;
			this->putereArme = new double[this->capacitateArme];
			for (int i = 0; i < this->nrArme; i++)
				this->putereArme[i] = c.putereArme[i];
		}
		
		
		
	}

	Caracter& operator=(const Caracter& c)
	{
		if (this != &c)
		{
			if (this->putereArme != nullptr)
			{
				delete[] this->putereArme;
				this->putereArme = nullptr;
				this->nrArme = 0;
			}
			this->denumire = c.denumire;
			this->nivelViata = c.nivelViata;

			this->capacitateArme = c.capacitateArme;

			if (c.nrArme > 0 && c.putereArme != nullptr)
			{
				this->nrArme = c.nrArme;
				this->putereArme = new double[this->capacitateArme];
				for (int i = 0; i < this->nrArme; i++)
					this->putereArme[i] = c.putereArme[i];
			}
			else
			{
				this->nrArme = 0;
				this->putereArme = nullptr;
			}
		}
		return *this;
	}

	~Caracter() {
		if (this->putereArme != nullptr)
		{
			delete[] this->putereArme;
			this->putereArme = nullptr;
			this->nrArme = 0;
		}
	}

	Caracter& operator+=(double _x) {
		if (_x > 0)
		{
			if (this->nrArme == this->capacitateArme)
			{
				this->capacitateArme *= 2;
				double* rez = new double[this->capacitateArme];
				for (int i = 0; i < this->nrArme; i++)
					rez[i] = this->putereArme[i];

				delete[] this->putereArme;
				this->putereArme = rez;
				
			}

			this->putereArme[this->nrArme++] = _x;
			return *this;
		}

	}

	//forma-prefixata
	Caracter& operator++() {
		this->nivelViata *= 1.1;
		if (this->nivelViata > 100) {
			this->nivelViata = 100;
		}
		return *this;//returnam obj de dupa modificare
	}

	//forma-postfixata
	Caracter operator++(int) {
		Caracter copie = *this;
		++(*this);
		//this->operator++();
		return copie;//returnam obj de dinainte de modificare

	}

	//cast explicit la double
	explicit operator double() {
		double total = 0;
		for (int i = 0; i < this->nrArme; i++)
			total += this->putereArme[i];
		return total;
	}


	Caracter operator+(const Caracter& c) const {  //const nu modifc obiectul curent(*this)
		Caracter rez = *this;
		for (int i = 0; i < c.nrArme; i++)
			rez += c.putereArme[i];
		return rez;
	}


	//this+=c; -> this = this+c;
	Caracter operator+=(const Caracter& c) {
		Caracter copie = *this;
		*this = *this + c;
		return *this;
	}


	//this-ul il ataca pe c
	void operator>>(Caracter& c) {
		if (this->nivelViata > Caracter::minViata) {
			//this->operator+=(c);
			(*this) += c;
			delete[] c.putereArme;
			c.capacitateArme = 5;
			c.nrArme = 0;
			c.putereArme = new double[c.capacitateArme];
			
		}
	}

	friend ostream& operator<<(ostream& out, const Caracter& c);
};

int Caracter::minViata = 20;

ostream& operator<<(ostream& out, const Caracter& c) {
	out << "\nId: " << c.id;
	out << "\nDenumire: " << c.denumire;
	out << "\nNivel viata: " << c.nivelViata;
	out << "\nNr arme: " << c.nrArme;
	out << "\nArme: ";
	for (int i = 0; i < c.nrArme; i++)
		out << c.putereArme[i] << " ";
	return out;
}

int main() {
	Caracter c1(1, "unu");

	for (int i = 1; i <= 7; i++) 
		c1 += i * 2; 

	cout << "Caracter 1 dupa adaugarea armelor:" << c1;

	++c1;
	cout << "\nCaracter 1 dupa ++:" << c1 ;

	// Putere totala
	double putereTotala = (double)c1;
	cout << "\nPuterea totala a caracterului 1: " << putereTotala;

	return 0;
}
