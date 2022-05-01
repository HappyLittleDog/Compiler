%code requires {
  #include <memory>
  #include <string>
  #include "ast.hpp"
  #include "logger.hpp"
}
%{
#include <iostream>
#include <memory>
#include <string>
#include "ast.hpp"
#include "logger.hpp"

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
%token INT RETURN PLUS MINUS MULT DIV MOD EQQ NEQ LT GT LEQ GEQ NOT AND OR
%token <str_val> IDENT
%token <int_val> INT_CONST
%type <ast_val> FuncDef FuncType Block Stmt Exp PrimaryExp UnaryExp Number
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
    :   RETURN Exp ';'
        {
            auto cur=new Stmt();
            cur->retv_=unique_ptr<BaseAst>($2);
            $$=cur;
        }
    ;

Exp
    :   UnaryExp
        {
            auto cur=new Exp();
            cur->subexp_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
    ;

UnaryExp
    :   PLUS UnaryExp
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=0;
            cur->subexp_=unique_ptr<BaseAst>($2);
            $$=cur;
        }
    |   MINUS UnaryExp
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=1;
            cur->subexp_=unique_ptr<BaseAst>($2);
            $$=cur;
        }
    |   NOT UnaryExp
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=2;
            cur->subexp_=unique_ptr<BaseAst>($2);
            $$=cur;
        }
    |   PrimaryExp
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=3;
            cur->subexp_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
    ;

PrimaryExp
    :   '(' Exp ')'
        {
            auto cur=new PrimaryExp();
            cur->cur_derivation_=0;
            cur->subexp_=unique_ptr<BaseAst>($2);
            $$=cur;
        }
    |   Number
        {
            auto cur=new PrimaryExp();
            cur->cur_derivation_=1;
            cur->subexp_=unique_ptr<BaseAst>($1);
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
    LOG_ERROR("%s", s);
    ast->Print();
}