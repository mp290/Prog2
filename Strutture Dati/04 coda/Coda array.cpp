#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <typeinfo>

using namespace std;

class coda{
	int *arr;
	int numEl;
	int size;
	int fronte;
	int fine;
	public:
		coda(int capacita){
			arr=new int[capacita];
			size=capacita;
			numEl=0;
			fronte=0;
			fine=1;
		}
		~coda(){
			delete []arr;
		}
		bool isFull(){
			if(numEl==size)
				return true;
			else
				return false;
		}
		bool isEmpty(){
			if(numEl==0)
				return true;
			else
				return false;
		}
		int getFront(){
			if(isEmpty()==false)
				return arr[fronte];
			else{
				cout<<"CODA VUOTA"<<endl;
				return -1;
			}
		}
		void enqueue(int x){
			if(isFull()==false){
				if(isEmpty()==true){
					arr[fronte]=x;
					numEl++;
				}
				else{
					arr[numEl]=x;
					numEl++;
					fine++;
				}
			}
			else
				cout<<"CODA PIENA"<<endl;
		}
		void dequeue(){
			if(isEmpty()==false){
				fronte++;
				numEl--;
			}
			else
				cout<<"CODA VUOTA"<<endl;
		}
		friend ostream & operator<<(ostream & os,coda & c);
};

ostream & operator<<(ostream & os,coda & c){
	if(c.isEmpty()==true)
		cout<<"CODA VUOTA"<<endl;	
	else{
		os<<"RAPPRESENTAZIONE SENZA INDICI"<<endl;
		os<<"FRONTE-->";
		for(int i=c.fronte;i<c.fine;i++){
			os<<"["<<c.arr[i]<<"] ";
		}
		os<<"["<<c.arr[c.fine]<<"]<--FINE"<<endl;
		
		os<<"RAPPRESENTAZIONE COMPLETA SENZA INDICI"<<endl;
		for(int i=0;i<c.fine;i++){
			if(i==c.fronte)
				os<<"FRONTE-->";
			os<<"["<<c.arr[i]<<"] ";
		}
		os<<"["<<c.arr[c.fine]<<"]<--FINE"<<endl;
		
		os<<"RAPPRESENTAZIONE CON INDICI"<<endl;
		os<<c.fronte<<")  FRONTE-->["<<c.arr[c.fronte]<<"]"<<endl;
		for(int i=c.fronte+1;i<c.fine;i++){
			os<<i<<")  ["<<c.arr[i]<<"]"<<endl;
		}
		os<<c.fine<<")  FINE-->["<<c.arr[c.fine]<<"]"<<endl;
		
		os<<"RAPPRESENTAZIONE COMPLETA CON INDICI"<<endl;
		for(int i=0;i<c.fine;i++){
			os<<i<<")  ";
			if(i==c.fronte)
				os<<"FRONTE-->";
			os<<"["<<c.arr[i]<<"]"<<endl;
		}
		os<<c.fine<<")  FINE-->["<<c.arr[c.fine]<<"]"<<endl;
	}
	return os;
}

int main(){
	coda c(7);
	cout<<c<<endl;
	if(c.isFull()==true)
		cout<<"CODA PIENA"<<endl;
	if(c.isEmpty()==true)
		cout<<"CODA VUOTA"<<endl;
	cout<<"///////////"<<endl;
	c.enqueue(5);
	c.enqueue(32);
	c.enqueue(2);
	c.enqueue(12);
	c.enqueue(21);
	c.enqueue(7);
	c.enqueue(87);
	cout<<c<<endl;
	if(c.isFull()==true)
		cout<<"CODA PIENA"<<endl;
	if(c.isEmpty()==true)
		cout<<"CODA VUOTA"<<endl;
	cout<<"FRONTE E':"<<c.getFront()<<endl;
	cout<<"///////////"<<endl;
	cout<<"RIMUOVO 3 ELEMENTO"<<endl;
	c.dequeue();
	c.dequeue();
	c.dequeue();
	if(c.isFull()==true)
		cout<<"CODA PIENA"<<endl;
	if(c.isEmpty()==true)
		cout<<"CODA VUOTA"<<endl;
	cout<<"FRONTE E':"<<c.getFront()<<endl;
	cout<<c<<endl;
}



