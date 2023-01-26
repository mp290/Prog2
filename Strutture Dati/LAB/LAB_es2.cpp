#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <typeinfo>

using namespace std;

template <typename T>
class nodo{
	public:
		T val;
		nodo<T> *sx;
		nodo<T> *dx;
		nodo<T> *padre;
};

template <typename T>
class bst{
	nodo<T> *root;
	int c=0;
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
	public:
		bst(){
			this->root=NULL;
		}
		void insert(T x){	
			nodo<T> *nuovo=new nodo<T>;
			nuovo->val=x;
			nuovo->sx=nuovo->dx=NULL;
			
			if(this->root){
				nodo<T> *iter=this->root;
				nodo<T> *n;
				while(iter!=NULL){
					if(iter->val==x){
						if((c%2)==0)
							iter=iter->sx;
						else
							iter=iter->dx;
					}
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
				c++;
			}
			else{
				nuovo->padre=NULL;
				this->root=nuovo;
				c++;
			}
		}
		template <typename U>
		friend ostream & operator <<(ostream & os,bst<U> & b);
};

template <typename U>
void stampa(nodo<U> *x,int l){
	if(x==NULL){
		if(l==0)
			cout<<"__\t";
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
	if(b.root){
		int h=b.altezza(b.root);
		os<<"ALBERO DI ALTEZZA:"<<h<<endl;
		os<<"ROOT-->";
		for(int i=0;i<h;i++){
			stampa(b.root,i);
			cout<<endl;
		}
	}
	else
		cout<<"ERRORE"<<endl;
	return os;
}

int main(){
	bst<int> bint;
	cout<<bint<<endl;
	bint.insert(10);
	bint.insert(8);
	bint.insert(12);
	bint.insert(9);
	bint.insert(11);
	bint.insert(13);
	bint.insert(7);
	cout<<bint<<endl;
	bint.insert(22);
	bint.insert(2);
	bint.insert(10);
	bint.insert(10);
	bint.insert(12);	
	bint.insert(12);
	bint.insert(8);
	bint.insert(8);
	bint.insert(123);
	cout<<bint<<endl;

}



