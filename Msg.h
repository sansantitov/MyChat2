#pragma once
#include <iostream>

class Msg
{
public:
    Msg(); //конструктор сообщения
    Msg(int id, int idFrom, std::string nameFrom, int idTo, std::string message); //конструктор с установкой значений
    void showMsg(); //отображение сообщения
    std::string getTime(); //выдача текущего времени
    int getIdTo(); //получение ID пользоваьеля-адресата сообщения
    std::string getMessage(); //получения текста сообщения

private:
    int _id; //ID сообщения
    std::string _datetime; //время формирования сообщения
    std::string _message; //текст сообщения
    int _idFrom; //ID пользователя-источника сообщения (от кого)
    std::string _nameFrom; //имя пользователя-источника сообщения
    int _idTo; //ID пользователя-адресата сообщения (кому)
};

