/***********************************************************************
* Program:
*    Assigment 01, Vector
*    Brother Helfrich, CS 235
* Author:
*    John Wood
* Summary:
*    My implementation of the STL vector class.
************************************************************************/
#ifndef vector_h
#define vector_h

#include <cstdlib>

namespace custom
{

/**************************************************
 * VECTOR
 * Definition of the vector class
 *************************************************/
template<class T>
class vector
{
private:
	T *array;
	int numSize;
	int numCapacity;

	void resize(int num) throw (const char *);

public:
	vector() : numCapacity(0), numSize(0), array(NULL) {}
	vector(int num)           	   throw (const char *);
	vector(int num, T t) 		   throw (const char *);
	vector(const vector <T> & rhs) throw (const char *);
    ~vector() { delete [] array; }

	// include const version of = operator and a non-const
    vector & operator = (const vector & rhs) throw (const char *);
	T & operator [] (int index)       throw (const char *)
	{
		try { return array[index]; }
		catch (...) { throw "ERROR: Invalid index"; }
	}
	T   operator [] (int index) const throw (const char *)
	{
		try { return array[index]; }
		catch (...) { throw "ERROR: Invalid index"; }
	}

	int size()     const { return numSize; }
	int capacity() const { return numCapacity; }

	bool empty();
	void clear();
	void push_back(const T & t) throw (const char *);

	class iterator;
	iterator begin() { return iterator(array); }
	iterator end();

	// extra credit iterator
	class const_iterator;
	const_iterator cbegin() const { return const_iterator(array); }
	const_iterator cend()   const;
};

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int num) throw (const char *)
{
	if (num == 0)
	{
		this->numCapacity = 0;
		this->numSize = 0;
		this->array = NULL;
		return;
	}

	// attempt to allocate
	try
	{
		array = new T[num];
		this->numCapacity = num;
		this->numSize = num;
	}
	catch (...)
	{
		throw "ERROR: Unable to allocate buffer";
	}
}

/*******************************************
 * VECTOR :: NON-DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(int num, T t) throw (const char *)
{
	if (num == 0)
	{
		this->numCapacity = 0;
		this->numSize = 0;
		this->array = NULL;
		return;
	}

	// attempt to allocate
	try
	{
		array = new T[num];
		this->numSize = 0;

		// set all positions in the array to 0
		for (int i = 0; i < num; i++)
		{
			array[i] = t;
			numSize++;
		}
	}
	catch (...)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// copy over member variables
	this->numCapacity = num;
}

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) throw (const char *)
{
	// do nothing if there is nothing to do
	if (rhs.numCapacity == 0)
	{
		this->numCapacity = 0;
		this->numSize = 0;
		this->array = NULL;
		return;
	}

	// attempt to allocate
	try
	{
		array = new T[rhs.numSize];
	}
	catch (...)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	this->numCapacity = rhs.numCapacity;
	this->numSize = rhs.numSize;

	// copy over individual items from the rhs vector to the new one
	for (int i = 0; i < numSize; i++)
		this->array[i] = rhs.array[i];
}

/*******************************************
 * VECTOR :: Assignment Operator
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> &rhs)
			 throw (const char *)
{
	// if the current vector does not have enough capacity,
	// give the current vector more
	if (rhs.size() > capacity())
		resize(rhs.size());

	this->numSize = rhs.numSize;
	this->numCapacity = rhs.numCapacity;

	for (int i = 0; i < size(); i++)
		array[i] = rhs.array[i];

	return *this;
}

/*******************************************
 * VECTOR :: RESIZE
 *******************************************/
template <class T>
inline void vector<T> :: resize(int num) throw (const char *)
{
	try
	{
		T *temp = new T[num];
		for (int i = 0; i < size(); i++)
			temp[i] = array[i];
		delete [] array;
		array = temp;
	}
	catch (...)
	{
		throw "ERROR: Unable to alloacate a new buffer for vector";
	}
}

/*******************************************
 * VECTOR :: EMPTY
 *******************************************/
template <class T>
bool vector <T> :: empty()
{
	if (numSize == 0)
		return true;
	return false;
}

/*******************************************
 * VECTOR :: PUSH_BACK
 *******************************************/
template <class T>
inline void vector <T> :: push_back(const T & t) throw (const char *)
{
	try
	{
		if (array == NULL)
		{
			array = new T[1];
			this->numCapacity = 1;
		}
		// double the capacity if there is no more room in the vector
		else if (size() == capacity())
		{
			this->numCapacity *= 2;
			resize(numCapacity);
		}

		// add the element to the last position in the array
		this->array[numSize] = t;
		this->numSize++;
	}
	catch (...)
	{
		throw "ERROR: Unable to allocate a new buffer for vector";
	}
}

/*******************************************
 * VECTOR :: CLEAR
 *******************************************/
template <class T>
void vector <T> :: clear()
{
	this->numSize = 0;
}

/**************************************************
 * VECTOR ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: iterator
{
public:
	// constructors, destructors, and assignment operator
	iterator()      : p(NULL)      {              }
	iterator(T * p) : p(p)         {              }
	iterator(const iterator & rhs) { *this = rhs; }
	iterator & operator = (const iterator & rhs)
	{
		this->p = rhs.p;
		return *this;
	}

	// equals, not equals operator
	bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
	bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

	// dereference operator
	T & operator * ()
	{
		return *p;
	}

	// prefix increment
	iterator & operator ++ ()
	{
		p++;
		return *this;
	}

	iterator & operator -- ()
	{
		p--;
		return *this;
	}

	// postfix increment
	iterator operator ++ (int postfix)
	{
		iterator tmp(*this);
		p++;
		return tmp;
	}

	iterator operator -- (int postfix)
	{
		iterator tmp(*this);
		p--;
		return tmp;
	}

private:
	T * p;
};

/********************************************
 * VECTOR :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: iterator vector <T> :: end ()
{
	return iterator(array + numSize);
}

/**************************************************
 * VECTOR CONST_ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: const_iterator
{
private:
	T * p;

public:
	// constructors, destructors, and assignment operator
	const_iterator()      : p(NULL)      {              }
	const_iterator(T * p) : p(p)         {              }
	const_iterator(const const_iterator & rhs) { *this = rhs; }
	iterator & operator = (const iterator & rhs)
	{
		this->p = rhs.p;
		return *this;
	}

	// equals, not equals operator
	bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
	bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

	// dereference operator
	// const before == return value is const
	// const after  == cannot change values within the function
	const T operator * () const
	{
		return *p;
	}

	// prefix increment
	const_iterator & operator ++ ()
	{
		p++;
		return *this;
	}

	const_iterator & operator -- ()
	{
		p--;
		return *this;
	}

	// postfix increment
	const_iterator operator ++ (int postfix)
	{
		iterator tmp(*this);
		p++;
		return tmp;
	}

	const_iterator operator -- (int postfix)
	{
		iterator tmp(*this);
		p--;
		return tmp;
	}
};

/********************************************
 * VECTOR :: CEND
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: const_iterator vector <T> :: cend() const
{
	return const_iterator(array + numSize);
}

}; // namespace custom

#endif
