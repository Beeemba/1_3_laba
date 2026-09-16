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

int main()
{
SafeArray Arr = createArray(5);
std::cout << "Создан массив размером 5\n";
return 0;
}