#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <typeinfo>

using namespace std;

template <class T> class nodo{
	public:
		T valore;
		nodo<T> *succ;
};

template <class T> class lista{
	nodo<T> *testa;
	public:
		lista(){
			testa=NULL;
		}
		~lista(){
			nodo<T>* iter=this->testa;
			while(iter!=NULL)	{
				nodo<T>* temp= iter->succ;
				delete iter;
				iter=temp;
			}
		}
		nodo<T> *getTesta(){
			return testa;
		}
		nodo<T> *search(T x){
			nodo<T>* p;
			for (p=this->testa; p!=NULL; p=p->succ){
				if (p->valore==x)
					return p;
			}
			return NULL;
		}
		void insert(T val){
			nodo<T>* nuovo= new nodo<T>;
			nuovo->valore=val;
			nuovo->succ=this->testa;
			this->testa=nuovo;
		}
		friend ostream & operator<<(ostream & os,const lista & ls){
			nodo<T>* iter=ls.testa;
			while (iter!=NULL) {
				os<< " " << iter->valore << "\t";
				iter=iter->succ;
			}
			return os;
		}
};

template <class H> class LGraph {
	private:
		int len, n, m;
		/*	len numero massimo di nodi
            n numero di nodi effettivo,
			m numero di archi effettivo,
		*/
		H **K;// lista di puntatori ad elementi di tipo H
		lista<int> **Adj; // lista di puntatori ad elementi di tipo Lista<int>

		int findIndex(H x) {
		// Trova l'indice associato al nodo
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}

	public:
		LGraph(int len) {
			this->len = len;
			n = m = 0;
			K = new H*[len];
			for(int i=0; i<len; i++)
                K[i] = NULL;
			Adj = new lista<int>*[len];
			for(int i=0; i<len; i++)
                // inizializzo ogni lista di adiacenza coma un Lista<int>
				Adj[i] = new lista<int>();
		}

		LGraph<H>* addNode(H k) {
		// Aggiunge un nodo al grafo (se non già presente)
			if(n==len) return this;
			if(findIndex(k)>=0) return this;
			K[n] = new H(k);
			n++;
			return this;
		}

		LGraph<H>* addEdge(H x, H y) {
		// Aggiunge un arco al grafo (se non già presente)
			int i = findIndex(x);
			int j = findIndex(y);
			if(i<0 || j<0) return this;
			if(!Adj[i]->search(j)) {
				Adj[i]->insert(j);
				m++;
			}
			return this;
		}

		void print() {
		    bool semplice = false; // seleziona la modalita' di stampa (vedi dopo)
			for(int i=0; i<n; i++) {
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				// VERSIONE 1 (semplice)
				 // stampo la lista degli indici (int) nella lista di adiacenza dell'elemento K[i]
				if(semplice)
                    cout << *Adj[i];
                else{
				// VERSIONE 2 (meno semplice)..
				// stampo lista di indici e valori dei nodi nella
				 // lista di adiacenza
				//      &(...) --> 'puntatore di (...)  '
				//      *(...) --> 'valore puntato da (...) '
                  //  Nodo<int>* iter =&(*Adj[i]->getTesta());
                    nodo<int>* iter =Adj[i]->getTesta();
                    //for(int c=0; iter!=NULL; iter=iter->succ, c++){
                    for(; iter!=NULL; iter=iter->succ){
                        cout << "\t(" << iter->valore << ", " << *K[iter->valore] << ")";
                    }
                }
				cout << endl;
			}
		}
};

int main(){
	

}



