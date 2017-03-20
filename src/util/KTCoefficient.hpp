#ifndef	GRAPHCHI_KTCoefficient 
#define GRAPHCHI_KTCoefficient


#include<iostream>
#include<stdlib.h>
#include<assert.h>
//using namespace std;

namespace graphchi{

long counter = 0;
int* aux = NULL;

void merge(int* a, int lo, int mid, int hi) {
	int i = lo, j = mid + 1;
	for (int k = lo; k <= hi; k++) {
		aux[k] = a[k];
	}
	for (int k = lo; k <= hi; k++) {
		if (i > mid) {
			a[k] = aux[j++];
		} else if (j > hi) {
			a[k] = aux[i++];
		} else if (aux[j] < aux[i]) {
			a[k] = aux[j++];
			counter += mid - i + 1;
		} else {
			a[k] = aux[i++];
		}
	}
}

void mergeSort(int* a, int lo, int hi) {
	if (hi <= lo) {
		return;
	}
	int mid = lo + (hi - lo) / 2;
	mergeSort(a, lo, mid);
	mergeSort(a, mid + 1, hi);
	merge(a, lo, mid, hi);
}


long mergeCount(int* a, int lena) {
	//aux = new int[a.length];
	aux = (int*)malloc(sizeof(int)*lena);
	mergeSort(a, 0, lena-1);
	free(aux); aux = NULL;
	return counter;
}

long distance(int* a, int* b, int lena, int lenb) {
	if (lena != lenb) {
		std::cout<<"array length is not equal!"<<std::endl;
		assert(false);
		return 0;
	}
	int N = lena;
	int* aIndex = (int *)malloc(sizeof(int)*N);
	for (int i = 0; i < N; i++) {
		aIndex[a[i]] = i;
	}

	int* bIndex = (int*)malloc(sizeof(int)*N);
	for (int i = 0; i < N; i++) {
		bIndex[i] = aIndex[b[i]];
	}
	long result = mergeCount(bIndex, N);
	free(aIndex); free(bIndex);
	return result; 
}

//use kendal-tau coefficient to measure the similarity between two sequences
double KT_Coefficient(int* a, int* b, int lena, int lenb){
	counter = 0;
	long dist = distance(a, b, lena, lenb);	
	double base = (double)lena*(double)(lena-1)/2.0;
	double result = 1.0-2.0*dist/base;
	std::cout<<"base: "<<base<<"\treverse number: "<<dist<<"\tlength:  "<<lena<<" \t coef: "<<result<<std::endl;
	assert(result <= 1.0 && result >= -1.0);
	//return 1.0-2.0*dist/base;
	return result;
}

int main() {
	int a[] = { 0, 3, 1, 6, 2, 5, 4 };
	int b[] = { 1, 0, 3, 6, 4, 2, 5 };

	int lena = sizeof(a)/sizeof(int);
	int lenb = sizeof(b)/sizeof(int);

	long dist = distance(a, b, 7, 7);
	//double base = lena*(lena-1)/2.0;
	std::cout<<"Inversions: "<<dist<<"\t Kendal-Tau coefficient:"<<KT_Coefficient(a, b, lena, lenb)<<std::endl;
	return 0;
}

};
#endif
