#pragma once
#include"Data.h"
#include<initializer_list>
#include<cassert>
#include"Func.h"
#include"MyException.h"

template<class T>
class List
{
	Data<T>* first = nullptr;
	Data<T>* last = nullptr;
	size_t   size = 0;

	Data<T>* find(size_t ind);

public:
	List() {	}
	List(initializer_list<T> list);
	~List();
	List(const List& l);
	List<T>& operator=(const List<T>& l);

	void push_back(const T& value);
	void push_front(const T& value);
	void insert(const T& value, size_t ind);

	void pop_back();
	void pop_front();
	void remove(size_t ind);

	T front();
	T back();
	T at(size_t ind);

	T& operator[](size_t ind);

	size_t length() const;
	bool isEmpty() const;
	void clear();
	void print(char t = ' ') const;
	void print_reverse(char t = ' ') const;

	List<T> operator+(const List<T>& l);
	void operator+=(const List<T>& l);


	void sort(bool(*method)(T, T) = asc);
	void reverse();

	void saveInFile();
};

template<class T>
Data<T>* List<T>::find(size_t ind)
{
	Data<T>* pos;
	if (ind <= size / 2)
	{
		pos = first;
		for (size_t i = 0; i < ind - 1; i++)
		{
			pos = pos->next;
		}
	}
	else
	{
		pos = last;
		for (size_t i = 0; i < size - ind; i++)
		{
			pos = pos->prev;
		}
	}
	return pos;
}

template<class T>
List<T>::List(initializer_list<T> list)
{
	for (T l : list)
	{
		push_back(l);
	}
}

template<class T>
List<T>::~List()
{
	this->clear();
}

template<class T>
List<T>::List(const List& l)
{
	Data<T>* temp = l.first;
	while (temp)
	{
		this->push_back(temp->value);
		temp = temp->next;
	}
}

template<class T>
List<T>& List<T>::operator=(const List<T>& l)
{
	if (this == &l)
		return *this;

	this->clear();

	Data<T>* temp = l.first;
	while (temp)
	{
		this->push_back(temp->value);
		temp = temp->next;
	}

	return *this;
}

template<class T>
void List<T>::push_back(const T& value)
{
	if (size == 0)
	{
		last = new Data<T>;
		//якщо пам'ять не виділилась то виклик виключення
		if (!last)
			throw BadAlloc(to_string(__LINE__), __FILE__);

		last->value = value;
		first = last;
	}
	else
	{
		last->next = new Data<T>;

		if (!last->next)
			throw BadAlloc(to_string(__LINE__), __FILE__);

		last->next->value = value;
		last->next->prev = last;
		last = last->next;
	}
	size++;
}

template<class T>
void List<T>::push_front(const T& value)
{
	if (size == 0)
	{
		last = new Data<T>;
		
		if (!last)
			throw BadAlloc(to_string(__LINE__), __FILE__);

		last->value = value;
		first = last;
	}
	else
	{
		first->prev = new Data<T>;

		if (!first->prev)
			throw BadAlloc(to_string(__LINE__), __FILE__);

		first->prev->value = value;
		first->prev->next = first;
		first = first->prev;
	}
	size++;
}

template<class T>
void List<T>::insert(const T& value, size_t ind)
{
	//assert(ind >= 0 && ind <= size);

	if (ind < 0 || ind > size)
		throw OutOfRange(to_string(__LINE__), __FILE__, to_string(ind));

	if (ind == 0)
	{
		this->push_front(value);
	}
	else if (ind == size)
	{
		this->push_back(value);
	}
	else
	{
		Data<T>* pos = find(ind);
		Data<T>* temp = new Data<T>;
		temp->value = value;
		temp->next = pos->next;
		temp->next->prev = temp;
		pos->next = temp;
		temp->prev = pos;
	}
}

template<class T>
void List<T>::pop_back()
{
	//assert(size > 0);
	if (size <= 0)
		throw LengthError(to_string(__LINE__), __FILE__, to_string(size));
	if (size == 1)
	{
		delete last;
		last = first = nullptr;
	}
	else
	{
		last = last->prev;
		delete last->next;
		last->next = nullptr;
	}
	size--;
}

