#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

struct DataCalendaristica {
	int zi, luna, an;
};
 
//multime formata din constante globale
enum FormaInvatamant {
	IF, ID, IFR      //enumeratile contin constante si se scriu cu majuscule
};

class Student
{
	char* nume;
	bool areBursa;
	FormaInvatamant formaInvatamant;
	double medieAdmitere;

public:
	//metoda tip constructor, implementarea de constructor default, fara parametrii
	Student()
	{
		cout << "\nApel constructor fara parametrii";
		// poointer this -> adresa obiectului apelator
		//this->nume = nullptr; // foarte buna optiune cand am un vector de note de ex, optam pt siruri de caractere alocat dinamic cu nullptr trebuie sa verificam daca e diferit de null inainte de afisare
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		this->areBursa=false; // -> face deferentiere (*this).areBursa si initalizam cu true/false
		this->formaInvatamant = FormaInvatamant::IF; 
		this->medieAdmitere = 0.0;
	}

	//metode accesor -- zona public!!! (get si set) si se ataseaza campurilor private! 
	//get - consulta o valoare, doar preia nu si modifica
	//orice  parm primeste pointeru this

	double getMedieAdmitere()
	{
		return this->medieAdmitere;
	}
	//setul este de tipul void - modifica
	void setMedieAdmitere(double _medieAdmitere)
	{
		if (_medieAdmitere >= 5 && _medieAdmitere <= 10)
		{
			this->medieAdmitere= _medieAdmitere;
		}
	}
	FormaInvatamant getFormaInvatamant()
	{
		return this->formaInvatamant;
	}
	
	void setFormaInvatamant(FormaInvatamant _FormaInvatamant)
	{
		this->formaInvatamant = _FormaInvatamant;
	}

	//provocarea la char* pt get si set
	
	//aceasta forma incalca incapsularea, daca nume e privat atunci 
	char* getNume1()
	{
		return this->nume;
	}
	
	//incalca incapsularea
	const char* getNume2()
	{
		return this->nume;
	}

	//forma corecta, ne obliga sa facem dezalocare,(alocarea se face pe heap)

	char* getNume()
	{
		//se face o copie a numelui
		char* copie = new char[strlen(this->nume) + 1];
		strcpy_s(copie, strlen(this->nume) + 1, this->nume);
		return copie;
	}

};

int main()
{
	Student s; //constructor aloca pe stiva zona de memorie ..
	cout << "\nMedie aritmetica: " << s.getMedieAdmitere();
	s.setMedieAdmitere(9);
	cout << "\nMedie admitere dupa set: " << s.getMedieAdmitere();

	cout << "\nForma Invatamant: " << s.getFormaInvatamant();
	s.setFormaInvatamant(ID);
	cout << "\nForma Invatamant dupa set este: " << s.getFormaInvatamant();

	return 0;
}

//tmea getter si setter pana cand...