#include <vector>
#include <iostream>
#include <string> 
bool isExist(const std::string& str)
{
	std::stack<char> subseq_stack; // Основной стек для работы с последовательностью
    bool flag = false; // Флаг наличия хотя бы одной открывающей скобки
    for(int i = 0; i < str.length(); i++){
        char bracket = str[i];
        if(bracket == '(' || bracket == '{' || bracket == '['){ // Записываем в стек открывающуюся скобку, и устанавливаем флаг
            subseq_stack.push(bracket);
            flag = true;
        }else{
            int modifier;
            if(bracket == ')')
                modifier = 1;
            else
                modifier = 2;
            // Проверяем стек на пустоту и сопоставляем верх стека и текущую скобку. Если не совпали, последовательность не существует
            if(subseq_stack.empty() || subseq_stack.top() != char((int)bracket - modifier)){ 
                return false;
            }else{
                //Иначе удаляем открывающуюся скобку из верхушки стека
                subseq_stack.pop();
            }
        }
        if(!bracket) //Заканчиваем цикл
            break;
    }
    return(flag && subseq_stack.empty());  // Если открывающаяся скобка была, и стек пуст, то такая последовательность является ПСП.     
}

bool isOperation(const char symbol) // Функция-провекра на то, что заданный символ - символ операции
{
	return (symbol == '+' || symbol == '-' || symbol == '/' || symbol == '*');
}


bool isFool(const std::string& str) // проверяем на то, что данная строка является корректным выражением(содержит цифры, операции и знак равенства)(Проверка на "дурака")
{
	bool result = false;
	for (int i = 0; i < str.size() - 1; i++)
	{
		if ((str[i] >= '0' && str[i] <= '9') && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		{
			result = true;
		}

		else if (isOperation(str[i]) && isOperation(str[i + 1]))
		{
			result = true;
		}
		else if (str.back() != '=')
		{
			result = true;
		}
	}

	return result;
}


float calculation(const std::string str) // Основная функция рассчётов
    //В программе реализуется алгоритм обратной польской нотации, где в стек записываются последовательно получаемые значения,
    // а затем с помощью операций по приоритетам над значениями совершаются соответственные действия, в конце получаем результат
{
	std::vector <char> stackOperation; // Стек с операциями
	std::vector <float> stackNumbers;// Стек с числами, которые находятся в выражении
	int cnt = -1;
	int backCnt = -1;
	for (int i = 0; i < str.size(); i++)
	{
		if ((isOperation(str[i]) || str[i] == '(') && str[i] != '=')
		{
			cnt = str[i] == '(' ? i : -1;
			if (str[i] != '(') // Определяем, что данный символ - операция
			{
				stackOperation.push_back(str[i]);
			}			
			if (str[i] == '(') // Иначе обрабатываем всё что идёт в скобках записывая в стек чисел.
			{
				int j;
				for (j = str.size(); j != i; j--)
				{
					if (str[j] == ')')
					{
						stackNumbers.push_back(calculation(str.substr(i + 1, j - i - 1)));
						i = j ;
						break;
					}

				}
				
			}
			
		}
		if (!isOperation(str[i]) && str[i] != '=' && str[i] != '(' && str[i] != ')') //записываем числа, которые лежат без скобок
		{
			stackNumbers.push_back(str[i] - 48);
		}
        // Четыре нижеследующих условных блока совершают операции по приоритету от умножения до вычитания.
        // Вынимаем два числа из стека с числами, вынимаем операцию из соотв.стека(она соответствует той, которая определена в условии)
        // Совершаем необходимое преобразование(умножение, деление, сложение или вычитание)
		if (!stackOperation.empty() && stackOperation.back() == '*' && stackNumbers.size() >= 2 && !isOperation(str[i]) && str[i + 1] != '(') 
		{
			float secondNumber = stackNumbers.back();
			stackNumbers.pop_back();
			float firstNumber = stackNumbers.back();
			stackNumbers.pop_back();
			stackOperation.pop_back();
			stackNumbers.push_back(firstNumber * secondNumber);
		}
		if (!stackOperation.empty() && stackOperation.back() == '/' && stackNumbers.size() >= 2 && !isOperation(str[i]) && str[i + 1] != '(' )
		{
			float secondNumber = stackNumbers.back();
			stackNumbers.pop_back();
			float firstNumber = stackNumbers.back();
			stackNumbers.pop_back();
			stackOperation.pop_back();
			stackNumbers.push_back(firstNumber / secondNumber);
		}
		if (!stackOperation.empty() && stackOperation.back() == '+' && stackNumbers.size() >= 2 && str[i + 1] != '*' && str[i + 1] != '/' && str[i + 1] != '(')
		{
			float secondNumber = stackNumbers.back();
			stackNumbers.pop_back();
			float firstNumber = stackNumbers.back();
			stackNumbers.pop_back();
			stackNumbers.push_back(firstNumber + secondNumber);
		}
		if (!stackOperation.empty() && stackOperation.back() == '-' && stackNumbers.size() >= 2 && str[i + 1] != '*' && str[i + 1] != '/' && str[i + 1] != '(')
		{
			float secondNumber = stackNumbers.back();
			stackNumbers.pop_back();
			float firstNumber = stackNumbers.back();
			stackNumbers.pop_back();
			stackOperation.pop_back();
			stackNumbers.push_back(firstNumber - secondNumber);

		}
	}
    // Результат вычислений
	return stackNumbers.back();
}

// Проверка на деление на ноль
bool isZeroDivided(const std::string& str)
{
	bool result = false;
	for (int i = 0; i < str.size(); i++) 
	{
		if (str[i] == '/')
		{
			if (str[i + 1] == '0')
			{
				result = true;
			}
			if (str[i + 1] == '(')
			{
				int j;
				for (j = i + 2; j != ')'; j++)
				{
				}
				result = calculation(str.substr(i + 2, j - i + 2)) == 0 ? true : result;
			}
		}
	}

	return result;
}

void main()
{
	std::string str = "3+2*(5+3*(9+6)+1)+3=";
	if (!isZeroDivided(str) && !isFool(str) && isExist(str))
	{
		std::cout << calculation(str) << std::endl;
	}
	else
	{
		std::cout << "fool" << std::endl;
	}
}
