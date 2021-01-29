#pragma once
#include "BinaryTree.hpp"
#include "List_Sequence.h"
#include <iostream>
//#include "ConvertText.h"
#include <fstream>
#include <string>
//#include <algorithm>
#include <sstream>
using namespace std;

//работа с файлами
LinkedListSequence<string>* file_list() {
	LinkedListSequence<string>* list = new LinkedListSequence<string>();
	string word;
	//файл с текстом
	ifstream in("C://Users/User/Desktop/text.txt");
	if (in.is_open()) {
		while (!in.eof()) {
			in >> word;
			list->Prepend(word);
		}
		in.close();
	}
	else throw length_error("File is empty");
	return list;
}

//самостоятельный ввод
LinkedListSequence<string>* write_list() {
	LinkedListSequence<string>* list = new LinkedListSequence<string>();
	string text;
	string word;

	cout << "Please, enter your text: \n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, text);
	
	stringstream s;
	s.str(text);
	while (!s.eof()) {
		s >> word;
		list->Prepend(word);
	}
	return list;
}

//длина строки в буквах
int Length(LinkedListSequence<string>* words){
	int length = 0;
	for (int i = 0; i < words->GetLength(); i++) {
		length += words->Get(i).length();
	}

	length += words->GetLength() - 1;
	//cout << "Length of string = " << length << endl;
	return length;
}


//создание словаря  
//choose:  1-деление по словам  2-деление по символам 
IDictionary<string, int>* create_ID(LinkedListSequence<string>* words, int sizepages, int choose) {

	IDictionary<string, int>* IDic = new IDictionary<string, int>();
	int page_number = 1;
	int cur_size = 0;
	int count_of_pages = 0;

	//деление по словам
	if (choose == 1) {
		int  wordscopy = words->GetLength();
		int a = wordscopy;
		wordscopy -= (int)(sizepages / 2);
		++count_of_pages;

		//определяем количество страниц
		if (wordscopy > 0) {
			int i = wordscopy;
			while (i > 0) {
				if ((count_of_pages % 10) == 0) 
					i -= (int)(sizepages * 3 / 4);
				else {
					i -= sizepages;
				}
				++count_of_pages;
			}
		}
		///////////////////////
		cout << "\nNumbers of pages " << count_of_pages << "\n";
		
		// все слова на первой странице
		if (count_of_pages == 1) {
			while (cur_size != words->GetLength()) {
				IDic->Insert(words->Get(cur_size), 1);
				cur_size++;
				--a;
			}
		} 
		else {
			for (int i = 0; i < count_of_pages; i++) {
				if (page_number == 1) {
					for (int j = 0; j < (int)(sizepages / 2) && (a >= 0); j++) {
						IDic->Insert(words->Get(cur_size), page_number);
						cur_size++;
						--a;
					}
				}
				else if ((page_number % 10) == 0) {
					for (int j = 0; j < (int)(sizepages * 3 / 4) && (a > 0); j++) {
						IDic->Insert(words->Get(cur_size), page_number);
						cur_size++;
						--a;
					}
				}
				else {
					for (int j = 0; (j < sizepages) && (a > 0); j++) {
						IDic->Insert(words->Get(cur_size), page_number);
						cur_size++;
						--a;
					}
				}
				page_number++;
			}
		}
	} //деление по буквам
	else {
		int length = Length(words);
		int wordscopy = length;
		int a = length;
		wordscopy -= (int)(sizepages / 2);
		++count_of_pages;

		if (wordscopy > 0) {
			for (int i = length; i > 0; ) {
				if ((count_of_pages % 10) == 0) {
					i -= (int)(sizepages * 3 / 4);
				}
				else {
					i -= sizepages;
				}
				++count_of_pages;
			}
		}
		///////////////////////
		cout << "\nNumbers of pages " << count_of_pages << "\n";

		// все буквы на первой странице
		if (count_of_pages == 1) {
			for (int i = 0; i < sizepages && (a > 0); i + words->Get(i).length()) {
				IDic->Insert(words->Get(cur_size), 1);
				cur_size++;
				a -= words->Get(i).length();
			}
		} 
		else {
			for (int i = 0; i < count_of_pages; i++) {
				if (page_number == 1) {
					for (int j = 0; (j < (int)(sizepages / 2)) && (a > 0); j + words->Get(i).length() + 1) {
						IDic->Insert(words->Get(cur_size), page_number);
						cur_size++;
						a -= words->Get(i).length() + 1;
					}
				}
				else if ((page_number % 10) == 0) {
					for (int j = 0; (j < (int)(sizepages * 3 / 4)) && (a > 0); j + words->Get(i).length() + 1) {
						IDic->Insert(words->Get(cur_size), page_number);
						cur_size++;
						a -= words->Get(i).length() + 1;
					}
				}
				else {
					for (int j = 0; (j < sizepages) && (a > 0); j + words->Get(i).length() + 1) {
						IDic->Insert(words->Get(cur_size), page_number);
						cur_size++;
						a -= words->Get(i).length() + 1;
					}
				}
				page_number++;
			}
		}
	}
	return IDic;
} 

