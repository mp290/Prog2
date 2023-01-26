#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class T> void bubblesort(T *, int);
template <class T> void insertionsort(T *, int);
template <class T> void selectionsort(T *, int);
template <class T> int partition(T *, int);
template <class T> void quicksort(T *, int);
template <class T> void merge(T *, int, int);
template <class T> void mergesort(T *, int);


template <class T> void scambia(T *v, int i, int j){
    T tmp = v[j];
    v[j] = v[i];
    v[i] = tmp;
}

template <class T> void stampa(T *v, int n){
    for(int i=0; i<n; i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

// O(n^2) caso pessimo e ottimo
template <class T>
void bubblesort(T *v, int n){
	int i,k;
	int temp;
	for(i = 0; i<n-1; i++)
		for(k = 0; k<n-1-i; k++)
			if(v[k] > v[k+1]) 
				scambia(v,k,k+1);
}

// O(n) caso ottimo
// O(n^2) caso pessimo
template <class T>
void insertionsort(T *v, int n){
	int i, j ,tmp;
	for (i = 1; i < n; i++){
		j = i;
		while (j > 0 && v[j - 1] > v[j]){
			scambia(v,j,j-1);
			j--;
		}
	}
}

// O(n^2) caso ottimo e pessimo
template <class T>
void selectionsort(T *v, int n){
	for(int i=0; i<n; i++){
        int min = i;
        for(int j=i+1; j<n; j++){
            if(v[j] < v[min])
                min = j;
        }
        scambia(v, i, min);
    }
}

template <class T>
void shellsort(T *v, int n){
	int salto = n/2;
	while ( salto>0 ) {
		for(int i=salto; i<n; i++){
			int j = i-salto;
			while ( j>=0 ){
				int k = j+salto;
				if ( v[j]<=v[k] ) j=-1;
				else {
					scambia(v,j,k);
					j = j-salto;
				}
			}
		}
		salto = salto/2;
	}
}


template <class T> void mergesort(T *v, int n){
    if(n<=1) return;
    int m = n/2; 
    mergesort(v,m);
    mergesort(v+m,n-m);
    merge(v,n,m);
}

template <class T> void merge(T *v, int n, int m){
    T b[n];
    int i,j,k;
    i = k = 0;
    j = m;
    while(i<m && j<n) {
        if(v[i]<v[j]) b[k++]=v[i++];
        else b[k++]=v[j++];
    }
    while(i<m) b[k++]=v[i++];
    while(j<n) b[k++]=v[j++];
    for(int i=0; i<n; i++) v[i] = b[i];
}


template <class T>
void quicksort(T *v, int n){
    if(n<=1) return;
    int m = partition(v,n); //v[0 ... m] < v[m+1 ... n-1]
    quicksort(v, m+1); // quicksort(v[0...m])
    quicksort(v+m+1, n-(m+1)); // quicksort(v[m+1...n-1])
}

template <class T>
int partition(T *v, int n){  // O(n)
    T x = v[0];  //elemento pivot
    int i = -1;
    int j = n;
    do {
        do i++; while(v[i]<x);
        do j--; while(v[j]>x);
        if(i<j) scambia(v,i,j);
    } while(i<j);
    return j;
}

int main () {
	int len; 	
	void (*sort[]) (int v[], int n) = { // vettore di puntatori a funzione
		bubblesort, insertionsort, selectionsort, mergesort, quicksort};
	char algos[5][15] = {"BubbleSort", "InsertionSort", "SelectionSort", "MergeSort", "QuickSort"};
	double time[5] = {0}; // conterrà i tempi di esecuzione con cui gli algoritmi verranno eseguiti
	cout << "Inserisci la dimensione del vettore : ";
	cin >> len;
	int *V = new int[len];

	clock_t inizio,fine;
	for(int i=0; i<5; i++) {
		//for(int j=0; j<len; j++) V[j] = rand()%10000; //inizializzazione random
		for(int j=0; j<len; j++) V[j] = j; //inizializzazione array già ordinato 
		for(int j=0; j<len/100; j++){       //un decimo degli elementi è stato spostato da qualche altra parte
			int k=rand()%len;
			int h=rand()%len;
			scambia(V,k,h);
		}
		inizio = clock();
		sort[i](V,len);
		fine = clock();
		double tempo = (double)((fine-inizio)*1000)/CLOCKS_PER_SEC;
		cout << algos[i] << " \t: " << tempo << " ms" << endl;
	}
	return 0;
}
