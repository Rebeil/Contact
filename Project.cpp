#include <iostream>
#include <string>
#include <cassert>
#include "Contact.h"
#include <windows.h>
const int two = 2;

void viewing_contacts(Contact* ct) {
    for (int i = 0; i < two; ++i) {
        std::cout << ct[i];
    }
}

void search_in_contacts(Contact& ct) {

}
void search_on_list_contacts() {

}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Contact test = { "1","2","3","4","5","6" };
    Contact* test2 = new Contact[two];

    test2[0] = { "1","2","3","4","5","6" };
    test2[1] = { "11","22","33","44","55","66" };
    
    viewing_contacts(test2);
    Contact* a = new Contact[two];
    a = a->deep_copy_contact(test2,two);
    std::cout << std::endl;
    viewing_contacts(a);
    a = a->contact_add(a, 2);
    viewing_contacts(a);
    
    return 0;
}

