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


    explicit unionTypes(int intValue) : intValue(intValue) {};
    explicit unionTypes(bool boolValue) : boolValue(boolValue) {};
    explicit unionTypes(byte byteValue) : byteValue(byteValue) {};
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
callType* creatCallObj(string func_name, string func_arg, int lineno);


struct statementType{
    string name;

    statementType(string name) : name(name) {};
};


bool compareType(string type1, string type2);

struct loserType{
    string name;
    loserType(string name) : name(name) {};
};

void printProductionRule(int meow);


/** type is the type conversion, type 2 is the orginal type, val2 is the val being converted*/
unionTypes convertIntAndByte(string type1, string type2, unionTypes val2, int lineno);


/** Data structures */

struct symbolTableRow{
    string name;
    string type;
    unionTypes value;
    int offset;

    symbolTableRow(string name, string type, unionTypes value, int offset) : name(name), type(type), value(value), offset(offset) {};
};

struct symbolTable {
    vector<symbolTableRow> table;
    string context;

    symbolTable(){};
    symbolTable(string context) : context(context) {};
};

void addSymbolTableRow(string name, string type, unionTypes value);

int initGlobalDataStructures();

bool checkSymbolTableForSymbol(string symbolName);

string getSymbolType(string symbolName);

unionTypes giveTrashValue(string type);

void addSymbolTableRow(string name, string type);

bool compareType(string type1, string type2);

struct binopType{
    string name;
    binopType(string name) : name(name) {};
};

void initGlobalDataStructures();






/** --------------------------------------------------------MISC-------------------------------------------------------- */


void printProductionRule(int meow);

bool isNumber(string type);

expType* createBinExp(expType* Bexp , binopType* Op , expType* Aexp);

void createScope(string context);

void popScope();


#endif //HW3_OUTPUT_HPP_HW3_H
