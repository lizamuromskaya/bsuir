#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <windows.h>
#include <exception>
#include <stdexcept>
#include <limits.h>

using namespace std;

class Exp {
protected:
	int kod;
public:
	Exp(int kod)
	{
		this->kod = kod;
	}
};

class Expvvod :public Exp {
	string message;
public:
	Expvvod(string st, int kod) :Exp(kod) {
		this->message = st;
	}
	void showExp() {
		cout <<"Код ошибки:"<< kod << "! " << message << endl;
	}
};

class Expfile :public Exp {
	string messag;
public:
	Expfile(string st, int kod) :Exp(kod) {
		this->messag = st;
	}
	void showExpfile() {
		cout << "Код ошибки:" << kod << "! " << messag << endl;
	}
};


string pr_str(istream& in);
string pr_p(istream& in);
string pr_date(istream& in);

//inputNum - проверка правильности введения чисел
// включает проверку для типа double на выход из границ DBL_MAX
//допускает ввод только положительных чисел
//примеры использования:
// //value = inputNum<int>(cin);
//value = inputNum<double>(cin);

template <class T>
T inputNum(istream& in)
{
	T num;
	bool flag;
	do
	{
		try
		{
			flag = 0;
			bool flagg;
			rewind stdin;
			in >> num;
			flagg = cin.rdstate();
			if ((flagg & ios::failbit) || (cin.get() != '\n'))
			{
				throw Expvvod("Была введена не цифра!", 10);
			}
			if ((num < DBL_MIN) || (num > DBL_MAX)) // проверка для типа double на выход из границ DBL_MAX=1.7976931348623158e+308
			{
				throw out_of_range("Выход за пределы!");
			}
			if (num < 0)
			{
				throw Expvvod("Цифра не положительная!", 11);
			}
		}

		catch (out_of_range o)
		{
			cin.clear();
			rewind(stdin);
			flag = 1;
			o.what();
			cout << o.what() << endl;
		}
		catch (Expvvod ob)
		{
			cin.clear();
			rewind(stdin);
			flag = 1;
			ob.showExp();
			cout << "Попробуйте снова." << endl;
		}
		catch (...) {
			cin.clear();
			rewind(stdin);
			flag = 1;
			cout << "Ошибка." << endl;
			cout << "Попробуйте снова." << endl;
		}
	} while (flag);
	return num;
}
//inputRange - проверка правильности введения чисел из заданного диапазона
//пример использования: Введение перемнной choice (int) из диапазона [0-3]
// int choice;
//choice = inputRange<int>(cin, 0, 3);
template <class T>
T inputRange(istream& in, double left, double right)
{
	T num;
	bool flag;
	do
	{
		try
		{
			flag = 0;
			rewind(stdin);
			in >> num;
			if ((cin.bad()) || (cin.get() != '\n'))
			{
				throw Expvvod("Была введена не цифра!", 102);
			}
			if ((num < left) || num > right)
			{
				throw range_error("Диапазон чисел неверен!");
			}
		}
		catch (Expvvod ob) {
			cin.clear();
			rewind(stdin);
			flag = 1;
			ob.showExp();
			cout << "Попробуйте снова." << endl;
		}
		catch (range_error ob)
		{
			cin.clear();
			rewind(stdin);
			flag = 1;
			cout << ob.what() << endl;
			cout << "Попробуйте снова." << endl;
		}
		catch (exception& exception)
		{
			cin.clear();
			rewind(stdin);
			flag = 1;
			cerr << "Вызвано стандратное исключение: " << exception.what() << '\n';
		}
		catch (...) {
			cin.clear();
			rewind(stdin);
			flag = 1;
			cout << "Ошибка." << endl;
			cout << "Попробуйте снова." << endl;
		}
	} while (flag);
	return num;
}

