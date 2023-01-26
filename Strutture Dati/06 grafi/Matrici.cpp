#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <typeinfo>

using namespace std;

template <class H> class Mgraph {
	private:
		int len, n, m;
		/* 	n numero di nodi effettivo,
			m numero di archi effettivo,
			len numero massimo di nodi
		*/
		int **M; //Contiene gli indici corrispondenti ai vari nodi
		H **K; // Contiene i valori di tipo H dei nodi
		int *p;//array predecessori

		int findIndex(H x) {
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
};

int main(){
	Mgraph<char> *Gr = new Mgraph<char>(9);
	
	cout<<"ADDNODE"<<endl;
	Gr->addNode('A')->addNode('B')->addNode('C')->addNode('D');
	Gr->addNode('E')->addNode('F')->addNode('G')->addNode('H')->addNode('I');
	Gr->print();
	
	cout<<"ADDEDGE"<<endl;
	Gr->addEdge('A','I')->addEdge('A','B');
	Gr->addEdge('B','I');
	Gr->addEdge('C','E');
	Gr->addEdge('D','F')->addEdge('D','G')->addEdge('D','H');
	Gr->addEdge('E','D')->addEdge('E','A');
	Gr->addEdge('F','G')->addEdge('F','D');
	Gr->addEdge('G','F');
	Gr->addEdge('I','C');
	Gr->print();
	
	cout<<"/////////"<<endl;
	
	Mgraph<int> *Gs = new Mgraph<int>(9);
	
	cout<<"ADDNODE"<<endl;
	Gs->addNode(0)->addNode(1)->addNode(2)->addNode(3);
	Gs->addNode(4)->addNode(5)->addNode(6)->addNode(7)->addNode(8);
	Gs->print();
	
	cout<<"ADDEDGE"<<endl;
	Gs->addEdge(1,5)->addEdge(1,7);
	Gs->addEdge(2,1);
	Gs->addEdge(3,4)->addEdge(3,7);
	Gs->addEdge(4,8);
	Gs->addEdge(8,6)->addEdge(8,8)->addEdge(8,5);
	Gs->print();
	
}



