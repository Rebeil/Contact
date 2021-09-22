#pragma once
#ifndef TEST_H
#define TEST_H
#include <conio.h>
#include <cstring>
#include <string>
#include <iostream>
//#define CIN_FLUSH if (std::cin.peek()) std::cin.ignore()

const int c3 = 3;								//размер полей контакта
const int t9 = 9;								//размер поля телефона

class Test
{
	static int count;
private:
	int counter = 0;
	char name[c3];
	char last_name[c3];
	char number_phone[t9];
private:
	void my_scan(Test* t) {	for (int i = 0; i < count; ++i) std::cin >> t[i];} // функция сканирования
public:
	inline static void inc_count() { ++count; }        //увеличиваем счётчик контактов
	inline void dec_count() { --count; }			   //уменьшаем счётчик контактов
	static int getValue() { return count; }
	Test() {										   //конструктор без параметров
		for (int i = 0; i < c3; ++i) {			
			this->name[i] = '\0';					   //зануляем строки,нуль терминант
			this->last_name[i] = '\0';
		}
		for (int i = 0; i < t9; ++i) {			
			this->number_phone[i] = '\0';			   //зануляем строки,нуль терминант
		}
	}
	Test(const char* name,const char* last_name, const char* number_phone) {//конструктор с аргументами
		for (int i = 0; i < (c3 - 1); ++i) {
			this->name[i] = name[i];
			this->last_name[i] = last_name[i];
		}
		//нуль терминант
		this->name[c3 - 1] = '\0';
		this->last_name[c3 - 1] = '\0';

		for (int i = 0; i < (t9 - 1); ++i) {
			this->number_phone[i] = number_phone[i];
		}
		this->number_phone[c3 - 1] = '\0';
	}
	void deep_copy(Test* new_t,const Test* old_t) {
		/*
		глубокое копирование
		*/
		for (int i = 0; i < count; ++i) {
			for (int j = 0; j < c3; ++j) {
				new_t[i].name[j] = old_t[i].name[j];
				new_t[i].last_name[j] = old_t[i].last_name[j];
			}
		}
	}
	int search_in_contact_name(const Test* t,const char *str) {
		/*
		Функция поиска по имени, возвращает -1 если такоо имени не найдено,больше -1 если найден
		*/
		int id_buf = -1;
		if (t) {
			for (int i = 0; i < count; ++i) {
				if (strcmp(t[i].name, str) == 0) {
					id_buf = i;
				}
			}
		}
		return id_buf;
	}
	int search_in_contact_last_name(const Test* t, const char* str) {
		/*
		Функция поиска по фамилии, возвращает -1 если такоо имени не найдено,больше -1 если найден
		*/
		int id_buf = -1;
		if (t) {
			for (int i = 0; i < count; ++i) {
				if (strcmp(t[i].last_name, str) == 0) {
					id_buf = i;
				}
			}
		}
		return id_buf;
	}

	void my_print(const Test* t, const Test* f) {				//функция вывода
		if (count == 0) std::cout << "Список контактов пуст" << std::endl;
		else for (int i = 0; i < count; ++i)  std::cout << t[i];
	}
	Test* contact_add(Test* t) {
		/*
		Функция выделяет новую память в куче(выделяет на n+1 контакт) 
		далее старые конакты копируются в новую,выделнную память и запрашивается ввод нового контакта
		*/
		inc_count();			    //увеличиваем количество контактов
		Test* buf = new Test[count];//создаём временный указатель
		buf->deep_copy(buf, t);		//копируем в него все контакты
		delete[] t;					//помечаем "старый" указатель как пустой(освобождаем для ОС память)
		std::cin >> buf[count - 1]; // вводим ещё один контакт
		t = buf;					//присваиваем освобождённому указателю временный 
									// временный указатель удаляется
		return t;					// возвращаем новый адрес массива контактов
	}
	Test* contact_del(Test* t) {
		/*
		Функция выделяет новую память в куче(выделяет на n-1 контакт)
		далее старые конакты копируются в новую,выделенную память,но на один меньше 
		*/
		if (count == 0) {//перенести в мэин
			std::cout <<"Нельзя удалить, потому что контактов 0";
		}
		else {
			dec_count();
			Test* buf = new Test[count];
			buf->deep_copy(buf, t);
			delete[] t;
			t = buf;
		}
		return t;
	}
	Test& operator=(const Test& other) = default;
	friend std::ostream& operator<<(std::ostream& os, const Test& t) {
		std::cout << "Print"<<std::endl;
		std::cout << t.name << std::endl << t.last_name << std::endl << t.number_phone<< std::endl;
		return os;
	}
	friend std::istream& operator>>(std::istream& in, Test& t) {
		std::cout << "Введите имя" << std::endl;
		int i = 0;
		char c;
		do {
			std::cin >> c;
			if (((int)c>=65 && (int)c<=90) ||		 // проблемы с вводом,если вводить цифру с буквой однвоременно,например "1щ"
				((int)c >= 97 && (int)c <= 122)||
				((int)c >= 192&& (int)c <= 255)) {
				std::cout<< (char)c;
				t.name[i] = c;
				++i;
			}
			else if ((int)c == 10) {
				std::cout << (char)c;
			}
		} while (c != '\n' && c != EOF && i < (c3 - 1));
		t.name[c3 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');	//очистка буфера
		//std::cout<<std::endl;

		std::cout << "Введите фамилию" << std::endl;
		i = 0;
		do {
			std::cin >> c;
			if (((int)c >= 65 && (int)c <= 90) || 
				((int)c >= 97 && (int)c <= 122) ||
				((int)c >= 192 && (int)c <= 255)) {
				std::cout << (char)c;
				t.last_name[i] = c;
				++i;
			}
			else if ((int)c == 10) {
				std::cout << (char)c;
			}
		} while (c != '\n' && c != EOF && i < (c3 - 1));
		t.last_name[c3 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');	//очистка буфера
		//std::cout << std::endl;

		std::cout << "Введите номер телефона" << std::endl;
		i = 0;
		do {
			c = _getch();
			if ((int)c >= 48 && (int)c <= 57) {
				std::cout << (char)c;;
				t.number_phone[i] = c;
				++i;
			}
		} while (c != '\n' && c != EOF && i < (t9 - 1));
		t.number_phone[t9 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');	//очистка буфера
		//std::cout << std::endl;

		return in;
	}
};


#endif TEST_H
