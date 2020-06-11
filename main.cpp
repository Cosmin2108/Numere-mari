#include <iostream>
#include<vector>
#include<list>
#include<vector>
#include<stdlib.h>
#include<string.h>
#include<math.h>

class NumereMari
{
    private:
    std::list<int> nr_mare;
    bool semn;
    int zecimale;

    public:
    NumereMari(){};
    ~NumereMari(){};
    NumereMari(const NumereMari &nr); /// construcor de copiere. daca nu pun & la arg, o fct creeaza o copie a paramentrului deci va apela din nou constructorul de copiere

    friend std::istream& operator >>(std::istream&in, NumereMari &nr);
    friend std::ostream& operator <<(std::ostream&out, NumereMari &nr);
    NumereMari operator+(NumereMari nr);
    NumereMari operator-(NumereMari nr);
    NumereMari operator-();
    NumereMari operator *(NumereMari &nr);
    friend NumereMari maxim(NumereMari &nr1,NumereMari &nr2);
    friend class VectorNrMari;
};

class VectorNrMari
{  private:
   NumereMari nr;

   public:

   friend std::istream& operator >>(std::istream&in,std::vector<VectorNrMari> &nr);
   friend std::ostream& operator <<(std::ostream&out, std::vector<VectorNrMari> &nr);
   friend std::vector<VectorNrMari> produs_vectorial(std::vector<VectorNrMari> &u, std::vector<VectorNrMari> &v);
   friend NumereMari maxim_vector(std::vector<VectorNrMari> &v);

};

NumereMari::NumereMari(const NumereMari &nr)  /// constructor de copiere.
{
    (*this).nr_mare.assign(nr.nr_mare.begin(),nr.nr_mare.end());
    (*this).semn=nr.semn;
    this->zecimale = nr.zecimale;
}

std::istream& operator >>(std::istream &in,  NumereMari &nr)
{
    if(!nr.nr_mare.empty())
        nr.nr_mare.clear();
    char *s=new char[1000];
    in>>s;
    if(s[0]=='-')
        nr.semn=0;
    else
    if(s[0]=='+')
        nr.semn=1;
     else
         { nr.nr_mare.push_back(s[0]-'0'); nr.semn=1; }

    for(int i=1;i<strlen(s);i++){
        if(s[i] == ',')
            nr.zecimale = strlen(s) - i - 1;
        else
            nr.nr_mare.push_back(s[i]-'0');
    }

    delete []s;
    return in;
}


std::ostream& operator <<(std::ostream &out, NumereMari &nr)
{
    if(nr.semn==0)
        out<<"-";

    int k = 0;
    for(std::list<int>::iterator i=nr.nr_mare.begin();i!=nr.nr_mare.end();i++){
        out<<*i;
        if(k != nr.nr_mare.size() - 1 && nr.nr_mare.size() - nr.zecimale - 1 == k) // afiseaza si virgula daca e cazul
            out<<',';
        k++;
    }


    return out;
}

NumereMari NumereMari::operator+(NumereMari nr)
{
    NumereMari aux;

    if(this->semn!=nr.semn)
    {
        if(this->semn==0)
            aux=nr-(-*this);
        else
            aux=*this-(-nr);
        return aux;
    }


    std::list<int>::reverse_iterator i=nr.nr_mare.rbegin();
    std::list<int>::reverse_iterator j=nr_mare.rbegin();
    int rest=0;
    while(i!=nr.nr_mare.rend()&&j!=nr_mare.rend())
    {
        aux.nr_mare.push_front((*i+*j+rest)%10);   /// insereaza la inceput;
        rest=(*i+*j+rest)/10;
        i++;j++;
    }

    while(i!=nr.nr_mare.rend())
    {
        aux.nr_mare.push_front((*i+rest)%10);
        rest=(*i+rest)/10;
        i++;
    }

    while(j!=nr_mare.rend())
    {
        aux.nr_mare.push_front((*j+rest)%10);
        rest=(*j+rest)/10;
        j++;
    }
    aux.semn=semn;
    if(rest)
        aux.nr_mare.push_front(rest);
    aux.zecimale = std::max(this->zecimale, nr.zecimale);

    return aux;
}

NumereMari NumereMari::operator-(NumereMari nr)
{
    NumereMari aux, copie=*this;
    if(this->semn!=nr.semn)
    {
        aux=*this+(-nr); // functioneaza si daca priumul e neg si al 2-lea poz dar si invers
        return aux;

    }
    else
    if(this->semn==nr.semn==0)
    {
         aux=(-nr)-(-*this);
         return aux;
    }
    else
    if(this->nr_mare.size() < nr.nr_mare.size())
    {
        aux = -(nr-*this); // scot minusul in fata daca  primul < ca al 2-lea in scadere
        return aux;
    }
    else
    if(nr_mare.size()==nr.nr_mare.size())
    {
        std::list<int>:: iterator m=nr_mare.begin();
        std::list<int>:: iterator n=nr.nr_mare.begin();

        while(m!=nr_mare.end()&&n!=nr.nr_mare.end()) // verific daca nr din stg e mai mare ca cel din drp chiar daca au acelasi nr de cifre. daca este, fac scaderea invers si inmultesc cu -1
        {
            if(*m<*n)
            {
                aux=-(nr-*this);
                return aux;
            }
            m++; n++;
        }
    }


    std::list<int>:: reverse_iterator i=nr_mare.rbegin();
    std::list<int>:: reverse_iterator j=nr.nr_mare.rbegin();

    int imprumut=0;
    while(i!=nr_mare.rend()&&j!=nr.nr_mare.rend())
    {
        if(*i<*j)
            imprumut=10;

        aux.nr_mare.push_front(imprumut+*i-*j);   /// insereaza la inceput;
        i++;
        j++;

        if(imprumut==10)
            (*i)--; /// scad valoarea cifrei pe care ma aflu. am avansat pe ea mai sus, cu i++, e un reverse iterator
        imprumut=0;
    }

     while(i!=nr_mare.rend())
     {
        if(i==nr_mare.rend())
        {
            if(*i!=0) /// cazul in care m-am imprumutat de la ulima cifra din stg si a devenit 0
                aux.nr_mare.push_front(*i);
        }
        else
            aux.nr_mare.push_front(*i);

        i++;
     }

     aux.semn=semn;
     *this=copie;
     aux.zecimale = std::max(this->zecimale, nr.zecimale);
     return aux;
}

