#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;
enum Culoare {
	ALB, NEGRU, ALBASTRU
};
class Masini
{
	char* marca;
	char modele[50];
	char initiala;
	int nrModele;
	float pretPornire;
	Culoare culoare;
	bool stock;
	
	int stocStatic[10];

	int* stocDinamic;
	int nrMasini;

	bool testDrive[5];

	bool* prezentare;
	int nrPrezentare;

	Culoare modelCulaore[5];

	Culoare* culdin;
	int nrculori;

public:
	Masini()
	{
		this->marca = new char[strlen("Anonim") + 1];
		strcpy_s(this->marca, strlen("Anonim") + 1, "Anonim");

		strcpy_s(this->modele, sizeof(this->modele), "Anonim");

		this->initiala = 'Am';
		this->nrModele = 0;
		this->culoare = Culoare::NEGRU;
		this->pretPornire = 0.0;
		this->stock = false;

		for (int i = 0; i < 10; i++)this->stocStatic[i] = 0;

		this->nrMasini = 3;
		this->stocDinamic = new int[this->nrMasini];
		for (int i = 0; i < this->nrMasini; i++)
			this->stocDinamic[i] = 0;

		for (int i = 0; i < 5; i++)this->testDrive[i] = false;

		this->nrPrezentare = 5;
		this->prezentare = new bool[this->nrPrezentare];
		for (int i = 0; i < this->nrPrezentare; i++)
			this->prezentare[i] = true;

		for (int i = 0; i < 5; i++)
			this->modelCulaore[i] = Culoare::ALBASTRU;
		this->nrculori = 3;
		this->culdin = new Culoare[this->nrculori];
		for (int i = 0; i < this->nrculori; i++)
			this->culdin[i] = Culoare::ALB;
	}

	//sir de caractere alocat dinamic char* marca;

	char* getModele()
	{
		char* copie = new char[strlen(this->modele) + 1];
		strcpy_s(copie,strlen(this->modele)+1,this->modele);
		return copie;
	}
	void setModele(const char* _modele)
	{
		
		if (this->modele != nullptr)
		{
			delete[] this->modele;
			this->modele = nullptr;
		}
		
		if (_modele != nullptr)
		{
			this->modele = new char[strlen(_modele) + 1];
			strcpy_s(this->modele, strlen(_modele) + 1, _modele); \
		}
		else
		{
			this->marca = new char[strlen("Anonim") + 1];
			strcpy_s(this->marca, strlen("Anonim") + 1, "Anonim");
		}
	}

	// sir de caractere alocat static char modele[50];
	char* getMarca()
	{
		char* copie = new char[strlen(this->marca) + 1];
		strcpy_s(copie, strlen(this->marca) + 1, this->marca);
		return copie;
	}
	void setMarca(const char* _marca)
	{
		if (_marca != nullptr)
			strcpy_s(this->marca, sizeof(this->modele) + 1, _marca);
		else
			strcpy_s(this->modele, sizeof(this->modele), "Anonim");
	}

	// vector numeric alocat static  int stocStatic[10];
	void getStocStatic(int _stoc[10])
	{
		for (int i = 0; i < 10; i++)
			_stoc[i] = this->stocStatic[i];
	}

	void setStocStatic(const int _stoc[10])
	{
		for (int i = 0; i < 10; i++)
			this->stocStatic[i] = _stoc[i];
	}

	//vector numeric alocat dinamic int* stocDinamic; int nrMasini;

	int* getStocDinamic()
	{
		if (this->stocDinamic == nullptr || this->nrMasini == 0)
		{
			return nullptr;
		}
		int* copie = new int[this->nrMasini];
		for (int i = 0; i < this->nrMasini; i++)
			copie[i] = this->stocDinamic[i];
		return copie;
	}
	/*void getStocDinamic(int*& _masini, int& _nrMasini)
	{

		_nrMasini = this->nrMasini;
		_masini = new int[_nrMasini];
		for (int i = 0; i < this->nrMasini; i++)
			_masini[i] = this->stocDinamic[i];
	}*/
	void setStocDinamic(const int* _masini, int _nrMasini)
	{
		if (_masini != nullptr && _nrMasini > 0)
		{
			delete[] this->stocDinamic;
			this->stocDinamic = nullptr;
			this->nrMasini = 0;

			this->nrMasini = _nrMasini;
			this->stocDinamic = new int[this->nrMasini];
			for (int i = 0; i < this->nrMasini; i++)
				this->stocDinamic[i] = _masini[i];
		}
		else
		{
			delete[] this->stocDinamic;
			this->stocDinamic = nullptr;
			this->nrMasini = 0;
		}
	}
	//vector de bool alocat static
	void getTestDrive(bool _testDrive[5])
	{
		for (int i = 0; i < 5; i++)
			_testDrive[i] = this->testDrive[i];
	}

	void setTestDrive(const bool _testDrive[5])
	{
		for (int i = 0; i < 5; i++)
			this->testDrive[i] = _testDrive[i];

	}

	//vector de bool alocat dinamic

	void getPrezentare(bool*& _prezentare, int& _nrPrezentare)
	{
		_nrPrezentare = this->nrPrezentare;
		_prezentare = new bool[_nrPrezentare];
		for (int i = 0; i < _nrPrezentare; i++)
			_prezentare[i] = this->prezentare[i];
	}

	void setPrezentare(const bool* _prezentare, int _nrPrezentare)
	{
		if (_prezentare != nullptr && _nrPrezentare > 0)
		{
			delete[] this->prezentare;
			this->prezentare = nullptr;
			this->nrPrezentare = 0;


			this->nrPrezentare = _nrPrezentare;
			this->prezentare = new bool[this->nrPrezentare];
			for (int i = 0; i < this->nrPrezentare; i++)
				this->prezentare[i] = _prezentare[i];
		}
		else
		{
			delete[] this->prezentare;
			this->prezentare = nullptr;
			this->nrPrezentare = 0;
		}
	}

