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
	nodo<T> min(nodo<T> x){
		nodo<T> m=x;
		while(m->sx!=NULL){
			m=m->sx;
		}
		return m;
	}
	public:
		bst(){
			root=NULL;
		}
		void insert(T x){
			nodo<T> *nuovo=new nodo<T>;
			nuovo->val=x;
			nuovo->sx=nuovo->dx=NULL;
			
			if(this->root){
				nodo<T> *iter=this->root;
				nodo<T> *n;
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
		int altezza(nodo<T> *x){
			if(x==0)
				return 0;
			
			int l=altezza(x->sx);
			int r=altezza(x->dx);
			if(l>r)
				return l+1;
			else
				return r+1;
		}
		nodo<T> succ(T x){
			nodo<T> *iter=this->root;
			while(iter->val!=x){
				if(x<iter->val)
					iter=iter->sx;
				else
					iter=iter->dx;
			}	
			
			if(iter->dx!=NULL)
				return min(iter->dx);
			else{
				nodo<T> *s=iter->padre;
				while((s!=NULL)&&(iter==s->dx)){
					iter=s;
					s=s->padre;
				}
				return s;
			}	
		}
		int distSucc(T x){
			int c=0;
			nodo<T> *iter=this->root;
			while(iter->val!=x){
				if(x<iter->val)
					iter=iter->sx;
				else
					iter=iter->dx;
			}	
			
			if(iter->dx!=NULL){
				while(iter->sx!=NULL){
					c++;
					iter=iter->sx;
				}
				return c;
			}
			else{
				nodo<T> *s=iter->padre;
				while((s!=NULL)&&(iter==s->sx)){
					c++;
					iter=s;
					s=s->padre;
				}
				return c;
			}
			return 0;
		}
		template <typename U>
		friend ostream & operator<<(ostream & os,bst<U> & b);
};

template <typename U> 
ostream & operator<<(ostream & os,bst<U> & b){
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

template <typename T> void stampa(nodo<T> *x,int l){
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

int main(){
	bst<int> i;
	cout<<"BST INTERI"<<endl;
	i.insert(10);
	i.insert(9);
	i.insert(15);
	i.insert(13);
	i.insert(7);
	i.insert(11);
	i.insert(5);
	i.insert(6);
	i.insert(16);
	i.insert(1);
	cout<<i<<endl;
	int x;
	cout<<"INSERISCI IL VALORE DEL NODO DI CUI VUOI LA DISTANZA DEL SUCCESSORE:"<<endl;
	cin>>x;
	int y=i.distSucc(x);
	cout<<"LA DISTANZA E' "<<y<<endl;
	
		bst<char> c;
	cout<<"BST CHAR"<<endl;

	c.insert('d');
	c.insert('e');
		c.insert('f');
			c.insert('a');
	c.insert('b');
	c.insert('c');
	c.insert('p');
	c.insert('l');
	c.insert('w');
	c.insert('n');
	c.insert('o');
	cout<<c<<endl;
	char z;
	cout<<"INSERISCI IL VALORE DEL NODO DI CUI VUOI LA DISTANZA DEL SUCCESSORE:"<<endl;
	cin>>z;
	int q=c.distSucc(z);
	cout<<"LA DISTANZA E' "<<q<<endl;
	
}



