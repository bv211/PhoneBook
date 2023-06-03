#include <iostream>
#include "PhoneBook.h"
#include <Windows.h>

int main() {
	setlocale(0, "");
	SetConsoleCP(1251);

	PhoneBook pb("contacts.txt");
	pb.print_contacts();

	auto contact = pb.get_contact(0);
	cout << endl << "========Удаляемый контакт========" << endl;
	cout << contact->get_fio() << endl;
	pb.delete_contact(contact);

	cout << endl << "========После удаления========" << endl;
	pb.print_contacts();

	pb.add_contact(new Contact("Хех ахаах", "123456"));
	pb.add_contact(new Contact("Петр Петро Петрович", "124568"));
	
	cout << endl << "========После добавления========" << endl;
	pb.print_contacts();

	return 0;
}