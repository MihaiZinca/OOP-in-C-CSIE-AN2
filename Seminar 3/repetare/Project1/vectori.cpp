#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

enum Burse {
	MERIT, SOCIALA, SPECIALA
};
class Note
{
	char litera;

	int noteStatice[5];

	int* noteDinamice;
	int nrNote;

	char numeStatic[30];

	char* numeDinamic;

	bool prezenteStatice[5];

	bool* prezenteDinamice;
	int nrPrezente;

	Burse bursaStatica[5];

	Burse* bursaDinamica;
	int nrBurse;
	
public:
	Note()
	{
		this->litera = 'A';
		for (int i = 0; i < 5; i++)this->noteStatice[i] = 0;

		this->nrNote = 3;
		this->noteDinamice = new int[this->nrNote];

		for (int i = 0; i < this->nrNote; i++)
			this->noteDinamice[i] = 0;

		strcpy_s(this->numeStatic, sizeof(this->numeStatic), "Anonim");

		this->numeDinamic = new char[strlen("Anonim") + 1];
		strcpy_s(this->numeDinamic, strlen("Anonim") + 1, "Anonim");

		for (int i = 0; i < 5; i++)this->prezenteStatice[i] = false;

		this->nrPrezente = 3;
		this->prezenteDinamice = new bool[this->nrPrezente];
		for (int i = 0; i < this->nrPrezente; i++)this->prezenteDinamice[i] = false;
	}

	// un carcacter
	char getLitera()
	{
		return this->litera;
	}
	void setLitera(char _litera)
	{
		this->litera = _litera;
	}

	// vector numeric alocat static
	void getNoteStatice(int _note[5])
	{
		for (int i = 0; i < 5; i++)
			_note[i] = this->noteStatice[i];
	}

	void setNoteStatice(const int _note[5])
	{
		for (int i = 0; i < 5; i++)
			this->noteStatice[i] = _note[i];
	}

	void afisareNoteStatice()
	{
		cout << "Note Statice: ";
		for (int i = 0; i < 5; i++)
			cout << this->noteStatice[i] << " ";
		cout << "\n";
	}

	// vector numeric alocat dinamic
	void getNoteDinamice(int*& _note, int & _nr)
	{
		_nr = this->nrNote;
		_note = new int[_nr];
		for (int i = 0; i < this->nrNote; i++)
			_note[i] = this->noteDinamice[i];
	}

