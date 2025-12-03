#include <iostream>
using namespace std;


//relatia de compunere -> has a(1-M) (1-1) 
//try catch

//next time(s9)
//terminam toti op de supraincarcat
//comparatie done
//= done
//<< done
//>> done
//[] done


class Produs {
	string denumire = "";
	double pret = 0;

public:
	//de ce este nevoie de un constructor default? ->pt ca obiectele sa poata fi create, chiar daca nu dam parametri
	Produs(){}
	Produs(string _denumire, double _pret)
	{
		this->denumire = _denumire;
		this->pret = _pret;
	}

	//constructor copiere copiaza octet cu octet
	Produs(const Produs& p)
	{
		this->denumire = p.denumire;
		this->pret = p.pret;
	}
	
	Produs& operator=(const Produs& p)
	{
		if (this != &p)
		{
			this->denumire = p.denumire;
			this->pret = p.pret;
		}
		return *this;
	}

	//meth de afisare ->suprarincarcare operatorului <<

	//permit obiectele de tipul Produs care sunt utilizate in functia mentionata 
	//sa aiba acces si la zona privata a clasei Produs
	friend ostream& operator<<(ostream& out, const Produs& p);
};


//trasnfer prin referinta
//ca sa modifici obiectul respectiv
//caz1. ca sa nu modifici obiectul respectiv(si aici nu putem si const)
//caz2. ca sa nu mai facem acea copie pe care ne o realizeaza transferul
//prin valoare(dar aici punem const,pt ca intentia nu este de a modifica obiectul)

ostream& operator<<(ostream& out, const Produs& p)//const doar pt optimizare rol de a ocloi copierea
{
	out << "\nDenumire: " << p.denumire;
	out << "\npret: " << p.pret;
	return out;
}

//Versiuni diferite de colectii de obiecte/referinte de tip Produs
//obiect vs referinta la obiect
//deep copy vs shallow copy


class WishList2 {
	Produs lista[100];//vector alocat static de obj de tip Produs
	int nrProduse=0;
	double buget = 0;

public:

	WishList2() {}
	WishList2(Produs* _lista, int _nrProduse, double _buget)
	{
		if (_lista != nullptr && _nrProduse > 0)
		{
			this->nrProduse = _nrProduse;
			for (int i = 0; i < this->nrProduse; i++)
				this->lista[i] = _lista[i];
		}
		this->buget = _buget;
	}

	WishList2(const WishList2& w)
	{
		if (w.lista != nullptr && w.nrProduse > 0)
		{
			this->nrProduse = w.nrProduse;
			for (int i = 0; i < this->nrProduse; i++)
				this->lista[i] = w.lista[i];
		}
		this->buget = w.buget;
	}

	WishList2& operator=(const WishList2& w)
	{
		if (this != &w)
		{
			//desturctor
			//copy constr + else
			if (w.lista != nullptr && w.nrProduse > 0)
			{
				this->nrProduse = w.nrProduse;
				for (int i = 0; i < this->nrProduse; i++)
					this->lista[i] = w.lista[i];
			}
			else
			{
				this->nrProduse = 0;
			}
			this->buget = w.buget;
		}
		return *this;
	}

	~WishList2(){ }

	friend ostream& operator<<(ostream& out, const WishList2& w);
	friend istream& operator>>(istream& is, const WishList2& w);
};

ostream& operator<<(ostream& out, const WishList2& w)
{
	out << "\nWishList2: ";
	out << "\nBuget: " << w.buget;
	out << "\nNr produse: " << w.nrProduse;
	for (int i = 0; i < w.nrProduse; i++)
		out << w.lista[i];
	return out;
}

istream& operator>>(istream& is, const WishList2& w)
{
	cout << "Buget: ";
	is >> w.buget;
	cout << "Nr produse: ";
	is >> w.nrProduse;
	for (int i = 0; i < w.nrProduse; i++)
		is >> w.lista[i];
	return is;
}

