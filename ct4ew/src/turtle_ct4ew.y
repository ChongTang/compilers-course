
%{
#include <stdio.h>
#include "symtab.h"
%}

%union { int i; node *n; double d;}

%token IF ELSE WHILE PROCEDURE CALL PARAM LEFTBRACE RIGHTBRACE
%token GO TURN VAR JUMP
%token FOR STEP TO DO
%token COPEN CCLOSE
%token SIN COS SQRT
%token <d> FLOAT
%token <n> ID               
%token <i> NUMBER       
%token SEMICOLON PLUS MINUS TIMES DIV OPEN CLOSE ASSIGN LT GT LE GE EQUAL NOTEQUAL


%type <n> decl
%type <n> decllist

%%
program: head decllist stmtlist tail;

head: { printf("%%!PS Adobe\n"
               "\n"
	       "newpath\n0 0 moveto\n\n"
	       );
      };

tail: { printf("closepath\nstroke\n"); };

decllist: ;
decllist: decllist decl;

decl: VAR ID SEMICOLON { printf("/tlt%s 0 def\n",$2->symbol);} ;


stmtlist: ;
stmtlist: stmtlist stmt ;

psedothen: LEFTBRACE {printf("{ ");};

stmt: IF OPEN cond CLOSE psedothen
      stmtlist RIGHTBRACE {printf("} ");}
      ELSE LEFTBRACE {printf("{ ");}
      stmtlist RIGHTBRACE {printf("} ifelse\n");};

stmt: IF OPEN cond CLOSE psedothen
	  stmtlist RIGHTBRACE {printf("} if\n");};

stmt: WHILE {printf("{ ");}
     OPEN cond CLOSE LEFTBRACE {printf("{} {exit} ifelse\n");}
     stmtlist RIGHTBRACE {printf("} loop\n");};

stmt: PROCEDURE ID LEFTBRACE {printf("/proc%s {",$2->symbol);}
     stmtlist RIGHTBRACE {printf("} def\n");};

stmt: ID ASSIGN expr SEMICOLON {printf("/tlt%s exch store\n",$1->symbol);} ;
stmt: GO expr SEMICOLON {printf("0 rlineto\n");};
stmt: JUMP expr SEMICOLON {printf("0 rmoveto\n");};
stmt: TURN expr SEMICOLON {printf("rotate\n");};


stmt: CALL ID params SEMICOLON {printf("proc%s\n",$2->symbol);};
params: ; 
params: params param;
param: factor;

stmt: FOR ID ASSIGN expr 
          STEP expr
	  TO expr
	  DO {printf("{ /tlt%s exch store\n",$2->symbol);} 
	     stmt {printf("} for\n");};

stmt: COPEN stmtlist CCLOSE;	 

cond: expr LT expr { printf("lt\n");};
cond: expr GT expr { printf("gt\n");};
cond: expr LE expr { printf("le\n");};
cond: expr GE expr { printf("ge\n");};
cond: expr EQUAL expr { printf("eq\n");};
cond: expr NOTEQUAL expr { printf("neq\n");};

expr: expr PLUS term { printf("add ");};
expr: expr MINUS term { printf("sub ");};
expr: term;

term: term TIMES factor { printf("mul ");};
term: term DIV factor { printf("div ");};
term: factor;

factor: MINUS atomic { printf("neg ");};
factor: PLUS atomic;
factor: SIN factor { printf("sin ");};
factor: COS factor { printf("cos ");};
factor: SQRT factor { printf("sqrt ");};
factor: atomic;



atomic: OPEN expr CLOSE;
atomic: NUMBER {printf("%d ",$1);};
atomic: FLOAT {printf("%f ",$1);};
atomic: ID {printf("tlt%s ", $1->symbol);};
atomic: PARAM;


%%
int yyerror(char *msg)
{  fprintf(stderr,"Error: %s\n",msg);
   return 0;
}

int main(void)
{   yyparse();
    return 0;
}

