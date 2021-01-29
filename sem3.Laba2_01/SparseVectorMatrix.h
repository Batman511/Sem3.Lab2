#pragma once
#include "BinaryTree.h"
#include "ArraySequence.h"
#include <fstream>
#include <sstream>
//#include <iostream>
#include <utility>
using namespace std;

/*
template <class T>
void Print(Sequence<T>* seq, const int length) {
	cout << "Your sequence: \n";
	for (int i = 0; i < length; i++) {
		cout << "[" << seq->Get(i) << "] ";
	}
	cout << "\n";
}
*/

//получение вектора
template <class T>
ArraySequence<T>* New_vector() {
	ArraySequence<T>* vector = new ArraySequence<T>();
	T element;
	ifstream in("C://Users/User/Desktop/vector.txt");
	if (in.is_open()) {
		while (!in.eof()) {
			in >> element;
			vector->Prepend(element);
		}
		in.close();
	}
	else throw length_error("File is empty");

	return vector;
}

//получение матрицы
template <class T>
ArraySequence<ArraySequence<T>*>* New_matrix() {
	ArraySequence<T>* lines; // = new ArraySequence<int>();
	ArraySequence<ArraySequence<T>*>* matrix = new ArraySequence<ArraySequence<T>*>();
	
	//string element;
	string s;
	int count_of_lines = 0;
	int count_of_elem = 0;
	ifstream in("C://Users/User/Desktop/matrix.txt"); 
	
	if (in.is_open()) {
		while (!in.eof()) {
			while (getline(in, s)) {
				s += ' ';
				lines = new ArraySequence<T>(count_of_elem);
				while (s.find(" ") != string::npos) {
					if (count_of_lines != 0) {
						for (int i = 0; i < count_of_elem; i++) {
							lines->InsertAt(s.substr(0, s.find(" ")),i);
							s.erase(0, s.find(' ') + 1);
						}
					}
					else {
						lines->Prepend(s.substr(0, s.find(" ")));
						s.erase(0, s.find(' ') + 1);
						count_of_elem++;
					}
				}
				matrix->Prepend(lines);
				count_of_lines++;
			}
			in.close();
			cout << "Number of columns = " << count_of_lines << "\n";
		}
	}
	else throw length_error("File is empty");
	return matrix;
}

//преобразование вектора и матрицы
template <class T, class TValue>
IDictionary<int, TValue>* MakeSparseVector(ArraySequence<T>* vector) {
	IDictionary<int, TValue>* IDic = new IDictionary<int, TValue>();
	for (long i = 0; i < vector->GetLength(); i++) {
		if (vector->Get(i) != 0) {
			IDic->Insert(i, vector->Get(i));
		}
	}
	return IDic;
}

template <class T>
IDictionary<pair<long, long>, T>* MakeSparseMatrix(ArraySequence<ArraySequence<T>*>* matrix) {
	IDictionary<pair<long, long>, T>* IDic = new IDictionary<pair<long, long>,T>();
	for (long i = 0; i < matrix->GetLength(); i++) {
		for (long j = 0; j < (matrix->Get(i))->GetLength(); j++)
			if (matrix->Get(i)->Get(j) != "0") {
				pair<long, long> index = make_pair(i, j);
				IDic->Insert(index, matrix->Get(i)->Get(j));
			}
	}
	return IDic;
}


