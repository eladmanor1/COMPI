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
    if (type1 == "STRING"){
        return (type2 == "STRING");
    }
    else if(type1 == "BOOL") {
        return (type2 == "BOOL");
    }
    else if(type1 == "INT") {
        return (type2 == "INT");
    }
    else if(type1 == "BYTE") {
        return (type2 == "BYTE");
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
        if (type != "STRING"){
            errorPrototypeMismatch(lineno, func_name, "STRING");
            exit(0);
        }
        return (new callType("VOID", func_name));
    }
    if(func_name=="printi") {
        if(type != "INT") {
            errorPrototypeMismatch(lineno, func_name, "INT");
            exit(0);
        }
        return (new callType("VOID",func_name));
    }
    if(func_name=="readi") {
        if(type != "INT") {
            errorPrototypeMismatch(lineno, func_name, "INT");
            exit(0);
        }
        return (new callType("INT",func_name));
    }
    return nullptr;
}

void initSymbolTablesStack(){
    symbolTable tempTable;
    tempTable.table.push_back(symbolTableRow("print", "VOID", unionTypes((int*)nullptr), 0));
    tempTable.table.push_back(symbolTableRow("printi", "VOID",unionTypes((int*)nullptr), 0));
    tempTable.table.push_back(symbolTableRow("readi", "INT",unionTypes((int*)nullptr), 0));
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
    if(type == "BYTE" || type == "INT")
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
    //Here we already knows that the 2 exps are numbers!
    //TODO: add here some value calculation and pass it on!

        string type;
        if(Aexp->type == "INT" || Bexp->type == "INT"){
            type = "INT";
        }
        else{
            type = "BYTE";
        }
        unionTypes trashvalue = giveTrashValue(type);
        return new expType(type,trashvalue,false,"");
}

unionTypes convertIntAndByte(string type1, string type2, unionTypes val2, int lineno){
    if(type1 == "INT" && type2 == "INT"){
        return unionTypes(val2.intValue);
    }
    else if(type1 == "INT" && type2 == "BYTE"){
        return unionTypes((int)val2.byteValue);
    }
    else if(type1 == "BYTE" && type2 == "INT"){
        byte temp = (byte)(val2.intValue);
        return unionTypes(temp);
    }
    /** byte and byte */
    else{
        return unionTypes(val2.byteValue);
    }
}


unionTypes giveTrashValue(string type){
    if (type == "STRING"){
        return unionTypes("");
    }
    else if(type == "BOOL"){
        return unionTypes(false);
    }
    else if(type == "BYTE"){
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
        return "STRING";
    }
    else if(name == "printi" || name == "readi"){
        return "INT";
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


