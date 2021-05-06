#include "Exp.h"
//pr_str - �������� ������������ �������� ������ ���� string
//��������� ���� ������ �������� ��������, ������ ����� ������ ���� �������, ��������� ������������� ������, ����������� ����� ������ 2 �������
string pr_str(istream& in) {
	string ss;
	int flagg;
	do {
		try {
			flagg = 0;
			rewind stdin;
			getline(cin, ss);
			if (ss.length() < 2)
				throw Expvvod("������ ������ ��������� ������� 2 �������!", 90);
			if (ss[0] < '�' || ss[0] > '�')
				throw Expvvod("����� ������ ���������� � ������� ����� � ���� �� ������� �����!", 140);
			for (int i = 0; i < ss.length(); i++)
			{
				if ((ss[i] < '�' || ss[i] > '�') && (ss[i] < '�' || ss[i] > '�') && (!(ss[i] == '-')))
					throw Expvvod("������ ������ ���� �� �������! ��������� ������������� ������.", 120);
			}
		}
		catch (Expvvod ob) {
			flagg = 1;
			ob.showExp();
			cout << "���������� �����." << endl;
		}
		catch (...) {
			flagg = 1;
			cout << "������." << endl;
			cout << "���������� �����." << endl;
		}
	} while (flagg);
	return ss;
}
//pr_p - �������� ������������ �������� ������ ���� string
//��������� ���� ������ ������� ���� � ������� ����
string pr_p(istream& in) {
	string ss;
	int flag;
	do {
		try {
			flag = 0;
			rewind stdin;
			getline(cin, ss);
			if (ss.empty()) {
				throw Expvvod("������ ������ ���� �� �������! ��� ����� ������ ���� ��������!", 180);
			}
			for (int i = 0; i < ss.length(); i++) {
				if (ss[i] < '�' || ss[i] > '�' && (ss[i] < '1' || ss[i] > '9'))
					throw Expvvod("������ ������ ���� �� �������! ��� ����� ������ ���� ��������!", 180);
			}
		}
		catch (Expvvod ob) {
			flag = 1;
			ob.showExp();
			cout << "���������� �����." << endl;
		}
		catch (...) {
			flag = 1;
			cout << "������." << endl;
			cout << "���������� �����." << endl;
		}
	} while (flag);
	return ss;
}

//pr_date - �������� ������������ �������� ������ ���� string
//������������ ��� �������� ����, �� ��������� ������ �� ������� ���������� ���� � �������, �������� ���� � �������� (�������_��� - 100, ������� ���)
//���� ������ ���� ��������� �������� '.' ��� '/'
string pr_date(istream& in) {
	string ss;
	int flag;
	rewind stdin;
	struct tm localtime; //struct tm - ��������� �������
	time_t now = time(NULL); // ��� ������ �������
	localtime_s(&localtime, &now); // ��������� �������� �������� ������� � �������� � �������������� ��������� � ������� ������� �������. 
	int currentYear, pastYear;
	currentYear = 1900 + localtime.tm_year;
	pastYear = currentYear - 100;
	do {
		try {
			flag = 0;
			rewind stdin;
			getline(cin, ss);
				if (ss.empty()) {
					throw Expvvod("������ ������ ���� � ������� ��.��.����� ��� ��/��/�����!", 200);
				}
			if (ss.length() < 10)
				throw Expvvod("������ ������ ���� � ������� ��.��.����� ��� ��/��/�����!", 200);
			if (ss[2] < '.' || ss[2] > '/' || ss[5] < '.' || ss[5] > '/')//�������� ����� ���������� ����� ���� � �������/������� � ����� (. ��� /)
				throw Expvvod("���� ������ ���� � ������� ��.��.����� ��� ��/��/�����!", 200);
			int day;
			string str1;
			str1 = ss.substr(ss.length() - 10, 2);
			day = atoi(str1.c_str());
			int month;
			string str2;
			str2 = ss.substr(ss.length() - 7, 2);
			month = atoi(str2.c_str());
			if (month == 4 || month == 6 || month == 9 || month == 11) {//�������� ���������� ���� � ������ ��� 30-�������
				if (day > 30 || day < 1)
					throw Expvvod("� ������ ������ �� ����� ���� ������ 30 ����!", 180);
			}
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) 
			{ //�������� ���������� ���� � ������ ��� 31-������� 01 03 05 07 08 10 12
				if (day > 31 || day < 1)
					throw Expvvod("� ������ ������ �� ����� ���� ������ 31 ���!", 180);
			}
			int yearf;
			string str;
			str = ss.substr(ss.length() - 4, 4);
			yearf = atoi(str.c_str());

			if (yearf < pastYear || yearf>currentYear) //�������� �� ���������� ���� � �������� (�������_��� - 100, ������� ���)
				throw out_of_range("��� �� ������ � ���������� ��������!");
				//cout<<"��� ������ ���� � ��������� �� " << pastYear << " �� " << currentYear << " ! ";

			if (month > 12 || month < 1)//�������� ������
				throw Expvvod("����� ������ �������!", 180);

			if (month == 2) {
				if (day > 29 || day < 1)
					throw Expvvod("� ������ ������ �� ����� ���� ������ 28/29 ����!", 180);
				if (!(((yearf) % 4) == 0 && (((yearf) % 100) != 0 || ((yearf) % 400) == 0))) {  //�������� �� ���������� ���, ��� �� ����������
					if (day > 28 || day < 1)
						throw Expvvod("��� �� ����������. ���������� ���� �� ������ 28!", 180);
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
			cout << "���������� �����." << endl;
		}
		catch (...) {
			flag = 1;
			cout << "������." << endl;
			cout << "���������� �����." << endl;
		}
	} while (flag);
	return ss;
}
