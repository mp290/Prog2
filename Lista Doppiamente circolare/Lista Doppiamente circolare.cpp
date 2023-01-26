// Lista doppiamente circolare.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <typeinfo>

using namespace std;

class nodo {
public:
	int val;
	nodo* succ;
	nodo* prec;
};

class listaDoppiamenteCircolare {
	nodo* testa;
	nodo* coda;
public:
	listaDoppiamenteCircolare() {
		cout << "CREO LISTA" << endl;
		testa = NULL;
		coda = NULL;
	}

	void inserTesta(int x) {
		nodo* nuovo = new nodo;
		nuovo->val = x;

		if (this->testa) {
			coda->succ = nuovo;
			nuovo->succ = testa;
			this->testa = nuovo;
		}
		else {
			nuovo->prec = nuovo;
			nuovo->succ = nuovo;
			this->testa = this->coda=nuovo;
		}
	}


	void inserCoda(int x) {
		nodo* nuovo = new nodo;
		nuovo->val = x;
		if (this->testa) {
			nuovo->prec = this->coda;
			nuovo->succ = this->testa;
			this->coda->succ = nuovo;
			this->testa->prec = nuovo;
			this->coda = nuovo;
		}
		else {
			inserTesta(x);
		}
		
	}

	nodo *ricerca(int x) {
		nodo* iter = this->testa;
		if (iter) {
			while (iter != coda) {
				if (iter->val == x) {
					return iter;
				}
				else {
					iter = iter->succ;
				}
			}
			if (this->coda->val == x) {
				return this->coda;
			}
			else {
				cout << "VALORE NON TROVATO" << endl;
				return NULL;
			}
		}
		else {
			cout << "LA LISTA E' VUOTA" << endl;
			return NULL;
		}
		return NULL;
	}


	void rimuovi(int x) {
		nodo* daDel = ricerca(x);//cerco il nodo da cancellare
		nodo* t = this->testa;//prendo la testa
		//nodo* c=this->coda->prec;
		if (t) {//controllo la testa
			if (t->val == x) {//se il valore si trova in testa
				this->testa = t->succ;//il successivo di t, sarà la nuova testa
				this->testa->prec = coda;//il precedente della testa è null
				delete t;//eliminiamo il nodo
			}


			else if (daDel==coda) {//se non è in testa, controlliamo che non sia in coda	
				this->coda->prec->succ = testa;
				coda = this->coda->prec;
				delete daDel;
				
			}
			else if (daDel) {//se non è ne in coda, ne in testa, è in mezzo
				nodo* s = t->succ;
				while (s->val != x) { 
					t = t->succ;
					s = s->succ;
				}
				t->succ = s->succ;
				s->succ->prec = t;
				delete s;
			}

		}

	}


	friend ostream& operator<<(ostream& os, listaDoppiamenteCircolare& l); //overloading
};

ostream& operator<<(ostream& os, listaDoppiamenteCircolare& l)
{
	nodo* iter = l.testa;  //passo la testa ad un nuovo nodo
	if (iter) {
		os << "->CODA("<<l.coda->val<<")";
		while (iter != l.coda) {
			os <<"<-"<<iter->val << "->";
			iter = iter->succ;
		}
		os <<"<-"<< l.coda->val << "->TESTA(" << l.testa->val << ")-->"<<endl;
	}
	else {
		os << "LISTA VUOTA" << endl;
	}
	return os;
}


int main() {

	listaDoppiamenteCircolare l;

	l.inserTesta(3);
	l.inserTesta(2);
	l.inserTesta(1);
	cout<<l;

	l.inserCoda(4);
	cout << l;
	l.inserCoda(5);
	cout << l;
	l.inserCoda(6);
	cout << l;

	nodo* n = l.ricerca(4);

	l.rimuovi(4);
	cout << l;


}
