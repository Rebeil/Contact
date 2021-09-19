#pragma once
#ifndef CONTACT_H
#define CONTACT_H
#include <string>
#include <iostream>

class Contact
{
private:
	std::string last_name;
	std::string first_name;
	std::string birthday;
	std::string company;
	std::string email;
	std::string phone_number;
public:
#pragma region constructors
	Contact() {
		last_name = "";
		first_name = "";
		birthday = "";
		company = "";
		email = "";
		phone_number = "";
	}
	Contact(std::string last_name, std::string first_name,
		    std::string birthday, std::string company, 
		    std::string email, std::string phone_number) {
		this->last_name = last_name;
		this->first_name = first_name;
		this->birthday = birthday;
		this->company = company;
		this->email = email;
		this->phone_number = phone_number;
	}
#pragma endregion

	friend std::ostream& operator<<(std::ostream& os, const Contact& ct);       // is operator print
	friend std::istream& operator>>(std::istream& in, Contact& ct);        // is operator scan

	Contact* deep_copy_contact(const Contact* ct, const int size_ct) {
		Contact* buf = new Contact[size_ct];
		if (ct) {
			for (int i = 0; i < size_ct; ++i) {
				buf[i].last_name = ct[i].last_name;
				buf[i].first_name = ct[i].first_name;
				buf[i].birthday = ct[i].birthday;
				buf[i].company = ct[i].company;
				buf[i].email = ct[i].email;
				buf[i].phone_number = ct[i].phone_number;
			}
		}
		return buf;
	}
	Contact* contact_add(const Contact* ct, const int size_ct) {
		const int a = size_ct;
		Contact* buf = new Contact[a + 1];
		if (ct) {
			buf = buf->deep_copy_contact(ct, a);
			//тут надо считать дополнительный контакт
		}
		return buf;
	}
	Contact& operator=(const Contact& other) {    //is operator =
		this->last_name = other.last_name;
		this->first_name = other.first_name;
		this->birthday = other.birthday;
		this->company = other.company;
		this->email = other.email;
		this->phone_number = other.phone_number;
		return *this;
	}

};
#endif CONTACT_H