	//vector de enum alocat static
	void getCuloareStatica(Culoare _culori[5])
	{
		for (int i = 0; i < 5; i++)
			_culori[i] = this->modelCulaore[i];
	}
	void setCuloareStatica(const Culoare _culori[5])
	{
		for (int i = 0; i < 5; i++)
			this->modelCulaore[i] = _culori[i];
	}

	//vector de enum alocat dinamic

	void getCuloareDinamica(Culoare*& _culori, int& _nr)
	{
		_nr = this->nrculori;
		_culori = new Culoare[_nr];
		for (int i = 0; i < _nr; i++)
			_culori[i] = this->culdin[i];
	}

	void setCuloareDinamica(const Culoare* _culori, int _nr)
	{
		if (_culori != nullptr && _nr > 0)
		{
			delete[] this->culdin;
			this->culdin = nullptr;
			this->nrculori = 0;


			this->nrculori = _nr;
			this->culdin = new Culoare[this->nrculori];
			for (int i = 0; i < this->nrculori; i++)
				this->culdin[i] = _culori[i];
		}
		else
		{
			delete[] this->culdin;
			this->culdin = nullptr;
			this->nrculori = 0;
		}
	}

	// un char
	char getInitiala()
	{
		return this->initiala;
	}
	void setInitiala(char _Initiala)
	{
		this->initiala = _Initiala;
	}

	// int
	int getNrModele()
	{
		return this->nrModele;
	}
	void setNrmodele(int _nrModele)
	{
		this->nrModele = _nrModele;
	}
	
	//float
	float getPretPornire()
	{
		return this->pretPornire;
	}
	void setPretPornire(float _pretPornire)
	{
		if (_pretPornire >= 200)this->pretPornire = _pretPornire;
	}

	//enum

	Culoare getCuloare()
	{
		return this->culoare;
	}
	void setCuloare(Culoare _culoare)
	{
		this->culoare = _culoare;
	}

	//bool

	bool getStoc()
	{
		return this->stock;
	}
	void setStoc(bool _stock)
	{
		this->stock = _stock;

	}
	
};
int main()
{
	Masini m1;

	// Test setters
	m1.setMarca("Dacia");
	m1.setModele("Logan");
	m1.setInitiala('L');
	m1.setNrmodele(5);
	m1.setPretPornire(5000);
	m1.setCuloare(ALBASTRU);
	m1.setStoc(true);

	int stocStatic[10] = { 10,9,8,7,6,5,4,3,2,1 };
	m1.setStocStatic(stocStatic);

	int stocDinamic[3] = { 12,15,18 };
	m1.setStocDinamic(stocDinamic, 3);

	bool testDrive[5] = { true,false,true,false,true };
	m1.setTestDrive(testDrive);

	bool prezentare[3] = { true,true,false };
	m1.setPrezentare(prezentare, 3);

	// Test getters
	char* marca = m1.getMarca();
	cout << "Marca: " << marca << endl;
	delete[] marca;

	char* modele = m1.getModele();
	cout << "Modele: " << modele << endl;
	delete[] modele;

	cout << "Initiala: " << m1.getInitiala() << endl;
	cout << "Numar modele: " << m1.getNrModele() << endl;
	cout << "Pret pornire: " << m1.getPretPornire() << endl;
	cout << "Culoare: " << m1.getCuloare() << endl;
	cout << "Stoc disponibil: " << (m1.getStoc() ? "Da" : "Nu") << endl;

	int stocOut[10];
	m1.getStocStatic(stocOut);
	cout << "Stoc static: ";
	for (int i = 0; i < 10; i++) cout << stocOut[i] << " ";
	cout << endl;

	int* stocDinamicOut = nullptr;
	int nrMasini = 0;
	m1.getStocDinamic(stocDinamicOut, nrMasini);
	cout << "Stoc dinamic (" << nrMasini << "): ";
	for (int i = 0; i < nrMasini; i++) cout << stocDinamicOut[i] << " ";
	cout << endl;
	delete[] stocDinamicOut;

	bool testDriveOut[5];
	m1.getTestDrive(testDriveOut);
	cout << "Test drive: ";
	for (int i = 0; i < 5; i++) cout << (testDriveOut[i] ? "1 " : "0 ");
	cout << endl;

	bool* prezentareOut = nullptr;
	int nrPrezentare = 0;
	m1.getPrezentare(prezentareOut, nrPrezentare);
	cout << "Prezentare (" << nrPrezentare << "): ";
	for (int i = 0; i < nrPrezentare; i++) cout << (prezentareOut[i] ? "1 " : "0 ");
	cout << endl;
	delete[] prezentareOut;


	// vector static
	Culoare vStatice[5] = { ALB, NEGRU, ALBASTRU, ALB, NEGRU };
	m1.setCuloareStatica(vStatice);

	Culoare vStaticeOut[5];
	m1.getCuloareStatica(vStaticeOut);
	for (int i = 0; i < 5; i++) cout << vStaticeOut[i] << " ";
	cout << endl;

	// vector dinamic
	Culoare vDinamice[3] = { ALBASTRU, NEGRU, ALB };
	m1.setCuloareDinamica(vDinamice, 3);

	Culoare* vDinamiceOut = nullptr;
	int nr;
	m1.getCuloareDinamica(vDinamiceOut, nr);
	for (int i = 0; i < nr; i++) cout << vDinamiceOut[i] << " ";
	cout << endl;

	delete[] vDinamiceOut;

	cout << "\n=== Test completat cu succes ===" << endl;
	return 0;
}
