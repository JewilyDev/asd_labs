#include <iostream>
#include <stack>
int main() {
    std::stack<char> subseq_stack; // Основной стек для работы с последовательностью
    std::string subseq_raw; // Строка для записи последовательности
    std::cout << "Write down the subsequence" << std::endl;
    std::getline(std::cin,subseq_raw);
    bool flag = false; // Флаг наличия хотя бы одной открывающей скобки
    for(int i = 0; i < subseq_raw.length(); i++){
        char bracket = subseq_raw[i];
        if(bracket == '(' || bracket == '{' || bracket == '['){ // Записываем в стек открывающуюся скобку, и устанавливаем флаг
            subseq_stack.push(bracket);
            flag = true;
        } else if (bracket == ')' || bracket == '}' || bracket == ']'){
            int modifier;
            if(bracket == ')')
                modifier = 1;
            else
                modifier = 2;
            // Проверяем стек на пустоту и сопоставляем верх стека и текущую скобку. Если не совпали, последовательность не существует
            if(subseq_stack.empty() || subseq_stack.top() != char((int)bracket - modifier)){ 
                std::cout << "The subsequence is not exist" << std::endl;
                bracket = 0;
                break;
            }else{
                //Иначе удаляем открывающуюся скобку из верхушки стека
                subseq_stack.pop();
            }
        }
        if(!bracket) //Заканчиваем цикл
            break;
    }
    if(flag && subseq_stack.empty()) // Если открывающаяся скобка была, и стек пуст, то такая последовательность является ПСП.
        std::cout << "The subsequence is exist" << std::endl;
}
