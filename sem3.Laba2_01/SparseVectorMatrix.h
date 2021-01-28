#pragma once
#include "BinaryTree.hpp"
#include "ArraySequence.h"
#include <utility>
using namespace std;


template <class T, class TValue>
IDictionary<int, TValue>* MakeSparseVector(ArraySequence<T>* vector);
IDictionary<pair<long, long>, string>* MakeSparseMatrix(ArraySequence<ArraySequence<string>*>* matrix);
template <class T>
void Print(Sequence<T>* seq, const int length);
template <class T>
ArraySequence<T>* New_vector();
template <class T>
ArraySequence<ArraySequence<string>*>* New_matrix();





