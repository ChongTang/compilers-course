/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     WHILE = 260,
     PROCEDURE = 261,
     CALL = 262,
     PARAM = 263,
     LEFTBRACE = 264,
     RIGHTBRACE = 265,
     GO = 266,
     TURN = 267,
     VAR = 268,
     JUMP = 269,
     FOR = 270,
     STEP = 271,
     TO = 272,
     DO = 273,
     COPEN = 274,
     CCLOSE = 275,
     SIN = 276,
     COS = 277,
     SQRT = 278,
     FLOAT = 279,
     ID = 280,
     NUMBER = 281,
     SEMICOLON = 282,
     PLUS = 283,
     MINUS = 284,
     TIMES = 285,
     DIV = 286,
     OPEN = 287,
     CLOSE = 288,
     ASSIGN = 289,
     LT = 290,
     GT = 291,
     LE = 292,
     GE = 293,
     EQUAL = 294,
     NOTEQUAL = 295
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define PROCEDURE 261
#define CALL 262
#define PARAM 263
#define LEFTBRACE 264
#define RIGHTBRACE 265
#define GO 266
#define TURN 267
#define VAR 268
#define JUMP 269
#define FOR 270
#define STEP 271
#define TO 272
#define DO 273
#define COPEN 274
#define CCLOSE 275
#define SIN 276
#define COS 277
#define SQRT 278
#define FLOAT 279
#define ID 280
#define NUMBER 281
#define SEMICOLON 282
#define PLUS 283
#define MINUS 284
#define TIMES 285
#define DIV 286
#define OPEN 287
#define CLOSE 288
#define ASSIGN 289
#define LT 290
#define GT 291
#define LE 292
#define GE 293
#define EQUAL 294
#define NOTEQUAL 295




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 7 "turtle_ct4ew.y"
{ int i; node *n; double d;}
/* Line 1529 of yacc.c.  */
#line 131 "turtle.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

