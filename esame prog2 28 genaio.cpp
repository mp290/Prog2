// esame prog2 28 genaio.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include <iostream>
using namespace std;


template<typename T>
class nodo {

	T val;
	nodo<T>* padre;
	nodo<T>* dx;
	nodo<T>* sx;

	template<typename C>
	friend class BST;

public:

	//costruttore
	nodo(T val) {
		this->val = val;
		padre = nullptr;
		dx = nullptr;
		sx = nullptr;
	}

	//Getter e setter dei valori del nodo
	nodo<T>* getPadre() {
		return this->padre;
	}

	nodo<T>* getDx() {
		return this->dx;
	}

	nodo<T>* getSx() {
		return this->sx;
	}

	T getVal() {
		return this->val;
	}

	void setPadre(nodo<T>* padre) {
		this->padre = padre;
	}

	void setDx(nodo<T>* dx) {
		this->dx = dx;
	}

	void setSx(nodo<T>* sx) {
		this->sx = sx;
	}

	void setVal(T val) {
		this->val = val;
	}

};







template<typename T>
class BST {

	nodo<T>* radice;
public:

	//costruttore dell'albero
	BST() {
		radice = nullptr;
	}

	//metodo per avere la radice
	nodo<T>* getRadice() {
		return this->radice;
	}

	//se l'albero è vuoto
	bool vuoto() {
		return radice == nullptr;
	}

	//inserisco un nodo all'albero passandogli solo il valore 
	void insert(T val) {

		if (vuoto())//controlla se è vuoto, se lo è
		{
			radice = new nodo<T>(val);//aggiunge una radice
			//il cout seguente è stato commentato perchè usato solo in fase di test
			//cout << "HO AGGIUNTO UNA RADICE  che e': " << radice->val<< endl;
			return; //esce
		}
		insert(radice, val);//se non è vuoto inserisce il nodo all'albero partendo dalla radice
	}

	//inserisco un nodo passando come parametri un nodo e un valore
	void insert(nodo<T>* iter, T val) {

		if (!iter->sx && val <= iter->val)
		{
			iter->sx = new nodo<T>(val);
			iter->sx->setPadre(iter);
			//il cout seguente è stato commentato perchè usato solo in fase di test
			//cout << "HO AGGIUNTO UN NODO A SINISTRA DI " << iter->val << " che e': " << iter->sx->val << endl;
			return;
		}

		if (!iter->dx && val > iter->val)
		{
			iter->dx = new nodo<T>(val);
			iter->dx->setPadre(iter);
			//il cout seguente è stato commentato perchè usato solo in fase di test
			//cout << "HO AGGIUNTO UN NODO A DESTRA DI " << iter->val << " che e': " << iter->dx->val << endl;
			return;
		}
		//arrivati alla foglia decidiamo se il valore va a destra o a sinistra
		if (val <= iter->val) {
			insert(iter->sx, val);
		}
		else {
			insert(iter->dx, val);
		}
	}


	nodo<T>* max() { return max(radice); }
	nodo<T>* max(nodo<T>* from) {

		if (vuoto())
			throw out_of_range("bst vuoto");

		nodo<T>* ptr = from;
		while (ptr->dx)
			ptr = ptr->dx;

		return ptr;
	}

	nodo<T>* min() { return min(radice); }

	nodo<T>* min(nodo<T>* from) {

		if (vuoto())
			throw out_of_range("BST VUOTO");

		nodo<T>* ptr = from;
		while (ptr->sx)
			ptr = ptr->sx;

		return ptr;
	}


	nodo<T>* ricerca(T val) {
		if (vuoto())
			throw out_of_range("BST VUOTO");

		return ricerca(radice, val);
	}

	nodo<T>* ricerca(nodo<T>* iter, T val) {

		if (!iter)
			return nullptr;

		if (iter->val == val)
			return iter;

		if (val <= iter->val)
			return ricerca(iter->sx, val);

		else
			return ricerca(iter->dx, val);
	}

	int distSucc(T val) {

		int count = 0;
		nodo<T>* iter = ricerca(val);

		if (!iter || iter == max())
			throw out_of_range("IL SUCCESSORE NON ESISTE");

		//Caso 1: il nodo ha un sottoalbero dx
		if (iter->dx)
		{
			iter = iter->dx;
			count++; //mi sono comunque spostato di un nodo

			while (iter->sx) //Cerco il minimo del sottoalbero dx
			{
				iter = iter->sx;
				count++;
			}

			return count;
		}
	}

	nodo<T>* successore(T val) {

		nodo<T>* iter = ricerca(val);
		if (!iter || iter == max())
			throw out_of_range("NON ESISTE SUCCESSORE");

		return successore(iter);
	}

	nodo<T>* successore(nodo<T>* x)
	{

		if (vuoto())
			return nullptr;

		if (x->dx)
			return min(x->dx);

		nodo<T>* y = x->padre;
		while (x && x == y->dx)
		{
			x = y;
			y = y->padre;
		}

		return y;
	}

	void visit(nodo<T>* ptr) { cout << "\n" << *ptr << endl; }

	void in_order(nodo<T>* ptr) {

		if (!ptr)
			return;

		in_order(ptr->sx);
		visit(ptr);
		in_order(ptr->dx);
	}

	void in_order() { in_order(radice); }

	template<typename G>
	friend ostream& operator<< (ostream& os, const nodo<G>& b);

};

template<typename T>
ostream& operator<< (ostream& os, const nodo<T>& p) {

	nodo<T> b = p;

	os << "Nodo del BST: " << b.getVal() << endl;
	os << "Valore =" << b.getVal() << endl;
	os << "Sinistro->" << b.getSx() << "\t destro->" << b.getDx() << "\t padre->" << b.getPadre()->getVal() << endl;
	return os;


	return os << "valore = " << b.getVal() << endl;
}



int main()
{
	BST<int> bst;
	bst.insert(14);
	bst.insert(33);
	bst.insert(13);
	bst.insert(89);
	bst.insert(23);
	bst.insert(74);

	cout << bst.successore(23)->getVal() << endl;
	cout << bst.distSucc(33) << endl;

	bst.in_order();


}