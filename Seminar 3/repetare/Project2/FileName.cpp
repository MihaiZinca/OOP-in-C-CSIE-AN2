#define _CRT_SECRURE_NO_WARNINGS
#include<iostream>
using namespace std;
enum Culoare {
	ALB, NEGRU, ROSU, VERDE, DEFAULT
};

class Masina
{
	int codMasina;
	char* marca;
	Culoare culoare;
	double vitezaMaxima;
	int kilometriBord;
	char Initiala;

	int preturi[5];

	int* masini;
	int nrMasini;

	char NumeProducator[50];

	bool valoare;

	bool prezProducatori[5];

	bool* jante;
	int nrJante;


public:
	Masina()
	{
		this->codMasina = 0;
		this->marca = new char[strlen("Anonima") + 1];
		strcpy_s(this->marca, strlen("Anonima") + 1, "Anonima");
		this->culoare = Culoare::ALB;
		this->vitezaMaxima = 0;
		this->kilometriBord = 0;
		this->Initiala = 'A';

		for (int i = 0; i < 5; i++)
			this->preturi[i] = 0;

		this->nrMasini = 3;
		this->masini = new int[this->nrMasini];

		for (int i = 0; i < this->nrMasini; i++)
			this->masini[i] = 0;

		strcpy_s(this->NumeProducator, strlen("Anonim") + 1, "Anonim");
		this->valoare = false;
	
		for (int i = 0; i < 5; i++)
			this->prezProducatori[i] = false;

		this->nrJante = 0;
		this->jante = new bool[this->nrJante];
		for (int i = 0; i < this->nrJante; i++)
			this->jante[i] = false;
	}


	int getCodMasina()
	{
		return this->codMasina;
	}

	void setCodMasina(int _codmasina)
	{
		if (_codmasina > 0)this->codMasina = _codmasina;
	}

	char* getMarca()
	{
		char* copie = new char[strlen(this->marca) + 1];
		strcpy_s(copie, strlen(this->marca) + 1, this->marca);
		return copie;
	}
	void setMarca(const char* _marca)
	{
		if (_marca != nullptr)
		{
			if (this->marca != nullptr)delete[] this->marca;
			this->marca = new char[strlen(_marca) + 1];
			strcpy_s(this->marca, strlen(_marca) + 1, _marca);
		}
	}
	double getVitezaMaxima()
	{
		return this->vitezaMaxima;
	}
	void setVitezaMaxima(double _vitmax)
	{
		this->vitezaMaxima = _vitmax;
	}

	int getKmBord()
	{
		return this->kilometriBord;
	}
	void setKmBord(int _kmb)
	{
		this->kilometriBord = _kmb;
	}

	Culoare getCuloare()
	{
		return this->culoare;
	}
	void setCuloare(Culoare _cul)
	{
		this->culoare = _cul;
	}

	char getInitala()
	{
		return this->Initiala;
	}

	void setInitiala(char _init)
	{
		this->Initiala = _init;
	}


	void getPreturi(int _preturi[5])
	{
		for (int i = 0; i < 5; i++)
			_preturi[i] = this->preturi[i];
	}
	void setPreturi(const int _preturi[5])
	{
		for (int i = 0; i < 5; i++)
			this->preturi[i] = _preturi[i];
	}

	void getMasini(int*& _masini, int& _nr)
	{
		_nr = this->nrMasini;
		_masini = new int[_nr];
		for (int i = 0; i < this->nrMasini; i++)
			_masini[i] = this->masini[i];
	}
	void setMasini(const int* _masini, int _nr)
	{
		if (_masini == nullptr || _nr <= 0)
		{
			if (this->masini != nullptr) delete[] this->masini;

			this->nrMasini = 0;
		}
		if (this->masini != nullptr) delete[] this->masini;
		this->nrMasini = _nr;
		this->masini = new int[this->nrMasini];
		for (int i = 0; i < this->nrMasini; i++)
			this->masini[i] = _masini[i];
	}

	char* getNumeProducator()
	{
		char* copie = new char[strlen(this->NumeProducator) + 1];
		strcpy(copie, this->NumeProducator);
		return copie;
	}
	void setNumeProducator(const char* _numeProd)
	{
		if (strlen(_numeProd) >= 5) strcpy(this->NumeProducator, _numeProd);
	}

	bool getValoare()
	{
		return this->valoare;
	}
	void setValoare(bool _val)
	{
		this->valoare = _val;
	}

	void getPrezProducatori(bool _prez[5])
	{
		for (int i = 0; i < 5; i++)
			_prez[i] = this->prezProducatori[i];
	}

	void setPrezProducatori(const bool _prez[5])
	{
		for (int i = 0; i < 5; i++)
			this->prezProducatori[i] = _prez[i];
	}

	void getJante(bool*& _jante, int & _nr)
	{
		_nr = this->nrJante;
		_jante = new bool[_nr];
		for (int i = 0; i < _nr; i++)
			_jante[i] = this->jante[i];
	}
	void setJante(const bool* _jante, int _nr)
	{
		// dac? vectorul intern exist?, elibereaz? memoria veche
		if (_jante == nullptr || _nr <= 0)
		{
			// dac? vectorul intern exist?, elibereaz? memoria veche
			if (this->jante != nullptr) delete[] this->jante;
			this->nrJante = 0;
		}
		// dac? vectorul intern exist?, elibereaz? memoria veche
		if (this->jante != nullptr)delete[] this.jante;

		this->nrJante = _nr;
		this->jante = new bool[this->nrJante];
		for (int i = 0; i < this->nrJante; i++)
			this->jante[i] = _jante[i];
	}
};
