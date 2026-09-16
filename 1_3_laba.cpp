#include <iostream>

struct SafeArray
{
    int* data;
    int size;
};

SafeArray createArray(int size)
{
    SafeArray arr;
    arr.size = size;
    arr.data = new int[size]{};
    return arr;
}

int& getElement(SafeArray& arr, int index)
{
static int a = 0;
if (index < 0 || index >= arr.size)
{
    std::cout << "Ошибка: индекс " << index << " выходит за границы массива (размер: " << arr.size << ")\n";
    return a;
}
return arr.data[index];
}

int main()
{
SafeArray Arr = createArray(5);
std::cout << "Создан массив размером 5\n";
std::cout <<"Заполнение массива через getElement:\n";
for (int i = 0; i < Arr.size; i++)
{
    getElement(Arr, i) = (i + 1) * 50;
}
std::cout << " \ngetElement(Arr, 2) = 999:\n";
getElement(Arr, 2) = 999;
std::cout << "\nПопытка доступа за границами (getElement(Arr,20)):\n";
int& ref = getElement(Arr, 20);
std::cout << "Возвращена ссылка на заглушку: " << ref << "\n";
return 0;
}