class WishList3 {
	Produs* lista[100];//vector alocat static de Produs* (referinte la Produs)
	int nrProduse=0;
	double buget=0;

public:
	WishList3(){ }
	WishList3(Produs** _lista, int _nrProduse, double _buget)
	{
		if (_nrProduse > 0 && _lista != nullptr)
		{
			this->nrProduse = _nrProduse;
			for (int i = 0; i < _nrProduse; i++)
				this->lista[i] = _lista[i];//aici se vede ca este shallow
		}
		this->buget = _buget;
	}
	~WishList3(){ }

	WishList3(const WishList3& w)
	{
		if (w.nrProduse > 0 && w.lista != nullptr)
		{
			this->nrProduse = w.nrProduse;
			for (int i = 0; i < w.nrProduse; i++)
				this->lista[i] = w.lista[i];//aici se vede ca este shallow
		}
		this->buget = w.buget;
	}

	WishList3& operator=(const WishList3& w)
	{
		if (this != &w)
		{
			if (w.nrProduse > 0 && w.lista != nullptr)
			{
				this->nrProduse = w.nrProduse;
				for (int i = 0; i < w.nrProduse; i++)
					this->lista[i] = w.lista[i];
			}
			this->buget = w.buget;
		}
		
		return *this;
	}

	friend ostream& operator<<(ostream& out, const WishList3& w);
	friend istream& operator>>(istream& is, const WishList3& w);
};

ostream& operator<<(ostream& out, const WishList3& w)
{
	out << "\nWishlist3: buget=" << w.buget << ", nr produse=" << w.nrProduse;
	for (int i = 0; i < w.nrProduse; i++)
		out << *w.lista[i];
	return out;
}
istream& operator>>(istream& is, const WishList3& w)
{
	cout << "Bugetul: ";
	is >> w.buget;

	cout << "Nr produse: ";
	is >> w.nrProduse;

	for (int i = 0; i < i < w.nrProduse; i++)
		is >> *w.lista[i];
	return is;
}

class WishList4 {
	Produs** lista=nullptr;//vector alocat dinamic de Produs* (referinte la Produs)
	int nrProduse=0;
	double buget=0;

public:
	WishList4(){ }
	WishList4(Produs** _lista, int _nrProduse, double _buget)
	{
		if (_nrProduse > 0 && _lista != nullptr)
		{
			this->nrProduse = _nrProduse;
			this->lista = new Produs * [this->nrProduse];
			for (int i = 0; i < _nrProduse; i++)
				this->lista[i] = _lista[i];//aici se vede ca este shallow
		}
		this->buget = _buget;
	}

	WishList4(const WishList4& w)
	{
		if (w.nrProduse > 0 && w.lista != nullptr)
		{
			this->nrProduse = w.nrProduse;
			this->lista = new Produs * [this->nrProduse];
			for (int i = 0; i < w.nrProduse; i++)
				this->lista[i] = w.lista[i];//aici se vede ca este shallow
		}
		this->buget = w.buget;
	}
	~WishList4()
	{
		if (this->lista != nullptr)
		{
			delete[] this->lista;
			this->lista = nullptr;
		}

	}
	WishList4& operator=(const WishList4& w)
	{
		if (this != &w)
		{
			if (this->lista != nullptr)
			{
				delete[] this->lista;
				this->lista = nullptr;
			}

			if (w.nrProduse > 0 && w.lista != nullptr)
			{
				this->nrProduse = w.nrProduse;
				this->lista = new Produs * [this->nrProduse];
				for (int i = 0; i < w.nrProduse; i++)
					this->lista[i] = w.lista[i];//aici se vede ca este shallow
			}
			else
			{
				this->lista = nullptr;
			}
			this->buget = w.buget;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const WishList4& w); //folosesc const ca sa nu il modificam pe w rol de a ocoli copierea
};

ostream& operator<<(ostream& out, const WishList4& w)
{ 
	out << "\nWishlist4: buget=" << w.buget << ", nr produse=" << w.nrProduse;
	for (int i = 0; i < w.nrProduse; i++)
		out << *w.lista[i];
	return out;
}


// implementarea este de tip deepcopy(adica primim niste referinte, dar ne alocam propria noastra zona de memorie pentru fiecare referinta, iar noi la nivel de obj wishlist, stocam o lista / vector de astfel de referinte
	class Wishlist4_1
{
	Produs** lista = nullptr; //vector dinamic de Produs* (referinte catre produse)
	int nrProduse = 0;
	double buget = 0;

public:
	Wishlist4_1() {}

