#include "Encoder.h"

// constructor
Encoder::Encoder(){
	this->uniqueChar=0;
	codeHolder = new string[27];
}
	
void Encoder::compressArray(int *oldArray){
	//inputting unique characters
	for(int i=0; i<27; i++){
		if (oldArray[i]!=0)
			uniqueChar++;
	}
	// initializing and setting compressedArray to default of nothing
	// adding 1 to size because first index is not used
	compressedArray = new pair<int, Node*> [uniqueChar+1];
	compressedArray[0].first = 0; compressedArray[0].second = NULL;
	int counter = 1;
	for(int i=0; i<27; i++){
		if (oldArray[i]!=0){
			char input;
			if(i==26)
				input = 32;
			else
				input = i+97;				
			Node *newNode = new Node(input, NULL, NULL);
			compressedArray[counter].second = newNode;
			compressedArray[counter].first = oldArray[i];
			counter++;
		}
		// if it is equal to 0, skip
	}
}

void Encoder::print(){
	for(int i=1; i<=uniqueChar; i++){
		std::cout << compressedArray[i].first << compressedArray[i].second->getData() << std::endl;
	}
}

void Encoder::heapify(){
	//percolate down starting from the first non leaf
	for(int i=uniqueChar/2; i>0; --i){
		percolateDown(i);
	}
}

void Encoder::percolateDown(int parent){
	while(parent*2 <= this->uniqueChar){
		// special case where parent*2+1 does not exist
		if(parent*2==uniqueChar){
			if(compressedArray[parent].first>compressedArray[uniqueChar].first)
				swap(parent, uniqueChar);
			parent = parent*2;
		}
		else if(compressedArray[parent].first>compressedArray[parent*2].first || compressedArray[parent].first>compressedArray[parent*2+1].first){
			// if both child same size or right child bigger, we swap right one
			if(compressedArray[parent*2+1].first <= compressedArray[parent*2].first ){
				swap(parent, parent*2+1);
				parent = parent*2+1;
			}
			else{
				swap(parent, parent*2);
				parent = parent*2;
			}	
		}
		else // end no swap will occur
			break;
	}
}

void Encoder::percolateUp(int child){
	bool keepPercolating = true;
	while(keepPercolating && child!=1){
		if(compressedArray[child].first<compressedArray[child/2].first){
			swap(child, child/2);
			child /= 2;
		}
		else
			keepPercolating=false;	
	}
}

pair<int, Node*> Encoder::deleteMin(){
	pair<int, Node*> tmp;
	tmp.first = compressedArray[1].first;
	tmp.second = compressedArray[1].second;
	compressedArray[1].first = compressedArray[uniqueChar].first;
	compressedArray[1].second = compressedArray[uniqueChar].second;
	compressedArray[uniqueChar].second=NULL;
	//@@@ potentially dlete ??
	uniqueChar--;
	percolateDown(1);
	return tmp;

}

void Encoder::swap(const int &parentIndex, const int &childIndex){
	int tmpChar = compressedArray[parentIndex].first;
	Node* tmp = compressedArray[parentIndex].second;
	compressedArray[parentIndex].second = compressedArray[childIndex].second;
	compressedArray[childIndex].second = tmp;
	compressedArray[parentIndex].first = compressedArray[childIndex].first;
	compressedArray[childIndex].first = tmpChar; 
}

void Encoder::combineAll(){ 
	while(uniqueChar>1){
		pair<int, Node*> holder;
		pair<int, Node*> rightChild = deleteMin();
		pair<int, Node*> leftChild = deleteMin();
		holder.first = rightChild.first + leftChild.first;
		holder.second = new Node('#', leftChild.second, rightChild.second);
		uniqueChar++;
		compressedArray[uniqueChar] = holder;
		percolateUp(uniqueChar);
	}
}

void Encoder::generateCode(){
	codeGenerator(compressedArray[1].second, "");
}

void Encoder::codeGenerator(Node* root, std::string code){
	if(root==NULL)
		return;
	if(root->getRightChild()==NULL && root->getLeftChild()==NULL){
		int index = root->getData();
		if(index==32)
			index = 26;
		else
			index -= 97;
		codeHolder[index] = code;
	}
	if(root->getLeftChild()!=NULL)
		codeGenerator(root->getLeftChild(), code + "1");
	if(root->getRightChild()!=NULL)
		codeGenerator(root->getRightChild(), code + "0");
}

void Encoder::print2(){
	for(int i=0; i<27; i++)
		cout << codeHolder[i] << endl;
}

void Encoder::addEncode(char x){
	if (x==32)
		encodedOutput.append(codeHolder[26]);
	else
		encodedOutput.append(codeHolder[x-97]);
}

string Encoder::getEncodedOutput(){
	return encodedOutput;
}

void Encoder::print3(){
	Node *root = compressedArray[1].second;
	cout << root->getData() << endl;
	root=root->getLeftChild();
	cout << root->getData() << endl;
	root=root->getLeftChild();
	cout << root->getData() << endl;
	root = root->getRightChild();
	cout << root->getData() << endl;
}

void Encoder::addDecode(char x){
	if (x=='0')
		decodePointer = decodePointer->getRightChild();
	else // x==1
		decodePointer = decodePointer->getLeftChild();
	if(decodePointer->getData()!= 35){
		this->decodedOutput += decodePointer->getData();
		decodePointer = compressedArray[1].second;
	}
}

string Encoder::getDecodedOutput(){
	return this->decodedOutput;
}
























