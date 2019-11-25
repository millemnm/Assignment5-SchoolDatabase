#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#include <iostream>
#include <stdio.h>
#include "Student.h"
//#include "Faculty.h"

using namespace std;

template <class type>
class BSTree
{
private:
	typedef struct node
	{
		type data;
		node *parent; //parent
		node *rChild; //right child - Larger
		node *lChild; //left child - Smaller
	} * node_ptr;

	node_ptr root; //root node

	int size;

	void insert(node_ptr newNode); //recursive function to help insert
	type search(int key, node_ptr curr);
	bool find(int key, node_ptr curr);

	void removal(node_ptr del);
	void printer(node_ptr curr);

	void Serialize(node_ptr curr, ostream &out);
	void Deserialize(node_ptr curr, istream &in);
public:
	BSTree();
	~BSTree();

	void insert(type data); //inserts new data into bst
	type remove(int key);
	type search(int key); //find data by the key
	bool find(int key); //returns true if that key exists

	int findMin(); //finds smallest key
	int findMax(); //finds largest key
	int findRoot(); //finds roots key

	int getSize();
	bool isEmpty();

	void PrintTree();

	void Serialize(ostream &out);
	void Deserialize(istream &in);
};


//default constructor
template <class type>
BSTree<type>::BSTree(){
	size = 0;
	root = nullptr;
}
//destructor
template <class type>
BSTree<type>::~BSTree(){
	root = nullptr;
}

//Insert data into the tree in it's correct place
template <class type>
void BSTree<type>::insert(type data){
	if(isEmpty()){
		root = new node;
		root->data = data;
		root->parent = nullptr;
		root->rChild = nullptr;
		root->lChild = nullptr;
		size++;
	}else{
		node_ptr newNode = new node;
		newNode->data = data;
		newNode->parent = root;
		newNode->rChild = nullptr;
		newNode->lChild = nullptr;
		insert(newNode);
		size++;
	}
}
template <class type>
void BSTree<type>::insert(node_ptr newNode){ //recursive overloaded function
	if(newNode->data > newNode->parent->data){ // inserted to the right if greater
		if(newNode->parent->rChild == nullptr){ //check if it can be the child
			newNode->parent->rChild = newNode;
		}else{
			newNode->parent = newNode->parent->rChild;
			insert(newNode); //recursion
		}
	}else{ //inserted to the left if less or equal (but should never be equal)
		if(newNode->parent->lChild == nullptr){ //check if it can be the child
			newNode->parent->lChild = newNode;
		}else{
			newNode->parent = newNode->parent->lChild;
			insert(newNode); //recursion
		}
	}
}

//the method to call to removea a node from a given key
template <class type>
type BSTree<type>::remove(int key){
	node_ptr curr = root;
	if(curr->data == key){
		removal(curr);
		size--;
		return curr->data;
	}else{ //if it actually has to search through to find it's pointer
		while(curr != nullptr){
			if(curr->data == key){
				removal(curr);
				size--;
				return curr->data;
			}else if(curr->data < key){ //check to the right
				curr = curr->rChild;
			}else{
				curr = curr->lChild;
			}
		}
	}
}
//The Function that actually removes the node
template <class type>
void BSTree<type>::removal(node_ptr del){
	if(del->lChild == nullptr && del->rChild == nullptr){ //no children
		if(del == root){ //if root
			root = nullptr;
		}else if(del->parent->lChild == del){ //if its the left child
			del->parent->lChild = nullptr;
		}else{ //if its the right child
			del->parent->rChild = nullptr;
		}
	}else if(del->lChild != nullptr && del->rChild != nullptr){ //2 children
		node_ptr curr = del->rChild;
		if(curr->lChild == nullptr){ //if there arent any left children
			if(del == root){ //if root
				root = curr;
				curr->lChild = del->lChild;
				curr->lChild->parent = curr;
			}else{
				curr->lChild = del->lChild;
				curr->lChild->parent = curr;
			}
		}else{ //if there is a successor
			while(curr->lChild != nullptr){
				curr = curr->lChild;
			}
			if(del == root){ //if root
				curr->parent->lChild = curr->rChild;
				curr->lChild = del->lChild;
				curr->rChild = del->rChild;
				root = curr;
				curr->parent = nullptr;
			}else{
				curr->parent->lChild = curr->rChild;
				curr->lChild = del->lChild;
				curr->rChild = del->rChild;
				curr->parent = del->parent;
			}
		}
	}else if(del->rChild != nullptr){ //right child
		if(del == root){ //if root
			root = del->rChild;
			root->parent = nullptr;
		}else if(del->parent->lChild == del){
			del->parent->lChild = del->rChild;
			del->rChild->parent = del->parent;
		}else{
			del->parent->rChild = del->rChild;
			del->rChild->parent = del->parent;
		}
	}else{ //left child
		if(del == root){ //if root
			root = del->lChild;
			root->parent = nullptr;
		}else if(del->parent->lChild == del){
			del->parent->lChild = del->lChild;
			del->lChild->parent = del->parent;
		}else{
			del->parent->rChild = del->lChild;
			del->lChild->parent = del->parent;
		}
	}
}