NumereMari NumereMari::operator-()
{
    NumereMari aux=*this;
    if(aux.semn==0)
        aux.semn=1;
    else
        aux.semn=0;

    return aux;
}

NumereMari NumereMari::operator*(NumereMari &nr)
{
  std::list<int>::reverse_iterator i;
  std::list<int>::reverse_iterator j;
  NumereMari aux,produs;
  if(semn!=nr.semn)
  produs.semn=0;
  else
  produs.semn=1;

  int deplasare=0;
  for(i=nr_mare.rbegin();i!=nr_mare.rend();i++)
  {
      int rest=0;
      for(j=nr.nr_mare.rbegin();j!=nr.nr_mare.rend();j++)
        {
            aux.nr_mare.push_front(((*j)*(*i)+rest)%10);
            rest=((*j)*(*i)+rest)/10;

        }
      if(rest!=0)
        aux.nr_mare.push_front(rest);
      aux.semn=produs.semn;
      for(int k=0;k<deplasare;k++)
        aux.nr_mare.push_back(0);

      produs=produs+aux;
      aux.nr_mare.clear();
      deplasare++;
  }
  aux.nr_mare.clear();
  produs.zecimale = this->zecimale + nr.zecimale;
  return produs;
}

NumereMari maxim(NumereMari &nr1, NumereMari &nr2)
{
    std::list<int>:: iterator m=nr1.nr_mare.begin();
    std::list<int>:: iterator n=nr2.nr_mare.begin();
       if(nr1.semn!=nr2.semn)
       {
           if(nr1.semn==0)
            return nr2;
           else
            return nr1;
       }
        else
       if(nr1.nr_mare.size()==nr2.nr_mare.size())
         {
           while(m!=nr1.nr_mare.end()&&n!=nr2.nr_mare.end())
           {
               if(*m<*n)
                if(nr1.semn==0)
                return nr1;
                else
                return nr2;
               m++; n++;
           }
           if(nr1.semn==0)
            return nr2;
           else
           return nr1;
         }
       else
       if(nr1.nr_mare.size()<nr2.nr_mare.size())
        if(nr1.semn==0)
          return nr1;
        else
         return nr2;
       else
        if(nr1.semn==0)
         return nr2;
        else
         return nr1;

}

std::istream& operator >>(std::istream&in, std::vector<VectorNrMari> &v)
{
    NumereMari aux;
    VectorNrMari aux2;
    int nr_elem;
    std::cout<<"Introdu nr de elem al vectorului: ";
    in>>nr_elem;
    for(int i=0;i<nr_elem;i++)
    {
     in>>aux;
     aux2.nr=aux;
     v.push_back(aux2);

    }
    return in;
}
std::ostream& operator <<(std::ostream&out,  std::vector<VectorNrMari> &v)
{
    for(int i=0;i<v.size();i++)
        out<<v[i].nr<<"  ";
    out<<"\n";
    return out;
}

NumereMari maxim_vector(std::vector<VectorNrMari> &v)
{
    NumereMari max_v=v[0].nr;

    for(int i=1;i<v.size();i++)
        max_v=maxim(max_v,v[i].nr);

    return max_v;
}


std::vector<VectorNrMari> produs_vectorial(std::vector<VectorNrMari> &u, std::vector<VectorNrMari> &v)
{
  std::vector<VectorNrMari> produs;
  VectorNrMari aux;

  for(int i=0;i<v.size();i++)
  {
     aux.nr=v[i].nr*u[i].nr;
     produs.push_back(aux);

  }

  return produs;
}


int main()
{
    NumereMari nr1,nr2,nr3, max_v;
    std::cout<<"Introdu numar intreg mare: ";
    std::cin>>nr1;

    std::cout<<"Introdu numar intreg mare: ";
    std::cin>>nr2;


    nr3=nr1+nr2;
    std::cout<<"Afisare suma numar intreg mare: "<<nr3<<"="<<nr1<<" + "<<nr2<<"\n";

    nr3=nr1-nr2;
    std::cout<<"Afisare diferenta numar intreg mare: "<<nr3<<"="<<nr1<<" - "<<nr2<<"\n";

    nr3=nr1*nr2;
    std::cout<<"Afisare produs numar intreg mare: "<<nr3<<"\n";

    nr3=maxim(nr1,nr2);
    std::cout<<"Afisare maximul dintre numerele intregi mari: "<<nr3<<"\n\n";

    // asta e o prostie. Nu aveam nevoie de a 2-a clasa. fac vector de prima clasa.
    //std::vector<VectorNrMari> v1,v2, produs;
    //std::cin>>v1>>v2;
    //max_v=maxim_vector(v1);
    //std::cout<<v1<<"\n"<<v2<<"\n";
    //std::cout<<"Maximul din vector v1: "<<max_v<<"\n";
    //produs=produs_vectorial(v1,v2);
    //std::cout<<"Produsul vectorial: "<<produs;

    return 0;
}
