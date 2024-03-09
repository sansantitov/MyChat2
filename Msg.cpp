#include "Msg.h"
#include "Functions.h"
#include <iostream>
#include <ctime>

Msg::Msg()
{
     _id = 0;
    _datetime = getTime();
	_message = "";
	_idFrom = 0;
	_nameFrom = "";
	_idTo = 0;
		
	
}

Msg::Msg(int id, int idFrom, std::string nameFrom, int idTo, std::string message)
{
	
	_id = id;
    _datetime = getTime();
	_message = message;
	_idFrom = idFrom;
	_nameFrom = nameFrom;
	_idTo = idTo;
}

void Msg::showMsg()
{
	if (!_message.empty())
	{
        std::string dtStr = _datetime;
        const std::string str = dtStr + " "+ _nameFrom + ": " + _message + "\n";
		std::cout << str;
	}
}

std::string Msg::getTime()
{
    time_t now = time(NULL);
    char str[26];
    ctime_s(str, 26, &now);
    std::string ss = str;
    return ss.substr(11,8);
}

int Msg::getIdTo()
{
    return _idTo;
}

std::string Msg::getMessage()
{
    return _message;
}


