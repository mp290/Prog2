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
};

class lista {
	nodo* testa;
public:
	//costruttore lista
	lista() {
		testa = NULL;
	}

	//aggiungere un valore in testa 
	void inserTesta(int x) {
		nodo* nuovo = new nodo;
		nuovo->val = x;
		if (this->testa) { //se la testa c'è, inserisce un nuovo nodo prima della testa, quindi il nuovo nodo sarà la testa
			nuovo->succ = this->testa;
			this->testa = nuovo;
		}
		else {// la testa non è presente e quindi il nuovo nodo sarà la testa, e dopo non c'è nulla perchè è presente solo la testa
			nuovo->succ = NULL;
			this->testa = nuovo;
		}
	}

	void insertCoda(int x) {
		nodo* nuovo = new nodo;
		nuovo->val = x;
		nuovo->succ = NULL;
		if (this->testa) {
			nodo* iter = this->testa;
			while (iter->succ != NULL) {
				iter = iter->succ;
			}
			iter->succ = nuovo;
		}
		else {
			nuovo->succ = NULL;
			this->testa = nuovo;
		}
	}
	
	void inser(int x,nodo *prec) {

		nodo* nuovo = new nodo;
		nuovo->val = x;
		nuovo->succ = prec->succ;
		prec->succ = nuovo;
	}

	nodo* ricerca(int x) {
		nodo* iter = this->testa;
		if (iter) {
			while (iter!= NULL) {
				if (x == iter->val) {
					return iter;
				}
				else {
					iter = iter->succ;
				}					
			}
			return NULL;
		}
		else {
			cout << "LISTA VUOTA";
		}
		
	}

	//cancellazione nodo
	void rimuovi(int x) {
		nodo *daDel=ricerca(x);//da Delete, da cancellare
		nodo* iter = this->testa;
		if (daDel) {
			if (iter) {
				if (iter->val == x) {
					this->testa = iter->succ;
					delete iter;
				}
				else {
					nodo *s = iter->succ;
					while ((s != NULL) && s != daDel) {
						iter = iter->succ;
						s = s->succ;
					}
					iter->succ = s->succ;
					delete s;
				}
			}
		}
	}


	friend ostream& operator<<(ostream& os, lista& l);
	
};

ostream& operator<<(ostream& os, lista& l) {
	nodo* iter = l.testa;
	if (iter) {
		while (iter != NULL) {
			os << iter->val << "-->";
			iter = iter->succ;
		}
		os << "NULL";
	}
	else {
		cout << "LISTA VUOTA";
	}
	return os;
}

int main()
{
	lista l;
	l.inserTesta(3);
	l.inserTesta(2);
	l.inserTesta(1);

	cout << l<<endl;

	int x = 0;
	cout << "Inserisci il valore da cercare" << endl;
	cin >> x;

	nodo *nodocercato=l.ricerca(x);
	if (nodocercato) {
		cout << "TROVATO"<<endl;
	}
	else {
		cout << "NON TROVATO"<<endl;
	}

	int y = 0;
	cout << "Inserisci il valore da inserire" << endl;
	cin >> y;
	l.inser(y, nodocercato);
	cout << l << endl;
}