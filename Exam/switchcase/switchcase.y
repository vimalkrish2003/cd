%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
%}

%token SWITCH CASE DEFAULT BREAK RETURN LE GE EQ NE ID NUM LBRACE RBRACE LPAREN RPAREN COLON SEMICOLON

%%

S : SWITCH LPAREN ID RPAREN LBRACE CASES RBRACE RETURN NUM SEMICOLON { printf("Switch-case statement accepted.\n"); }
  ;

CASES : CASES CASEBLOCK
      | CASEBLOCK
      ;

CASEBLOCK : CASE NUM COLON BODY BREAK SEMICOLON
          | DEFAULT COLON BODY BREAK SEMICOLON
          ;

BODY : BODY STATEMENT
     | STATEMENT
     ;

STATEMENT : ID '=' E SEMICOLON
          | E SEMICOLON
          ;

E : E '+' E
  | E '-' E
  | E '*' E
  | E '/' E
  | E LE E
  | E GE E
  | E EQ E
  | E NE E
  | ID
  | NUM
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter the switch-case statement:\n");
    yyparse();
    return 0;
}
