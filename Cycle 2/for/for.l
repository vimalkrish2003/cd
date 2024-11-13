%{
#include "y.tab.h"
%}

%%

for                 return FOR;
[a-zA-Z_][a-zA-Z0-9_]*  return ID;
[0-9]+              return NUM;
"="                 return EQ;
";"                 return SEMI;
"<"                 return LT;
">"                 return GT;
"++"                return INC;   // Increment operator
"--"                return DEC;   // Decrement operator
"+"                 return PLUS;
"-"                 return MINUS;
"*"                 return TIMES;
"/"                 return DIV;
[ \t\n]             ;  // Ignore whitespace
.                   return yytext[0];  // Return any other character

%%


int yywrap(void) {
    return 1;
}