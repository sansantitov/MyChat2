# MyChat2
Решение по заданию 16.9.1 (модуль 16 "STL")

# Команда
Александр Титов

# Основные черты решения 
использованием контейнеров стандартной библиотеки шаблонов \
поддержка кирилицы \
регистрация нового участника или вход в уже существующую учетную запись \
возможность обмена сообщениями в режиме личных сообщений и общего чата \
смена пользователя в процессе общения

# Классы

**class Chat**\
поиск ID пользователя по логину
int findUserLogin(std::string login);\
добавление пользователя
void addUser(std::string login, std::string password, std::string name); \
поиск ID пользователя по логину-паролю
int findUserIdByLoginPassword(std::string login, std::string password); \
поиск имени пользователя по ID пользователя
std::string findUserNameByUserId(int idUser); \ 
отображение пользователей
void showUsers(); \
отображение сообщений для текущего пользоваеля
void showMsgs(); \
запись сообщения для "пересылки"
void sendMsg(int userIdTo, std::string message); \
регистрация нового пользователя
void registr(); \
получение ID текущего пользователя
int getUserIdLogin(); \
авторизация пользователя по логину-паролю
std::string login(); 

**class User** \
конструктор с установкой свойств
User(int id, std::string login, std::string psw, std::string name); \
установка свойств
void setUser(int id, std::string login, std::string psw, std::string name); \
отображение информации о пользователе
void showUser(); 

**class Msg** \
конструктор с установкой значений
Msg(int id, int idFrom, std::string nameFrom, int idTo, std::string message); \
отображение сообщения
void showMsg(); \
выдача текущего времени
std::string getTime(); \
получение ID пользователя-адресата сообщения
int getIdTo(); \
получения текста сообщения
std::string getMessage(); 


**class Users** \
Класс пользователей на основе контейнера vector и класса User 
 

**class Msgs** \
Класс сообщений на основе контейнера vector и класса Msg

# Функции
выдача кирилицы в терминал
void rout(std::string); \
выбор в терминале символа с проверкой
std::string choice(std::string, std::string); \
проверка стринга на цифру
bool is_number(const std::string&); 

