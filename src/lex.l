%option noyywrap
%option nounput
%option noinput
%{
#include <iostream>
#include <string>
#include "parser.tab.hpp"
#include "logger.hpp"

using namespace std;
%}
%option yylineno
/* Regular definitions */
WhiteSpace              [ \t\n\r]*
LineComment             "//".*
LongComment             "/*"((\/+[^*/]*)|("*"+[^*/]+)|([^*/]*))*"*"+"/"
NonZeroDigit            [1-9]
DecimalDigit            [0-9]
OctalDigit              [0-7]
HexPrefix               0[xX]
HexDigit                [0-9a-fA-F]
IDNonDigit              [A-Za-z_]
IDChar                  [0-9A-Za-z_]
%%
{WhiteSpace}                                            {;}
{LineComment}|{LongComment}                             {;}
"int"                                                   {return INT;}
"return"                                                {return RETURN;}
[(){};]                                                 {return yytext[0];}
{NonZeroDigit}{DecimalDigit}*                           {yylval.int_val=(int)strtol(yytext,NULL,10); return INT_CONST;}
"0"{OctalDigit}*                                        {yylval.int_val=(int)strtol(yytext,NULL,8); return INT_CONST;}
{HexPrefix}{HexDigit}*                                  {yylval.int_val=(int)strtol(yytext,NULL,16); return INT_CONST;}
{IDNonDigit}{IDChar}*                                   {yylval.str_val=new string(yytext); return IDENT;}
.                                                       {LOG_ERROR("\"%s\"@[line #%d]: unrecognized token", yytext, yylineno);}
%%