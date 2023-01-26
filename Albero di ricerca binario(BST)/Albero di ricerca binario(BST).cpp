// Albero di ricerca binario(BST).cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
// PROVA

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
    nodo* padre;
    nodo* destro;
    nodo* sinistro;
    int val=0;
    nodo() {
        padre = NULL;
        destro = NULL;
        sinistro = NULL;
        int val = 0;
    }
    
};

class BST {
    nodo* root;
    
private:
    void trapianta(nodo* x, nodo* y) {
        if (x->padre == NULL)
            this->root = y;
        else {
            if (x == x->padre->sinistro)
                x->padre->sinistro = y;
            else
                x->padre->destro = y;
        }
        if (y != NULL)
            y->padre = x->padre;
    }

    void canc(nodo* x) {
        nodo* y=NULL;

        if (x->sinistro == NULL)
            trapianta(x, x->destro);
        else {
            if (x->destro == NULL)
                trapianta(x, x->sinistro);
            else {
                y = min(x->destro);
                if (y->padre != x) {
                    trapianta(y, y->destro);
                    y->destro = x->destro;
                    y->destro->padre = y;
                }
            }
            trapianta(x, y);
            y->sinistro = x->sinistro;
            y->sinistro->padre = y;
        }
        delete x;
    }


    void insert(int x) {
        nodo *nuovo = new nodo;
        nuovo->val = x;
        nodo* iter = this->root;//nodo ausialiare che mi serve per iterare
        nodo* aux = new nodo;//Nodo che mi serve per salvare il precedente di iter, cioè l'ausiliare
        bool pos;//flag per la posizione del nodo TRUE SE VA A SINISTRA, FALSE SE VA A DESTRA
        if (this->root != NULL) {//se la testa è presente
            while (iter != NULL) {//i nodi nuovi vanno aggiunti sempre come foglie, quindi dobbiamo arrivare alle foglie
                aux = iter;//conservo il precedente di iter che poi sarà null in aux
                if (iter->val > x) {//se il valore da inserire è minore della radice vado a sinistra
                    pos = true;//setto a true quindi so che devo andare a sinistra                   
                    iter = iter->sinistro;//scorro verso sinistra
                }
                else {//altrimenti vado a destra
                    pos = false;//stesso discorso del sinistro però se va a destra                    
                    iter = iter->destro;                    
                }
            }            
            nuovo->padre = aux;//alla fine assegno aux come padre del nodo nuovo, 
            if (pos == true) {//scelto il padre dobbiamo decidere se il nuovo nodo figlio deve andare a destra o a sinistra del padre, 
                //ci siamo conservati la posizione di dove va messo quando abbiamo iterato e in base a dove deve andare va messo
                aux->sinistro = nuovo;
                cout << "HO AGGIUNTO UN NODO A SINISTRA DI " << aux->val << " che e': " << aux->sinistro->val<< endl;
            }
            else {
                aux->destro = nuovo;
                cout << "HO AGGIUNTO UN NODO A DESTRA DI " << aux->val << " che e': " << aux->destro->val << endl;
            }            
        }
        else {// se la testa non è presente creo la testa
            nuovo->padre = NULL;//la radice non ha padre
            this->root = nuovo;//la radice è appunto il nodo nuovo
            cout << "HO AGGIUNTO UNA RADICE: " <<this->root->val<< endl;
        }
        
    }

    nodo* ricercaP(int x) {
        nodo* iter = this->root;
        if (iter) {
            while (iter != NULL) {
                if (x == iter->val)
                    return iter;

                if (x < iter->val)
                    iter = iter->sinistro;
                else
                    iter = iter->destro;
            }
            return NULL;
        }
        else
            cout << "ALBERO VUOTO"<<endl;
    }

    nodo* minP(nodo* x) {
        nodo* min = x;
        while (min->sinistro!=NULL) {
            min = min->sinistro;
        }
        return min;
    }
    nodo* maxP(nodo* x) {
        nodo* max = x;
        while (max->destro != NULL) {
            max = max->destro;
        }
        return max;
    }
    
    nodo* succP(int x) {
        nodo* p = ricerca(x);
        if (p) {
            if (p->destro) {
               return min(p->destro);
            }
            
        else {
            nodo* s = p->padre;
            while ((s != NULL) && (p == s->destro)) {
                p = s;
                s = s->padre;
            }
            return s;
            }            
        }
    }

