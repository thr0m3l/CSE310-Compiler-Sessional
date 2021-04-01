#include "./SymbolTable/SymbolTable.h"
#include <fstream>
#include <string>
// #include <iostream>
using namespace std;


int line_count = 1;
int keyword_count = 0;
int err_count = 0;

ofstream log, token;
ifstream in;
SymbolTable st(&log);

string toUpper(string str){
    for (auto & c: str) c = toupper(c);
    return str;

}

string tokenGenerator(string s){
    return "<" + toUpper(s) + ">";
}

string tokenGenerator(string type, string symbol){
    return "<" + type + "," + symbol + ">";
}

void printLog(int line, string token, string lexeme)
{
    log << "\nLine no " << line << ": Token "
        << tokenGenerator(token)<<" Lexeme "<<lexeme<<" found";
}

void printToken(string lexeme){
    //Prints token for keywords;
    token<<tokenGenerator(lexeme);
}

void printToken(string tkn, string lexeme){
    token<<tokenGenerator(tkn, lexeme);
}

void insertToken(string symbol, string type)
{
    st.insertSymbol(symbol, type);
    st.printAll();
}

//------------------------------------------------------------------

void handle_keyword(char *str)
{
    string s(str);
    printLog(line_count,toUpper(s), s);
    printToken(s);
    keyword_count++;
}

void handle_const_int(char *str){
    string s(str);
    insertToken(s, "CONST_INT");
    printLog(line_count, "CONST_INT", s);
    printToken("CONST_INT", s);
}

void handle_const_float(char *str){
    string s(str);
    insertToken(s, "CONST_FLOAT");
    printLog(line_count, "CONST_FLOAT", s);
    printToken("CONST_FLOAT", s);
}

void handle_const_char(char *str, string type){
    string s(str);
    string refined = "";
    
    for(int i = 1; i < s.length() - 1; ++i){
        refined += s[i];
    }

    insertToken(refined, type);
    printLog(line_count, type, refined);
    printToken(type, refined);
}

void handle_operator(char *str, string opr){
    string s(str);

    printLog(line_count, opr, s);
    printToken(opr, s);

    if (opr == "LCURL"){
        st.enterScope();
    } 

    if (opr == "RCURL"){
        st.exitScope();
    }    
}

void handle_id (char *str){
    string s(str);
    printLog(line_count, "ID", s);
    printToken("ID", s);
    insertToken(s, "ID");
}

void handle_error(char *str, string msg){
    string s(str);
    log <<"\n"<<"Error at line no: "<<line_count<<". "<<msg<<": "<<s<<endl;
    err_count++;
}

//-------------------------------------------------------------------




