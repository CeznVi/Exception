#pragma once
#include<fstream>

class MyException : public exception
{
	string err;

public:
	MyException(string l, string f, string e)
	{
		err = (string)__DATE__ + ", " + (string)__TIME__ + ",Line: " + l + ", \nFile: " + f + ",\nError: " + e;
	}

	virtual const char* what() const noexcept
	{
		return err.c_str();
	}

	void saveError()
	{
		ofstream out("log.txt", ios::app);
		out << err << endl;
		out.close();
	}
};
