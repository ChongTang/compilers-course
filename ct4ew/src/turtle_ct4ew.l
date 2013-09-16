
%{
#include "symtab.h"
#include "token.h"
%}

digit           [0-9]+
id              [a-zA-Z]+[a-z0-9A-Z]*
variable        [a-z]+[a-z0-9A-Z]*
bs              [\ \t]+
%%

\/\/.*          ;
[[:space:]]     ;

GO              return GO;
TURN            return TURN; 
VAR             return VAR;
JUMP            return JUMP;
FOR             return FOR;
STEP            return STEP;
TO              return TO;
DO              return DO;
BEGIN           return COPEN;
END             return CCLOSE;


IF              return IF;
FI              return FI;
THEN            return THEN;
ELSE            return ELSE;
WHILE           return WHILE;
OD              return OD;
SWITCH          return SWITCH;
CASE            return CASE;
PROCEDURE       return PROCEDURE;



sin             return SIN;
cos             return COS;
sqrt            return SQRT;

;               return SEMICOLON;
\+              return PLUS;
-               return MINUS;
\*              return TIMES;
\/              return DIV;
\(              return OPEN;
\)              return CLOSE;
=               return ASSIGN;



\<              return LESSTHAN;
\>              return GREATERTHAN;
\{              return LEFTBRACE;
\}              return RIGHTBRACE;
,               return COMMA;

[a-z]+          { yylval.n = lookup(yytext); 
                  if (yylval.n==NULL)
		    yylval.n = insert(yytext);
                  return ID;
		}
    
[0-9]+\.[0-9]+  yylval.d = atof(yytext);  return FLOAT;
[0-9]+          yylval.i = atoi(yytext);  return NUMBER;

.               fprintf(stderr,"Unexpected character %c (%2X)\n",yytext[0],yytext[0]);

%%
