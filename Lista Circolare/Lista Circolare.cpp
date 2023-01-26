#include <iostream>

using namespace std;

class nodo {
public:
	int val;
	nodo* succ;
};

class listaCircolare {
	nodo *testa;
	nodo *coda;
public:
	listaCircolare() {
		cout << "CREO LISTA"<<endl;
		testa = NULL;
		coda = NULL;
	}

	void inserTesta(int x) {
		nodo* nuovo = new nodo;
		nuovo->val = x;
		if (this->testa) {
			nuovo->succ = this->testa;
			this->testa = nuovo;
		}
		else {
			this->testa = nuovo;
			this->testa->succ = this->coda=nuovo;
		}
	}

	void inserCoda(int x) {
		nodo* nuovo = new nodo;
		nuovo->val = x;
		nuovo->succ = this->testa;
		if (this->testa) {
			this->coda->succ = nuovo;
			this->coda = nuovo;
		}
		else {
			this->coda = this->testa = nuovo;
		}
	}

	nodo* ricerca(int x) {
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
				cout << "VALORE NON TROVATO"<<endl;
				return NULL;
			}
		}
		else {
			cout << "LA LISTA E' VUOTA"<<endl;
			return NULL;
		}
		return NULL;
	}

	void inser(int x, nodo *pre) {
		nodo* nuovo = new nodo;
		nuovo->val = x;
		if (pre == this->coda || pre == NULL) {
			inserCoda(x);
		}
		else {
			nuovo->succ = pre->succ;
			pre->succ = nuovo;
		}
	}

	void rimuovi(int x) {
		nodo* daDel = ricerca(x);
		nodo* iter = this->testa;
		if (iter) {
			if (daDel) {
				if (daDel == this->coda) {//se elemento da eliminare è la coda
					cout << "RIMUOVO CODA" << endl;
					while (iter->succ != coda) {
						iter = iter->succ;
					}
					iter->succ = testa;
					delete daDel;
					coda = iter;					
				}
				else if (daDel->val == this->testa->val) {//se elemento da eliminare è testa
					cout << "RIMUOVO TESTA" << endl;
					coda->succ = daDel->succ;
					testa = daDel->succ;
					delete daDel;
				}
				else {// caso generico
					cout << "RIMUOVO GENERICO NODO" << endl;
					while (iter->succ != daDel) {
						iter=iter->succ;
					}
					iter->succ = daDel->succ;
					delete daDel;
				}
			}
			else {
				cout << "NON RIMUOVO NULLA" << endl;
			}
		}
	}

	friend ostream& operator<<(ostream& os, listaCircolare& l); //overloading
};

ostream& operator<<(ostream& os, listaCircolare& l)
{
	nodo* iter = l.testa;  //passo la testa ad un nuovo nodo
	if (iter) {
		os << "-->";
		while (iter != l.coda) {
			os<< iter->val << "->";
			iter = iter->succ;
		}
		os << l.coda->val << "-->TESTA(" << l.testa->val<<")"<<endl;
	}
	else {
		os << "LISTA VUOTA" << endl;
	}
	return os;
}

int main()
{
	listaCircolare l;

	cout << l;

	l.inserTesta(3);
	l.inserTesta(2);
	l.inserTesta(1);

	cout << l;

	l.inserCoda(4);
	l.inserCoda(5);
	l.inserCoda(6);

	cout << l;
	
	nodo* n = l.ricerca(9);
	l.inser(7, n);
	cout << l;

	l.rimuovi(1);
	cout << l;
	l.rimuovi(3);
	cout << l;
	l.rimuovi(7);
	cout << l;
	l.rimuovi(2);
	cout << l;
	l.rimuovi(6);
	cout << l;
	l.rimuovi(4);
	cout << l;
	l.rimuovi(6);
	cout << l;
}