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

void printSafe(const SafeArray& arr)
{
    std::cout << "Массив (размер " << arr.size << "): ";
    for (int i = 0; i < arr.size; i++)
    {
        std::cout << arr.data[i] << " ";
    }
    std::cout << "\n";
}

SafeArray resizeArray(const SafeArray& oldArr, int newSize)
{
    SafeArray newArr;
    newArr.size = newSize;
    newArr.data = new int [newSize]{};
    int copy = (oldArr.size < newSize) ? oldArr.size : newSize;
    
    if (newSize < oldArr.size)
    {
        std::cout << "Удаленные элементы: ";
        for (int i = newSize; i < oldArr.size; i++)
        {
            std::cout << oldArr.data[i] << " ";
        }
        std::cout << "\n";
    }

    for (int i = 0; i < copy; i++)
    {
        newArr.data[i] = oldArr.data[i];
    }
    return newArr;
}

void deleteArray(SafeArray& arr) 
{ 
    delete[] arr.data; 
    arr.data = nullptr; 
    arr.size = 0; 
} 

int main()
{
SafeArray Arr = createArray(5);
std::cout << "Создан массив\n";
printSafe(Arr);
std::cout <<"Заполнение массива через getElement:\n";
for (int i = 0; i < Arr.size; i++)
{
    getElement(Arr, i) = (i + 1) * 50;
}
printSafe(Arr);
std::cout << " \ngetElement(Arr, 2) = 999:\n";
getElement(Arr, 2) = 999;
printSafe(Arr);
std::cout << "\nПопытка доступа за границами (getElement(Arr,20)):\n";
int& ref = getElement(Arr, 20);
std::cout << "Возвращена ссылка на заглушку: " << ref << "\n";
std::cout << "\nУвеличение размера с 5 до 8:\n";
SafeArray resizedUp = resizeArray(Arr, 8);
printSafe(resizedUp);

std::cout << "\nУменьшение размера с 8 до 4:\n";
SafeArray resizedDown = resizeArray(resizedUp, 4);
printSafe(resizedDown);

deleteArray(Arr); 
deleteArray(resizedUp); 
deleteArray(resizedDown); 
std::cout << "\nПамять освобождена.\n";
return 0;
}