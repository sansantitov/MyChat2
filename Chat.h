#pragma once
#include <iostream>

class Chat
{
public:
    Chat(); //конструктор
    int findUserLogin(std::string login); //поиск ID пользователя по логину
    void addUser(std::string login, std::string password, std::string name); //добавление пользоваьеля
    int findUserIdByLoginPassword(std::string login, std::string password); //поиск ID пользователя по логину-паролю
    std::string findUserNameByUserId(int idUser);  //поиск имени пользователя по ID пользователя
    void showUsers(); //отображение пользователей
    void showMsgs(); //отображение сообщений для текущего пользоваеля
    void sendMsg(int userIdTo, std::string message); //запись сообщения для "пересылки"
    void registr(); //регистрация нового пользователя
    int getUserIdLogin(); //получение ID текущего пользователя
    std::string login(); //авторизация пользователя по логину-паролю

private:
    int _userIdLogin; //ID текущего пользователя
    int _userIdMax; //максимальное (последнее) значение ID зарегистрированного пользователя
    int _msgIdMax; //максимальное (последнее) значение ID записанного сообщения
	
};

