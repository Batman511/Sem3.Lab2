//#include <iostream>
//#include "Tests.h"
//#include "BinaryTree.h"
#include "ConvertText.h"
#include "SparseVectorMatrix.h"
using namespace std;

void interface() {


	
};


//выравнивание и вывод
template <class TKey, class TValue>
void _PrintKeyValue1(TreeNode<TKey, TValue>* Node, int lvl) {
	if (Node != nullptr) {
		_PrintKeyValue1(Node->GetLeft(), lvl);
		cout << "[" << Node->GetKey() << "]";
		cout << "  " << Node->GetValue() << "\n";
		_PrintKeyValue1(Node->GetRight(), lvl);
	}
};

template <class TValue>
void _PrintKeyValue2(TreeNode<pair<long, long>, TValue>* Node, int lvl) {
	if (Node != nullptr) {
		_PrintKeyValue2(Node->GetLeft(), lvl);
		cout << "[" << Node->GetKey().first << "]" << "[" << Node->GetKey().second << "]";
		cout << "  " << Node->GetValue() << "\n";
		_PrintKeyValue2(Node->GetRight(), lvl);
	}
};

template <class TKey, class TValue>
void PrintSparseVector(IDictionary<TKey, TValue>* IDic) {
	cout << "\n//////////////////////////\n"
		<< "It is your Sparse Vector: \n"
		<< "[index] Value \n";
	_PrintKeyValue1(IDic->GetTree()->GetRoot(), IDic->GetTree()->Height());
	cout << "//////////////////////////\n";
}

template <class TValue>
void PrintSparseMatrix(IDictionary<pair<long, long>, TValue>* IDic) {
	cout << "\n//////////////////////////\n"
		<< "It is your Sparse Matrix: \n"
		<< "[index][index] Value \n";
	_PrintKeyValue2(IDic->GetTree()->GetRoot(), IDic->GetTree()->Height());
	cout << "//////////////////////////\n";
}

void interface_Sparse() {
	int choose;

	cout << "//////////////////////Sparse Vector & Matrix task//////////////////////\n"
		<< "1. Make sparse vector \n" << "2. Make sparse matrix \n";
	cin >> choose;
	do {
		cin >> choose;
		if (choose != 1 && choose != 2)	std::cout << "ERROR. You need choose 1 or 2 \n";
	} while (choose != 1 && choose != 2);

	if (choose == 1) {
		PrintSparseVector(MakeSparseVector<int, int>(New_vector<int>()));
	}
	if (choose == 2) {
		PrintSparseMatrix(MakeSparseMatrix(New_matrix<string>()));
	}

}

int main() {
	


	interface_Sparse();
	//interface_Text();

	return 0;
};

