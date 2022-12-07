#include <iostream>
#include "math.h"
int main() {
    int x;
    int a,b,c;
    std::cin >> x;
    for(int s = 1; s <= x; s++){
        for(int i = 0; i <= (int)log2(x); i++){
            a = i;
            for(int j = 0; j <= (int)log2(x); j++){
                b = j;
                for(int k = 0; k <= (int)log2(x); k++){
                    c = k;
                    if(pow(3,a) * pow(5,b) * pow(7,c) == s)  {
                        std::cout << s << "C" << std::endl;
                    }
                }
            }
        }
    }
    return 0;
}
