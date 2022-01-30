#pragma once
#ifndef CONTACT_H
#define CONTACT_H
#include <conio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <regex>
#include <iomanip>

const int c16 = 16;								//размер полей контакта
const int t11 = 11;								//размер поля телефона
const int e16 = 16;								//размер поля емайла

class Contact
{
	static unsigned int count;					//всего контактов
private:
	unsigned int id_contact;

	bool flag_is_fav = false; //если правда то выводим контакт как любимый иначе выводим как обычный
	//////////////////////////////////////////////////////////
	char name[c16];
	char last_name[c16];
	char number_phone[t11];
	char birthday[c16];
	char company[c16];
	char email[e16];

private:

	inline static void inc_count() { ++count; }        //увеличиваем счётчик контактов
	inline static void dec_count() { --count; }			   //уменьшаем счётчик контактов

	void my_scan(Contact* t) {	for (unsigned int i = 0; i < count; ++i) std::cin >> t[i];} // функция сканирования

	void deep_copy(Contact* new_t,const Contact* old_t, const unsigned int id_for_del = -1) {
		/*
		глубокое копирование
		*/
		if (new_t && old_t) {
			for (unsigned int i = 0; i < count; ++i) {
				new_t[i].id_contact = old_t[i].id_contact;
				if (i != -1 && i >= id_for_del) { 
					for (int j = 0; j < c16; ++j) {
						new_t[i].name[j] = old_t[i + 1].name[j];
						new_t[i].last_name[j] = old_t[i + 1].last_name[j];
						new_t[i].email[j] = old_t[i + 1].email[j];
						new_t[i].birthday[j] = old_t[i + 1].birthday[j];
						new_t[i].company[j] = old_t[i + 1].company[j];
					}
					for (int j = 0; j < t11; ++j) {
						new_t[i].number_phone[j] = old_t[i + 1].number_phone[j];
					}
					new_t[i].flag_is_fav = old_t[i + 1].flag_is_fav;
				}
				else {
					for (int j = 0; j < c16; ++j) {
						new_t[i].name[j] = old_t[i].name[j];
						new_t[i].last_name[j] = old_t[i].last_name[j];
						new_t[i].email[j] = old_t[i].email[j];
						new_t[i].birthday[j] = old_t[i].birthday[j];
						new_t[i].company[j] = old_t[i].company[j];
					}
					for (int j = 0; j < t11; ++j) {
						new_t[i].number_phone[j] = old_t[i].number_phone[j];
					}
					new_t[i].flag_is_fav = old_t[i].flag_is_fav;
				}	
			}
		}
		else {
			std::cout << "Указатель/ли пустой/е" << std::endl;
		}
	}

public:
	friend std::ostream& operator<<(std::ostream& os, const Contact& t) {
		//Оператор для вывода контакта
		if (t.flag_is_fav) {
			std::cout<<(char)(149);
			std::cout << std::setw(15) << t.name << "|" << std::setw(15) << t.last_name << "|" << std::setw(10) << t.number_phone << "|"
				<< std::setw(29) << t.email << "|" << std::setw(13) << t.birthday << "|" << std::setw(15) << t.company << "|" 
				<< std::setw(11) << t.id_contact << "|" << std::endl;
		}
		else {
			std::cout << std::setw(16) << t.name << "|" << std::setw(15) << t.last_name << "|" << std::setw(10) << t.number_phone << "|"
				<< std::setw(29)<< t.email << "|" << std::setw(13)<<t.birthday<<"|"<< std::setw(15)<<t.company<<"|" 
				<< std::setw(11) << t.id_contact << "|" << std::endl;
		}

		return os;
	}

