#include "chat.h"
#include <vector>
#include "User.h"
#include "Msg.h"
#include "Functions.h"

extern std::vector<User> users;
extern std::vector<Msg> msgs;



 Chat::Chat()
 {
     users.emplace_back(0,"All","1","All users");
     _userIdLogin = -1;
     _userIdMax = 0; //0-зарезервировано для выдачи всем
     _msgIdMax = -1;
 }


 int Chat::findUserLogin(std::string login)
 {
     int id = -1;
     for (int i = 0; i < users.size(); ++i)
     {
         if (users[i].getLogin() == login)
         {
             id = users[i].getId();
             break;
         }
     }
     return id;
 }


 void Chat::addUser(std::string login, std::string password, std::string name)
{
    //User* u = new User(++_userIdMax, login, password, name);
    std::unique_ptr<User> u = std::make_unique<User>(++_userIdMax, login, password, name);

    users.push_back(*u);
}

int Chat::findUserIdByLoginPassword(std::string login, std::string password)
{
    int id = -1;
    for (int i = 0; i < users.size(); ++i)
    {
        if (users[i].getLogin() == login && users[i].getPsw() == password)
        {
            id = users[i].getId();
            break;
        }
    }
    _userIdLogin = id;
    return id;
}

std::string Chat::findUserNameByUserId(int idUser)
{
    std::string name;
    for (int i = 0; i < users.size(); ++i)
    {
        if (users[i].getId() == idUser)
        {
            name = users[i].getName();
            break;
        }
    }
    return name;
}




void Chat::showUsers()
{
    rout("--- ID  Имя пользователя -----------\n");

    if (users.size() > 1)
    {
        for (int i = 1; i < users.size(); ++i)
        {
            users[i].showUser();
        }
    }
    std::cout << "------------------------------------\n";
}

void Chat::sendMsg(int userIdTo, std::string message)
{
    std::string userName = findUserNameByUserId(_userIdLogin);
    //Msg* m = new Msg(++_msgIdMax, _userIdLogin, userName, userIdTo, message);
    std::unique_ptr<Msg> m = std::make_unique<Msg>(++_msgIdMax, _userIdLogin, userName, userIdTo, message);
    //if (msgs.size() == 1 && msgs[0].getMessage()=="") msgs[0] = *m;
    msgs.push_back(*m);
}

void Chat::showMsgs()
{
    std::string userName = findUserNameByUserId(_userIdLogin);
    std::cout << "******** " << userName << ": ";
    rout   ("принятые сообщения *******\n");
    for (int i = 0; i < msgs.size(); ++i)
    {
        if (msgs[i].getIdTo() == 0 || msgs[i].getIdTo() == _userIdLogin) msgs[i].showMsg();
    }
    std::string s(37+userName.length(), '*');
    std::cout << s << std::endl;
}

int Chat::getUserIdLogin()
{
    return _userIdLogin;
}


void Chat::registr()
{
    std::string login, password, name;
    rout("*** Регистрация нового пользователя ***\n");

    while (true)
    {

        rout("логин нового пользователя: ");
        getline(std::cin, login);
        if (login.length() < 2) rout ("в логине должно быть не менее двух символов!\n");
        else if (findUserLogin(login) >= 0) rout ("пользователь с таким логином уже зарегистрирован!\n");
        else break;
    }
    rout("пароль: ");
    getline(std::cin, password);
    rout("имя: ");
    getline(std::cin, name);
    addUser(login, password, name);
    rout("******** регистрация закончена ********\n");
}


std::string Chat::login()
{
    std::string rr;
    //bool isExit = false;
    rout("Для авторизации введите логин или \"4\"-для регистрация нового пользователя\n");
    while (true)
    {
        std::string login, password;
        int id;
        while (true)
        {
            
            rout("логин: ");
            getline(std::cin, login);
            if (login == "4")
            {
                rr = "4";
                break;
            }
            else if (login.length() < 2) rout ("в логине должно быть не менее двух символов!\n");
            else break;
        }

        if (rr != "4")
        {
            rout("пароль: ");
            getline(std::cin, password);
            id = findUserIdByLoginPassword(login, password);
            if (id < 0)
            {
                rout("логин-пароль не соответствуют ни одному пользователю!\n");
                rr = choice("повторить-1, регистрация нового-4, выход-0: ", "140");
                if (rr != "1") break;
            }
            else break;
                
        }
        else break;
    }
    return rr;
}











