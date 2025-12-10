#include<iostream>
using namespace std;

//to do home afisare+ citire obj de tip enum folosind ostream si istream -categoric la lucrare

enum class Functie {
    Junior, Senior, Manager, Director 
};

class Angajat {

protected: //<-> public doar ca in mostenire gen
    string nume = "Anonim";
    float salariuBaza = 0;
    Functie functie = Functie::Junior;

public:
    Angajat() {
        cout << "\nApel constructor fara param Angajat";
    }

    Angajat(string _nume)// folosit ot a1="Maria" gen un caz mai ascuns sa zic, face conversie
    {
        this->nume = _nume;
    }

    Angajat(string _nume, float _salariuBaza) {
        cout << "\nApel constructor cu param Angajat";
        this->nume = _nume;
        this->salariuBaza = _salariuBaza;
    }

    Angajat(const Angajat& a) {
        cout << "\nApel constructor copiere Angajat";
        this->nume = a.nume;
        this->salariuBaza = a.salariuBaza;
    }

    Angajat& operator=(const Angajat& a) {
        cout << "\nApel operator= Angajat";
        if (this != &a) {
            this->nume = a.nume;
            this->salariuBaza = a.salariuBaza;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Angajat& a);
    friend istream& operator>>(istream& is, Angajat& a);

    float calculSalariu() {
        return this->salariuBaza;
    }

    bool operator==(const Angajat& a)const {
        return this->nume == a.nume;
    }

    bool operator!() // strict verificare existenta
    {
        return this->salariuBaza == 0;
    }

    //cast la string
    operator string()
    {
        return this->nume;
    }

    //cast la double explicit= se va folosi atunci cand vrem noi
    explicit operator double()
    {
        return this->salariuBaza;
    }

    ~Angajat() {
        cout << "\nApel destructor Angajat";
    }
};

ostream& operator<<(ostream& out, const Angajat& a) {
    out << "\nNume: " << a.nume;
    out << "\nSalariu baza: " << a.salariuBaza;
    out << "Functie: ";
    switch (a.functie) {
        case Functie::Junior: out << "Junior"; break;
        case Functie::Senior: out << "Senior"; break;
        case Functie::Manager: out << "Manager"; break;
        case Functie::Director: out << "Director"; break;
    }
    return out;
}
istream& operator>>(istream& is, Angajat& a)
{
    cout << "\nIntroduceti Numele:";
    is >> a.nume;
    cout << "\nIntroduceti salariu de baza: ";
    is>>a.salariuBaza;

    int f;
    cout << "Functie (0=Junior, 1=Senior, 2=Manager, 3=Director): ";
    is >> f;

    switch (f) 
    {
    case 0: a.functie = Functie::Junior; break;
    case 1: a.functie = Functie::Senior; break;
    case 2: a.functie = Functie::Manager; break;
    case 3: a.functie = Functie::Director; break;
    default: a.functie = Functie::Junior; 
    }
    return is;

}


//citit despre Listkov substitution(principiu) 
//relatia de tip is-a (1-1)
//mostenire/derivare - atribute comune in mai multe clase, reutilizarea codului
//Manager is a Angajat(done)

//TO DO:Manager has a Angajat(1-M) suficient de adaugat o colectie de angajati la manager - 
// concept de design pattern Composite(modeleaza o arborescenta).  -PT EXAMEN SE FAC SUB CU ASA CV

class Manager : public Angajat // derivata din clasa angajat, are in plus diverse elemente, defaultul de derivare e private 
    //->toate campurile din angajat devin private pt manager
    //public - mostenteste tot, logic sizeof manager e mai mare ca angajat
    //clasa Angajat -> clasa parinte/bazza
    //clasa Manager -> clasa derivata/copil
{
    //campuri specifie unui Manager
    int nrSubordonati = 0; //manager se ocupa doar de nrSubordonati si trimite la clasa angajat sa se ocupe de ce stie ea

public:
    Manager()
    {
        cout << "\nApel constructor fara param Manager";
    }

    Manager(string _nume, float _salariuBaza, int _nrSubordonati) :Angajat(_nume, _salariuBaza)
    {
        cout << "\nApel constructor cu param Manager";
        // nu mai puntem this.nume=_nume
        // this.salariuBaza=_salariuBaza 
        //nu tine de manager, el trb sa se ocupe doar de partea lui adc de _nrSubordonati

        this->nrSubordonati = _nrSubordonati;
    }

    Manager(Angajat a, int _nrSubordonati) //trasnfer prin valoare(Angajat a), se face o copie se distruge, 
    {
        cout << "\nApel constructor cu param 2 Manager";
        this->nrSubordonati = _nrSubordonati;
    }


    //copy constructor
    Manager(const Manager& m) :Angajat(m) //constructor de copiere, folosind upcast, managerul s-a redus la un angajat
    {
        cout << "\n Apel constructor copiere Manager";
        this->nrSubordonati = m.nrSubordonati;
    }


    Manager& operator=(const Manager& m)
    {
        if (this != &m) //obligatoriu cand avem alocare dinamica
        {
            this->Angajat::operator=(m); //upcast implicit
            // operator=(m); bluca infinita manager la manager
            this->nrSubordonati = m.nrSubordonati;
        }
        return *this;
    }

    ~Manager()
    {
        cout << "\nApel destructor Manager";
    }

    friend ostream& operator<<(ostream& out, const Manager& m);
    friend istream& operator>>(istream& is, Manager& m);
};

//prin toate metodele friend am acces la zona protected/private/..
//Angajat:: -operator de rezolutie se folos doar in metodele din clasa
ostream& operator<<(ostream& out, const Manager& m)
{
    out << (Angajat)m; //upcast explicit prin valoare returneaza o copie care ulterior este distrusa
    out << "\nNr subordonati: " << m.nrSubordonati;

    return out;
}

istream& operator>>(istream& is, Manager& m)
{
    cout << "Angajatul: ";
    is>>(Angajat&)m; //upcast prin REFERINTA
    cout << "\nNr subordonati: ";
    is >> m.nrSubordonati;
    return is;

}

//TO DO:Manager has a Angajat(1-M) suficient de adaugat o colectie de angajati la manager - 

class Manager : public Angajat
{
    int nrSub = 0;
    Angajat** subordonati = nullptr; //pointer la vector de pointeri Angajat*

public:
    Manager(){ }
    Manager(string _nume, float _salariuBaza,int _nrSubordonati) :Angajat(_nume, _salariuBaza) 
    {
        this->nrSub = _nrSubordonati;
    }

