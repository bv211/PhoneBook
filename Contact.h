#pragma once
#include <string>

using namespace std;

class Contact {
	string _fio;
	string _phone_number;

public:
	Contact(const string& fio, const string& phone_number) :
		_fio(fio), _phone_number(phone_number) {}

	string get_fio() const {
		return _fio;
	}

	string get_phone() const {
		return _phone_number;
	}
};
