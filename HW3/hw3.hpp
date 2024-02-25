//
// Created by יובל קרן on 22/02/2024.
//

#ifndef HW3_OUTPUT_HPP_HW3_H
#define HW3_OUTPUT_HPP_HW3_H
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

union unionTypes{
    int intValue;
    bool boolValue;
    byte byteValue;
    string* stringValue;
    int* ptrVal;


    unionTypes(int intValue) : intValue(intValue) {};
    unionTypes(bool boolValue) : boolValue(boolValue) {};
    unionTypes(byte byteValue) : byteValue(byteValue) {};
    unionTypes(int* ptrVal) : ptrVal(ptrVal) {};
    unionTypes(string* stringValue) : stringValue(stringValue) {};

};

struct intType{
    int value;
    string type;

    intType(int value) : value(value) {
        type = "int";
    };
};

struct byteType{
    byte value;
    const string type;

    byteType(byte value, string type) : value(value), type(type) {};

};

struct boolType{
    bool value;
    string type;

    boolType(int value, string type) : value(value), type(type) {};
    boolType(int value, char* type) : value(value) {
        this->type = type;
    };


};

struct stringType{
    string value;
    const string type;

    stringType(string value) : value(value), type("string") {};

};
struct expType{
    string type;
    unionTypes value;
    bool is_var;
    string name;

    expType(string type, unionTypes value, bool is_var, string name) : type(type), value(value), is_var(is_var), name(name) {};
};

struct typeType{
    string name;

    typeType(string name) : name(name) {};
};

struct typeID{
    string name;
    unionTypes value;
    string type;

    typeID(string name, unionTypes value, string type) : name(name), value(value), type(type) {};
};

struct callType{
    string type;
    string name;

    callType(string type, string name) : type(type), name(name) {};
};
//comment
callType* creatCallObj(string func_name, expType* func_arg);


struct statementType{
    string name;

    statementType(string name) : name(name) {};
};


struct symbolTableRow{
    string name;
    string type;
    int offset;

    symbolTableRow(string name, string type, int offset) : name(name), type(type), offset(offset) {};
};


typedef vector<symbolTableRow> symbolTable;


bool checkSymbolTableForSymbol(string symbolName);


void addSymbolTableRow(string name, string type);

bool compareType(string type1, string type2);

struct loserType{
    string name;
    loserType(string name) : name(name) {};
};


void initGlobalDataStructures();


void printProductionRule(int meow);




#endif //HW3_OUTPUT_HPP_HW3_H