//Search for data from the key
template <class type>
type BSTree<type>::search(int key){
	node_ptr curr = root;
	if(curr->data == key){
		return curr->data;
	}else{
		return search(key, curr);
	}
}
template <class type>
type BSTree<type>::search(int key, node_ptr curr){ //recursive overloaded function
	if(curr->data < key){ //check to the right
		curr = curr->rChild;
		if(curr->data == key){
			return curr->data;
		}else{
			return search(key, curr);
		}
	}else{ //check to the left
		curr = curr->lChild;
		if(curr->data == key){
			return curr->data;
		}else{
			return search(key, curr);
		}
	}
}

//returns true if key exists
template <class type>
bool BSTree<type>::find(int key){
	node_ptr curr = root;
	if(isEmpty()){
		return false;
	}else if(curr->data == key){
		return true;
	}else{
		return find(key, curr);
	}
}
template <class type>
bool BSTree<type>::find(int key, node_ptr curr){ //recursive overloaded function
	if(curr->data < key){ //check to the right
		curr = curr->rChild;
		if(curr == nullptr){
			return false;
		}else if(curr->data == key){
			return true;
		}else{
			return find(key, curr);
		}
	}else{ //check to the left
		curr = curr->lChild;
		if(curr == nullptr){
			return false;
		}else if(curr->data == key){
			return true;
		}else{
			return find(key, curr);
		}
	}
}

//finds Smallest Key
template <class type>
int BSTree<type>::findMin(){
	node_ptr curr = root;
	if(curr == nullptr){
		return -1;
	}else{
		while(curr->lChild != nullptr){
			curr = curr->lChild;
		}
		return curr->getID();
	}
}
//Finds Largest Key
template <class type>
int BSTree<type>::findMax(){
	node_ptr curr = root;
	if(curr == nullptr){
		return -1;
	}else{
		while(curr->rChild != nullptr){
			curr = curr->rChild;
		}
		return curr->getID();
	}
}
//Finds Roots Key
template <class type>
int BSTree<type>::findRoot(){
	if(root == nullptr){
		return -1;
	}else{
		return root->data.getID();
	}
}

//Prints the tree in order from least to greatest key
template <class type>
void BSTree<type>::PrintTree(){
	if(isEmpty()){
		std::cout << "The Tree is Empty!" << '\n';
	}else{
		printer(root);
	}
}
template <class type>
void BSTree<type>::printer(node_ptr curr){
	if(curr->lChild != nullptr){
		printer(curr->lChild);
	}

	curr->data.print();
	//std::cout << curr->data << '\n' << '\n';

	if(curr->rChild != nullptr){
		printer(curr->rChild);
	}
}

template <class type>
int BSTree<type>::getSize(){
	return size;
}

template <class type>
bool BSTree<type>::isEmpty(){
	return (size == 0);
}

template <class type>
void BSTree<type>::Serialize(ostream &out){
	out << root->data;
	Serialize(root->lChild, out);
	Serialize(root->rChild, out);
	out << "!\n";
}
template <class type>
void BSTree<type>::Deserialize(istream &in){
	root = new node;
	root->data.deserialize(in);
	root->parent = nullptr;
	size++;

	if(in.peek() != '!'){
		root->lChild = new node;
		root->lChild->parent = root;
		Deserialize(root->lChild, in);
	}else{
		string emptystr;
		getline(in, emptystr); // skip the line with !
		root->lChild = nullptr;
	}

	if(in.peek() != '!'){
		root->rChild = new node;
		root->rChild->parent = root;
		Deserialize(root->rChild, in);
	}else{
		string emptystr;
		getline(in, emptystr); // skip the line with !
		root->rChild = nullptr;
	}

}
//Recursive:
template <class type>
void BSTree<type>::Serialize(node_ptr curr, ostream &out){
	if(curr == nullptr){//put a marker (!) where any empty children aren
		out << "!\n";
		return;
	}else{
		out << curr->data;
		Serialize(curr->lChild, out);
		Serialize(curr->rChild, out);
	}
}
template <class type>
void BSTree<type>::Deserialize(node_ptr curr, istream &in){
	curr->data.deserialize(in);
	size++;

	if(in.peek() != '!'){
		curr->lChild = new node;
		curr->lChild->parent = curr;
		Deserialize(curr->lChild, in);
	}else{
		string emptystr;
		getline(in, emptystr); // skip the line with !
		curr->lChild = nullptr;
	}

	if(in.peek() != '!'){
		curr->rChild = new node;
		curr->rChild->parent = curr;
		Deserialize(curr->rChild, in);
	}else{
		string emptystr;
		getline(in, emptystr); // skip the line with !
		curr->rChild = nullptr;
	}
}

#endif
