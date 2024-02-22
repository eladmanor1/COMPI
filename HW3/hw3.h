//
// Created by יובל קרן on 22/02/2024.
//

#ifndef HW3_OUTPUT_HPP_HW3_H
#define HW3_OUTPUT_HPP_HW3_H
#include <iostream>
#include <vector>
#include <stack>

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
    string name ="";
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


class statementType{
    string name;
};


class symbolTableRow{
    string name;
    string type;
    int offset;
};


typedef vector<symbolTableRow> symbolTable;


vector<symbolTable> symbolTablesStack;
stack<int> offsetStack;


bool checkSymbolTableForSymbol(string symbolName){
    if(symbolTablesStack.empty()){
        return false;
    }

    for(auto& currSymbolTable : symbolTablesStack){
        for(auto& currRow : currSymbolTable){
            if(currRow.name == symbolName){
                return true;
            }
        }
    }
    return false;
}


void addSymbolTableRow(string name, string type){
    if(symbolTablesStack.empty()){
        cout << "Something wrong has happened!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        return;
    }

    offset = offsetStack.top();
    offsetStack.top() += 1;

    symbolTableRow rowToAdd(name, type, offset);

    symbolTablesStack.back().push_back(rowToAdd);
}

bool compareType(string type1, string type2){
    if (type1 == "string"){
        return (type2 == "string");
    }
    else if(type1 == "bool") {
        return (type2 == "bool");
    }
    else if(type1 == "int") {
        return (type2 == "int");
    }
    else if(type1 == "byte") {
        return (type2 == "byte");
    }
}







#endif //HW3_OUTPUT_HPP_HW3_H