    Manager(const Manager& m) :Angajat(m)
    {
        this->nrSub = m.nrSub;
        if (m.nrSub > 0 && m.subordonati != nullptr)
        {
            this->nrSub = m.nrSub;
            this->subordonati = new Angajat * [this->nrSub];
            for (int i = 0; i < m.nrSub; i++)
                this->subordonati[i] = new Angajat(*m.subordonati[i]);
        }
    }

    ~Manager()
    {
        if (this->subordonati != nullptr)
        {
            delete[]this->subordonati;
            this->subordonati = nullptr;
        }
    }
    
    Manager& operator=(const Manager& m)
    {
        if (this != &m)
        {
            this->Angajat::operator=(m);
            if (this->subordonati != nullptr)
            {
                delete[]this->subordonati;
                this->subordonati = nullptr;
            }
            this->nrSub = m.nrSub;
            if (m.nrSub > 0 && m.subordonati != nullptr)
            {
                this->nrSub = m.nrSub;
                this->subordonati = new Angajat * [this->nrSub];
                for (int i = 0; i < m.nrSub; i++)
                    this->subordonati[i] = new Angajat(*m.subordonati[i]);
            }
            else
            {
                this->nrSub= 0;
                this->subordonati = nullptr;
            }
        }
        return *this;

    }

