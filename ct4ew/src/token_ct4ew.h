
/* Tokens.  */
#define GO 258
#define TURN 259
#define VAR 260
#define JUMP 261
#define FOR 262
#define STEP 263
#define TO 264
#define DO 265
#define COPEN 266
#define CCLOSE 267
#define SIN 268
#define COS 269
#define SQRT 270
#define FLOAT 271
#define ID 272
#define NUMBER 273
#define SEMICOLON 274
#define PLUS 275
#define MINUS 276
#define TIMES 277
#define DIV 278
#define OPEN 279
#define CLOSE 280
#define ASSIGN 281

/*Defined by Chong*/
#define WHILE 282
#define IF 283
#define ELSE 284
#define PROCEDURE 285
#define THEN    286
#define LT 287
#define GT 288
#define LE 289
#define GE 290
#define SWITCH 291
#define CASE 292
#define COMMA   293
#define LEFTBRACE   294
#define RIGHTBRACE   295
#define EQUAL 296
#define NOTEQUAL 297
#define CALL 298
#define PARAM 299

typedef union YYSTYPE
{ int i; node *n; double d;}
        YYSTYPE;
YYSTYPE yylval;