	//constructor cu toti param
	Wishlist4_1(Produs** _lista, int _nrProduse, double _buget)
	{
		if (_nrProduse > 0 && _lista != nullptr)
		{
			this->nrProduse = _nrProduse;
			this->lista = new Produs * [this->nrProduse];
			for (int i = 0; i < _nrProduse; i++)
				this->lista[i] = new Produs(*_lista[i]);//apelez constructor de copiere -deepcopy!
		}
		this->buget = _buget;
	}

	Wishlist4_1(const Wishlist4_1& w)
	{
		if (w.nrProduse > 0 && w.lista != nullptr)
		{
			this->nrProduse = w.nrProduse;
			this->lista = new Produs * [this->nrProduse];
			for (int i = 0; i < w.nrProduse; i++)
				this->lista[i] = new Produs(*w.lista[i]);
		}
		this->buget = w.buget;
	}

	Wishlist4_1& operator=(const Wishlist4_1& w) {
		if (this != &w) {
			if (this->lista != nullptr) {
				for (int i = 0; i < this->nrProduse; i++)
					delete this->lista[i];
				delete[] this->lista;
				this->lista = nullptr;
			}
			if (w.nrProduse > 0 && w.lista != nullptr)
			{
				this->nrProduse = w.nrProduse;
				this->lista = new Produs * [this->nrProduse];
				for (int i = 0; i < w.nrProduse; i++)
					this->lista[i] = new Produs(*w.lista[i]);
			}
			this->buget = w.buget;
		}
		return *this;
	}

	~Wishlist4_1() {
		if (this->lista != nullptr) {
			for (int i = 0; i < this->nrProduse; i++)
				delete this->lista[i];
			delete[] this->lista;
			this->lista = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const Wishlist4_1& w);
};

ostream& operator<<(ostream& out, const Wishlist4_1& w) {
	out << "\nWishlist4: buget=" << w.buget << ", nr produse=" << w.nrProduse;
	for (int i = 0; i < w.nrProduse; i++)
		out << *w.lista[i];
	return out;
}

//relatie de tip 1-1
class WishList5 {
	Produs theCadou; //un singur Produs
	double buget;
	
public:
	WishList5() { }
	WishList5(Produs& _theCadou, double _buget ): theCadou(_theCadou), buget(_buget)
	{ }

	WishList5(const WishList5& w) :theCadou(w.theCadou), buget(w.buget)
	{ }

	WishList5& operator=(const WishList5& w)
	{
		if (this != &w)
		{
			this->theCadou = w.theCadou;   
			this->buget = w.buget;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const WishList5& w);

};

ostream& operator<<(ostream& out, const WishList5& w)
{
	out << "\nWishlist5:";
	out << "\nBuget: " << w.buget;
	out << "\nCadou: " << w.theCadou;  
	return out;
}

//relatie de tip 1-1
//implementarea curenta este de tipul shallow copy
class WishList6 {
	Produs* theCadou=nullptr; //un singur pointer catre 1 Produs
	double buget = 0;

public:

	WishList6() {}
	WishList6(Produs* _theCadou, double _buget)
	{
		this->theCadou = _theCadou;
		this->buget = _buget;
	}
	
	WishList6(const WishList6& w)
	{
		this->theCadou = w.theCadou;
		this->buget = w.buget;
	}

