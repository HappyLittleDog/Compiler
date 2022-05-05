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
%token INT RETURN PLUS MINUS MULT DIV MOD EQQ NEQ LT GT LEQ GEQ NOT AND OR EQ CONST IF ELSE WHILE BREAK CONTINUE VOID
%token <str_val> IDENT
%token <int_val> INT_CONST
%type <int_val> BType
%type <ast_val> CompUnits CompUnit FuncDef Block Stmt Exp PrimaryExp UnaryExp AddExp MulExp RelExp EqExp LAndExp LOrExp Number Decl ConstDecl ConstDefs ConstDef ConstInitVal BlockItems BlockItem LVal ConstExp VarDecl VarDefs VarDef InitVal Open_If_Stmt Closed_If_Stmt FuncFParams FuncFParam FuncRParams
%%
Program
    :   CompUnits
        {
            ast=unique_ptr<BaseAst>($1);
        }
    ;

CompUnits
    :   
        {
            auto cur=new CompUnits();
            $$=cur;
        }
    |   CompUnits CompUnit
        {
            auto cur=reinterpret_cast<CompUnits*>($1);
            cur->items_.push_back(unique_ptr<BaseAst>($2));
            $$=cur;
        }
    ;

CompUnit
    :   FuncDef
        {
            auto cur=new CompUnit();
            cur->item_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
    |   Decl
        {
            auto cur=new CompUnit();
            cur->item_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
    ;

FuncDef
    :   BType IDENT '(' FuncFParams ')' Block
        {
            auto cur=new FuncDef();
            cur->functype_=int($1);
            cur->ident_=*unique_ptr<string>($2);
            cur->params_=shared_ptr<BaseAst>($4);
            auto blk=reinterpret_cast<Block*>($6);
            blk->params_=cur->params_;
            cur->block_=unique_ptr<BaseAst>(blk);
            $$=cur;
        }
    ;

FuncFParams
    :
        {
            auto cur=new FuncFParams();
            $$=cur;
        }
    |   FuncFParam
        {
            auto cur=new FuncFParams();
            cur->params_.push_back(unique_ptr<BaseAst>($1));
            $$=cur;
        }
    |   FuncFParams ',' FuncFParam
        {
            auto cur=reinterpret_cast<FuncFParams*>($1);
            cur->params_.push_back(unique_ptr<BaseAst>($3));
            $$=cur;
        }
    ;

FuncFParam
    :   BType IDENT
        {
            auto cur=new FuncFParam();
            cur->type_=int($1);
            cur->ident_ = *($2);
            $$=cur;
        }
    ;

FuncRParams
    :   
        {
            auto cur=new FuncRParams();
            $$=cur;
        }
    |   Exp
        {
            auto cur=new FuncRParams();
            cur->params_.push_back(unique_ptr<BaseAst>($1));
            $$=cur;
        }
    |   FuncRParams ',' Exp
        {
            auto cur=reinterpret_cast<FuncRParams*>($1);
            cur->params_.push_back(unique_ptr<BaseAst>($3));
            $$=cur;
        }
    ;

Block
    :   '{' BlockItems '}'
        {
            auto cur=new Block();
            cur->items_=unique_ptr<BaseAst>($2);
            $$=cur;
        }
    ;

BlockItems
    :
        {
            auto cur=new BlockItems();
            $$=cur;
        }
    |   BlockItems BlockItem
        {
            auto cur=reinterpret_cast<BlockItems*>($1);
            cur->items_.push_back(unique_ptr<BaseAst>($2));
            $$=cur;
        }
    ;

BlockItem
    :   Decl
        {
            auto cur=new BlockItem();
            cur->cur_derivation_=0;
            cur->item_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
    |   Stmt
        {
            auto cur=new BlockItem();
            cur->cur_derivation_=1;
            cur->item_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
    ;

Decl
	:	ConstDecl
		{
            auto cur=new Decl();
            cur->item_=unique_ptr<BaseAst>($1);
            $$=cur;
		}
    |   VarDecl
        {
            auto cur=new Decl();
            cur->item_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
	;

ConstDecl
	:	CONST BType ConstDefs ';'
		{
            auto cur=new ConstDecl();
            cur->type_=int($2);
            cur->item_=unique_ptr<BaseAst>($3);
            $$=cur;
		}
	;

VarDecl
    :   BType VarDefs ';'
        {
            auto cur=new VarDecl();
            cur->type_=int($1);
            cur->item_=unique_ptr<BaseAst>($2);
            $$=cur;
        }
    ;

BType
    :   VOID
        {
            $$=0;
        }
	|	INT 
        {
            $$=1;
        }
	;

ConstDefs
	:	ConstDef
		{
            auto cur=new ConstDefs();
            cur->defs_.push_back(unique_ptr<BaseAst>($1));
            $$=cur;
		}
	|	ConstDefs ',' ConstDef
		{
            auto cur=reinterpret_cast<ConstDefs*>($1);
            cur->defs_.push_back(unique_ptr<BaseAst>($3));
            $$=cur;
		}
	;

ConstDef
	:	IDENT EQ ConstInitVal
		{
            auto cur=new ConstDef();
            cur->ident_ = *($1);
            cur->initval_=unique_ptr<BaseAst>($3);
            // CurConstSymTab.insert(cur->ident_, cur->initval_->CalcVal());
            $$=cur;
		}
	;

ConstInitVal
	:	ConstExp
		{
            auto cur=new ConstInitVal();
            cur->subexp_=unique_ptr<BaseAst>($1);
            $$=cur;
		}
	;

ConstExp
	:	Exp
		{
            auto cur=new ConstExp();
            cur->subexp_=unique_ptr<BaseAst>($1);
            $$=cur;
		}
	;

VarDefs
    :   VarDef
        {
            auto cur=new VarDefs();
            cur->defs_.push_back(unique_ptr<BaseAst>($1));
            $$=cur;
        }
    |   VarDefs ',' VarDef
        {
            auto cur=reinterpret_cast<VarDefs*>($1);
            cur->defs_.push_back(unique_ptr<BaseAst>($3));
            $$=cur;
        }
    ;

VarDef
    :   IDENT
        {
            auto cur=new VarDef();
            cur->cur_derivation_=0;
            cur->ident_ = *($1);
            // CurVarSymTab.insert(cur->ident_);
            $$=cur;
        }
    |   IDENT EQ InitVal
        {
            auto cur=new VarDef();
            cur->cur_derivation_=1;
            cur->ident_ = *($1);
            cur->initval_=unique_ptr<BaseAst>($3);
            // CurVarSymTab.insert(cur->ident_);
            $$=cur;
        }
    ;

InitVal
    :   Exp
        {
            auto cur=new Exp();
            cur->subexp_=unique_ptr<BaseAst>($1);
            // cur->isconst_=cur->subexp_->IsConst();
            $$=cur;
        }
    ;

Stmt
    :   Open_If_Stmt
        {
            auto cur=new Stmt();
            cur->cur_derivation_=0;
            cur->subexp_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
    |   Closed_If_Stmt
        {
            auto cur=new Stmt();
            cur->cur_derivation_=1;
            cur->subexp_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
    ;

Closed_If_Stmt
    :   RETURN Exp ';'
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>($2);
            $$=cur;
        }
    |   RETURN ';'
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=0;
            $$=cur;
        }
    |   LVal EQ Exp ';'
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            $$=cur;
        }
    |   ';'
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=2;
            $$=cur;
        }
    |   Exp ';'
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=3;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
    |   Block
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=4;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
    |   IF '(' Exp ')' Closed_If_Stmt ELSE Closed_If_Stmt
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=5;
            cur->subexp1_=unique_ptr<BaseAst>($3);
            cur->subexp2_=unique_ptr<BaseAst>($5);
            cur->subexp3_=unique_ptr<BaseAst>($7);
            $$=cur;
        }
    |   WHILE '(' Exp ')' Stmt
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=6;
            cur->subexp1_=unique_ptr<BaseAst>($3);
            cur->subexp2_=unique_ptr<BaseAst>($5);
            $$=cur;
        }
    |   BREAK ';'
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=7;
            $$=cur;
        }
    |   CONTINUE ';'
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=8;
            $$=cur;
        }
    ;