//максимальная длина Key
LinkedListSequence<int>* listlength = new LinkedListSequence<int>();
int GetMaxLength(TreeNode<string, int>* Node) {
	if (Node != nullptr) {
		GetMaxLength(Node->GetLeft());
		listlength->Append(Node->GetKey().length());		
		GetMaxLength(Node->GetRight());
	}

	int maxlength = 0;
	for (int i = 0; i < listlength->GetLength(); i++) {
		if (listlength->Get(i) > maxlength) maxlength = listlength->Get(i);
	}

	return maxlength;
}

//выравнивание и вывод
void _PrintKeyValue(TreeNode<string, int>* Node, int lvl,int maxlength) {
	if (Node != nullptr) {
		_PrintKeyValue(Node->GetLeft(), lvl, maxlength);
		cout << "[" << Node->GetKey() << "]";
		for (int i = 0; i < (maxlength-Node->GetKey().length()); i++) cout << " "; 
		cout << " on page " << Node->GetValue() << "\n";
		_PrintKeyValue(Node->GetRight(), lvl, maxlength);
	}
}; 
void PrintKeyValue(TreeNode<string, int>* Node, int lvl, int maxlength) {
	cout<< "\n//////////////////////////\n"
		<< "It is your IDictionary: \n"
		<< "[word] on page N\n";
	_PrintKeyValue(Node, lvl,maxlength);
	cout << "//////////////////////////\n";
}


void PrintTree(TreeNode<string, int>* Node, int lvl) {
	if (Node != nullptr) {
		PrintTree(Node->GetLeft(), lvl);
		for (int i = 0; i < lvl - Node->height(); i++) cout << "         ";
		cout << "[" << lvl - Node->height() << "]";
		cout << " Key: " << Node->GetKey() << " Value: " << Node->GetValue() << "\n";
		PrintTree(Node->GetRight(), lvl);
	}
}; 


void interface_Text() {
	int choose1,choose2, size(0);

	//выбор типа деления строки
	cout << "//////////////////////Alphabetical index task//////////////////////\n" 
		 << "Enter type of page length:\n" << "1. Number of words\n" << "2. Number of symbols\n";
	cin >> choose1;
	cout << "Enter the size of pages: \n";
	do {
		cin >> size;
		if (size <= 0)	std::cout << "ERROR. The size cannot be zero or negative \n";
	} while (size <= 0);

	// выбор текста
	cout << "How do you want to enter your text? \n" << "1.From File \n" << "2.New text by hand \n" ;
	cin >> choose2;
	LinkedListSequence<string>* words;
	words = new LinkedListSequence<string>();
	
	if (choose2 == 1) {
		words = file_list();
		cout << "Your text:\n";
		words->Print();
	}
	else {
		words = write_list();
	};
	
	IDictionary<string, int>* IDic=create_ID(words,size,choose1);
	BinaryTree<string, int>* Tree = IDic->GetTree();
	PrintKeyValue(Tree->GetRoot(), Tree->Height(), GetMaxLength(Tree->GetRoot()));
}





