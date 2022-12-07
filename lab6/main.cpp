#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> array = {5,3,78,31,22,55,23213,777,234324,8678678,333,51,4,6,8,123,5,1,2,1,2,80,70,2,11,677};
    int size = array.size();
    for(int i = 0; i < size - 1; i++ ){
        int min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            if (array.at(j) < array.at(min_index))
            {
                min_index = j;
            }
        }
        if(min_index != i){
            std::swap(array.at(i),array.at(min_index));
        }
    }
    for(int i = 0; i < size; i++ ){
        std::cout << array.at(i) << std::endl;
    }

    return 0;
}
