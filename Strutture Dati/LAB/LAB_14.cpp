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
	void preorder(nodo<T> *x){
		if(x){
			cout<<x->val<<"\t";
			preorder(x->sx);
			preorder(x->dx);
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
	public:
		bst(){
			this->root=NULL;
		}
		void visit(){
			preorder(this->root);
		}
		void insert(T x){
			nodo<T> *nuovo=new nodo<T>;
			nuovo->val=x;
			nuovo->sx=nuovo->dx=NULL;
			
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
		int distanzaChiavi(T x,T y){
			int c=0;
			nodo<T> *iter=this->root;
			//UNA DELLE CHIAVI E' LA RADICE
			if(iter->val==x){
				if(x>y)
					iter=iter->sx;
				else
					iter=iter->dx;
				c++;
				while(iter->val!=y){
					if(y<iter->val)
						iter=iter->sx;
					else
						iter=iter->dx;
					c++;
					}
				return c;
			}
			if(iter->val==y){
				if(y>x)
					iter=iter->sx;
				else
					iter=iter->dx;
				c++;
				while(iter->val!=x){
					if(x<iter->val)
						iter=iter->sx;
					else
						iter=iter->dx;
					c++;
				}
				return c;
			}
			if((x<iter->val)&&(y<iter->val)){//ENTRAMBE SI TROVANO NEL SOTTOALBERO SX
				if(x>y){
					while(iter->val!=x){
						if(x<iter->val)
							iter=iter->sx;
						else
							iter=iter->dx;
					}
					nodo<T> *s=iter;
					while(s->val!=y){
						if(y<s->val)
							s=s->sx;
						else
							s=s->dx;
						c++;
					}
					return c;
				}
				else{
					while(iter->val!=y){
						if(y<iter->val)
							iter=iter->sx;
						else
							iter=iter->dx;
					}
					nodo<T> *s=iter;
					while(s->val!=x){
						if(x<s->val)
							s=s->sx;
						else
							s=s->dx;
						c++;
					}
					return c;
				}
			}
			else{
				if((x>iter->val)&&(y>iter->val)){//ENTRAMBE SI TROVANO NEL SOTTOALBERO DX
					if(x<y){
						while(iter->val!=x){
							if(x<iter->val)
								iter=iter->sx;
							else
								iter=iter->dx;
						}
						nodo<T> *s=iter;
						while(s->val!=y){
							if(y<s->val)
								s=s->sx;
							else
								s=s->dx;
							c++;
						}
						return c;
					}
					else{
						while(iter->val!=y){
							if(y<iter->val)
								iter=iter->sx;
							else
								iter=iter->dx;
						}
						nodo<T> *s=iter;
						while(s->val!=x){
							if(x<s->val)
								s=s->sx;
							else
								s=s->dx;
							c++;
						}
						return c;
					}
				}
				else{//SI TROVANO IN  UNA A DX UNA A SX
					while(iter->val!=x){
						if(x<iter->val)
							iter=iter->sx;
						else							
							iter=iter->dx;
						c++;
					}
					nodo<T> *i=this->root;
					while(i->val!=y){
						if(y<i->val)
							i=i->sx;
						else
							i=i->dx;
						c++;
					}
					return c;
				}
			}
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
		os<<"ALBERO VUOTO"<<endl;
	return os;
}

int main(){
	bst<int> b;
	cout<<b<<endl;
	b.insert(10);
	b.insert(20);
	b.insert(5);
	b.insert(15);
	b.insert(21);
	b.insert(8);
	b.insert(2);
	b.insert(24);
	b.insert(1);
	cout<<b<<endl;
	cout<<"VISIT:\t";
	b.visit();
	cout<<endl;
	int x,y;
	cout<<"INSERISCI La 1 CHIAVE:"<<endl;
	cin>>x;
	cout<<"INSERISCI La 2 CHIAVE:"<<endl;
	cin>>y;
	cout<<"LA DISTANZA E':"<<b.distanzaChiavi(x,y)<<endl;
}