Open_If_Stmt
    :   IF '(' Exp ')' Stmt
        {
            auto cur=new Open_If_Stmt();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>($3);
            cur->subexp2_=unique_ptr<BaseAst>($5);
            $$=cur;
        }
    |   IF '(' Exp ')' Closed_If_Stmt ELSE Open_If_Stmt
        {
            auto cur=new Open_If_Stmt();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>($3);
            cur->subexp2_=unique_ptr<BaseAst>($5);
            cur->subexp3_=unique_ptr<BaseAst>($7);
            $$=cur;
        }
    ;

Exp
    :   LOrExp
        {
            auto cur=new Exp();
            cur->subexp_=unique_ptr<BaseAst>($1);
            // cur->isconst_=cur->subexp_->IsConst();
            $$=cur;
        }
    ;

LOrExp
    :   LAndExp
        {
            auto cur=new LOrExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            $$=cur;
        }
    |   LOrExp OR LAndExp
        {
            auto cur=new LOrExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    ;

LAndExp
    :   EqExp
        {
            auto cur=new LAndExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            $$=cur;
        }
    |   LAndExp AND EqExp
        {
            auto cur=new LAndExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    ;

EqExp
    :   RelExp
        {
            auto cur=new EqExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            $$=cur;
        }
    |   EqExp EQQ RelExp
        {
            auto cur=new EqExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    |   EqExp NEQ RelExp
        {
            auto cur=new EqExp();
            cur->cur_derivation_=2;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    ;

RelExp
    :   AddExp
        {
            auto cur=new RelExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            $$=cur;
        }
    |   RelExp LT AddExp
        {
            auto cur=new RelExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    |   RelExp GT AddExp
        {
            auto cur=new RelExp();
            cur->cur_derivation_=2;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    |   RelExp LEQ AddExp
        {
            auto cur=new RelExp();
            cur->cur_derivation_=3;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    |   RelExp GEQ AddExp
        {
            auto cur=new RelExp();
            cur->cur_derivation_=4;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    ;

AddExp
    :   MulExp
        {
            auto cur=new AddExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            $$=cur;
        }
    |   AddExp PLUS MulExp
        {
            auto cur=new AddExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    |   AddExp MINUS MulExp
        {
            auto cur=new AddExp();
            cur->cur_derivation_=2;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    ;

MulExp
    :   UnaryExp
        {
            auto cur=new MulExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            $$=cur;
        }
    |   MulExp MULT UnaryExp
        {
            auto cur=new MulExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    |   MulExp DIV UnaryExp
        {
            auto cur=new MulExp();
            cur->cur_derivation_=2;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    |   MulExp MOD UnaryExp
        {
            auto cur=new MulExp();
            cur->cur_derivation_=3;
            cur->subexp1_=unique_ptr<BaseAst>($1);
            cur->subexp2_=unique_ptr<BaseAst>($3);
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            $$=cur;
        }
    ;

UnaryExp
    :   PLUS UnaryExp
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=0;
            cur->subexp_=unique_ptr<BaseAst>($2);
            // cur->isconst_=cur->subexp_->IsConst();
            $$=cur;
        }
    |   MINUS UnaryExp
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=1;
            cur->subexp_=unique_ptr<BaseAst>($2);
            // cur->isconst_=cur->subexp_->IsConst();
            $$=cur;
        }
    |   NOT UnaryExp
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=2;
            cur->subexp_=unique_ptr<BaseAst>($2);
            // cur->isconst_=cur->subexp_->IsConst();
            $$=cur;
        }
    |   PrimaryExp
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=3;
            cur->subexp_=unique_ptr<BaseAst>($1);
            // cur->isconst_=cur->subexp_->IsConst();
            $$=cur;
        }
    |   IDENT '(' FuncRParams ')'
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=4;
            cur->isconst_=0;
            cur->ident_ = *($1);
            cur->subexp_=unique_ptr<BaseAst>($3);
            $$=cur;
        }
    ;

PrimaryExp
    :   '(' Exp ')'
        {
            auto cur=new PrimaryExp();
            cur->cur_derivation_=0;
            cur->subexp_=unique_ptr<BaseAst>($2);
            // cur->isconst_=cur->subexp_->IsConst();
            $$=cur;
        }
    |   Number
        {
            auto cur=new PrimaryExp();
            // cur->isconst_=true;
            cur->cur_derivation_=1;
            cur->subexp_=unique_ptr<BaseAst>($1);
            $$=cur;
        }
    |	LVal
		{
			auto cur=new PrimaryExp();
            cur->cur_derivation_=2;
            cur->subexp_=unique_ptr<BaseAst>($1);
            // cur->isconst_=cur->subexp_->IsConst();
            $$=cur;
		}
    ;

LVal
	:	IDENT
		{
            auto cur=new LVal();
            cur->ident_ = *($1);
            // cur->isconst_=CurConstSymTab.exists(cur->ident_);
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