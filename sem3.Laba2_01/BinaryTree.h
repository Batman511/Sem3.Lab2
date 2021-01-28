#pragma once
#define TN TreeNode<TKey, TValue>*

template <class TKey, class TValue>
class TreeNode {
public:
	TreeNode(TValue& value, TKey& key);
	TreeNode();
	TKey GetKey();
	TValue GetValue();
	void SetLeft(TN const left);
	void SetRight(TN const right);
	void SetKey(const TKey& new_key);
	TN GetLeft() const;
	TN GetRight() const;
	int height(TN subTree);
};


template<class TKey, class TValue>
class BinaryTree {
public:
	TN root;
	TN GetRoot();
	BinaryTree();
	BinaryTree(TN root);
	~BinaryTree();
	void Travel(TN list, TN root, int& index);
	void Balance();
	void Insert(TKey new_key, TValue new_value);
	void Clear();
	int GetCount();
	int Height();
	bool EntryCheck(TKey key);
	TValue FindValue(TKey key);
	void DeleteNode(TKey key);
	//void PrintTree(TN Node, int lvl);
	//void PrintKeyValue(TN Node, int lvl);
	void Map(TValue(*foo)(TValue), TN Node);
	void Map(TValue(*foo)(TValue));
};

template <class TKey, class TElement>
class IDictionary {
private:
	int Count;

public:
	BinaryTree<TKey, TElement>* Tree;
	IDictionary();
	~IDictionary();
	int GetCount();
	TreeNode<TKey, TElement>* GetTree();
	bool CheckKey(TKey key);
	TElement Get(TKey key);
	//void PrintBigTree();
	//void PrintItems();
	void Insert(TKey key, TElement element);
	void Delete(TKey key);
	void Clear();
};