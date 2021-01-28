#include <iostream>
#include "Tests.h"
#include "BinaryTree.hpp"
#include "ConvertText.hpp"
//#include "SparseVectorMatrix.hpp"
//#define TN TreeNode<TKey, TValue>*
using namespace std;

void interface() {


	
};

/*
template<class TKey, class TValue>
void PrintTree(TN Node, int lvl) {
	if (Node != nullptr) {
		PrintTree(Node->GetRight(), lvl + 1);
		for (int i = 0; i < lvl - Node->height(); i++) cout << "    ";
		cout << "[" << lvl - Node->height() << "]";
		cout << " Key: " << Node->GetKey() << "Value: " << Node->GetValue() << "\n";
		PrintTree(Node->GetLeft(), lvl + 1);
	}
}; */

/*
template<class TKey, class TValue>
void PrintKeyValue(TN Node, int lvl) {
	if (Node != nullptr) {
		PrintKeyValue(Node->GetRight(), lvl + 1);
		cout << "[" << Node->GetKey() << "] = " << Node->GetValue() << "\n";
		PrintKeyValue(Node->GetLeft(), lvl + 1);
	}
}; */

int main() {
	
	interface_Text();
	//Test_BinaryTree();

	return 0;
};

