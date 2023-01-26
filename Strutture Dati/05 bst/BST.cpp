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
		nodo *sx;
		nodo *dx;
		nodo *padre;
};

class BST{
	nodo *root;
	int numEl=0;
	void Preorder(nodo *x){//RAD SX DX
		if(x){
			cout<<x->val<<"\t";
			Preorder(x->sx);
			Preorder(x->dx);
		}
	}
	void Postorder(nodo *x){//SX DX RAD
		if(x){
			Postorder(x->sx);
			Postorder(x->dx);
			cout<<x->val<<"\t";
		}
	}
	void Inorder(nodo *x){//SX RAD DX
		if(x){
			Inorder(x->sx);
			cout<<x->val<<"\t";
			Inorder(x->dx);
		}
	}
	void canc(nodo *x){
		nodo *y;
		
		if(x->sx==NULL)
			trapianta(x,x->dx);
		else{
			if(x->dx==NULL)
				trapianta(x,x->sx);
			else{
				y=min(x->dx);
				if(y->padre!=x){
					trapianta(y,y->dx);
					y->dx=x->dx;
					y->dx->padre=y;
				}
			}
			trapianta(x,y);
			y->sx=x->sx;
			y->sx->padre=y;
		}
		delete x;
	}
	nodo *min(nodo *x){
		nodo *min=x;
		while(min->sx!=NULL){
			min=min->sx;
		}
		return min;
	}
	nodo *max(nodo *x){
		nodo *max=x;
		while(max->dx!=NULL){
			max=max->dx;
		}
		return max;
	}
	void trapianta(nodo *x,nodo *y){
		if(x->padre==NULL)
			this->root=y;
		else{
			if(x==x->padre->sx)
				x->padre->sx=y;
			else
				x->padre->dx=y;	
		}
		if(y!=NULL)
			y->padre=x->padre;
	}
	public:
		BST(){
			root=NULL;
		}
		void PreOrder(){
			Preorder(root);
		}
		void PostOrder(){
			Postorder(root);
		}
		void InOrder(){
			Inorder(root);
		}
		int Min(){//per il predecessore
			nodo *Min=min(this->root);
			return Min->val;
		}
		int Max(){//per il successore
			nodo *Max=max(this->root);
			return Max->val;
		}
		void insert(int x){
			nodo *nuovo=new nodo;
			nuovo->val=x;
			nuovo->sx=nuovo->dx=NULL;
			
			if(this->root==NULL){//SE E' LA RADICE
				nuovo->padre=NULL;
				this->root=nuovo;
			}
			else{
				nodo *iter=this->root;
				nodo *n;
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
		}
		bool cancella(int x){
			nodo *n=BST::ricerca(x);
			if(n){
				nodo *iter=this->root;
				while(iter!=NULL){
					if(x==iter->val){
						canc(iter);
						return true;
					}			
					if(x<iter->val)
						iter=iter->sx;
					else
						iter=iter->dx;
				}
			}
			else
				return false;
			
		}
		nodo *ricerca(int x){
			nodo *iter=this->root;
			if(iter){
				while(iter!=NULL){
					if(x==iter->val)
						return iter;
				
					if(x<iter->val)
						iter=iter->sx;
					else
						iter=iter->dx;
				}
				return NULL;
			}
			else
				cout<<"ERRORE"<<endl;
		}
		nodo *successore(int x){
			nodo *n=ricerca(x);
			if(n){
				if(n->dx!=NULL)
					return min(n->dx);
				else{
					nodo *s=n->padre;
					while((s!=NULL)&&(n==s->dx)){
						n=s;
						s=s->padre;
					}
					return s;
				}	
			}
			else{
				cout<<"NON TROVATO"<<endl;
				return NULL;
			}
		}
		int distanzaSucc(int x){
			int c=1;
			nodo *n=ricerca(x);
			if(n){
				if(n->dx!=NULL){
					nodo *min=n->dx;
					while(min->sx!=NULL){
						min=min->sx;
						c++;
					}
					return c++;
				}
				else{
					nodo *s=n->padre;
					while((s!=NULL)&&(n==s->dx)){
						n=s;
						s=s->padre;
						c++;
					}
					return c;
				}	
			}
			else{
				cout<<"NON TROVATO"<<endl;
				return NULL;
			}
		}
		nodo *predecessore(int x){
			nodo *n=ricerca(x);
			if(n){
				if(n->sx!=NULL)
					return max(n->sx);
				else{
					nodo *s=n->padre;
					while((s!=NULL)&&(n==s->sx)){
						n=s;
						s=s->padre;
					}
					return s;
				}	
			}
			else{
				cout<<"NON TROVATO"<<endl;
				return NULL;
			}
		}
		int distanzaPre(int x){
			int c=1;
			nodo *n=ricerca(x);
			if(n){
				if(n->sx!=NULL){
					nodo *max=n->sx;
					while(max->dx!=NULL){
						max=max->dx;
						c++;
					}
					return c++;
				}
				else{
					nodo *s=n->padre;
					while((s!=NULL)&&(n==s->sx)){
						n=s;
						s=s->padre;
						c++;
					}
					return c;
				}	
			}
			else{
				cout<<"NON TROVATO"<<endl;
				return NULL;
			}
		}
		int altezza(nodo *x){
			if(x==NULL)
				return 0;
				
			int left=altezza(x->sx);
			int right=altezza(x->dx);
			
			if(left>right)
				return left+1;
			else
				return right+1;
		}
		friend ostream & operator<<(ostream & os,BST & bst);
};

void stampa(nodo *x,int livello){
	if(x==NULL){
		if(livello==0)
			cout<<"_\t";
		return;
	}
	
	if(livello==0)
		cout<<x->val<<"\t";
			
	if(livello>0){
		stampa(x->sx,livello-1);
		stampa(x->dx,livello-1);
	}
}

ostream & operator<<(ostream & os,BST & bst){
	nodo *iter=bst.root;
	if(iter){
		os<<"ALBERO DI ALTEZZA: "<<bst.altezza(bst.root)<<endl;
		os<<"	ROOT-->";
		for(int i=0;i<bst.altezza(bst.root);i++){
			stampa(iter,i);
			cout<<endl;
		}
	}
	else
		cout<<"ERRORE"<<endl;
	return os;
}

int main(){
	BST bst;
	cout<<bst<<endl;
	bst.insert(20);
	bst.insert(10);
	bst.insert(25);
	bst.insert(8);
	bst.insert(15);
	bst.insert(23);
	bst.insert(27);
	bst.insert(6);
	bst.insert(9);
	bst.insert(13);
	bst.insert(22);
	bst.insert(26);
	bst.insert(30);
	cout<<bst<<endl;
	cout<<"PRE ORDER"<<endl;
	bst.PreOrder();
	cout<<endl;
	cout<<"POST ORDER"<<endl;
	bst.PostOrder();
	cout<<endl;
	cout<<"IN ORDER"<<endl;
	bst.InOrder();
	cout<<endl;
	int x,y;
	cout<<"INSERISCI ELEMENTO DA CERCARE:"<<endl;
	cin>>x;
	nodo *n=bst.ricerca(x);
	if(n)
		cout<<"TROVATO"<<endl;
	else
		cout<<"NON TROVATO"<<endl;
	cout<<"IL SUCCESSORE E':"<<bst.successore(x)->val<<endl;
	cout<<"LA DISTANZA DEL SUCCESSORE E':"<<bst.distanzaSucc(x)<<endl;
	cout<<"IL PREDECESSORE E':"<<bst.predecessore(x)->val<<endl;
	cout<<"LA DISTANZA DEL PREDECESSORE E':"<<bst.distanzaPre(x)<<endl;
	cout<<"IL MAX E':"<<endl;
	cout<<bst.Max()<<endl;
	cout<<"IL MIN E':"<<endl;
	cout<<bst.Min()<<endl;
	cout<<"INSERISCI ELEMENTO DA RIMUOVERE:"<<endl;
	cin>>y;
	bool q=bst.cancella(y);
	if(q==true)
		cout<<"RIMOSSO"<<endl;
	else
		cout<<"NON RIMOSSO"<<endl;
	cout<<bst<<endl;
}