	void setNoteDinamice(const int* _note, int _nr)
	{
		if (_note == nullptr || _nr <= 0)
		{
			if (this->noteDinamice != nullptr)
			{
				delete[] this->noteDinamice;

			}

			this->nrNote = 0;
		}
		if (this->noteDinamice != nullptr) delete[] this->noteDinamice;

		this->nrNote = _nr;
		this->noteDinamice = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++)
			this->noteDinamice[i] = _note[i];
	}

	void afisareNoteDinamice()
	{
		if (this->noteDinamice == nullptr || this->nrNote <= 0)
		{
			cout << "nu exista note dinamice";

		}
		cout << "Note dinamice: ";
		for (int i = 0; i < this->nrNote; i++)
			cout << this->noteDinamice[i] << " ";
		cout << "\n";
	}

	//sir de caractere alocat static
	char* getNumeStatic()
	{
		char* copie = new char[strlen(this->numeStatic) + 1];
		strcpy(copie, this->numeStatic);
		return copie;
	}
	void setNumeStatic(const char* _nume)
	{
		if (strlen(_nume) >= 5)strcpy(this->numeStatic, _nume);
	}

	void afisareNumeStatic()
	{
		cout << "Nume static: " << this->numeStatic << endl;
	}


	//sir de caractere alocat dinamic
	char* getNumeDinamic()
	{
		char* co = new char[strlen(this->numeDinamic) + 1];
		strcpy_s(co, strlen(this->numeDinamic) + 1, this->numeDinamic);
		return co;
	}
	
	void setNumeDinamic(const char* _name)
	{
		if (_name != nullptr)
		{
			if (this->numeDinamic != nullptr) delete[] this->numeDinamic;
		}
		this->numeDinamic = new char[strlen(_name) + 1];
		strcpy_s(this->numeDinamic, strlen(_name) + 1, _name);
	}

	void afisareNumeDinamic()
	{
		if (this->numeDinamic != nullptr)
		{
			cout << "Nume dinamic: " << this->numeDinamic << endl;
		}
		else
		{
			cout << "Nume Dinamic:-";
		}
	}

	// vector de bool static
	void getPrezenteStatice(bool _prezente[5])
	{
		for (int i = 0; i < 5; i++)
			_prezente[i] = this->prezenteStatice[i];
	}
	void setPrezenteStatice(const bool _prezente[5])
	{
		for (int i = 0; i < 5; i++)
			this->prezenteStatice[i] = _prezente[i];
	}
	
	void afisarePrezenteStatice()
	{
		cout << "Prezente Statice:";
		for (int i = 0; i < 5; i++)
			cout << this->prezenteStatice[i] << " ";
		cout << "\n";
	}


	// vector de bool dinamic
	void getPrezenteDinamice(bool*& _prezente, int& _nr)
	{
		_nr = this->nrPrezente;
		_prezente = new bool[_nr];
		for (int i = 0; i < _nr; i++)
			_prezente[i] = this->prezenteDinamice[i];
	}
	
	void setPrezenteDinamice(const bool* _prezente, int _nr)
	{
		if (_prezente == nullptr || _nr <= 0)
		{
			if (this->prezenteDinamice != nullptr)
				delete[] this->prezenteDinamice;
			this->nrPrezente = 0;
		}
		if (this->prezenteDinamice != nullptr) delete[] this->prezenteDinamice;
		this->nrPrezente = _nr;
		this->prezenteDinamice = new bool[this->nrPrezente];
		for (int i = 0; i < this->nrPrezente; i++)
			this->prezenteDinamice[i] = _prezente[i];

	}
	void afisarePrezenteDinamice()
	{
		if (this->prezenteDinamice != nullptr && this->nrPrezente > 0)
		{
			cout << "Prezente Dinamice: ";
			for (int i = 0; i < this->nrPrezente; i++)
				cout << this->prezenteDinamice[i] << " ";
			cout << "\n";
		}
		else
		{
			cout << "Prezente Dinamice - ";
		}
	}

	//Vector de enum static
	void getBurseStatice(Burse _burse[5])
	{
		for (int i = 0; i < 5; i++)
			_burse[i] = this->bursaStatica[i];
	}
	void setBurseStatice(const Burse _burse[5])
	{
		for (int i = 0; i < 5; i++)
			this->bursaStatica[i] = _burse[i];
	}

	void afisareBurseStatice()
	{
		cout << "Burse statice: ";
		for (int i = 0; i < 5; i++)
			cout << this->bursaStatica[i] << " ";
		cout << "\n";
	}

	//Vector de enum dinamic

	void getBurseDinamic(Burse*& _burse, int& _nr)
	{
		_nr = this->nrBurse;
		_burse = new Burse[_nr];
		for (int i = 0; i < _nr; i++)
			_burse[i] = this->bursaDinamica[i];
	}

	void setBurseDinamic(const Burse* _burse, int _nr)
	{
		if (_burse == nullptr || _nr <= 0)
		{
			if (this->bursaDinamica != nullptr)delete[] this->bursaDinamica;
			this->nrBurse = 0;
		}
		if (this->bursaDinamica != nullptr) delete[] this->bursaDinamica;
		this->nrBurse = _nr;
		this->bursaDinamica = new Burse[this->nrBurse];
		for (int i = 0; i < _nr; i++)
			this->bursaDinamica[i] = _burse[i];
	}
	
	void afisareBurseDinamice()
	{
		if (this->bursaDinamica != nullptr && this->nrBurse > 0)
		{
			cout << "Bursa dinamica: ";
			for (int i = 0; i < this->nrBurse; i++)
				cout << this->bursaDinamica[i] << " ";
			cout << "\n";
		}
		else cout << "Bursa dinamica -";
	}
};

int main()
{
	Note n;

	//afisare char litera
	cout << "\nLitera este: " << n.getLitera();
	n.setLitera('B');
	cout << "\n Litera dupa set este: " << n.getLitera();
	cout << endl;

	// VECTOR STATIC
	int note1[5] = { 10, 9, 9, 7, 10 };
	n.setNoteStatice(note1);
	n.afisareNoteStatice();

	// VECTOR DINAMIC
	int note2[] = { 6, 8, 9, 10 };
	n.setNoteDinamice(note2, 4);
	n.afisareNoteDinamice();

	// SIR STATIC
	n.setNumeStatic("Popescu Ion");
	n.afisareNumeStatic();

	// SIR DINAMIC
	n.setNumeDinamic("Ionescu Maria");
	n.afisareNumeDinamic();

	// Vector static bool
	bool prezenteStatice[5] = { true, false, true, true, false };
	n.setPrezenteStatice(prezenteStatice);
	n.afisarePrezenteStatice();

	// Vector dinamic bool
	bool prezenteDinamice[] = { false, true, true, false };
	n.setPrezenteDinamice(prezenteDinamice, 4);
	n.afisarePrezenteDinamice();

	// Vector static
	Burse burseStatice[5] = { MERIT, SOCIALA, SPECIALA, MERIT, SOCIALA };
	n.setBurseStatice(burseStatice);
	n.afisareBurseStatice();

	// Vector dinamic
	Burse burseDinamice[] = { SOCIALA, MERIT, SPECIALA };
	n.setBurseDinamic(burseDinamice, 3);
	n.afisareBurseDinamice();
	
	return 0;
}