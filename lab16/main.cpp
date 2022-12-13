#include <iostream>
#include <stack>
#include <string>
#include <vector>
class Tree // Комментарии добавлены только к методам, касающимся обхода, все пояснения к структуре дерева есть в ЛР 17.
{
public:
    int value;
    Tree* parent;
    Tree* left;
    Tree* right;
    std::string string; // для линейно-скобочной записи.
    Tree(const int v, Tree* p)
    {
        value = v;
        parent = p;
    }

    Tree()
    {

    }

    Tree(std::string str)
    {
        string = str;
    }

    void add(const int v)
    {
        if (v > value)
        {
            if (right == nullptr)
            {
                right = new Tree(v, this);
            }
            else
            {
                right->add(v);
            }
        }
        else
        {
            if (left == nullptr)
            {
                left = new Tree(v, this);
            }
            else
            {
                left->add(v);
            }
        }
    }


    std::string toString(int value) // переводит число в строку
    {
        std::string result;

        if (value > 9)
        {
            result += char(value / 10 + 48);
            result += char(value % 10 + 48);
        }
        else
        {
            result += char(value + 48);
        }

        return result;
    }


    void print(Tree* tree) // переводит дерево в линейно-скобочуню запись
    {
        string += toString(tree->value);
        if (tree->left != nullptr || tree->right != nullptr)
        {
            string += '(';
            if (tree->left != nullptr)
            {
                print(tree->left);
            }
            string += ',';
            if (tree->right != nullptr)
            {
                print(tree->right);
            }
            string += ')';
        }

    }


    void Print()
    {
        print(this);
    }


    bool isDigital(const char elem)
    {
        return (elem >= '0' && elem <= '9') ? true : false;
    }


    Tree parse(std::string str) // парсит  строку в бинарное дерево
    {
        Tree result;
        int index;
        if (isDigital(str[0]) && isDigital(str[1]))
        {
            int val = (str[0] - 48) * 10 + str[1] - 48;
            result.value = val;
            index = 2;
        }
        else if (isDigital(str[0]) && !isDigital(str[1]))
        {
            int val = str[0] - 48;
            result.value = val;
            index = 1;
        }


        for (int i = index; i < str.size() - 1;)
        {
            if (isDigital(str[i]) && isDigital(str[i + 1]))
            {
                int value = (str[i] - 48) * 10 + str[i + 1] - 48;
                result.add(value);
                i += 2;
            }
            else if (isDigital(str[i]) && !isDigital(str[i + 1]))
            {
                int value = str[i] - 48;
                result.add(value);
                i++;
            }
            else
            {
                i++;
            }
        }

        return result;
    }
};
void direct(std::vector<int>& v, Tree* tree) // Прямой обход бзе использования рекурсии
{
    std::stack <Tree*> s; // Создаём стек из указателей на узлы
    s.push(nullptr); // Первым элементом(в итоге последним) точно будет пустой указатель
    Tree* tempTree = tree; // сохраняем копию дерева, по которому совершаем обход
    do
    {
        if (tempTree != nullptr)  // Если полученный на вход указатель не пустой, тогда вставляем его в стек, и значение его вставляем в соотв.вектор,
                                  // Сам же элемент сдвигаем влево.
        {
            s.push(tempTree);
            v.push_back(tempTree->value);
            tempTree = tempTree->left;
        }
        else
        {
            if (s.top() == nullptr) // Если стек пуст(имеется только пустой указатель), тогда завершаем обход
            {
                break;
            }
            tempTree = s.top(); // Берём верхушку стека
            s.pop(); // "снимаем её" на обход
            tempTree = tempTree->right; // Двигаемся вправо
        }
    } while (true);
}

void center(std::vector<int>& v, Tree* tree)
{
    std::stack <Tree*> s; // Создаём стек из указателей на узлы
    s.push(nullptr); // Первым элементом(в итоге последним) точно будет пустой указатель
    Tree* tempTree = tree; // сохраняем копию дерева, по которому совершаем обход
    do
    {
        if (tempTree != nullptr)
        {
            s.push(tempTree); // вставляем в стек текущий указатель и двигаемся влево
            tempTree = tempTree->left;
        }
        else
        {
            if (s.top() == nullptr) // если завершили обход - выходим
            {
                break;
            }
            tempTree = s.top(); // вынимаем указатель сверху и продолжаем обход вправо.
            s.pop();
            v.push_back(tempTree->value);
            tempTree = tempTree->right;
        }
    } while (true);
}

void reverse(std::vector<int>& v, Tree* tree)
{
    std::stack <Tree*> s; // Создаём  стек из указателей на узлы
    Tree* lastVisited = nullptr; // Используем указатель последнего посещённого узла
    Tree* tempTree = tree; // сохраняем копию дерева, по которому совершаем обход
    while (!s.empty() || tempTree != nullptr) // Завершим обход если стек будет пуст и указатель обхода будет пустым
    {
        if (tempTree != nullptr)
        {
            s.push(tempTree);  // вставляем в стек текущий указатель и двигаемся влево
            tempTree = tempTree->left;
        }
        else
        {
            Tree* topTree = s.top(); // вынимаем указатель сверху
            if (topTree->right != nullptr && lastVisited != topTree->right) // Если последний посещенный узел не есть правый потомок, то двигаемся из узла вверху стека вправо
            {
                tempTree = topTree->right;
            }
            else // иначе указываем, что верхний элемент стека - последний посещённый, и извлекаем его.
            {
                v.push_back(topTree->value);
                lastVisited = s.top();
                s.pop();
            }
        }
    }
}


int main()
{

    std::vector <int> directValues;
    std::vector <int> centerValues;
    std::vector <int> reverseValues;
    int maxElem;
    std::string str = "8(3(1,6(4,7)),10(,14(13,)))";
    Tree tree;
    tree = tree.parse(str);
    Tree newTree = tree;
    newTree.Print();

    direct(directValues, &newTree); //прямой обход
    center(centerValues, &newTree);
    reverse(reverseValues, &newTree);

    for (auto& value : reverseValues)
    {
        std::cout << value << "\t";
    }
}
