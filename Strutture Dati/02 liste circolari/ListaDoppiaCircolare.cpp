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
		nodo *prec;
};

class listaDoppiaCircolare{
	nodo *testa;
	nodo *coda;
	public:
		listaDoppiaCircolare(){
			testa=NULL;
			coda=NULL;
		}
		~listaDoppiaCircolare(){
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
				nuovo->prec=this->coda;
				nuovo->succ=this->testa;
				this->testa=nuovo;
			}
			else{
				nuovo->prec=nuovo;
				nuovo->succ=nuovo;
				this->testa=this->coda=nuovo;
			}
		}
		void inser(nodo *pre,int x){
			if(pre==this->coda){
				listaDoppiaCircolare::inserCoda(x);
			}
			else{
				nodo *nuovo=new nodo;
				nuovo->val=x;
				nuovo->succ=pre->succ;
				nuovo->prec=pre;
				pre->succ=nuovo;
			}
		}
		void inserCoda(int x){
			nodo *nuovo=new nodo;
			nuovo->val=x;
			
			if(this->testa){
				nuovo->succ=this->testa;
				nuovo->prec=this->coda;
				this->coda->succ=nuovo;
				this->testa->prec=nuovo;
				this->coda=nuovo;
			}
			else{
				nuovo->succ=nuovo;
				nuovo->prec=nuovo;
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
			nodo *n=listaDoppiaCircolare::ricerca(x);
			nodo *iter=this->testa;
			if(iter){
				if(n){
					if(n==this->testa){//RIMUOVO LA TESTA
						nodo *s=this->testa->succ;
						delete this->testa;
						this->testa=s;
						this->testa->prec=this->coda;
					}
					else{
						if(n==this->coda){//RIMUOVO LA CODA
							while(iter->succ!=this->coda){
								iter=iter->succ;
							}
							delete this->coda;
							this->coda=iter;
							this->coda->succ=this->testa;
						}
						else{//CASO GENERICO
							nodo *s=iter->succ;
							while(s->val!=x){
								iter=iter->succ;
								s=s->succ;
							}
							iter->succ=s->succ;
							s->succ->prec=iter;
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
		friend ostream & operator <<(ostream & os,listaDoppiaCircolare & l);
};

ostream & operator <<(ostream & os,listaDoppiaCircolare & l){
	nodo *iter=l.testa;
	nodo *coda=l.coda;
	if(iter){
		if(iter==coda){
			os<<"CODA("<<coda->val<<")<--"<<iter->val<<"-->TESTA("<<iter->val<<")"<<endl;		
		}
		else{//SE HO PIU' DI UN ELEMENTO
			os<<"CODA("<<coda->val<<")";
			while(iter!=coda){//STAMPO LA LISTA TRANNE LA CODA
				os<<"<--"<<iter->val<<"-->";
				iter=iter->succ;
			}
			os<<"<--"<<iter->val<<"-->TESTA("<<l.testa->val<<")"<<endl;;//STAMPO LA CODA
		}
	}
	else
		os<<"LISTA VUOTA"<<endl;
	return os;
}

int main(){
	listaDoppiaCircolare s;
	cout<<s<<endl;
	s.inserCoda(12);
	s.inserCoda(10);
	s.inserCoda(8);
	s.inserTesta(14);
	s.inserTesta(16);
	cout<<s<<endl;
	int x,y,z;
	cout<<"INSERISCI ELEMENTO DA CERCARE"<<endl;
	cin>>x;
	nodo *n=s.ricerca(x);
	if(n)
		cout<<"TROVATO"<<endl;
	else
		cout<<"NON TROVATO"<<endl;
	cout<<"INSERISCI ELEMENTO DA INSERIRE"<<endl;
	cin>>z;
	s.inser(n,z);
	cout<<s<<endl;
	cout<<"INSERISCI ELEMENTO RIMUOVERE"<<endl;
	cin>>y;
	s.rimuovi(y);
	cout<<s<<endl;
}




