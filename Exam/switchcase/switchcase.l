%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%%

[\t ]+           ;  
\n               ; 

switch           { return SWITCH; }
case             { return CASE; }
default          { return DEFAULT; }
break            { return BREAK; }
return           { return RETURN; }
"<="             { return LE; }
">="             { return GE; }
"=="             { return EQ; }
"!="             { return NE; }
"{"              { return LBRACE; }
"}"              { return RBRACE; }
"("              { return LPAREN; }
")"              { return RPAREN; }
":"              { return COLON; }
";"              { return SEMICOLON; }
[0-9]+           { yylval = atoi(yytext); return NUM; }   
[a-zA-Z][a-zA-Z0-9]* { return ID; }  
.                { return yytext[0]; }   

%%

int yywrap() {
    return 1;
}
