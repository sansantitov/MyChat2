#include "User.h"
#include <iostream>

User::User()
{

	_id = -1;
	_login = "";
	_psw = "";
	_name = "";

}


User::User(int id, std::string login, std::string psw, std::string name)
{
	
	_id = id;
	_login = login;
	_psw = psw;
	_name = name;
	
}


void User::setUser(int id, std::string login, std::string psw, std::string name)
{

	_id = id;
	_login = login;
	_psw = psw;
	_name = name;

}

void User::showUser()
{
    const std::string str = "     " + std::to_string( _id) + "  " + _name+"\n";
	std::cout << str;
}

int User::getId()
{
    return _id;
}

std::string User::getLogin()
{
    return _login;
}

std::string User::getPsw()
{
    return _psw;
}

std::string User::getName()
{
    return _name;
}
