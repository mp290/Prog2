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

class listaDoppia{
	nodo *testa;
	public:
		listaDoppia(){
			testa=NULL;
		}
		~listaDoppia(){
			nodo *iter=this->testa;
			while(iter!=NULL){
				nodo *n=iter->succ;
				delete iter;
				iter=n;
			}
		}
		void inserTesta(int x){
			nodo *nuovo=new nodo;
			nuovo->val=x;
			nuovo->prec=NULL;
			
			if(this->testa){
				nuovo->succ=this->testa;
				this->testa->prec=nuovo;
				this->testa=nuovo;
			}
			else{
				nuovo->succ=NULL;
				this->testa=nuovo;
			}
		}
		void inserCoda(int x){
			nodo *nuovo=new nodo;
			nuovo->val=x;
			nuovo->succ=NULL;
			
			if(this->testa){
				nodo *iter=this->testa;
				while(iter->succ!=NULL){
					iter=iter->succ;
				}
				iter->succ=nuovo;
				nuovo->prec=iter;
			}
			else{
				nuovo->prec=NULL;
				this->testa=nuovo;
			}
		}
		void inser(nodo *pre,int x){
			nodo *nuovo=new nodo;
			nuovo->val=x;
			nuovo->succ=pre->succ;
			nuovo->prec=pre;
			pre->succ=nuovo;
		}
		nodo *ricerca(int x){
			nodo *iter=this->testa;
			if(iter){
				for(iter;iter!=NULL;iter=iter->succ){
					if(iter->val==x)
						return iter;
				}
				return NULL;
			}
			else
				cout<<"LISTA VUOTA"<<endl;
		}
		void rimuovi(int x){
			nodo *n=listaDoppia::ricerca(x);
			nodo *iter=this->testa;
			if(n){
				if(iter){
					if(iter->val==x){//RIMUOVO LA TESTA
						this->testa=iter->succ;
						this->testa->prec=NULL;
						delete iter;
					}		
					else{
						nodo *s=iter->succ;
						while((s!=NULL)&&(s!=n)){
							iter=iter->succ;
							s=s->succ;
						}
						iter->succ=s->succ;
						s->succ->prec=iter;
						delete s;
					}
				}
				else
					cout<<"LISTA VUOTA"<<endl;
			}
			else
				cout<<"NON TROVATO"<<endl;
		}
		friend ostream & operator <<(ostream & os,listaDoppia & l);
};

ostream & operator <<(ostream & os,listaDoppia & l){
	nodo *iter=l.testa;
	if(iter){
		os<<"NULL";
		while(iter!=NULL){
			os<<"<--"<<iter->val<<"-->";
			iter=iter->succ;
		}
		os<<"NULL";
	}
	else
		cout<<"LISTA VUOTA"<<endl;
	return os;
}

int main(){
	listaDoppia l;
	cout<<l<<endl;
	cout<<"TESTA"<<endl;
	l.inserTesta(0);
	l.inserTesta(2);
	l.inserTesta(3);
	l.inserTesta(12);
	cout<<l<<endl;
	cout<<"CODA"<<endl;
	l.inserCoda(3);
	l.inserCoda(2);	
	l.inserCoda(6);
	cout<<l<<endl;
	int x,y,z;
	cout<<"INSERISCI ELEMENTO DA CERCARE:"<<endl;
	cin>>x;
	nodo*n=l.ricerca(x);
	if(n)
		cout<<"TROVATO"<<endl;
	else
		cout<<"NON TROVATO"<<endl;
	cout<<"INSERISCI ELEMENTO DA INSERIRE:"<<endl;
	cin>>z;
	l.inser(n,z);
	cout<<l<<endl;
	cout<<"INSERISCI ELEMENTO DA RIMUOVERE:"<<endl;
	cin>>y;
	l.rimuovi(y);
	cout<<l<<endl;
}



