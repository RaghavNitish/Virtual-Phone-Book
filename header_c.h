#include <iostream>
#include <vector>

class Node{
    public:
        Node* prev;
        Node* next;
        std::string value;
        unsigned long int key;

        Node(unsigned long int node_key, std::string node_value);
};

class HashTable{
    public:
        int size;
        Node** ht;

        HashTable();
        ~HashTable();
        void insert(unsigned long int key, std::string value);
        void search(unsigned long int key);
        void delete_table(unsigned long int key);
        void print(int i);
        void create_table(int table_size);
};

class DoubleHashing{
    public:
        int size;
        std::vector < std::string > ht;
        std::vector < bool > ht_state;
        std::vector < unsigned long int > ht_key;

        DoubleHashing();
        ~DoubleHashing();
        void insert(unsigned long int key, std::string value);
        void search(unsigned long int key);
        void delete_table(unsigned long int key);
        void create_table(int table_size);
        int h1(unsigned long int key);
        int h2(unsigned long int key);
};