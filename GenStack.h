#ifndef GENSTACK_H
#define GENSTACK_H
#include <iostream>
#include <cstdlib>
#include <stdexcept>

//Default capacity for the stack
const int SIZE = 5;

using namespace std;

template <class type>
class GenStack
{
	public:
		GenStack();//constructor
		GenStack(int maxSize);//overloaded constructor
		~GenStack();//destructor

		void push(type d);
		type pop();
		type peek();//aka top()

		bool isFull();
		bool isEmpty();

	private:
		int size;
		int top;

		type *myArray;
};

//default constructor
template <class type>
GenStack<type>::GenStack(){
	size = SIZE;
	myArray = new type[size];
	top = -1;
}

template <class type>
GenStack<type>::GenStack(int maxSize){
	myArray = new type[maxSize];
	size = maxSize;
	top = -1;
}

template <class type>
GenStack<type>::~GenStack(){
	delete myArray;
}

template <class type>
void GenStack<type>::push(type d){
	//Instead of making the array longer, remove the first item
	if(isFull()){
		--top;
		type * newArray = new type[size];
		for(int i = 0; i < top; ++i){
			newArray[i] = myArray[i+1];
			myArray = newArray;
		}
	}
	myArray[++top] = d;
}

template <class type>
type GenStack<type>::pop(){
	//check if its empty
	if(isEmpty()){
		throw std::out_of_range("Stack Underflow");
	}
	return myArray[top--];
}

template <class type>
type GenStack<type>::peek(){
	if(isEmpty()){
		throw std::out_of_range("Stack Underflow");
	}
	return myArray[top];
}

template <class type>
bool GenStack<type>::isFull(){
	return (top == size-1);
}

template <class type>
bool GenStack<type>::isEmpty(){
	return (top == -1);
}

#endif
