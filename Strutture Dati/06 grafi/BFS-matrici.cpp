#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <typeinfo>

using namespace std;

// definisco delle costanti per i colori dei nodi
#define W 0
#define G 1
#define B 2
#define inf len+1    // definisco un valore infinito
                    // (nessun cammino minimo puo' essere piu lungo di len)
                    
class coda{
	int *arr;
	int capacita;
	int fronte;
	int fine;
	int c;
	int getfronte(){
		if(isEmpty()){
        	cout << "Coda vuota!!!" << endl;
        	cout << "Operazione non riuscita." << endl;
        	return -1;
    	}
    	else
		{
        	return arr[fronte];
    	}
	}
	public:
		coda(int size){
			arr= new int[size];
 		    capacita=size;
   			fronte=0;
    		fine=-1;
    		c=0;
		}
		~coda(){
			delete[] arr;
		}
		int getsize() const{
			return c;
		}
		void enqueue(int x){
			if(isFull()){
        		cout << "Coda piena!!!"<<endl;
        		cout << "Operazione non riuscita."<<endl;
    		}
    		else
			{
        		//cout << "Inserisco " << x << endl;
        		fine = (fine+1)%capacita;
        		arr[fine] = x;
       		 	c++;
    		}
		}
		int dequeue(){
			int x;
			
			if(isEmpty()){
        		cout << "Lista vuota!!!" << endl;
        		cout << "Operazione non riuscita." << endl;
    		}
    		else
			{
        		//cout << "Rimuovo " << arr[fronte] << endl;
        		x=arr[fronte];
        		fronte = (fronte +1)%capacita;
        		c--;
        		return x;
    		}
		}
		bool isEmpty() const{
			return getsize()==0;
		}
		bool isFull() const{
			return getsize()==capacita;
		}
};

template <class H> class Mgraph {
	private:
		int len, n, m;
		/* 	n numero di nodi effettivo,
			m numero di archi effettivo,
			len numero massimo di nodi
		*/
		int **M; //MATRICE ADIACENZA-Contiene gli indici corrispondenti ai vari nodi
		H **K; //MATRICE INDICI-Contiene i valori di tipo H dei nodi
		int *p,*d;
		// d -> distanze dalla sorgente durante la BFS
		// p -> array dei predecessori
		
		int findIndex(H x) {// Associa un indice al nodo (se esiste)
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}
		
		void printPath(int x) {
			if(x==-1) return;
			if(p[x]==-1) cout << x;
			else {
				printPath(p[x]);
				cout << "->" << x;
			}
		}
	public:
		Mgraph(int len) {
			this->len = len;
			n = m = 0;
			d = new int[len]; /* vettore delle distanze
								(dalla sorgente)
								*/
			p = new int[len]; // vettore dei precedenti

			M = new int*[len];
			for(int i=0; i<len; i++) {
				M[i] = new int[len];
				for(int j=0; j<len; j++)
					M[i][j] = 0;
			}
			K = new H*[len];
			for(int i=0; i<len; i++) K[i] = NULL;
		}

		Mgraph<H>* addNode(H k) {
			if(n==len) return this;
			if(findIndex(k)>=0) return this;
			K[n] = new H(k);
			n++;
			return this;
		}

		Mgraph<H>* addEdge(H x, H y) {
			int i = findIndex(x);
			int j = findIndex(y);
			if(i<0 || j<0) return this;
			if(!M[i][j]) {
				M[i][j] = 1;
				m++;
			}
			return this;
		}

		void print() {
			for(int i=0; i<n; i++) {
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				for(int j=0; j<n; j++) {
					if(M[i][j]) cout << *K[j] << " ";
				}
				cout << endl;
			}
		}
		void BFS(int s) {
		    bool debug = true; // se == true stampo lo stato dei nodi (i loro colori)
			int c[len]; // lista dei colori
			coda *Q = new coda(len);
			//iniz.
			for(int i=0; i<n; i++) {
				c[i] = W;
				p[i] = -1;
				d[i] = inf;
			}
			Q->enqueue(s);
			c[s] = G;
			d[s] = 0;
			while(!Q->isEmpty()){

                // posso stampare qui lo stato dei colori (utile per comprensione/debug)
                if(debug){
                    stampaColoriNodi(c);
                    cout << endl;
                }
				int x = Q->dequeue();
				// visito la lista di adj del nodo x
				for(int i=0; i<n; i++) {
					if(M[x][i]==1) {
						if(c[i]==W) {
							c[i] = G;
							Q->enqueue(i);
							p[i] = x;
							d[i] = d[x]+1;
						}
					}
				}
				c[x] = B;
				if(debug) cout << "ho completato la visita di " << *K[x] << endl;
			}
			// stampo le distanze
			cout << "Distanze dalla sorgente:" << endl;
			for(int i=0; i<n; i++) {
				cout << "[" << *K[i] << "]->";
				if(d[i]==inf) 
					cout << "inf." << endl;
				else
					cout << d[i] << endl;
			}
			cout << endl;
		}

		void BFS(H x) {
			int s = findIndex(x);
			if(s>=0) BFS(s);
		}

		// se il parametro 'sologrigi' e' true, stampa solo quelli grigi
        void stampaColoriNodi(int* colors, bool sologrigi=false){
            for(int i=0; i<n; i++) {
				if(sologrigi&& colors[i]!=G) continue;

                cout << " " << *K[i];
                switch(colors[i]){
                    case W: cout << "(w)";break;
                    case G: cout << "(g)";break;
                    case B: cout << "(b)";break;
                }

            }
        }
};

int main(){
	Mgraph<char> *Gr=new Mgraph<char>(9);
	cout<<"ADDNODE"<<endl;
	Gr->addNode('A')->addNode('B')->addNode('C')->addNode('D');
	Gr->addNode('E')->addNode('F')->addNode('G')->addNode('H');
	Gr->addNode('I');
	Gr->print();
	cout<<"ADDEDGE"<<endl;
	Gr->addEdge('A','I')->addEdge('A','B');
	Gr->addEdge('B','I');
	Gr->addEdge('C','E');
	Gr->addEdge('E','D')->addEdge('E','A');
	Gr->addEdge('F','G')->addEdge('F','D');
	Gr->addEdge('G','F');
	Gr->addEdge('I','C');
	Gr->print();
	cout<<"////////"<<endl;
	Gr->BFS('B');
}



