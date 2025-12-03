#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;


enum Bursa
{
	MERIT, SOCIALA
};

class Student
{
	char* nume;
	float medie;
	bool areBursa;
	Bursa tipBursa;

public:
	
	Student()
	{
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		this->medie = 0.0;
		this->areBursa = false;
		this->tipBursa = Bursa::MERIT;
	}
	//metode accesor zona public
	// get si set se ataseaza campurilor private 
	//get consulta o valoarea, doar preia si nu modifca

	float getMedie()
	{
		return this->medie;
	}

	//set modifica valoarea verifica 

	void setMedie(float _medie)
	{
		if (_medie >= 5 && _medie <= 10)
		{
			this->medie = _medie;
		}
	}

	char* getNume()
	{
		char* copie = new char[strlen(this->nume) + 1];
		strcpy_s(copie, strlen(this->nume) + 1, this->nume);
		return copie;

	}

	void setNume(const char* _nume)
	{
		if (_nume != nullptr)
		{
			if (this->nume != nullptr)delete[] this->nume;
		}
		this->nume = new char[strlen(_nume) + 1];
		strcpy_s(this->nume, strlen(_nume) + 1, _nume);
	}
	Bursa getBursa()
	{
		return this->tipBursa;
	}

	void setBursa(Bursa _tipBursa)
	{
		this->tipBursa = _tipBursa;
	}
	bool getareBursa()
	{
		return this->areBursa;
	}
	void setareBursa(bool _areBursa)
	{
		this->areBursa = _areBursa;
	}
};
int main()
{
	Student s;
	cout << "mEDIE ESTE: " << s.getMedie();
	s.setMedie(10);
	cout << "media dupa set este " << s.getMedie();

	cout << "tipul bursei este " << s.getBursa;
	s.setBursa(SOCIALA);
	cout << "tipul bursei dupa set este " << s.getBursa;

	cout << "verifica daca are bursa: " << s.getareBursa;
	s.setareBursa(true);
	cout << "verificare bursa dupa set " << s.getareBursa;
	return 0;
}
