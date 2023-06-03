#pragma once
#include "Contact.h"

class PhoneBook {
	Contact** _contacts{ nullptr };
	const string _path;
	size_t _count{ 0 };

	Contact* create_contact(const string& fio, const string& phone) {
		return new Contact(fio, phone);
	}

	void load() {
		_count = get_count_lines();
		if (_count < 0) return;

		_contacts = new Contact * [_count] {};

		FILE* file = nullptr;
		if (fopen_s(&file, _path.c_str(), "r") != 0)
			return;

		const int size = 256;
		char buffer[size]{};
		auto delimeter = ';';
		auto new_line = '\n';
		int i = 0;

		while (fgets(buffer, size, file)) {
			auto* point = strchr(buffer, delimeter);
			*point = '\0';

			auto* end_line = strchr(point + 1, new_line);
			if (end_line != nullptr)
				*end_line = '\0';

			_contacts[i] = create_contact(buffer, point + 1);
			i++;
		}
	}

	void reset(Contact** contacts) {
		delete[] _contacts;
		_contacts = contacts;
	}
public:
	PhoneBook(const string& path) : _path(path) {
		load();
	}

	~PhoneBook() {
		if (_contacts == nullptr) return;

		for (size_t i = 0; i < _count; i++)
			delete _contacts[i];

		delete[] _contacts;
	}

	int get_count_lines() {
		FILE* file = nullptr;
		if (fopen_s(&file, _path.c_str(), "r") != 0)
			return -1;

		char symbol{};
		int count = 0;

		while (!feof(file)) {
			symbol = fgetc(file);
			if (symbol == '\n')
				count++;
		}

		if (symbol != '\n') count++;

		return count;
	}

	void print_contacts() const {
		for (size_t i = 0; i < _count; i++) {
			auto contact = _contacts[i];
			if (contact == nullptr)
				continue;

			cout << i + 1 << ":" << endl
				<< contact->get_fio() << endl
				<< contact->get_phone() << endl;
		}
	}

	void add_contact(Contact* contact) {
		auto old_count = _count;
		_count++;
		auto** tmp_contacts = new Contact * [_count] {};

		for (size_t i = 0; i < old_count; i++)
			tmp_contacts[i] = _contacts[i];

		tmp_contacts[old_count] = contact;
		reset(tmp_contacts);
	}

	Contact* get_contact(int index) const {
		if (index >= _count || index < 0) return nullptr;

		return _contacts[index];
	}

	void delete_contact(int index) {
		if (index >= _count || index < 0) return;

		delete _contacts[index];
		_count--;

		auto** tmp_contacts = new Contact * [_count] {};
		int j{ 0 };

		for (size_t i = 0; i < _count; i++) {
			if (index == i) j++;

			tmp_contacts[i] = _contacts[j];
			j++;
		}

		reset(tmp_contacts);
	}

	void delete_contact(Contact* contact) {
		for (size_t i = 0; i < _count; i++) {
			auto con = _contacts[i];

			if (con != contact) continue;

			delete_contact(i);
			return;
		}
	}
};