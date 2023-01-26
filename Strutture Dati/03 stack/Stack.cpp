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

class stack{
	nodo *top;
	nodo *coda;
	public:
		stack(){
			top=NULL;
			coda=NULL;
		}
		~stack(){
			nodo *iter=this->coda;
			while(iter!=NULL){
				nodo *n=iter->succ;
				delete iter;
				iter=n;
			}
		}
		void push(int x){
			nodo *nuovo=new nodo;
			nuovo->val=x;
			nuovo->succ=NULL;
			
			if(coda){
				this->top->succ=nuovo;
				this->top=nuovo;
			}
			else
				this->top=this->coda=nuovo;	
		}
		int pop(){
			nodo *iter=this->coda;
			if(iter){
				while(iter->succ!=this->top){
					iter=iter->succ;
				}
				int n=iter->succ->val;
				delete iter->succ;
				iter->succ=NULL;
				this->top=iter;
				return n;
			}
			else
				cout<<"PILA VUOTA IMPOSSIBILE RIMUOVERE"<<endl;
		}
		friend ostream & operator <<(ostream & os,stack & s);
};

ostream & operator <<(ostream & os,stack & s){
	nodo *iter=s.coda;
	if(iter){
		if(iter==s.top){
			os<<"CODA=TOP  "<<iter->val<<endl;	
		}
		else{
			os<<"CODA["<<s.coda->val<<"]"<<endl;
			iter=iter->succ;
			while(iter!=s.top){
				os<<"["<<iter->val<<"]"<<endl;
				iter=iter->succ;
			}
			os<<"TOP["<<s.top->val<<"]"<<endl;
		}
	}
	else
		cout<<"PILA VUOTA"<<endl;
	return os;
}

int main(){
	stack s;
	cout<<s<<endl;
	cout<<"PUSH"<<endl;
	s.push(3);
	s.push(5);
	s.push(7);
	s.push(9);
	s.push(45);
	cout<<s<<endl;
	cout<<"POP"<<endl;
	int x=s.pop();
	cout<<"ELEMENTO PRELEVATO:"<<x<<endl;
	cout<<s<<endl;
	cout<<"POP"<<endl;
	int y=s.pop();
	cout<<"ELEMENTO PRELEVATO:"<<y<<endl;
	cout<<s<<endl;
}



