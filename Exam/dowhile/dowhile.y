%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
%}

%token ID NUM DO WHILE LE GE EQ NE

%%


S : DO '{' BODY '}' WHILE '(' E ')' ';' { printf("Do-While loop accepted\n"); }
  ;


BODY : BODY E ';' 
     | E ';'
     ;


E : ID '=' E
  | E '+' E
  | E '-' E
  | E '*' E
  | E '/' E
  | E LE E
  |E  GE E
  |E NE E
  |E EQ E
  | ID
  | NUM
  ;

%%


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}


int main() {
    printf("Enter the do-while statement:\n");
    yyparse();
    return 0;
}