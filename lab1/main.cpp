#include <iostream>
#include <stack>
int main() {
    std::stack<char> subseq_stack;
    std::string subseq_raw;
    std::cout << "Write down the subsequence" << std::endl;
    std::getline(std::cin,subseq_raw);
    bool flag = false;
    for(int i = 0; i < subseq_raw.length(); i++){
        char bracket = subseq_raw[i];
        if(bracket == '(' || bracket == '{' || bracket == '['){
            subseq_stack.push(bracket);
            flag = true;
        }else{
            int modifier;
            if(bracket == ')')
                modifier = 1;
            else
                modifier = 2;
            if(subseq_stack.empty() || subseq_stack.top() != char((int)bracket - modifier)){
                std::cout << "The subsequence is not exist" << std::endl;
                bracket = 0;
                break;
            }else{
                subseq_stack.pop();
            }
        }
        if(!bracket)
            break;
    }
    if(flag && subseq_stack.empty())
        std::cout << "The subsequence is exist" << std::endl;
}
