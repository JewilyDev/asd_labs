#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

class HashTable
{
  int capacity;
  std::list<std::vector<char>> *table;
  std::vector<int> keys;
public:
  HashTable(int V);
  void insertItem(int key, std::vector<char> data);
  int search(std::string text);
  void deleteItem(int key,std::vector<char> data = {});
  int checkPrime(int n)
  {
  int i;
  if (n == 1 || n == 0)
  {
    return 0;
  }
  for (i = 2; i < n / 2; i++)
  {
    if (n % i == 0)
    {
    return 0;
    }
  }
  return 1;
  }
  int getPrime(int n)
  {
  if (n % 2 == 0)
  {
    n++;
  }
  while (!checkPrime(n))
  {
    n += 2;
  }
  return n;
  }
  int hashFunction(int key)
  {
  return (key % capacity);
  }
  void displayHash();
};
HashTable::HashTable(int c)
{
  int size = getPrime(c);
  this->capacity = size;
  table = new std::list<std::vector<char>>[size];
}
void HashTable::insertItem(int key,  std::vector<char> data)
{
  int index = hashFunction(key);
  std::vector<int>::iterator findIter = std::find(keys.begin(), keys.end(), index);
  if(findIter == keys.end()){
      keys.push_back(index);
  }
  table[index].push_back(data);
}
void HashTable::deleteItem(int key,std::vector<char> data)
{
  int index = hashFunction(key);
  if (table[index].begin() != table[index].end()){}
}
void HashTable::displayHash()
{
  std::list<std::vector<char>>::iterator it = table->begin();
    for (int j = 0; j < keys.size();j++){
        std::cout << "[" << keys[j] << "]"  <<std::endl;
        std::cout << "[" << std::endl;
        for(auto n : table[keys[j]]){
            for(auto k : n){
                std::cout << k;
            }
            std::cout << std::endl;
        }
        std::cout << ']' << std::endl;
    }
}
int HashTable::search(std::string text)
{
    std::vector<char> val;
    for (int i = 0; i <= text.size(); i++){
        if((int)text[i] != 0){
            val.push_back(text[i]);
        }
    }
    int tempHash = 0;
    for(char i : val){
        tempHash += (int)i;
    }
    int index = hashFunction(tempHash);
    int counter = 0;
    for(auto n : table[index]){
        if(n == val){
            counter++;
        }
    }
    return counter;
}
int main()
{
  std::string text;
  int preHash = 0;
  HashTable h(1000);
  std::vector<char> word = {};
  std::vector<char> wordToFind = {};
  std::getline(std::cin,text,'\n');
  for (int i = 0; i <= text.size(); i++){
        if(text[i] != ' ' && (int)text[i] != 0){
            preHash += (int)text[i];
            word.push_back(text[i]);
        }else{
            h.insertItem(h.hashFunction(preHash),word);
            word.clear();
            preHash = 0;
        }
    }
  std::cout << h.search("is") << std::endl;
  h.displayHash();

}