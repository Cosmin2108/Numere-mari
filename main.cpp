#include <iostream>
#include<vector>
#include<list>
#include<vector>
#include<stdlib.h>
#include<string.h>

class numere_int_mari
{
private:
std::list<int> nr_mare;
bool semn;

public:
numere_int_mari(){};
~numere_int_mari(){};
numere_int_mari(const numere_int_mari &nr); /// construcor de copiere. daca nu pun & la arg, o fct creeaza o copie a paramentrului deci va apela din nou constructorul de copiere

friend std::istream& operator >>(std::istream&in, numere_int_mari &nr);
friend std::ostream& operator <<(std::ostream&out, numere_int_mari &nr);
numere_int_mari operator+(numere_int_mari nr);
numere_int_mari operator-(numere_int_mari nr);
numere_int_mari operator-();
numere_int_mari operator *(numere_int_mari &nr);
friend numere_int_mari maxim(numere_int_mari &nr1,numere_int_mari &nr2);
friend class vector_nr_int;
};

class vector_nr_int
{  private:
   numere_int_mari nr;

   public:

   friend std::istream& operator >>(std::istream&in,std::vector<vector_nr_int> &nr);
   friend std::ostream& operator <<(std::ostream&out, std::vector<vector_nr_int> &nr);
   friend std::vector<vector_nr_int> produs_vectorial(std::vector<vector_nr_int> &u, std::vector<vector_nr_int> &v);
   friend numere_int_mari maxim_vector(std::vector<vector_nr_int> &v);

};

numere_int_mari::numere_int_mari(const numere_int_mari &nr)  /// daca aloc ceva dinamic e nevoie de asta pt a nu se sterge valoarea catre care pointeaza
{
    (*this).nr_mare.assign(nr.nr_mare.begin(),nr.nr_mare.end());
     (*this).semn=nr.semn;
}

std::istream& operator >>(std::istream&in,  numere_int_mari &nr)
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

    for(int i=1;i<strlen(s);i++)
        nr.nr_mare.push_back(s[i]-'0');

    delete []s;
    return in;
}


std::ostream& operator <<(std::ostream &out, numere_int_mari &nr)
{
    if(nr.semn==0)
    out<<"-";

   for(std::list<int>::iterator i=nr.nr_mare.begin();i!=nr.nr_mare.end();i++)
     out<<*i;

 return out;
}

numere_int_mari numere_int_mari::operator+(numere_int_mari nr)
{
    numere_int_mari aux;

    if(semn!=nr.semn)
     {
      if(semn==0)
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
     return aux;
}

numere_int_mari numere_int_mari::operator-(numere_int_mari nr)
{
    numere_int_mari aux, copie=*this;
    if(semn!=nr.semn)
    {
         aux=*this+(-nr);
         return aux;

    }
    else
    if(semn==nr.semn==0)
    {
         aux=(-nr)-(-*this);
         return aux;
    }
    else
    if(nr_mare.size()<nr.nr_mare.size())
     {
        aux=-(nr-*this);
        return aux;
     }
     else
     if(nr_mare.size()==nr.nr_mare.size())
     {
         std::list<int>:: iterator m=nr_mare.begin();
         std::list<int>:: iterator n=nr.nr_mare.begin();

         while(m!=nr_mare.end()&&n!=nr.nr_mare.end())
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
        (*i)--;
        imprumut=0;
    }

     while(i!=nr_mare.rend())
     {   if(i==nr_mare.rend())
          {if(*i!=0)
            aux.nr_mare.push_front(*i);
          }
          else
          aux.nr_mare.push_front(*i);

         i++;
     }

     aux.semn=semn;
     *this=copie;
     return aux;

}

numere_int_mari numere_int_mari::operator-()
{
    numere_int_mari aux=*this;
    if(aux.semn==0)
        aux.semn=1;
    else
        aux.semn=0;

    return aux;
}

numere_int_mari numere_int_mari::operator*(numere_int_mari &nr)
{
  std::list<int>::reverse_iterator i;
  std::list<int>::reverse_iterator j;
  numere_int_mari aux,produs;
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
  return produs;
}

numere_int_mari maxim(numere_int_mari &nr1, numere_int_mari &nr2)
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

std::istream& operator >>(std::istream&in, std::vector<vector_nr_int> &v)
{
    numere_int_mari aux;
    vector_nr_int aux2;
    int nr_elem;
    std::cout<<"Introud nr de elem al vectorului: ";
    in>>nr_elem;
    for(int i=0;i<nr_elem;i++)
    {
     in>>aux;
     aux2.nr=aux;
     v.push_back(aux2);

    }
    return in;
}
std::ostream& operator <<(std::ostream&out,  std::vector<vector_nr_int> &v)
{
    for(int i=0;i<v.size();i++)
        out<<v[i].nr<<"  ";
    out<<"\n";
    return out;
}

numere_int_mari maxim_vector(std::vector<vector_nr_int> &v)
{
    numere_int_mari max_v=v[0].nr;

   for(int i=1;i<v.size();i++)
        max_v=maxim(max_v,v[i].nr);

return max_v;
}


std::vector<vector_nr_int> produs_vectorial(std::vector<vector_nr_int> &u, std::vector<vector_nr_int> &v)
{
  std::vector<vector_nr_int> produs;
  vector_nr_int aux;

  for(int i=0;i<v.size();i++)
  {
     aux.nr=v[i].nr*u[i].nr;
     produs.push_back(aux);

  }

  return produs;
}


int main()
{  numere_int_mari nr1,nr2,nr3, max_v;
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

   std::vector<vector_nr_int> v1,v2, produs;
   std::cin>>v1>>v2;
   max_v=maxim_vector(v1);
   std::cout<<v1<<"\n"<<v2<<"\n";
   std::cout<<"Maximul din vector v1: "<<max_v<<"\n";
   produs=produs_vectorial(v1,v2);
   std::cout<<"Produsul vectorial: "<<produs;

    return 0;
}
