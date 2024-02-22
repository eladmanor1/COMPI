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

class stringType{
    string value;
    const string type = "string"

};
class expType{
    string type;
    union value{
        int intValue;
        bool boolValue;
        byte byteValue;
        string stringValue;
        int* ptrVal;
    };
    bool is_var;
};

class typeType{
    string value;
    string type;
};

class typeID{
    string name;
    union value{
        int intValue;
        bool boolValue;
        byte byteValue;
        string stringValue;
    };
    string type;
};

class callType{
    string type;
};

callType* creatCallObj(string func_name, expType* func_arg){
    if( func_arg->name == "")
        return nullptr;
    switch (func_name){
        case "print" :
            if(func_arg->type != "string")
                return nullptr;
            return (new callType("void"));
            break;
        case "printi" :
            if(func_arg->type != "int")
                return nullptr;
            return (new callType("void"));
            break;
        case "readi" :
            if(func_arg->type != "int")
                return nullptr;
            return (new callType("int"));
            break;
        default : return nullptr; break;
    }
}

#endif //HW3_OUTPUT_HPP_HW3_H
