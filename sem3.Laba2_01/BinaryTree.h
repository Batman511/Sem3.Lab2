#pragma once
#include <string>
#include <algorithm>
#include <iostream>
#define TN TreeNode<TKey, TValue>*
using namespace std;

//звено дерева
template <class TKey, class TValue>
class TreeNode {
public:
	TKey key;
	TValue value;
	TreeNode* left;
	TreeNode* right;

	//создание звена
	TreeNode(TKey& key, TValue& value) {
		this->value = value;
		this->key = key;
		this->left = nullptr;
		this->right = nullptr;
	}
	TreeNode() {
		this->left = nullptr;
		this->right = nullptr;
	}

	//получение ключа
	TKey GetKey() {
		return this->key;
	}

	//получение элемента
	TValue GetValue() {
		return this->value;
	}

	//задание адреса элемента
	void SetLeft(TN const left) {
		this->left = left;
	}
	void SetRight(TN const right) {
		this->right = right;
	}

	//получение адреса элемента
	TN GetLeft() const {
		return left;
	}
	TN GetRight() const {
		return right;
	}

	int height() {
		int length = 0;
		if (this == nullptr) return 0;
		else {
			length = 1 + max(this->GetLeft()->height(), this->GetRight()->height());
			return length;
		}
	}

	//задание ключа
	void SetKey(const TKey& new_key) {
		key = new_key;
	}

	//операторы
	bool operator > (const TreeNode<TKey, TValue>& a) {
		return key > a.GetKey();
	}
	bool operator < (const TreeNode<TKey, TValue>& a) {
		return key < a.GetKey();
	}
	bool operator >= (const TreeNode<TKey, TValue>& a) {
		return !(key < a.GetKey());
	}
	bool operator == (const TreeNode<TKey, TValue>& a) {
		return key == a.GetKey();
	}
	bool operator != (const TreeNode<TKey, TValue>& a) {
		return !(key == a.GetKey());
	}
};

template<class TKey,class TValue>
class BinaryTree {
public:
	//корень дерева
	TN root;

	BinaryTree() {
		this->root = nullptr;
	}

	BinaryTree(TN root) {
		this->root = root;
	}

	TN GetRoot() {
		return root;
	}

	//вставить элемент
	void Insert(TKey new_key, TValue new_value) {
		TN ptr = root;
		TN end = nullptr;
		TN InsertNode = new TreeNode<TKey,TValue>(new_key,new_value);

		while (ptr != nullptr) {
			end = ptr;
			if (new_key < ptr->GetKey()) { ptr = ptr->left; }
			else ptr = ptr->right;
		}

		if (end == nullptr) root = InsertNode;
		else {
			if (new_key < end->GetKey()) { end->left = InsertNode; }
			else end->right = InsertNode;
		}
	}

	//количество узлов
	int _getcount(TN subTree) {
		int res = 0;
		if (subTree == nullptr) return 0;
		res += _getcount(subTree->GetLeft());
		res += _getcount(subTree->GetRight());
		return res + 1;
	}
	int  GetCount() {
		return _getcount(root);
	}

	//удаление дерева
	void _clear(TN badTree) {
		if (badTree == nullptr) return;
		_clear(badTree->GetLeft());
		_clear(badTree->GetRight());
		delete badTree;
	}
	void Clear() {
		_clear(root);
		root = nullptr;
	}

	//деструктор
	~BinaryTree() {
		Clear();
	}

	//обход дерева
	void Travel(TN list, TN root, int& index) {
		if (root == nullptr) return;
		Travel(list, root->GetLeft(), index);
		list[index] = *root;
		index++;
		Travel(list, root->GetRight(), index);
	}

	//балансировка
	TN _Balance(TN list,int small, int large) {
		if (small > large) return nullptr;
		int mid = (small + large) / 2;
		TN newRoot = new TreeNode <TKey, TValue>(list[mid].GetKey(), list[mid].GetValue());

		newRoot->SetLeft(_Balance(list, small, mid - 1));
		newRoot->SetRight(_Balance(list, mid + 1,large));
		return newRoot;
	}
	void Balance() {
		int index = 0;
		int num = GetCount();
		TN List = new TreeNode <TKey, TValue>[num]();
		Travel(List, root, index);
		Clear();
		root = _Balance(List, 0, num - 1);
		delete[] List;
	}

	//поиск элемента (раньше FindNode)
	TValue _FindValue(TN Node, TKey need_key) {
		if (root == nullptr) throw exception("Empty");
		if (Node == nullptr) throw exception("Not Found");
		if (Node->key == need_key) { return Node->GetValue(); }
		else if (need_key < Node->key) { return _FindValue(Node->left, need_key); }
		else if (need_key > Node->key) { return _FindValue(Node->right, need_key); }
	}
	TValue FindValue(TKey key) {
		return _FindValue(this->root, key);
	}

	//проверка на вхождение
	bool EntryCheck(TKey key){
		TN temp = this->root;

		while (temp != nullptr){
			if (key < temp->GetKey()) temp = temp->left;
			else {
				if (key > temp->GetKey()) temp = temp->right;
				else return true;
			}
		}

		if (temp == nullptr) return false;
	}

