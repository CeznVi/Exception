#include <iostream>
#include <Windows.h>
#include <string>
#include "List.h"


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try
    {
        List<int> l;
        l.push_front(2);
        l.push_front(1);
        l.push_front(12);
        l.push_front(13);
        l.push_front(14);

        //Вийняток №1 - вихід за межі масиву
        //cout << l[5] << '\n';

        //Вийняток №2 - отримати доступ до першого чи останнього елементу списку
        //при розмірі списку < 0 
        l.clear();
        cout << l.back() << '\n';


        l.print();
        l.print_reverse();


    }

    catch (exception& e)
    {
	cout << e.what() << endl;
	MyException* ex = dynamic_cast<MyException*>(&e);
	if(ex)
		ex->saveError();
    }

  
    std::cout << "Hello World!\n";

    return 0;
}

