/***********************************************************************
* File:
*    deque.h
* Authors:
*    John Wood and Etienne Beaulac (Group 3)
* Description:
*    Our implementation of the deque STL class
************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <assert.h>

namespace custom
{

/***********************************************************************
* DEQUE :: Class Definition
* deque method and member variable definitions
************************************************************************/
template <class T>
class deque
{
private:
	T *array;
	int iBack;
	int iFront;
	int numCapacity;

	void resize(int newCapacity)						   throw (const char *);
	int capacity()                      {        return numCapacity;          }
    bool isAllocated() 			        {        return numCapacity > 0;      }
	int iFrontNormalized(int value, int capacity);
	int iBackNormalized(int value);


public:
	deque() : array(NULL), iFront(0), iBack(-1), numCapacity(0) {          }
	deque(int newCapacity) 								   throw (const char *);
	deque(const deque <T> & rhs) 						   throw (const char *);
	~deque() 					        { if (isAllocated()) delete [] array; }
	deque <T> & operator = (const deque <T> & rhs)	       throw (const char *);

	int size()		        const 		{      return iBack - iFront + 1;     }
	bool empty()	        const 		{      return size() == 0;            }
	void clear()                        {      iBack = -1; iFront = 0;        }
    
	void push_front(const T & t)						   throw (const char *);
	void push_back(const T & t)						       throw (const char *);
	void pop_front()                                       throw (const char *);
	void pop_back()                                        throw (const char *);
	T & front()					  					       throw (const char *);
	T & back()					 						   throw (const char *);
    const T & front()		const 		  				   throw (const char *);
	const T & back()		const 		 				   throw (const char *);
};

/*******************************************
* DEQUE :: Assignment
* Assignment operator overload for deque
*******************************************/
template <class T>
deque <T> & deque <T> :: operator = (const deque <T> & rhs)  throw(const char *)
{
	if (&rhs == this)
		return *this;

	clear();

	if (numCapacity < rhs.size())
		resize(rhs.size());

    int capacity = rhs.numCapacity;
	assert(numCapacity >= rhs.size());
	for (int i = rhs.iFront; i <= rhs.iBack; i++)
		push_back(rhs.array[iFrontNormalized(i, capacity)]);

	return *this;
}

/*******************************************
* DEQUE :: Non-Default Constructor
* Takes in a capacity and sets the member variables
*******************************************/
template <class T>
deque <T> :: deque(int newCapacity) 		                throw (const char *)
{
    array = NULL;
    clear();
    numCapacity = 0;
	if (newCapacity == 0)
		return;

	try
	{
		resize(newCapacity);
		numCapacity = newCapacity;
		assert(size() <= numCapacity);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}
}

/*******************************************
* DEQUE :: Copy Constructor
* Creates a copy of a deque, using the assignment operator
*******************************************/
template <class T>
deque <T> :: deque(const deque <T> & rhs)                   throw (const char *)
{
    array = NULL;
    clear();
    numCapacity = 0;
	*this = rhs;
}

/*******************************************
* DEQUE :: RESIZE
* Resize the array and wrap the existing elements
*******************************************/
template<class T>
void custom::deque<T> :: resize(int newCapacity)	         throw(const char *)
{
	try
	{
		assert(numCapacity >= 0);
		if (newCapacity == 0)
			return;

		if (size() > 0)
		{
			int tempBack = -1;
			T * temp = new T[newCapacity];
			for (int i = 0; i < size(); i++)
			{
				temp[i] = array[iFrontNormalized(iFront, numCapacity)];
                tempBack++;
				iBack++;
				pop_front();
			}

			delete[] array;
			array = temp;
			iBack = tempBack;
			iFront = 0;
		}
		else
		{
			array = new T[newCapacity];
			clear();
		}

		numCapacity = newCapacity;
		assert(size() <= numCapacity);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a new buffer for deque";
	}
}

/*******************************************
* DEQUE :: iFrontNormalized
* Calculates the normalized iFront
*******************************************/
template<class T>
int deque <T> ::iFrontNormalized(int value, int capacity)
{
	value %= capacity;
	if (value < 0)
		value += capacity;
	return value;
}

/*******************************************
* DEQUE :: iBackNormalized
* Calculates the normalized iBack
*******************************************/
template<class T>
int deque <T> ::iBackNormalized(int value)
{
	value %= numCapacity;
	if (value < 0)
		value += numCapacity;
	return value;
}

/*******************************************
* DEQUE :: PUSH_BACK
* Push a new element into the back of the deque
*******************************************/
template <class T>
void deque <T> ::push_back(const T & t)				throw (const char *)
{
	try
	{
		if (numCapacity == 0)
		{
			assert(array == NULL);
			resize(1);
		}
		else if (size() >= numCapacity)
			resize(capacity() * 2);

		assert(size() <= numCapacity);
		iBack++;
		array[iBackNormalized(iBack)] = t;
		assert(size() <= numCapacity);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a new buffer for deque";
	}
}

/*******************************************
* DEQUE :: PUSH_FRONT
* Push a new element into the front of the deque
*******************************************/
template <class T>
void deque <T> ::push_front(const T & t)				throw (const char *)
{
	try
	{
		if (numCapacity == 0)
		{
			assert(array == NULL);
			resize(1);
		}
		else if (size() >= numCapacity)
			resize(capacity() * 2);

		assert(size() <= numCapacity);
		iFront--;
		array[iFrontNormalized(iFront, numCapacity)] = t;
		assert(size() <= numCapacity);
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to access data from an empty deque";
	}
}

/*******************************************
* DEQUE :: POP_BACK
* Remove the element at the back of the deque
*******************************************/
template <class T>
void deque <T> ::pop_back() throw (const char *)
{
	if (!empty())
		iBack--;
}

/*******************************************
* DEQUE :: POP_FRONT
* Remove the element at the front of the deque
*******************************************/
template <class T>
void deque <T> ::pop_front() throw (const char *)
{
	if (!empty())
		iFront++;
}

/*******************************************
* DEQUE :: FRONT
* Return the first element in the array by reference
*******************************************/
template <class T>
T & custom::deque<T> :: front() throw(const char *)
{
	if (empty())
		throw "ERROR: unable to access data from an empty deque";
	else
		return array[iFrontNormalized(iFront, numCapacity)];
}

/*******************************************
* DEQUE :: FRONT
* Return the first element in the array as const
*******************************************/
template <class T>
const T & custom::deque<T> :: front() const throw(const char *)
{
	if (empty())
		throw "ERROR: unable to access data from an empty deque";
	else
		return array[iFrontNormalized(iFront, numCapacity)];
}

/*******************************************
* DEQUE :: BACK
* Return the last element in the list by reference
*******************************************/
template <class T>
T & custom::deque<T> :: back() throw(const char *)
{
	if (empty())
		throw "ERROR: unable to access data from an empty deque";
	else
		return array[iBackNormalized(iBack)];
}

/*******************************************
* DEQUE :: BACK
* Return the last element in the list as const
*******************************************/
template <class T>
const T & custom::deque<T> :: back() const throw(const char *)
{
	if (empty())
		throw "ERROR: unable to access data from an empty deque";
	else
		return array[iBackNormalized(iBack)];
}

}; // namespace custom

#endif // deque_H
