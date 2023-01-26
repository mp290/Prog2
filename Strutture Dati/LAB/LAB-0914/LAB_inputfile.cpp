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
		nodo<T> *sx;
		nodo<T> *dx;
		nodo<T> *padre;
		T val;
};

template <typename T>
class bst{
	nodo<T> *root;
	void preorder(nodo<T> *x){
		if(x){
			cout<<x->val<<"\t";
			preorder(x->sx);
			preorder(x->dx);
		}
	}
	int distanza(T x,T y){
		int c=0;
		nodo<T> *iter=this->root;
		nodo<T> *a=NULL;//NODO CON VALORE X;
		while(iter!=NULL){
			if(iter->val==x)
				a=iter;
			if(x<iter->val)
				iter=iter->sx;
			else
				iter=iter->dx;
		}
			
		if(a){
			while(a!=NULL){
				if(a->val==y)
					return c;
				if(y<a->val){
					a=a->sx;
					c++;
				}
				else{
					a=a->dx;
					c++;
				}
			}
			return -1;
		}
		else
			return -1;
	}
	public:
		bst(){
			this->root=NULL;
		}
		void visit(){
			preorder(this->root);
		}
		void insert(T x){
			nodo<T> *nuovo=new nodo<T>;
			nuovo->sx=nuovo->dx=NULL;
			nuovo->val=x;
			
			if(this->root){
				nodo<T> *iter=this->root;
				nodo<T> *n=NULL;
				while(iter!=NULL){
					n=iter;
					if(x<iter->val)
						iter=iter->sx;
					else
						iter=iter->dx;
				}
				if(n){
					nuovo->padre=n;
					if(x<n->val)
						n->sx=nuovo;
					else
						n->dx=nuovo;
				}
			}
			else{
				nuovo->padre=NULL;
				this->root=nuovo;	
			}
		}
		int distanzaChiavi(T h,T k){
			if(this->root->val==k)//K E' LA RADICE
				return distanza(k,h);
			
			if(this->root->val==h)//H E' LA RADICE
				return distanza(h,k);
			else{
				if(((h<this->root->val)&&(k<this->root->val))||((h>this->root->val)&&(k>this->root->val))){//H E K STANNO NELLO STESSO SOTTOALBERO SX
					int c=distanza(h,k);//H PRECEDE K
					if(c!=-1)
						return c;
					else
						return distanza(k,h);//K PRECEDE H
				}
				else{//H E K NON SONO NELLO STESSO SOTTOALBERO
					return (distanza(this->root->val,h)+distanza(this->root->val,k));
				}
			}
		}
		int altezza(nodo<T> *x){
			if(x==NULL)
				return 0;
			int l=altezza(x->sx);
			int r=altezza(x->dx);
			if(l>r)
				return l+1;
			else
				return r+1;
		}
		template <typename U>
		friend ostream & operator <<(ostream & os,bst<U> & b);
};

template <typename U>
void stampa(nodo<U> *x,int l){
	if(x==NULL){
		if(l==0)
			cout<<"--\t";
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
	nodo<U> *r=b.root;
	if(r){
		int h=b.altezza(r);
		os<<"ALBERO DI ALTEZZA:"<<h<<endl;
		os<<"ROOT-->";
		for(int i=0;i<h;i++){
			stampa(r,i);
			os<<endl;
		}
	}
	else
		cout<<"ALBERO VUOTO"<<endl;
	return os;
}

int main(){
	ifstream in;
	ofstream out;
	in.open("input.txt");
	out.open("output.txt");
	for(int task=0;task<6;task++){
		string type;
		in>>type;
		int N;
		in>>N;
		if(type=="int"){
			bst<int> *bi=new bst<int>;
			for(int i=0;i<N;i++){
				char c;
				in>>c;
				in>>c;
				in>>c;
				in>>c;
				int a;
				in>>a;
				bi->insert(a);
			}
			cout<<"VISIT:";
			bi->visit();
			cout<<endl;
			int h,k;
			in>>h;
			in>>k;
			out<<bi->distanzaChiavi(h,k);
		}
		else{
			bst<char> *bc=new bst<char>;
			for(int i=0;i<N;i++){
				char c;
				in>>c;
				in>>c;
				in>>c;
				in>>c;
				char a;
				in>>a;
				bc->insert(a);
			}
			cout<<"VISIT:";
			bc->visit();
			cout<<endl;
			char h,k;
			in>>h;
			in>>k;
			out<<bc->distanzaChiavi(h,k);
		}
	}
}



