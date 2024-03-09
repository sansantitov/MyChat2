#pragma once
#include <exception>
#include <iostream>


class bad_range :public std::exception
{
public:
    const char* what() const noexcept
    {
        return "Выход индекса за пределы массива!";
    }

};


class bad_length :public std::exception
{
public:
    const char* what() const noexcept
    {
        return "Неправильная длина массива!";
    }
};


template <typename T> class TArray //шаблон класса динамического массива
{
    
private:
    int m_length{};
    T* m_data{};

public:
    TArray() = default;

    TArray(int);
    TArray(const TArray&);
    ~TArray();
    void erase();
    T& operator[](int);
    void reallocate(int);
    void resize(int);
    TArray& operator=(const TArray&);
    void insertBefore(T, int);
    void remove(int);
    void insertAtBeginning(T);
    void insertAtEnd(T);
    int getLength() const;
    int findValue(T) const;
};


template <typename T>
TArray<T>::TArray(int length):m_length{ length }
{
    //assert(length >= 0);
    try 
    {
        if (length <= 0) throw bad_length();
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        exit(1);
    }
    m_data = new T[length]{};
}

template <typename T>
TArray<T>::TArray(const TArray& a)
{
    // Устанавливаем новую длину
    reallocate(a.getLength());

    // Копируем элементы
    for (int index{ 0 }; index < m_length; ++index)
        m_data[index] = a.m_data[index];
}

template <typename T>
TArray<T>::~TArray()
{
    delete[] m_data;
    //здесь не нужно устанавливать m_data в значение null или m_length в 0, 
    //так как объект в любом случае будет уничтожен сразу после этой функции
}

template <typename T>
void TArray<T>::erase()
{
    delete[] m_data;
   //Нам нужно убедиться, что здесь мы установили для m_data значение nullptr, 
   //иначе оно будет указывать на освобожденную память!
    m_data = nullptr;
    m_length = 0;
}

template <typename T>
T& TArray<T>::operator[](int index)
{
    //assert(index >= 0 && index < m_length);
    try
    {
        if (index < 0 || index >= m_length) throw bad_range();
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        exit(1);
    }
    return m_data[index];
}

//Перераспределить память и изменяет размер массива, любые существующие элементы будут уничтожены
//Эта функция работает быстро
template <typename T>
void TArray<T>::reallocate(int newLength)
{
    //Сначала удаляем все существующие элементы
    erase();

    //Если массив теперь будет пуст, выход
    if (newLength <= 0)
        return;

    //Выделяем память под новые элеметы
    m_data = new T[newLength];
    m_length = newLength;
}

// Изменяет размер массива. Любые существующие элементы будут сохранены. 
// Эта функция работает медленно.
template <typename T>
void TArray<T>::resize(int newLength)
{
    //Если массив уже имеет правильную длину, то выход
    if (newLength == m_length) return;

    //Если новая длина нулевая
    if (newLength <= 0)
    {
        erase();
        return;
    }

    // Теперь мы можем предположить, что newLength содержит как минимум 1 элемент. 
    // Алгоритм работает следующим образом: сначала мы собираемся выделить новый массив, 
    // потом скопировать элементы из существующего массива в новый массив.
    // Как только это будет сделано, мы сможем уничтожить старый массив и сделать, 
    // чтобы m_data указывал на новый массив.

    // Сначала выделяем память под новый массив
    T* data{ new T[newLength] };

    // Затем нам нужно выяснить, сколько элементов копировать из существующего
    // массива в новый массив. Мы хотим скопировать как можно больше элементов
    // в меньшем из двух массивов.
    if (m_length > 0)
    {
        int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

        // Копируем элементы один за другим
        for (int index{ 0 }; index < elementsToCopy; ++index)
            data[index] = m_data[index];
    }

    // Удаляем старый массив, потому что он больше не нужен
    delete[] m_data;

    // И вместо этого используем новый массив. 
    // Так как данные были распределены динамически, они не будут уничтожены, если выйдут за пределы области видимости.
    m_data = data;
    m_length = newLength;
}

template <typename T>
TArray<T>& TArray<T>::operator=(const TArray& a)
{
    if (&a == this)
        return *this;

    //Установим размер нового массива
    reallocate(a.getLength());

    // Копируем элементы
    for (int index{ 0 }; index < m_length; ++index)
        m_data[index] = a.m_data[index];

    return *this;
}

template <typename T>
void TArray<T>::insertBefore(T value, int index)
{
    // Провеяем на корректность индекса
    //assert(index >= 0 && index <= m_length);
    try
    {
        if (index < 0 || index > m_length) throw bad_range();
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        exit(1);
    }


    // Сначала создаем новый массив на один элемент больше старого массива
    T* data{ new T[m_length + 1] };

    // Скопируйте все элементы до индекса
    for (int before{ 0 }; before < index; ++before)
        data[before] = m_data[before];

    // Вставляем наш новый элемент в новый массив
    data[index] = value;

    // Скопируем все значения после вставленного элемента
    for (int after{ index }; after < m_length; ++after)
        data[after + 1] = m_data[after];

    // Удаляеме старый массив и используйте вместо него новый массив
    delete[] m_data;
    m_data = data;
    ++m_length;
}

template <typename T>
void TArray<T>::remove(int index)
{
    //assert(index >= 0 && index < m_length);
    try
    {
        if (index < 0 || index >= m_length) throw bad_range();
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        exit(1);
    }


    // Если удаляем последний элемент массива, мы можем просто стереть массив и вернуться раньше
    if (m_length == 1)
    {
        erase();
        return;
    }

    // Создаем новый массив на один элемент меньше старого массива
    T* data{ new T[m_length - 1] };

    // Копируем все элементы до индекса
    for (int before{ 0 }; before < index; ++before)
        data[before] = m_data[before];

    // Копируем все значения после удаленного элемента
    for (int after{ index + 1 }; after < m_length; ++after)
        data[after - 1] = m_data[after];

    // Удаляем старый массив и используем вместо него новый массив
    delete[] m_data;
    m_data = data;
    --m_length;
}

// Дополнительные функции для удобства
template <typename T>
void TArray<T>::insertAtBeginning(T value)
{
    insertBefore(value, 0);
}
template <typename T>
void TArray<T>::insertAtEnd(T value)
{
    insertBefore(value, m_length);
}

template <typename T>
int TArray<T>::getLength() const { return m_length; }

template <typename T>
int TArray<T>::findValue(T value) const
{
    int index = -1;
    for (int i{ 0 }; i < m_length; ++i)
        if (m_data[i] == value)
        {
            index = i;
            break;
        }

    return index;
}




