#pragma once
#include "BinaryTree.h"
#include "ArraySequence.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
using namespace std;

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


