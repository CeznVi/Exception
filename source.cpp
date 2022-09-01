#include <iostream>
#include <Windows.h>
#include <string>
#include "List.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    ///Завдання №1
    try
    {
        List<int> l{2,3,5};
        List<int> l2{ 21,334,45 };
        l.push_back(1212);
        l.push_front(2);
        l.push_front(1);
        l.push_front(12);
        l.push_front(13);
        l.push_front(14);
        l.print();

        //Вийняток №1 - вихід за межі масиву
        //cout << l[5] << '\n';
        //l.remove(6);
        //l.clear();
        //cout << "LENGHT IS " << l.length() << '\n';
        //l.insert(3, 1);


        //Вийняток №2 - отримати доступ до першого чи останнього елементу списку
        //при розмірі списку < 0 
        //l.clear();
        //cout << l.back() << '\n';
        //cout << l.front() << '\n';
        //l.pop_back();
        //l.pop_front();

        //Вийняток №3 - операційна система не може виділити пам'ять
        //l.push_back(6);
        //l.push_front(21);
           
        //Вийняток №4 - при додаванні списків перевірка що не сталося
        // переповнення лічильника SIZE
        //l.push_back(6);
        //l.push_front(21);



        l.print();



    }

    catch (exception& e)
    {
	cout << e.what() << endl;
	MyException* ex = dynamic_cast<MyException*>(&e);
	if(ex)
		ex->saveError();
    }
        
    return 0;
}

