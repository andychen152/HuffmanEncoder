#ifndef __NODE_H__
#define __NODE_H__

class Node {
	private:
		char data;
		Node *leftChild;
		Node *rightChild;
	public:
		Node(char data, Node* left, Node* right){
			this->data = data;
			this->leftChild = left;
			this->rightChild = right;
		}

		char getData() const {
			return this->data;
		}

		void setData(const char &newData){
			this->data = newData;
		}

		Node* getLeftChild() const {
			return this->leftChild;
		}

		void setLeftChild(Node *newLeftChild){
			this->leftChild = newLeftChild;
		}

		Node* getRightChild() const {
			return this->rightChild;
		}

		void setRightChold(Node *newRightChild){
			this->rightChild = newRightChild;
		}
};
#endif