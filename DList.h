#ifndef DOUBLELINKEDLIST
#define DOUBLELINKEDLIST
#include <iostream>

using namespace std;

template <class type>
class DList
{
private:
	typedef struct node
	{
		type data;
		node *next; //next node
		node *prev; //previous node
	} * node_ptr;

	node_ptr head; //head node
	node_ptr tail; //tail node

	int size;

public:
	DList();
	~DList();

	type getFront();
	type getBack();
	type getIndex(int index);

	void addFront(type data); //add data to the front (head)
	void addBack(type data); //add data to the back (tail)
	void addMiddle(type data, int index); //add data at a specific index
	void addSort(int data); //for int data type only!!!

	bool remove(type data); //remove data with specific data
	type removeHead(); //remove from the front and return the data
	type removeTail(); //remove from the back and return data

	int getSize();
	bool isEmpty();
	void print();

	friend ostream & operator << (ostream &out, const DList &l1){
		if(l1.isEmpty()){
			out << "EMPTY";
			return out;
		}else{
			out << l1.getIndex(0);
			for(int i = 1; i < l1.size; ++i){
				out << ", " << l1.getIndex(i);
			}
			return out;
		}
	}
};


//default constructor
template <class type>
DList<type>::DList(){
	size = 0;
	head = nullptr;
	tail = nullptr;
}
//destructor
template <class type>
DList<type>::~DList(){
	node_ptr curr = head;
	while(curr != nullptr){
		node_ptr del = curr;
		if(curr->next != nullptr){
			curr = curr->next;
		}
		delete del;
	}
}

template <class type>
type DList<type>::getFront(){
	return head->data;
}
template <class type>
type DList<type>::getBack(){
	return tail->data;
}
template <class type>
type DList<type>::getIndex(int index){
	node_ptr curr = head;
	for(int i = 0; i < index; ++i){
		curr = curr->next;
	}
	return curr->data;
}

template <class type>
void DList<type>::addFront(type data){
	node_ptr newNode = new node;
	newNode->data = data;
	newNode->next = nullptr;
	newNode->prev = nullptr;

	if(isEmpty()){
		head = newNode;
		tail = newNode;
	}else{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	size++;
}
template <class type>
void DList<type>::addBack(type data){
	node_ptr newNode = new node;
	newNode->data = data;
	newNode->next = nullptr;
	newNode->prev = nullptr;

	if(isEmpty()){
		head = newNode;
		tail = newNode;
	}else{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	size++;
}

template <class type>
void DList<type>::addMiddle(type data, int index){
	if(index >= size){ //check if it's the new tail or to large
		addBack(data);
	}else if(index == 0){ //check if its a new head
		addFront(data);
	}else{
		node_ptr prev_ptr = head;
		node_ptr newNode = new node;
		newNode->data = data;

		for(int i = 0; i < index; ++i){ //iterate through the list
			prev_ptr = prev_ptr->next;
		}
		node_ptr next_ptr = prev_ptr->next;
		newNode->prev = prev_ptr;
		newNode->next = next_ptr;
		prev_ptr->next = newNode;
		next_ptr->prev = newNode;

		size++;
	}
}
template <class type> // ONLY FOR INT DATA TYPE!
void DList<type>::addSort(int data){ // Adds the data from smallest to largest
	node_ptr newNode = new node;
	newNode->data = data;
	newNode->next = nullptr;
	newNode->prev = nullptr;

	if(isEmpty()){
		head = newNode;
		tail = newNode;
	}else if(head->data >= newNode->data){
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}else if(tail->data <= newNode->data){
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}else{
		node_ptr curr_ptr = head->next;
		while(curr_ptr->data < newNode->data){
			curr_ptr = curr_ptr->next;
		}
		node_ptr prev_ptr = curr_ptr->prev;
		newNode->next = curr_ptr;
		newNode->prev = prev_ptr;
		prev_ptr->next = newNode;
		curr_ptr->prev = newNode;
	}
	size++;
}

template <class type>
bool DList<type>::remove(type data){
	node_ptr curr_ptr = head;

	if(isEmpty()){
		return false;
	}

	while(curr_ptr != nullptr){ //iterate through till it finds the correct data
		if(data == curr_ptr->data){ //if it finds the data its looking for
			node_ptr currPrev = curr_ptr->prev;
			node_ptr currNext = curr_ptr->next;

			if(size == 1){ //if its removing the only element
				head = nullptr;
				tail = nullptr;
			}else if(currPrev == nullptr){ //if it's removing the head
				currNext->prev = nullptr;
				head = currNext;
			}else if(currNext == nullptr){ //if its removing the tail
				currPrev->next = nullptr;
				tail = currPrev;
			}else{
				currPrev->next = currNext;
				currNext->prev = currPrev;
			}
			size--;
			return true;
		}
		curr_ptr = curr_ptr->next;
	}
	return false;
}

template <class type>
type DList<type>::removeHead(){
	if(size == 1){ //if the list is about to become empty
		type ans = head->data;
		head = nullptr;
		tail = nullptr;
		size = 0;
		return ans;
	}
	type ans = head->data;
	node_ptr curr = head->next;
	curr->prev = nullptr;
	head = curr;
	size--;
	return ans;
}
template <class type>
type DList<type>::removeTail(){
	if(size == 1){ //if the listis about to become empty
		type ans = head->data;
		head = nullptr;
		tail = nullptr;
		size = 0;
		return ans;
	}
	type ans = tail->data;
	node_ptr curr = tail->prev;
	curr->next = nullptr;
	tail = curr;
	size--;
	return ans;
}

template <class type>
int DList<type>::getSize(){
	return size;
}

template <class type>
bool DList<type>::isEmpty(){
	return (size == 0);
}

template <class type>
void DList<type>::print(){
	if(isEmpty()){
		std::cout << "EMPTY" << '\n';
	}else{
		std::cout << getIndex(0);
		for(int i = 1; i < size; ++i){
			std::cout << ", " << getIndex(i);
		}
		std::cout << '\n';
	}
}

#endif
