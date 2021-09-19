#include "Contact.h"
#include <cassert>
#include <Windows.h>

#pragma region operators

std::ostream& operator<<(std::ostream& os, const Contact& ct)
{
	assert(ct.first_name != "" && ct.last_name != "" && ct.birthday != "" &&
		ct.company != "" && ct.email != "" && ct.phone_number != "");
	std::cout << "Фамилия ";
	os << ct.last_name << std::endl;
	std::cout << "Имя ";
	os<<ct.first_name << std::endl;
	std::cout << "День рождения ";
	os << ct.birthday << std::endl;
	std::cout << "Компания ";
	os << ct.company << std::endl;
	std::cout << "Емайл ";
	os << ct.email << std::endl;
	std::cout << "Номер телефона ";
	os << ct.phone_number << std::endl;
	return os;
}
std::istream& operator>>(std::istream& in, Contact& ct)
{
	std::cout << "Введите фамилию ";
	in >> ct.last_name;
	std::cout<< "Введите имя ";
	in >> ct.first_name;
	std::cout << "Введите дату рождения ";
	in >> ct.birthday;
	std::cout << "Введите компанию ";
	in >> ct.company;
	std::cout << "Введите емайл ";
	in >> ct.email;
	std::cout << "Введите номер телефона ";
	in >> ct.phone_number;
	assert(ct.first_name != "" && ct.last_name != ""&& ct.birthday!="" &&
	ct.company!=""&&ct.email!=""&&ct.phone_number!="");
	return in;
}

#pragma endregion
