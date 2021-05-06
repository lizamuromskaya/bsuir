#include "Exp.h"
//pr_str - проверка правильности введения строки типа string
//Допускает ввод только русского алфавита, первая буква должна быть большой, допустимо использование дефиса, минимальная длина строки 2 символа
string pr_str(istream& in) {
	string ss;
	int flagg;
	do {
		try {
			flagg = 0;
			rewind stdin;
			getline(cin, ss);
			if (ss.length() < 2)
				throw Expvvod("Строка должна содержать минимум 2 символа!", 90);
			if (ss[0] < 'А' || ss[0] > 'Я')
				throw Expvvod("Слово должно начинаться с большой буквы и быть на русском языке!", 140);
			for (int i = 0; i < ss.length(); i++)
			{
				if ((ss[i] < 'А' || ss[i] > 'Я') && (ss[i] < 'а' || ss[i] > 'я') && (!(ss[i] == '-')))
					throw Expvvod("Строка должна быть на русском! Допустимо использование дефиса.", 120);
			}
		}
		catch (Expvvod ob) {
			flagg = 1;
			ob.showExp();
			cout << "Попробуйте снова." << endl;
		}
		catch (...) {
			flagg = 1;
			cout << "Ошибка." << endl;
			cout << "Попробуйте снова." << endl;
		}
	} while (flagg);
	return ss;
}
//pr_p - проверка правильности введения строки типа string
//Допускает ввод только больших букв и наличие цифр
string pr_p(istream& in) {
	string ss;
	int flag;
	do {
		try {
			flag = 0;
			rewind stdin;
			getline(cin, ss);
			if (ss.empty()) {
				throw Expvvod("Строка должна быть на русском! Все буквы должны быть большими!", 180);
			}
			for (int i = 0; i < ss.length(); i++) {
				if (ss[i] < 'А' || ss[i] > 'Я' && (ss[i] < '1' || ss[i] > '9'))
					throw Expvvod("Строка должна быть на русском! Все буквы должны быть большими!", 180);
			}
		}
		catch (Expvvod ob) {
			flag = 1;
			ob.showExp();
			cout << "Попробуйте снова." << endl;
		}
		catch (...) {
			flag = 1;
			cout << "Ошибка." << endl;
			cout << "Попробуйте снова." << endl;
		}
	} while (flag);
	return ss;
}

//pr_date - проверка правильности введения строки типа string
//Используется для проверки даты, не допускает выхода за пределы количества дней и месяцев, введение года в пределах (текущий_год - 100, текущий год)
//Дата должна быть разделена символом '.' или '/'
string pr_date(istream& in) {
	string ss;
	int flag;
	rewind stdin;
	struct tm localtime; //struct tm - структура времени
	time_t now = time(NULL); // Тип данных времени
	localtime_s(&localtime, &now); // Принимает значение текущего времени в секундах и инициализирует структуру в местном формате времени. 
	int currentYear, pastYear;
	currentYear = 1900 + localtime.tm_year;
	pastYear = currentYear - 100;
	do {
		try {
			flag = 0;
			rewind stdin;
			getline(cin, ss);
				if (ss.empty()) {
					throw Expvvod("Строка должна быть в формате ДД.ММ.ГГГГГ или ДД/ММ/ГГГГГ!", 200);
				}
			if (ss.length() < 10)
				throw Expvvod("Строка должна быть в формате ДД.ММ.ГГГГГ или ДД/ММ/ГГГГГ!", 200);
			if (ss[2] < '.' || ss[2] > '/' || ss[5] < '.' || ss[5] > '/')//проверка знака разделения между днем и месяцем/месяцем и годом (. или /)
				throw Expvvod("Дата должна быть в формате ДД.ММ.ГГГГГ или ДД/ММ/ГГГГГ!", 200);
			int day;
			string str1;
			str1 = ss.substr(ss.length() - 10, 2);
			day = atoi(str1.c_str());
			int month;
			string str2;
			str2 = ss.substr(ss.length() - 7, 2);
			month = atoi(str2.c_str());
			if (month == 4 || month == 6 || month == 9 || month == 11) {//проверка количества дней в месяце для 30-дневных
				if (day > 30 || day < 1)
					throw Expvvod("В данном месяце не может быть больше 30 дней!", 180);
			}
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) 
			{ //проверка количества дней в месяце для 31-дневных 01 03 05 07 08 10 12
				if (day > 31 || day < 1)
					throw Expvvod("В данном месяце не может быть больше 31 дня!", 180);
			}
			int yearf;
			string str;
			str = ss.substr(ss.length() - 4, 4);
			yearf = atoi(str.c_str());

			if (yearf < pastYear || yearf>currentYear) //проверка на нахождение года в пределах (текущий_год - 100, текущий год)
				throw out_of_range("Год не входит в допустимый диапазон!");
				//cout<<"Год должен быть в диапозоне от " << pastYear << " до " << currentYear << " ! ";

			if (month > 12 || month < 1)//проверка месяца
				throw Expvvod("Месяц введен неверно!", 180);

			if (month == 2) {
				if (day > 29 || day < 1)
					throw Expvvod("В данном месяце не может быть больше 28/29 дней!", 180);
				if (!(((yearf) % 4) == 0 && (((yearf) % 100) != 0 || ((yearf) % 400) == 0))) {  //проверка на высокосный год, год не высокосный
					if (day > 28 || day < 1)
						throw Expvvod("Год не высокосный. Количество дней не больше 28!", 180);
				}
			}
		}

		catch (out_of_range ob) {
			flag = 1;
			ob.what();
			cout << ob.what() << endl;
		}

		catch (Expvvod ob) {
			flag = 1;
			ob.showExp();
			cout << "Попробуйте снова." << endl;
		}
		catch (...) {
			flag = 1;
			cout << "Ошибка." << endl;
			cout << "Попробуйте снова." << endl;
		}
	} while (flag);
	return ss;
}
