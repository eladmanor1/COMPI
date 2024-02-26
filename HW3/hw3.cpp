//
// Created by יובל קרן on 22/02/2024.
//

#include "hw3.hpp"
#include <iostream>
#include <stack>
#include "hw3_output.hpp"

using namespace std;
using namespace output;

#define MAX_BYTE 255

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
        initGlobalDataStructures();
    }

    int offset = offsetStack.top();
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
    tempTable.push_back(symbolTableRow("print", "void", -1));
    tempTable.push_back(symbolTableRow("printi", "void", -1));
    tempTable.push_back(symbolTableRow("readi", "int", -1));
    symbolTablesStack.push_back(tempTable);
}

void initOffsetStack(){
    offsetStack.push(0);
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
        for(auto& currRow : currSymbolTable){
            if(currRow.name == symbolName){
                return currRow.type;
            }
        }
    }
    return "error and im crazy";
}

bool isNumber(expType* exp){
    if(exp->type == "byte" || exp->type == "int")
        return true;
    return false;
}
//
//void  checkForOversize(int res, int lineno){
//    if (res >= MAX_BYTE){
//        errorByteTooLarge(res,lineno);
//        exit(0);
//    }
//}


expType* createBinExp(expType* Aexp , binType* Op , expType* Bexp){
    //here we already know that Bexp->type == Aexp->type
        if(Op == "+"){
            res = unionTypes(Aexp->value + Bexp->value);
        }
        if(Op == "-") {
            res = unionTypes(Aexp->value - Bexp->value);
        }
        if(Op == "*"){
            res = unionTypes(Aexp->value *Bexp->value);
        }
        if(Op == "/") {
            res = unionTypes(Aexp->value / Bexp->value);
         }
        return (new expType(Bexp->type,res,false,""));
    }

}