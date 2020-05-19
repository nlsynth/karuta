/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SRC_FE_PARSER_H_INCLUDED
# define YY_YY_SRC_FE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    K_ADD_SUB = 258,
    K_AS = 259,
    K_ASSIGN = 260,
    K_BOOL = 261,
    K_BREAK = 262,
    K_CASE = 263,
    K_CHANNEL = 264,
    K_CONST = 265,
    K_CONTINUE = 266,
    K_DEF = 267,
    K_DEFAULT = 268,
    K_DO = 269,
    K_ELSE = 270,
    K_ENUM = 271,
    K_EQ_COMPARE = 272,
    K_FUNC = 273,
    K_FOR = 274,
    K_GOTO = 275,
    K_IF = 276,
    K_IMPORT = 277,
    K_INC_DEC = 278,
    K_INT = 279,
    K_LG_COMPARE = 280,
    K_MAILBOX = 281,
    K_OBJECT = 282,
    K_PROCESS = 283,
    K_RETURN = 284,
    K_SHARED = 285,
    K_SHIFT = 286,
    K_STRING = 287,
    K_SWITCH = 288,
    K_THREAD = 289,
    K_VAR = 290,
    K_WHILE = 291,
    K_WITH = 292,
    NUM = 293,
    SYM = 294,
    STR = 295,
    K_LOGIC_OR = 296,
    K_LOGIC_AND = 297,
    K_BIT_CONCAT = 298,
    SIGN = 299,
    ADDRESS = 300
  };
#endif
/* Tokens.  */
#define K_ADD_SUB 258
#define K_AS 259
#define K_ASSIGN 260
#define K_BOOL 261
#define K_BREAK 262
#define K_CASE 263
#define K_CHANNEL 264
#define K_CONST 265
#define K_CONTINUE 266
#define K_DEF 267
#define K_DEFAULT 268
#define K_DO 269
#define K_ELSE 270
#define K_ENUM 271
#define K_EQ_COMPARE 272
#define K_FUNC 273
#define K_FOR 274
#define K_GOTO 275
#define K_IF 276
#define K_IMPORT 277
#define K_INC_DEC 278
#define K_INT 279
#define K_LG_COMPARE 280
#define K_MAILBOX 281
#define K_OBJECT 282
#define K_PROCESS 283
#define K_RETURN 284
#define K_SHARED 285
#define K_SHIFT 286
#define K_STRING 287
#define K_SWITCH 288
#define K_THREAD 289
#define K_VAR 290
#define K_WHILE 291
#define K_WITH 292
#define NUM 293
#define SYM 294
#define STR 295
#define K_LOGIC_OR 296
#define K_LOGIC_AND 297
#define K_BIT_CONCAT 298
#define SIGN 299
#define ADDRESS 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "src/fe/parser.ypp" /* yacc.c:1909  */

  class ArrayInitializer *array;
  class ArrayShape *shape;
  class Expr *expr;
  class ExprSet *expr_set;
  class EnumDecl *enum_decl;
  class Stmt *stmt;
  class VarDecl *var_decl;
  class VarDeclSet *var_decl_set;
  class NstBlock *block;
  const char *str;
  sym_t sym;
  iroha::NumericLiteral num;
  int id;
  int sub_op;
  struct WidthSpec width_spec;
  class Annotation *annotation;
  class AnnotationKeyValue *annotation_value;
  class AnnotationKeyValueSet *annotation_value_set;

#line 165 "src/fe/parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FE_PARSER_H_INCLUDED  */
