#include <iostream>
#include "header_c.h"
#include <string>
#include <cmath>

//Node constructor
Node::Node(unsigned long int node_key, std::string node_value){
    prev = NULL;
    next = NULL; 
    key = node_key;
    value = node_value;
}

//HashTable class constructor
HashTable::HashTable(){
    size = 0;
}

//A function which deletes an existing hash table (if any) and creates a new hash table given the table’s size
void HashTable::create_table(int table_size){
    if (size != 0){
        Node* current_node;
        Node* temp;

        for (int i = 0; i < size; i++){
            current_node = ht[i];

            while (current_node != NULL){
                temp = current_node;
                current_node = current_node->next;
                delete temp;
            }
            ht[i] = NULL;
        }

        size = 0;
    
    }

    ht = new Node* [table_size];
    size = table_size;

    for (int i = 0; i < size; i++){
        ht[i] = NULL;
    }
    std::cout << "success" << std::endl;
}

//HashTable class destructor
HashTable::~HashTable(){
    Node* current_node;
    Node* temp;

    for (int i = 0; i < size; i++){
        current_node = ht[i];

        while (current_node != NULL){
            temp = current_node;
            current_node = current_node->next;
            delete temp;
        }
        ht[i] = NULL;
    }
    size = 0;
}

//A function which inserts a key and the associated caller into the hash table
void HashTable::insert(unsigned long int key, std::string value){
    int ht_index = key % size;

    if (ht[ht_index] == NULL){
        Node *temp = new Node(key, value);
        ht[ht_index] = temp;
        std::cout << "success" << std::endl;
    }
    else{
        Node* current_node = ht[ht_index];
        Node* old_node;

        bool dup_key = false;

        while(current_node != NULL){
            if (current_node->key == key){
                std::cout << "failure" << std::endl;
                dup_key = true;
                break;
            }
            else{
                old_node = current_node;
                current_node = current_node->next;
            }    
        }
        if (dup_key == false){
            Node *temp = new Node(key, value);
            old_node -> next = temp;
            temp -> prev = old_node;

            std::cout << "success" << std::endl;
        }
    }
}

//A function which searches for a key in the hash table
void HashTable::search(unsigned long int key){
    int ht_index = key % size;
    Node* current_node = ht[ht_index];

    if (current_node == NULL){
        std::cout << "not found" << std::endl;
    }
    else{
        bool key_found = false;
        while(current_node != NULL){
            if (current_node -> key == key){
                key_found = true;
                std::cout << "found " << current_node ->value << " in " << ht_index << std::endl;
                break;
            }
            else{
                current_node = current_node->next;
            } 
        }
        if (key_found == false){
            std::cout << "not found" << std::endl;
        }
    }
}

//A function which prints the chain of keys that starts at a position
void HashTable::print(int i){
    Node* current_node = ht[i];
    
    while (current_node != NULL){
        if (current_node->next != NULL){
            std::cout << current_node->key;
        }
        else{
            std::cout << current_node->key << " ";
        }
        current_node = current_node->next;
    }
}

//A function which deletes a given key from the table
void HashTable::delete_table(unsigned long int key){
    int ht_index = key % size;
    Node *current_node = ht[ht_index];

    if (current_node == NULL){
        std::cout << "failure" << std::endl;
    }
    else{
        bool key_found = false;
        while (current_node != NULL){
            if (current_node->key == key){
                key_found = true;
                break;
            }
            else{
                current_node = current_node->next;
            }
        }
        if (key_found == true){
            if (current_node->next == NULL && current_node->prev != NULL){
                current_node->prev->next = current_node->next;
            }
            else if (current_node->prev == NULL && current_node->next != NULL){
                current_node->next->prev = current_node->prev;

            }
            else if (current_node->next != NULL && current_node->prev != NULL){
                current_node->prev->next = current_node->next;
                current_node->next->prev = current_node->prev;
            }
            else{
                ht[ht_index] = NULL;
            }

            delete current_node;
            std::cout << "success" << std::endl;
        }

        else{
            std::cout << "failure" << std::endl;
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//Double Hashing Member Function Definitions

//A function which returns the value of the primary hash function
int DoubleHashing::h1(unsigned long int key){
    return key % size;
}

//A function which returns the value of the secondary hash function
int DoubleHashing::h2(unsigned long int key){
    int temp = fmod(std::floor(key/size), size);

    if (temp % 2 == 0){
        temp++;
    }
    return temp;
}

//DoubleHashing class constructor
DoubleHashing::DoubleHashing(){
    size = 0;
}

//A function which deletes an existing hash table (if any) and creates a new hash table given the table’s size
void DoubleHashing::create_table(int table_size){
    if (size != 0){
        for (int i = 0; i < size; i++){
            ht_state[i] = 0;
        }
    }
 
    ht.resize(table_size);
    ht_key.resize(table_size);
    ht_state.resize(table_size);

    for (int i = 0; i < size; i++){
        ht_state[i] = 0;
    }

    size = table_size;

    std::cout << "success" << std::endl;
}

//DoubleHashing class destructor
DoubleHashing::~DoubleHashing(){
        ht.clear();
        ht_state.clear();      
}

//A function which inserts a key and the associated caller into the hash table
void DoubleHashing::insert(unsigned long int key, std::string value){
    int ht_index = h1(key);
    int count = 0;
    bool found_key = false;
    int u = 1;

    //Checking the number of occupied locations
    for (int i = 0; i < size; i++){
        if (ht_state[i] == 1){
            count++;
        }
    }

    if (count == size){
        std::cout << "failure" << std::endl;
    }

    //If there is space....
    else{
        //Computing the hash table index
        while (ht_state[ht_index] == 1){
            ht_index = (h1(key) + u*h2(key)) % size;
            u++;
        }

        //If we find key in hash table, then we print failure
        for (int i = 0; i < size; i++){
            if ((ht_key[i] == key) && (ht_state[i] == 1)){
                found_key = true;
                break;
            }
        }

        if (found_key == true){
            std::cout << "failure" << std::endl;
        }

        //If we don't find the key, then we add it
        else{
            ht_key[ht_index] = key;
            ht[ht_index] = value;
            ht_state[ht_index] = 1;
            std::cout << "success" << std::endl;
        }
    }
}

//A function which deletes a given key from the table
void DoubleHashing::delete_table(unsigned long int key){
    int index;
    bool found_key = false;

    for (int i = 0; i < size; i++){
        if ((ht_key[i] == key) && (ht_state[i] == 1)){
            index = i;
            found_key = true;
            break;
        }
    }

    if (found_key == true){
        ht_state[index] = 0;
        std::cout << "success" << std::endl;
    }
    else{
        std::cout << "failure" << std::endl;
    }
}

//A function which searches for a key in the hash table
void DoubleHashing::search(unsigned long int key){
    int index;
    bool found_key = false;

    for (int i = 0; i < size; i++){
        if ((ht_key[i] == key) && (ht_state[i] == 1)){
            index = i;
            found_key = true;
            break;
        }
    }

    if (found_key == true){
        ht_state[index] = 1;
        std::cout << "found " << ht[index] << " in " << index << std::endl;
    }
    else{
        std::cout << "not found" << std::endl;
    }
}