%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h" 
%}

%%


[\t ]+       ;  
\n           ;  

do           return DO;
while        return WHILE;
"<="         return LE;
">="         return GE;
"=="         return EQ;
"!="         return NE;
[0-9]+       return NUM;            
[a-zA-Z][a-zA-Z0-9]* return ID;     
.            return yytext[0];       

%%


int yywrap() {
    return 1;
}


/*TO RUN
flex dowhile.l
yacc -d dowhile.y
 gcc y.tab.c lex.yy.c -lfl
 ./a.out*/