	//высота дерева
	int _height(TN subTree) {
		int length = 0;

		if (subTree == nullptr) return 0;
		else {
			length = 1 + max(_height(subTree->GetLeft()), _height(subTree->GetRight()));
			return length;
		}
	}
	int Height() {
		return _height(root);
	}

	//удаление элемента (удалять можно только листья)
	void DeleteNode(TKey key) {
		return _DeleteNode(this->root, key);
	}

	void _DeleteNode(TN Node, TKey key) {
		if (Node == nullptr) throw exception("Empty");

		TN tmp = root;
		TN end = nullptr;

		while ((tmp != nullptr) && (tmp->key != key)) {
			if (tmp->GetKey() > key) {
				end = tmp;
				tmp = tmp->GetLeft();
			}
			else {
				end = tmp;
				tmp = tmp->GetRight();
				}
			
		}
		
		if (tmp == nullptr) {
			throw exception("Empty");
			break;
		}
		else {
			if ((tmp->GetLeft() == nullptr) && (tmp->GetRight() == nullptr)) {
				if (end->GetLeft() == tmp)
					end->SetLeft(nullptr);
				else end->SetRight(nullptr);
				delete tmp;
				break;
			}
			else if ((tmp->GetLeft() == nullptr && tmp->GetRight() != nullptr) || (tmp->GetLeft() != nullptr && tmp->GetRight() == nullptr)) {
				if (end->GetLeft() == tmp){
					if (tmp->GetLeft() != nullptr){
						end->SetLeft(tmp->GetLeft());
					}
					else end->SetLeft(tmp->GetRight());
					delete tmp;
					break;
				}
				else {
					if (tmp->GetLeft() != nullptr){
						end->SetRight(tmp->GetLeft());
					}
					else end->SetRight(tmp->GetRight());
					delete tmp;
					break;
				}
			}
			else if ((tmp->GetLeft() != nullptr) && (tmp->GetRight() != nullptr)){ 
				TN leftLarg = tmp->GetLeft();
				TN leftEnd = nullptr;
				while (leftLarg->GetRight() != nullptr) {
					leftEnd = leftLarg;
					leftLarg = leftLarg->GetRight();
				}
				tmp->SetKey(leftLarg->GetKey());
				if (leftLarg->GetLeft() == nullptr){
					leftEnd->SetRight(nullptr);
					delete leftLarg;
				}
				else {
					leftEnd->SetRight(leftLarg->GetLeft());
					delete leftLarg;
				}
			}
		}
	}

	/*
	//ввод дерева
	void EnterTree() {
		std::cout << "Enter size of the Tree: ";
		int count;
		std::cin >> count;

		for (int i = 0; i < count; i++) {
			T data;
			std::cout << "Element " << i << " : ";
			std::cin >> data;
			Insert(data);
		}
	} */

	//вывод дерева
	/*
	void PrintTree(TN Node, int lvl) {
		if (Node != nullptr) {
			//throw exception("Empty");

			PrintTree(Node->right, lvl + 1);
			for (int i = 0; i < lvl - this->Height(); i++) std::cout << "    ";
			std::cout << "[" << lvl - this->Height() << "]";
			std::cout <<"Key: " << Node->GetKey() << "Value: " << Node->GetValue() << "\n";
			PrintTree(Node->left, lvl + 1);
		}
	}
	void PrintKeyValue(TN Node, int lvl) {
		if (Node != nullptr) {
			PrintKeyValue(Node->right, lvl + 1);
			std::cout << "[" << Node->GetKey() << "] = " << Node->GetValue() << "\n";
			PrintKeyValue(Node->left, lvl + 1);
		}
	} */

	//Map
	void Map(TValue(*foo)(TValue), TN Node) {
		Node->value = foo(Node->value);
		if (Node->left != nullptr) Map(foo, Node->left);
		if (Node->right != nullptr) Map(foo, Node->right);
	}

	void Map(TValue(*foo)(TValue)) {
		if (this->root == nullptr) {
			std::cout << "Empty" << "\n";
		}
		else this->Map(foo, this->root);
	}

	
};

/*
//вывод пары
ostream& operator<< (ostream& a, pair<long, long> para) {
	a << para.first << para.second;
	return a;
} */

//словарь
template <class TKey, class TElement>
class IDictionary {
private:
	int Count;

public:
	BinaryTree<TKey, TElement>* Tree;

	IDictionary() {
		Tree = new BinaryTree<TKey, TElement>();
	}

	~IDictionary() {
		Tree->Clear();
	}

	int GetCount() {
		return Tree->GetCount();
	}

	BinaryTree<TKey, TElement>* GetTree() {
		return Tree;
	}

	bool CheckKey(TKey key) {
		return Tree->EntryCheck(key);
	}

	TElement Get(TKey key) {
		if (CheckKey(key))
			return Tree->FindValue(key);
		else
			throw exception("Element not found");
	}

	void Insert(TKey key, TElement element) {
		Tree->Insert(key, element);
		++this->Count;
	}

	void Delete(TKey key) {
		Tree->DeleteNode(key);
	}

	void Clear() {
		Tree->Clear();
	}
};

