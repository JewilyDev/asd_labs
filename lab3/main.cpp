#include <iostream>
#include <vector>
#include <algorithm>
std::vector <int> v;
int main()
{
    int x = 1000;
    int a = 1;
    int b = 0;
    int c = 0;
    int i = 0;
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

    sort(v.rbegin(), v.rend());

    for (int k = 0; k < i; k++)
        std::cout << v[k] << " " << std::endl;
}