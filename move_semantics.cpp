/**************************************
 *NOTE: use -fno-elide-constructors flag
***************************************/

#include <iostream>

using std::cout;
using std::endl;

class A
{
	size_t _size;
	int* _data;

public:
	A()
	{
		cout << "A() called on " << this << endl;
		_size = 100;
		_data = new int[_size];
		for (int i = 0; i < _size; i++)
		{
			_data[i] = rand() % 10;
		}
	}

	A(const A& origin)
	{
		cout << "A(const A& origin) called on "
		     << this << endl;
		this->_size = origin._size;
		this->_data = new int[_size];
		for (int i = 0; i < _size; i++)
		{
			this->_data[i] = origin._data[i];
		}
	}

	A& operator=(const A& origin)
	{
		cout << "operator=(const A& origin) called on "
		     << this << endl;
		if (this != &origin) 
		{
			int* tmp_data = new int[origin._size];
			for (int i = 0; i < origin._size; i++)
			{
				tmp_data[i] = origin._data[i];
			}

			delete this->_data;
			this->_size = origin._size;
			this->_data = tmp_data;
		}
		return *this;
	}

	A(A&& origin) //non-const as we change the origin
	{
		cout << "A(A&&) called on " << this << endl;
		this->_size = origin._size;
		this->_data = origin._data;

		//have to leave origin in a consistent state
		origin._data = nullptr; 
		origin._size = 0;
	}

	A& operator=(A&& origin)
	{
		cout << "operator=(A&& origin) called on "
		     << this << endl;
		if(this != &origin)
		{
			delete[] this->_data;
			this->_size = origin._size;
			this->_data = origin._data;
			origin._data = nullptr;
			origin._size = 0;

		}
		return *this;
	}
	~A()
	{
		cout << "~A() called on " << this << endl;
		delete[] _data;
	}
};

void foo(A a)
{
	cout << "foo()" << endl;
}

A bar()
{
	cout << "bar()" << endl;
	A tmp;
	return tmp;
}


int main()
{
	A a; //A()
	foo(a); //A(const A&), because a is l-value
	foo(std::move(a)); //A(A&&)
	bar(); //A(), then A(A&&)

 }