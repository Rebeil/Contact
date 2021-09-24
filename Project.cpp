#include <iostream>
#include "Test.h"
#include <Windows.h>
//static varable
unsigned int Test::count = 0;
long int Test::ts = 0;
//unsigned int Test::id_contact = 0;

const int str3 = 3;
enum Comands {
    Add_contact = 1000,
    Del_contac = 1001,
    search_in_contact_name = 1002,
    search_in_contact_last_name = 1003,
    print_contacts = 1004
};
int main()
{ 
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    Test *contacts = new Test[Test::get_count()]; // создаём обычные контакты
    if (contacts) {
        char buf[str3];
        for (int i = 0; i < str3 ; ++i) {
            buf[i] = '\0';
        }

        /// <summary>
        std::string a = "text.example@random.com";
        /// </summary>
        /// <returns></returns>

        int answer = 0;
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
                    if (Test::get_count() == 0) {//перенести в мэин
                        std::cout << "Список контактов пуст" << std::endl;
                    }
                    else {
                        for (int i = 0; i < (str3 - 1); ++i) std::cin >> buf[i];
                        buf[str3 - 1] = '\0';
                        answer = contacts->search_in_contact_name(contacts, buf);
                    }
                    break;
                case 'd':
                    contacts = contacts->contact_del(contacts);
                    break;
                case 'a':
                    contacts = contacts->contact_add(contacts);
                    break;
                case 'p':
                    contacts->my_print(contacts);
                    break;
                case 'f':
                    break;
                case 'e':
                    std::cout << contacts->is_email_valid(a);
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
