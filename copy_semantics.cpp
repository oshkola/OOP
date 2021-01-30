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
		_size = 20;
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
		if (this != &origin) //check self-assignment
		{
			//the trick is to copy _data from origin
			//to the tmp object, and only after that
			//delete this->_data
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

A foo2()
{
	cout << "foo2()" << endl;
	A tmp;
	return tmp;
}


int main()
{
	A a; //A() called
	A a1(a); //A(const A& origin) called
	A a2; //A() called
	a2 = a1; //operator=(const A& origin) called
	foo(a2); // A(const A& origin) called
	foo2(); // A() called. Copy constructor isn't called for some reason
	        // probably due to the Return Value Optimisation.

}
