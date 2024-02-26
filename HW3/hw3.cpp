//
// Created by יובל קרן on 22/02/2024.
//

#include "hw3.hpp"
#include <iostream>
#include <stack>
#include "hw3_output.hpp"

using namespace std;
using namespace output;



vector<symbolTable> symbolTablesStack;
stack<int> offsetStack;

bool checkSymbolTableForSymbol(string symbolName){
    if(symbolTablesStack.empty()){
        return false;
    }

    for(auto& currSymbolTable : symbolTablesStack){
        for(auto& currRow : currSymbolTable.table){
            if(currRow.name == symbolName){
                return true;
            }
        }
    }
    return false;
}


void addSymbolTableRow(string name, string type, unionTypes value){
    if(symbolTablesStack.empty()){
        initGlobalDataStructures();
    }

    int offset = offsetStack.top();
    offsetStack.top() += 1;

    symbolTableRow rowToAdd(name, type, value, offset);

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
    else{
        printf("Something has gone terribly wrong!\n");
        return false;
    }
}

void printProductionRule(int meow){
    ++meow;
}


callType* creatCallObj(string func_name, string type, int lineno){
    if(type == "")
        return nullptr;
    if(func_name=="print") {
        if (type != "string"){
            errorPrototypeMismatch(lineno, func_name, "string");
            exit(0);
        }
        return (new callType("void", func_name));
    }
    if(func_name=="printi") {
        if(type != "int") {
            errorPrototypeMismatch(lineno, func_name, "int");
            exit(0);
        }
        return (new callType("void",func_name));
    }
    if(func_name=="readi") {
        if(type != "int") {
            errorPrototypeMismatch(lineno, func_name, "int");
            exit(0);
        }
        return (new callType("int",func_name));
    }
    return nullptr;
}

void initSymbolTablesStack(){
    symbolTable tempTable;
    tempTable.push_back(symbolTableRow("print", "void", unionTypes((int*)nullptr), -1));
    tempTable.push_back(symbolTableRow("printi", "void",unionTypes((int*)nullptr), -1));
    tempTable.push_back(symbolTableRow("readi", "int",unionTypes((int*)nullptr), -1));
    tempTable.context = "global";
    symbolTablesStack.push_back(tempTable);
}

void initOffsetStack(){
    offsetStack.push(0);
}

void addSymbolTable(string context){
    symbolTable tempTable(context);
    int tempValue = offsetStack.top();

    symbolTablesStack.push_back(tempTable);
    offsetStack.push(tempValue);
}

void initGlobalDataStructures(){
    initSymbolTablesStack();
    initOffsetStack();
}

string getSymbolType(string symbolName){
    if(symbolTablesStack.empty()){
        printf("SHITTTTT\n");
    }

    for(auto& currSymbolTable : symbolTablesStack){
        for(auto& currRow : currSymbolTable.table){
            if(currRow.name == symbolName){
                return currRow.type;
            }
        }
    }
    return "error and im crazy";
}


unionTypes convertIntAndByte(string type1, string type2, unionTypes val2, int lineno){
    if(type1 == "int" && type2 == "int"){
        return unionTypes(val2.intValue);
    }
    else if(type1 == "int" && type2 == "byte"){
        return unionTypes((int)val2.byteValue);
    }
    else if(type1 == "byte" && type2 == "int"){
        byte temp = (byte)(val2.intValue);
        return unionTypes(temp);
    }
    /** byte and byte */
    else{
        return unionTypes(val2.byteValue);
    }
}
