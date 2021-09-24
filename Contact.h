#pragma once
#ifndef TEST_H
#define TEST_H
#include <conio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <regex>
//#define CIN_FLUSH if (std::cin.peek()) std::cin.ignore()

const int c3 = 3;								//размер полей контакта
const int t11 = 11;								//размер поля телефона
const int e30 = 30;								//размер поля емайла

class Test
{
	static long int ts;
	static unsigned int count;					//всего контактов
	//static unsigned int fav_count;				//избранных контактов
private:
	unsigned int id_contact;

	bool flag_is_fav = false;
	//////////////////////////////////////////////////////////
	char name[c3];
	char last_name[c3];
	char number_phone[t11];

	//std::string email;
private:
	inline void inc_id() { id_contact = ts; }

	inline static void inc_count_and_t() { ++count; ++ts; }        //увеличиваем счётчик контактов
	inline static void dec_count() { --count; }			   //уменьшаем счётчик контактов

	void my_scan(Test* t) {	for (unsigned int i = 0; i < count; ++i) std::cin >> t[i];} // функция сканирования

	void deep_copy(Test* new_t, const Test* old_t) {
		/*
		глубокое копирование
		*/
		if (new_t && old_t) {
			for (unsigned int i = 0; i < count; ++i) {
				for (int j = 0; j < c3; ++j) {
					new_t[i].name[j] = old_t[i].name[j];
					new_t[i].last_name[j] = old_t[i].last_name[j];
				}
				for (int j = 0; j < t11; ++j) {
					new_t[i].number_phone[j] = old_t[i].number_phone[j];
				}
				new_t[i].id_contact = old_t[i].id_contact;
				//new_t[i].email = old_t[i].email;
			}
		}
		else {
			std::cout << "Указатель/ли пустой/е" << std::endl;
		}
	}
public:
	friend std::ostream& operator<<(std::ostream& os, const Test& t) {
		std::cout << "|" << t.name << "          |" << t.last_name << "             |" << t.number_phone << "     " << t.id_contact << std::endl;
		return os;
	}

