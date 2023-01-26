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
	int fronte;
	int fine;
	int size;
	int c;
	public:
		coda(int s){
			size=s;
			arr=new int[size];
			fronte=0;
			fine=0;
			c=0;
		}
		~coda(){
			delete []arr;
		}
		bool isFull(){
			if(c==size)
				return true;
			else
				return false;
		}
		bool isEmpty(){
			if(c==0)
				return true;
			else
				return false;
		}
		int getFronte(){
			return arr[fronte];
		}
		void enqueue(int x){
			if(isFull())
				cout<<"CODA PIENA"<<endl;
			else{
				arr[fine]=x;
				fine++;
				c++;
			}
		}
		int dequeue(){
			if(isEmpty())
				cout<<"CODA VUOTA"<<endl;
			else{
				int x=arr[fronte];
				fronte++;
				c--;
				return x;
			}
		}
		friend ostream & operator <<(ostream & os,coda & c);
};

ostream & operator <<(ostream & os,coda & c){
	if(c.isEmpty())
		os<<"CODA VUOTA"<<endl;
	else{
		os<<"FRONTE-->";
		for(int i=c.fronte;i<c.fine;i++){
			os<<"["<<c.arr[i]<<"]";
		}
		os<<"<--FINE";
	}
	return os;
}

int main(){
	coda c(5);
	cout<<c<<endl;
	if(c.isEmpty())
		cout<<"VUOTA"<<endl;
	if(c.isFull())
		cout<<"PIENA"<<endl;
	cout<<"////////////////////"<<endl;
	c.enqueue(10);
	c.enqueue(9);
	c.enqueue(6);
	int q=c.getFronte();
	cout<<"FRONTE:"<<q<<endl;
	c.enqueue(3);
	c.enqueue(1);
	cout<<c<<endl;
	if(c.isEmpty())
		cout<<"VUOTA"<<endl;
	if(c.isFull())
		cout<<"PIENA"<<endl;
	cout<<"////////////////////"<<endl;
	int x=c.dequeue();
	cout<<"RIMOSSO :"<<x<<endl;
	cout<<c<<endl;
	int y=c.dequeue();
	cout<<"RIMOSSO :"<<y<<endl;
	cout<<c<<endl;
	int as=c.getFronte();
	cout<<"FRONTE:"<<as<<endl;
	int z=c.dequeue();
	cout<<"RIMOSSO :"<<z<<endl;
	cout<<c<<endl;
	int a=c.dequeue();
	cout<<"RIMOSSO :"<<a<<endl;
	cout<<c<<endl;
	int v=c.dequeue();
	cout<<"RIMOSSO :"<<v<<endl;
	cout<<c<<endl;
	if(c.isEmpty())
		cout<<"VUOTA"<<endl;
	if(c.isFull())
		cout<<"PIENA"<<endl;
	cout<<"////////////////////"<<endl;
	int s=c.dequeue();
		int wer=c.getFronte();
	cout<<"FRONTE:"<<wer<<endl;
}



