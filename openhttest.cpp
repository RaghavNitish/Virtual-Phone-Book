#include <iostream>
#include "header_c.h"
#include <string>

int main(){
    std::string line;
    DoubleHashing hash_obj;
	while(getline(std::cin, line)){
		if (line.substr(0, 1) == "n"){
		    int operand = std::stoi(line.substr(2));
		    hash_obj.create_table(operand);
		}
		else if (line.substr(0, 1) == "i"){
		    unsigned long int key = std::stoul(line.substr(2, 12)); 
		    std::string value = line.substr(13);
		    hash_obj.insert(key, value);
		}
		else if (line.substr(0, 1) == "s"){
		    unsigned long int operand = std::stoul(line.substr(2));
		    hash_obj.search(operand);
		}
		else if (line.substr(0, 1) == "d"){
		    unsigned long int operand = std::stoul(line.substr(2));
		    hash_obj.delete_table(operand);
		}
	}
    return 0;
}
