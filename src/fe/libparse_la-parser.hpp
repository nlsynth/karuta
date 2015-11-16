/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_Z_YY_SRC_FE_LIBPARSE_LA_PARSER_HPP_INCLUDED
# define YY_Z_YY_SRC_FE_LIBPARSE_LA_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int z_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    K_DEF = 258,
    K_ENUM = 259,
    K_IMPORT = 260,
    K_STRUCT = 261,
    K_ASSIGN = 262,
    K_SHIFT = 263,
    K_INT = 264,
    K_BOOL = 265,
    K_STRING = 266,
    K_OBJECT = 267,
    K_THREAD = 268,
    K_CHANNEL = 269,
    K_ADD_SUB = 270,
    K_LG_COMPARE = 271,
    K_EQ_COMPARE = 272,
    K_INC_DEC = 273,
    K_CONST = 274,
    K_IF = 275,
    K_ELSE = 276,
    K_RETURN = 277,
    K_GOTO = 278,
    K_FOR = 279,
    K_SPAWN = 280,
    K_WHILE = 281,
    K_DO = 282,
    K_CONTINUE = 283,
    K_SWITCH = 284,
    K_CASE = 285,
    K_DEFAULT = 286,
    K_BREAK = 287,
    NUM = 288,
    SYM = 289,
    STR = 290,
    K_LOGIC_OR = 291,
    K_LOGIC_AND = 292,
    K_BIT_CONCAT = 293,
    SIGN = 294,
    ADDRESS = 295
  };
#endif
/* Tokens.  */
#define K_DEF 258
#define K_ENUM 259
#define K_IMPORT 260
#define K_STRUCT 261
#define K_ASSIGN 262
#define K_SHIFT 263
#define K_INT 264
#define K_BOOL 265
#define K_STRING 266
#define K_OBJECT 267
#define K_THREAD 268
#define K_CHANNEL 269
#define K_ADD_SUB 270
#define K_LG_COMPARE 271
#define K_EQ_COMPARE 272
#define K_INC_DEC 273
#define K_CONST 274
#define K_IF 275
#define K_ELSE 276
#define K_RETURN 277
#define K_GOTO 278
#define K_FOR 279
#define K_SPAWN 280
#define K_WHILE 281
#define K_DO 282
#define K_CONTINUE 283
#define K_SWITCH 284
#define K_CASE 285
#define K_DEFAULT 286
#define K_BREAK 287
#define NUM 288
#define SYM 289
#define STR 290
#define K_LOGIC_OR 291
#define K_LOGIC_AND 292
#define K_BIT_CONCAT 293
#define SIGN 294
#define ADDRESS 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 16 "parser.ypp" /* yacc.c:1909  */

  class ArrayInitializer *array;
  class Expr *expr;
  class Stmt *stmt;
  class VarDecl *var_decl;
  class VarDeclSet *var_decl_set;
  class NstBlock *block;
  const char *str;
  sym_t sym;
  uint64_t num;
  const class numeric::Width *width;
  class import_param *import_param;
  class import_params *import_params;

#line 149 "src/fe/libparse_la-parser.hpp" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE z_yylval;

int z_yyparse (void);

#endif /* !YY_Z_YY_SRC_FE_LIBPARSE_LA_PARSER_HPP_INCLUDED  */
