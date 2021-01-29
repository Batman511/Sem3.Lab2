#pragma once
#include "BinaryTree.hpp"
#include "ArraySequence.h"
#include <fstream>
//#include "SparseVectorMatrix.hpp"
#include <sstream>
#include <iostream>
#include <utility>
using namespace std;

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


IDictionary<pair<long, long>, string>* MakeSparseMatrix(ArraySequence<ArraySequence<string>*>* matrix) {
	IDictionary<pair<long, long>, string>* IDic = new IDictionary<pair<long, long>, string>();
	for (long i = 0; i < matrix->GetLength(); i++) {
		for (long j = 0; j < (matrix->Get(i))->GetLength(); j++)
			if (matrix->Get(i)->Get(j) != "0") {
				pair<long, long> index = make_pair(i, j);
				IDic->Insert(index, matrix->Get(i)->Get(j));
			}
	}
	return IDic;
}


template <class T>
void Print(Sequence<T>* seq, const int length) {
	cout << "Your sequence: \n";
	for (int i = 0; i < length; i++) {
		cout << "[" << seq->Get(i) << "] ";
	}
	cout << "\n";
}

//получение вектора
template <class T>
ArraySequence<T>* New_vector() {
	ArraySequence<T>* vector = new ArraySequence<T>();
	T element;
	ifstream in("C://Users/User/Desktop/vector.txt"); //file with vector
	if (in.is_open()) {
		while (!in.eof()) {
			in >> element;
			vector->Prepend(element);
		}
		in.close();
	}
	//else cout << "File didn't open: ";
	else throw length_error("File is empty");

	return vector;
}

//получение матрицы
template <class T>
ArraySequence<ArraySequence<string>*>* New_matrix() {
	ArraySequence<string>* lines = new ArraySequence<string>();
	ArraySequence<ArraySequence<string>*>* matrix = new ArraySequence<ArraySequence<string>*>();
	
	T element;
	string s;
	int count_of_lines = 0;
	int count_of_elem = 0;
	ifstream in("C://Users/User/Desktop/matrix.txt"); 
	
	if (in.is_open()) {
		while (!in.eof()) {
			while (getline(in, s)) {
				s += ' ';
				lines = new ArraySequence<string>(count_of_elem);
				while (s.find(" ") != string::npos) {
					if (count_of_lines != 0) {
						for (int i = 0; i < count_of_elem; i++) {
							lines->InsertAt(i, s.substr(0, s.find(" ")));
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


///////////////////подумать/////////////

//выравнивание и вывод
void _PrintKeyValue2(TreeNode<int, int>* Node, int lvl) {
	if (Node != nullptr) {
		_PrintKeyValue2(Node->GetLeft(), lvl);
		cout << "[" << Node->GetKey() << "]";
		cout << "  " << Node->GetValue() << "\n";
		_PrintKeyValue2(Node->GetRight(), lvl);
	}
};

void PrintKeyValue2(TreeNode<int, int>* Node, int lvl) {
	cout << "\n//////////////////////////\n"
		<< "It is your IDictionary: \n"
		<< "[index] Value \n";
	_PrintKeyValue2(Node, lvl);
	cout << "//////////////////////////\n";
}

void PrintSparseVector(IDictionary<int, int>* IDic) {
	PrintKeyValue2(IDic->GetTree()->GetRoot(), IDic->GetTree()->Height());
}


void PrintSparseMatrix(IDictionary<pair<long, long>, int>* IDic) {
	PrintKeyValue2(IDic->GetTree()->GetRoot(), IDic->GetTree()->Height());
}
