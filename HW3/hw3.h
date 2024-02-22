//
// Created by יובל קרן on 22/02/2024.
//

#ifndef HW3_OUTPUT_HPP_HW3_H
#define HW3_OUTPUT_HPP_HW3_H
#include <iostream>
#include <vector>

using namespace std;

class intType{
    int value;
    const string type = "int";
};

class byteType{
    byte value;
    const string type = "byte";
};

class boolType{
    bool value;
    const string type = "bool";
};

class expType{
    string type;
    string value;
    bool is_var;


};



#endif //HW3_OUTPUT_HPP_HW3_H
