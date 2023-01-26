#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <typeinfo>
#include <fstream>

using namespace std;

template <typename T>
class nodo{
	public:
		T val;
		nodo<T> *succ;
		nodo<T> *prec;
};

template <typename T>
class Nodo{
	public:
		T val;
		Nodo<T> *sx;
		Nodo<T> *dx;
		Nodo<T> *padre;
};

template <typename T>
class listaCircDoppia{
	nodo<T> *testa;
	nodo<T> *coda;
	public:
		listaCircDoppia(){
			this->testa=NULL;
			this->coda=NULL;
		}
		T getCoda(){
			return this->coda->val;
		}
		void inserTesta(T x){
			nodo<T> *nuovo=new nodo<T>;
			nuovo->val=x;
			nuovo->prec=this->coda;
			
			if(this->testa){
				nuovo->succ=this->testa;
				this->testa=nuovo;
			}
			else{
				nuovo->succ=nuovo;
				this->testa=this->coda=nuovo;
			}
		}
		void inserCoda(T x){
			nodo<T> *nuovo=new nodo<T>;
			nuovo->val=x;
			nuovo->succ=this->testa;
			
			if(this->testa){
				this->coda->succ=nuovo;
				nuovo->prec=this->coda;
				this->coda=nuovo;
			} 
			else{
				nuovo->prec=nuovo;
				this->coda=this->testa=nuovo;
			}
		}
		template <typename U>
		friend ostream & operator <<(ostream & os,listaCircDoppia<U> & l);
};

template <typename T>
class bst{
	Nodo<T> *root;
	int altezza(Nodo<T> *x){
		if(x==NULL)
			return 0;
		
		int l=altezza(x->sx);
		int r=altezza(x->dx);
		
		if(l>r)
			return l+1;
		else
			return r+1;
	}
	public:
		bst(){
			this->root=NULL;
		}
		T getRoot(){
			return this->root->val;
		}
		void insert(T x){
			Nodo<T> *nuovo=new Nodo<T>;
			nuovo->val=x;
			nuovo->sx=nuovo->dx=NULL;
		
			if(this->root){
				Nodo<T> *iter=this->root;
				Nodo<T> *n;
				while(iter!=NULL){
					n=iter;
					if(x<iter->val)
						iter=iter->sx;
					else
						iter=iter->dx;
				}
				nuovo->padre=n;
				if(x<n->val)
					n->sx=nuovo;
				else
					n->dx=nuovo;
			}
			else{
				nuovo->padre=NULL;
				this->root=nuovo;
			}
		}
		template <typename U>
		friend ostream & operator <<(ostream & os,bst<U> & b);
};

template <typename U>
void stampa(Nodo<U> *x,int l){
	if(x==NULL){
		if(l==0)
			cout<<"_\t";
		return;
	}
	if(l==0)
		cout<<x->val<<"\t";
	if(l>0){
		stampa(x->sx,l-1);
		stampa(x->dx,l-1);
	}
}

template <typename U>
ostream & operator <<(ostream & os,bst<U> & b){
	Nodo<U> *n=b.root;
	if(n){
		int h=b.altezza(b.root);
		os<<"ALBERO DI ALTEZZA:"<<h<<endl;
		os<<"ROOT-->";
		for(int i=0;i<h;i++){
			stampa(n,i);
			cout<<endl;
		}
	}	
	else
		os<<"ALBERO VUOTO"<<endl;
	return os;
}

template <typename U>
ostream & operator <<(ostream & os,listaCircDoppia<U> & l){
	nodo<U> *iter=l.testa;
	if(iter){
		if(iter==l.coda){
			os<<"<--TESTA("<<l.testa->val<<"="<<l.coda->val<<")CODA-->";
		}
		else{
			os<<"<--TESTA("<<iter->val<<")";
			while(iter!=l.coda){
				os<<"<--"<<iter->val<<"-->";
				iter=iter->succ;
			}
			os<<"<--"<<l.coda->val<<"-->("<<l.coda->val<<")CODA-->";
		}
			
	}
	else
		os<<"LISTA VUOTA"<<endl;
	return os;
}

int main(){
	ifstream in;
	ofstream out;
	in.open("lab.txt");
	out.open("output.txt");
	for(int i=0;i<6;i++){
		string struttura;
		in>>struttura;
		string type;
		in>>type;
		if(struttura=="BST"){
			if(type=="int"){
				bst<int> *b=new bst<int>;
				b->insert(10);
				out<<b->getRoot()<<endl;
			}
			else{
				if(type=="char"){
					bst<char> *b=new bst<char>;
					b->insert('c');
					out<<b->getRoot()<<endl;
				}
				else{
					bst<double> *b=new bst<double>;
					b->insert(1.23);
					out<<b->getRoot()<<endl;
				}
			}
		}
		else{
			if(type=="int"){
				listaCircDoppia<int> *l=new listaCircDoppia<int>;
				l->inserTesta(12);
				out<<l->getCoda()<<endl;
			}
			else{
				if(type=="char"){
					listaCircDoppia<char> *l=new listaCircDoppia<char>;
					l->inserTesta('s');
					out<<l->getCoda()<<endl;
				}
				else{
					listaCircDoppia<double> *l=new listaCircDoppia<double>;
					l->inserTesta(1.21);
					out<<l->getCoda()<<endl;
				}
			}
		}
	}
}




