#include "ConvertText.h"
#include "SparseVectorMatrix.h"
using namespace std;

int Size(int x) {
	int n = 1;
	while ((x /= 10) > 0) n++;
	return n;
}

//выравнивание и вывод
void _PrintKeyValue1(TreeNode<int, int>* Node, int lvl) {
	if (Node != nullptr) {
		_PrintKeyValue1(Node->GetLeft(), lvl);
		cout << "[" << Node->GetKey() << "]";
		for (int i = 0; i < (3 - Size(Node->GetKey())) ; i++) cout << " ";
		cout << "  |   " << Node->GetValue() << "\n";
			// << "---------------\n";
		_PrintKeyValue1(Node->GetRight(), lvl);
	}
};
void _PrintKeyValue2(TreeNode<pair<long, long>, string>* Node, int lvl) {
	if (Node != nullptr) {
		_PrintKeyValue2(Node->GetLeft(), lvl);
		cout << "[" << Node->GetKey().first << "]" << "[" << Node->GetKey().second << "]";
		for (int i = 0; i < (3 - Size(max(Node->GetKey().first, Node->GetKey().second))); i++) cout << " ";
		cout << "  |   " << Node->GetValue() << "\n";
			//<< "---------------\n";
		_PrintKeyValue2(Node->GetRight(), lvl);
	}
};

template <class TKey, class TValue>
void PrintSparseVector(IDictionary<TKey, TValue>* IDic) {
	cout << "\n//////////////////////////\n"
		<< "It is your Sparse Vector: \n"
		<< "[index]  Value \n"
		<< "--------------\n";
	_PrintKeyValue1(IDic->GetTree()->GetRoot(), IDic->GetTree()->Height());
	cout << "--------------\n";
}

template <class TValue>
void PrintSparseMatrix(IDictionary<pair<long, long>, TValue>* IDic) {
	cout << "\n//////////////////////////\n"
		<< "It is your Sparse Matrix: \n"
		<< "[ind][ind]  Value \n"
		<< "------------------\n";
	_PrintKeyValue2(IDic->GetTree()->GetRoot(), IDic->GetTree()->Height());
	cout << "------------------\n";
}

void interface_Sparse() {
	int choose;

	cout << "\n//////////////////////Sparse Vector & Matrix task//////////////////////\n"
		<< "1. Make sparse vector \n" << "2. Make sparse matrix \n";
	cin >> choose;
	do {
		if (choose != 1 && choose != 2) {
			std::cout << "ERROR. You need choose 1 or 2 \n";
			cin >> choose;
		}
	} while (choose != 1 && choose != 2);

	if (choose == 1) {
		PrintSparseVector(MakeSparseVector<int, int>(New_vector<int>()));
	}
	if (choose == 2) {
		PrintSparseMatrix(MakeSparseMatrix(New_matrix<string>()));
	}
}

int main() {
	string choose1{"0"};
	int choose(0);

	cout << "Lets Start\n";
	do {
		cout << "Choose the Task:\n"
			 << "1. Alphabetical index task \n2. Sparse Vector & Matrix task \n3. Tests \n4. Exit \n";
		do {
			if (choose1 == "0") cin >> choose1;
			else if (choose1 != "1" && choose1 != "2" && choose1 != "3" && choose1 != "4") {
				std::cout << "ERROR. You need choose a number from 1 to 4 \n";
				cin >> choose1;
			}
		} while (choose1 != "1" && choose1 != "2" && choose1 != "3" && choose1 != "4");
		choose = stoi(choose1);

		switch (choose) {
		case 1:
			interface_Text();
			break;
		case 2:
			interface_Sparse();
			break;
		case 3:
			//Tests();
			break;
		case 4:
			std::cout << "\n ***** Good job ***** \n";
			break;
		default: std::cout << "ERROR. You kill me.";
		}
		choose1 = "0";
	}while (choose != 4);

	return 0;
};