	friend std::istream& operator>>(std::istream& in, Test& t) {
		std::cout << "Введите имя" << std::endl;
		int i = 0;
		char c;
		do {
			c = _getch();//std::cin >> c;
			if (((int)c >= 65 && (int)c <= 90) ||		 // проблемы с вводом,если вводить цифру с буквой однвоременно,например "1щ"
				((int)c >= 97 && (int)c <= 122) ||
				((int)c >= 192 && (int)c <= 255)) {
				_putch(c);//std::cout<< (char)c;
				t.name[i] = c;
				++i;
			}
			else {
				std::cout << std::endl << "Вы ввели не букву\n";
			}
		} while (c != '\n' && c != EOF && i < (c3 - 1));
		t.name[c3 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения
		std::cout << std::endl << "Вы ввели: " << t.name << std::endl;
		fflush(stdin);
		//std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');	//очистка буфера
		//std::cout<<std::endl;

		std::cout << "Введите фамилию" << std::endl;
		i = 0;
		do {
			c = _getch();
			if (((int)c >= 65 && (int)c <= 90) ||
				((int)c >= 97 && (int)c <= 122) ||
				((int)c >= 192 && (int)c <= 255)) {
				_putch(c);
				t.last_name[i] = c;
				++i;
			}
			else {
				std::cout << std::endl << "Вы ввели не букву\n";
			}
		} while (c != '\n' && c != EOF && i < (c3 - 1));
		t.last_name[c3 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения
		std::cout << std::endl << "Вы ввели:" << t.last_name << std::endl;
		fflush(stdin);
		//std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');	//очистка буфера
		//std::cout << std::endl;

		std::cout << "Введите номер телефона" << std::endl << "+7(";
		i = 0;
		do {
			if (i == 3) {
				_putch(41);
			}
			if (i == 6) {
				_putch(45);
			}
			if (i == 8) {
				_putch(45);
			}
			c = _getch();
			if ((int)c >= 48 && (int)c <= 57) {
				_putch(c);
				t.number_phone[i] = c;
				++i;
			}
			else {
				std::cout << std::endl << "Вы ввели не цифру\n";
			}
		} while (c != '\n' && c != EOF && i < (t11 - 1));
		t.number_phone[t11 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения
		std::cout << std::endl << std::endl << "Вы ввели:" << t.number_phone << std::endl;
		fflush(stdin);
		//std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');	//очистка буфера
		//std::cout << std::endl;

		return in;
	}
	Test* contact_add(Test* t) {
		/*
		Функция выделяет новую память в куче(выделяет на n+1 контакт)
		далее старые конакты копируются в новую,выделнную память и запрашивается ввод нового контакта
		*/
		Test* buf = new Test[count + 1];//создаём временный указатель
		buf->deep_copy(buf, t);		//копируем в него все контакты
		inc_count_and_t();			//увеличиваем количество контактов
		delete[] t;					//помечаем "старый" указатель как пустой(освобождаем для ОС память)
		std::cin >> buf[count - 1]; //вводим ещё один контакт
		inc_id();					//увеличиваем id //inc_count_and_t();
		t = buf;					//присваиваем освобождённому указателю временный 
									//временный указатель удаляется
		return t;					// возвращаем новый адрес массива контактов
	}

	Test* contact_del(Test* t) {
		/*
		Функция выделяет новую память в куче(выделяет на n-1 контакт)
		далее старые конакты копируются в новую,выделенную память,но на один меньше
		*/
		if (count == 0) {//перенести в мэин?
			std::cout << "Нельзя удалить, потому что нет контактов" << std::endl;
		}
		else {
			dec_count();			//уменьшаем количество контактов
			Test* buf = new Test[count];
			buf->deep_copy(buf, t);
			delete[] t;
			t = buf;
		}
		return t;
	}

	Test& operator=(const Test& other) = default;

	Test() {										   //конструктор без параметров
		for (int i = 0; i < c3; ++i) {			
			this->name[i] = '\0';					   //зануляем строки,нуль терминант
			this->last_name[i] = '\0';
		}
		for (int i = 0; i < t11; ++i) {			
			this->number_phone[i] = '\0';			   //зануляем строки,нуль терминант
		}
		//this->email = '\0';
		id_contact = 0;
	}

	Test(const char* name,const char* last_name, const char* number_phone, const std::string email) {//конструктор с аргументами
		id_contact = 0;
		for (int i = 0; i < (c3 - 1); ++i) {
			this->name[i] = name[i];
			this->last_name[i] = last_name[i];
		}
		//нуль терминант
		this->name[c3 - 1] = '\0';
		this->last_name[c3 - 1] = '\0';

		for (int i = 0; i < (t11 - 1); ++i) {
			this->number_phone[i] = number_phone[i];
		}
		this->number_phone[c3 - 1] = '\0';

		//this->email = email;

	}
	
	int search_in_contact_name(const Test* t,const char *str) {
		/*
		Функция поиска по имени, возвращает -1 если такоо имени не найдено,больше -1 если найден
		*/
		int id_buf = -1;
		if (count == 0) {//перенести в мэин//////////////////////////////////////////////////////////////
			std::cout <<"Список контактов пуст"<<std::endl;
		}
		else {
			if (t) {
				for (unsigned int i = 0; i < count; ++i) {
					if (strcmp(t[i].name, str) == 0) {
						id_buf = i;
					}
				}
			}
		}
		return id_buf;
	}

	int search_in_contact_last_name(const Test* t, const char* str, const unsigned int flag = 0) {
		/*
		Функция поиска по фамилии, возвращает -1 если такоо имени не найдено,больше -1 если найден
		*/
		int id_buf = -1;
		if (t) {
			for (unsigned int i = 0; i < count; ++i) {
				if (strcmp(t[i].last_name, str) == 0) {
					id_buf = i;
				}
			}
		}
		return id_buf;
	}

	void my_print(const Test* t) {				
		//функция вывода
		if (count == 0) std::cout << "Список контактов пуст" << std::endl;
		else { 
			std::cout << "|Имя" << "         |" << "Фамилия" << "        |" << "Телефон"<<"         "<<"id контакта" << std::endl;
			for (unsigned int i = 0; i < count; ++i) 
				std::cout << t[i]; 
		}
	}

	bool is_email_valid(const std::string& email)
	{
		const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

		return std::regex_match(email, pattern);
	}

	static int get_count() { return count; }			   //возвращает количество контактов
	int get_id_contacts() { return id_contact; }
};


#endif TEST_H
