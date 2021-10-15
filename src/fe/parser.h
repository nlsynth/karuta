/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_SRC_FE_PARSER_H
# define YY_SRC_FE_PARSER_H
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
    K_ALWAYS = 259,
    K_AS = 260,
    K_ASSIGN = 261,
    K_BOOL = 262,
    K_BREAK = 263,
    K_CASE = 264,
    K_CHANNEL = 265,
    K_CONST = 266,
    K_CONTINUE = 267,
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
    K_UINT = 280,
    K_TYPE = 281,
    K_LG_COMPARE = 282,
    K_MAILBOX = 283,
    K_OBJECT = 284,
    K_PROCESS = 285,
    K_RETURN = 286,
    K_SHARED = 287,
    K_SHIFT = 288,
    K_STRING = 289,
    K_SWITCH = 290,
    K_THREAD = 291,
    K_INPUT = 292,
    K_OUTPUT = 293,
    K_VAR = 294,
    K_WHILE = 295,
    K_WITH = 296,
    K_MODULE = 297,
    NUM = 298,
    SYM = 299,
    STR = 300,
    K_LOGIC_OR = 301,
    K_LOGIC_AND = 302,
    K_BIT_CONCAT = 303,
    SIGN = 304,
    ADDRESS = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "src/fe/parser.ypp"

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

#line 129 "src/fe/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_SRC_FE_PARSER_H  */
