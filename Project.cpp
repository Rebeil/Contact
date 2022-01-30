#include <iostream>
#include "Contact.h"
#include <Windows.h>
//static varable
unsigned int Contact::count = 0;

const int str16 = 16;
int main()
{ 
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    Contact *contacts = new Contact[Contact::get_count()]; // создаём обычные контакты
    if (contacts) {
        char buf[str16];
        
        int answer;
        char id_for_fav;
        char key;
        while(1) {
            std::cout << "Введите команду\n q - для выхода,\n" <<
                " d - для удаления контакта,\n a - для добавления контакта,\n" <<
                " p - для просмотра контактов, \n s - для поиска контакта, \n" << 
                " f - добавить контакт в избранное : " << std::endl;
            std::cin >> key;
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');	//очистка буфера
            if (key != 'q') {
                switch (key)
                {
                case 's':
                    if (Contact::get_count() == 0) {//перенести в мэин
                        std::cout << "Список контактов пуст" << std::endl;
                    }
                    else {
                        char c;
                        int i = 0;
                        std::cout << "Выберите как искать, n - среди имени, f - среди фамилии" << std::endl;
                        answer = 0;
                        for (int i = 0; i < str16; ++i) {
                            buf[i] = '\0';
                        }
                        while (1) {
                            c = std::cin.get();
                            if (c == 'n') {
                                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                                std::cout << "Введите имя" << std::endl;
                                do {
                                    c = std::cin.get();
                                    if (c == '\n') break;
                                    buf[i] = c;
                                    ++i;
                                } while (c != EOF && i < (str16 - 1));
                                buf[str16 - 1] = '\0';

                                answer = contacts->search_in_contact_name(contacts, buf);
                                if (answer != -1) {
                                    std::cout << "Контакт найден его id: " << answer << std::endl;
                                }
                                else {
                                    std::cout << "Такого контакта не существует" << std::endl;
                                }
                                break;
                            }
                            else if (c == 'f') {
                                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                                std::cout << "Введите фамилию" << std::endl;
                                do {
                                    c = std::cin.get();
                                    if (c == '\n') break;
                                    buf[i] = c;
                                    ++i;
                                } while (c != EOF && i < (str16 - 1));
                                buf[str16 - 1] = '\0';

                                answer = contacts->search_in_contact_last_name(contacts, buf);
                                if (answer != -1) {
                                    std::cout << "Контакт найден его id: " << answer << std::endl;
                                }
                                else {
                                    std::cout << "Такого контакта не существует" << std::endl;
                                }
                                break;
                            }
                            else {
                                std::cout << "Ошибка ввода, повторите" << std::endl;
                            }
                        }
                        
                    }
                    break;
                case 'd':

                    if (Contact::get_count() == 0) {
                        std::cout << "Нельзя удалить, потому что нет контактов" << std::endl;
                    }
                    else {
                        std::cout << "Выберите контакт,который хотели бы удалить(введите его \"id\")" << std::endl;
                        contacts->my_print(contacts);
                        char id_for_del;
                        while (1) {
                            std::cin >> id_for_del;
                            if (isdigit(id_for_del)) {
                                if ((int)id_for_del - 48 < Contact::get_count()) {
                                    contacts = contacts->contact_del(contacts, (int)id_for_del - 48);
                                    break;
                                }
                                else {
                                    std::cout << "Вы вышли за пределы id,повторите ввод" << std::endl;
                                }
                            }
                            else {
                                std::cout << "Вы ввели не цифру/число,повторите ввод" << std::endl;
                            }
                        }
                    }
                    break;
                case 'a':
                    contacts = contacts->contact_add(contacts);
                    break;
                case 'p':
                    contacts->my_print(contacts);
                    break;
                case 'f':
                    std::cout << "Введите id контакта, который хотите добавить в избранное";
                    contacts->my_print(contacts);
                    while (1) {
                        std::cin >> id_for_fav;
                        if (isdigit(id_for_fav)) {
                            contacts->favorite_add_contact(contacts, (int)id_for_fav-48);
                            break;
                        }
                        else {
                            std::cout << "Вы ввели не цифру/число,повторите ввод" << std::endl;
                        }
                    }
                    break;
                default:
                    std::cout << "Неверно введена команда" << std::endl;
                    //std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');	//очистка буфера
                    break;
                }
            }
            else {
                std::cout << "Выход из программы"; 
                break; 
            }
        }
    }
    else {
        std::cout << "Указатель/ли пустой/е" << std::endl;
    }
    return 0;
}

