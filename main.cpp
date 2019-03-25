#include <iostream>
#include<conio.h>
#include<string.h>
#include<fstream>

using namespace std;
ifstream f("date.in");

class Nod{
    int info;
    Nod* next;
public:
    Nod(){next=0;};//constructor implicit
    Nod(int info,Nod* next=0);//de initializare
    int getInfo();//da info
    int setInfo(int info);//seteaza info
    Nod* getNext();
    void setNext(Nod* next);
    int operator = (Nod &n);
    friend class coada;
    friend istream& operator>>(istream& t, Nod &n);
    friend ostream& operator<<(ostream& v, Nod &n);
};
/*constructor de initializare*/
Nod::Nod(int info,Nod* next)
{
    this->info=info;
    this->next=next;
}

int Nod::getInfo()
{
    return info;
}

int Nod::setInfo(int info)
{
    this->info=info;
}

Nod* Nod::getNext()
{
    return next;
}
void Nod::setNext(Nod* next)
{
    this->next=next;
}

int Nod::operator =(Nod &n)
{
    return this->info==n.info;
}


istream& operator>>(istream& t, Nod &n){
    cout<<"Citeste info la nod : ";
    t>>n.info;
    return t;
}

ostream& operator<<(ostream& v, Nod &n){
    v<<n.info<<" , ";
    return v;
}

class coada
{
    Nod *prim;
    Nod* ultim;
public:
    coada();//constructor
    ~coada();//destructor
    int isEmpty() ;//coada vida
    Nod* getFirst() const;//da nodul prim
    Nod* getLast() const ;
    int top();//afiseaza primul element din coada
    void push (Nod n);//adaugare
    void pop ();
    coada operator - ( coada& c);
    coada operator + ( coada &c);
    coada copie();
    friend ostream& operator<<(ostream& out, coada&);
    friend istream& operator>>(istream& in, coada&);

};
coada::coada()//constructor
{
    prim=ultim=0;
}
coada::~coada()//destructor
{
    Nod* p=prim;
    Nod*q;
    while(p!=0)
    {
        q=p;
        p=p->next;
        delete q;
    }
    prim=ultim=0;
}

int coada::isEmpty() //coada goala
{
    return prim==0;
}

void coada::push(Nod n)//adaugare nod
{
    Nod *p;
    p=new Nod(n.info,0);
    if(isEmpty())
        prim=ultim=p;
    else {
        ultim->next=p;
        ultim=p;
    }
}


void coada::pop ()
{
    int X;
    Nod *p;
    p= new Nod();
    if (prim == 0) // Underflowy
                cout<<"goala";
    else
    {
        //extragerea valorii, cu eliberarea spaþiului care a fost ocupat de nodul Front
        X = prim -> info;
        p = prim;
        prim = prim -> next;
        delete p  ;
        if (prim == 0) // coada avea un singur element, iar acum e vidã
            ultim = 0;
    }
}

Nod* coada::getFirst() const{
     return prim;
    }

Nod* coada::getLast() const {
     return ultim;
    }
//afiseaza primul element din coada
int coada::top(){
    Nod * p= getFirst();
    cout<<p->getInfo();
     return 0;
    }

ostream& operator<<(ostream& out, coada& coada){
 Nod * p=coada.prim;
        while(p!=NULL){
            out<<p->getInfo()<<",";
            delete p;
            p=p->getNext();
            }
        cout<<"\b ";
        delete p;
        return out;
}


istream& operator>>(istream& r, coada& coada){
    int numar_noduri;
    cout<<"da numarul de noduri: ";
    r>>numar_noduri;
    for(int i=0;i<numar_noduri;i++)
    {
        cout<<"da info : ";
        int info ;
        r >> info;
        coada.push(info);
    }
    return r;
}


coada coada::operator - (coada& c)
{
    while(c.getFirst()->getInfo() == this->getFirst()->getInfo())
    {
        c.pop();
        this->pop();
    }
    return *this;
}

coada coada::copie()
{
    coada c;
    Nod* p=this->prim;
    while(p!=0)
    {
        c.push(p->info);
        p=p->next;
    }
    return c;
}
coada coada::operator + (coada& c)
{
    coada t = this->copie();
    Nod *p = c.prim;
    while(p!=0)
    {
        t.push(p->info);
        p=p->next;
    }
    return t;
}



int main()
{
    cout<<"1. Tastatura  \n 2. Fisier \n";
    int vala;
    cin>>vala;
    switch(vala)
    {
    case 1:
        {
    int val;
    cout<<"Alege : \n 1. Push \n 2. Pop \n 3. Top \n 4. Afisare coada \n 5. Concatenare \n 6. Diferenta \n 7. Citire coada de la tastatura \n  ";
    cout<<"\n Alegerea este :";
    cin>>val;
    coada coada,c1,rez,c2;
    switch(val)
    {
    case 1:
        {
            cout<<"Adauga nodul";
            int info;
            cin>>info;
            coada.push(info);
        };
        break;
    case 2:
        {
            cout<<"Se sterge primul nod ";
            coada.pop();
        };
        break;
    case 3:
        {
            cout<<"Afiseaza varful cozii :";
            coada.top();
        };
        break;
    case 4:
        {
            cout<<"Coada este : ";
            cout<<coada;
        };
        break;
    case 5:
        {
            cout<<"Concatenare : ";
            cin>>c1;
            cin>>c2;
            rez=c2+c1;
            cout<<rez;
        };
        break;
    case 6:
        {
          cout<<"Diferenta a doua cozi : ";
          cin>>c1;
          cin>>c2;
          rez=c2-c1;
          cout<<rez;
        };
        break;
    case 7:
        {
            cout<<"Citire coada de la tastatura : ";
            cin>>coada;
        };
        break;
    default: cout<<"Comanda incorecta :) \n Pentru terminare apasati 0 ";
    break;
    }
        }
        break;
    case 2:
        {
           int val;
    cout<<"Alege : \n 1. Push \n 2. Pop \n 3. Top \n 4. Afisare coada \n 5. Concatenare \n 6. Diferenta \n 7. Citire coada de la tastatura \n  ";
    cout<<"\n Alegerea este :";
    f>>val;
    coada coada,c1,rez,c2;
    switch(val)
    {
    case 1:
        {
            cout<<"Adauga nodul";
            int info;
            f>>info;
            coada.push(info);
        };
        break;
    case 2:
        {
            cout<<"Se sterge primul nod ";
            coada.pop();
        };
        break;
    case 3:
        {
            cout<<"Afiseaza varful cozii :";
            coada.top();
        };
        break;
    case 4:
        {
            cout<<"Coada este : ";
            cout<<coada;
        };
        break;
    case 5:
        {
            cout<<"Concatenare : ";
            f>>c1;
            f>>c2;
            rez=c2+c1;
            cout<<rez;
        };
        break;
    case 6:
        {
          cout<<"Diferenta a doua cozi : ";
          f>>c1;
          f>>c2;
          rez=c2-c1;
          cout<<rez;
        };
        break;
    case 7:
        {
            cout<<"Citire coada de la tastatura : ";
            f>>coada;
        };
        break;
    default: cout<<"Comanda incorecta :) \n Pentru terminare apasati 0 ";
    break;
        }
        break;
        }
    return 0;
}
}
