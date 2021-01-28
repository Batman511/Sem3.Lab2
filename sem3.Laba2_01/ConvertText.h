#pragma once
#include "List_Sequence.h"
#include <string>
//#include "ConvertText.cpp"
#include <sstream>
#include "BinaryTree.h"
using namespace std;

LinkedListSequence<string>* file_list();
LinkedListSequence<string>* write_list();
int Length(LinkedListSequence<string>* words);
IDictionary<string, int>* create_ID(LinkedListSequence<string>* words, int sizepages, int choose);
void interface_Text();