	WishList6& operator=(const WishList6& w)
	{
		if (this != &w)
		{
			this->theCadou = w.theCadou;
			this->buget = w.buget;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const WishList6& w);
};

ostream& operator<<(ostream & out, const WishList6 & w)
{
	out << "\nWishList6 :";
	out << "\nBuget " << w.buget;
	out << "\nCadou " << *w.theCadou; 
	
	return out;
}

//implementarea curenta este de tip deep copy
class WishList6_1 {
	Produs* theCadou = nullptr; //un singur pointer catre 1 Produs
	double buget = 0;

public:

	WishList6_1() {}
	WishList6_1(Produs* _theCadou, double _buget)
	{
		if (_theCadou != nullptr)
		{
			this->theCadou = new Produs(*_theCadou); // copie a obiectului
		}
		this->buget = _buget;
	}

	WishList6_1(const WishList6_1& w)
	{
		if (w.theCadou != nullptr)
		{
			this->theCadou = new Produs(*w.theCadou); // copie a obiectului
		}
		this->buget = w.buget;
	}

	~WishList6_1()
	{
		if (this->theCadou != nullptr)
		{
			delete[]this->theCadou;
			this->theCadou = nullptr;
		}
	}

	WishList6_1& operator=(const WishList6_1& w)
	{
		if (this != &w)
		{
			if (this->theCadou != nullptr)
			{
				delete[]this->theCadou;
				this->theCadou = nullptr;
			}
			if (w.theCadou != nullptr)
			{
				this->theCadou = new Produs(*w.theCadou); // copie a obiectului
			}
			else
			{
				this->theCadou = nullptr;
			}
			this->buget = w.buget;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const WishList6_1& w);
};

ostream& operator<<(ostream& out, const WishList6_1& w)
{
	out << "\nWishList6_1 :";
	out << "\nBuget " << w.buget;
	out << "\nCadou " << *w.theCadou;

	return out;
}


//pentru fiecare prieten
//retin o colectie de produse de referinte la produse 
//pe care vreau sa le ofer cadou

// deci practic o sa am 
/*lista =
[
	[Produs*, Produs*, Produs*],   // prietenul 0
	[Produs*, Produs*],             // prietenul 1
	[Produs*]                        // prietenul 2
]
*/

class WishList7
{
	Produs*** lista=nullptr;
	int nrPrieteni=0;
	int* nrProduse=nullptr; //nr produse per fiecare prieten
	double buget=0;

public:
	WishList7(){ }
	WishList7(Produs*** _lista, int _nrPrieteni, int* _nrProduse, double _buget)
	{
		if (_lista != nullptr && _nrPrieteni > 0 && _nrProduse != nullptr)
		{
			this->nrPrieteni = _nrPrieteni;

			this->nrProduse = new int[this->nrPrieteni];
			this->lista = new Produs **[this->nrPrieteni];

			for (int i = 0; i < this->nrPrieteni; i++)
			{
				this->nrProduse[i] = _nrProduse[i];

				if (this->nrProduse[i] > 0 && _lista[i] != nullptr)
				{
					this->lista[i] = new Produs *[this->nrProduse[i]];

					for (int j = 0; j < this->nrProduse[i]; j++)
					{
						if (_lista[i][j] != nullptr)
							this->lista[i][j] = new Produs(*_lista[i][j]); // deep copy
						else
							this->lista[i][j] = nullptr;
					}
				}
				else
				{
					this->lista[i] = nullptr;
				}
			}
		}
		

		this->buget = _buget;
	}

	WishList7(const WishList7& w)
	{
		if (w.lista != nullptr && w.nrPrieteni > 0 && w.nrProduse != nullptr)
		{
			this->nrPrieteni = w.nrPrieteni;

			this->nrProduse = new int[this->nrPrieteni];
			this->lista = new Produs * *[this->nrPrieteni];

			for (int i = 0; i < this->nrPrieteni; i++)
			{
				this->nrProduse[i] = w.nrProduse[i];

				if (this->nrProduse[i] > 0 && w.lista[i] != nullptr)
				{
					this->lista[i] = new Produs * [this->nrProduse[i]];

					for (int j = 0; j < this->nrProduse[i]; j++)
					{
						if (w.lista[i][j] != nullptr)
							this->lista[i][j] = new Produs(*w.lista[i][j]); // deep copy
						else
							this->lista[i][j] = nullptr;
					}
				}
				else
				{
					this->lista[i] = nullptr;
				}
			}
		}
		else
		{
			this->nrPrieteni = 0;
			this->lista = nullptr;
			this->nrProduse = nullptr;
		}

		this->buget = w.buget;
	}

