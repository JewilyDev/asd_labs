#include<iostream>
#include <string>
class Tree
{
public:
	int value;
	Tree* parent; // поле ссылка на родителя
	Tree* left; // поле ссылка на левого потомка
	Tree* right; // поле ссылка на правого потомка
        std::string string; // для линейно-скобочной записи.

	Tree(const int v,  Tree* p) // Конструктор, который позволяет положить значение в виде листа одного из узлов
	{
		value = v;
		parent = p;
	}
	
    Tree()
    {

    }
    Tree(std::string str)// Конструктор образовывающий дерево по скобочной последовательности
    {
        string = str;
    }

	void add(const int v) // Метод добавления значения в дерево
	{
        if (v > value) // Если новое значение больше значения узла добавляем в правое поддерево, или создаем это поддерево если его нет
        {
            if (right == nullptr)
            {
                right = new Tree(v,this);
            }
            else
            {
                right->add(v);
            }
        } 
        else // Аналогично если значение меньше, добавляем влево.
        {
            if (left== nullptr)
            {
                left = new Tree(v,this);
            }
            else
            {
                left->add(v);
            }
        }
	}
    // Рекурсивный алгоритм поиска,к оторый в зависимости от текущего значения сворачивает вправо/влево для поиска. Начинается с корня дерева
    Tree* search(Tree* item, int v) // поиск поддерева по элементу
    {
        if (item == nullptr && item->value == v) // элемент и содержит искомое значение
        {
            return item;
        }
        if (item != nullptr && item->value > v) // Поиск в левом поддереве
        {
            return search(item->left, v);
        }
        if (item != nullptr && item->value < v)// Поиск в правом поддереве
        {
            return search(item->right, v);
        }
    }
    // Входная точка поиска в дереве по значению
    Tree* Search(int v)
    {
        return search(this, v);
    }
    // Самая сложная операция - удаление из дерева, самый сложный случай - наличие двух потомков у удаляемого узла.
    void remove(int value)
    {
        Tree *item = this->Search(value);
        if (item == nullptr) return; // Если такого элемента даже нет - удалять нечего
        Tree* currentTree = nullptr;
        // удаление корня
        if (this == item)
        {
            if (item->right != nullptr) // Если есть правое поддерево, тогда ищем в нём самый левый элемент(он будет наименьшим)
            {
                currentTree = item->right;
                while (currentTree->left != nullptr)
                {
                    currentTree = currentTree->left;
                }

            }
            else if (item->left != nullptr) // Если имеется только левое дерево, а правое не существует, то ищим самый правый элемент, он будет наименьшим
            {
                currentTree = item->left;
                while (currentTree->right != nullptr)
                {
                    currentTree = currentTree->right;
                }
            }

            int val = currentTree->value;
            remove(val);//Удаляем это значение рекурсивно, смотри случаи описанные ниже
            item->value = val;

        }
        // удаление листьев, самый тривиальный случай, где мы просто значение соотв.потомка у родителя элемента устанавливаем как nullptr.
        else if (item->left == nullptr && item->right == nullptr && item->parent != nullptr)
        {
            if (item->parent->right == item)
            {
                item->parent->right = nullptr;
            }
            else
            {
                item->parent->left = nullptr;
            }
        }
        // удаление узла, который имеет левого потомка, просто вставляем дочерний узел вместо удаляемого
        else if (item->left != nullptr && item->right == nullptr && item->parent != nullptr)
        {
            item->left->parent = item->parent;
            if (item == item->parent->left)
            {
                *item->parent->left = *item->left;
            }
            else if (item == item->parent->right)
            {
                *item->parent->right = *item->left;
            }

        }
        // удаление узла, который имеет правого потомка, просто вставляем дочерний узел вместо удаляемого
        else if (item->left == nullptr && item->right != nullptr && item->parent != nullptr)
        {
            item->right->parent = item->parent;
            if (item == item->parent->left)
            {
                *item->parent->left = *item->right;
            }
            else if (item == item->parent->right)
            {
                *item->parent->right = *item->right;
            }

        }
        // удаление узла, который имеет оба потомка. Самый сложный случай, который следует описать детальнее
	// Его основной идеей является поиск наименьшего элемента в левом поддереве(если оно есть, или самого маленького в правом)
	// Затем найденный элемент стоит поменять местами с удаляемым, и удалить последний как лист(описано выше)
	// Нижеприведённый код исполняет алгоритм "смены местами" этих двух элементов, что является весьма муторным процессом.
        else if (item->left != nullptr && item->right != nullptr && item->parent != nullptr)
        {
            currentTree = item->right; // Сначала заходим в правое поддерево 
            if (currentTree->left != nullptr) // Если существует левый потомок, тогда мы двигаемся влево до упора
            {
                while (currentTree->left != nullptr)
                {
                    currentTree = currentTree->left; // Записываем самый левый элемент
                }
                if (currentTree->right != nullptr) // если у самого левого элемента существует ещё и правый потомок, тогда перестраиваем дерево:
                {
                    currentTree->right->parent = currentTree->parent; // Ставим правого потомка на наше место
                    currentTree->parent->left = currentTree->right; // Меняем местами соседа текущего листа и правого потомка текущего листа
                }
                else
                {
                    currentTree->parent->left = nullptr; //Если правый потомок остутствует, то делаем тоже что и выше, формально, но проще сразу задать соседу nullptr
                }
		// Если имеем совпадение найденного листа с текущим узлом, то переприсваеваем указатели
                item->left->parent = currentTree;
                currentTree->left = item->left;
                if (item->parent->right == item) // Если мы "лежим справа", то меняем узлы местами(правый на текущий)
                {
                    currentTree->parent = item->parent->right;
                    item->parent->right = currentTree;
                }
                else // Если мы "лежим справа", то меняем узлы местами(левый на текущий)
                {
                    currentTree->parent = item->parent->left;
                    item->parent->left = currentTree;
                }
                currentTree->right = item->right;
                item->right->parent = currentTree;
            }
            else // Аналогично действиям выше, только без учёта существования левого потомка.
            {
                item->left->parent = currentTree;
                currentTree->left = item->left;
                currentTree->parent = item->parent;
                if (item->parent->left == item)
                {
                    item->parent->left = currentTree;
                }
                else
                {
                    item->parent->right = currentTree;
                }
            }

        }


    }
    std::string toString(int value) // переводит число в строку, стандартный сишный atoi на случай 2 разрядов
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
    void print(Tree* tree) // переводит дерево в линейно-скобочуню запись рекурсивно
    {
        string += toString(tree->value); // добавляем значение текущего узла 
        if (tree->left != nullptr || tree->right != nullptr)
        {
            string += '('; // Идентифицируем вложенность
            if (tree->left != nullptr)
            {
                print(tree->left); //упомянутая рекурсия(влево)
            }
            string += ',';
            if (tree->right != nullptr)
            {
                print(tree->right); //упомянутая рекурсия(вправо)
            }
            string += ')';
        }

    }
    void Print()
    {
        print(this);
    }

    bool isDigital(const char elem) // быстрая проверка на то, является ли строка - числом
    {
        return (elem >= '0' && elem <= '9');
    }

    Tree parse(std::string str) // парсит  строку в бинарное дерево. Главное замечание: 48 = '0'
    {
        Tree result;
        int index;
        if (isDigital(str[0]) && isDigital(str[1])) // Если в числе 2 разряда переводим его в число
        {
            int val = (str[0] - 48) * 10 + str[1] - 48;
            result.value = val;
            index = 2;
        }
        else if (isDigital(str[0]) && !isDigital(str[1])) // Одноразрядное число переводим в цифру
        {
            int val = str[0] - 48;
            result.value = val; // задаём корень дерева по первому числу
            index = 1;
        }


        for (int i = index; i < str.size() - 1;)// Переводим остальную последовательность, вставляя уже описанным методом add переводя строки в числа
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



int main()
{
    std::string str = "8(3(1,6(4,7)),10(,14(13,)))";
    Tree tree;
    tree = tree.parse(str);
    Tree newTree = tree;
    newTree.remove(10);
    newTree.Print();
    for (auto& value : newTree.string)
    {
        std::cout << value;
    }

}
