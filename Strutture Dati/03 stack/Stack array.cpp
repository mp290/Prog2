#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <typeinfo>

using namespace std;

class stack{
	int *arr;
	int c;
	int numEl=0;
	public:
		stack(int size){
			arr=new int[size];
			c=size;
		}
		~stack(){
			delete []arr;
		}
		void push(int x){
			if(numEl<c){
				arr[numEl]=x;
				numEl++;
			}
			else
				cout<<"PILA PIENA"<<endl;
		}
		int pop(){
			if(numEl==0)
				cout<<"PILA VUOTA"<<endl;
			else{
				int x=arr[numEl-1];
				numEl--;
				return x;
			}
		}
		friend ostream & operator<<(ostream & os,stack & s);
};

ostream & operator<<(ostream & os,stack & s){
	if(s.numEl==0)
		cout<<"PILA VUOTA"<<endl;
	else{
		os<<"TOP=";
		for(int i=(s.numEl-1);i>0;i--){
			os<<"["<<s.arr[i]<<"]"<<endl;
		}
		os<<"CODA=["<<s.arr[0]<<"]"<<endl;
	}
	return os;
}

int main(){
	stack s(7);
	cout<<s<<endl;
	cout<<"PUSH"<<endl;
	s.push(6);
	s.push(2);
	s.push(8);
	s.push(9);
	cout<<s<<endl;
	cout<<"POP"<<endl;
	int x=s.pop();
	cout<<"ELEMENTO PRELEVATO:"<<x<<endl;
	cout<<s<<endl;
	int y=s.pop();
	cout<<"ELEMENTO PRELEVATO:"<<y<<endl;
	cout<<s<<endl;
	s.push(63);
	s.push(22);
	s.push(83);
	s.push(92);
	s.push(0);
	s.push(23);
	cout<<s<<endl;
	
}



