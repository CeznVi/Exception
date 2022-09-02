#pragma once
#include<fstream>

class MyException : public exception
{
protected:
	string err;

public:
	MyException() {}
	MyException(string l, string f, string e)
	{
		err = (string)__DATE__ + ", " + (string)__TIME__ + ",Line: " + l + ", \nFile: " + f + ",\nError: " + e;
	}

	virtual const char* what() const noexcept
	{
		return err.c_str();
	}

	virtual void saveError()
	{
		ofstream out("log.txt", ios::app);
		out << err << endl;
		out.close();
	}
};

//Вийняток виходу за межі області бачення масиву
class OutOfRange : public MyException
{

public:
	OutOfRange(string l, string f, string e)
	{
		err = (string)__DATE__ + ", " + (string)__TIME__ + ",Line: " + l + ", \nFile: " + f + ",\nError: Index out of range - " + e;
	}
};

//Вийняток виходу за межі при довжині = 0
class LengthError : public MyException
{

public:
	LengthError(string l, string f, string e)
	{
		err = (string)__DATE__ + ", " + (string)__TIME__ + ",Line: " + l + ", \nFile: " + f + ",\nError: Lenght = " + e;
	}
};

//Вийняток при якому операційна система не може виділити пам'ять
class BadAlloc : public MyException
{

public:
	BadAlloc(string l, string f)
	{
		err = (string)__DATE__ + ", " + (string)__TIME__ + ",Line: " + l + ", \nFile: " + f + ",\nError: Out of memory";
	}
};

//Вийняток при якому переповнюэться зміна яка зберігає число
class OverflowError : public MyException
{

public:
	OverflowError(string l, string f)
	{
		err = (string)__DATE__ + ", " + (string)__TIME__ + ",Line: " + l + ", \nFile: " + f + ",\nError: overflow error";
	}
};