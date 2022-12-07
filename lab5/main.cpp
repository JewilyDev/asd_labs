#include <iostream>
#include <vector>

int main() {
    std::vector<int> array = {5,1,78,31,22,55,23213,777,234324,8678678,333,51,4,6,8,123,5,1,2,1,2,80,70,2,11,677};
    int size = array.size();
    for(int i = 1; i < size ; i++){
        for(int j = i; j > 0 && array.at(j-1) > array.at(j); j--){
            std::swap(array.at(j-1), array.at(j));
        }
    }
    for(int i = 1; i < size ; i++){
        std::cout << array.at(i) << std::endl;
    }
    return 0;
}
