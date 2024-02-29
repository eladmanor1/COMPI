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
int dummy = initGlobalDataStructures();


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
        printf("ERROR - symbolTableStack is empty!");
    }

    int offset = offsetStack.top();
    offsetStack.top() += 1;

    symbolTableRow rowToAdd(name, type, value, offset);

    symbolTablesStack.back().table.push_back(rowToAdd);
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
    tempTable.table.push_back(symbolTableRow("print", "void", unionTypes((int*)nullptr), 0));
    tempTable.table.push_back(symbolTableRow("printi", "void",unionTypes((int*)nullptr), 0));
    tempTable.table.push_back(symbolTableRow("readi", "int",unionTypes((int*)nullptr), 0));
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

int initGlobalDataStructures(){
    initSymbolTablesStack();
    initOffsetStack();
    return 0;
}

string getSymbolType(string symbolName){
    if(symbolTablesStack.empty()){
        //TODO somthing
        printf("SHITTTTT\n");
    }

    /** going in reverse order over the symboltable stack, so we get the most recent occurence */
    for(auto currSymbolTable = symbolTablesStack.rbegin(); currSymbolTable != symbolTablesStack.rend(); ++currSymbolTable){
        for(auto& currRow : currSymbolTable->table){
            if(currRow.name == symbolName){
                return currRow.type;
            }
        }
    }
    return "error and im crazy";
}

bool isNumber(string type){
    if(type == "byte" || type == "int")
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


expType* createBinExp(expType* Aexp , binopType* Op , expType* Bexp){
        int res_int;
        byte res_byte;
        Avalue = unionTypes(Aexp->value);
        Bvalue = unionTypes(Bexp->value);
        if (Op->name == "+") {
//            res_int = Aexp->value.intValue + Bexp->value.intValue;
//            res_byte = byte(static_cast<int>(Aexp->value.byteValue) + static_cast<int>(Bexp->value.byteValue));
            res = unionTypes(Avalue+Bvalue);

        }
        if (Op->name == "-") {
//            res_int = Aexp->value.intValue - Bexp->value.intValue;
//            res_byte = byte(static_cast<int>(Aexp->value.byteValue) - static_cast<int>(Bexp->value.byteValue));
            res = unionTypes(Avalue-Bvalue);
        }
        if (Op->name == "*") {
//            res_int = Aexp->value.intValue * Bexp->value.intValue;
//            res_byte = byte(static_cast<int>(Aexp->value.byteValue) * static_cast<int>(Bexp->value.byteValue));
            res = unionTypes(Avalue*Bvalue);

        }
        if (Op->name == "/") {
//            res_int = Aexp->value.intValue / Bexp->value.intValue;
//            res_byte = byte(static_cast<int>(Aexp->value.byteValue) / static_cast<int>(Bexp->value.byteValue));
            res = unionTypes(Avalue/Bvalue);

        }
        if(Aexp->type == "int" || Bexp->type == "int"){
            return (new expType("int",res.intValue,false,""));
        } else {
            return (new expType("byte",res.byteValue,false,""));
        }
        return nullptr;
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


unionTypes giveTrashValue(string type){
    if (type == "string"){
        return unionTypes("");
    }
    else if(type == "bool"){
        return unionTypes(false);
    }
    else if(type == "byte"){
        byte meow = (byte)0;
        return unionTypes(meow);
    }
    else{
        return unionTypes(0);
    }
}


void createScope(string context){
    symbolTable newTable(context);
    symbolTablesStack.push_back(newTable);

    //creating a new level and putting in the highest level same value, seems weird but that's how the stack is used
    int temp = offsetStack.top();
    offsetStack.push(temp);
}

bool checkIfFunc(string name){
    //TODO:add a check if this is not a var also.
    if((name == "print") || (name == "printi") || (name == "readi")){
        return true;
    }
    else{
        return false;
    }
    return false;
}

string getFuncArgType(string name){
    if(name == "print"){
        return "string";
    }
    else if(name == "printi" || name == "readi"){
        return "int";
    }
    else{
        return "ERRRORRR!!!!!!";
    }
}


void popScope(){
    endScope();
    symbolTable currTable = symbolTablesStack.back();

    //do the prints
    for(auto & currRow : currTable.table){
        bool isFunc = checkIfFunc(currRow.name);
        if(!isFunc){
            printID(currRow.name, currRow.offset, currRow.type);
        }
        else{
            string funcArgType = getFuncArgType(currRow.name);
            printID(currRow.name, currRow.offset, makeFunctionType(funcArgType, currRow.type));
        }
    }

    //pop the data structures!
    symbolTablesStack.pop_back();
    offsetStack.pop();
}


bool checkIfInsideWhileBlock(){

    /** going in reverse order over the symboltable stack, so we get the most recent occurence. I don't think it really matters in this case, but still, it's more correct*/
    for(auto currSymbolTable = symbolTablesStack.rbegin(); currSymbolTable != symbolTablesStack.rend(); ++currSymbolTable){
        if(currSymbolTable->context == "while"){
            return true;
        }
    }
    return false;
}


