#pragma once
#include <stdexcept>
#include <exception>
#include <iostream>

//const char * IndexOutOfRange = "Index out of range";

template <class T>
class LinkedList {

private:
	struct Node
	{
		T values = 0;
		Node* next = nullptr;
	};

	Node* head = nullptr;
	int size = 0;

public:
	const char* IndexOutOfRange = "Index out of range";
	//конструкторы
	LinkedList() : size(0), head(nullptr)
	{};

	LinkedList(const T* values, const int size) : LinkedList()
	{
		if (size < 0) throw std::length_error("Index is negative");
		if (size == 0) throw std::length_error("Node is empty");

		Node* tail = new Node{ *values,nullptr };
		head = tail;

		for (size_t i = 1; i < size; i++) {
			Node* body = new Node{ *(values + i),nullptr };
			tail->next = body;
			tail = body;
		}

		this->size = size;
	}

	//копирующий конструктор
	LinkedList(LinkedList <T> const& list) {
		Node* body{ head };
		Node* List{ body };

		for (size_t i = 1; i < size; i++, body = body->next) {
			List = new Node{ body->values,List };
		}

		this->size = size;
	}

	//деструктор
	~LinkedList() {
		while (this->head != nullptr) {
			Node* body{ head->next };
			delete[] head;
			this->head = body;
		}

		delete[] this->head;
	}

	//вывод первого элемента списка
	T GetFirst() {
		if (size == 0) throw std::length_error(IndexOutOfRange);
		//std::cout << head->values;

		return head->values;
	}

	//вывод последнего элемента списка
	T GetLast() {
		if (size == 0) throw std::length_error(IndexOutOfRange);
		Node* body{ head };

		for (size_t i = 0; i < size - 1; i++) body = body->next;
		//std::cout << body->values;

		return body->values;
	}

	//получение элемента по индексу
	T Get(int index) {
		if (index < 0 || index >= size) throw std::length_error(IndexOutOfRange);
		Node* body{ head };

		for (size_t i = 0; i < index; i++) body = body->next;
		return body->values;
	}

	T& operator [] (int index) {
		if (index < 0 || index >= size) throw std::length_error(IndexOutOfRange);
		Node* body{ head };

		for (size_t i = 0; i < index; i++) body = body->next;

		return body->values;
	}

	//Получить список всех элементов
	LinkedList<T>* GetSubList(int startIndex, int endIndex) {
		if (startIndex < 0 || endIndex < 0 || startIndex >= size || endIndex >= size || startIndex > endIndex)
			throw std::length_error(IndexOutOfRange);
		Node* body{ head };

		for (size_t i = 0; i < startIndex; i++) body = body->next;

		LinkedList<T>* newNode = new LinkedList<T>;

		for (size_t i = startIndex; i < endIndex + 1; i++) {
			newNode->Prepend(body->values);
			body = body->next;
		}

		newNode->size = endIndex - startIndex + 1;

		return newNode;
	}

	//длина списка
	int GetLength() {
		return size;
	}

	//добавление элемента в начало списка
	void Append(T data) {
		head = new Node{ data,head };

		++size;
	}

	//добавление элемента в конец списка
	void Prepend(T data) {
		if (head == nullptr)  head = new Node{ data,head };
		else {
			Node* body{ head };
			for (size_t i = 1; i < size; i++) body = body->next;
			body->next = new Node{ data,nullptr };
		}

		++size;
	}

	//Вставляет элемент в заданную позицию
	void InsertAt(T data, int index) {
		if (index < 0 || index >= size) throw std::length_error(IndexOutOfRange);
		Node* body{ head };

		if (index == 0) {
			body->values = data;
		}
		else {
			for (size_t i = 0; i < index - 1; i++) body = body->next;

			Node* newNode = new Node{ data,(body->next)->next };
			body->next = newNode;
		}
		//this->size += 1;
	}

	//Соединене двух списков
	LinkedList<T>* Concat(LinkedList<T>* list) {
		Node* body{ this->head };
		LinkedList<T>* newList = new LinkedList<T>();

		for (int i = 0; i < this->size; i++) {
			newList->Prepend(body->values);
			body = body->next;
		}

		Node* body2{ list->head };
		for (int i = this->size; i < (list->size + this->size); i++) {
			newList->Prepend(body2->values);
			body2 = body2->next;
		}

		newList->size = this->size + list->size;

		return newList;
	}

	//Вывод списка
	void Print() {
		for (int i = 0; i < size; i++) {
			std::cout << Get(i) << " ";
		};
		std::cout << "\n";
	}

	//Ввод списка
	void EnterList() {
		std::cout << "Enter size of the List: ";
		int count;
		std::cin >> count;

		for (int i = 0; i < count; i++) {
			T data;
			std::cout << "Element " << i << " : ";
			std::cin >> data;
			Prepend(data);
		}

	}
};