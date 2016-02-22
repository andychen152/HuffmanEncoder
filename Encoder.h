#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <utility>
#include <string>
#include <iostream>
#include <iomanip>
#include "Node.h"

using namespace std;


class Encoder{
	private:
		int uniqueChar;
		pair<int, Node*> * compressedArray;
		string *codeHolder;
		string encodedOutput;
		string decodedOutput;
		Node *decodePointer;
	public:
		Encoder();
		
		void combineAll();
		void compressArray(int *oldArray);
		void heapify();
		void swap(const int &parentIndex, const int &childIndex);
		void print();
		void percolateDown(int parent);
		void percolateUp(int child);
		void generateCode();
		void codeGenerator(Node* root, std::string code);
		pair<int, Node*> deleteMin();
		void print2();
		void addDecode(char x);
		void addEncode(char x);
		string getEncodedOutput();
		string getDecodedOutput();
		void print3();
		void initializeDecode(){this->decodePointer = compressedArray[1].second;}


};


#endif