    nodo* precP(int x) {
        nodo* p = ricerca(x);
        if (p) {
            if (p->sinistro) {
                return max(p->sinistro);
            }
            else {
                nodo* s = p->padre;
                while ((s != NULL) && (p == s->sinistro)) {
                    p = s;
                    s = s->padre;
                }
                return s;
            }
        }
    }


    int distPrecP(int x) {
        int c = 1;
        nodo* n = ricerca(x);
        if (n) {
            if (n->sinistro != NULL) {
                nodo* max = n->sinistro;
                while (max->destro != NULL) {
                    max = max->destro;
                    c++;
                }
                return c++;
            }
            else {
                nodo* s = n->padre;
                while ((s != NULL) && (n == s->sinistro)) {
                    n = s;
                    s = s->padre;
                    c++;
                }
                return c;
            }
        }
        else {
            cout << "NON TROVATO" << endl;
            return NULL;
        }
    }
   
    int distSuccP(int x) {
        int c = 1;
        nodo* n = ricerca(x);
        if (n) {
            if (n->destro != NULL) {
                nodo* min = n->destro;
                while (min->sinistro != NULL) {
                    min = min->sinistro;
                    c++;
                }
                return c++;
            }
            else {
                nodo* s = n->padre;
                while ((s != NULL) && (n == s->destro)) {
                    n = s;
                    s = s->padre;
                    c++;
                }
                return c;
            }
        }
        else {
            cout << "NON TROVATO" << endl;
            return NULL;
        }
    }

 public:
    BST() {
        root = NULL;
    }

    int distPrec(int x) {
        return distPrecP(x);
    }

    int distSucc(int x) {

        return distSuccP(x);
    }

    bool cancella(int x) {
        nodo* n = BST::ricerca(x);
        if (n) {                      
            if (x == n->val) {
                int a = n->val;
                canc(n);
                cout << "VALORE CANCELLATO: " << a<<endl;
                return true;
            }           
        }
        else
            return false;

    }


    nodo* prec(int x) {
        return precP(x);
    }

    nodo* succ(int x) {
        return succP(x);
    }

    nodo* min(nodo *p) {
        return minP(p);
    }
    nodo* min() {
        return minP(this->root);
    }

    nodo* max() {
        return maxP(this->root);
    }
    nodo* max(nodo *p) {
        return maxP(p);
    }

    void inser() {
        int x;
        cout << "INSERISCI IL VALORE CHE VUOI AGGIUNGERE NELL'ALBERO: ";
        cin >> x;
        insert(x);
    }
    void inser(int x) {
        insert(x);
    }

    nodo* ricerca(int x) {   
        nodo* cercato = ricercaP(x);
        if (cercato) {
            return cercato;
        }
        else {           
        }
        return NULL;
    }

    int altezza(nodo* x) {
        if (x == NULL)
            return 0;

        int left = altezza(x->sinistro);
        int right = altezza(x->destro);

        if (left > right)
            return left + 1;
        else
            return right + 1;
    }

    friend ostream& operator<<(ostream& os, BST& bst);
    
};

void stampa(nodo* x, int livello) {
    if (x == NULL) {
        if (livello == 0)
            cout << "_\t";
        return;
    }

    if (livello == 0)
        cout << x->val << "\t";

    if (livello > 0) {
        stampa(x->sinistro, livello - 1);
        stampa(x->destro, livello - 1);
    }
}

ostream& operator<<(ostream& os, BST& bst) {
    nodo* iter = bst.root;
    if (iter) {
        os << "ALBERO DI ALTEZZA: " << bst.altezza(bst.root) << endl;
        os << "	ROOT-->";
        for (int i = 0; i < bst.altezza(bst.root); i++) {
            stampa(iter, i);
            cout << endl;
        }
    }
    else
        cout << "ERRORE" << endl;
    return os;
}

int main() {

    BST bst;
    /*
    for (int i = 0; i < 10; i++) {
        bst.inser();
   }
   */
    bst.inser(20);
    bst.inser(10);
    bst.inser(25);
    bst.inser(8);
    bst.inser(15);
    bst.inser(23);
    bst.inser(27);
    bst.inser(9);
    bst.inser(26);
    bst.inser(30);

    cout << endl<<bst;

    bst.ricerca(2);

    cout <<"SUCCCESSIVO DI 20 e' "<<bst.succ(20)->val << " e dista: " << bst.distSucc(20) << endl;
    cout <<"PREDECESSORE DI 20 e' " << bst.prec(20)->val<<" e dista: " << bst.distPrec(20) << endl;

    if (bst.cancella(10)) {

    }
    else {
        cout << "errore" << endl;
    }

    cout << bst;


   
}