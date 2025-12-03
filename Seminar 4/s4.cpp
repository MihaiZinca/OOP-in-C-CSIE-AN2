#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Student {
	
	string nume; //char* nume; char nume[21]
	int nrNote;
	int* note;
	double buget;

public:
	//constructori 
	//forma de constructori cu parametrii
	//fiind alocare dinamica esti obligat sa ai un constructuor cu param si unu cu param
	Student()
	{
		cout << "\nApel constructor fara param";
		this->nume = "Anonim"; //pt ca avem string
		this->nrNote = 0;
		this->note = nullptr; //cat mai aproape de 0;
		this->buget = 0;
	}
	Student(double _buget)
	{
		this->nume = "Anonim"; 
		this->nrNote = 0;
		this->note = nullptr;
		if (_buget > 0) {
			this->buget = _buget;
		}
		else
		{
			this->buget = 0;
		}
	}

	//la test !!implementare constructor cu validare pe note gen
	
	//nu pot sa vin din exterior daca nu vin cu validari!
	Student(string _nume, int _nrNote, int* _note, double _buget)
	{
		if (_nume.length()>=2) //metoda deci () 
		{
			this->nume = _nume;
		}
		else
		{
			this->nume = "Anonim";
		}
		if (_nrNote > 0 && _note != nullptr)
		{
			this->nrNote = _nrNote;

			//v1 shallow copy (opusu lui deep)  - extrem de periculos , nu creeaza propria zona de memorie
			//this->note = _note;

			//v2 deep copy
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = _note[i];
		}
		else
		{
			this->nrNote = 0;
			this->note = nullptr;
		}

		if (_buget > 0) {
			this->buget = _buget;
		}
		else
		{
			this->buget = 0;
		}
	}
	//meth de prelucrare ->afisare
	//avem deja obiectul this, exista tot timpul 
	// void afisare () const //protejam adresa de la pointerul this , la un getter pune mereu const pentru a se proteja!
	void afisare()
	{
		cout << "\nNume: " << this->nume;
		cout << "\nNr note: " << this->nrNote;
		cout << "\nNote: ";
		for (int i = 0; i < this->nrNote; i++)
			cout << this->note[i] << " ";
		cout << "\nBuget: " << this->buget;
	}
	//meth accesor(get si set)
		
	void setNote(const int* _note, int _nrNote)
	{
		//to do home
		//!!obj de la adresa this deja exista

		if (_note != nullptr && _nrNote > 0)
		{
			delete[] this->note;
			this->note = nullptr;
			this->nrNote = 0;

			this->nrNote = _nrNote;
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = _note[i];
		}
		else
		{
			delete[] this->note;
			this->note = nullptr;
			this->nrNote = 0;
		}
	}

	void setNota(int _nota, int _index) //seteaza nota de pe o poz anume
	{
		//to do home
		//plus validari

		if (_index >= 0 && _index < this->nrNote)
		{
			if (_nota >= 1 && _nota <= 10) this->note[_index] = _nota;
		}

	}

	int* getNote()
	{
		//to do home
		if (this->note == nullptr || this->nrNote == 0)
		{
			return nullptr;
		}
		int* copie = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++)
			copie[i] = this->note[i];
		return copie;
	}
	int getNote(int _index) // doar o nota gen
	{
		//to do 
		if (_index >= 0 && _index < this->nrNote)
		{
			return this->note[_index];
		}
	}
	int getNrNote()
	{
		return this->nrNote;
	
	}

	//meth prelucrare
	//meth care sterge prima nota
	
	void stergerePrimaNota()
	{
		if (this->note != nullptr && this->nrNote > 0)
		{
			if (this->nrNote > 1)
			{
				int* nou = new int[this->nrNote - 1];
				for (int i = 1; i < this->nrNote; i++)
					nou[i - 1] = this->note[i];

				delete[] this->note;
				this->note = nou;
				this->nrNote--;
			}
			else if (this->nrNote == 1) {
				delete[] this->note;
				this->note = nullptr;
				this->nrNote = 0;
			}
		}
	}
	// meth care sterge ultima nota
	
	void stergereUltimaNota()
	{
		if (this->note != nullptr && this->nrNote > 0)
		{
			if (this->nrNote > 1)
			{
				int* nou = new int[this->nrNote - 1];
				for (int i = 0; i < this->nrNote - 1; i++)
					nou[i] = this->note[i];

				delete[] this->note;
				this->note = nou;
				this->nrNote--;
			}
			else if (this->nrNote == 1)
			{
				delete[] this->note;
				this->note = nullptr;
				this->nrNote = 0;
			}
		}
	}
	// meth care sterge toate notele sub medie
	void stergereSubMedie(int medie) 
	{
		if (this->note != nullptr && this->nrNote > 0)
		{
			if (this->nrNote > 1)
			{
				int nr = 0;
				for (int i = 0; i < this->nrNote; i++)
					if (this->note[i] < medie)nr++;
				int j = 0;
				int* nou = new int[this->nrNote - nr];
				for (int i = 0; i < this->nrNote; i++)
					if (this->note[i] < medie)
					{
						nou[j] = this->note[i];
						j++;
					}
				delete[] this->note;
				this->note = nou;
				this->nrNote = this->nrNote - nr;
			}
			else if (this->nrNote == 1) 
			{
					if (this->note[0] < medie)
					{
						delete[] this->note;
						this->note = nullptr;
						this->nrNote = 0;
					}
			}
		}
	}
	// meth care dubleaza ultima nota (p1,p2,p3,.. p5 )
	
	void dublareUltimaNota()
	{
		if (this->note != nullptr && this->nrNote > 0)
		{
				int ultima = this->note[nrNote - 1];
				int* nou = new int[this->nrNote + 1];
				for (int i = 0; i < this->nrNote; i++)
					nou[i] = this->note[i];
				
				nou[this->nrNote] = 2 * ultima;

			
				delete[] this->note;
				this->note = nou;
				this->nrNote++;

		}
	}
	//meth care adauga o noua nota la sfarsitul vectorului
	
	void adaugareNotaSfarsit(int _nota)
	{
		if (this->note != nullptr && this->nrNote > 0)
		{
			if (_nota >= 1 && _nota <= 10)
			{
				int* nou = new int[this->nrNote + 1];
				for (int i = 0; i < this->nrNote; i++)
					nou[i] = this->note[i];

				nou[nrNote] = _nota;

				delete[] this->note;
				this->note = nou;
				this->nrNote++;

			}
		}

	}
	
	// + o clasa masina, ii stim capacitatea rezervorului, capactiatea curenta si un vectori de alimentari, si o meth care sa consume combusil
	

	//supraincarcare operatori 
	
	//destructor 
 };

