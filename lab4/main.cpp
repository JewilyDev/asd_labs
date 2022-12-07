#include <iostream>
#include <vector>


int main() {
    std::vector<int> array = {5,1,78,31,22,55,23213,777,234324,8678678,333,51,4,6,8,123,5,1,2,1,2,80,70,2,11,677};
    float factor = 1.2473309; // Число из лекции(определено опытным путём)
    int size = array.size();
    int step = size - 1;
    while (step >= 1)
    {
        for (int i = 0; i + step < size; i++)
        {
            if (array.at(i) > array.at(i + step))
            {
                std::swap(array.at(i), array.at(i + step));
            }
        }
        step =  step / factor;
    }
    for(int i = 0 ; i < size; i++){
        std::cout << array.at(i) << std::endl;
    }
    return 0;
}