    void adaugaSubordonat(Angajat* a)
    {
        Angajat** nou = new Angajat * [this->nrSub + 1];
        for (int i = 0; i < this->nrSub; i++)
            nou[i] = this->subordonati[i];

        nou[this->nrSub] = a;
        delete[]this->subordonati;
        this->subordonati = nou;
        this->nrSub++;
    }

    friend ostream& operator<<(ostream& out, const Manager& m);
    friend istream& operator>>(istream& is,  Manager& m);
};
ostream& operator<<(ostream& out, const Manager& m)
{
    out << (Angajat)m;
    out << "Nr subordonati: " << m.nrSub;
    for (int i = 0; i < m.nrSub; i++)
        out << "\n Subordonatul " << i << *m.subordonati[i];
    return out;
}
istream& operator>>(istream& is, Manager& m)
{
    is >> (Angajat&)m;
    cout << "Nr subordonati: ";
    is >> m.nrSub;
    if (m.nrSub > 0) 
    {
        m.subordonati = new Angajat * [m.nrSub];
        for (int i = 0; i < m.nrSub; i++)
        {
            Angajat* a = new Angajat();
            is >> *a;
            m.subordonati[i] = a;
        }
    }
    return is;

}

int main()
{
    Angajat a1("Gigel", 1200);
    Angajat a2("Costel", 1500);
    cout << "\n operator !";
    if (!a1)
        cout << "\nAngajatul a1 nu are salariu";
    else
        cout << "\nAngajatul a1 are salariu >0";

    cout << "\n operator cast/conversie"; //return dintr un obiect o parte din altc obligatoriu in interiorul clasei!!
    string nume = a1; //practic un constructor din clasa string ori de cate ori contextul cerere se face o conversie implicita 
    cout << "\nNume folosid cast la string: " << nume;

    double salariu = (double)a1; //cast explicit
    cout << "\nSalariul folosind cast la double: " << salariu;
    //to do toString din java folosind cast la string

    // ex cand pundem explicit sau nu if(a1!=1500)
    //  cout<<"\nA1 are salariu diferit de 1500";

    //a1="Maria"; //sa venim cu o implementare ai numele lui a1 - sa devina Maria; putem cu operatorul egal , si this sa returneze string
    // sau a1 devine un angajat cu numele Maria si salariu=0 - un cast de la string la Angajat  
    // -nu putem sa facem asta nu avem acces la clasa string. pot sa fac un constructur cu un singur param unde returnez numele ;
    //string nume2="Maria";
    //a2=nume2;


    cout << "\nTest operator>>";
    Angajat a4;
    cin >> a4;
    cout << "\nAti introdus: " << a4;



    // Manager fara subordonati
    Manager m1("Ionel", 3000, 0);
    cout << "\nManager fara subordonati: " << m1;

    // Manager cu subordonati
    Manager m2("Costelus", 3500, 0);


    Angajat* s1 = new Angajat("Ana", 1200);
    Angajat* s2 = new Angajat("Mihai", 1400);
    Angajat* s3 = new Angajat("Elena", 1300);


    m2.adaugaSubordonat(s1);
    m2.adaugaSubordonat(s2);
    m2.adaugaSubordonat(s3);

    cout << "\nManager cu 3 subordonati: " << m2;

    cout << "\nTest constructor copiere Manager";
    Manager m3 = m2;
    cout << "\nManager copiat: " << m3;

    cout << "\nTest operator= Manager";
    Manager m4;
    m4 = m2; // atribuire
    cout << "\nManager atribuit: " << m4;

    cout << "\nTest operator>> Manager (citire de la tastatura)";
    Manager m5;
    cin >> m5;
    cout << "\nAti introdus managerul: " << m5;


    delete s1;
    delete s2;
    delete s3;

    return 0;
}

//lucrare fara partea de derivare, relatie de compunere ne da implementare corespunzatoare main , sub deschise de propus un opeartor, 
// sau cum sa fie implementat op