int main()
{
	Student s;

	Student s1; //ce este, sizeof de student, pe fiecare linie de cate ori ce constructor se apeleaza 


	Student* s2;//este un pointer la un student, un pointer ocupa 4/8 - nu se apleaza niciun constructor
	
	s2 = new Student(); //acum se apleaza o singura data constructor, s2 este un pointer catre un student
	s2 = new Student[5];//vector apelat dinamic, se apleaza de 5 ori constructorul default, sizeof(4/8)!!!!!
	s2 = new Student; // tot constructorul fara aparam se apleteaza o singura data este echivalent cu linia 94!

	Student s3[5];//vector alocat static de obiecte de tip student, se apleaza de 5 ori constructorul default, d aia e esential sa avem constructor default, acum sizeof(5 * ocupa un student)

	Student* s4[5]; // vector alocat static de student*, 5 casute in care fiecare casuta este alocata o adresa (vector de pointer la student) sizeof 4*5 , potrivita sa devina o matrice

	Student** s5;//pointer la pointer la student, ocupa tot 4/8 bytes,poate sa devina un vector alocat dinamic de pointer la student, sau o matrice de pointer la student

	Student s6(25);//se apleaza constructorul cu un parametru, s6 este un obiect de tip student
	Student s7 = 25;// exact la fel ca mai sus

	Student s8(); //s8 nu este un obiect de tip student!! s8 este o functie !!!!!
	return 0;
}