#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <typeinfo>

using namespace std;

class nodo{
	public:
		int val;
		nodo *succ;
};

class listaCircolare{
	nodo *testa;
	nodo *coda;
	public:
		listaCircolare(){
			testa=NULL;
			coda=NULL;
		}
		~listaCircolare(){
			nodo *iter=this->testa;
			while(iter!=this->coda){
				nodo *n=iter->succ;
				delete iter;
				iter=n;
			}
			delete iter;//CANCELLO LA CODA
		}
		void inserTesta(int x){
			nodo *nuovo=new nodo;
			nuovo->val=x;
			
			if(this->testa){
				nuovo->succ=this->testa;
				this->testa=nuovo;
			}
			else{
				nuovo->succ=nuovo;
				this->testa=this->coda=nuovo;
			}
		}
		void inser(nodo *pre,int x){
			if(pre==this->coda){
				listaCircolare::inserCoda(x);
			}
			else{
				nodo *nuovo=new nodo;
				nuovo->val=x;
				nuovo->succ=pre->succ;
				pre->succ=nuovo;
			}
		}
		void inserCoda(int x){
			nodo *nuovo=new nodo;
			nuovo->val=x;
			nuovo->succ=this->testa;
			
			if(this->testa){
				this->coda->succ=nuovo;
				this->coda=nuovo;
			}
			else{
				this->testa=this->coda=nuovo;
			}
			
		}
		nodo *ricerca(int x){
			nodo *iter=this->testa;
			if(iter){
				for(iter;iter!=this->coda;iter=iter->succ){
					if(iter->val==x)
						return iter;
				}
				if(this->coda->val==x)
					return this->coda;
				return NULL;
			}
			else
				cout<<"LISTA VUOTA"<<endl;
		}
		void rimuovi(int x){
			nodo *n=listaCircolare::ricerca(x);
			nodo *iter=this->testa;
			if(iter){
				if(n){
					if(n==this->testa){//RIMUOVO LA TESTA
						nodo *s=this->testa->succ;
						delete this->testa;
						this->testa=s;
					}
					else{
						if(n==this->coda){//RIMUOVO LA CODA
							while(iter->succ!=this->coda){
								iter=iter->succ;
							}
							delete this->coda;
							this->coda=iter;
						}
						else{//CASO GENERICO
							nodo *s=iter->succ;
							while(s->val!=x){
								iter=iter->succ;
								s=s->succ;
							}
							iter->succ=s->succ;
							delete s;
						}
					}
				}
				else
					cout<<"NON TROVATO"<<endl;
			}
			else
				cout<<"LISTA VUOTA"<<endl;
		}
		friend ostream & operator <<(ostream & os,listaCircolare & l);
};

ostream & operator <<(ostream & os,listaCircolare & l){
	nodo *iter=l.testa;
	nodo *coda=l.coda;
	if(iter){
		if(iter==coda){
			os<<"-->"<<iter->val<<"-->TESTA("<<iter->val<<")--"<<endl;		
		}
		else{//SE HO PIU' DI UN ELEMENTO
			while(iter!=coda){//STAMPO LA LISTA TRANNE LA CODA
				os<<"-->"<<iter->val;
				iter=iter->succ;
			}
			os<<"-->"<<iter->val<<"-->TESTA("<<l.testa->val<<")--"<<endl;//STAMPO LA CODA
		}
	}
	else
		os<<"LISTA VUOTA"<<endl;
	return os;
}

int main(){
	listaCircolare l;
	cout<<l<<endl;
	cout<<"TESTA"<<endl;
	l.inserTesta(3);
	l.inserTesta(4);
	l.inserTesta(12);
	cout<<l<<endl;
	cout<<"CODA"<<endl;
	l.inserCoda(7);
	l.inserCoda(9);
	l.inserCoda(1);
	cout<<l<<endl;
	int x,y,z;
	cout<<"INSERISCI ELEMENTO DA CERCARE:"<<endl;
	cin>>x;
	nodo *n=l.ricerca(x);
	if(n)
		cout<<"TROVATO"<<endl;
	else
		cout<<"NON TROVATO"<<endl;
	cout<<"INSERISCI ELEMENTO DA INSERIRE:"<<endl;
	cin>>y;
	l.inser(n,y);
	cout<<l<<endl;
	cout<<"INSERISCI ELEMENTO DA RIMUOVERE:"<<endl;
	cin>>z;
	l.rimuovi(z);
	cout<<l<<endl;
}



