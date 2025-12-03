#include <iostream>
using namespace std;

//TO DO HOME1
//sa se modeleze clasa Masina(VIN, nr de inmatirculare+ EXTRA inca cv)
//vin ul este unic si constant(o primim ca parametrul DAR verificam ca este unica
//nr de inmatriculare(unic dar nu este constant)
//se poate schimba nr imatriculare cu un nr generat automat aleator sau pot cerere eu nr preferntial
//modalitate de verificare a disponibilitatii nr preferentiale


class Masina
{
	const string VIN; 
	string nrInmatriculare;
	string marca;

	static Masina* masiniExistente[100]; //am folosit static ca sa am un vector comun tuturo obiectelor
	static int nrMasini;

public:
	Masina(string _VIN, string _nrInmatriculare, string _marca) : VIN(_VIN), marca(_marca)
	{
		for (int i = 0; i < this->nrMasini; i++)
			if (masiniExistente[i]->VIN == _VIN)
				throw exception("\nVIN-ul deja exista");
		for (int i = 0; i < this->nrMasini; i++)
			if (masiniExistente[i]->nrInmatriculare == _nrInmatriculare)
				throw exception("\nNr inmatriculare deja exsita");

		this->nrInmatriculare = _nrInmatriculare;
		this->masiniExistente[this->nrMasini++] = this;

	}
	~Masina()
	{ }
	Masina(const Masina& m) : VIN(m.VIN), marca(m.marca)
	{
		
			for (int i = 0; i < this->nrMasini; i++)
				if (masiniExistente[i]->VIN ==m.VIN)
					throw exception("\nVIN-ul deja exista");
			for (int i = 0; i < this->nrMasini; i++)
				if (masiniExistente[i]->nrInmatriculare == m.nrInmatriculare)
					throw exception("\nNr inmatriculare deja exsita");
			this->nrInmatriculare = m.nrInmatriculare;
			this->masiniExistente[this->nrMasini++] = this;
	}
	string getVIN()
	{
		return this->VIN;
	}
	string getMarca()
	{
		return this->marca;
	}
	string getNrInmatriculare()
	{
		return this->nrInmatriculare;
	}

	void setNrInmatricularePreferential(string& nr)
	{
		for (int i = 0; i < this->nrMasini; i++)
			if (masiniExistente[i]->nrInmatriculare ==nr)
				throw exception("\nNr inmatriculare deja exsita");

		this->nrInmatriculare = nr;

	}

	void afisare()
	{
		cout << "\nVIN: " << VIN;
		cout << "\nNrInmatriculare: " << nrInmatriculare;
		cout<< "\nMarca: " << marca;
	}
	
};
Masina* Masina::masiniExistente[100];
int Masina::nrMasini = 0;

//TO DO HOME2
//sa se modifice implementarea curenta a.i id-ul generat sa respecte o regula, ex1:este format din cifre diferite, ex2:nr impare/prime
class Abonat {
	const int id; //este generat automat pt a oferi unicitate; ATRIBUTELE CONSTANTE SE INITIALIZEAZA DOAR LA CONSTRUCTORI
	int nrApeluri=0;
	string* apeluri=nullptr;//lista pers contactate;
	static int generatorId; //ma ajuta sa generez id uri dupa o regula

public:
	Abonat():id(Abonat::generatorId++) //lista de initializatori se apeleza constructori din alte clase si se initializeaza const, campurile statice se fac asa Abonat :: camp static
	{
	}

	Abonat(int _nrApeluri, string* _apeluri):id(Abonat::generatorId++)
	{
		if (_nrApeluri > 0 && _apeluri != nullptr)
		{
			this->nrApeluri = _nrApeluri;
			this->apeluri = new string[this->nrApeluri];
			for (int i = 0; i < this->nrApeluri; i++)
				this->apeluri[i] = _apeluri[i];
		}
	}

	Abonat(const Abonat& a):id(Abonat::generatorId++)
	{
		if (a.nrApeluri > 0 && a.apeluri != nullptr)
		{
			this->nrApeluri = a.nrApeluri;
			this->apeluri = new string[this->nrApeluri];
			for (int i = 0; i < this->nrApeluri; i++)
				this->apeluri[i] = a.apeluri[i];
		}
	}

	
	~Abonat()
	{
		if (this->apeluri != nullptr)
		{
			delete[] this->apeluri;
			this->apeluri = nullptr;
		}
	}

	Abonat& operator=(const Abonat& a)
	{
		if (this != &a)
		{
			//destructor
			//constructor de copiere
			if (this->apeluri != nullptr)
			{
				delete[] this->apeluri;
				this->apeluri = nullptr;
			}
			if (a.nrApeluri > 0 && a.apeluri != nullptr)
			{
				this->nrApeluri = a.nrApeluri;
				this->apeluri = new string[this->nrApeluri];
				for (int i = 0; i < this->nrApeluri; i++)
					this->apeluri[i] = a.apeluri[i];
			}
			else
			{
				this->apeluri = nullptr;
				this->nrApeluri = 0;
			}

		}
		return *this;
	}

	bool operator==(string _x)
	{
		for (int i = 0; i < this->nrApeluri; i++)
			if (this->apeluri[i] == _x) return true;
		
		return false;
	}

	friend bool operator<(int _x, const Abonat& a);//ca sa ne imprietenim cu functia glob.

	void afisare()
	{
		cout << "\nID: " << this->id;
		cout << "\nNr Apeluri: " << this->nrApeluri;
		cout << "\nLista de persoane contactate: ";
		for (int i = 0; i < this->nrApeluri; i++)
			cout << this->apeluri[i] << " ";
		cout << endl;
	}

};

int Abonat::generatorId = 1000;


bool operator<(int _x, const Abonat& a) 
{
	return _x < a.nrApeluri;  //adevarat sau fals
}

int main()
{
	Abonat a1;
	a1.afisare();
	
	string vector[] = { "Ana","Victor","Gigel" };
	Abonat a2(3, vector);
	a2.afisare();

	Abonat a3(a2); //apel constructor de copiere;
	Abonat a4 = a2; //apel constructor de copiere;

	a4.afisare();
	a3.afisare();
	
	a1 = a4;
	a1.afisare();

	if (a4 == "Victor")
	{
		cout << "\n a4 l- a contactat pe Victor";
	}
	else
		cout << "\n nu l-a contactat pe Victor";

	if (10 < a3)
	{
		cout << "\n a3 are nr apeluri > 10";
	}
	else
	{
		cout <<"\n a3 are nr apeluri <= 10";
	}

	try {
		
		Masina m1("200", "B-23-MAZ", "AUDI");
		Masina m2("201", "AG-99-LKA", "BMW");


		cout << "\nMasini initiale";
		m1.afisare();
		m2.afisare();

		string nrNou = "AG-12-AVC";
		m1.setNrInmatricularePreferential(nrNou);

		cout << "\nDupa schimbarea nr preferential";
		m1.afisare();


	}
	catch (exception& ex)
	{
		cout << "\nEroare: " << ex.what();
	}

	

	//to do home operator ++ versiune otpimizata
	return 0;
}