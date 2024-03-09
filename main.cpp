#include "Msg.h"
#include "TArray.h"
#include "User.h"
#include "Chat.h"
#include <iostream>
#include "Functions.h"
#ifdef _WIN32
#include <Windows.h>
#endif

TArray<User> users(1); //класс пользователей на основе шаблона TArray<User>
TArray<Msg> msgs(1); //класс сообщений на основе шаблона TArray<Msg>

int main()
{
#ifdef _WIN32
    int cp1 = GetConsoleCP();
    int cp2 = GetConsoleOutputCP();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    system("cls");
    Chat* chat = new Chat();
    bool isExit = false;


    while (!isExit)
    {
        std::string strChoice;
        //strChoice = "0" - выход
        //strChoice = "1" - сообщение
        //strChoice = "3" - вход-авторизация(логин-пароль)
        //strChoice = "4" - регистрация нового пользователя (логин-пароль-имя)

        
        while (!isExit)
        {
            strChoice = chat->login(); //авторизация
            if (strChoice == "0") //на выход
            {
                
                isExit = true;
                break;
            }
            else if (strChoice == "4") chat->registr(); //регистрация
            else break; //авторизация прошла
        }

        if (!isExit)
        {
            while (true)
            {
                std::string message;
                chat->showMsgs(); //отоюражение всех сообщений для авторизованного пользователя

                std::string strUserTo; //для выбора Id пользователя-адресата
                int intUserTo = 0; //Id пользователя - целое

                std::string strChoice1 = choice("послать сообщение-1, авторизация (новый вход)-3, закончить-0: ", "130");

                if (strChoice1 == "0") { isExit = true; break; } //на выход
                else if (strChoice1 == "3") { break; } //на авторизацию

                if (strChoice1 == "1") //сообщение
                {
                    while (true)
                    {
                        chat->showUsers(); //отображение пользователей для выбора Id адресата - кому послать или 0-для всех
                        rout("Кому послать (ID адресата)? (послать всем-0): ");
                        getline(std::cin, strUserTo); //ввод Id адресата
                        intUserTo = strUserTo.length() == 1 && is_number(strUserTo) ? stoi(strUserTo) : -1;
                        if (chat->findUserNameByUserId(intUserTo) != "") break; //есть такой пользовьтель
                    }
                    rout("сообщение: ");
                    getline(std::cin, message); //ввод сообщения
                    chat->sendMsg(intUserTo, message); //запись сообщения
                }
            }
        }
    }
#ifdef _WIN32
    SetConsoleCP(cp1);
    SetConsoleOutputCP(cp2);
#endif
    delete chat;
    msgs.erase();
    users.erase();

    return 0;
}

