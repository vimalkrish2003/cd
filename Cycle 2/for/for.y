%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token FOR ID NUM EQ SEMI LT GT INC DEC PLUS MINUS TIMES DIV

%%

// Define grammar rules
program:
    program statement
    | /* empty */
    ;

statement:
    for_loop| 
	expression SEMI |
    ;

for_loop:
    FOR '(' init SEMI condition SEMI increment ')' '{' statement '}'
    {
        printf("accepted\n");
    }
    ;

init:
    ID EQ NUM
    ;

condition:
    ID LT NUM |
	ID GT NUM
    ;

increment:
    ID INC | 
	ID DEC
    ;

expression:
    ID EQ ID PLUS NUM |
	ID EQ ID MINUS NUM |
	ID INC |
	ID DEC 
    ;

%%

// Error handling
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter a 'for' loop:\n");
    yyparse(); // Start parsing
    return 0;
}


/* 
               To run:
yacc -d for.y
lex for.l
gcc lex.yy.c y.tab.c  -ll 
./a.out   press ctrl+d after string entered


*/