#include <iostream>
using namespace std;


class Caracter {
	const int id;
	string denumire = "-";
	int nivelViata = 80;//apartine intervalului (0;100]
	int nrArme = 0;
	double* putereArme = nullptr;

	static int minViata;

	   
public:
	Caracter(int _id) :id(_id) {}
	Caracter(int _id, string _denumire) :id(_id)
	{
		this->denumire = _denumire;
		
	}

	//copy constructor
	Caracter(const Caracter& c) :id(c.id)
	{
		this->denumire = c.denumire;
		this->nivelViata = c.nivelViata;
		if (c.nrArme > 0 && c.putereArme != nullptr)
		{
			this->nrArme = c.nrArme;
			this->putereArme = new double[this->nrArme];
			for (int i = 0; i < this->nrArme; i++)
				this->putereArme[i] = c.putereArme[i];
		}
	}

	~Caracter() 
	{
		if (this->putereArme != nullptr)
		{
			delete[] this->putereArme;
			this->putereArme = nullptr;
			this->nrArme = 0;
		}
	}

	//operator =
	Caracter& operator=(const Caracter& c)
	{
		if (this != &c) //punem doar daca avem alocat memorie din
		{
			//destructor
			//copy cons

			if (this->putereArme != nullptr)
			{
				delete[] this->putereArme;
				this->putereArme = nullptr;
				this->nrArme = 0;
			}

			this->denumire = c.denumire;
			this->nivelViata = c.nivelViata;
			if (c.nrArme > 0 && c.putereArme != nullptr)
			{
				this->nrArme = c.nrArme;
				this->putereArme = new double[this->nrArme];
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

	double& operator[](int _index)
	{
		if (_index >= 0 && _index < this->nrArme)
		{
			return this->putereArme[_index];
		}
		else
		{
			throw exception("Indexnul nu este valid");
		}
	}

	//op += a+=10 (int/double/etc) --adaugare intr un vector
	Caracter& operator+=(double _x)
	{
		if (_x > 0)
		{
			double* nou = new double[this->nrArme + 1];
			for (int i = 0; i < this->nrArme; i++)
				nou[i] = this->putereArme[i];
			nou[this->nrArme] = _x;

			delete[]this->putereArme;
			this->putereArme = nou;
			this->nrArme++;

			return *this;
		}
	}
	// operator ++(forma prefixata ++x)
	Caracter& operator++()
	{
		this->nivelViata *= 1.1;
		return *this;
	}
	
	//operator ++(forma postfixata x++)
	Caracter operator++(int)
	{
		Caracter copie = *this;
		this->operator++(); //++(*this);  sau this->nivelViata*=1.1
		return copie;
	}

	//cast explicit la double
	explicit operator double()
	{
		double total = 0;
		for (int i = 0; i < this->nrArme; i++)\
			total += this->putereArme[i];
		return total;
	}

	//operator + c3=c1+c2
	Caracter operator+(const Caracter& c)const //nu modific ob curent (*this)
	{
		Caracter rez = *this;
		int totalArme = rez.nrArme + c.nrArme;

		double* armeNoi = new double[totalArme];

		for (int i = 0; i < rez.nrArme; i++)
			armeNoi[i] = rez.putereArme[i];

		for (int i = 0; i < c.nrArme; i++)
			armeNoi[rez.nrArme + i] = c.putereArme[i];

		delete[]rez.putereArme;
		rez.putereArme = armeNoi;
		rez.nrArme = totalArme;

		return rez;
	}

	//operator += c3+=c1 echiv c3=c3+c1
	//Caracter operator+=(const Caracter& c) -VARIANTA CAND apelam operatorul +
	//{
	//	*this = *this + c;
	//	return *this;
	//}

	Caracter operator+=(const Caracter& c)
	{
		int totalArme = this->nrArme + c.nrArme;
		double* armeNoi = new double[totalArme];
		for (int i = 0; i < this->nrArme; i++)
			armeNoi[i] = this->putereArme[i];

		for (int i = 0; i < c.nrArme; i++)
			armeNoi[this->nrArme + 1] = c.putereArme[i];

		delete[] putereArme;
		this->putereArme = armeNoi;
		this->nrArme = totalArme;

		return *this;
	}

	//atac alt op
	void operator>>(Caracter& c)
	{
		if (this->nivelViata > Caracter::minViata)
		{
			//this->operator+=(c);
			(*this) += c;
			delete[] c.putereArme;
			c.putereArme = nullptr;
			c.nrArme = 0;
		}
	}

	//c3 = c1 + 10;
	Caracter operator+(double _x)const 
	{
			Caracter copie = *this;
			copie.nivelViata += _x;
			return copie;
		
	}

	//comparare TOT
	bool operator==(const Caracter& c) const 
	{
		if (denumire != c.denumire) return false;
		if (nivelViata != c.nivelViata) return false;
		if (nrArme != c.nrArme) return false;
		for (int i = 0; i < nrArme; i++) {
			if (putereArme[i] != c.putereArme[i])
				return false;
		}

		return true; 
	}

	bool operator!=(const Caracter& c) const {
		return !(*this == c);
	}
	
	//strict verificare existenta
	bool operator!()
	{
		return this->nivelViata == 0;
	}
	
	bool operator>(const Caracter& c)const 
	{
		return this->nivelViata > c.nivelViata;
	}

	int operator-(const Caracter& c) const 
	{
		return this->nivelViata - c.nivelViata;
	}

	friend ostream& operator<<(ostream& out, const Caracter& c);
	friend istream& operator>>(istream& is, Caracter& c);
};

int Caracter::minViata = 20;

ostream& operator<<(ostream& out, const Caracter& c)
{
	out << "\nId: " << c.id;
	out << "\nDenumire " << c.denumire;
	out << "\n Nivel viata: " << c.nivelViata;
	out << "\nNr arme: " << c.nrArme;
	out << "\nArme: ";
	for (int i = 0; i < c.nrArme; i++)
		out << c.putereArme[i] << " ";
	return out;
}
istream& operator>>(istream& is, Caracter& c)
{
	is >> c.denumire;
	is >> c.nivelViata;
	is >> c.nrArme;
	for (int i = 0; i < c.nrArme; i++)
		is >> c.putereArme[i];
	return is;

}


int main() {
	// Creare caractere cu constructori
	Caracter c1(12, "Erou");
	Caracter c2(14, "Zburatorul");
	cout << "\n--- Initial ---";
	cout << c1;
	cout << c2;

	// Adaugare arme folosind operator += double
	c1 += 10;
	c1 += 12;
	cout << "\n--- Dupa adaugare arme ---";
	cout << c1;

	// Incrementare viata ++ prefix
	cout << "\n----------- ++(pre) ----------";
	cout << "\nInainte: " << c1;
	c2 = ++c1; // operator++ prefix
	cout << "\nDupa ++c1, c2 = " << c2;
	cout << "\nc1 = " << c1;

	// Incrementare viata ++ postfix
	cout << "\n----------- ++(post) ----------";
	cout << "\nInainte: " << c1;
	c2 = c1++; // operator++ postfix
	cout << "\nDupa c1++, c2 = " << c2;
	cout << "\nc1 = " << c1;

	// Cast explicit la double -> suma puterilor armelor
	double totalArme = (double)c1; // explicit operator double()
	cout << endl << "Total arme c1: " << totalArme;

	// Concatenare arme cu operator +
	Caracter c3(15, "Combinat");
	c3 = c1 + c2; // operator+ intre caractere
	cout << "\n--- c3 = c1 + c2 ---";
	cout << c3;

	// Crestere viata cu operator + double
	c3 = c1 + 10; // operator+ cu double
	cout << "\n--- c3 = c1 + 10 ---";
	cout << c3;

	// c3 ataca c1 folosind operator >>
	c3 >> c1; // operator>> pentru transfer arme
	cout << "\n--- Dupa c3 >> c1 ---";
	cout << "\nc1 = " << c1;
	cout << "\nc3 = " << c3;

	// Verificare operator [] pentru acces si modificare arma
	cout << "\n--- Test operator[] ---";
	try {
		cout << "\nPrima arma c1: " << c1[0];
		c1[0] += 5; // modific arma
		cout << "\nPrima arma c1 dupa modificare: " << c1[0];
	}
	catch (exception& e) {
		cout << "\nEroare: " << e.what();
	}

	// Verificare operator ! pentru viata 0
	Caracter c4(16, "Mort");
	c4 = c4 + (-80); // scade viata pentru test
	if (!c4) // operator! verifica daca viata == 0
		cout << "\nCaracterul " << c4 << " are viata 0";

	// Comparare operator== si operator!=
	if (c1 == c2) // operator== compara toate atributele
		cout << "\nc1 si c2 sunt egale";
	else
		cout << "\nc1 si c2 sunt diferite";

	if (c1 != c2) // operator!= foloseste operator==
		cout << "\nc1 si c2 sunt diferite (verificat cu !=)";

	// Comparare operator>
	if (c1 > c2) // operator> compara nivelViata
		cout << "\nc1 are mai multa viata decat c2";

	// Operator- intre caractere (returneaza diferenta de viata)
	int diffViata = c1 - c2; // operator-
	cout << "\nDiferenta de viata c1 - c2: " << diffViata;

	// Operator- cu double (scade viata c1)
	Caracter c5 = c1 + 20; // operator+ cu double
	Caracter c6 = c5 - 10; // operator- cu double (daca se implementeaza similar)
	cout << "\nDupa c5 - 10, c6 = " << c6;

	return 0;
}
