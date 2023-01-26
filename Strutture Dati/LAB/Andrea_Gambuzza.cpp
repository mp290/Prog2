#include <iostream>
#include <fstream>
#include <string>

using namespace std;
template <class T>
class Nodo{
	public:
		T val;
		Nodo<T>* right;
		Nodo<T>* left;
		Nodo<T>* parent;
};

template <class H>
class BST{
	Nodo<H>* root;
	
	public:
		BST(){root = NULL;}
		
		void insert(H valore){
			Nodo<H>* nuovo = new Nodo<H>;
			nuovo->val = valore;
			nuovo->right = nuovo->left = NULL;
			Nodo<H>* x = root;
			Nodo<H>* y = NULL;
			
			while(x != NULL){
				y = x;
				if(valore > x->val)
					x = x->right;
				else 
					x = x->left;
			}
			nuovo->parent = y;
			if(y == NULL)
				root = nuovo;
			else if(valore > y->val)
				y->right = nuovo;
			else
				y->left = nuovo;
		}
	
		int altezza(Nodo<H>* p ) const{
			if(p == NULL)
				return 0;
			int lh = altezza(p->left);
			int rh = altezza(p->right);
			
			if(lh > rh)
				return (lh+1);
			else
				return (rh+1);
		}
	
		 
		
		Nodo<H>* ricerca(int valore){
			Nodo<H>* p = root;
			while(p->val != valore){
				if(p == NULL)
					return NULL;
				if(valore > p->val)
					p = p->right;
				else 
					p = p->left;
				} 
				return p;
			}
	
		int distanza(Nodo<H>* n1, Nodo<H>* radice){ 
			Nodo<H>* aux = radice;
			int n = 0;
			while( aux != n1){
				if(n1->val > aux->val)
					aux = aux->right;
				else 
					aux = aux->left;
				n++;
			}
			return n;
		}
	
	
		int DistanzaTraN(H val1, H val2){
			Nodo<H>* n1 = ricerca(val1);
			Nodo<H>* n2 = ricerca(val2);
			int dis = 0;
			if(n1 == NULL || n2 == NULL)
				return 0;
			
			else if((n1->val > root->val && n2->val > root->val ) || (n1->val < root->val && n2->val < root->val )){
				Nodo<H>* aux = root;
				while(( n1->val > aux->val && n2->val > aux->val) || (n1->val < aux->val && n2->val < aux->val) ){
					if(aux == n1)
						dis = distanza(n2,aux);
					else if( aux == n2)
						dis = distanza(n1,aux);
					
					if(n1->val > aux->val)
						aux = aux->right;
					else 
						aux = aux->left;
				}
				dis = distanza(n1,aux)+distanza(n2,aux);
			}
			
			else
				return distanza(n1,root) + distanza(n2,root);
		
		return dis;
		}
	
	
		template <class V>
		friend ostream &operator<<(ostream & os, const BST<V> & a);
	
	
};

template <class I>
void printlevel(Nodo<I>* p, int level){
	if(p == NULL){
		if(level == 0)
			cout<<"\t";
		return;
	}
	
	if(level == 0)
		cout<<p->val<<"\t";
	else if(level > 0){
		printlevel(p->left, level-1);
		printlevel(p->right, level-1);
	}
}


template <class V>
ostream &operator<<(ostream & os, const BST<V> & a){
	int h = a.altezza(a.root);
	cout<<"Albero di altezza: "<<h<<endl;
	for(int i = 0; i<h; i++){
		printlevel(a.root, i);
		cout<<endl;
	} 
	return os;
}


int main(){
	ifstream file;
	file.open("input.txt", std::ifstream::in);
	while(!file.eof()){
		string s;
		getline(file, s, ' ');
		if( s == "int"){
			BST<int> albero;
			string n;
			getline(file, n, ' ');	 		
			for(int i = 0; i<stoi(n); i++){
				string scarto;
				string ins;
				getline(file, scarto, ':');
				getline(file, ins, ' ');
				int v = stoi(ins);
				albero.insert(v);
				
			}
			string n1, n2;
			getline(file, n1, ' ');
			getline(file, n2);
			cout<<albero<<endl;
			cout<<albero.DistanzaTraN(stoi(n1), stoi(n2))<<endl;
		}
		else if( s == "char"){
			BST<char> albero;
			string n;
			getline(file, n, ' ');			
			for(int i = 0; i<stoi(n); i++){
				string scarto;
				string ins;
				getline(file, scarto, ':');
				getline(file, ins, ' ');
				char v = ins[0];
				albero.insert(v);
				
			}
			string n1, n2;
			getline(file, n1, ' ');
			getline(file, n2);
			cout<<albero<<endl;
			cout<<albero.DistanzaTraN(n1[0], n2[0])<<endl;
			}
			
			
			
			
		}
		
		
}
	
	