template<class T>
void List<T>::pop_front()
{
	//assert(size > 0);
	if (size <= 0)
		throw LengthError(to_string(__LINE__), __FILE__, to_string(size));
	if (size == 1)
	{
		delete first;
		first = last = nullptr;
	}
	else
	{
		first = first->next;
		delete first->prev;
		first->prev = nullptr;
	}
}

template<class T>
void List<T>::remove(size_t ind)
{
	//assert(ind >= 0 && ind < size);
	if (ind < 0 || ind >= size)
		throw OutOfRange(to_string(__LINE__), __FILE__, to_string(ind));

	if (ind == 0)
	{
		this->pop_front();
	}
	else if (ind == size - 1)
	{
		this->pop_back();
	}
	else
	{
		Data<T>* pos = find(ind+1);
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		delete pos;
		size--;
	}
}

template<class T>
T List<T>::front()
{
	//assert(size > 0);
	if (size <= 0)
		throw LengthError(to_string(__LINE__), __FILE__, to_string(size));
	return first->value;
}

template<class T>
T List<T>::back()
{
	//assert(size > 0);
	if (size <= 0)
		throw LengthError(to_string(__LINE__), __FILE__, to_string(size));
	return last->value;
}

template<class T>
T List<T>::at(size_t ind)
{
	return this->operator[](ind);
}

template<class T>
T& List<T>::operator[](size_t ind)
{
	//assert(ind >= 0 && ind < size);
	if (ind < 0 || ind >= size)
		throw OutOfRange(to_string(__LINE__), __FILE__, to_string(ind));

	return find(ind+1)->value;
}

template<class T>
size_t List<T>::length() const
{
	return size;
}

template<class T>
bool List<T>::isEmpty() const
{
	return size == 0;
}

template<class T>
void List<T>::clear()
{
	Data<T>* temp = first;
	while (temp)
	{
		first = first->next;
		delete temp;
		temp = first;
	}
	last = nullptr;
	size = 0;
}

template<class T>
void List<T>::print(char t) const
{
	Data<T>* temp = first;
	while (temp)
	{
		cout << temp->value << t;
		temp = temp->next;
	}
	cout << '\n';
}

template<class T>
void List<T>::print_reverse(char t) const
{
	Data<T>* temp = last;
	while (temp)
	{
		cout << temp->value << t;
		temp = temp->prev;
	}
	cout << '\n';
}

template<class T>
List<T> List<T>::operator+(const List<T>& l)
{
	//Перевірка на переповненість лічильника списку
	size_t max_sizeT = (size_t)-1;
	

	if ((max_sizeT - (this->size) - l.size) <= 0)
		throw OverflowError(to_string(__LINE__), __FILE__);

	Data<T>* temp = l.first;
	while (temp)
	{
		this->push_back(temp->value);
		temp = temp->next;
	}

	return *this;
}

template<class T>
void List<T>::operator+=(const List<T>& l)
{
	*this = *this + l;
}

template<class T>
void List<T>::sort(bool(*method)(T, T))
{
	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t j = 0; j < size - 1 - i; j++)
		{
			T& val1 = this->operator[](j);
			T& val2 = this->operator[](j + 1);
			if (method(val1, val2))
			{
				swap(val1, val2);
			}
		}
	}
}

template<class T>
void List<T>::reverse()
{
	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t j = 0; j < size - 1 - i; j++)
		{
			T& val1 = this->operator[](j);
			T& val2 = this->operator[](j + 1);
			if (val1 < val2)
			{
				swap(val1, val2);
			}
		}
	}
}

template<class T>
void List<T>::saveInFile()
{
	std::ofstream fout;
	fout.open("List.txt", std::ios::app);

	if (!fout)
		throw FileSystemError(to_string(__LINE__), __FILE__);

	Data<T>* temp = first;
	while (temp)
	{
		fout << temp->value << ' ';
		temp = temp->next;
	}	
	fout << '\n';
	fout.close();


}