	friend std::istream& operator>>(std::istream& in, Contact& t) {
		//Оператор для ввода контакта
		std::cout << "Введите имя" << std::endl;
		int i = 0;
		char c;
		do {
			c = _getch();
			if (c == '\r') break;
			if (((int)c >= 65 && (int)c <= 90) ||		 
				((int)c >= 97 && (int)c <= 122) ||
				((int)c >= 192 && (int)c <= 255)) {
				_putch(c);;
				t.name[i] = c;
				++i;
			}
			else {
				std::cout << std::endl << "Вы ввели не букву\n";
			}
		} while (c != EOF && i < (c16 - 1));
		t.name[c16 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения
		std::cout << std::endl << "Вы ввели: " << t.name << std::endl;
		fflush(stdin);

		std::cout << "Введите фамилию" << std::endl;
		i = 0;
		do {
			c = _getch();
			if (c == '\r') break;
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
		} while (c != EOF && i < (c16 - 1));
		t.last_name[c16 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения
		std::cout << std::endl << "Вы ввели:" << t.last_name << std::endl;
		fflush(stdin);

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
			if (c == '\r') break;
			if ((int)c >= 48 && (int)c <= 57) {
				_putch(c);
				t.number_phone[i] = c;
				++i;
			}
			else {
				std::cout << std::endl << "Вы ввели не цифру\n";
			}
		} while (c != EOF && i < (t11 - 1));
		t.number_phone[t11 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения
		std::cout << std::endl << std::endl << "Вы ввели:" << t.number_phone << std::endl;
		fflush(stdin);

		std::cout << std::endl;

		std::cout << "Введите почту" << std::endl;
		while (1) {
			i = 0;
			do {
				c = std::cin.get();
				if (c == '\n') break;
				t.email[i] = c;
				++i;
			} while (c != EOF && i < (e16 - 1));
			t.email[e16 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения
			if (t.is_email_valid(std::string(t.email))) {
				std::cout<<std::endl << "Почта валидна";
				break;
			}
			else {
				std::cout << "Повторите ввод" << std::endl;
			}
		}

		std::cout << std::endl << "Вы ввели:" << t.email << std::endl;
		//std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Введите дату рождения" << std::endl;
		i = 0;
		do {
			c = std::cin.get();
			if (c == '\n') break;
			t.birthday[i] = c;
			++i;
		} while (c != EOF && i < (c16 - 1));
		t.birthday[c16 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения

		std::cout << "Введите компанию" << std::endl;
		i = 0;
		do {
			c = std::cin.get();
			if (c == '\n') break;
			t.company[i] = c;
			++i;
		} while (c != EOF && i < (c16 - 1));
		t.company[c16 - 1] = '\0';//убирает лишние символы из ввода,чтобы не было переполнения
		
		return in;
	}
	Contact* contact_add(Contact* t) {
		/*
		Функция выделяет новую память в куче(выделяет на n+1 контакт)
		далее старые конакты копируются в новую,выделнную память и запрашивается ввод нового контакта
		*/
		Contact* buf = new Contact[count + 1];//создаём временный указатель
		buf->deep_copy(buf, t);		    //копируем в него все контакты
		inc_count();				    //увеличиваем количество контактов
		delete[] t;						//помечаем "старый" указатель как пустой(освобождаем для ОС память)
		std::cin >> buf[count - 1];		//вводим ещё один контакт
										//inc_count_and_t();
		t = buf;						//присваиваем освобождённому указателю временный 
										//временный указатель удаляется
		return t;						// возвращаем новый адрес массива контактов
	}

	Contact* contact_del(Contact* t, const int id_for_del) {
		/*
		Функция выделяет новую память в куче(выделяет на n-1 контакт)
		далее старые конакты копируются в новую,выделенную память,но на один меньше
		*/
		dec_count();			//уменьшаем количество контактов
		Contact* buf = new Contact[count];
		buf->deep_copy(buf, t, id_for_del);
		delete[] t;
		t = buf;

		return t;
	}

	Contact& operator=(const Contact& other) = default; //дефолтный оператор присваивания

	Contact() {										   //конструктор без параметров
		for (int i = 0; i < c16; ++i) {			
			this->name[i] = '\0';					   //зануляем строки,нуль терминант
			this->last_name[i] = '\0';
			this->birthday[i] = '\0';
			this->company[i] = '\0';
		}
		for (int i = 0; i < t11; ++i) {			
			this->number_phone[i] = '\0';			   //зануляем строки,нуль терминант
		}
		for (int i = 0; i < e16; ++i) {
			this->email[i]= '\0';
		}
		id_contact = count;
	}
		
	int search_in_contact_name(const Contact* t,const char *str) {
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
						id_buf = t[i].id_contact;
					}
				}
			}
		}
		return id_buf;
	}

	int search_in_contact_last_name(const Contact* t, const char* str, const unsigned int flag = 0) {
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

	void my_print(const Contact* t) {				
		//функция вывода
		if (count == 0) std::cout << "Список контактов пуст" << std::endl;
		else { 
			std::cout << std::setw(17) <<"Имя|" << std::setw(16) << "Фамилия|" << std::setw(11) << "Телефон|" << std::setw(30) <<
				"Почта|" << std::setw(11) <<"Дата рождения|" << std::setw(16)<<"Компания|" << std::setw(11) << "id контакта|" << std::endl;
			for (unsigned int i = 0; i < count; ++i) 
				std::cout << t[i]; 
		}
	}

	void favorite_add_contact(Contact* t, const int id) {
		//Функция для пометки любимого контакта по id
		t[id].flag_is_fav = true;
	}

	bool is_email_valid(const std::string& email)
	{
		//функция для проверки на валидность емайла
		const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

		return std::regex_match(email, pattern);
	}

	static int get_count() { return count; }			   //возвращает количество контактов
	int get_id_contacts() { return id_contact; }		  //возвращает текущий id контакта
};

#endif CONTACT_H