	WishList7& operator=(const WishList7& w)
	{
		if (this != &w)
		{
			//destructor 
			if (this->lista != nullptr)
			{
				for (int i = 0; i < this->nrPrieteni; i++)
				{
					if (this->lista[i] != nullptr)
					{
						for (int j = 0; j < this->nrProduse[i]; j++)
						{
							delete this->lista[i][j];
						}
						delete[] this->lista[i];
					}
				}
				delete[] this->lista;
			}

			delete[]this->nrProduse;

			if (w.lista != nullptr && w.nrPrieteni > 0 && w.nrProduse != nullptr)
			{
				this->nrPrieteni = w.nrPrieteni;

				this->nrProduse = new int[this->nrPrieteni];
				this->lista = new Produs * *[this->nrPrieteni];

				for (int i = 0; i < this->nrPrieteni; i++)
				{
					this->nrProduse[i] = w.nrProduse[i];

					if (this->nrProduse[i] > 0 && w.lista[i] != nullptr)
					{
						this->lista[i] = new Produs * [this->nrProduse[i]];

						for (int j = 0; j < this->nrProduse[i]; j++)
						{
							if (w.lista[i][j] != nullptr)
								this->lista[i][j] = new Produs(*w.lista[i][j]); // deep copy
							else
								this->lista[i][j] = nullptr;
						}
					}
					else
					{
						this->lista[i] = nullptr;
					}
				}
			}
			else
			{
				this->nrPrieteni = 0;
				this->lista = nullptr;
				this->nrProduse = nullptr;
			}

			this->buget = w.buget;

		}
		return *this;
	}

	~WishList7()
	{
		if (this->lista != nullptr)
		{
			for (int i = 0; i < this->nrPrieteni; i++)
			{
				if (this->lista[i] != nullptr)
				{
					for (int j = 0; j < this->nrProduse[i]; j++)
					{
						delete this->lista[i][j]; 
					}
					delete[] this->lista[i]; 
				}
			}
			delete[] this->lista; 
		}

		delete[]this->nrProduse; 
	}

	friend ostream& operator<<(ostream& out, const WishList7& w);


};
 ostream& operator<<(ostream& out, const WishList7& w)
{
	out << "\nWishList7:";
	out << "\nBuget: " << w.buget;
	out << "\nNr prieteni: " << w.nrPrieteni;

	for (int i = 0; i < w.nrPrieteni; i++)
	{
		out << "\nPrieten " << i << " are " << w.nrProduse[i] << " produse:";
		for (int j = 0; j < w.nrProduse[i]; j++)
		{
			out << "\nProdus[" << j << "]: ";
			if (w.lista[i][j] != nullptr)
				out << *w.lista[i][j];
			else
				out << "NULL";
		}
	}
	return out;
}



 


//contina o colectie de obiecte/referinte de tip Produs
class WishList {
	Produs* lista; //->vector alocat dinamic de obiecte de tip produs
	int nrProduse=0;
	double buget=0;

public:
	WishList(){ }
	WishList(Produs* _lista, int _nrProduse, double _buget)
	{
		if (_nrProduse > 0 && _lista != nullptr)
		{
			this->nrProduse = _nrProduse;
			this->lista = new Produs[this->nrProduse];//ce se apeleaza? (construct fara param de nrProduse ori)
			for (int i = 0; i < this->nrProduse; i++)
				this->lista[i] = _lista[i]; //ce se apeleaza?(operator =)
		}
		this->buget = _buget;
	}
	friend ostream& operator<<(ostream& out, const WishList& w);


