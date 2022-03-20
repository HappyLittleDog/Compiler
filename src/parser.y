%code requires {
  #include <memory>
  #include <string>
  #include "ast.hpp"
}
%{
#include <iostream>
#include <memory>
#include <string>
#include "ast.hpp"

using namespace std;
int yylex();
void yyerror(std::unique_ptr<BaseAst> &ast, const char *s);
%}
%parse-param { std::unique_ptr<BaseAst> &ast }
%union {
    int int_val;
    std::string* str_val;
    BaseAst* ast_val;
}
%token INT RETURN
%token <str_val> IDENT
%token <int_val> INT_CONST
%type <ast_val> FuncDef FuncType Block Stmt Number
%%
CompUnit
    :   FuncDef 
        {
            ast=unique_ptr<BaseAst>($1);
        }
    ;

FuncDef
    :   FuncType IDENT '(' ')' Block
        {
            auto cur=new FuncDef();
            cur->functype_=unique_ptr<BaseAst>($1);
            cur->ident_=*unique_ptr<string>($2);
            cur->block_=unique_ptr<BaseAst>($5);
            $$=cur;
        }
    ;

FuncType
    :   INT
        {
            auto cur=new FuncType();
            cur->rettype_=DataType::INT;
            $$=cur;
        }
    ;

Block
    :   '{' Stmt '}'
        {
            auto cur=new Block();
            cur->stmt_=unique_ptr<BaseAst>($2);
            $$=cur;
        }
    ;

Stmt
    :   RETURN Number ';'
        {
            auto cur=new Stmt();
            cur->retv_=unique_ptr<BaseAst>($2);
            $$=cur;
        }
    ;

Number
    :   INT_CONST
        {
            auto cur=new Number();
            cur->int_const_=to_string($1);
            $$=cur;
        }
    ;
%%
void yyerror(std::unique_ptr<BaseAst> &ast, const char *s)
{
    cerr<<"[error] "<<s<<endl;
}