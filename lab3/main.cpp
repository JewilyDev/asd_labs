#include <iostream>
#include <vector>
#include <algorithm>
std::vector <int> v;
int main()
{
    int x = 1000; // Произвольное число для которого хотим получить результат
    int a = 1;
    int b = 0;
    int c = 0;
    int i = 0;
    // Последовательно составляем все числа состоящие из степеней 3 5 и 7, записываем их в вектор
    while (a <= x)
    {
        b = a;
        while (b <= x)
        {
            c = b;
            while (c <= x)
            {
                v.push_back(c);
                i++;
                c *= 7;
            }
            b *= 5;
        }
        a *= 3;
    }

    sort(v.rbegin(), v.rend()); // Сортируем полученный вектор для удобства восприятия

    for (int k = 0; k < i; k++) // Выводим полученные значения.
        std::cout << v[k] << " " << std::endl;
}
