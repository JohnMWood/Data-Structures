/***********************************************************************
* File:
*    queue.h
* Authors:
*    John Wood and Etienne Beaulac (Group 3)
* Description:
*    Our implementation of the queue STL class
************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <assert.h>
using std::cout;
using std::endl;
using std::cin;

namespace custom
{

/***********************************************************************
* QUEUE :: Class Definition
* Queue method and member variable definitions
************************************************************************/
template <class T>
class queue
{
private:
	T *array;
	int numPush;
	int numPop;
	int numCapacity;

	void resize(int newCapacity)					throw (const char *);
	int iHead() { return numPop % numCapacity; }
	int iTail() { return (numPush - 1) % numCapacity; }

public:
	queue() : array(NULL), numPush(0), numPop(0), numCapacity(0) {  }
	queue(int newCapacity) 							throw (const char *);
	queue(const queue <T> & rhs) 					throw (const char *);
	~queue();

	queue <T> & operator = (const queue <T> & rhs)	throw (const char *);

	void debug();

	int size()		const { return numPush - numPop; }
	bool empty()	const { return numPush == numPop; }
	void clear();
	void push(const T & t)							throw (const char *);
	void pop();
	T & front()					  					throw (const char *);
	const T & front()		const 		  			throw (const char *);
	T & back()					 					throw (const char *);
	const T & back()		const 		 			throw (const char *);
};

/*******************************************
* QUEUE :: Assignment
* Assignment operator overload for queue
*******************************************/
template <class T>
queue <T> & queue <T> :: operator = (const queue <T> & rhs)
	throw(const char *)
{
	try
	{
		if (array == rhs.array)
			return *this;

		if (numCapacity < rhs.size())
			resize(rhs.size());

		numPop = 0;
		numPush = 0;

		assert(numCapacity >= rhs.size());
		for (int i = rhs.numPop; i < rhs.numPush; i++)
			push(rhs.array[i % rhs.numCapacity]);

		return *this;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new buffer for queue";
	}
}

/*******************************************
* QUEUE :: Non-Default Constructor
* Takes in a capacity and sets the member variables
*******************************************/
template <class T>
queue <T> :: queue(int newCapacity) throw (const char *)
{
	if (newCapacity == 0)
		return;

	array = NULL;
	numCapacity = 0;
	numPush = 0;
	numPop = 0;

	try
	{
		resize(newCapacity);
		numCapacity = newCapacity;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}
}

/*******************************************
* QUEUE :: Copy Constructor
* Creates a copy of a queue, using the assignment operator
*******************************************/
template <class T>
queue <T> :: queue(const queue <T> & rhs) throw (const char *)
{
	array = NULL;
	numCapacity = 0;
	numPush = 0;
	numPop = 0;
	*this = rhs;
}

/*******************************************
* QUEUE :: Deconstructor
* Deconstructor for the queue class
*******************************************/
template <class T>
queue <T> :: ~queue()
{
	if (numPush != numPop)
		delete[] array;
}



/*******************************************
* QUEUE :: CLEAR
* Clear the elements in the queue
*******************************************/
template<class T>
void queue<T> :: clear()
{
	numPush = 0;
	numPop = 0;
}

/*******************************************
* QUEUE :: RESIZE
* Resize the array and wrap the existing elements
*******************************************/
template<class T>
void custom::queue<T> :: resize(int newCapacity)	throw(const char *)
{
	try
	{
		assert(numCapacity >= 0);
		if (newCapacity == 0)
			return;


		if (size() > 0)
		{
			int tempPush = 0;
			T * temp = new T[newCapacity];
			for (int i = 0; i < size(); i++)
			{
				temp[i] = array[iHead()];
				tempPush++;
				numPush++;
				pop();
			}

			delete[] array;
			array = temp;
			numPush = tempPush;
			numPop = 0;
		}
		else
		{
			array = new T[newCapacity];
			numPush = 0;
			numPop = 0;
		}

		numCapacity = newCapacity;
		assert(size() <= numCapacity);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new buffer for vector";
	}
}

/*******************************************
* QUEUE :: PUSH
* Push a new element into the queue
*******************************************/
template <class T>
void queue <T> ::push(const T & t)				throw (const char *)
{
	try
	{
		if (numCapacity == 0)
		{
			assert(array == NULL);
			resize(1);
		}
		else if (size() >= numCapacity)
			resize(numCapacity * 2);

		assert(size() <= numCapacity);
		this->numPush++;
		this->array[iTail()] = t;

		assert(size() <= numCapacity);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new buffer for vector";
	}
}

/*******************************************
* QUEUE :: POP
* Remove the element at the head of the queue
*******************************************/
template <class T>
void queue <T> ::pop()
{
	if (size() > 0)
		numPop++;
}

/*******************************************
* QUEUE :: FRONT
* Return the first element in the array by reference
*******************************************/
template<class T>
T & custom::queue<T> :: front() throw(const char *)
{
	try
	{
		if (size() <= 0)
			throw "ERROR: attempting to access an item in an empty queue";

		if (size() > 0)
			return array[iHead()];
	}
	catch (...)
	{
		throw "ERROR: attempting to access an item in an empty queue";
	}
}

/*******************************************
* QUEUE :: FRONT
* Return the first element in the array as const
*******************************************/
template<class T>
const T & custom::queue<T> :: front() const throw(const char *)
{
	try
	{
		if (size() <= 0)
			throw "ERROR: attempting to access an item in an empty queue";

		if (size() > 0)
			return array[iHead()];
	}
	catch (...)
	{
		throw "ERROR: attempting to access an item in an empty queue";
	}
}

/*******************************************
* QUEUE :: BACK
* Return the last element in the list by reference
*******************************************/
template<class T>
T & custom::queue<T> :: back() throw(const char *)
{
	try
	{
		if (size() <= 0)
			throw "ERROR: attempting to access an item in an empty queue";

		// return the last element
		if (size() > 0)
			return array[iTail()];
	}
	catch (...)
	{
		throw "ERROR: attempting to access an item in an empty queue";
	}
}

/*******************************************
* QUEUE :: BACK
* Return the last element in the list as const
*******************************************/
template<class T>
const T & custom::queue<T> :: back() const throw(const char *)
{
	try
	{
		if (size() <= 0)
			throw "ERROR: attempting to access an item in an empty queue";

		// return the last element
		if (size() > 0)
			return array[iTail()];
	}
	catch (...)
	{
		throw "ERROR: attempting to access an item in an empty queue";
	}
}

}; // namespace custom

#endif // QUEUE_H
