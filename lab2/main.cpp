#include <iostream>
#include <stack>

bool IsCorrectBrackets(std::string brackets){
    std::stack<char> subseq_stack;
    std::string subseq_raw = brackets;
    for(int i = 0; i < subseq_raw.length(); i++){
        char bracket = subseq_raw[i];
        if(bracket == '(' || bracket == '{' || bracket == '['){
            subseq_stack.push(bracket);
        }else{
            int modifier;
            if(bracket == ')')
                modifier = 1;
            else
                modifier = 2;
            if(subseq_stack.top() != char((int)bracket - modifier)){
                bracket = 0;
                return false;
            }
            else{
                subseq_stack.pop();
            }
        }
        if(!bracket)
            break;
    }
    if(subseq_stack.empty())
        return true;
}

int main() {
    std::stack<char> expression;
    std::string expression_raw;
    std::getline(std::cin,expression_raw);
    for(int i = 0; i < expression_raw.length(); i++)
    {

    }

    return 0;
}