	//!!!NU FACEM RETURN PRIN REFERINTA LA TIPURI DE DATA DE BAZA(INT/FLOAT/DOUBLE)!!! DE CE????? ->dangling 
	//operator[] cu rol de consultare va intoarce mereu un obiect si nu referinta sa
	//daca se doreste si cu rol de modificare atunci va intoarce o referinta
	


	//op binar(WishList[] int)
	//obligatoriu se implementeaza in clasa printr o functie membra

	Produs& operator[](int _index) {
		if (_index >= 0 && _index < this->nrProduse)
			return this->lista[_index];
		else
		{
			//nu punem cout!
			throw exception("Indexul nu este valid");//arunca un nou obiect
			//de tipul clasei exception care este construit pe baza constr cu parm care primeste un string cu rol de mesaj
		}
	}

	~WishList() {
		if (this->lista != nullptr) {
			delete[]this->lista;
			this->lista = nullptr;
		}
	}

	WishList(const WishList& w) //constructor copiere
	{
		if (w.nrProduse > 0 && w.lista != nullptr)
		{
			this->nrProduse = w.nrProduse;
			this->lista = new Produs[this->nrProduse];//ce se apeleaza? (construct fara param de nrProduse ori)
			for (int i = 0; i < this->nrProduse; i++)
				this->lista[i] = w.lista[i]; //ce se apeleaza?(operator =)
		}
		this->buget = w.buget;
	}

	WishList& operator=(const WishList& w)
	{
		if (this != &w)
		{
			//destructor 
			if (this->lista != nullptr) {
				delete[]this->lista;
				this->lista = nullptr;
			}
			//constructor de copiere
			if (w.nrProduse > 0 && w.lista != nullptr)
			{
				this->nrProduse = w.nrProduse;
				this->lista = new Produs[this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
					this->lista[i] = w.lista[i]; 
			}
			else
			{
				//situatia in care this avea produse dar w nu are
				this->nrProduse = 0;
				this->lista = nullptr;
			}
			this->buget = w.buget;
		}
		return *this;
	}


};

ostream& operator<<(ostream& out, const WishList& w)//const doar pt optimizare rol de a ocloi copierea
{
	out << "\nNrProduse: " << w.nrProduse;
	out << "\nProduse: ";
	for (int i = 0; i < w.nrProduse; i++)
		out << w.lista[i];
	out << "\nBuget: " << w.buget;
	return out;
}



int main()
{
	Produs p1("Stilou", 500);
	//p1.afiare()
	cout << p1; //ostream << Produs
	Produs p2("Pix", 200);
	Produs p3("Ciocolata", 150);
	Produs v[] = { p1,p2,p3 };//ce se apeleza? ->constructor copiere
	WishList w(v, 3, 1200);
	cout << w;
	WishList w2 = w;
	cout << w2;
	cout << "\n---------operator [] ---------";
	Produs p4;

	p4 = w[1];//operatorul index[] extrage obiectul de pe index ul primit ca parametru

	//op binar(WishList[] int)
	//obligatoriu se implementeaza in clasa printr o functie membra

	try {
		w[-1] = p3;//daca implementez operatorul si cu rol de modificare (adica intoarce o referinta si modifica in lista de obiecte/produse ale lui WishList w)
		cout << w;
	}

	catch (exception& ex) 
	{
		//to do in situatia in care metoda a fost apelata cu input neconform
		cout << ex.what();//echivalent cu un getMesaj()

	}


	//to do home DE REMODELAT MECANISMUL DE APEL OPERATOR INDEX[]
	//UTILIZATORUL REINTRODUCERE INDEXUL PANA CE ACESTA ESTE VALID	

	Produs p("Acadele", 900);
	cout << "\n---------operator [] REMODELAT ---------";
	bool indexV = false;
	int index;

	while (!indexV)
	{
		cout << "\nIntroducere index: ";
		cin >> index;

		try
		{
			w[index] = p;
			indexV = true;
		
		}
		catch (exception& ex)
		{
			cout << "\nEroare: " << ex.what();
			cout << "\nReluam";
		}
	}
	cout << "\nWishlist dupa modificare:";
	cout << w;

	return 0;
}